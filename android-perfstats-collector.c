#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

/* local includes */
#include "android-perfstats-collector.h"
#include "collect-gpucpu.h"
#include "collect-mem.h"
#include "debug.h"

/* global vars */
struct CPUGPUAttr cpugpuData;
struct MemBusAttr memData;


void initialise(){

    /* init cpugpu structures */
    cpugpuData.cpu0Util=0.0;
    cpugpuData.cpu1Util=0.0;
    cpugpuData.cpu2Util=0.0;
    cpugpuData.cpu3Util=0.0;

    cpugpuData.gpuUtil=0.0;

    cpugpuData.cpuFreq=0.0;
    cpugpuData.gpuFreq=0.0;

    cpugpuData.numCores=0;
    cpugpuData.clusterConfig=0;
}


void _debug_cpugpuData(){
    DEBUG(("\n--_debug_cpugpuData-\n"));
    DEBUG(("%.2f,", cpugpuData.cpu0Util));
    DEBUG(("%.2f,", cpugpuData.cpu1Util));
    DEBUG(("%.2f,", cpugpuData.cpu2Util));
    DEBUG(("%.2f,", cpugpuData.cpu3Util));

    DEBUG(("%.2f,", cpugpuData.gpuUtil));
    DEBUG(("%.2f,", cpugpuData.cpuFreq));
    DEBUG(("%.2f,", cpugpuData.gpuFreq));
    DEBUG(("%d,", cpugpuData.numCores));
    DEBUG(("%d", cpugpuData.clusterConfig));
    DEBUG(("\n---\n"));
}

void _debug_memData(){
    DEBUG(("\n--_debug_memData-\n"));
    DEBUG(("%.2f,", memData.mem0_0.bw));
    DEBUG(("%.2f,", memData.mem0_1.freq));
    DEBUG(("\n---\n"));
}



int main(int argc, char** argv) {
   DEBUG(("Hello world!!!\n"));

   int count;
   count=0;

   while(count<10){

        initialise();

        getCPUGPUStats(&cpugpuData, count);
        getMemStats(&memData, count);

        _debug_cpugpuData();
        _debug_memData();

        usleep(500000);
        count++;





   }






   return 0;



}
