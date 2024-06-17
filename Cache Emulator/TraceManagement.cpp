#include "TraceManagement.h"

//globally defined here
int addrOffsetLen = 0;
int addrSetLen = 0;
int addrTagLen = 0;
int numSets = 0;


cacheAddress EncodeAddress(unsigned long address) {

	cacheAddress newCacheAddress;
	newCacheAddress.tag = address / (0b1 << (addrSetLen + addrOffsetLen));			//gets top [addrTagLen] bits
	newCacheAddress.set = (address / CacheBlockSize) % numSets;						//gets middle bits
	newCacheAddress.byteOffset = address % CacheBlockSize;							//gets bottom [addrOffsetLen] bits
	newCacheAddress.address = (newCacheAddress.tag << addrSetLen + addrOffsetLen) + (newCacheAddress.set << addrOffsetLen) + newCacheAddress.byteOffset;

	return newCacheAddress;	
}
void CalculateCacheAddress() {

	numSets = CacheSize * 1024 / CacheBlockSize / CacheAssoc;

	addrOffsetLen = log2l(CacheBlockSize);
	addrSetLen = log2l(numSets);
	addrTagLen = CACHE_ADDR_LENGTH - addrSetLen - addrOffsetLen;


}