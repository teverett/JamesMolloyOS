
[![CI](https://github.com/teverett/JamesMolloyOS/actions/workflows/main.yml/badge.svg)](https://github.com/teverett/JamesMolloyOS/actions/workflows/main.yml)

# James Molloy Tutorial OS

## Introduction

This repo was forked from, a copy of chapter 10 of the James Molloy tutorials.

https://github.com/cirosantilli/jamesmolloy-kernel-development-tutorials/tree/master/10_user

It has numerous fixes from this page:

https://wiki.osdev.org/James_Molloy%27s_Tutorial_Known_Bugs

And some new code to set up a kernel stack which was developed here with help from the OSdev.org community

https://forum.osdev.org/viewtopic.php?t=57734 

The OS boots into user mode as intended.  The Github actions config contains the necessary configuratation steps to create a working build environment on OS X and Linux.  Kernel image, FS image and a dump file are uploaded as Github artefacts.

![boot](https://github.com/teverett/JamesMolloyOS/blob/main/pic/boot.png?raw=true)

## Building

To build the Kernel

<code>
make clean
make
make run
<code>

for debugging with Qemu

<code>
make clean
make
make debug
</code>

## Debugging

On VSCode, use this launch.json configuration

<code>
{
    "version": "0.2.0",
    "configurations": [
      {
        "type": "gdb",
        "request": "attach",
        "name": "Attach to gdbserver",
        "executable": "kernel/bin/kernel.elf",
        "target": ":1234",
        "remote": true,
        "cwd": "${workspaceRoot}",
        "valuesFormatting": "parseText"
      }
    ]
  }
</code>