/*
 * Nehe Lesson 33 Code (ported to Linux//GLX by Patrick Schubert 2003
 * with help from the lesson 1 basecode for Linux/GLX by Mihael Vrbanec)
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>

enum texType {empty = 0, warehouse, crate, warehousePillar, warehouseFloor, stoneWall, brickWall, grass,  mansion, garden, extraBombs, stim, extraRange,  metalDoor,fire1}; 

struct Texture{
	GLubyte	* imageData;				/* Image Data (Up To 32 Bits) */
	GLuint	bpp;					/* Image Color Depth In Bits Per Pixel */
	GLuint	width;					/* Image Width */
	GLuint	height;					/* Image Height */
	GLuint	texID;					/* Texture ID Used To Select A Texture */
	GLuint	type;					/* Image Type (GL_RGB, GL_RGBA) */
	Texture() : imageData(0), bpp(0), width(0), height(0), texID(0), type(0){}
};	

#endif
