#include "tga.h"













tImageTGA::tImageTGA(void)
{
 data = NULL;
}


tImageTGA::~tImageTGA(void)
{
 if(data)
 {
  free(data);
 }
}


tImageTGA * LoadTarga(const char *filename)
{
 tImageTGA  * pImageData = NULL;
 WORD         width      = 0;
 WORD         height     = 0;
 byte         length     = 0;
 byte         imageType  = 0;
 byte         bits       = 0;
 FILE       * pFile      = NULL;
 int          channels   = 0;
 int          stride     = 0;
 int          i          = 0;


 if((pFile = fopen(filename, "rb")) == NULL)
 {
  fclose(pFile);
  return 0;
 }

 pImageData = (tImageTGA*)malloc(sizeof(tImageTGA));

 fread(&length, sizeof(byte), 1, pFile);

 fseek(pFile,1,SEEK_CUR);
 fread(&imageType, sizeof(byte), 1, pFile);

 fseek(pFile, 9, SEEK_CUR);
 fread(&width,  sizeof(WORD), 1, pFile);
 fread(&height, sizeof(WORD), 1, pFile);
 fread(&bits,   sizeof(byte), 1, pFile);

 fseek(pFile, length + 1, SEEK_CUR);

 if(imageType != TGA_RLE)
 {
  if(bits == 24 || bits == 32)
  {
	  printf("\n image bits 24/32");
   channels = bits / 8;
   stride = channels * width;
   pImageData->data = new unsigned char[stride * height];

   for(int y = 0; y < height; y++)
   {
    unsigned char *pLine = &(pImageData->data[stride * y]);

    fread(pLine, stride, 1, pFile);

    for(i = 0; i < stride; i += channels)
    {
     int temp     = pLine[i];

     pLine[i]     = pLine[i + 2];
     pLine[i + 2] = temp;
    }
   }
  }

  else if(bits == 16)
  {
   unsigned short pixels = 0;
	printf("\n image bits 16");
   int r = 0;
   int g = 0;
   int b = 0;

   channels         = 3;
   stride           = channels * width;
   pImageData->data = new unsigned char[stride * height];

   for(int i = 0; i < width*height; i++)
   {
    fread(&pixels, sizeof(unsigned short), 1, pFile);

    b = (pixels & 0x1f) << 3;
    g = ((pixels >> 5) & 0x1f) << 3;
    r = ((pixels >> 10) & 0x1f) << 3;

    pImageData->data[i * 3 + 0] = r;
    pImageData->data[i * 3 + 1] = g;
    pImageData->data[i * 3 + 2] = b;
   }
  }
  else
  return NULL;
 }
 else
 {
  byte rleID       = 0;
  int  colorsRead  = 0;
  channels         = bits / 8;
  stride           = channels * width;

  printf("\n image bits compressed");

  pImageData->data = new unsigned char[stride * height];                // <================== get size of this array
  
  printf("\n channel  %i * width %i * height %i", channels, width, height);
  printf("\n %i", stride * height);
  printf("\n");
  
  byte *pColors    = new byte [channels];

  while(i < width*height)
  {
   fread(&rleID, sizeof(byte), 1, pFile);

   if(rleID < 128)
   {
    rleID++;
    while(rleID)
    {
     fread(pColors, sizeof(byte) * channels, 1, pFile);

     pImageData->data[colorsRead + 0] = pColors[2];
     pImageData->data[colorsRead + 1] = pColors[1];
     pImageData->data[colorsRead + 2] = pColors[0];

     if(bits == 32)
     pImageData->data[colorsRead + 3] = pColors[3];

     i++;
     rleID--;
     colorsRead += channels;
    }
   }
   else
   {
    rleID -= 127;

    fread(pColors, sizeof(byte) * channels, 1, pFile);
    while(rleID)
    {
     pImageData->data[colorsRead + 0] = pColors[2];
     pImageData->data[colorsRead + 1] = pColors[1];
     pImageData->data[colorsRead + 2] = pColors[0];

     if(bits == 32)
     pImageData->data[colorsRead + 3] = pColors[3];

     i++;
     rleID--;
     colorsRead += channels;
    }
   }
  }
  delete [] pColors;
 }
 
 

 fclose(pFile);
 pImageData->channels = channels;
 pImageData->sizeX    = width;
 pImageData->sizeY    = height;

 return pImageData;
}



unsigned int LoadTga(const char * FileName)
{
 unsigned int Texture = 0;

 if(!FileName)
 {
  return 0;
 }

 tImageTGA * pImage = LoadTarga(FileName);

 if(pImage == NULL)
 {
  return 0;
 }

 //~ glGenTextures(1, &Texture);
 //~ glBindTexture(GL_TEXTURE_2D, Texture);

 //~ int textureType = GL_RGB;
 //~ if(pImage->channels == 4)
 //~ textureType = GL_RGBA;

 //~ gluBuild2DMipmaps(GL_TEXTURE_2D, pImage->channels, pImage->sizeX,
                   //~ pImage->sizeY, textureType, GL_UNSIGNED_BYTE, pImage->data);

 //~ glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
 //~ glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);


 if(pImage)
 {
  if(pImage->data)
  {
   delete [] pImage->data;
  }
   free(pImage);
   pImage = NULL;
 }
 
 return Texture;
}

