#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <time.h>

/* local includes */
#include "android-perfstats-collector.h"
#include "collect-gpucpu.h"
#include "collect-mem.h"
#include "debug.h"
#include "common.h"




/* global vars */
struct CPUGPUAttr cpugpuData;
struct MemBusAttr memData;
char fnameMemInfo[OUTFNAME_NAME_LEN];
char fnameCPUGPUInfo[OUTFNAME_NAME_LEN];

struct itimerval tick; // timer tick



void initialise(){

    /* init cpugpu structures */
    return;
}


void _debug_cpugpuData(){
    int i;
    DEBUG(("\n--_debug_cpugpuData-\n"));

    for(i = 0;i < NUM_CPU_CORES;i++){
        DEBUG(("cpu%d - %llu, %llu, %llu, %d, %d, %d\n", \
        i, cpugpuData.cpuCoreSet[i].busy, cpugpuData.cpuCoreSet[i].niceBusy, cpugpuData.cpuCoreSet[i].idle, \
        cpugpuData.cpuFreq, cpugpuData.gpuFreq, cpugpuData.gpuUtil));
    }

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
    DEBUG((">>_debug_memData :: mem0_1, %4.2f, %3.2f, %2.2f, %d\n", memData.mem0_1.bw, memData.mem0_1.freq, memData.mem0_1.sat, memData.mem0_1.dur));
    DEBUG((">>_debug_memData :: mem1_0, %4.2f, %3.2f, %2.2f, %d\n", memData.mem1_0.bw, memData.mem1_0.freq, memData.mem1_0.sat, memData.mem1_0.dur));
    DEBUG((">>_debug_memData :: mem1_1, %4.2f, %3.2f, %2.2f, %d\n", memData.mem1_1.bw, memData.mem1_1.freq, memData.mem1_1.sat, memData.mem1_1.dur));
    DEBUG((">>_debug_memData :: cci, %4.2f, %3.2f, %2.2f, %d\n", memData.cci.bw, memData.cci.freq, memData.cci.sat, memData.cci.dur));
    DEBUG((">>_debug_memData :: gsc0, %4.2f, %3.2f, %2.2f, %d\n", memData.gsc0.bw, memData.gsc0.freq, memData.gsc0.sat, memData.gsc0.dur));
    DEBUG((">>_debug_memData :: gsc1, %4.2f, %3.2f, %2.2f, %d\n", memData.gsc1.bw, memData.gsc1.freq, memData.gsc1.sat, memData.gsc1.dur));
    DEBUG((">>_debug_memData :: disp0, %4.2f, %3.2f, %2.2f, %d\n", memData.disp0.bw, memData.disp0.freq, memData.disp0.sat, memData.disp0.dur));
    DEBUG((">>_debug_memData :: disp1, %4.2f, %3.2f, %2.2f, %d\n", memData.disp1.bw, memData.disp1.freq, memData.disp1.sat, memData.disp1.dur));
    DEBUG(("\n---\n"));
}



