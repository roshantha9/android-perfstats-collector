# exit immediately if any command is in error
set -e

# remove previously compiled obj files
make clean

# make silently
make -s all

# wait a little before pushing the result
sleep 1

adb push android-perfstats-collector /data/local/tmp

