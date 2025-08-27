::Using qemu 7.0 (the last version supporting -soundhw)
qemu-system-x86_64 -drive file=bin/OS.img,format=raw -m 8192 -soundhw pcspk,sb16 -monitor stdio