/*! \file matrix.h
 *
 * \author John Reppy
 */

/* CMSC23700 Sample code
 *
 * COPYRIGHT (c) 2010 John Reppy (http://cs.uchicago.edu/~jhr)
 * All rights reserved.
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "defs.h"
#include "vector.h"

/*! \brief a 3x3 matrix */
typedef float		Mat3x3f_t[9];

/*! \brief a 4x4 matrix */
typedef float		Mat4x4f_t[16];



/***** Matrix3f_t utilities *****/

/*! \brief matrix copy
 *  \param src the source matrix
 *  \param dst the destination matrix
 *
 * sets the vector \a dst to \a src
 */
static inline void CopyM3f (Mat3x3f_t src, Mat3x3f_t dst)
{
    for (int i = 0;  i < 9;  i++) dst[i] = src[i];
}

/*! \brief set the matrix to the identity */
extern void LoadIdentityM3f (Mat3x3f_t m);

/*! \brief matrix-vector multiply
 *  \param mat the matrix
 *  \param v the vector
 *  \param dst the destination vector
 *
 * sets the vector \a dst to \a mat * \a v.
 */
static inline void MultMV3f (Mat3x3f_t mat, Vec3f_t v, Vec3f_t dst)
{
    for (int i = 0;  i < 3;  i++) {
	dst[i] = mat[0+i] * v[0] + mat[3+i] * v[1] + mat[6+i] * v[2];
    }
}

/*! \brief matrix-matrix multiply
 *  \param m1 the matrix
 *  \param m2 the other matrix
 *  \param dst the destination matrix (should not be \a m1 or \a m2)
 *
 * sets the matrix \a dst to \a m1 * \a m2.
 */
extern void MultMM3f (Mat3x3f_t m1, Mat3x3f_t m2, Mat3x3f_t dst);

/*! \brief return the determinate of the matrix.
 */
static inline float DetM3f (Mat3x3f_t m)
{
    return m[0]*(m[4]*m[8] - m[7]*m[5])
	 - m[3]*(m[1]*m[8] - m[7]*m[2])
	 + m[6]*(m[1]*m[5] - m[4]*m[2]);
}


/***** Matrix4f_t utilities *****/

/* index for column-major layout */
#define _I(r,c)		(4*(c)+(r))

/*! \brief matrix copy
 *  \param src the source matrix
 *  \param dst the destination matrix
 *
 * sets the vector \a dst to \a src
 */
static inline void CopyM4f (Mat4x4f_t src, Mat4x4f_t dst)
{
    for (int i = 0;  i < 16;  i++) dst[i] = src[i];
}

/*! \brief get the ith row of the matrix.
 *  \param m the source matrix
 *  \param i the row index (between 0 and 3)
 *  \param row the vector to copy the row into.
 */
static inline void RowM4f (Mat4x4f_t m, int i, Vec4f_t row)
{
    assert ((0 <= i) && (i < 4));
    row[0] = m[_I(i,0)];
    row[1] = m[_I(i,1)];
    row[2] = m[_I(i,2)];
    row[3] = m[_I(i,3)];
}

/*! \brief get the ith column of the matrix.
 *  \param m the source matrix
 *  \param i the column index (between 0 and 3)
 *  \param col the vector to copy the column into.
 */
static inline void ColM4f (Mat4x4f_t m, int i, Vec4f_t col)
{
    assert ((0 <= i) && (i < 4));
    col[0] = m[_I(0,i)];
    col[1] = m[_I(1,i)];
    col[2] = m[_I(2,i)];
    col[3] = m[_I(3,i)];
}

/*! \brief set the matrix to the identity
 *  \param m the destination matrix
 *
 * This function sets \a m = I.
 */
extern void LoadIdentityM4f (Mat4x4f_t m);

/*! \brief load an isometric-scaling transformation.
 *  \param s the scaling factor.
 *  \param m the destination matrix
 *
 * This function sets \a m = S(\a s).
 */
extern void LoadIsoScaleM4f (float s, Mat4x4f_t m);

/*! \brief load an anisometric-scaling transformation.
 *  \param sx the X scaling factor.
 *  \param sy the Y scaling factor.
 *  \param sz the Z scaling factor.
 *  \param m the destination matrix
 *
 * This function sets \a dst = S(\a sx, \a sy, \a sz).
 */
extern void LoadScaleM4f (float sx, float sy, float sz, Mat4x4f_t m);

/*! \brief load a translation transformation.
 *  \param tx the X translation.
 *  \param ty the Y translation.
 *  \param tz the Z translation.
 *  \param m the destination matrix
 *
 * This function sets \a m = T(\a tx, \a ty, \a tz).
 */
