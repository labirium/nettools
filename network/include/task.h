#pragma once

#include <mutex>
#include <functional>

namespace network
{

/// @brief Класс осуществляет постановку задачи
///
class Task : public std::enable_shared_from_this<Task>
{
public:
	/// @brief Конструктор
	///
	Task();
	/// @brief Деструктор
	///
	~Task();
public:
	/// @brief Осуществляет постановку задачи в отдельный поток
	///
	/// @param[in] typeScan typeScan тип сканирования
	/// @param[in] hostProfileManager описание мереджера для обработки результата сканирования сети
	IdScanTask AddThreadTask(const network::enums::TypeScan typeScan, const HostProfileManagerPtr& hostProfileManager);
	/// @brief Осуществляет постановку задачи
	///
	/// @param[in] typeScan тип сканирования
	/// @param[in] hostProfileManager описание мереджера для обработки результата сканирования сети
	IdScanTask AddTask(const network::enums::TypeScan typeScan, const HostProfileManagerPtr& hostProfileManager);
	/// @brief Получаем статус сканирования
	///
	/// @param[in] idScan номер задачи
	/// @return Возвращает true если задача заврешена
	bool IsTask(const IdScanTask idScan) const;
private:
	/// @brief Осуществляет изменение списка узлов на основе последнего сканирования
	///
	/// @param[in] idTask номер задачи
	void BeginChangeHosts(const IdScanTask idTask);
	/// @brief Осуществляет изменение списка узлов на основе последнего сканирования
	///
	/// @param[in] ethernetHostProfile список найденых сетевых устройств 
	/// @param[in] idTask номер задачи
	/// @param[in] hostProfileManager описание мереджера для обработки результата сканирования сети
	void EndChangeHosts(const EthernetHostProfileList& ethernetHostProfile, const IdScanTask idTask, const HostProfileManagerPtr& hostProfileManager);
private:
	/// Список активных задач
	IdScanTaskList idScanTaskList_;
private:
	mutable std::mutex guard_;
};
}