# Driver for ODDOR truck shifter knob


## Installation

### Manual

```
make install
```

### DKMS
DKMS will install module into system, and will update it every time you update your kernel. Module will persist after reboots. It's the preferrable way to install it on the most distros.

1. Install `dkms` package from your distro package manager
2. Clone repository to `/usr/src/oddor-truckshift`
3. Install the module:
`sudo dkms install /usr/src/oddor-truckshift`
4. Update initramfs:
`sudo update-initramfs -u`
5. Reboot

To remove module:
`sudo dkms remove oddor-truckshift/<version> --all`
