/*! \file quat.h
 *
 * \author John Reppy
 */

/* CMSC23700 Sample code
 *
 * COPYRIGHT (c) 2010 John Reppy (http://www.cs.uchicago.edu/~jhr)
 * All rights reserved.
 */

#ifndef _QUAT_H_
#define _QUAT_H_

#include <stdbool.h>
#include "vector.h"
#include "matrix.h"

typedef float Quatf_t[4];	//!< single-precision quaternion; the coordinates
				//! are (x, y, z, w)

/*! \brief convert an axis/angle pair to a unit quaternion
 *  \param axis the axis vector
 *  \param theta CCW rotation angle in radians
 *  \param dst the result quaternion;  if the axis is a unit vector,
 *             then the result will be a unit quaternion.
 */
static inline void FromAxisAngle (Vec3f_t axis, float theta, Quatf_t dst)
{
    theta *= 0.5;  // theta/2
    float s = sinf(theta);
    dst[0] = s*axis[0];
    dst[1] = s*axis[1];
    dst[2] = s*axis[2];
    dst[3] = cosf(theta);
}

/*! \brief convert a quaternion to axis angle.
 *  \param q the quaternion
 *  \param axis for returning the axis vector
 *  \param theta for returning the CCW rotation angle in radians
 */
static inline void ToAxisAngle (Quatf_t q, Vec3f_t axis, float *theta)
{
    float w2 = q[3]*q[3];
    if (w2 < (1.0 - EPSILON)) {
	*theta = 2.0 * acosf(q[3]);
	float s = 1.0 / sqrtf(1.0 - w2);
	axis[0] = s * q[0];
	axis[1] = s * q[1];
	axis[2] = s * q[2];
    }
    else {  // return e1
	*theta = 0.0;
	axis[0] = 1.0;
	axis[1] = 0.0;
	axis[2] = 0.0;
    }

}

/*! \brief convert a unit quaternion to a 4x4 rotation matrix in column-major order.
 */
static inline void ToRotMatrix (Quatf_t q, Mat4x4f_t dst)
{
#define M(r,c)		dst[4*(c)+(r)]
    float x2 = 2.0 * q[0] * q[0];
    float xy = 2.0 * q[0] * q[1];
    float xz = 2.0 * q[0] * q[2];
    float xw = 2.0 * q[0] * q[3];
    float y2 = 2.0 * q[1] * q[1];
    float yz = 2.0 * q[1] * q[2];
    float yw = 2.0 * q[1] * q[3];
    float z2 = 2.0 * q[2] * q[2];
    float zw = 2.0 * q[2] * q[3];
    M(0,0) = 1.0 - y2 - z2;
    M(0,1) = xy - zw;
    M(0,2) = xz + yw;
    M(0,3) = 0.0;
    M(1,0) = xy + zw;
    M(1,1) = 1.0 - x2 - z2;
    M(1,2) = yz - xw;
    M(1,3) = 0.0;
    M(2,0) = xz - yw;
    M(2,1) = yz + xw;
    M(2,2) = 1.0 - x2 - y2;
    M(2,3) = 0.0;
    M(3,0) = 0.0;
    M(3,1) = 0.0;
    M(3,2) = 0.0;
    M(3,3) = 1.0;
#undef M
}

/*! \brief quaternion addition
 *  \param q1 a quaternion
 *  \param q2 another quaternion
 *  \param dst the result of adding \a q1 and \a q2.
 */
static inline void AddQuatf (Quatf_t q1, Quatf_t q2, Quatf_t dst)
{
    dst[0] = q1[0] + q2[0];
    dst[1] = q1[1] + q2[1];
    dst[2] = q1[2] + q2[2];
    dst[3] = q1[3] + q2[3];
}

/*! \brief quaternion subtraction
 *  \param q1 a quaternion
 *  \param q2 another quaternion
 *  \param dst the result of subtracting \a q1 from \a q2.
 */
static inline void SubQuatf (Quatf_t q1, Quatf_t q2, Quatf_t dst)
{
    dst[0] = q1[0] - q2[0];
    dst[1] = q1[1] - q2[1];
    dst[2] = q1[2] - q2[2];
    dst[3] = q1[3] - q2[3];
}

/*! \brief quaternion multiplication
 *  \param q1 a quaternion
 *  \param q2 another quaternion
 *  \param dst the result of multiplying \a q1 and \a q2.
 */
static inline void MulQuatf (Quatf_t q1, Quatf_t q2, Quatf_t dst)
{
    dst[0] = q1[3]*q2[0] + q1[0]*q2[3] + q1[1]*q2[2] - q1[2]*q2[1];
    dst[1] = q1[3]*q2[1] - q1[0]*q2[2] + q1[1]*q2[3] + q1[2]*q2[0];
    dst[2] = q1[3]*q2[2] + q1[0]*q2[1] - q1[1]*q2[0] + q1[2]*q2[3];
    dst[3] = q1[3]*q2[3] - q1[0]*q2[0] - q1[1]*q2[1] - q1[2]*q2[2];
}

/*! \brief scale a quaternion by a scalar
 *  \param s the scaling factor
 *  \param q the quaternion
 *  \param dst the result quaternion.
 */
static inline void ScaleQuatf (float s, Quatf_t q, Quatf_t dst)
{
    dst[0] = s * q[0];
    dst[1] = s * q[1];
    dst[2] = s * q[2];
    dst[3] = s * q[3];
}

/*! \brief return the conjugate of a quaternion.
 *  \param q the argument quaternion
 *  \param dst the resulting conjugate of \a q.
 */
