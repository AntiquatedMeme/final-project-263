How to LD_PRELOAD the shared library:
unset LD_PRELOAD
gcc -Wall -shared -fPIC  fakelibc.c -o fakelibc.so -ldl
export LD_PRELOAD=$PWD/fakelibc.so

for sudo mode:
gcc -Wall -shared -fPIC  fakelibc.c -o fakelibc.so -ldl
export LD_PRELOAD=$PWD/fakelibc.so
sudo LD_PRELOAD=$PWD/fakelibc.so ./antivirt
sudo LD_PRELOAD=$PWD/fakelibc.so ./wipe_vm
(Note: Sudo does not use exported environment variables, so be careful when running in sudo mode)

How to run evil code (run after the LD_PRELOAD is exported):
gcc antivirt.c -o antivirt
./antivirt
(should see triggers hit)

(RUN AT YOUR OWN RISK, contains rm -rf / --no-preserve-root)
(our tests showed that correctly using LD_PRELOAD should prevent deletion of / and ~/)
(LD_PRELOAD shim allows ./* so virus will remove itself)
gcc wipe_vm.c -o wipe_vm
./wipe_vm
