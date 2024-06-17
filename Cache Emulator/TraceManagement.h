#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "CacheManagement.h"
#include "DataTypes.h"


cacheAddress EncodeAddress(unsigned long address);
void CalculateCacheAddress();
