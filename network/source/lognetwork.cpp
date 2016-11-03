#include <network/include/precompiled.h>

#include <assert.h>
#include <pcap/pcap.h>

using namespace network;
using namespace network::logger;
using namespace network::tools;

void network::logger::Info(const char*, ...) throw()
{
}

void network::logger::Warning(const char*, ...) throw()
{

}

void network::logger::Error(const char*, ...)throw()
{

}


void network::logger::dump(const HostProfilePtr& host) throw()
{
	if (!host){
		assert(!"Invalid input data");
		return;
	}

	printf("\nMAC: ");
	for (const uint8_t data : host->GetMacAddress()) {
		printf("%02X:", data);
	}

	auto ipData = host->GetIp();

	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &ipData, str, INET_ADDRSTRLEN);

	printf("\nIP: %s\n", str);
	printf("Time Stamp: %d\n", host->GetTime());
}

void network::logger::dump(const HostProfileList& hostProfiles) throw()
{
	for (const auto data : hostProfiles){
		dump(data);
	}
}

void network::logger::dump(const EthernetProfilePtr& ethernetProfile) throw()
{
	if (!ethernetProfile){
		assert(!"Invalid input data");
		return;
	}

	printf("\nName: %s\n", ethernetProfile->GetName().c_str());
	printf("Description: %s\n", ethernetProfile->GetDescription().c_str());
	printf("Mac:");
	for (const uint8_t data : ethernetProfile->GetMacAddress()) {
		printf("%02X:", data);
	}

	printf("\n");

	for (const auto data : ethernetProfile->GetInterfaceProfilesList()) {
		printf("Ip: %s\n", GetIpStr(data).c_str());
	}

}

void network::logger::dump(const EthernetHostProfileList& ethernetHostProfile) throw()
{
	for (const auto data : ethernetHostProfile){
		dump(data.first);
		dump(data.second);
	}
}
