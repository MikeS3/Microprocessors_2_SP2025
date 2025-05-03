#include <ioregs.h>
#include <syscall_list.h>

int svc_set_led(unsigned int state) {
    if(state) {
        /* set LED on GP25 to high */
        SIO.gpio_out_set = (1u << 25);  // Set the output high
    } else {
        /* set LED on GP25 to low */
        SIO.gpio_out_clr = (1u << 25);  // Clear the output (set low)
    }
    return 0;
}