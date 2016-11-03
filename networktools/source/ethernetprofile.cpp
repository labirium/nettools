#include <networktools\include\precompiled.h>
#include <assert.h>
#include <cguid.h>
#include <atlbase.h>

namespace networktools
{
//=====================================================================================================================
HRESULT STDMETHODCALLTYPE EthernetProfile::QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject)
{
	if (riid == IID_IUnknown){
		*ppvObject = static_cast<networktools::manager::IEthernetProfile*>(this);
	}
	else if (riid == IID_IEthernetProfile){
		*ppvObject = static_cast<networktools::manager::IEthernetProfile*>(this);
	}
	else{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppvObject)->AddRef();

	return NOERROR;
}
//=====================================================================================================================
ULONG STDMETHODCALLTYPE EthernetProfile::AddRef()
{
	InterlockedIncrement(&ref_);
	return ref_;

}
//=====================================================================================================================
ULONG STDMETHODCALLTYPE EthernetProfile::Release()
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
bool STDMETHODCALLTYPE EthernetProfile::IsVpn(void) const throw()
{
	return ethernetProfile_->IsVpn();
}
//=====================================================================================================================
uint64_t STDMETHODCALLTYPE EthernetProfile::GetIndex(void) const throw()
{
	return ethernetProfile_->GetIndex();
}
//=====================================================================================================================
BSTR STDMETHODCALLTYPE EthernetProfile::GetName(void) const throw()
{
	CComBSTR data(ethernetProfile_->GetName().c_str());
	return data.Detach();
}
//=====================================================================================================================
BSTR STDMETHODCALLTYPE EthernetProfile::GetDescription(void) const throw()
{
	CComBSTR data(ethernetProfile_->GetDescription().c_str());
	return data.Detach();
}
//=====================================================================================================================
SAFEARRAY FAR* STDMETHODCALLTYPE EthernetProfile::GetInterfaceProfiles(void) const throw()
{
	const auto profiles = ethernetProfile_->GetInterfaceProfilesList();
	if (profiles.size() == 0){
		return NULL;
	}

	SAFEARRAYBOUND sabounds[1];
	sabounds[0].lLbound = 0;
	sabounds[0].cElements = static_cast<ULONG>(profiles.size());

	SAFEARRAY FAR* psarray = SafeArrayCreate(VT_UNKNOWN, 1, sabounds);
	if (psarray == NULL){
		return NULL;
	}

	LONG number = 0;
	for (const auto data : profiles)
	{
		void* element = new networktools::InterfaceProfiles(data);
		if (FAILED(SafeArrayPutElement(psarray, &number, element))){
			SafeArrayDestroy(psarray);
			return NULL;
		}

		++number;
	}

	return psarray;
}
//=====================================================================================================================
EthernetProfile::EthernetProfile(const network::EthernetProfilePtr& ethernetProfile) : ethernetProfile_(ethernetProfile), ref_( 0 )
{
	assert(ethernetProfile_ && "Invalid input data.");
}
//=====================================================================================================================
EthernetProfile::~EthernetProfile()
{
}
//=====================================================================================================================
}