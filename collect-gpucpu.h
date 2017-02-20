#ifndef __COLLECT_GPUCPU_H_INCLUDED__
#define __COLLECT_GPUCPU_H_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"

/* structures */
struct CoreAttr{
    int online;
    unsigned long long busy;
    unsigned long long niceBusy;
    unsigned long long idle;
};

struct CPUGPUAttr{
    // utilisation
    struct CoreAttr cpuCoreSet[NUM_CPU_CORES];

    int gpuUtil;

    // frequency
    int cpuFreq;
    int gpuFreq;

    // misc
    int clusterConfig;
};


/* functions */
void getCPUGPUStats(struct CPUGPUAttr *cgAttr, int sampleCount);
int getCurCPUFreq(void);
int getCurGPUFreq(void);
int getCurGPUUtil(void);


#endif // __COLLECT_GPUCPU_H_INCLUDED__
