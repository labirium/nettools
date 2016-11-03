#include <network/include/precompiled.h>
#include <network/include/manager.h>
#include <algorithm> 
#include <thread>
#include <atomic>

using namespace network;

namespace
{
/// @brief Возвращает уникальное значеие задачи
///
IdScanTask CreateIdScanTask(void)
{
	static std::atomic<IdScanTask> idScanTask = 0;
	return ++idScanTask;
}
}

network::EthernetProfileList Manager::GetEthernetProfileList(void) const
{
	return network::ethernet::GetEthernetProfileList();
}

HostProfileList Manager::GetHostProfileList(const uint64_t index) const
{
	return hostProfileManager_->GetHostProfileList(index);
}

HostProfileList Manager::GetHostProfileList(const EthernetProfilePtr& ethernetProfile) const
{
	if (!ethernetProfile){
		return HostProfileList();
	}

	return GetHostProfileList(ethernetProfile->GetIndex());
}

IdScanTask Manager::AddTask(const network::enums::TypeScan typeScan)
{
	switch (typeScan)
	{
	case network::enums::ArpHost:
	{
		return task_->AddTask(typeScan, hostProfileManager_);
	}
	case network::enums::Arp:
	case network::enums::Icmp:
	{
		return task_->AddThreadTask(typeScan, hostProfileManager_);
	}
	default:
		break;
	}

	return INVALID_HANDLE;
}

bool Manager::IsTask(const IdScanTask idScan) const
{
	return task_->IsTask(idScan);
}

Manager::Manager() : task_(std::make_shared<Task>()), hostProfileManager_(std::make_shared<HostProfileManager>())
{
	assert(task_ && "Invalid input data.");
}

Manager::~Manager()
{
}
