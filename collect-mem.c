/* local includes */
#include "collect-mem.h"
#include "common.h"
#include "locations.h"
#include "debug.h"

void getMemStats(struct MemBusAttr *memAttr, int sampleCount){
    FILE *fp;
    int lineCount=0;
    char buff[BUFF_SIZE];



    DEBUG(("-- getMemStats --\n"));

    //printf("%.2f", cgattr->cpuFreq);


    fp = fopen(PATH_RD_BW_MON, "r");
    if(fp){
        fgets(buff, BUFF_SIZE, fp); // ignore first line

        // loop through each line and get bus stats
        while(fgets(buff, BUFF_SIZE, fp)){
            DEBUG(("line %d:: %s", lineCount,buff));




            lineCount++;
        }



    }else{
        DEBUG(("getMemStats:: Error - failed to open - %s\n", PATH_RD_BW_MON));
    }


    memAttr->mem0_0.bw=sampleCount*2.0;

}





