#pragma once

namespace networktools
{
/// @brief Интерфейс сетевых настроек
///
class  InterfaceProfiles : public networktools::manager::IInterfaceProfiles
{
public:
	/// @brief Конструктор
	///
	/// @param[in] interfaceProfile описание сетевых настроек
	explicit InterfaceProfiles(const network::InterfaceProfilesPtr& interfaceProfile);
	/// @brief Деструктор
	///
	~InterfaceProfiles();
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
	/// @brief Возвращает Ip адрес
	///
	BSTR STDMETHODCALLTYPE GetIp(void) const throw();
	/// @brief Возвращает Маска
	///
	BSTR STDMETHODCALLTYPE GetMask(void) const throw();
private:
	/// описание сетевых настроек
	network::InterfaceProfilesPtr interfaceProfile_;
private:
	/// Содержит количество ссылок на объект
	ULONG ref_;
};
}