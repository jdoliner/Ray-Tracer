/*! \file vector.h
 *
 * \brief Various types and operations for 3D vectors.
 *
 * \author John Reppy
 */

/* CMSC23700 Sample code
 *
 * COPYRIGHT (c) 2010 John Reppy (http://www.cs.uchicago.edu/~jhr)
 * All rights reserved.
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>

/*! \brief a small value for testing if something is close to 0 */
#define EPSILON 1e-6

typedef float		Vec2f_t[2];	//!< 2D vector (used for texture coords)
typedef float		Vec3f_t[3];	//!< 3D vector
typedef float		Vec4f_t[4];	//!< 4D vector
typedef unsigned char	Color_t[4];	//!< RGBA color representation

/*! \brief a ray */
typedef struct {
    Vec3f_t	orig;			//!< the origin of the ray
    Vec3f_t	dir;			//!< the direction of the ray, which should be
					//!< a unit vector
} Rayf_t;

/*! \brief find the minumum of 2 floats */
static inline float Minf (float a, float b) {
    if (a < b)
	return a;
    else
	return b;
}

/* \brief find the maximum of 2 floats */
static inline float Maxf (float a, float b) {
    if (a > b)
	return a;
    else
	return b;
}

/* \brief find the absolute value of a float */
static inline float Absf (float a) {
    if (a > 0)
	return a;
    else
	return -a;
}

//! \brief Square a number
static inline float Sqrf (float x) { return (x*x); }

//! \brief clamp a float value to [0.0,1.0]
static inline float Clampf (float x)
{
    if (x < 0.0) return 0.0;
    else if (x > 1.0) return 1.0;
    else return x;
}

/*! \brief copy a 2D vector
 *  \param src the source vector
 *  \param dst the destination vector
 *
 * sets the vector \a dst to \a src
 */
static inline void CopyV2f (Vec2f_t src, Vec2f_t dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
}

//! \brief 3D vector dot product
//! \param v1 an argument vector
//! \param v2 an argument vector
//! \return the dot produce of \a v1 and \a v2
static inline float DotV3f (Vec3f_t v1, Vec3f_t v2)
{
    return ((v1[0]*v2[0]) + (v1[1]*v2[1]) + (v1[2]*v2[2]));
}

//! \brief return the length squared of a 3D vector
//! \param v the argument vector
//! \return the square of the length of \a v
static inline float LengthSqV3f (Vec3f_t v)
{
    return DotV3f (v, v);
}

//! vector length
//! \param v the argument vector
//! \return the length of \a v
static inline float LengthV3f (Vec3f_t v)
{
    return sqrt (LengthSqV3f(v));
}

/*! \brief scalar-vector multiplication
 *  \param s the scalar multiplier
 *  \param v the vector to be scaled
 *  \param dst the result vector
 *
 *  sets the vector \a dst to \a s * \a v.
 */
static inline void ScaleV3f (float s, Vec3f_t v, Vec3f_t dst)
{
    dst[0] = s*v[0];
    dst[1] = s*v[1];
    dst[2] = s*v[2];
}

/*! \brief vector normalization
 *  \param v the vector to normalize
 *  \return the length of \a v
 *
 * This function normalized \a v to be a unit vector and returns the
 * original length of \a v.  If the length of \a v is close to zero,
 * the it is not normalized and 0 is returned.
 */
static inline float NormalizeV3f (Vec3f_t v)
{
    float s = LengthSqV3f(v);
    if (s < EPSILON) return 0.0;
    s = sqrt(s);
    ScaleV3f (1.0 / s, v, v);
    return s;
}

/*! \brief Clamp a vector to the unit cube
 *  \param v the vector to be clamped.
 *
 * Clamps each coordinate of \a v to the unit interval.
 */
static inline void ClampV3f (Vec3f_t v)
{
    v[0] = Clampf(v[0]);
    v[1] = Clampf(v[1]);
    v[2] = Clampf(v[2]);
}

/*! \brief vector negation
 *  \param v an argument vector
 *  \param dst the result vector
 *
 * sets the vector \a dst to the negation of \a v
 */
static inline void NegV3f (Vec3f_t v, Vec3f_t dst)
{
    dst[0] = -v[0];
    dst[1] = -v[1];
    dst[2] = -v[2];
}

/*! \brief vector copy
 *  \param src the source vector
 *  \param dst the destination vector
 *
 * sets the vector \a dst to \a src
 */
