/*
 * Nehe Lesson 33 Code (ported to Linux//GLX by Patrick Schubert 2003
 * with help from the lesson 1 basecode for Linux/GLX by Mihael Vrbanec)
 */

#ifndef TGA_H
#define TGA_H

#include <GL/gl.h>
#include <stdio.h>
#include "Texture.h"

typedef struct
{
	GLubyte Header[12];					/* TGA File Header */
} TGAHeader;

typedef struct
{
	GLubyte		header[6];				/* First 6 Useful Bytes From The Header */
	GLuint		bytesPerPixel;				/* Holds Number Of Bytes Per Pixel Used In The TGA File */
	GLuint		imageSize;				/* Used To Store The Image Size When Setting Aside Ram */
	GLuint		temp;					/* Temporary Variable */
	GLuint		type;
	GLuint		Height;					/* Height of Image */
	GLuint		Width;					/* Width ofImage */
	GLuint		Bpp;					/* Bits Per Pixel */
} TGA;

unsigned char LoadTGA(Texture * texture, char const * filename);	/* Load a TGA file */
unsigned char LoadUncompressedTGA(Texture *,const char *,FILE *);	/* Load an Uncompressed file */
unsigned char LoadCompressedTGA(Texture *,const char *,FILE *);		/* Load a Compressed file */

#endif
