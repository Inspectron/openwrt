#!/usr/bin/env bash

# Check if the number of arguments is 1
if [ $# -ne 1 ]; then
  echo "Usage: $0 <number_of_jobs_for_make>"
  exit 1
fi

./scripts/feeds update -a
./scripts/feeds install -a
./scripts/feeds update packages
./scripts/feeds install -a -p packages
cp insp_config .config
make menuconfig
make -j$1
