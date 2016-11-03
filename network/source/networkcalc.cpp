
#include <network/include/precompiled.h>
#include <assert.h>
#include <ws2tcpip.h>

using namespace network;
using namespace network::tools;

std::string network::tools::GetMaskStr(const InterfaceProfilesPtr& data)
{
	assert(data && "Invalid input data.");

	auto in = data->GetMask();

	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &in, str, INET_ADDRSTRLEN);

	return str;
}

std::string network::tools::GetIpStr(const InterfaceProfilesPtr& data)
{
	assert(data && "Invalid input data.");

	auto in = data->GetIp();

	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &in, str, INET_ADDRSTRLEN);

	return str;
}

std::string network::tools::GetIpStr(const network::HostProfilePtr& data)
{
	assert(data && "Invalid input data.");

	auto in = data->GetIp();

	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &in, str, INET_ADDRSTRLEN);

	return str;
}

uint32_t network::tools::GetStartIp(const InterfaceProfilesPtr& interface)
{
	assert(interface && "Invalid input data.");

	const auto ip = interface->GetIp();
	const auto mask = interface->GetMask();
	
	const auto ipstart = ntohl(ip.S_un.S_addr & mask.S_un.S_addr) + 1;
	return ntohl(ipstart);
}

uint32_t network::tools::GetCountIp(const InterfaceProfilesPtr& interface)
{
	assert(interface && "Invalid input data.");

	const auto mask = interface->GetMask();
	return (~ntohl(mask.S_un.S_addr)) - 1;
}

uint32_t network::tools::GetEndIp(const InterfaceProfilesPtr& interface)
{
	assert(interface && "Invalid input data.");

	const auto startIp = ntohl(GetStartIp(interface));
	return ntohl(startIp + GetCountIp(interface));
}
