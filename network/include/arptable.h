#pragma once

namespace network
{
/// @brief Возвращает список хостов на основе встроенной таблицы машрутизации
///
/// @param[in] ethernetProfile Описание сетевого интерфейса
/// @param[out] hosts Список полученных хостов
bool GetArpHostTalbeForInterface(const EthernetProfilePtr& ethernetProfile, HostProfileList& hosts );
}

