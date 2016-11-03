#pragma once

namespace networktools
{
/// @brief Класс содержит реализацию интерфейса сетевого взаимодействия
///
class NetworkManager : public networktools::manager::INetworkManager
{
public:
	/// @brief Конструктор
	///
	NetworkManager();
	/// @brief Деструктор
	///
	~NetworkManager();
protected:
	/// @brief Возвращает COM объект
	///
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject);
	/// @breif Осуществляет увеличение ссылки COM объекта
	///
	ULONG STDMETHODCALLTYPE AddRef(void);
	/// @breif Осуществляет уменьшение ссылки COM объекта
	///
	ULONG STDMETHODCALLTYPE Release(void);
public:
	/// @brief Возвращает список сетевых интерфейсов
	///
	SAFEARRAY FAR* STDMETHODCALLTYPE GetNetworkEthernet(void) const throw();
	/// @brief Возвращает список сетевых узлов для заданного интерфейса
	/// 
	/// @param[in] profile описание сетевого интерфейса
	SAFEARRAY FAR* STDMETHODCALLTYPE GetHostProfileList(const networktools::manager::IEthernetProfile& profile) const throw();
public:
	/// @brief Ставит задачу в очередь
	///
	/// @param[in] typeScan тип сканирования
	/// @return Возвращает id задачи
	manager::IdScanTask STDMETHODCALLTYPE AddTask(const manager::enums::TypeScan typeScan) throw();
	/// @brief Проверка завершение выполнения задачи
	/// 
	/// @param[in] idTask задача 
	/// @return Возвращает true если задача заврешена
	bool STDMETHODCALLTYPE IsTask(const manager::IdScanTask idTask) const throw();
private:
	/// осуществляет поиск устройств в сети
	network::ManagerPtr manager_;
private:
	/// Содержит количество ссылок на объект
	ULONG ref_;
};
}
