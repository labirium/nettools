#pragma once


#ifdef _MSC_VER
#  ifdef NETWORK_TOOLS_EXPORTS
#    define NETWORK_TOOLS  __declspec(dllexport)
#  else
#    define NETWORK_TOOLS  __declspec(dllimport)
#  endif
#else
#  ifndef NETWORK_TOOLS
#    define NETWORK_TOOLS extern "C"
#  endif
#endif

#include <network\network.h>

#include <networktools\include\imanager.h>
#include <networktools\include\hostprofile.h>
#include <networktools\include\interfaceprofiles.h>
#include <networktools\include\ethernetprofile.h>
#include <networktools\include\networkmanager.h>

#pragma comment(lib, "OleAut32.lib")
#pragma comment(lib, "Gdi32.lib")
