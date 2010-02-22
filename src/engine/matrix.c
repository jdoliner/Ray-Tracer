/*! \file matrix.c
 *
 * \brief Various types and operations for square matrices.
 *
 * \author John Reppy
 *
 * Various functions on 3x3 and 4x4 matrices of floats.  We follow the OpenGL
 * column-major representation.  Also, transformations are postmultiplied as in
 * OpenGL.
 */

/* CMSC23700 Sample code
 *
 * COPYRIGHT (c) 2010 John Reppy (http://www.cs.uchicago.edu/~jhr)
 * All rights reserved.
 */

#include "defs.h"
#include "matrix.h"
#include <stdio.h>

/***** Mat3x3f_t operations *****/

#define I(i,j)	(3*(j-1)+i-1)
#define M(i,j)	m[I(i,j)]
#define D(i,j)	dst[I(i,j)]

extern void IdentityM3f (Mat3x3f_t m)
{
    for (int i = 1;  i <= 3;  i++) {
	for (int j = 1;  j <= 3;  j++) {
	    M(i,j) = (i == j);
	}
    }
}

#define M1(i,j)	m1[I(i,j)]
#define M2(i,j)	m2[I(i,j)]
void MultMM3f (Mat3x3f_t m1, Mat3x3f_t m2, Mat3x3f_t dst)
{
    float t1, t2;		// temporary values to avoid aliasing between m1 and dst

    assert (m2 != dst);

    t1 =  M1(1,1)*M2(1,1) + M1(1,2)*M2(2,1) + M1(1,3)*M2(3,1);
    t2 =  M1(1,1)*M2(1,2) + M1(1,2)*M2(2,2) + M1(1,3)*M2(3,2);
    D(1,3) =  M1(1,1)*M2(1,3) + M1(1,2)*M2(2,3) + M1(1,3)*M2(3,3);
    D(1,1) = t1;
    D(1,2) = t2;

    t1 =  M1(2,1)*M2(1,1) + M1(2,2)*M2(2,1) + M1(2,3)*M2(3,1);
    t2 =  M1(2,1)*M2(1,2) + M1(2,2)*M2(2,2) + M1(2,3)*M2(3,2);
    D(2,3) =  M1(2,1)*M2(1,3) + M1(2,2)*M2(2,3) + M1(2,3)*M2(3,3);
    D(2,1) = t1;
    D(2,2) = t2;

    t1 =  M1(3,1)*M2(1,1) + M1(3,2)*M2(2,1) + M1(3,3)*M2(3,1);
    t2 =  M1(3,1)*M2(1,2) + M1(3,2)*M2(2,2) + M1(3,3)*M2(3,2);
    D(3,3) =  M1(3,1)*M2(1,3) + M1(3,2)*M2(2,3) + M1(3,3)*M2(3,3);
    D(3,1) = t1;
    D(3,2) = t2;

}

#undef I
#undef M
#undef M1
#undef M2
#undef D


/***** Mat4x4f_t operations *****/

#define I(i,j)	(4*(j-1)+i-1)
#define M(i,j)	m[I(i,j)]
#define D(i,j)	dst[I(i,j)]

/* LoadIdentityM4f:
 */
void LoadIdentityM4f (Mat4x4f_t m)
{
    for (int i = 1;  i <= 4;  i++) {
	for (int j = 1;  j <= 4;  j++) {
	    M(i,j) = (i == j) ? 1.0 : 0.0;
	}
    }
}

/* LoadIsoScaleM4f:
 */
void LoadIsoScaleM4f (float s, Mat4x4f_t m)
{
    for (int i = 1;  i <= 4;  i++) {
	for (int j = 1;  j <= 4;  j++) {
	    M(i,j) = (i == j) ? s : 0.0;
	}
    }
    M(4,4) = 1.0;
}

/* LoadScaleM4f:
 */
void LoadScaleM4f (float sx, float sy, float sz, Mat4x4f_t m)
{
    for (int i = 0;  i < 16;  i++) m[i] = 0.0;
    M(1,1) = sx;
    M(2,2) = sy;
    M(3,3) = sz;
    M(4,4) = 1.0;
}

