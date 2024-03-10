#include <linux/module.h>
#include <linux/init.h>
#include <linux/input.h>

//This pointer will be used to hold the address of the input device structure
static struct input_dev *input_dev;

//Callback function waiting for the event
static void input_event(unsigned int type, unsigned int code, int value) {
    if (type == EV_KEY && code == BTN_MIDDLE && value == 1) {
        //Takes screenshot and saves it on given location
        system("scrot ~/home/Desktop/screenshot.png");
    }

    //Reports a change in the state of a button or key to the input subsystem
    input_report_key(input_dev, code, value);
    //Synchronizes the input subsystem with the current state of the input device.
    input_sync(input_dev);
}

static int __init mouse_screenshot_init(void) {
    int error;

    //Allocate memory for the input_dev structure
    input_dev = input_allocate_device();
    if (!input_dev) {
        pr_err("Failed to allocate input device\n");
        return -ENOMEM;
    }

    //Sets the name and ID fields of the input_dev structure
    input_dev->name = "Mouse screenshot device";
    input_dev->phys = "mouse-screenshot/input0";
    input_dev->id.bustype = BUS_USB;
    input_dev->id.vendor = 0x0000;
    input_dev->id.product = 0x0000;
    input_dev->id.version = 0x0000;

    //Used to set the input event types that the device is capable of generating
    input_set_capability(input_dev, EV_KEY, BTN_MIDDLE);

    //Register the input device represented by the input_dev structure with the Linux input subsystem
    //Returns 0 if succeeded
    error = input_register_device(input_dev);
    if (error) {
        pr_err("Failed to register input device\n");
        input_free_device(input_dev);
        return error;
    }

    //Indicates that the input device supports keyboard and button events
    input_dev->evbit[0] |= BIT_MASK(EV_KEY);

    //Whenever the input device generates an input event, the input subsystem will invoke the input_event function to handle the event
    input_dev->event = input_event;

    return 0;
}

static void __exit mouse_screenshot_exit(void) {
    input_unregister_device(input_dev);
    input_free_device(input_dev);
}

module_init(mouse_screenshot_init);
module_exit(mouse_screenshot_exit);
