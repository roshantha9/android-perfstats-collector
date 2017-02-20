/* local includes */
#include "collect-mem.h"
#include "common.h"
#include "locations.h"
#include "debug.h"

void getMemStats(struct MemBusAttr *memAttr, int sampleCount){
    FILE *fp;
    int lineCount=0;
    char buff[BUFF_SIZE];
    char name[10];
    float bw, freq, sat;
    int duration;

    DEBUG(("-- getMemStats -- %d\n", sampleCount));

    fp = fopen(PATH_RD_BW_MON, "r");
    if(fp){
        //fgets(buff, BUFF_SIZE, fp); // ignore first line (headers)

        // loop through each line and get bus stats
        while(fgets(buff, BUFF_SIZE, fp)){

            DEBUG(("line %d:: %s", lineCount, buff));

            // get data for each member in the busprobe
            // original printf formatting in the kernel debug : "%-10s %4u.%02u MBps %3u.%02u MHz %2u.%02u%% during %lld us\n"
            sscanf(buff, "%10s %f MBps %f MHz %f%% during %d us\n", name, &bw, &freq, &sat, &duration);

            //DEBUG((">>line sscanf %d:: %10s, %4.2f, %3.2f, %2.2f, %d", lineCount,name, bw, freq, sat, duration));

            // allocate correctly into data struct
            if(strstr(buff, "mfc0")){
                //DEBUG(("--here mfc0\n"));
                memAttr->mfc0.bw=bw;
                memAttr->mfc0.freq=freq;
                memAttr->mfc0.sat=sat;
                memAttr->mfc0.dur=duration;

            }else if(strstr(buff, "mfc1")){
                //DEBUG(("--here mfc1\n"));
                memAttr->mfc1.bw=bw;
                memAttr->mfc1.freq=freq;
                memAttr->mfc1.sat=sat;
                memAttr->mfc1.dur=duration;

            }else if(strstr(buff, "gsc23")){
                //DEBUG(("--here gsc23\n"));
                memAttr->gsc23.bw=bw;
                memAttr->gsc23.freq=freq;
                memAttr->gsc23.sat=sat;
                memAttr->gsc23.dur=duration;

            // we have to move disp0 and disp 1 higher up in the conditional
            // because "isp0" is a substr of disp0, and therefore disp0 wasn't
            // getting caught
            }else if(strstr(buff, "disp0")){
                //DEBUG(("--here disp0\n"));
                memAttr->disp0.bw=bw;
                memAttr->disp0.freq=freq;
                memAttr->disp0.sat=sat;
                memAttr->disp0.dur=duration;

            }else if(strstr(buff, "disp1")){
                //DEBUG(("--here disp1\n"));
                memAttr->disp1.bw=bw;
                memAttr->disp1.freq=freq;
                memAttr->disp1.sat=sat;
                memAttr->disp1.dur=duration;

            }else if(strstr(buff, "gen")){
                 //DEBUG(("--here gen\n"));
                memAttr->gen.bw=bw;
                memAttr->gen.freq=freq;
                memAttr->gen.sat=sat;
                memAttr->gen.dur=duration;

            }else if(strstr(buff, "fsys")){
                //DEBUG(("--here fsys\n"));
                memAttr->fsys.bw=bw;
                memAttr->fsys.freq=freq;
                memAttr->fsys.sat=sat;
                memAttr->fsys.dur=duration;

            }else if(strstr(buff, "mem0_0")){
                //DEBUG(("--here mem0_0\n"));
                memAttr->mem0_0.bw=bw;
                memAttr->mem0_0.freq=freq;
                memAttr->mem0_0.sat=sat;
                memAttr->mem0_0.dur=duration;

            }else if(strstr(buff, "mem0_1")){
                //DEBUG(("--here mem1_0\n"));
                memAttr->mem0_1.bw=bw;
                memAttr->mem0_1.freq=freq;
                memAttr->mem0_1.sat=sat;
                memAttr->mem0_1.dur=duration;

            }else if(strstr(buff, "mem1_0")){
                //DEBUG(("--here mem0_1\n"));
                memAttr->mem1_0.bw=bw;
                memAttr->mem1_0.freq=freq;
                memAttr->mem1_0.sat=sat;
                memAttr->mem1_0.dur=duration;

            }else if(strstr(buff, "mem1_1")){
                //DEBUG(("--here mem1_1\n"));
                memAttr->mem1_1.bw=bw;
                memAttr->mem1_1.freq=freq;
                memAttr->mem1_1.sat=sat;
                memAttr->mem1_1.dur=duration;

            }else if(strstr(buff, "cci")){
                //DEBUG(("--here cci\n"));
                memAttr->cci.bw=bw;
                memAttr->cci.freq=freq;
                memAttr->cci.sat=sat;
                memAttr->cci.dur=duration;

            }else if(strstr(buff, "gsc0")){
                //DEBUG(("--here gsc0\n"));
                memAttr->gsc0.bw=bw;
                memAttr->gsc0.freq=freq;
                memAttr->gsc0.sat=sat;
                memAttr->gsc0.dur=duration;

            }else if(strstr(buff, "gsc1")){
                //DEBUG(("--here gsc1\n"));
                memAttr->gsc1.bw=bw;
                memAttr->gsc1.freq=freq;
                memAttr->gsc1.sat=sat;
                memAttr->gsc1.dur=duration;

            }else if(strstr(buff, "isp0")){
                //DEBUG(("--here isp0\n"));
                memAttr->isp0.bw=bw;
                memAttr->isp0.freq=freq;
                memAttr->isp0.sat=sat;
                memAttr->isp0.dur=duration;


            }else if(strstr(buff, "isp1")){
                //DEBUG(("--here isp1\n"));
                memAttr->isp1.bw=bw;
                memAttr->isp1.freq=freq;
                memAttr->isp1.sat=sat;
                memAttr->isp1.dur=duration;

            }else{
                DEBUG(("getMemStats:: WARNING : unknown bwprobe member detected\n"));
            }


            lineCount++;
        }

    }else{
        DEBUG(("getMemStats:: Error - failed to open - %s\n", PATH_RD_BW_MON));
    }

    // close file
    fclose(fp);

}





