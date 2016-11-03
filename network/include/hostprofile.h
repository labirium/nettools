#pragma once

namespace network
{
/// @brief Описание узла
///
class HostProfile
{
public:
	/// @brief конструктор
	/// 
	/// @param[in] ip IP адрес
	/// @param[in] mac физический адрес
	/// @param[in] time время получения ответа
	HostProfile(const struct in_addr& ip, const MacAddress& mac, const time_t time);
	/// @brief Деструктор
	///
	~HostProfile();
public:
	/// @brief Осуществляет модификацию свойств удаленного узла
	///
	void ChangeRemoveHostProfile(const RemoveHostProfilePtr& removeHostProfile);
public:
	/// @brief Возвращает физический адресс
	///
	const MacAddress& GetMacAddress(void) const;
	/// @brief Возвращает Ip адрес
	///
	const struct in_addr& GetIp(void) const;
	/// @brief Возвращает время ответа
	///
	time_t GetTime(void) const;
private:
	/// ip адрес
	struct in_addr ip_;
	/// физический адрес
	MacAddress mac_;
	/// Время формирования запроса
	time_t time_;
};
}
