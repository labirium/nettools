
#include <network/include/precompiled.h>

#include <pcap/pcap.h>

#include <iphlpapi.h>
#include <stdio.h>
#include <assert.h>

using namespace network;
using namespace network::arp;
using namespace network::tools;
using namespace network::ethernet;

/// @brief Осуществляет отправку arp запросов
///
/// @param[in] pcap хендел на сетевой интерфейс
/// @param[in] source ip адрес отправителя
/// @param[in] srcMac физический адрес отправителя
/// @param[in] dspIp ip адрес получателя
/// @return Возвращает true при успешном отправке пакета
bool SendArpScanProbe(pcap_t * pcap, const struct in_addr& source, const MacAddress& srcMac, const struct in_addr& dspIp)
{
	uint8_t frame[ETH_HDR_LEN + ARP_HDR_LEN + ARP_ETHIP_LEN];
	memset(frame, 0x00, sizeof(frame));

	eth_pack_hdr_f(frame, ETH_ADDR_BROADCAST, srcMac.data(), ETH_TYPE_ARP);
	arp_pack_hdr_ethip_f(frame + ETH_HDR_LEN, ARP_OP_REQUEST, srcMac.data(), source, ETH_ADDR_EMPTY, dspIp);

	// Send down the packet 
	if (pcap_sendpacket(pcap, frame, sizeof(frame)) != 0)
	{
		network::logger::Error("Error sending the packet : %s", pcap_geterr(pcap));
		return false;
	}

	return true;
}

/// @brief Осуществляет отправку arp запросов
///
/// @param[in] pcap хендел на сетевой интерфейс
/// @param[in] ethernetProfile описание сетевого интерфейса
/// @return Возвращает количество успешных отправленных пакетов
int ScanArpInterface(pcap_t * pcap, const EthernetProfileList::value_type& ethernetProfile)
{
	int count = 0;

	for (const auto interface : ethernetProfile->GetInterfaceProfilesList()){

		const auto countIp = GetCountIp(interface);
		if (countIp > 0xFFFF){
			assert(!"Invalid logic");
			continue;
		}
		
		for (auto currentIp = ntohl(GetStartIp(interface)); currentIp < ntohl(GetEndIp(interface)); ++currentIp){

			struct in_addr dstIp;
			dstIp.S_un.S_addr = ntohl(currentIp);

			if (!SendArpScanProbe(pcap, interface->GetIp(), ethernetProfile->GetMacAddress(), dstIp)){
				continue;
			}

			++count;
		}
	}

	return count;
}

/// @brief Осуществляет считывание arp запросов с сетевого интерфейса
///
/// @param[in] pcap хендел на сетевой интерфейс
/// @return Возвращает результат сканирования
HostProfileList ReadArpPacket(pcap_t * pcap)
{

	HostProfileList hostProfiles;

	struct pcap_pkthdr pkthdr;
	const unsigned char *packet = NULL;
	while ((packet = pcap_next(pcap, &pkthdr)) != NULL)
	{
		const struct arp_hdr *arpheader = reinterpret_cast<const struct arp_hdr *>(packet + ETH_HDR_LEN);
		const struct arp_ethip *pack_ethip_p = reinterpret_cast<const struct arp_ethip *>((uint8_t *)(arpheader)+ARP_HDR_LEN);

		if ((ntohs(arpheader->ar_op) != ARP_OP_REPLY || (ntohs(arpheader->ar_pro) != ETH_TYPE_IP) || !(ntohs(arpheader->ar_hrd) != ARP_OP_REPLY))){
			continue;
		}

		struct in_addr spa;
		memcpy(&spa, pack_ethip_p->ar_spa, IP_ADDR_LEN);
		

		MacAddress macAddress(ETH_ADDR_LEN, 0);
		memcpy(&macAddress[0], pack_ethip_p->ar_sha, ETH_ADDR_LEN);

		hostProfiles.push_back(std::make_shared<HostProfile>(spa, macAddress, time(0x00)));
	}
	
	return std::move(hostProfiles);
}

/// @brief Осуществляет сканирование на заданном сетевом интерфейсе
///
/// @param[in] ethernetProfile свойства сетевого интерфейса
/// @param[out] результат сканирования
/// @return Возвращаеь результат при успешном сканировании
bool sendArpScanProbe(const network::EthernetProfileList::value_type& ethernetProfile, HostProfileList& hostProfiles)
{
	if (!ethernetProfile){
		return false;
	}
	
	pcap_t *pcap;
	char errbuf[PCAP_ERRBUF_SIZE];
	memset(errbuf, 0x00, sizeof(errbuf));

	// Open the adapter 
	if ((pcap = pcap_open_live( ethernetProfile->GetName().c_str(), 65536, 0, 1000,	errbuf )) == NULL){
		
		network::logger::Error("ERROR: %s", errbuf);
		return false;
	}

	struct bpf_program filter;
	if (pcap_compile(pcap, &filter, "arp", 1, 0) == -1){

		network::logger::Error("ERROR: %s", pcap_geterr(pcap));
		
		pcap_close(pcap);
		return false;
	}

	if (pcap_setfilter(pcap, &filter) == -1)
	{
		network::logger::Error("ERROR: %s", pcap_geterr(pcap));

		pcap_close(pcap);
		return false;
	}

	if (ScanArpInterface(pcap, ethernetProfile) == 0){
		pcap_close(pcap);
		return true;
	}

	auto hosts = ReadArpPacket(pcap);
	hostProfiles.swap(hosts);

	pcap_close(pcap);

	return true;
}

EthernetHostProfileList network::ArpHostTableProbe(void)
{
	EthernetHostProfileList data;

	for (const auto ethernetProfile : GetEthernetProfileList())
	{
		HostProfileList hostProfiles;
		if (!GetArpHostTalbeForInterface(ethernetProfile, hostProfiles)){
			continue;
		}

		data.insert({ ethernetProfile, hostProfiles });
	}

	return std::move(data);
}

EthernetHostProfileList network::ArpScanProbe(void)
{
	EthernetHostProfileList data;

	for(const auto ethernetProfile : GetEthernetProfileList())
	{
		HostProfileList hostProfiles;
		if (!sendArpScanProbe(ethernetProfile, hostProfiles)){
			continue;
		}

		data.insert( { ethernetProfile,hostProfiles} );
	}

	return std::move(data);
}