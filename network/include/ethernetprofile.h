#pragma once

namespace network
{
/// @brief Свойства интерфейса
///
class EthernetProfile
{
public:
	/// @brief Конструктор
	///
	/// @param[in] index Индекс сетевого интерфейса
	/// @param[in] name Имя интерфейса
	/// @param[in] description Описание интерфейса
	/// @param[in] macAddress физический адрес
	/// @param[in] isVpn true - определяет сетевой интерфейс как VPN
	/// @param[in] interfaceProfiles Описание сетевого интерфейса
	EthernetProfile(const uint64_t index, const std::string& name, const std::string& description, const MacAddress& macAddress, const bool isVpn, const InterfaceProfilesList& interfaceProfiles);
	/// @brief Деструтор
	///
	~EthernetProfile();
public:
	/// @brief Возвращает индекс сетевого интерфейса
	///
	uint64_t GetIndex(void) const;
	/// @brief Возвращает имя интерфейса
	///
	const std::string& GetName(void) const;
	/// @brief Возвращает описание интерфейса
	///
	const std::string& GetDescription(void) const;
	/// @brief Возвращает физический адрес
	///
	const MacAddress& GetMacAddress(void) const;
	/// @brief Возвращает true если определен признак VPN
	///
	bool IsVpn(void) const;
	/// @brief Возвращает список сетевых интерфейсов
	///
	const InterfaceProfilesList& GetInterfaceProfilesList(void) const;
private:
	/// Список сетевых интерфейсов
	InterfaceProfilesList interfaceProfiles_;
	/// Физический адрес
	MacAddress macAddress_;
	/// Имя интерфейса
	std::string name_;
	/// Описание интерфейса
	std::string description_;
	///  Индекс сетевого интерфейса
	uint64_t index_;
	/// признак VPN
	bool isVpn_;
};
}
