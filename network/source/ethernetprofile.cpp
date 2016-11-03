#include <network/include/precompiled.h>

using namespace network;

uint64_t EthernetProfile::GetIndex(void) const
{
	return index_;
}

const InterfaceProfilesList& EthernetProfile::GetInterfaceProfilesList(void) const
{
	return interfaceProfiles_;
}

const std::string& EthernetProfile::GetDescription(void) const
{
	return description_;
}

const std::string& EthernetProfile::GetName(void) const
{
	return name_;
}

const MacAddress& EthernetProfile::GetMacAddress(void) const
{
	return macAddress_;
}

bool EthernetProfile::IsVpn(void) const
{
	return isVpn_;
}

EthernetProfile::EthernetProfile(const uint64_t index, const std::string& name, const std::string& description, const MacAddress& macAddress, const bool isVpn, const InterfaceProfilesList& interfaceProfiles)
	: index_(index), name_(name), description_(description), macAddress_(macAddress), isVpn_(isVpn), interfaceProfiles_(interfaceProfiles)
{

}

EthernetProfile::~EthernetProfile()
{

}