/* LoadTranslateM4f:
 */
void LoadTranslateM4f (float tx, float ty, float tz, Mat4x4f_t m)
{
    LoadIdentityM4f (m);
    M(1,4) = tx;
    M(2,4) = ty;
    M(3,4) = tz;
}

/* IsoScaleM4f:
 *
 * dst = m * S(s)
 */
void IsoScaleM4f (float s, Mat4x4f_t m, Mat4x4f_t dst)
{
    D(1,1) = s * M(1,1);
    D(2,1) = s * M(2,1);
    D(3,1) = s * M(3,1);
    D(4,1) = s * M(4,1);
    D(1,2) = s * M(1,2);
    D(2,2) = s * M(2,2);
    D(3,2) = s * M(3,2);
    D(4,2) = s * M(4,2);
    D(1,3) = s * M(1,3);
    D(2,3) = s * M(2,3);
    D(3,3) = s * M(3,3);
    D(4,3) = s * M(4,3);
    D(1,4) = M(1,4);
    D(2,4) = M(2,4);
    D(3,4) = M(3,4);
    D(4,4) = M(4,4);
}

/* ScaleM4f:
 *
 * dst = m * S(sx,sy,sz)
 */
void ScaleM4f (float sx, float sy, float sz, Mat4x4f_t m, Mat4x4f_t dst)
{
    D(1,1) = sx * M(1,1);
    D(2,1) = sx * M(2,1);
    D(3,1) = sx * M(3,1);
    D(4,1) = sx * M(4,1);
    D(1,2) = sy * M(1,2);
    D(2,2) = sy * M(2,2);
    D(3,2) = sy * M(3,2);
    D(4,2) = sy * M(4,2);
    D(1,3) = sz * M(1,3);
    D(2,3) = sz * M(2,3);
    D(3,3) = sz * M(3,3);
    D(4,3) = sz * M(4,3);
    D(1,4) = M(1,4);
    D(2,4) = M(2,4);
    D(3,4) = M(3,4);
    D(4,4) = M(4,4);
}

/* TranslateM4f:
 *
 * dst = m * T(tx,ty,tz)
 */
void TranslateM4f (float tx, float ty, float tz, Mat4x4f_t m, Mat4x4f_t dst)
{
    D(1,1) = M(1,1);
    D(2,1) = M(2,1);
    D(3,1) = M(3,1);
    D(4,1) = M(4,1);
    D(1,2) = M(1,2);
    D(2,2) = M(2,2);
    D(3,2) = M(3,2);
    D(4,2) = M(4,2);
    D(1,3) = M(1,3);
    D(2,3) = M(2,3);
    D(3,3) = M(3,3);
    D(4,3) = M(4,3);
    D(1,4) = tx*M(1,1) + ty*M(1,2) + tz*M(1,3) + M(1,4);
    D(2,4) = tx*M(2,1) + ty*M(2,2) + tz*M(2,3) + M(2,4);
    D(3,4) = tx*M(3,1) + ty*M(3,2) + tz*M(3,3) + M(3,4);
    D(4,4) = tx*M(4,1) + ty*M(4,2) + tz*M(4,3) + M(4,4);
}

#define M1(i,j)	m1[I(i,j)]
#define M2(i,j)	m2[I(i,j)]

/* MultMM4f
 *
 * dst = m1 * m2
 */
