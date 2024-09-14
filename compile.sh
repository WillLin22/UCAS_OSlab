#! /usr/bin/bash
# crimg(){
#     cd ./build && ../createimage --extended bootblock main && cd ..
# }

make clean
make dirs
make elf
# crimg
make image
# make debug