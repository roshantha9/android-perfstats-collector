/* local includes */
#include "collect-gpucpu.h"
#include "debug.h"
#include "common.h"
#include "locations.h"

void getCPUGPUStats(struct CPUGPUAttr *cgAttr, int sampleCount){
    FILE *fp;
    int lineCount=0;
    char buff[BUFF_SIZE];
    int coreId;
    int coreUtil;
    int curCPUFreq;
    unsigned long long cpuinfo[10], busy, nice_busy, idle, busysub, nice_busysub, idlesub;

    DEBUG(("-- getCPUGPUStats -- %d\n", sampleCount));
    curCPUFreq = getCurCPUFreq();

    DEBUG(("curCPUFreq = %d\n", curCPUFreq));

    /*
    fp = fopen(PATH_RD_PROCSTAT, "r");
    if(fp){

        fgets(buff, BUFF_SIZE, fp); // ignore first line
		while(fgets(buff, BUFF_SIZE, fp))
		{
			if(strstr(buff, "cpu"))
			{
				coreUtil=0;
				// time(unit: jiffies) spent of all cpus for: user nice system idle iowait irq softirq stead guest
				sscanf(buff, "cpu%d %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",\
                                    &coreId, &cpuinfo[0], &cpuinfo[1], \
                                    &cpuinfo[2], &cpuinfo[3], &cpuinfo[4], \
                                    &cpuinfo[5], &cpuinfo[6], &cpuinfo[7], \
                                    &cpuinfo[8], &cpuinfo[9]);

				busy = cpuinfo[0] + cpuinfo[1] + cpuinfo[2] + \
                        cpuinfo[4] + cpuinfo[5] + cpuinfo[6] + \
                        cpuinfo[7] + cpuinfo[8] + cpuinfo[9];

				busysub = busy - coreSet[coreId].busy;
				nice_busy = cpuinfo[1];
				nice_busysub = nice_busy - coreSet[coreId].nice_busy;
				idle = cpuinfo[3];
				idlesub = idle - coreSet[coreId].idle;
				if(busysub + idlesub == 0)
				{
					coreSet[coreId].util = 0;
					coreSet[coreId].midUtil = 0;
				}
				else
				{
					coreSet[coreId].util = (float)(busysub) / (busysub + idlesub) * CPUFreq;
					coreSet[coreId].midUtil = (float)(busysub - nice_busysub) / (busysub + idlesub) * CPUFreq;
				}

                //log for governor
				totalCUtilization = totalCUtilization + coreSet[coreId].util;
				coreCounter++;
				if(currentCUtilization < coreSet[coreId].util)
					currentCUtilization = coreSet[coreId].util;

				INFO(("core %d: util %f midUtil %f\n", coreId, coreSet[coreId].util, coreSet[coreId].midUtil));
				coreSet[coreId].busy = busy;
				coreSet[coreId].nice_busy = nice_busy;
				coreSet[coreId].idle = idle;
			}
			else // string 'cpu' is not found
			{
				break;
			}
		}
		fclose(fp);
	}
    else{
        DEBUG(("getCPUGPUStats:: Error - failed to open - %s\n", PATH_RD_PROCSTAT));
    }
    */


    cgAttr->clusterConfig=sampleCount;

}


int getCurCPUFreq(void){
	int freq;
	FILE *fp = fopen(PATH_RD_CPUFREQ, "r");
	if(fp){
		fscanf(fp, "%d", &freq);
		fclose(fp);
	}else{
	    DEBUG(("getCurCPUFreq:: Error - failed to open - %s\n", PATH_RD_CPUFREQ));
		exit(0);
	}
	return freq;
}




