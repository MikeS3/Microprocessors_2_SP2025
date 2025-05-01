#include <interrupt.h>
#include <systick.h>
#include <ioregs.h>
#include "image.h"

ISR(SYSTICK_vect)
{
//systick service routine
if(img[0].index = img[0].size - 1) //at the end of the image
{
    img[0].index = 0; //go to the beginning.

}else
{
    img[0].index++; // increment column
}
NVIC_ISER = 1 << NVIC_BIT(SPI0_vect); //enable SPI interrupt
NVIC_ISPR = 1 << NVIC_BIT(SPI0_vect); //enable interrupt pending register

}