void MultMM4f (Mat4x4f_t m1, Mat4x4f_t m2, Mat4x4f_t dst)
{
    float t1, t2, t3;		// temporary values to avoid aliasing between m1 and dst

    assert (m2 != dst);

    t1 =  M1(1,1)*M2(1,1) + M1(1,2)*M2(2,1) + M1(1,3)*M2(3,1) + M1(1,4)*M2(4,1);
    t2 =  M1(1,1)*M2(1,2) + M1(1,2)*M2(2,2) + M1(1,3)*M2(3,2) + M1(1,4)*M2(4,2);
    t3 =  M1(1,1)*M2(1,3) + M1(1,2)*M2(2,3) + M1(1,3)*M2(3,3) + M1(1,4)*M2(4,3);
    D(1,4) = M1(1,1)*M2(1,4) + M1(1,2)*M2(2,4) + M1(1,3)*M2(3,4) + M1(1,4)*M2(4,4);
    D(1,1) = t1;
    D(1,2) = t2;
    D(1,3) = t3;

    t1 =  M1(2,1)*M2(1,1) + M1(2,2)*M2(2,1) + M1(2,3)*M2(3,1) + M1(2,4)*M2(4,1);
    t2 =  M1(2,1)*M2(1,2) + M1(2,2)*M2(2,2) + M1(2,3)*M2(3,2) + M1(2,4)*M2(4,2);
    t3 =  M1(2,1)*M2(1,3) + M1(2,2)*M2(2,3) + M1(2,3)*M2(3,3) + M1(2,4)*M2(4,3);
    D(2,4) = M1(2,1)*M2(1,4) + M1(2,2)*M2(2,4) + M1(2,3)*M2(3,4) + M1(2,4)*M2(4,4);
    D(2,1) = t1;
    D(2,2) = t2;
    D(2,3) = t3;

    t1 =  M1(3,1)*M2(1,1) + M1(3,2)*M2(2,1) + M1(3,3)*M2(3,1) + M1(3,4)*M2(4,1);
    t2 =  M1(3,1)*M2(1,2) + M1(3,2)*M2(2,2) + M1(3,3)*M2(3,2) + M1(3,4)*M2(4,2);
    t3 =  M1(3,1)*M2(1,3) + M1(3,2)*M2(2,3) + M1(3,3)*M2(3,3) + M1(3,4)*M2(4,3);
    D(3,4) = M1(3,1)*M2(1,4) + M1(3,2)*M2(2,4) + M1(3,3)*M2(3,4) + M1(3,4)*M2(4,4);
    D(3,1) = t1;
    D(3,2) = t2;
    D(3,3) = t3;

    t1 =  M1(4,1)*M2(1,1) + M1(4,2)*M2(2,1) + M1(4,3)*M2(3,1) + M1(4,4)*M2(4,1);
    t2 =  M1(4,1)*M2(1,2) + M1(4,2)*M2(2,2) + M1(4,3)*M2(3,2) + M1(4,4)*M2(4,2);
    t3 =  M1(4,1)*M2(1,3) + M1(4,2)*M2(2,3) + M1(4,3)*M2(3,3) + M1(4,4)*M2(4,3);
    D(4,4) = M1(4,1)*M2(1,4) + M1(4,2)*M2(2,4) + M1(4,3)*M2(3,4) + M1(4,4)*M2(4,4);
    D(4,1) = t1;
    D(4,2) = t2;
    D(4,3) = t3;

}

/* InverseM4f:
 */
