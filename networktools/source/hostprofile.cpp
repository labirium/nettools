#include <networktools\include\precompiled.h>
#include <assert.h>
#include <cguid.h>
#include <atlbase.h>

namespace networktools
{
//=====================================================================================================================
	HRESULT STDMETHODCALLTYPE HostProfile::QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject)
{
	if (riid == IID_IUnknown){
		*ppvObject = static_cast<networktools::manager::IHostProfile*>(this);
	}
	else if (riid == IID_IHostProfile){
		*ppvObject = static_cast<networktools::manager::IHostProfile*>(this);
	}
	else{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppvObject)->AddRef();

	return NOERROR;
}
//=====================================================================================================================
	ULONG STDMETHODCALLTYPE HostProfile::AddRef()
{
	InterlockedIncrement(&ref_);
	return ref_;

}
//=====================================================================================================================
ULONG STDMETHODCALLTYPE HostProfile::Release()
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
uint64_t STDMETHODCALLTYPE HostProfile::GetTime(void) const throw()
{
	return hostProfile_->GetTime();
}
//=====================================================================================================================
BSTR STDMETHODCALLTYPE HostProfile::GetIp(void) const throw()
{
	CComBSTR data(network::tools::GetIpStr(hostProfile_).c_str());
	return data.Detach();
}
//=====================================================================================================================
HostProfile::HostProfile(const network::HostProfilePtr& hostprofile) : hostProfile_(hostprofile), ref_(0)
{
	assert(hostProfile_ && "Invalid input data.");
}
//=====================================================================================================================
HostProfile::~HostProfile()
{
}
//=====================================================================================================================
}