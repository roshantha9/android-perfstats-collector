/* local includes */
#include "collect-gpucpu.h"
#include "debug.h"


void getCPUGPUStats(struct CPUGPUAttr *cgAttr, int sampleCount){
    DEBUG(("-- getCPUGPUStats --\n"));

    //printf("%.2f", cgattr->cpuFreq);

    cgAttr->clusterConfig=sampleCount;

}