bool InverseM4f (Mat4x4f_t m, Mat4x4f_t dst)
{

  // NOTE: we do the computation in double precision to get better results
    double Tbt34C12 = M(3,1)*M(4,2) - M(3,2)*M(4,1);		// 2x2 subdeterminants
    double Tbt34C13 = M(3,1)*M(4,3) - M(3,3)*M(4,1);
    double Tbt34C14 = M(3,1)*M(4,4) - M(3,4)*M(4,1);
    double Tbt34C23 = M(3,2)*M(4,3) - M(3,3)*M(4,2);
    double Tbt34C24 = M(3,2)*M(4,4) - M(3,4)*M(4,2);
    double Tbt34C34 = M(3,3)*M(4,4) - M(3,4)*M(4,3);
    double Tbt24C12 = M(2,1)*M(4,2) - M(2,2)*M(4,1);		// 2x2 subdeterminants
    double Tbt24C13 = M(2,1)*M(4,3) - M(2,3)*M(4,1);
    double Tbt24C14 = M(2,1)*M(4,4) - M(2,4)*M(4,1);
    double Tbt24C23 = M(2,2)*M(4,3) - M(2,3)*M(4,2);
    double Tbt24C24 = M(2,2)*M(4,4) - M(2,4)*M(4,2);
    double Tbt24C34 = M(2,3)*M(4,4) - M(2,4)*M(4,3);
    double Tbt23C12 = M(2,1)*M(3,2) - M(2,2)*M(3,1);		// 2x2 subdeterminants
    double Tbt23C13 = M(2,1)*M(3,3) - M(2,3)*M(3,1);
    double Tbt23C14 = M(2,1)*M(3,4) - M(2,4)*M(3,1);
    double Tbt23C23 = M(2,2)*M(3,3) - M(2,3)*M(3,2);
    double Tbt23C24 = M(2,2)*M(3,4) - M(2,4)*M(3,2);
    double Tbt23C34 = M(2,3)*M(3,4) - M(2,4)*M(3,3);

    double sd11 = M(2,2)*Tbt34C34 - M(2,3)*Tbt34C24 + M(2,4)*Tbt34C23;	// 3x3 subdeterminants
    double sd12 = M(2,1)*Tbt34C34 - M(2,3)*Tbt34C14 + M(2,4)*Tbt34C13;
    double sd13 = M(2,1)*Tbt34C24 - M(2,2)*Tbt34C14 + M(2,4)*Tbt34C12;
    double sd14 = M(2,1)*Tbt34C23 - M(2,2)*Tbt34C13 + M(2,3)*Tbt34C12;
    double sd21 = M(1,2)*Tbt34C34 - M(1,3)*Tbt34C24 + M(1,4)*Tbt34C23;	// 3x3 subdeterminants
    double sd22 = M(1,1)*Tbt34C34 - M(1,3)*Tbt34C14 + M(1,4)*Tbt34C13;
    double sd23 = M(1,1)*Tbt34C24 - M(1,2)*Tbt34C14 + M(1,4)*Tbt34C12;
    double sd24 = M(1,1)*Tbt34C23 - M(1,2)*Tbt34C13 + M(1,3)*Tbt34C12;
    double sd31 = M(1,2)*Tbt24C34 - M(1,3)*Tbt24C24 + M(1,4)*Tbt24C23;	// 3x3 subdeterminants
    double sd32 = M(1,1)*Tbt24C34 - M(1,3)*Tbt24C14 + M(1,4)*Tbt24C13;
    double sd33 = M(1,1)*Tbt24C24 - M(1,2)*Tbt24C14 + M(1,4)*Tbt24C12;
    double sd34 = M(1,1)*Tbt24C23 - M(1,2)*Tbt24C13 + M(1,3)*Tbt24C12;
    double sd41 = M(1,2)*Tbt23C34 - M(1,3)*Tbt23C24 + M(1,4)*Tbt23C23;	// 3x3 subdeterminants
    double sd42 = M(1,1)*Tbt23C34 - M(1,3)*Tbt23C14 + M(1,4)*Tbt23C13;
    double sd43 = M(1,1)*Tbt23C24 - M(1,2)*Tbt23C14 + M(1,4)*Tbt23C12;
    double sd44 = M(1,1)*Tbt23C23 - M(1,2)*Tbt23C13 + M(1,3)*Tbt23C12;

    double det = (M(1,1)*sd11 - M(1,2)*sd12 + M(1,3)*sd13 - M(1,4)*sd14);
    if ((det > -EPSILON) && (det < EPSILON))
	return false;
    double detInv = 1.0 / det;

    D(1,1) = sd11*detInv;
    D(2,1) = -sd12*detInv;
    D(3,1) = sd13*detInv;
    D(4,1) = -sd14*detInv;
    D(1,2) = -sd21*detInv;
    D(2,2) = sd22*detInv;
    D(3,2) = -sd23*detInv;
    D(4,2) = sd24*detInv;
    D(1,3) = sd31*detInv;
    D(2,3) = -sd32*detInv;
    D(3,3) = sd33*detInv;
    D(4,3) = -sd34*detInv;
    D(1,4) = -sd41*detInv;
    D(2,4) = sd42*detInv;
    D(3,4) = -sd43*detInv;
    D(4,4) = sd44*detInv;

    return true;
}

/* PrintM4f:
 */
void PrintM4f (Mat4x4f_t m)
{
    for (int i = 1;  i <= 4;  i++) {
	printf ("| %7f %7f %7f %7f |\n", M(i,1), M(i,2), M(i,3), M(i,4));
    }
}
