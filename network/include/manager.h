#pragma once

#include <mutex>

namespace network
{
namespace enums
{
	/// Тип сканирования
	enum
	{
		/// Arp сканирование
		Arp,
		/// Анализ arp таблицы хоста
		ArpHost,
		/// Icmp сканирование
		Icmp
	};

	/// Тип сканирования
	typedef int TypeScan;

}

/// невалидный параметр
#define INVALID_HANDLE -1
/// отсуствует таск
#define NO_TASK 0


/// @brief Класс осуществляет поиск устройств в сети
///
class Manager
{
public:
	/// @brief Коннструктор
	///
	Manager( void );
	/// @brief Деструктор
	///
	~Manager();
	/// @brief Конструктор копирования
	Manager(const Manager& that) = delete;
public:
	/// @brief Возвращает список сетевых интерфейсов
	///
	network::EthernetProfileList GetEthernetProfileList(void) const;
	/// @brief Возвращает список сетевых узлов для заданного интерфейса
	/// 
	/// @param[in] ethernetProfile описание сетевого интерфейса
	HostProfileList GetHostProfileList(const EthernetProfilePtr& ethernetProfile) const;
	/// @brief Возвращает список сетевых узлов для заданного интерфейса
	/// 
	/// @param[in] index индекс сетевого интерфейса
	HostProfileList GetHostProfileList(const uint64_t index) const;
public:
	/// @brief Задаем задачу на сканирование
	///
	/// @param[in] typeScan тип сканирования
	/// @return Возвращает 0 если результат  не требует асинхронной обработки
	///         Возвращает INVALID_HANDLE если неполучилось выставить в ощередь
	///         Возвращает значение для проверки его завершения в IdScanTask
	IdScanTask AddTask(const network::enums::TypeScan typeScan);
	/// @brief Получаем статус сканирования
	///
	/// @param[idScan] номер задачи
	/// @return Возвращает true если задача заврешена
	bool IsTask(const IdScanTask idScan) const;
private:
	/// Менеджер задач
	TaskPtr task_;
	/// Менеджер данных
	HostProfileManagerPtr hostProfileManager_;
};
}