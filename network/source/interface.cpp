#include <network/include/precompiled.h>

using namespace network;

const struct in_addr& InterfaceProfiles::GetIp(void) const
{
	return ip_;
}

const struct in_addr& InterfaceProfiles::GetMask(void) const
{
	return mask_;
}

InterfaceProfiles::InterfaceProfiles(const unsigned long ip, const  unsigned long mask)
{
	ip_.S_un.S_addr = ip;
	mask_.S_un.S_addr = mask;
}

InterfaceProfiles::InterfaceProfiles(const struct in_addr& ip, const struct in_addr& mask)
	: ip_(ip), mask_(mask)
{

}

InterfaceProfiles::~InterfaceProfiles()
{

}
