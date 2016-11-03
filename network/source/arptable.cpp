#include <network/include/precompiled.h>

#include <winsock2.h>
#include <iphlpapi.h>

using namespace network;

bool network::GetArpHostTalbeForInterface(const EthernetProfilePtr& ethernetProfile, HostProfileList& hosts)
{
	PMIB_IPNETTABLE pIpArpTab = NULL;

	DWORD dwActualInfoSize = 0;
	GetIpNetTable(pIpArpTab, &dwActualInfoSize, true);

	if (0 == dwActualInfoSize){
		return false;
	}

	std::vector<uint8_t> adapter(dwActualInfoSize, 0);
	pIpArpTab = (PMIB_IPNETTABLE)adapter.data();
	if (GetIpNetTable(pIpArpTab, &dwActualInfoSize, true) != NO_ERROR){
		return false;
	}

	HostProfileList hostProfileList;
	for (DWORD index = 0; index < pIpArpTab->dwNumEntries; ++index)
	{
		if (pIpArpTab->table[index].dwIndex != ethernetProfile->GetIndex() || pIpArpTab->table[index].dwType != MIB_IPNET_TYPE_DYNAMIC){
			continue;
		}

		struct in_addr ip;
		ip.S_un.S_addr = pIpArpTab->table[index].dwAddr;
		
		MacAddress macAddress(ETH_ADDR_LEN, 0x00);
		memcpy(&macAddress[0], (const void*)pIpArpTab->table[index].bPhysAddr, ETH_ADDR_LEN);

		hostProfileList.push_back(std::make_shared<HostProfile>(ip, macAddress, time(0x00)));
 	}

	hosts.swap(hostProfileList);

	return true;
}
