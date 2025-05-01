#ifndef IMAGE_H__
#define IMAGE_H__

extern struct image_data
	{
		unsigned short size;
		unsigned short index;
		unsigned char data[0x300];
	} img[2];

#endif