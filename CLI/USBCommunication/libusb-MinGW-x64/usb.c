#include "usb.h"

int cb_done = 0;
libusb_device *device = NULL;
libusb_device **list = NULL;
struct libusb_interface_descriptor itf_desc;

void cb_in(struct libusb_transfer *transfer)
{
    cb_done = 1;
}

void cb_out(struct libusb_transfer *transfer)
{    
    cb_done = 1;
}

void init_usb() {
    libusb_init(NULL);

    // Discover devices
    ssize_t cnt = libusb_get_device_list(NULL, &list);
    for (ssize_t i = 0; i < cnt; i++) {
        device = list[i];
    
        struct libusb_device_descriptor desc;
        while (libusb_get_device_descriptor(device, &desc) != 0);
        if (desc.idVendor == VID && desc.idProduct == PID) {
            struct libusb_config_descriptor *config_desc;
            while (libusb_get_active_config_descriptor(device, &config_desc) != 0);
            const struct libusb_interface *interface_list = config_desc->interface;
            uint8_t num_of_inter = config_desc->bNumInterfaces;
            for (int j = 0; j < num_of_inter; ++j) {
                uint8_t num_of_alt = interface_list[j].num_altsetting;
                for (int k = 0; k < num_of_alt; ++k) {
                    if (interface_list[j].altsetting[k].bNumEndpoints == NUM_ENDPOINS) {
                        itf_desc = interface_list[j].altsetting[k];
                        libusb_free_config_descriptor(config_desc);    
                        return;
                    }
                }
            }
            libusb_free_config_descriptor(config_desc);
        }
    }
}

void release_usb() {
    libusb_free_device_list(list, 1);
    libusb_exit(NULL);
}

int read_usb_raw(uint8_t buf[], uint16_t len)
{
    init_usb();
    struct libusb_config_descriptor *config_desc;
    if (libusb_get_active_config_descriptor(device, &config_desc) != 0)
    {
        libusb_free_config_descriptor(config_desc);
        release_usb();
        return -1;
    }
    struct libusb_device_handle *handle;
    if (libusb_open(device, &handle) != 0)
    {
        libusb_free_config_descriptor(config_desc);
        release_usb();
        return -1;
    }
    if (libusb_claim_interface(handle, itf_desc.bInterfaceNumber) != 0)
    {
        libusb_close(handle);
        libusb_free_config_descriptor(config_desc);
        release_usb();
        return -1;
    }
    uint8_t ep_in = itf_desc.endpoint[EP_IN_INDEX].bEndpointAddress;
    struct libusb_transfer *transfer = libusb_alloc_transfer(0);
    // printf("Reading...\n");
    libusb_fill_bulk_transfer(transfer, handle, ep_in, buf, len, cb_in, NULL, 0);
    if (libusb_submit_transfer(transfer) != 0)
    {
        libusb_release_interface(handle, itf_desc.bInterfaceNumber);
        libusb_close(handle);
        libusb_free_config_descriptor(config_desc);
        release_usb();
        return -1;
    }
    while (cb_done == 0) {
        struct timeval tv;
        tv.tv_sec = 10;
        tv.tv_usec = 0;
        int r = libusb_handle_events_timeout(NULL, &tv);
        if (cb_done == 0 || r < 0)
        {    
            libusb_free_transfer(transfer);
            libusb_release_interface(handle, itf_desc.bInterfaceNumber);
            libusb_close(handle);
            libusb_free_config_descriptor(config_desc);
            release_usb();
            return -1;
        }
    }
    cb_done = 0;

    libusb_free_transfer(transfer);
    libusb_release_interface(handle, itf_desc.bInterfaceNumber);
    libusb_close(handle);
    libusb_free_config_descriptor(config_desc);
    release_usb();

    return 0;
}

int write_usb_raw(uint8_t buf[], uint16_t len)
{
    init_usb();
    struct libusb_config_descriptor *config_desc;
    if (libusb_get_active_config_descriptor(device, &config_desc) != 0)
    {
        release_usb();  
        return -1;
    }
    struct libusb_device_handle *handle;
    if (libusb_open(device, &handle) != 0)
    {
        libusb_free_config_descriptor(config_desc);
        release_usb();
        return -1;
    }
    if (libusb_claim_interface(handle, itf_desc.bInterfaceNumber) != 0)
    {    
        libusb_close(handle);
        libusb_free_config_descriptor(config_desc);
        release_usb();
        return -1;
    }
    uint8_t ep_out = itf_desc.endpoint[EP_OUT_INDEX].bEndpointAddress;
    struct libusb_transfer *transfer = libusb_alloc_transfer(0);
    libusb_fill_bulk_transfer(transfer, handle, ep_out, buf, len, cb_out, NULL, 0);
    // printf("Writing...\n");
    if (libusb_submit_transfer(transfer) != 0)
    {
        libusb_release_interface(handle, itf_desc.bInterfaceNumber);
        libusb_close(handle);
        libusb_free_config_descriptor(config_desc);
        release_usb();
        return -1;
    }
    while (cb_done == 0) {
        struct timeval tv;
        tv.tv_sec = 10;
        tv.tv_usec = 0;
        int r = libusb_handle_events_timeout(NULL, &tv);
        if (cb_done == 0 || r < 0)
        {
            libusb_free_transfer(transfer);
            libusb_release_interface(handle, itf_desc.bInterfaceNumber);
            libusb_close(handle);
            libusb_free_config_descriptor(config_desc);
            release_usb();
            return -1;
        }
    }
    cb_done = 0;

    libusb_free_transfer(transfer);
    libusb_release_interface(handle, itf_desc.bInterfaceNumber);
    libusb_close(handle);
    libusb_free_config_descriptor(config_desc);
    release_usb();

    return 0;
}

void read_usb(uint8_t buf[], uint16_t len)
{
    while (read_usb_raw(buf, len) != 0);
}

void write_usb(uint8_t buf[], uint16_t len)
{
    while (write_usb_raw(buf, len) != 0);
}