#pragma once

namespace network
{
namespace logger
{

/// @brief Информационное поле
void Info(const char*, ...) throw();
/// @brief Предупреждение
void Warning(const char*, ...) throw();
/// @brief Ошибка
void Error(const char*, ...)throw() ;


/// @brief Детализация хоста
///
void dump(const HostProfilePtr& host) throw();
/// @brief Детализация списка хостов
///
void dump(const HostProfileList& hostProfiles) throw();
/// @brief Детализация интерфейса
///
void dump(const EthernetProfilePtr& ethernetProfile) throw();
/// @brief Детализация списка интерфейсов
///
void dump(const EthernetHostProfileList& ethernetHostProfile) throw();

}
}
