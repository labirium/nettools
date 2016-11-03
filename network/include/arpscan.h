
#pragma once

namespace network
{
/// @brief Осуществляет выборку из arp таблицы
///
EthernetHostProfileList ArpHostTableProbe(void);
/// @brief Осуществляет arp сканирование на всех интерфейсах
///
EthernetHostProfileList ArpScanProbe(void);
}