static inline void ConjugateQuatf (Quatf_t q, Quatf_t dst)
{
    dst[0] = -q[0];
    dst[1] = -q[1];
    dst[2] = -q[2];
    dst[3] = q[3];
}

/*! \brief return the magnitude of a quaternion squared.
 *  \param q the argument quaternion
 *  \return the magnitude of \a q squared
 */
static inline float QuatMagnitudeSqf (Quatf_t q)
{
    return q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
}

/*! \brief return the magnitude of a quaternion.
 *  \param q the argument quaternion
 *  \return the magnitude of \a q
 */
static inline float QuatMagnitudef (Quatf_t q)
{
    return sqrtf (QuatMagnitudeSqf (q));
}

/*! \brief normalize a quaternion
 *  \param q the quaternion to normalize
 *  \param dst the normalized quaternion
 */
static inline void NormalizeQuatf (Quatf_t q, Quatf_t dst)
{
    float len = QuatMagnitudef(q);
    if (len > EPSILON)
	ScaleQuatf (1.0 / len, q, dst);
    else {
	dst[0] = 0.0;
	dst[1] = 0.0;
	dst[2] = 0.0;
	dst[3] = 1.0;
    }
}

/*! \brief return the multiplicative inverse of a quaternion
 *  \param q the quaternion
 *  \param dst the inverse of \a q.  The result is undefined is the
 *         the inverse doesn't exist.
 *  \return true if the inverse exists, false otherwise.
 */
static inline bool InverseQuatf (Quatf_t q, Quatf_t dst)
{
    float mag2 = QuatMagnitudeSqf (q);

    if (mag2 > EPSILON) {
	ConjugateQuatf (q, dst);
	ScaleQuatf (1.0 / mag2, dst, dst);
	return true;
    }
    else
	return false;

}

/*! \brief multiply a quaternion times a 3D vector (the vector is treated as a
 *         quaternion with a 0 w component).
 *  \param q the quaternion
 *  \param v the vector
 *  \param dst the resulting quaternion
 */
static inline void MulQxV3f (Quatf_t q, Vec3f_t v, Quatf_t dst)
{
    dst[0] = q[3]*v[0] + q[1]*v[2] - q[2]*v[1];
    dst[1] = q[3]*v[1] - q[0]*v[2] + q[2]*v[0];
    dst[2] = q[3]*v[2] + q[0]*v[1] - q[1]*v[0];
    dst[3] = -(q[0]*v[0] + q[1]*v[1] + q[2]*v[2]);
}

/*! \brief rotate a vector by a unit quaternion
 *  \param q the quaternion that defines the rotation
 *  \param v the vector/point to be rotated
 *  \param dst the resulting vector/point
 */
static inline void RotateVecByQuatf (Quatf_t q, Vec3f_t v, Vec3f_t dst)
{
    Quatf_t q1, q2;
    MulQxV3f (q, v, q1);
    ConjugateQuatf (q, q2);
  /* v = (q1 * q2).xyz */
    dst[0] = q1[3]*q2[0] + q1[0]*q2[3] + q1[1]*q2[2] - q1[2]*q2[1];
    dst[1] = q1[3]*q2[1] - q1[0]*q2[2] + q1[1]*q2[3] + q1[2]*q2[0];
    dst[2] = q1[3]*q2[2] + q1[0]*q2[1] - q1[1]*q2[0] + q1[2]*q2[3];

}

/*! \brief linear interpolation between unit quats.
 *  \brief q1 starting quaternion
 *  \param t weight
 *  \param q2 ending quaternion
 *  \param dst result of lerp
 */
static inline void LerpQuatf (Quatf_t q1, float t, Quatf_t q2, Quatf_t dst)
{
    dst[0] = q1[0] + t*(q2[0] - q1[0]);
    dst[1] = q1[1] + t*(q2[1] - q1[1]);
    dst[2] = q1[2] + t*(q2[2] - q1[2]);
    dst[3] = q1[3] + t*(q2[3] - q1[3]);
    NormalizeQuatf (dst, dst);
}

/*! \brief spherical linear interpolation between unit quats.
 *  \brief q1 starting quaternion
 *  \param t weight
 *  \param q2 ending quaternion
 *  \param dst result of slerp
 */
static inline void SlerpQuatf (Quatf_t q1, float t, Quatf_t q2, Quatf_t dst)
{
  // compute the dot product between quats
    float dp = q1[0]*q2[0] + q1[1]*q2[1] + q1[2]*q2[2] + q1[3]*q2[3];

    if (dp > 0.9995) {
      // the quats are close, so use lerp
	LerpQuatf (q1, t, q2, dst);
    }
    else {
      // ensure that -1 <= dp < 1; we know already that dp <= 0.9995
	if (dp < -1.0f) dp = -1.0f;
	float theta = t * acosf(dp);
      // q = normalze (q2 - dp * q1)
	Quatf_t q;
	q[0] = q2[0] - dp*q1[0];
	q[1] = q2[1] - dp*q1[1];
	q[2] = q2[2] - dp*q1[2];
	q[3] = q2[3] - dp*q1[3];
        NormalizeQuatf (dst, dst);
      // dst = cos(theta) * q1 + sin(theta) * q
	float c = cosf(theta);
	float s = sinf(theta);
	dst[0] = c * q1[0] + s * q[0];
	dst[1] = c * q1[1] + s * q[1];
	dst[2] = c * q1[2] + s * q[2];
	dst[3] = c * q1[3] + s * q[3];
    }

}

/*! \brief copy a quaternion
 *  \param src the source quaternion
 *  \param dst the destination quaternion.
 */
static inline void CopyQuatf (Quatf_t src, Quatf_t dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
}

#endif /* !_QUAT_H_ */
