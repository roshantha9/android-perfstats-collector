#ifndef __COLLECT_GPUCPU_H_INCLUDED__
#define __COLLECT_GPUCPU_H_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



/* structures */

struct CPUGPUAttr{
    // utilisation
    float cpu0Util;
    float cpu1Util;
    float cpu2Util;
    float cpu3Util;
    float gpuUtil;

    // frequency
    float cpuFreq;
    float gpuFreq;

    // misc
    int numCores;
    int clusterConfig;
};


/* functions */
void getCPUGPUStats(struct CPUGPUAttr *cgAttr, int sampleCount);
int getCurCPUFreq(void);


#endif // __COLLECT_GPUCPU_H_INCLUDED__
