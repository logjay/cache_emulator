#include "CacheManagement.h"


extern int numSets;
cacheSet* initializeCache() {

	cacheSet* allSets;
	
	int numSetsTotal = CacheSize * 1024 / CacheBlockSize / CacheAssoc;

	allSets = (cacheSet*)calloc(numSetsTotal,sizeof(cacheSet));

	return allSets;
}

bool WalkCacheTags(cacheSet* CompleteCache, cacheAddress cAdd) {


	int numSetsTotal = CacheSize * 1024 / CacheBlockSize / CacheAssoc;
	int placeholder;

	for (int i = 0; i < CacheAssoc; i++) {
		if (cAdd.tag == CompleteCache[cAdd.set].block[i].blockTag) {
			switch(CacheReplacementAlgth) {
			case 0: //LRU
				placeholder = CompleteCache[cAdd.set].block[i].replacementTag;
				for (int j = 0; j < CacheAssoc; j++) {
					if (CompleteCache[cAdd.set].block[j].replacementTag > placeholder) {
						CompleteCache[cAdd.set].block[j].replacementTag--;
					}
				}
				CompleteCache[cAdd.set].block[i].replacementTag = CacheAssoc;
				break;
			}
			return true;
		}
	}
	return false;
}

void PullAddrToCache(cacheSet* CompleteCache, cacheAddress curAdd) {

	cacheSet* currentSet = &CompleteCache[curAdd.set];
	bool blockPulled = false;
	srand(time(NULL));

	switch (CacheReplacementAlgth) {
	case 0: //LRU
	case 1: //FIFO
		for (int i = 0; i < CacheAssoc; i++) {
			if (currentSet->block[i].replacementTag == 0 && !blockPulled) {
				currentSet->block[i].replacementTag = CacheAssoc;
				currentSet->block[i].blockTag = curAdd.tag;
				currentSet->block[i].byteOffset = curAdd.byteOffset;
				blockPulled = true;
			}
			else if (currentSet->block[i].replacementTag != 0) {
				currentSet->block[i].replacementTag--;
			}
		}
		break;
	case 2: //Rand()
		int randblock = rand() % CacheAssoc;
		currentSet->block[randblock].blockTag = curAdd.tag;
		currentSet->block[randblock].byteOffset = curAdd.byteOffset;
		break;
	}

}