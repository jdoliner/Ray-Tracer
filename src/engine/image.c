/*! \file image.c
 *
 * \brief Implementation of functions to handle .ppm images
 *
 * \author Joe Doliner
 */

#include <stdio.h>
#include "image.h"
#include "defs.h"
#include "vector.h"

/* !New_Image
 * \brief allocates the structures needed for a new image
 * \param width the width of the image
 * \param heigh the heigh of the image
 */
Image_t *New_Image(int width, int height, Color_t *data) {
    Image_t *image = NEW(Image_t);
    image->width = width;
    image->height = height;
    image->data = data;
    return image;
}

/* !Delete_Image
 * \brief free an image point and the associated data array
 */
void Delete_Image(Image_t *image) {
    free(image->data);
    free(image);
}

/* !Write_Image
 * \brief print the image out as a ppm file
 */
void Write_Image(Image_t *image, const char *fname) {
    int i;
    FILE *out = fopen(fname, "wb");
    assert(out);
    fprintf(out, "P3\n%d %d\n255\n", image->width, image->height);
    for (i = 0; i < image->width * image->height; i++) {
	fprintf(out, "%d %d %d", image->data[i][0], image->data[i][1], image->data[i][2]);
	if (i % image->width == 0 && image->width != 0)
	    fprintf(out, "\n");
	else
	    fprintf(out, "\t");
    }
    fclose(out);
}
