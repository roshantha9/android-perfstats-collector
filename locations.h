#ifndef __LOCATIONS_H_INCLUDED__
#define __LOCATIONS_H_INCLUDED__

/* input file locations */

// memory related
#define PATH_RD_BW_MON          "/sys/kernel/debug/bw_monitor"
#define PATH_RD_MIF_CUR_FREQ    "/sys/devices/platform/exynos5-busfreq-mif/devfreq/exynos5-busfreq-mif/cur_freq"
#define PATH_RD_INT_CUR_FREQ   "/sys/devices/platform/exynos5-busfreq-int/devfreq/exynos5-busfreq-int/cur_freq"

// cpu gpu related
#define PATH_RD_PROCSTAT    "/proc/stat"
#define PATH_RD_GPUUTIL     "/sys/module/pvrsrvkm/parameters/sgx_gpu_utilization"
#define PATH_RD_CPUFREQ     "/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq"
#define PATH_RD_GPUFREQ     "/sys/module/pvrsrvkm/parameters/sgx_gpu_clk"




#endif // __COLLECT_GPUCPU_H_INCLUDED__
