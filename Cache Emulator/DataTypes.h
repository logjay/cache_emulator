#pragma once

#define MAX_ADDR_FILE_LENGTH 1.6e7
#define MAX_TRACE_STRING_LENGTH 12
#define CACHE_ADDR_LENGTH 32

//design parameters
#define CacheAssoc 1 //1, 2, 4, 8
#define CacheReplacementAlgth 2 //0 = LRU, 1 = FIFO, 2 = Rand()
#define CacheBlockSize 128 //bytes - 16, 32, 64, 128
#define CacheSize 8 //KB - 16, 32, 64, 128

typedef char Byte;
struct cacheAddress {
	unsigned long address; //whole address

	unsigned long tag;
	unsigned int set;
	unsigned int byteOffset;
};

struct cacheBlock {
	unsigned long blockTag;
	int replacementTag;
	int byteOffset;
};

struct cacheSet {
	cacheBlock block[CacheAssoc];
};
