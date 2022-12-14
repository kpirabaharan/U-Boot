cd ~/uboot/
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- distclean
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- barrometer_config
time make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j8