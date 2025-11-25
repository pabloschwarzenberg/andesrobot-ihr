Conflicto en libgl con python3-opencv

libGL error: No matching fbConfigs or visuals found
libGL error: failed to load driver: swrast

milo@milo:~/Documents/andesrobot-ihr/vision$ sudo ldconfig -p | grep -i gl.so
[sudo] password for milo: 
	libwayland-egl.so.1 (libc6,AArch64) => /lib/aarch64-linux-gnu/libwayland-egl.so.1
	libwayland-egl.so.1 (libc6,AArch64) => /usr/lib/aarch64-linux-gnu/nvidia/libwayland-egl.so.1
	libwayland-egl.so (libc6,AArch64) => /lib/aarch64-linux-gnu/libwayland-gl.so
	libwayland-egl.so (libc6,AArch64) => /usr/lib/aarch64-linux-gnu/nvidia/libwayland-egl.so