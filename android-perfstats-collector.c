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
    DEBUG((">>_debug_memData :: mfc0, %4.2f, %3.2f, %2.2f, %d\n", memData.mfc0.bw, memData.mfc0.freq, memData.mfc0.sat, memData.mfc0.dur));
    DEBUG((">>_debug_memData :: mfc1, %4.2f, %3.2f, %2.2f, %d\n", memData.mfc1.bw, memData.mfc1.freq, memData.mfc1.sat, memData.mfc1.dur));
    DEBUG((">>_debug_memData :: gsc23, %4.2f, %3.2f, %2.2f, %d\n", memData.gsc23.bw, memData.gsc23.freq, memData.gsc23.sat, memData.gsc23.dur));
    DEBUG((">>_debug_memData :: isp0, %4.2f, %3.2f, %2.2f, %d\n", memData.isp0.bw, memData.isp0.freq, memData.isp0.sat, memData.isp0.dur));
    DEBUG((">>_debug_memData :: isp1, %4.2f, %3.2f, %2.2f, %d\n", memData.isp1.bw, memData.isp1.freq, memData.isp1.sat, memData.isp1.dur));
    DEBUG((">>_debug_memData :: gen, %4.2f, %3.2f, %2.2f, %d\n", memData.gen.bw, memData.gen.freq, memData.gen.sat, memData.gen.dur));
    DEBUG((">>_debug_memData :: fsys, %4.2f, %3.2f, %2.2f, %d\n", memData.fsys.bw, memData.fsys.freq, memData.fsys.sat, memData.fsys.dur));
    DEBUG((">>_debug_memData :: mem0_0, %4.2f, %3.2f, %2.2f, %d\n", memData.mem0_0.bw, memData.mem0_0.freq, memData.mem0_0.sat, memData.mem0_0.dur));
    DEBUG((">>_debug_memData :: mem1_0, %4.2f, %3.2f, %2.2f, %d\n", memData.mem1_0.bw, memData.mem1_0.freq, memData.mem1_0.sat, memData.mem1_0.dur));
    DEBUG((">>_debug_memData :: mem0_1, %4.2f, %3.2f, %2.2f, %d\n", memData.mem0_1.bw, memData.mem0_1.freq, memData.mem0_1.sat, memData.mem0_1.dur));
    DEBUG((">>_debug_memData :: mem1_1, %4.2f, %3.2f, %2.2f, %d\n", memData.mem1_1.bw, memData.mem1_1.freq, memData.mem1_1.sat, memData.mem1_1.dur));
    DEBUG((">>_debug_memData :: cci, %4.2f, %3.2f, %2.2f, %d\n", memData.cci.bw, memData.cci.freq, memData.cci.sat, memData.cci.dur));
    DEBUG((">>_debug_memData :: gsc0, %4.2f, %3.2f, %2.2f, %d\n", memData.gsc0.bw, memData.gsc0.freq, memData.gsc0.sat, memData.gsc0.dur));
    DEBUG((">>_debug_memData :: gsc1, %4.2f, %3.2f, %2.2f, %d\n", memData.gsc1.bw, memData.gsc1.freq, memData.gsc1.sat, memData.gsc1.dur));
    DEBUG((">>_debug_memData :: disp0, %4.2f, %3.2f, %2.2f, %d\n", memData.disp0.bw, memData.disp0.freq, memData.disp0.sat, memData.disp0.dur));
    DEBUG((">>_debug_memData :: disp1, %4.2f, %3.2f, %2.2f, %d\n", memData.disp1.bw, memData.disp1.freq, memData.disp1.sat, memData.disp1.dur));
    DEBUG(("\n---\n"));
}



int main(int argc, char** argv) {
   DEBUG(("Hello world!!!\n"));

   int count;
   count=0;

   while(count<1000){

        initialise();

        getCPUGPUStats(&cpugpuData, count);
        getMemStats(&memData, count);

        //_debug_cpugpuData();
        //_debug_memData();

        usleep(500000);
        count++;





   }






   return 0;



}
