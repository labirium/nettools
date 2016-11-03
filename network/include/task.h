#pragma once

#include <mutex>
#include <functional>

namespace network
{

/// @brief  ласс осуществл€ет постановку задачи
///
class Task : public std::enable_shared_from_this<Task>
{
public:
	/// @brief  онструктор
	///
	Task();
	/// @brief ƒеструктор
	///
	~Task();
public:
	/// @brief ќсуществл€ет постановку задачи в отдельный поток
	///
	/// @param[in] typeScan typeScan тип сканировани€
	/// @param[in] hostProfileManager описание мереджера дл€ обработки результата сканировани€ сети
	IdScanTask AddThreadTask(const network::enums::TypeScan typeScan, const HostProfileManagerPtr& hostProfileManager);
	/// @brief ќсуществл€ет постановку задачи
	///
	/// @param[in] typeScan тип сканировани€
	/// @param[in] hostProfileManager описание мереджера дл€ обработки результата сканировани€ сети
	IdScanTask AddTask(const network::enums::TypeScan typeScan, const HostProfileManagerPtr& hostProfileManager);
	/// @brief ѕолучаем статус сканировани€
	///
	/// @param[in] idScan номер задачи
	/// @return ¬озвращает true если задача заврешена
	bool IsTask(const IdScanTask idScan) const;
private:
	/// @brief ќсуществл€ет изменение списка узлов на основе последнего сканировани€
	///
	/// @param[in] idTask номер задачи
	void BeginChangeHosts(const IdScanTask idTask);
	/// @brief ќсуществл€ет изменение списка узлов на основе последнего сканировани€
	///
	/// @param[in] ethernetHostProfile список найденых сетевых устройств 
	/// @param[in] idTask номер задачи
	/// @param[in] hostProfileManager описание мереджера дл€ обработки результата сканировани€ сети
	void EndChangeHosts(const EthernetHostProfileList& ethernetHostProfile, const IdScanTask idTask, const HostProfileManagerPtr& hostProfileManager);
private:
	/// —писок активных задач
	IdScanTaskList idScanTaskList_;
private:
	mutable std::mutex guard_;
};
}