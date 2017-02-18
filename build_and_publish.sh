set -e

make clean
make -s all

sleep 1

adb push android-perfstats-collector /data/local/tmp

