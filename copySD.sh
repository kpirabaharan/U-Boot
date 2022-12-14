cd ~/uboot/
sudo dd if=./MLO of=/dev/sdb count=1 seek=1 bs=128k
sudo dd if=./u-boot.img of=/dev/sdb count=2 seek=1 bs=384k