// log perf stat output for mem related data
void outputResultsMem(int sCount){
    FILE *fp;
    fp = fopen(fnameMemInfo, "a");
    if(fp == NULL){
        DEBUG(("OutputResults:: Error - Couldn't open file - %s \n", fnameMemInfo));
        exit(0);
    }else{

        // write the different data to file
        // irrelevant monitors/probes are commented out
        fprintf(fp, "%d,%4.2f,%3.2f,%2.2f,%d,"
                "%4.2f,%3.2f,%2.2f,%d,"
                //"%4.2f,%3.2f,%2.2f,%d,"
                "%4.2f,%3.2f,%2.2f,%d,"
                "%4.2f,%3.2f,%2.2f,%d,"
                "%4.2f,%3.2f,%2.2f,%d,"
                "%4.2f,%3.2f,%2.2f,%d,"
                "%4.2f,%3.2f,%2.2f,%d,"
                "%4.2f,%3.2f,%2.2f,%d,"
                "%4.2f,%3.2f,%2.2f,%d,"
                "%4.2f,%3.2f,%2.2f,%d,"
                //"%4.2f,%3.2f,%2.2f,%d,"
                //"%4.2f,%3.2f,%2.2f,%d,"
                //"%4.2f,%3.2f,%2.2f,%d,"
                //"%4.2f,%3.2f,%2.2f,%d,"
                "%4.2f,%3.2f,%2.2f,%d\n",

                    sCount,
                    memData.mfc0.bw, memData.mfc0.freq, memData.mfc0.sat, memData.mfc0.dur,
                    memData.mfc1.bw, memData.mfc1.freq, memData.mfc1.sat, memData.mfc1.dur,
                    //memData.gsc23.bw, memData.gsc23.freq, memData.gsc23.sat, memData.gsc23.dur,
                    memData.isp0.bw, memData.isp0.freq, memData.isp0.sat, memData.isp0.dur,
                    memData.isp1.bw, memData.isp1.freq, memData.isp1.sat, memData.isp1.dur,
                    memData.gen.bw, memData.gen.freq, memData.gen.sat, memData.gen.dur,
                    memData.fsys.bw, memData.fsys.freq, memData.fsys.sat, memData.fsys.dur,
                    memData.mem0_0.bw, memData.mem0_0.freq, memData.mem0_0.sat, memData.mem0_0.dur,
                    memData.mem1_0.bw, memData.mem1_0.freq, memData.mem1_0.sat, memData.mem1_0.dur,
                    memData.mem0_1.bw, memData.mem0_1.freq, memData.mem0_1.sat, memData.mem0_1.dur,
                    memData.mem1_1.bw, memData.mem1_1.freq, memData.mem1_1.sat, memData.mem1_1.dur,
                    //memData.cci.bw, memData.cci.freq, memData.cci.sat, memData.cci.dur,
                    //memData.gsc0.bw, memData.gsc0.freq, memData.gsc0.sat, memData.gsc0.dur,
                    //memData.gsc1.bw, memData.gsc1.freq, memData.gsc1.sat, memData.gsc1.dur,
                    //memData.disp0.bw, memData.disp0.freq, memData.disp0.sat, memData.disp0.dur,
                    memData.disp1.bw, memData.disp1.freq, memData.disp1.sat, memData.disp1.dur
                );

    }
    fclose(fp);
    return;

}



// log perf stat output for mem related data
void outputResultsCPUGPU(int sCount){
    FILE *fp;
    fp = fopen(fnameCPUGPUInfo, "a");
    if(fp == NULL){
        DEBUG(("OutputResults:: Error - Couldn't open file - %s \n", fnameCPUGPUInfo));
        exit(0);
    }else{

        // write the different data to file
        // count, freq, {busy, nicebusy, idle} - per CPU, gpufreq, gpuutil
        fprintf(fp, "%d, %d,"
                // fixed for 4 cores
                "%llu,%llu,%llu,"
                "%llu,%llu,%llu,"
                "%llu,%llu,%llu,"
                "%llu,%llu,%llu,"
                "%d,%d\n",

                    sCount, cpugpuData.cpuFreq,
                    cpugpuData.cpuCoreSet[0].busy, cpugpuData.cpuCoreSet[0].niceBusy, cpugpuData.cpuCoreSet[0].idle,
                    cpugpuData.cpuCoreSet[1].busy, cpugpuData.cpuCoreSet[1].niceBusy, cpugpuData.cpuCoreSet[1].idle,
                    cpugpuData.cpuCoreSet[2].busy, cpugpuData.cpuCoreSet[2].niceBusy, cpugpuData.cpuCoreSet[2].idle,
                    cpugpuData.cpuCoreSet[3].busy, cpugpuData.cpuCoreSet[3].niceBusy, cpugpuData.cpuCoreSet[3].idle,
                    cpugpuData.gpuFreq,
                    cpugpuData.gpuUtil
                );

    }
    fclose(fp);
    return;
}








int main(int argc, char** argv) {
   int count;


   DEBUG(("------ Starting Performance Data Collection ---------\n"));

   // save output file name
   if(argc == 3){
       strcpy (fnameMemInfo,argv[1]);
       strcpy (fnameCPUGPUInfo,argv[2]);
   }
   else{
       DEBUG(("main:: Error - not enough arguments : usage: ./android-perfstats-collector <outfile>\n"));
       exit(0);
   }

   // periodically query stats
   count=0;

   while(1){

        //initialise();

        getCPUGPUStats(&cpugpuData, count);
        getMemStats(&memData, count);

        _debug_cpugpuData();
        //_debug_memData();

        outputResultsMem(count);
        outputResultsCPUGPU(count);

        usleep(SAMPLING_PERIOD);
        count++;

   }






   return 0;



}
