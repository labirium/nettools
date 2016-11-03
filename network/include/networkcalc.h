#pragma once

namespace network
{
namespace tools
{
/// @brief Возвращает ip адрес в строковом выражении
///
std::string GetIpStr(const network::InterfaceProfilesPtr& data);
/// @brief Возвращает ip адрес в строковом выражении
///
std::string GetIpStr(const network::HostProfilePtr& data);
/// @brief Возвращает mask адрес в строковом выражении
///
std::string GetMaskStr(const network::InterfaceProfilesPtr& data);

/// @brief Возвращает страртовый ip адрес сети
///
/// @param[in] data описание интерфейса на основе которого делались расчеты
uint32_t GetStartIp(const network::InterfaceProfilesPtr& data);

/// @brief Возвращает количество ip адресов в сети
///
/// @param[in] data описание интерфейса на основе которого делались расчеты
uint32_t GetCountIp(const network::InterfaceProfilesPtr& data);

/// @brief Возвращает последний ip адрес сети
///
/// @param[in] data описание интерфейса на основе которого делались расчеты
uint32_t GetEndIp(const network::InterfaceProfilesPtr& data);
}
}
