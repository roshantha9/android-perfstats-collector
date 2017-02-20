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
    int i,coreCounter=0;
    unsigned long long cpuinfo[10], busy, nice_busy, idle, busysub, nice_busysub, idlesub;

    DEBUG(("-- getCPUGPUStats -- %d\n", sampleCount));
    curCPUFreq = getCurCPUFreq();

    // save curfreq
    cgAttr->cpuFreq = curCPUFreq;

    DEBUG(("curCPUFreq = %d\n", curCPUFreq));

    fp = fopen(PATH_RD_PROCSTAT, "r");
    if(fp){

        fgets(buff, BUFF_SIZE, fp); // ignore first line
		while(fgets(buff, BUFF_SIZE, fp))
		{
			if(strstr(buff, "cpu"))
			{
				coreUtil=0;
				// time(unit: jiffies) spent of all cpus for: user nice system idle iowait irq softirq stead guest
				// get info
				sscanf(buff, "cpu%d %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",\
                                    &coreId, &cpuinfo[0], &cpuinfo[1], \
                                    &cpuinfo[2], &cpuinfo[3], &cpuinfo[4], \
                                    &cpuinfo[5], &cpuinfo[6], &cpuinfo[7], \
                                    &cpuinfo[8], &cpuinfo[9]);


                // calculate metrics
				busy = cpuinfo[0] + cpuinfo[1] + cpuinfo[2] + \
                        cpuinfo[4] + cpuinfo[5] + cpuinfo[6] + \
                        cpuinfo[7] + cpuinfo[8] + cpuinfo[9];

				nice_busy = cpuinfo[1];
				idle = cpuinfo[3];

                DEBUG(("-- cpu%d, %llu, %llu, %llu\n", coreId, busy, nice_busy, idle));

                if (coreCounter >= NUM_CPU_CORES){
                    DEBUG(("getCPUGPUStats:: Error - too many cores counted!"));
                    exit(0);
                }else{
                    cgAttr->cpuCoreSet[coreCounter].busy = busy;
                    cgAttr->cpuCoreSet[coreCounter].niceBusy = nice_busy;
                    cgAttr->cpuCoreSet[coreCounter].idle = idle;
                }

				coreCounter++;
			}
			else{ // string 'cpu' is not found - end of cpu stats reached
				break;
			}
		}
		fclose(fp);
	}
    else{
        DEBUG(("getCPUGPUStats:: Error - failed to open - %s\n", PATH_RD_PROCSTAT));
        exit(0);
    }

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




