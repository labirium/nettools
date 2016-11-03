#include <networktools\include\precompiled.h>
#include <assert.h>
#include <oaidl.h>
#include <winerror.h>

namespace networktools
{
//=====================================================================================================================
HRESULT STDMETHODCALLTYPE NetworkManager::QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject)
{
	if (riid == IID_IUnknown){
		*ppvObject = static_cast<networktools::manager::INetworkManager*>(this);
	}
	else if (riid == IID_INetworkManager){
		*ppvObject = static_cast<networktools::manager::INetworkManager*>(this);
	}
	else{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppvObject)->AddRef();

	return NOERROR;
}
//=====================================================================================================================
ULONG STDMETHODCALLTYPE NetworkManager::AddRef()
{
	InterlockedIncrement(&ref_);
	return ref_;

}
//=====================================================================================================================
ULONG STDMETHODCALLTYPE NetworkManager::Release()
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
SAFEARRAY FAR* STDMETHODCALLTYPE NetworkManager::GetNetworkEthernet(void) const throw()
{
	const auto profiles = manager_->GetEthernetProfileList();
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
		void* element = new networktools::EthernetProfile(data);
		if (FAILED(SafeArrayPutElement(psarray, &number, element))){
			SafeArrayDestroy(psarray);
			return NULL;
		}

		++number;
	}

	return psarray;
}
//=====================================================================================================================
SAFEARRAY FAR* STDMETHODCALLTYPE NetworkManager::GetHostProfileList(const networktools::manager::IEthernetProfile& profile) const throw()
{
	const auto hosts = manager_->GetHostProfileList( profile.GetIndex() );
	if (hosts.size() == 0){
		return NULL;
	}

	SAFEARRAYBOUND sabounds[1];
	sabounds[0].lLbound = 0;
	sabounds[0].cElements = static_cast<ULONG>(hosts.size());

	SAFEARRAY FAR* psarray = SafeArrayCreate(VT_UNKNOWN, 1, sabounds);
	if (psarray == NULL){
		return NULL;
	}

	LONG number = 0;
	for (const auto data : hosts)
	{
		void* element = new networktools::HostProfile(data);
		if (FAILED(SafeArrayPutElement(psarray, &number, element))){
			SafeArrayDestroy(psarray);
			return NULL;
		}

		++number;
	}

	return psarray;
}
//=====================================================================================================================
manager::IdScanTask STDMETHODCALLTYPE NetworkManager::AddTask(const manager::enums::TypeScan typeScan) throw()
{
	return manager_->AddTask(typeScan);
}
//=====================================================================================================================
bool STDMETHODCALLTYPE NetworkManager::IsTask(const manager::IdScanTask idTask) const throw()
{
	return manager_->IsTask(idTask);
}
//=====================================================================================================================
NetworkManager::NetworkManager() : ref_(0), manager_(std::make_shared<network::Manager>())
{
	assert(manager_ && "Invalid init parametr.");
}
//=====================================================================================================================
NetworkManager::~NetworkManager()
{
}
//=====================================================================================================================
}