
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <functional>


struct sockaddr_in;

namespace network
{

typedef enum tagProtectedLevel
{
	Unknown,
	Normal,
	TrustedVendors,
	Strict

}ProtectedLevel;

namespace protocol
{
class RpcClient;
/// указатель на описание клиенского подключени€
typedef std::shared_ptr<RpcClient> RpcClientPtr;

/// ќписание структуры данных
typedef std::map<std::wstring, std::wstring> MapData;
}

class RemoveHost;
/// ”казатель на сетевой узел
typedef std::shared_ptr<RemoveHost> RemoveHostPtr;

class RemoveHostProfile;
/// указатель на свойства удаленного узла
typedef std::shared_ptr<RemoveHostProfile> RemoveHostProfilePtr;

class RemoveHostProfileManager;
/// ”казатель на свойства удаленных узлов
typedef std::shared_ptr<RemoveHostProfileManager> RemoveHostProfileManagerPtr;
typedef std::map<RemoveHost, RemoveHostProfilePtr> RemoveHostList;


typedef std::function<void(const std::string& ethernetId, const std::string& host, const network::protocol::MapData& data)> RpcCallback;
typedef std::shared_ptr<RpcCallback> RpcCallbackPtr;

/// @brief ќписание типа сканировани€
typedef int IdScanTask;

class EthernetProfile;
/// @brief ”казатель на свойства ethernet
typedef std::shared_ptr<EthernetProfile> EthernetProfilePtr;
/// @brief —писок на свойства ethernet
typedef std::vector<EthernetProfilePtr> EthernetProfileList;

class InterfaceProfiles;
/// @brief ”казатель cетевые настройки интерфейса
typedef std::shared_ptr<InterfaceProfiles> InterfaceProfilesPtr;
/// @brief —писок на cетевые настройки интерфейса
typedef std::vector<InterfaceProfilesPtr> InterfaceProfilesList;

/// @brief BLOB Mac адрес
typedef std::vector<char> MacAddress;

class HostProfile;
/// @brief ”казатель на описание хоста
typedef std::shared_ptr<HostProfile> HostProfilePtr;
/// @brief —писок узлов
typedef std::vector<HostProfilePtr> HostProfileList;

/// @brief —оотвествие сетевого интерфейса с найденными узлами
typedef std::map<EthernetProfilePtr, HostProfileList> EthernetHostProfileList;

/// @brief ”казатель на класс осуществл€ющий обработку задачи
class Task;
typedef std::shared_ptr<Task> TaskPtr;

/// @brief ”казатель на класс содержащий данные результата сканировани€
class HostProfileManager;
typedef std::shared_ptr<HostProfileManager> HostProfileManagerPtr;

/// @brief ”казатель на класс осуществл€ющий поиск устройств в сети
class Manager;
typedef std::shared_ptr<Manager> ManagerPtr;
/// @brief —писок задач
typedef std::set<IdScanTask> IdScanTaskList;

namespace icmp
{
/// @brief Blob пакет
typedef std::vector<char> BlobPacket;
}

}