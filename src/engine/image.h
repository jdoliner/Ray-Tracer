/*! \file scene.h
 *
 * \brief A representation of a scene to be rendered
 *
 * \author Joe Doliner
 */

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "vector.h"

/* \brief a representation of a ppm image */
typedef struct {
    int		width;		/*!< the width of the image */
    int 	height; 	/*!< the height of the image */
    Color_t	*data;		/*!< an array of the pixel data */
} Image_t;

/* !New_Image
 * \brief allocates the structures needed for a new image
 * \param width the width of the image
 * \param heigh the heigh of the image
 */
Image_t *New_Image(int width, int height, Color_t *data);

/* !Delete_Image
 * \brief free an image point and the associated data array
 */
void *Delete_Image(Image_t *image);

/* !Write_Image
 * \brief print the image out as a ppm file
 */
int Write_Image(Image_t *image, const char *fname);

#endif
