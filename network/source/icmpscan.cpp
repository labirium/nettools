
#include <network/include/precompiled.h>

#include <assert.h>
#include <pcap/pcap.h>
#include <network/include/icmpheader.h>


using namespace network;
using namespace network::icmp;
using namespace network::tools;

namespace
{
/// @brief Осуществляет отправку arp запросов
///
bool SendPacketProbe(const SOCKET socket, const struct in_addr& dst)
{
	const auto icmpPacket = network::icmp::СreateIcmpPacket(0);

	struct sockaddr_in dest;
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr = dst;
	dest.sin_family = AF_INET;
	
	const uint32_t bwrote = sendto(socket, &icmpPacket[0], static_cast<int>(icmpPacket.size()), 0, (struct sockaddr*)&dest, sizeof(dest));
	if (bwrote == SOCKET_ERROR)
	{
		network::logger::Error("sendto failed: %d", WSAGetLastError());
		return false;
	}

	return true;
}

int ScanIcmpInterface(const SOCKET socket, const network::EthernetProfileList::value_type& ethernetProfile)
{
	int count = 0;

	for (const auto interface : ethernetProfile->GetInterfaceProfilesList()){

		auto countIp = GetCountIp(interface);
		if (countIp > 0xFFFF){
			assert(!"Invalid logic");
			continue;
		}

		for (auto currentIp = ntohl(GetStartIp(interface)); currentIp < ntohl(GetEndIp(interface)); ++currentIp){

			struct in_addr dstIp;
			dstIp.S_un.S_addr = ntohl(currentIp);

			if (!SendPacketProbe(socket, dstIp)){
				continue;
			}

			if (count > 0xFFFF){
				break;
			}

			++count;
		}
	}

	return count;
}

HostProfilePtr CheckResp(const std::vector<char>& recvbuf)
{
	network::icmp::ip * iphdr = (network::icmp::ip *)&recvbuf[0];
	const uint16_t iphdrlen = iphdr->ip_hl * 4;

	const std::vector<char>::size_type sizedata = iphdrlen + ICMP_MIN_SIZE;
	if (recvbuf.size()  < sizedata){
		return HostProfilePtr();
	}

	network::icmp::icmp *icmphdr = (network::icmp::icmp*)(&recvbuf[0] + iphdrlen);
	if (icmphdr->icmp_type != ICMP_REPLY){
		return HostProfilePtr();
	}
	
	struct in_addr ip;
	memset(&ip, 0x00, sizeof(ip));
	ip.S_un.S_addr = iphdr->ip_src;

	return std::make_shared<HostProfile>(ip, MacAddress(), ::time(0x00));
}

HostProfileList ReadIcmpPacket(const SOCKET socket, const time_t time)
{
	const time_t start = ::time(0x00);

	HostProfileList hostList;

	do
	{
		if (::time(0x00) - start > time){
			break;
		}

		std::vector<char> recvbuf(65000);

		struct sockaddr_in recv_from;
		int32_t from_len = sizeof(recv_from);
		const int32_t bytes_read = recvfrom(socket, &recvbuf[0], static_cast<int>(recvbuf.size()), 0, (struct sockaddr*)&recv_from, &from_len);
		if (bytes_read == SOCKET_ERROR)
		{
			network::logger::Error("recvfrom failed: %d", WSAGetLastError());
			break;
		}
				
		const auto host = CheckResp(recvbuf);
		host ? hostList.push_back(host) : (void)host;

	} while (true);

	return std::move(hostList);
}

HostProfileList scanProbe(const SOCKET socketSend, const SOCKET socketRead, const network::EthernetProfileList::value_type& ethernetProfile, const time_t time)
{
	if (!ethernetProfile){
		network::logger::Error("Invalid input data.");
		return HostProfileList();
	}

	if (ScanIcmpInterface(socketSend, ethernetProfile) == 0){
		return HostProfileList();
	}

	return ReadIcmpPacket(socketRead, time);
}

}

EthernetHostProfileList network::icmp::ScanIcmpProbe(const EthernetProfileList& ethernetsProfiles)
{
	const uint32_t timeout = 1000;
	const time_t maxWait = 4;

	const SOCKET socketSend = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, 0);
	if (socketSend == INVALID_SOCKET)
	{
		network::logger::Error("WSASocket() failed: %d", WSAGetLastError());
		return EthernetHostProfileList();
	}
		
	int32_t result = setsockopt(socketSend, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
	if (result == SOCKET_ERROR)
	{
		network::logger::Error("Failed to set send timeout: %d", WSAGetLastError());
		closesocket(socketSend);
		return EthernetHostProfileList();
	}

	const SOCKET socketRead = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, 0);
	if (socketRead == INVALID_SOCKET)
	{
		network::logger::Error("Invalid create socket: %d", WSAGetLastError());
		closesocket(socketSend);
		return EthernetHostProfileList();
	}

	result = setsockopt(socketRead, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
	if (result == SOCKET_ERROR)
	{
		network::logger::Error("Failed to set send timeout: %d", WSAGetLastError());
		closesocket(socketSend);
		closesocket(socketRead);
		return EthernetHostProfileList();
	}


	struct sockaddr_in socket_listen_address;
	socket_listen_address.sin_family = AF_INET;
	socket_listen_address.sin_addr.s_addr = htonl(INADDR_ANY);
	socket_listen_address.sin_port = htons(0);

	if (bind(socketRead, (SOCKADDR*)&socket_listen_address, sizeof(socket_listen_address)) == SOCKET_ERROR)
	{
		network::logger::Error("bind failed: %d\n", WSAGetLastError());
		closesocket(socketSend);
		closesocket(socketRead); 

		return EthernetHostProfileList();
	}
	
	EthernetHostProfileList data;
	for (const auto ethernetsHostProfile : ethernetsProfiles){
		
		const auto hostProfiles = scanProbe(socketSend, socketRead, ethernetsHostProfile, maxWait);
		data.insert({ ethernetsHostProfile, hostProfiles });
	}


	closesocket(socketSend);
	closesocket(socketRead);
	WSACleanup();

	return std::move(data);
}

EthernetHostProfileList network::icmp::ScanIcmpProbe(void)
{
	return network::icmp::ScanIcmpProbe(network::ethernet::GetEthernetProfileList());
}


