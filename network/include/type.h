
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
/// указатель на описание клиенского подключения
typedef std::shared_ptr<RpcClient> RpcClientPtr;

/// Описание структуры данных
typedef std::map<std::wstring, std::wstring> MapData;
}

class RemoveHost;
/// Указатель на сетевой узел
typedef std::shared_ptr<RemoveHost> RemoveHostPtr;

class RemoveHostProfile;
/// указатель на свойства удаленного узла
typedef std::shared_ptr<RemoveHostProfile> RemoveHostProfilePtr;

class RemoveHostProfileManager;
/// Указатель на свойства удаленных узлов
typedef std::shared_ptr<RemoveHostProfileManager> RemoveHostProfileManagerPtr;
typedef std::map<RemoveHost, RemoveHostProfilePtr> RemoveHostList;


typedef std::function<void(const std::string& ethernetId, const std::string& host, const network::protocol::MapData& data)> RpcCallback;
typedef std::shared_ptr<RpcCallback> RpcCallbackPtr;

/// @brief Описание типа сканирования
typedef int IdScanTask;

class EthernetProfile;
/// @brief Указатель на свойства ethernet
typedef std::shared_ptr<EthernetProfile> EthernetProfilePtr;
/// @brief Список на свойства ethernet
typedef std::vector<EthernetProfilePtr> EthernetProfileList;

class InterfaceProfiles;
/// @brief Указатель cетевые настройки интерфейса
typedef std::shared_ptr<InterfaceProfiles> InterfaceProfilesPtr;
/// @brief Список на cетевые настройки интерфейса
typedef std::vector<InterfaceProfilesPtr> InterfaceProfilesList;

/// @brief BLOB Mac адрес
typedef std::vector<char> MacAddress;

class HostProfile;
/// @brief Указатель на описание хоста
typedef std::shared_ptr<HostProfile> HostProfilePtr;
/// @brief Список узлов
typedef std::vector<HostProfilePtr> HostProfileList;

/// @brief Соотвествие сетевого интерфейса с найденными узлами
typedef std::map<EthernetProfilePtr, HostProfileList> EthernetHostProfileList;

/// @brief Указатель на класс осуществляющий обработку задачи
class Task;
typedef std::shared_ptr<Task> TaskPtr;

/// @brief Указатель на класс содержащий данные результата сканирования
class HostProfileManager;
typedef std::shared_ptr<HostProfileManager> HostProfileManagerPtr;

/// @brief Указатель на класс осуществляющий поиск устройств в сети
class Manager;
typedef std::shared_ptr<Manager> ManagerPtr;
/// @brief Список задач
typedef std::set<IdScanTask> IdScanTaskList;

namespace icmp
{
/// @brief Blob пакет
typedef std::vector<char> BlobPacket;
}

}