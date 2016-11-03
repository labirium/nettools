/// @file Содержит набор тестов для тестирования публичного класса Manager

#include <unitests/include/precompiled.h>


//=====================================================================================================================
TEST(Managers, GetEthernetProfileList)
{
	network::Manager manager;
	auto ethernetProfileList = manager.GetEthernetProfileList();
	EXPECT_NE(ethernetProfileList.size(), 0);
}
//=====================================================================================================================
TEST(Managers, GetHostProfileList)
{
	network::Manager manager;
	auto ethernetProfileList = manager.GetEthernetProfileList();
	EXPECT_NE(ethernetProfileList.size(), 0);

	for (const auto& data : ethernetProfileList)
	{
		EXPECT_EQ(static_cast<bool>(data), true);

		const auto hosts = manager.GetHostProfileList(data);
		network::logger::dump(hosts);
	}
}
//=====================================================================================================================
TEST(Managers, Arp)
{
	network::Manager manager;
	auto idScan = manager.AddTask(network::enums::Arp);
	EXPECT_NE(idScan, INVALID_HANDLE);
	EXPECT_NE(idScan, NO_TASK);

	bool result = manager.IsTask(idScan);
	EXPECT_EQ(result, false);

	std::string name;
	std::getline(std::cin, name);
}
//=====================================================================================================================
TEST(Managers, Icmp)
{
	network::Manager manager;
	auto idScan = manager.AddTask(network::enums::Icmp);
	EXPECT_NE(idScan, INVALID_HANDLE);
	EXPECT_NE(idScan, NO_TASK);

	const bool result = manager.IsTask(idScan);
	EXPECT_EQ(result, false);
}
//=====================================================================================================================
TEST(Managers, ArpHost)
{
	network::Manager manager;
	auto idScan = manager.AddTask( network::enums::ArpHost );
	EXPECT_NE(idScan, INVALID_HANDLE);
	EXPECT_EQ(idScan, NO_TASK);

	bool result = manager.IsTask(idScan);
	EXPECT_EQ(result, true);

	result = manager.IsTask(INVALID_HANDLE);
	EXPECT_NE(result, false);
}
//=====================================================================================================================

