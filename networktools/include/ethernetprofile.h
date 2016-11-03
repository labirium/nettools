#pragma once

namespace networktools
{
/// @breif Возвращает описание сетевого интерфейса
///
class EthernetProfile : public networktools::manager::IEthernetProfile
{
public:
	/// @brief Конструктор
	///
	explicit EthernetProfile(const network::EthernetProfilePtr& ethernetProfile );
	/// @brief Деструктор
	///
	~EthernetProfile();
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
	/// @brief Возвращает индекс сетевого интерфейса
	///
	uint64_t STDMETHODCALLTYPE GetIndex(void) const throw();
	/// @brief Возвращает true если определен признак VPN
	///
	bool STDMETHODCALLTYPE IsVpn(void) const throw();
	/// @brief Возвращает имя интерфейса
	///
	BSTR STDMETHODCALLTYPE GetName(void) const throw();
	/// @brief Возвращает описание интерфейса
	///
	BSTR STDMETHODCALLTYPE GetDescription(void) const throw();
public:
	/// @brief Возвращает список сетевых настроек
	///
	SAFEARRAY FAR* STDMETHODCALLTYPE GetInterfaceProfiles(void) const throw();
private:
	/// описание сетевого интерфейса
	network::EthernetProfilePtr ethernetProfile_;
private:
	/// Содержит количество ссылок на объект
	ULONG ref_;
};
}
