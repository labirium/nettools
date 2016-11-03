#include <network/include/precompiled.h>
#include <ws2tcpip.h>

using namespace network;

time_t HostProfile::GetTime(void) const
{
	return time_;
}

const struct in_addr& HostProfile::GetIp(void) const
{
	return ip_;
}

const MacAddress& HostProfile::GetMacAddress(void) const
{
	return mac_;
}

HostProfile::HostProfile(const struct in_addr& ip, const MacAddress& mac, const time_t time)
	: ip_(ip), mac_(mac), time_(time)
{

}

HostProfile::~HostProfile()
{
}