extern void LoadTranslateM4f (float tx, float ty, float tz, Mat4x4f_t m);

/*! \brief concatenate an isometric-scaling transformation.
 *  \param s the scaling factor.
 *  \param m the matrix to be scaled
 *  \param dst the destination matrix
 *
 * This function sets \a dst = \a m * S(\a s)
 */
extern void IsoScaleM4f (float s, Mat4x4f_t m, Mat4x4f_t dst);

/*! \brief concatenate an anisometric-scaling transformation.
 *  \param sx the X scaling factor.
 *  \param sy the Y scaling factor.
 *  \param sz the Z scaling factor.
 *  \param m the matrix to be scaled
 *  \param dst the destination matrix
 *
 * This function sets \a dst = \a m * S(\a sx, \a sy, \a sz)
 */
extern void ScaleM4f (float sx, float sy, float sz, Mat4x4f_t m, Mat4x4f_t dst);

/*! \brief concatenate a translation transformation.
 *  \param tx the X translation.
 *  \param ty the Y translation.
 *  \param tz the Z translation.
 *  \param m the matrix to be scaled
 *  \param dst the destination matrix
 *
 * This function sets \a dst = \a m * T(\a tx, \a ty, \a tz)
 */
extern void TranslateM4f (float tx, float ty, float tz, Mat4x4f_t m, Mat4x4f_t dst);

/*!\brief transform a 3D vector by a matrix in column-major order
 */
static inline void TransformVec3f (Mat4x4f_t mat, Vec3f_t v, Vec3f_t dst)
{
    dst[0] = mat[_I(0,0)]*v[0] + mat[_I(0,1)]*v[1] + mat[_I(0,2)]*v[2];
    dst[1] = mat[_I(1,0)]*v[0] + mat[_I(1,1)]*v[1] + mat[_I(1,2)]*v[2];
    dst[2] = mat[_I(2,0)]*v[0] + mat[_I(2,1)]*v[1] + mat[_I(2,2)]*v[2];
}

/*!\brief transform a 3D point by a matrix in column-major order
 */
static inline void TransformPt3f (Mat4x4f_t mat, Vec3f_t pt, Vec3f_t dst)
{
    dst[0] = mat[_I(0,0)]*pt[0] + mat[_I(0,1)]*pt[1] + mat[_I(0,2)]*pt[2] + mat[_I(0,3)];
    dst[1] = mat[_I(1,0)]*pt[0] + mat[_I(1,1)]*pt[1] + mat[_I(1,2)]*pt[2] + mat[_I(1,3)];
    dst[2] = mat[_I(2,0)]*pt[0] + mat[_I(2,1)]*pt[1] + mat[_I(2,2)]*pt[2] + mat[_I(2,3)];
}

/*!\brief transform a 4D vector by a matrix in column-major order
 */
static inline void MulMatVec4f (Mat4x4f_t mat, Vec4f_t v, Vec4f_t dst)
{
    dst[0] = mat[_I(0,0)]*v[0] + mat[_I(0,1)]*v[1] + mat[_I(0,2)]*v[2] + mat[_I(0,3)]*v[3];
    dst[1] = mat[_I(1,0)]*v[0] + mat[_I(1,1)]*v[1] + mat[_I(1,2)]*v[2] + mat[_I(1,3)]*v[3];
    dst[2] = mat[_I(2,0)]*v[0] + mat[_I(2,1)]*v[1] + mat[_I(2,2)]*v[2] + mat[_I(2,3)]*v[3];
    dst[3] = mat[_I(3,0)]*v[0] + mat[_I(3,1)]*v[1] + mat[_I(3,2)]*v[2] + mat[_I(3,3)]*v[3];
}

/*! \brief matrix-matrix multiply
 *  \param m1 the matrix
 *  \param m2 the other matrix
 *  \param dst the destination matrix (should not be \a m2)
 *
 * Sets the matrix \a dst to \a m1 * \a m2.  Note that m1 and dst
 * are allowed to be the same matrix, but that m2 and dst must be
 * different.
 */
extern void MultMM4f (Mat4x4f_t m1, Mat4x4f_t m2, Mat4x4f_t dst);

/*! \brief compute the inverse of a matrix.
 *  \param m the input matrix
 *  \param dst the destination matrix
 *  \returns true if the matrix was invertible.
 */
extern bool InverseM4f (Mat4x4f_t m, Mat4x4f_t dst);

/*! \brief print the matrix to stdout. */
extern void PrintM4f (Mat4x4f_t m);

#undef _I

#endif /*!_MATRIX_H_ */
