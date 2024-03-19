# Mouse Screenshot Kernel Module

## Overview
This kernel module allows you to capture a screenshot on Linux systems when the middle button of a mouse is pressed. It integrates with the Linux input subsystem to detect mouse events and execute the screenshot command.

## Prerequisites
- Linux kernel headers must be installed on your system.
- The `scrot` command-line tool must be installed to capture screenshots.

## Installation
1. Compile the kernel module by running:
    ```
    make
    ```

2. Load the module into the kernel using:
    ```
    sudo insmod mouse_screenshot.ko
    ```

## Usage
Once the module is loaded, simply press the middle button of your mouse to capture a screenshot. The screenshot will be saved to `~/home/Desktop/screenshot.png`.

## Uninstallation
To unload the module from the kernel, execute:
```
sudo rmmod mouse_screenshot
```

## Resources
Linux Input Subsystem:  [https://www.kernel.org/doc/html/v4.16/driver-api/input.html](https://www.kernel.org/doc/html/v4.16/driver-api/input.html)
