/// @file 
/// @brief Файл содержит список хедаров для публикации модуля network

#pragma once

#include <windows.h>
#include <inaddr.h>
#include <string>

#include <network/include/type.h>

#include <network/include/arpscan.h>
#include <network/include/icmpscan.h>

#include <network/include/lognetwork.h>

#include <network/include/interface.h>
#include <network/include/ethernetprofile.h>
#include <network/include/hostprofile.h>
#include <network/include/manager.h>

#include <network/include/networkcalc.h>


#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wpcap.lib")
