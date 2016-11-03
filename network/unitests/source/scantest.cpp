/// @file Содержит набор тестов для тестирования сканирования сети

#include <unitests/include/precompiled.h>

//=====================================================================================================================
/// @brief Осуществляет выборку из arp таблицы
///
TEST(Arp, ArpHostTableProbe)
{
	const auto data = network::ArpHostTableProbe();
	EXPECT_NE(data.size(), 0);

	network::logger::dump(data);
}
//=====================================================================================================================
/// @brief Осуществляет arp сканирование на всех интерфейсах
///
TEST(Arp, ArpScanProbe)
{
	const auto data = network::ArpScanProbe();
	EXPECT_NE(data.size(), 0);

	network::logger::dump(data);
}
//=====================================================================================================================
