/// @file 
/// @brief Файл содержит список хедаров для осуществления предварительной сборки заголовков

#pragma once

//WINDOWS
#include <network/include/targetver.h>

/// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN       

#include <windows.h>
#include <inaddr.h>

#include <network/include/type.h>

#include <network/include/arpheader.h>
#include <network/include/arptable.h>

#include <network/include/lognetwork.h>
#include <network/include/networkcalc.h>
#include <network/include/ethernetprofile.h>
#include <network/include/hostprofile.h>
#include <network/include/ethernet.h>
#include <network/include/interface.h>
#include <network/include/networkcalc.h>
#include <network/include/manager.h>
#include <network/include/task.h>
#include <network/include/hostprofilemanager.h>

#include <network/include/arpscan.h>
#include <network/include/icmpscan.h>


