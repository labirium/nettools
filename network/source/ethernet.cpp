#include <network/include/precompiled.h>

#include <pcap/pcap.h>
#include <iphlpapi.h>
#include <assert.h>

using namespace network;
using namespace network::ethernet;

namespace
{
/// @brief Возвращает свойства интерфейса
///
/// @param[in] interface интерфейс на обработку
InterfaceProfilesList GetInterfaceProfiles(const pcap_if_t* interface)
{
	InterfaceProfilesList data;

	if (0x00 == interface && 0x00 == interface->addresses){
		return std::move(data);
	}

	// check if the device captureble
	for (pcap_addr_t * dev_addr = interface->addresses; dev_addr != NULL; dev_addr = dev_addr->next) {

		if (dev_addr->addr->sa_family != AF_INET || 0x00 == dev_addr->addr || 0x00 == dev_addr->netmask) {
			continue;
		}

		struct sockaddr_in* sockaddr = reinterpret_cast<struct sockaddr_in*>(dev_addr->addr);
		struct sockaddr_in* sockmask = reinterpret_cast<struct sockaddr_in*>(dev_addr->netmask);
		if (0 == sockaddr->sin_addr.S_un.S_addr || 0 == sockmask->sin_addr.S_un.S_addr || 0xFF == sockmask->sin_addr.S_un.S_addr){
			continue;
		}

		data.push_back(std::make_shared<InterfaceProfiles>(sockaddr->sin_addr, sockmask->sin_addr));
	}

	return std::move(data);
}
}

bool network::ethernet::GetIndexInterface(const std::string& name, uint64_t& index, bool& isVpn)
{
	PIP_ADAPTER_INFO adapterInfo = NULL;

	DWORD dwActualInfoSize = 0;
	if (GetAdaptersInfo(adapterInfo, &dwActualInfoSize) != ERROR_BUFFER_OVERFLOW){
		return false;
	}

	if (0 == dwActualInfoSize){
		return false;
	}

	std::vector<uint8_t> adapter(dwActualInfoSize, 0);
	adapterInfo = (PIP_ADAPTER_INFO)adapter.data();
	if (GetAdaptersInfo(adapterInfo, &dwActualInfoSize) != NO_ERROR){
		return false;
	}

	PIP_ADAPTER_INFO pAdapter = adapterInfo;
	while (pAdapter) {

		if (0 == pAdapter || name.find(pAdapter->AdapterName) == std::string::npos){
			pAdapter = pAdapter->Next;
			continue;
		}

		index = pAdapter->Index;
		isVpn = pAdapter->Type == MIB_IF_TYPE_PPP ? true : false;
		return true;
	}

	return false;
}

MacAddress network::ethernet::GetMacAddress(const std::string& name)
{
	DWORD size = 0;
	GetAdaptersInfo(NULL, &size);
	if (0 == size){
		return MacAddress();
	}

	std::vector<int8_t> data(size, 0x00);
	IP_ADAPTER_INFO *info = reinterpret_cast<IP_ADAPTER_INFO*>(data.data());

	if (GetAdaptersInfo(info, &size) != NO_ERROR){
		return MacAddress();
	}

	for (IP_ADAPTER_INFO* pos = info; pos != NULL; pos = pos->Next) {

		if (name.find(pos->AdapterName) == std::string::npos || 0 == pos->AddressLength){
			continue;
		}

		MacAddress data(pos->AddressLength, 0x00);
		memcpy(data.data(), pos->Address, pos->AddressLength);
		return std::move(data);
	}

	return MacAddress();
}

EthernetProfileList network::ethernet::GetEthernetProfileList(void)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	memset(errbuf, 0x00, sizeof(errbuf));

	// Retrieve the device list from the local machine
	pcap_if_t *alldevs = NULL;
	if (pcap_findalldevs(&alldevs, errbuf) == -1){
		throw std::runtime_error(errbuf);
	}

	if (alldevs == NULL){
		return EthernetProfileList();
	}

	EthernetProfileList profile;
	for (pcap_if_t *interface = alldevs; interface != NULL; interface = interface->next)
	{
		if (0x00 == interface || 0x00 == interface->name){
			continue;
		}

		const auto interfaceProfiles = GetInterfaceProfiles(interface);
		if (interfaceProfiles.empty()){
			continue;
		}

		std::string name(interface->name);
		std::string description(interface->description ? interface->description : "");

		//получаем физический адрес
		const auto macAddress = GetMacAddress(name);
		//получаем индекс сетевого интерфейса
		uint64_t index = 0;
		bool isVpn = false;
		if (!GetIndexInterface(name, index, isVpn)){
			assert(!"Invalid get index for interface");
			continue;
		}

		profile.emplace_back(std::make_shared<EthernetProfile>(index, name, description, macAddress, isVpn, interfaceProfiles));
	}

	// We don't need any more the device list. Free it 
	pcap_freealldevs(alldevs);

	return std::move(profile);
}
