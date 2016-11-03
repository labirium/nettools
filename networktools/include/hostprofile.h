#pragma once

namespace networktools
{
/// @brief Описание узла
///
class HostProfile : public networktools::manager::IHostProfile
{
public:
	/// @brief Конструктор
	///
	explicit HostProfile(const network::HostProfilePtr& hostprofile);
	/// @brief Деструктор
	///
	~HostProfile();
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
	/// @brief Возвращает время ответа
	///
	uint64_t STDMETHODCALLTYPE GetTime(void) const throw();
	/// @brief Возвращает Ip адрес
	///
	BSTR STDMETHODCALLTYPE GetIp(void) const throw();
private:
	/// описание сетевого интерфейса
	network::HostProfilePtr hostProfile_;
private:
	/// Содержит количество ссылок на объект
	ULONG ref_;
};
}
