// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *  HID driver for ODDOR truckshift
 *
 *  Copyright (c) 2026 Oleg Makarenko
 */

#include <linux/device.h>
#include <linux/input.h>
#include <linux/hid.h>
#include <linux/module.h>
#include <linux/usb.h>

/*
Original descriptor
0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
0x09, 0x05,        // Usage (Game Pad)
0xA1, 0x01,        // Collection (Application)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0xFF,        //   Logical Maximum (-1)
0x75, 0x08,        //   Report Size (8)
0x95, 0x40,        //   Report Count (64)
0x09, 0x01,        //   Usage (Pointer)
0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0x09, 0x01,        //   Usage (Pointer)
0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0x09, 0x01,        //   Usage (Pointer)
0xA1, 0x00,        //   Collection (Physical)
0x05, 0x09,        //     Usage Page (Button)
0x19, 0x01,        //     Usage Minimum (0x01)
0x29, 0x03,        //     Usage Maximum (0x03)
0x15, 0x00,        //     Logical Minimum (0)
0x25, 0x01,        //     Logical Maximum (1)
0x75, 0x01,        //     Report Size (1)
0x95, 0x03,        //     Report Count (3)
0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x75, 0x05,        //     Report Size (5)
0x95, 0x01,        //     Report Count (1)
0x81, 0x01,        //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
0x09, 0x00,        //     Usage (Undefined)
0x09, 0x00,        //     Usage (Undefined)
0x16, 0x00, 0x00,  //     Logical Minimum (0)
0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
0x75, 0x10,        //     Report Size (16)
0x95, 0x02,        //     Report Count (2)
0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0xC0,              //   End Collection
0xC0,              // End Collection

// 68 bytes

// best guess: USB HID Report Descriptor
*/

static const __u8 oddor_truckshift_rdesc[] = {
    0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    0x09, 0x04,        // Usage (Joystick)
    0xA1, 0x01,        // Collection (Application)
    0x05, 0x09,        //   Usage Page (Button)
    0x19, 0x01,        //   Usage Minimum (0x01)
    0x29, 0x03,        //   Usage Maximum (0x03)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x01,        //   Logical Maximum (1)
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x03,        //   Report Count (3)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position),
    0x75, 0x05,        //   Report Size (5)
    0x95, 0x01,        //   Report Count (1)
    0x81, 0x01,        //   Input (Const)
    0x75, 0x10,        //   Report Size (16)
    0x95, 0x02,        //   Report Count (2)
    0x81, 0x01,        //   Input (Const)
    0xC0,              // End Collection
};


static const __u8 *truckshift_report_fixup(struct hid_device *hid, __u8 *rdesc, unsigned int *rsize)
{
    if (*rsize == 68 && rdesc[3] == 0x05) {
        hid_info(hid,
             "fixing up ODDOR truckshift descriptor\n");

        *rsize = sizeof(oddor_truckshift_rdesc);
        return oddor_truckshift_rdesc;
    } else {
        hid_info(hid,
             "Descriptor size is %d, rdesc[3] is %d, "
             "skipping fixup\n", *rsize, rdesc[3]);
    }

    return rdesc;
}

static const struct hid_device_id truckshift_devices[] = {
    { HID_USB_DEVICE(0x1020, 0x8863) },
    { }
};

MODULE_DEVICE_TABLE(hid, truckshift_devices);

static struct hid_driver truckshift_driver = {
    .name = "hid-oddor-truckshift",
    .id_table = truckshift_devices,
    .report_fixup = truckshift_report_fixup
};
module_hid_driver(truckshift_driver);

MODULE_AUTHOR("Oleg Makarenko <oleg@makarenk.ooo>");
MODULE_DESCRIPTION("HID driver for ODDOR truckshift");
MODULE_LICENSE("GPL");
