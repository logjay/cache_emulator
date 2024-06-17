#include <iostream>
#include <fstream>
using namespace std;

#include "TraceManagement.h"
#include "CacheManagement.h"
#include "DataTypes.h"

#define addrFilePath "S:\\Documents\\School\\SJSU\\2022-23\\EE275\\MiniProject3\\Cache Emulator\\addr_trace.txt"
#define outputFile "S:\\Documents\\School\\SJSU\\2022-23\\EE275\\MiniProject3\\Cache Emulator\\results.csv"
//#define addrFilePath "addr_trace.txt"
//#define outputFile "results.csv"

int main()
{

    //tracking parameters
    /*
    * total sim addresses
    * total cache hits
    * cache hit ratio
    */
    int VitalsTotalCalls = -1;
    int VitalsTotalHits = -1;
    double VitalsHitRatio;

    printf("\nStarting cache emulator\n\n\tAuthor: Logan Williams - 016672721\n\n");
    printf("\nStarting cache simulation with parameters:\n \
            Associativity       : %d\n \
            Replacement Algth   : %d\n \
            Block Size          : %d\n \
            Cache Size          : %d\n",
        CacheAssoc, CacheReplacementAlgth, CacheBlockSize, CacheSize);

    cacheSet* CompleteCache = initializeCache();

    //init loop
    std::fstream AddressFile(addrFilePath);
    std::string line;
    char* nextTrace = new char[MAX_TRACE_STRING_LENGTH];
    long addrOffset = 0;
    unsigned long addrPointer = 0;

    cacheAddress currentCacheAddress;
    CalculateCacheAddress();

    int addrMax=0;

    //main loop
    for (int i = 0; i < MAX_ADDR_FILE_LENGTH; i++) {

        std::getline(AddressFile, line);
        strcpy_s(nextTrace, MAX_TRACE_STRING_LENGTH, line.c_str());
        addrOffset = strtol(nextTrace, NULL, 10);
        addrPointer += addrOffset;

        currentCacheAddress = EncodeAddress(addrPointer);


        if (WalkCacheTags(CompleteCache, currentCacheAddress)) {
            VitalsTotalHits++;
        }else {
            PullAddrToCache(CompleteCache, currentCacheAddress);
        }


        if (addrPointer > addrMax) {
            addrMax = addrPointer;
        }


        //printf("%s \t\t%ld  \t\t  %ld \n", nextTrace, addrOffset,addrPointer);
        VitalsTotalCalls++;
        if (nextTrace[0] == 0) {
            break;
        }
    } //End for
    printf("\nMax Address Found: %d\n", addrMax);

    AddressFile.close();
    
    VitalsHitRatio = (double)VitalsTotalHits / (double)VitalsTotalCalls;

    printf("\nExiting cache simulation:\n \
        Simulation Vitals:\n \
            Total Calls         : % d\n \
            Total Hits          : % d\n \
            Hit Ratio           : % 0.2f%%\n",
        VitalsTotalCalls, VitalsTotalHits, VitalsHitRatio* 100);

    free(CompleteCache);


    ///////////write results to CSV
    std::fstream resultCSVCheck(outputFile);
    std::ofstream resultCSV;
    std::string temp;
    bool headersCreated = false;
    bool combinationLogged = false;
    std::string headers = "Cache Size,Block Size,Associativity,Replacement Algth,Calls,Hits,Ratio";
    std::string paramCombo = std::to_string(CacheSize) + ",";
                paramCombo += std::to_string(CacheBlockSize) + ",";
                paramCombo += std::to_string(CacheAssoc) + ",";
                paramCombo += std::to_string(CacheReplacementAlgth);


    //check if current set of parameters already exist
    //check if headers already exist
    std::getline(resultCSVCheck, temp);
    if (temp.compare(headers) == 0) {
        headersCreated = true;
    }
    while (temp[0] != 0) {
        std::getline(resultCSVCheck, temp);
        if (temp.compare(0, paramCombo.size(), paramCombo) == 0) {
            combinationLogged = true;
        }
    }
    resultCSVCheck.close();

    
    if (!headersCreated) {
        resultCSV.open(outputFile);
        resultCSV << headers << endl;
        resultCSV.close();
    }

    if (!combinationLogged) {
        resultCSV.open(outputFile, std::ios::app);
        resultCSV << paramCombo << "," << VitalsTotalCalls << "," << VitalsTotalHits << "," << VitalsHitRatio << endl;
        resultCSV.close();
    }
    

    return 0;
}

