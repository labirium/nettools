#pragma once

#include <network/include/precompiled.h>

namespace network
{
namespace ethernet
{
/// @brief Возвращает индекс для сетевого интерфейса
///
/// @param[in] name имя сетевого интерфейса
/// @param[out] index возвращает индекс интерфейса
/// @param[out] isVpn возвращает true если сетевой интерфейс используется для VPN
/// @return Возвращает результат операции
bool GetIndexInterface(const std::string& name, uint64_t& index, bool& isVpn);
/// @brief Возвращает физический адрес по имени интерфейса
///
/// @param[in] name имя сетевого интерфейса
/// @return Возвращает физический адрес
MacAddress GetMacAddress(const std::string& name);

/// @brief Возвращает список доступных сетевых интерфейсов
///
EthernetProfileList GetEthernetProfileList(void);
}
}

