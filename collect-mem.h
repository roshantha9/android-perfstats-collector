#ifndef __COLLECT_MEM_H_INCLUDED__
#define __COLLECT_MEM_H_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



/* structures */
struct BWMonAttr{
    float bw;
    float freq;
    float sat;
    int dur;
};



struct MemBusAttr{

    // info from bw_mon
    struct BWMonAttr mfc0;
    struct BWMonAttr mfc1;
    struct BWMonAttr gsc23;
    struct BWMonAttr isp0;
    struct BWMonAttr isp1;
    struct BWMonAttr gen;
    struct BWMonAttr fsys;
    struct BWMonAttr mem0_0;
    struct BWMonAttr mem1_0;
    struct BWMonAttr mem0_1;
    struct BWMonAttr mem1_1;
    struct BWMonAttr cci;
    struct BWMonAttr gsc0;
    struct BWMonAttr gsc1;
    struct BWMonAttr disp0;
    struct BWMonAttr disp1;

    // freq info
    int freqBusFreqINT;
    int freqBusFreqMIF;

    // generic mem info
    float memUsage;
    float pageUsage;

};


/* functions */
void getMemStats(struct MemBusAttr *memAttr, int sampleCount);
int getCurMIFFreq(void);
int getCurINTFreq(void);


#endif // __COLLECT_MEM_H_INCLUDED__
