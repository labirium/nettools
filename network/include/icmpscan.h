
#pragma once

namespace network
{
namespace icmp
{
/// @brief Осуществляет сканирование заданных сетевых интерфейсов
///
EthernetHostProfileList ScanIcmpProbe(const EthernetProfileList& ethernetsProfiles);
/// @brief Сканирование всех сетевых интерфейсов
///
EthernetHostProfileList ScanIcmpProbe(void);
}
}
