#ifndef _TGA_H
#define _TGA_H


#include <stdio.h>
#include <stdlib.h>

#define TGA_RGB	 2
#define TGA_A	 3
#define TGA_RLE	 10

typedef unsigned short WORD;
typedef unsigned char  byte;


struct tImageTGA
{
 tImageTGA(void);
~tImageTGA(void);
 int             channels;
 int             sizeX;
 int             sizeY;
 unsigned char * data;
};


tImageTGA *    LoadTarga(const char *);
unsigned int   LoadTga(const char *);


#endif