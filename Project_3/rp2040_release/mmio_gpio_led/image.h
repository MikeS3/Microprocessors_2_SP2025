#ifndef IMAGE_H__
#define IMAGE_H__

extern struct image_data
	{
		unsigned short size;
		unsigned short index;
		unsigned char data[0x300];
	} img[2];

	extern enum ImageState{
		IMAGE_0 = 0,
		IMAGE_1 = 1
	} current_image;;


#endif