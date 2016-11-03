#include <networktools\include\precompiled.h>
#include <assert.h>
#include <cguid.h>
#include <atlbase.h>

namespace networktools
{
//=====================================================================================================================
HRESULT STDMETHODCALLTYPE InterfaceProfiles::QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject)
{
	if (riid == IID_IUnknown){
		*ppvObject = static_cast<networktools::manager::IInterfaceProfiles*>(this);
	}
	else if (riid == IID_InterfaceProfiles){
		*ppvObject = static_cast<networktools::manager::IInterfaceProfiles*>(this);
	}
	else{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppvObject)->AddRef();

	return NOERROR;
}
//=====================================================================================================================
ULONG STDMETHODCALLTYPE InterfaceProfiles::AddRef()
{
	InterlockedIncrement(&ref_);
	return ref_;
}
//=====================================================================================================================
ULONG STDMETHODCALLTYPE InterfaceProfiles::Release()
{
	// Decrement the object's internal counter.
	const ULONG ulRefCount = InterlockedDecrement(&ref_);
	if (0 == ref_)
	{
		delete this;
	}
	return ulRefCount;
}
//=====================================================================================================================
BSTR STDMETHODCALLTYPE InterfaceProfiles::GetIp(void) const throw()
{
	CComBSTR data(network::tools::GetIpStr(interfaceProfile_).c_str());
	return data.Detach();
}
//=====================================================================================================================
BSTR STDMETHODCALLTYPE InterfaceProfiles::GetMask(void) const throw()
{
	CComBSTR data(network::tools::GetMaskStr(interfaceProfile_).c_str());
	return data.Detach();
}
//=====================================================================================================================
InterfaceProfiles::InterfaceProfiles(const network::InterfaceProfilesPtr& interfaceProfile) : ref_(0), interfaceProfile_(interfaceProfile)
{
	assert(interfaceProfile && "Invalid init parametr.");
}
//=====================================================================================================================
InterfaceProfiles::~InterfaceProfiles()
{

}
//=====================================================================================================================
}