#include <interrupt.h>
#include <systick.h>
#include <ioregs.h>
#include "image.h"

ISR(SYSTICK_vect)
{
//systick service routine
if(img[current_image].index = img[current_image].size - 1) //at the end of the image
{
    img[current_image].index = 0; //go to the beginning.

}else
{
    img[current_image].index++; // increment column
}
NVIC_ISER = 1 << NVIC_BIT(SPI0_vect); //enable SPI interrupt
NVIC_ISPR = 1 << NVIC_BIT(SPI0_vect); //enable interrupt pending register

}
