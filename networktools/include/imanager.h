#pragma once

#include <vector>

namespace networktools
{
namespace manager
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
typedef int32_t TypeScan;
;
}

/// @brief Описание типа сканирования
typedef int32_t IdScanTask;

/// @brief Интерфейс описания узла
///
struct IHostProfile : public IUnknown
{
	/// @brief Возвращает Ip адрес
	///
	virtual BSTR STDMETHODCALLTYPE GetIp(void) const throw() = 0;
	/// @brief Возвращает время ответа
	///
	virtual uint64_t STDMETHODCALLTYPE GetTime(void) const throw() = 0;
};

/// @brief Интерфейс сетевых настроек
///
struct IInterfaceProfiles : public IUnknown
{
	/// @brief Возвращает Ip адрес
	///
	virtual BSTR STDMETHODCALLTYPE GetIp(void) const throw() = 0;
	/// @brief Возвращает Маска
	///
	virtual BSTR STDMETHODCALLTYPE GetMask(void) const throw() = 0;
};

/// @breif Интерфейс сетевого интерфейса
///
struct IEthernetProfile : public IUnknown
{
	/// @brief Возвращает индекс сетевого интерфейса
	///
	virtual uint64_t STDMETHODCALLTYPE GetIndex(void) const throw() = 0;
	/// @brief Возвращает true если определен признак VPN
	///
	virtual bool STDMETHODCALLTYPE IsVpn(void) const throw() = 0;
	/// @brief Возвращает имя интерфейса
	///
	virtual BSTR STDMETHODCALLTYPE GetName(void) const throw() = 0;
	/// @brief Возвращает описание интерфейса
	///
	virtual BSTR STDMETHODCALLTYPE GetDescription(void) const = 0;
public:
	/// @brief Возвращает список сетевых настроек
	///
	virtual SAFEARRAY FAR* STDMETHODCALLTYPE GetInterfaceProfiles(void) const throw() = 0;
};

/// @brief Интерфейс для сетевого взаимодействия
///
struct INetworkManager : public IUnknown
{
	/// @brief Возвращает список сетевых интерфейсов
	///
	virtual SAFEARRAY FAR* STDMETHODCALLTYPE GetNetworkEthernet(void) const throw() = 0;
	/// @brief Возвращает список сетевых узлов для заданного интерфейса
	/// 
	/// @param[in] profile описание сетевого интерфейса
	virtual SAFEARRAY FAR* STDMETHODCALLTYPE GetHostProfileList(const IEthernetProfile& profile) const throw() = 0;
public:
	/// @brief Ставит задачу в очередь
	///
	/// @param[in] typeScan тип сканирования
	/// @return Возвращает id задачи
	virtual IdScanTask STDMETHODCALLTYPE AddTask(const enums::TypeScan typeScan) throw() = 0;
	/// @brief Проверка завершение выполнения задачи
	/// 
	/// @param[in] idTask задача 
	/// @return Возвращает true если задача заврешена
	virtual bool STDMETHODCALLTYPE IsTask(const IdScanTask idTask) const throw() = 0;
};

}
}

// {864DFD92-00C7-43E4-8856-CD3490769CDA}
DEFINE_GUID(IID_IHostProfile,
0x864dfd92, 0xc7, 0x43e4, 0x88, 0x56, 0xcd, 0x34, 0x90, 0x76, 0x9c, 0xda);

// {6F4EBF8F-A620-4CEA-8A88-2A168563A9E0}
DEFINE_GUID(IID_InterfaceProfiles,
	0x6f4ebf8f, 0xa620, 0x4cea, 0x8a, 0x88, 0x2a, 0x16, 0x85, 0x63, 0xa9, 0xe0);

// {2B3F116C-2717-4A29-8C5E-50F2566BFFC7}
DEFINE_GUID(IID_IEthernetProfile,
	0x2b3f116c, 0x2717, 0x4a29, 0x8c, 0x5e, 0x50, 0xf2, 0x56, 0x6b, 0xff, 0xc7);

// {D1C66136-AB61-4F6C-8984-50B128750CD1}
DEFINE_GUID(IID_INetworkManager,
	0xd1c66136, 0xab61, 0x4f6c, 0x89, 0x84, 0x50, 0xb1, 0x28, 0x75, 0xc, 0xd1);

/// @brief Factory function
///
extern "C" NETWORK_TOOLS networktools::manager::INetworkManager* WINAPI CreateNetworkManager();
