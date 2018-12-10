How to LD_PRELOAD the shared library:
unset LD_PRELOAD
gcc -Wall -shared -fPIC  fakelibc.c -o fakelibc.so -ldl
export LD_PRELOAD=$PWD/fakelibc.so

How to run evil code (run after the LD_PRELOAD is exported):
gcc antivirt.c -o antivirt
./antivirt
(should see triggers hit)

(RUN AT YOUR OWN RISK, contains rm -rf / --no-preserve-root)
(our tests showed that correctly using LD_PRELOAD should prevent deletion of / and ~/)
(LD_PRELOAD shim allows ./* so virus will remove itself)
gcc wipe_vm.c -o wipe_vm
./wipe_vm

Notes on sudo:
sudo messes with environment variables, so exporting LD_PRELOAD may not carry over to sudo. 
Our tests were run in user mode for that reason, but environment variables for sudo can be edited.
Thus, our implementations provides a proof of concept that this approach can work, and it should 
carry over to sudo when the LD_PRELOAD is configured correctly for sudo.
