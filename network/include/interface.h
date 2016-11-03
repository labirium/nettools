#pragma once

namespace network
{
/// @brief Сетевые настройки интерфейса
class InterfaceProfiles
{
public:
	/// @brief Конструктор
	///
	/// @param[in] ip адрес
	/// @param[in] mask маска сети
	InterfaceProfiles(const struct in_addr& ip, const struct in_addr& mask);
	/// @brief Конструктор
	///
	/// @param[in] ip адрес
	/// @param[in] mask маска сети
	InterfaceProfiles(const unsigned long ip, const unsigned long mask);
	/// @brief Деструктор
	///
	~InterfaceProfiles();
public:
	/// @brief Возвращает Ip адрес
	///
	const struct in_addr& GetIp(void) const;
	/// @brief Возвращает Маска
	///
	const struct in_addr& GetMask(void) const;
private:
	/// ip адрес
	struct in_addr ip_;
	/// маска
	struct in_addr mask_;
};
}