static inline void CopyV3f (Vec3f_t src, Vec3f_t dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

/*! \brief vector addition
 *  \param u an argument vector
 *  \param v an argument vector
 *  \param dst the result vector
 *
 * sets the vector \a dst to \a u + \a v
 */
static inline void AddV3f (Vec3f_t u, Vec3f_t v, Vec3f_t dst)
{
    dst[0] = u[0] + v[0];
    dst[1] = u[1] + v[1];
    dst[2] = u[2] + v[2];
}

/*! \brief scaled vector addition
 *  \param u an argument vector
 *  \param s the scaling factor
 *  \param v an argument vector
 *  \param dst the result vector
 * 
 *  sets the vector \a dst to \a u + \a s * \a v
 */
static inline void ScaledAddV3f (Vec3f_t u, float s, Vec3f_t v, Vec3f_t dst)
{
    dst[0] = u[0] + s*v[0];
    dst[1] = u[1] + s*v[1];
    dst[2] = u[2] + s*v[2];
}

/*! \brief vector subtraction
 *  \param u an argument vector
 *  \param v an argument vector
 *  \param dst the result vector
 *
 * sets the vector \a dst to \a u - \a v
 */
static inline void SubV3f (Vec3f_t u, Vec3f_t v, Vec3f_t dst)
{
    dst[0] = u[0] - v[0];
    dst[1] = u[1] - v[1];
    dst[2] = u[2] - v[2];
}

/*! \brief linear interpolation between two vectors.
 *  \param u an argument vector
 *  \param s the scaling factor
 *  \param v an argument vector
 *  \param dst the result vector
 * 
 *  sets the vector \a dst to (1-t)*\a u + \a t * \a v
 */
static inline void LerpV3f (Vec3f_t u, float t, Vec3f_t v, Vec3f_t dst)
{
    dst[0] = u[0] + t*(v[0] - u[0]);
    dst[1] = u[1] + t*(v[1] - u[1]);
    dst[2] = u[2] + t*(v[2] - u[2]);
}

/*! \brief vector cross product
 *  \param v1 an argument vector
 *  \param v2 an argument vector
 *  \param dst the result vector
 * 
 *  sets the vector \a dst to the cross product of \a v1 and \a v2.
 */
static inline void CrossV3f (Vec3f_t v1, Vec3f_t v2, Vec3f_t dst)
{
    float x = v1[1]*v2[2] - v1[2]*v2[1];
    float y = v1[2]*v2[0] - v1[0]*v2[2];
    float z = v1[0]*v2[1] - v1[1]*v2[0];
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
}

/*! \brief reflect 1 vector over a normal vector
 *  \param v the vector to be reflected
 *  \param N the normal vector
 *  \param dst the result vector
 */
static inline void ReflectV3f (Vec3f_t v, Vec3f_t N, Vec3f_t dst)
{
    Vec3f_t tmp;
    ScaleV3f(2 * DotV3f(N, v), N, tmp);
    SubV3f(v, tmp, tmp);
    CopyV3f(tmp, dst);
}

//! return a point on a ray
//! \param r the ray
//! \param t the distance along the ray
//! \param dst the resulting point
static inline void RayToPointf (Rayf_t *r, float t, Vec3f_t dst)
{
    ScaledAddV3f (r->orig, t, r->dir, dst);
}

//! make a ray: p1------p2-->
//! \param p1 the first point
//! \param p2 the second point
//! \param dst the destination ray
static inline void PointstoRayf (Vec3f_t p1, Vec3f_t p2, Rayf_t *dst)
{
    CopyV3f(p1, dst->orig);
    SubV3f(p2, p1, dst->dir);
    NormalizeV3f(dst->dir);
}

//! \brief copy a color
//! \param src the source color
//! \param dst the destination color
static inline void CopyColor (Color_t src, Color_t dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
}

//! \brief scale a color
//! \param c the source color
//! \param s the scaling factor
//! \param dst the destination color
static inline void ScaleColor (Color_t c, float s, Color_t dst)
{
    dst[0] = (char) lrint(s * c[0]);
    dst[1] = (char) lrint(s * c[1]);
    dst[2] = (char) lrint(s * c[2]);
    dst[3] = c[3];
}

//! \brief blend 2 colors
//! \param c1 the first color
//! \param c2 the second color
//! \param r the ratio
//! \param dst the destination color
static inline void BlendColor (Color_t c1, Color_t c2, float r, Color_t dst)
{
    dst[0] = (char) lrint(r * c1[0] + (1 - r) * c2[0]);
    dst[1] = (char) lrint(r * c1[1] + (1 - r) * c2[1]);
    dst[2] = (char) lrint(r * c1[2] + (1 - r) * c2[2]);
    dst[3] = (char) lrint(r * c1[3] + (1 - r) * c2[3]);
}

#endif /* !_VECTOR_H_ */
