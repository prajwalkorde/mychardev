# MyCharDev – Simple Character Device Driver

## Overview

`mychardev` is a Linux kernel module that implements a **simple character device** using `register_chrdev`.  
It provides basic `read()` and `write()` functionality through a fixed-size kernel buffer.  
After loading, the device node `/dev/mychardev` can be used from user-space programs or shell commands.

---

## Features

- Dynamically allocated major number via `register_chrdev`.
- Supports:
  - `open()` / `release()`
  - `read()` from kernel buffer
  - `write()` to kernel buffer
  - `llseek()` within the buffer
- Fixed buffer size: 4096 bytes (`BUF_SIZE`)
- Minimal, educational example for character device drivers.

---

## Project Structure

mychardev/
├─ Makefile # Kernel module build instructions
└─ mychardev.c # Character device driver source code


---

## Build Instructions

1. Install kernel headers and build tools (Debian/Ubuntu):
```bash
sudo apt install build-essential linux-headers-$(uname -r)

Build the kernel module:
make
