#pragma once

namespace network
{
/// @brief Содержит и обрабатывает результат сканирование сети
///
class HostProfileManager
{
public:
	/// @brief Конструктор
	///
	HostProfileManager();
	/// @brief Деструктор
	///
	~HostProfileManager();
public:
	/// @brief Возвращает список сетевых узлов для заданного интерфейса
	/// 
	/// @param[in] index индекс сетевого интерфейса
	HostProfileList GetHostProfileList(const uint64_t index) const;
	/// @brief Осуществляет обработку события изменения списка устройств
	///
	/// @param[in] task номер таска
	/// @param[in] hostProfile список устройств
	void ChangeEthernetHostProfile(const IdScanTask task, const EthernetHostProfileList& hostProfile);
private:
	/// содержит результат предварительнльного анализа сети
	EthernetHostProfileList ethernetHostsProfile_;
private:
	mutable std::mutex guard_;
};
}
