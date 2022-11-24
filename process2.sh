#!/usr/bin/bash
# echo helloworld1
cd ..
cd new_kernel/linux-5.19.8
make -j$(nproc)
