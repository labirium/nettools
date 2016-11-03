#include <network/include/precompiled.h>

using namespace network;

void HostProfileManager::ChangeEthernetHostProfile(const IdScanTask task, const EthernetHostProfileList& hostProfile)
{
	//выставляем локер
	std::lock_guard<std::mutex> lock(guard_);
	ethernetHostsProfile_ = hostProfile;
}

HostProfileList HostProfileManager::GetHostProfileList(const uint64_t index) const
{
	for (auto data : ethernetHostsProfile_)
	{
		if (data.first->GetIndex() == index){
			return data.second;
		}	
	}

	return HostProfileList();
}

HostProfileManager::HostProfileManager()
{
	ChangeEthernetHostProfile(network::enums::ArpHost, network::ArpHostTableProbe());
}

HostProfileManager::~HostProfileManager()
{
}
