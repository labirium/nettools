#include <networktools\include\precompiled.h>

//=====================================================================================================================
NETWORK_TOOLS networktools::manager::INetworkManager* WINAPI CreateNetworkManager()
{
	return  new networktools::NetworkManager();
}
//=====================================================================================================================
