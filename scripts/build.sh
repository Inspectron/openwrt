#!/usr/bin/env bash

./scripts/feeds update -a
./scripts/feeds install -a
./scripts/feeds update packages
./scripts/feeds install -a -p packages
cp insp_config .config
make menuconfig
