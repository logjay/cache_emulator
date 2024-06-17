#pragma once

#include <time.h>
#include "TraceManagement.h"
#include "DataTypes.h"



cacheSet* initializeCache();
bool WalkCacheTags(cacheSet* CompleteCache, cacheAddress cAdd);
void PullAddrToCache(cacheSet* CompleteCache, cacheAddress address);