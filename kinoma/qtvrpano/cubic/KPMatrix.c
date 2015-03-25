/*
 *     Copyright (C) 2010-2015 Marvell International Ltd.
 *     Copyright (C) 2002-2010 Kinoma, Inc.
 *
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */



#ifndef PRAGMA_MARK_SUPPORTED
	#if defined(macintosh) || defined(__MWERKS__)
		#define PRAGMA_MARK_SUPPORTED 1
	#else /* !PRAGMA_MARK_SUPPORTED */
		#define PRAGMA_MARK_SUPPORTED 0
	#endif /* !PRAGMA_MARK_SUPPORTED */
#endif /* PRAGMA_MARK_SUPPORTED */


#ifndef MINIMAL_CUBIC
	#define MINIMAL_CUBIC 0	/* This should really be set on the command line instead */
#endif /* MINIMAL_CUBIC */


/********************************************************************************
 ********************************************************************************
 ********************************************************************************
 *****	The following should be identical for single and double precision	*****
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************/


#define MAXDIM	8					/* The maximum dimension of a matrix */

#define QW		0					/* Indices appropriate for WXYZ quaternions */
#define QX		1
#define QY		2
#define	QZ		3

struct M33		{ FLOAT m[3][3]; };	/* Makes it easier to access 3x3 matrices */
typedef FLOAT	vec3[3];			/* Makes it easier to access 3x3 matrices */


#ifndef   NULL
	#define  NULL		0
#endif /* NULL */


#define KPName3(a,b,c)				_KPName3_aux(a,b,c)
#define _KPName3_aux(a,b,c)			a##b##c

#if PRAGMA_MARK_SUPPORTED
#pragma mark KPZeroVector
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC
/********************************************************************************
 * KPZeroVector
 ********************************************************************************/

void
KPName3(KP,FLTPREC,ZeroVector)(FLOAT *v, long n)
{
	while (n--)
		*v++ = 0;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPCopyVector
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPCopyVector
 ********************************************************************************/

void
KPName3(KP,FLTPREC,CopyVector)(const FLOAT *fr, FLOAT *to, long n)
{
	while (n--)
		*to++ = *fr++;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPScaleVector
#endif /* PRAGMA_MARK_SUPPORTED */
/********************************************************************************
 * KPScaleVector
 ********************************************************************************/

void
KPName3(KP,FLTPREC,ScaleVector)(FLOAT s, const FLOAT *fr, FLOAT *to, long n)
{
	while (n--)
		*to++ = s * *fr++;
}


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPNormVector
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC
/********************************************************************************
 * KPNormVector
 ********************************************************************************/

FLOAT
KPName3(KP,FLTPREC,NormVector)(register const FLOAT *v, register long n)
{
	register double	mag;

	for (mag = 0.0; n--; ) {
		register double x = *v++;
		mag += x * x;
	}

	mag = sqrt(mag);
	return (FLOAT)mag;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPNormalizeVector
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPNormalizeVector
 ********************************************************************************/

FLOAT
KPName3(KP,FLTPREC,NormalizeVector)(const FLOAT *fr, FLOAT *to, long n)
{
	register double	mag;
	long			i;

	for (i = n, mag = 0.0; i--; ) {
		register double x = *fr++;
		mag += x * x;
	}
	fr -= n;

	if (mag != 0) {
		register FLOAT iMag = (FLOAT)(1.0 / (mag = sqrt(mag)));
		for (i = n; i--; )
			*to++ = *fr++ * iMag;
	}
	else {
		for (i = n; i--; )
			*to++ = 0;
	}

	return (FLOAT)mag;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPDotProductVector
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPNormalizeVector
 ********************************************************************************/

FLOAT
KPName3(KP,FLTPREC,DotProductVector)(register const FLOAT *v0, register const FLOAT *v1, register long n)
{
	double dot;

	for (dot = 0; n--; )
		dot += *v0++ * *v1++;

	return (FLOAT)dot;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPCrossProductVector3D
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPNormalizeVector
 ********************************************************************************/

void
KPName3(KP,FLTPREC,CrossProductVector3D)(const FLOAT *L, const FLOAT *R, FLOAT *P)
{
	P[0] = (FLOAT)((double)L[1] * (double)R[2] - (double)L[2] * (double)R[1]);
	P[1] = (FLOAT)((double)L[2] * (double)R[0] - (double)L[0] * (double)R[2]);
	P[2] = (FLOAT)((double)L[0] * (double)R[1] - (double)L[1] * (double)R[0]);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPIdentityMatrix
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPIdentityMatrix
 ********************************************************************************/

void
KPName3(KP,FLTPREC,IdentityMatrix)(FLOAT *M, long nRows, long nCols)
{
	register FLOAT	*p, val;
	register long	i;

	for (i = nRows * nCols, val = 0, p = M; i--; )
		 *p++ = val;

	i = (nRows <= nCols ? nRows : nCols);
	nCols++;								/* Distance between one 1 and the next */
	for (p = M, val = 1; i--; p += nCols)
		*p = val;							/* Scatter the 1's along the diagonal */
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPLinearTransform
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPLinearTransform
 * Linear transformations, for transforming vectors and matrices.
 * This works for row vectors and column vectors alike.
 *	L[nRows][lCol]	- left matrix
 *	R[lCol][rCol]	- right matrix
 *	P[nRows][rCol]	- product matrix
 *
 * Examples:
 * v[3] * M[3][3] -> w[3] :			KPLinearTransform(&v[0], &M[0][0], &w[0], 1, 3, 3);
 * M[3][3] * v[3] -> w[3] :			KPLinearTransform(&M[0][0], &v[0], &w[0], 3, 3, 1);
 * M[4][4] * N[4][4] -> P[4][4]:	KPLinearTransform(&M[0][0], &N[0][0], &P[0][0], 4, 4, 4);
 * v[4] * M[4][3] -> w[3]:			KPLinearTransform(&v[0], &M[0][0], &w[0], 1, 4, 3);
 * v[3] tensor w[3] -> T[3][3]:		KPLinearTransform(&v[0], &w[0], T[3][3], 3, 1, 3);
 *
 * This does not work in-place.
 ********************************************************************************/

void
KPName3(KP,FLTPREC,LinearTransform)(
	const    FLOAT	*L,		/* The left matrix */
	const    FLOAT	*R,		/* The right matrix */
	register FLOAT	*P,		/* The resultant matrix */
	long			nRows,	/* The number of rows of the left and resultant matrices */
	long			lCols,	/* The number of columns in the left matrix */
	long			rCols	/* The number of columns in the resultant matrix */
)
{
	register const FLOAT	*lp;					/* Left matrix pointer for dot product */
	register const char		*rp;					/* Right matrix pointer for dot product */
	register long			k;						/* Loop counter */
	register double			sum;					/* Extended precision for intermediate results */
	register long			j, i;					/* Loop counters */
	const char				*lb;
	register long			rRowBytes	= rCols * sizeof(FLOAT);
	register long			lRowBytes	= lCols * sizeof(FLOAT);

	for (i = nRows, lb = (const char*)L; i--; lb += lRowBytes) {	/* Each row in L */
		for (j = 0; j < rCols; j++) {								/* Each column in R */
			lp = (const FLOAT *)lb;									/* Left of ith row of L */
			rp = (const char *)(R + j);								/* Top of jth column of R */
			sum = 0;
			for (k = lCols; k--; rp += rRowBytes)
				sum += *lp++ * (*((const FLOAT*)rp));				/* *P += L[i'][k'] * R[k'][j] */
			*P++ = (FLOAT)sum;
		}
	}
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPAffineTransform
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPAffineTransform
 * Affine transformations, for transforming points in row vector form.
 *	L[nRows][lCol]			- input
 *	R[lCol+1][rCol]	- matrix
 *	P[nRows][rCol]			- output
 *
 * Examples:
 * p[3] * M[4][3] -> q[3]:	MLAffineTransform(&p[0], &M[0][0], &q[0], 1, 3, 3);
 ********************************************************************************/

void
KPName3(KP,FLTPREC,AffineTransform)(
	const    FLOAT	*L,		/* The left matrix */
	const    FLOAT	*R,		/* The right matrix */
	register FLOAT	*P,		/* The product matrix */
	long			nRows,	/* The number of rows of the left and resultant matrices */
	long			lCols,	/* The number columns in the left and rows in the right matrix */
	long			rCols	/* The number of columns in the resultant matrix */
)
{
	register const FLOAT	*lp;							/* Left matrix pointer for dot product */
	register const char		*rp;							/* Right matrix pointer for dot product */
	register long			k;								/* Loop counter */
	register double			sum;							/* Extended precision for intermediate results */
	register long			j, i;							/* Loop counters */
	register long			rRowBytes	= rCols * sizeof(FLOAT);
	register long			lRowBytes	= lCols * sizeof(FLOAT);
	const char				*lb			= (const char*)L;

	for (i = nRows; i--; lb += lRowBytes) {					/* Each row in L */
		for (j = 0; j < rCols; j++) {						/* Each column in R */
			lp = (const FLOAT *)lb;							/* Left of ith row of L */
			rp = (const char *)(R + j);						/* Top of jth column of R */
			sum = 0;
			for (k = lCols; k--; rp += rRowBytes)
				sum += *lp++ * (*((const FLOAT*)rp));		/* *P += L[i'][k'] * R[k'][j] */
			*P++ = (FLOAT)(sum + (*((const FLOAT*)rp)));	/* Add translation at the end */
		}
	}
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPTransposeSquareMatrixInPlace
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPTransposeSquareMatrixInPlace
 *		This only works for square matrices.
 ********************************************************************************/

void
KPName3(KP,FLTPREC,TransposeSquareMatrixInPlace)(FLOAT *M, long n)
{
	register long	i, j;
	register FLOAT	*p, *q, t;

	for (i = n; --i; M += n + 1) {
		for (j = i, p = M + 1, q = M + n; j--; p++, q += n) {
			t = *p;
			*p = *q;
			*q = t;
		}
	}
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPLUDecompose
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC
/********************************************************************************
 * KPLUDecompose() decomposes the coefficient matrix A into upper and lower
 * triangular matrices, the composite being the LU matrix.
 * This is then followed by multiple applications of KPLUSolve(),
 * to solve several problems with the same system matrix.
 *
 * 1 is returned if the matrix is non-singular and the decomposition was successful;
 * 0 is returned if the matrix is singular and the decomposition failed.
 ********************************************************************************/

#define luel(i, j)  lu[(i)*n+(j)]
#define ael(i, j)	a[(i)*n+(j)]
#define A(i,j)		a[(i)*n+(j)]

long
KPName3(KP,FLTPREC,LUDecompose)(
	register const FLOAT	*a,		/* the (n x n) coefficient matrix */
	register double			*lu, 	/* the (n x n) lu matrix augmented by an (n x 1) pivot sequence */
	register long			n		/* the order of the matrix */
)
{
	register long	i, j, k;
	long			pivotindex;
	double			pivot, biggest, mult, tempf;
	register long	*ps;
	double			scales[MAXDIM];

	ps = (long *)(&lu[n*n]); /* Memory for ps[] comes after LU[][] */

	for (i = 0; i < n; i++) {	/* For each row */
		/* Find the largest element in each row for row equilibration */
		biggest = 0.0;
		for (j = 0; j < n; j++)
			if (biggest < (tempf = fabs(luel(i,j) = ael(j,i)))) /* A transposed for row vectors */
				biggest = tempf;
		if (biggest != 0.0)
			scales[i] = 1.0 / biggest;
		else {
			scales[i] = 0.0;
			return(0);	/* Zero row: singular matrix */
		}

		ps[i] = i;		/* Initialize pivot sequence */
	}

	for (k = 0; k < n-1; k++) { /* For each column */
		/* Find the largest element in each column to pivot around */
		biggest = 0.0;
		pivotindex = k;
		for (i = k; i < n; i++) {
			if (biggest < (tempf = fabs(luel(ps[i],k)) * scales[ps[i]])) {
				biggest = tempf;
				pivotindex = i;
			}
		}
		if (biggest == 0.0)
			return(0);	/* Zero column: singular matrix */
		if (pivotindex != k) {	/* Update pivot sequence */
			j = ps[k];
			ps[k] = ps[pivotindex];
			ps[pivotindex] = j;
		}

		/* Pivot, eliminating an extra variable each time */
		pivot = luel(ps[k],k);
		for (i = k+1; i < n; i++) {
			luel(ps[i],k) = mult = luel(ps[i],k) / pivot;
			if (mult != 0.0) {
				for (j = k+1; j < n; j++)
					luel(ps[i],j) -= mult * luel(ps[k],j);
			}
		}
	}
	return(luel(ps[n-1],n-1) != 0.0);	/* 0 if singular, 1 if not */
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPLUSolve
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC
/********************************************************************************
 * KPLUSolve() solves the linear equation (xA = b) after the matrix A has
 * been decomposed with KPLUDecompose() into the lower and upper triangular
 * matrices L and U, giving the equivalent equation (xUL = b).
 ********************************************************************************/

void
KPName3(KP,FLTPREC,LUSolve)(
	register const double	*lu,	/* the decomposed LU matrix */
	register const FLOAT	*b,		/* the constant vector */
	register FLOAT			*x,		/* the solution vector */
	register long			n		/* the order of the equation */
)
{
	register long		i, j;
	double				dot;
	register const long	*ps;

	ps = (const long *)(&lu[n*n]); /* Memory for ps[] comes after LU[][] */

	/* Vector reduction using U triangular matrix */
	for (i = 0; i < n; i++) {
		dot = 0.0;
		for (j = 0; j < i; j++)
			dot += luel(ps[i],j) * x[j];
		x[i] = (FLOAT)(b[ps[i]] - dot);
	}

	/* Back substitution, in L triangular matrix */
	for (i = n-1; i >= 0; i--) {
		dot = 0.0;
		for (j = i+1; j < n; j++)
			dot += luel(ps[i],j) * x[j];
		x[i] = (FLOAT)((x[i] - dot) / luel(ps[i],i));
	}
}

#undef luel
#undef ael
#undef A
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPInvertMatrix
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC
/********************************************************************************
 * KPInvertMatrix()
 *	Inverts square matrices
 *	With tall matrices, invert upper part and transform the bottom
 *	rows as would be expected if embedded into a larger matrix.
 *	Undefined for wide matrices.
 * M^(-1) --> Minv
 * Works in-place.
 *
 * 1 is returned if the matrix was non-singular and the inversion was successful;
 * 0 is returned if the matrix was singular and the inversion failed.
 ********************************************************************************/

long
KPName3(KP,FLTPREC,InvertMatrix)(const FLOAT *M, long nRows, register long nCols, FLOAT *Minv)
{
	FLOAT			*m;
	long			tallerBy = nRows - nCols;				/* Excess of rows over columns */
	register long	j, i;
	FLOAT			b[MAXDIM];
	double			lu[MAXDIM*MAXDIM+MAXDIM];

	/* Decompose matrix into L and U triangular matrices */
	if ((tallerBy < 0) || (KPName3(KP,FLTPREC,LUDecompose)(M, lu, nCols) == 0)) {
		return(0);		/* Singular */
	}

	/* Invert matrix by solving nCols simultaneous equations nCols times */
	for (i = 0, m = Minv; i < nCols; i++, m += nCols) {
		for(j = 0; j < nCols; j++)
			b[j] = 0;
		b[i] = 1;

		KPName3(KP,FLTPREC,LUSolve)(lu, b, m, nCols);							/* Into a row of m */
	}

	/* Special post-processing for affine transformations (e.g. 4x3) */
	if (tallerBy) {											/* Affine transformation */
		register FLOAT *t = Minv+nCols*nCols;				/* Translation vector */
		m = Minv;											/* Reset m */
		KPName3(KP,FLTPREC,LinearTransform)(t, m, t, tallerBy, nCols, nCols);	/* Invert translation */
		for (j = tallerBy * nCols; nCols--; t++)
			*t = -*t;										/* Negate translation vector */
	}

	return(1);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPNormMatrix
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC
/********************************************************************************
 * KPNormMatrix
 * L-infinity norm (induced by ROW vectors) of the largest square submatrix of the given matrix.
 ********************************************************************************/

FLOAT
KPName3(KP,FLTPREC,NormMatrix)(register const FLOAT *M, long height, register long width)
{
	register long			i;
	long					j;
	register const FLOAT	*m;
	register double			sum;
	long					subsquare			= (width < height) ? width : height;
	register double			max					= 0;

	for (j = subsquare, m = M; j--; m = ++M) {
		for (i = subsquare, sum = 0; i--; m += width) {
			#if !USE_SINGLE_PRECISION_TRANSCENDENTALS
				sum += fabs(*m);
			#else /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
				sum += fabsf(*m);
			#endif /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
		}
		if (max < sum)
			max = sum;
	}

	return((FLOAT)max);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPDeterminantMatrix
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPDeterminantMatrix() evaluates a determinant by triangularization with
 * searching for pivot in row and with scaling of the rows of the matrix
 * before triangularization.
 ********************************************************************************/

#define A(i,j) b[(n*(i))+(j)]

FLOAT
KPName3(KP,FLTPREC,DeterminantMatrix)(register const FLOAT *a, register long n)
{
	FLOAT			product;
	register long	i, j, r, s;
	FLOAT			mult[MAXDIM], b[MAXDIM*MAXDIM];
	FLOAT			temp, mx;

	/* Copy matrix to working storage */
	{
		register FLOAT *p = b;
		register const FLOAT *q = a;
		for (i = n*n; i--; )
			*p++ = *q++;
	}

	/* Equilibration of rows */
	for (i = n; i--; ) {
		mx = 0;
		for (j = n; j--; )
			if (mx < (temp =
				#if !USE_SINGLE_PRECISION_TRANSCENDENTALS
					(FLOAT)fabs(A(i,j))
				#else /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
					fabsf(A(i,j))
				#endif /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
			))
				mx = temp;
		if (mx == 0)
			return(0);			/* Singular matrix */
		mult[i] = mx;			/* = base^ex for exact scaling */
		if (mx != 1)
			for (j = n; j--; )
				A(i,j) /= mx;	/* Use scalb() or ldexp() for speed & accuracy */
	}

	product = 1;
	for (r = 0; r < n-1; r++) {
		s = r;
		#if !USE_SINGLE_PRECISION_TRANSCENDENTALS
			mx = (FLOAT)fabs(A(r,r));
		#else /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
			mx = fabsf(A(r,r));
		#endif /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
		for (j = r+1; j < n; j++) {
			if (mx < (temp =
				#if !USE_SINGLE_PRECISION_TRANSCENDENTALS
					(FLOAT)fabs(A(r,j))
				#else /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
					fabsf(A(r,j))
				#endif /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
			)) {
				mx = temp;
				s = j;
			}
		}
		if (mx == 0)
			return(0);
		if (s != r) {
			product = -product;
			for (i = r; i < n; i++) {
				temp = A(i,r);
				A(i,r) = A(i,s);
				A(i,s) = temp;
			}
		}
		product *= A(r,r);	/* Be on guard for overflow or underflow here */
		for (i = r+1; i < n; i++) {
			temp = A(i,r) / A(r,r);
			for (j = r+1; j < n; j++)
				A(i,j) -= A(r,j) * temp;
		}
	}
	temp = product * A(n-1,n-1);
	for (r = 0; r < n; r++)
		temp *= mult[r];	/* Again danger of overflow or underflow */
	return(temp);
}
#undef A
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark -
#endif /* PRAGMA_MARK_SUPPORTED */
/********************************************************************************
 ********************************************************************************
 ********************************************************************************
 *****						3x3 Matrix Specializations						*****
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************/


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPAdjointMatrix3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || defined(DOUBLE_PRECISION)
/********************************************************************************
 *  KPAdjointMatrix3x3
 * Adjoint(M) --> out
 * IN PLACE SUPPORTED
 ********************************************************************************/

void
KPName3(KP,FLTPREC,AdjointMatrix3x3)(const FLOAT *M, FLOAT *out)
{
	register vec3	*m, *a;
	FLOAT			tmp[3][3];

	if (out == M) {
		*((struct M33*)(void*)(&tmp[0][0])) = *((struct M33*)(void*)(&M[0]));	/* Copy matrix to tmp */
		m = tmp;
	}
	else {
		m = (vec3*)M;
	}

	a = (vec3*)out;

	a[0][0] = (FLOAT)( (double) m[1][1] * m[2][2] - (double) m[1][2] * m[2][1]);
	a[0][1] = (FLOAT)(-(double) m[0][1] * m[2][2] + (double) m[0][2] * m[2][1]);
	a[0][2] = (FLOAT)( (double) m[0][1] * m[1][2] - (double) m[0][2] * m[1][1]);
	a[1][0] = (FLOAT)(-(double) m[1][0] * m[2][2] + (double) m[1][2] * m[2][0]);
	a[1][1] = (FLOAT)( (double) m[0][0] * m[2][2] - (double) m[0][2] * m[2][0]);
	a[1][2] = (FLOAT)(-(double) m[0][0] * m[1][2] + (double) m[0][2] * m[1][0]);
	a[2][0] = (FLOAT)( (double) m[1][0] * m[2][1] - (double) m[1][1] * m[2][0]);
	a[2][1] = (FLOAT)(-(double) m[0][0] * m[2][1] + (double) m[0][1] * m[2][0]);
	a[2][2] = (FLOAT)( (double) m[0][0] * m[1][1] - (double) m[0][1] * m[1][0]);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPSetRotationX3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 *  KPSetRotationX3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,SetRotationX3x3)(FLOAT rad, FLOAT *M)
{
	register vec3* m = (vec3*)M;
	#if !USE_SINGLE_PRECISION_TRANSCENDENTALS
		FLOAT s = (FLOAT)sin(rad);	FLOAT c = (FLOAT)cos(rad);
	#else /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
		FLOAT s = sinf(rad);		FLOAT c = cosf(rad);
	#endif /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
	m[0][0] = 1;	m[0][1] = 0;	m[0][2] = 0;
	m[1][0] = 0;	m[1][1] = c;	m[1][2] = s;
	m[2][0] = 0;	m[2][1] = -s;	m[2][2] = c;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPSetRotationY3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 *  KPSetRotationY3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,SetRotationY3x3)(FLOAT rad, FLOAT *M)
{
	register vec3* m = (vec3*)M;
	#if !USE_SINGLE_PRECISION_TRANSCENDENTALS
		FLOAT s = (FLOAT)sin(rad);	FLOAT c = (FLOAT)cos(rad);
	#else /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
		FLOAT s = sinf(rad);		FLOAT c = cosf(rad);
	#endif /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
	m[0][0] = c;	m[0][1] = 0;	m[0][2] = -s;
	m[1][0] = 0;	m[1][1] = 1;	m[1][2] = 0;
	m[2][0] = s;	m[2][1] = 0;	m[2][2] = c;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPSetRotationZ3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 *  KPSetRotationZ3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,SetRotationZ3x3)(FLOAT rad, FLOAT *M)
{
	register vec3* m = (vec3*)M;
	#if !USE_SINGLE_PRECISION_TRANSCENDENTALS
		FLOAT s = (FLOAT)sin(rad);	FLOAT c = (FLOAT)cos(rad);
	#else /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
		FLOAT s = sinf(rad);		FLOAT c = cosf(rad);
	#endif /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
	m[0][0] = c;	m[0][1] = s;	m[0][2] = 0;
	m[1][0] = -s;	m[1][1] = c;	m[1][2] = 0;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = 1;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPSetRotationZAboutCenter3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 *  KPSetRotationZAboutCenter3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,SetRotationZAboutCenter3x3)(FLOAT rad, const FLOAT *center, FLOAT *M)
{
	register vec3* m = (vec3*)M;
	#if !USE_SINGLE_PRECISION_TRANSCENDENTALS
		FLOAT s = (FLOAT)sin(rad);	FLOAT c = (FLOAT)cos(rad);
	#else /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
		FLOAT s = sinf(rad);		FLOAT c = cosf(rad);
	#endif /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
	FLOAT v = 1 - c;
	m[0][0] = c;	m[0][1] = s;	m[0][2] = 0;
	m[1][0] = -s;	m[1][1] = c;	m[1][2] = 0;
	m[2][0] = center[0] * v + center[1] * s;	m[2][1] = center[1] * v - center[0] * s;	m[2][2] = 1;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPSetScaleRotationZFromCenterToCenter3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 *  KPSetScaleRotationZFromCenterToCenter3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,SetScaleRotationZFromCenterToCenter3x3)(
	FLOAT		scale,		/* Isotropic scale factor */
	FLOAT		radians,	/* Rotation angle in radians */
	const FLOAT	*frCenter,	/* Rotate the image about this center */
	const FLOAT *toCenter,	/* Translate the frCenter to the toCenter */
	FLOAT		*M			/* The resultant matrix */
)
{
	register vec3* m = (vec3*)M;
	#if !USE_SINGLE_PRECISION_TRANSCENDENTALS
		FLOAT sk = (FLOAT)sin(radians) * scale;	FLOAT ck = (FLOAT)cos(radians) * scale;
	#else /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
		FLOAT sk = sinf(radians) * scale;		FLOAT ck = cosf(radians) * scale;
	#endif /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
	m[0][0] = ck;	m[0][1] = sk;	m[0][2] = 0;
	m[1][0] = -sk;	m[1][1] = ck;	m[1][2] = 0;
	m[2][0] = toCenter[0] - frCenter[0] * ck + frCenter[1] * sk;
	m[2][1] = toCenter[1] - frCenter[1] * ck - frCenter[0] * sk;
	m[2][2] = 1;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPSetRotationPanTiltRoll3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPSetRotationPanTiltRoll3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,SetRotationPanTiltRoll3x3)(FLOAT pan, FLOAT tilt, FLOAT roll, FLOAT *M)
{
	FLOAT P[3][3], T[3][3], R[3][3], Q[3][3];

	KPName3(KP,FLTPREC,SetRotationY3x3)(pan,  P[0]);
	KPName3(KP,FLTPREC,SetRotationX3x3)(tilt, T[0]);
	KPName3(KP,FLTPREC,SetRotationZ3x3)(roll, R[0]);

	KPName3(KP,FLTPREC,LinearTransform)(R[0], T[0], Q[0], 3, 3, 3);
	KPName3(KP,FLTPREC,LinearTransform)(Q[0], P[0], M,    3, 3, 3);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPSetRotationPanTilt3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPSetRotationPanTilt3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,SetRotationPanTilt3x3)(FLOAT pan, FLOAT tilt, FLOAT *M)
{
	FLOAT P[3][3], T[3][3];

	KPName3(KP,FLTPREC,SetRotationY3x3)(pan,  P[0]);
	KPName3(KP,FLTPREC,SetRotationX3x3)(tilt, T[0]);

	KPName3(KP,FLTPREC,LinearTransform)(T[0], P[0], M,    3, 3, 3);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPSetRotationAxisSineCosine3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPSetRotationAxisSineCosine3x3
 *
 * Modification of Michael Pique's formula in
 * Graphics Gems Vol. 1.  Andrew Glassner, Ed.  Addison-Wesley.
 *
 * The axis is assumed to be normalized.
 ********************************************************************************/

void
KPName3(KP,FLTPREC,SetRotationAxisSineCosine3x3)(
	register const FLOAT	*a,	/* axis of rotation */
	register FLOAT			s,	/* sine */
	register FLOAT			c,	/* cosine */
	register FLOAT			*M	/* 3x3 matrix */
)
{
	register FLOAT t;			/* versine */
	register FLOAT q1, q2;

	t = 1 - c;

	/* Diagonal terms */
	M[0*3+0] = t * a[0] * a[0] + c;
	M[1*3+1] = t * a[1] * a[1] + c;
	M[2*3+2] = t * a[2] * a[2] + c;

	/* Skew terms */
	q1 = t * a[0] * a[1];
	q2 = s * a[2];
	M[0*3+1] = q1 + q2;
	M[1*3+0] = q1 - q2;

	q1 = t * a[0] * a[2];
	q2 = s * a[1];
	M[0*3+2] = q1 - q2;
	M[2*3+0] = q1 + q2;

	q1 = t * a[1] * a[2];
	q2 = s * a[0];
	M[1*3+2] = q1 + q2;
	M[2*3+1] = q1 - q2;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPAxisAngleToMatrix3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPAxisAngleToMatrix3x3
 *
 * Set matrix to rotation about an axis by the given angle.
 *
 * The axis is assumed to be normalized.
 ********************************************************************************/

void
KPName3(KP,FLTPREC,AxisAngleToMatrix3x3)(const FLOAT *a, FLOAT radians, FLOAT *M)
{
	#if !USE_SINGLE_PRECISION_TRANSCENDENTALS
		KPName3(KP,FLTPREC,SetRotationAxisSineCosine3x3)(a, (FLOAT)sin(radians), (FLOAT)cos(radians), M);
	#else /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
		KPName3(KP,FLTPREC,SetRotationAxisSineCosine3x3)(a, sinf(radians), cosf(radians), M);
	#endif /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPQuaternionWXYZToMatrix3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPQuaternionWXYZToMatrix3x3
 *	This assumes that the quaternion is WXYZ and normalized,
 *	and the matrix is desired to be suitable for transforming row vectors.
 ********************************************************************************/

void
KPName3(KP,FLTPREC,QuaternionWXYZToMatrix3x3)(const FLOAT *q, FLOAT *M)
{
	register vec3	*R			= (vec3*)M;
	double			a, b, c;

	/* Diagonals */
	a = q[QX]; a *= a;
	b = q[QY]; b *= b;
	c = q[QZ]; c *= c;
	R[0][0] = (FLOAT)(1 - 2 * (b + c));
	R[1][1] = (FLOAT)(1 - 2 * (a + c));
	R[2][2] = (FLOAT)(1 - 2 * (a + b));

	/* Skew terms */
	a = (double)q[QX] * (double)q[QY];
	b = (double)q[QW] * (double)q[QZ];
	R[0][1] = (FLOAT)(2 * (a + b));
	R[1][0] = (FLOAT)(2 * (a - b));

	a = (double)q[QY] * (double)q[QZ];
	b = (double)q[QW] * (double)q[QX];
	R[1][2] = (FLOAT)(2 * (a + b));
	R[2][1] = (FLOAT)(2 * (a - b));

	a = (double)q[QX] * (double)q[QZ];
	b = (double)q[QW] * (double)q[QY];
	R[2][0] = (FLOAT)(2 * (a + b));
	R[0][2] = (FLOAT)(2 * (a - b));
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark -
#endif /* PRAGMA_MARK_SUPPORTED */
/********************************************************************************
 ********************************************************************************
 ********************************************************************************
 *****				3x3 Projection and Immersion Matrices					*****
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************/



#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * ComputeProjectionProjection
 *		3x3 matrix to project a 3D image to 2D
 ********************************************************************************/

static void
ComputeProjectionProjection(
	long	w,		/* Width */
	long	h,		/* Height */
	FLOAT	f,		/* Distance to the image, in the same units used for the height */
	FLOAT	cx,		/* Center of image, relative to center of projection */
	FLOAT	cy,		/* Center of image, relative to center of projection */
	FLOAT	a,		/* Aspect ratio of image pixels: a<1 for tall pixels, a>1 for wide pixels */
	FLOAT	k,		/* Skew of x on each scanline */
	FLOAT	*M		/* Projection matrix, from 3D to 2D */
)
{
	FLOAT	ai, fai;

	ai  = 1 / a;
	fai = f * ai;
	cx  = (w - 1) * (FLOAT)(0.5) - cx;
	cy  = (h - 1) * (FLOAT)(0.5) + cy;

	M[0*3+0] = -fai;	M[0*3+1] = 0;		M[0*3+2] = 0;
	M[1*3+0] = -fai*k;	M[1*3+1] = f;		M[1*3+2] = 0;
	M[2*3+0] = cx;		M[2*3+1] = cy;		M[2*3+2] = 1;
}
#endif /* MINIMAL_CUBIC */


#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * ComputeImmersionProjection
 *		Immerse a 2D image into 3D
 ********************************************************************************/

static void
ComputeImmersionProjection(
	long	w,		/* Width */
	long	h,		/* Height */
	FLOAT	f,		/* Distance to the image */
	FLOAT	cx,		/* Center of image, relative to center of projection */
	FLOAT	cy,		/* Center of image, relative to center of projection */
	FLOAT	a,		/* Aspect ratio of image pixels: a<1 for tall pixels, a>1 for wide pixels */
	FLOAT	k,		/* Skew of x on each scanline */
	FLOAT	*M		/* Immersion matrix, from 2D to 3D */
)
{
	FLOAT fi, afi;
	fi  = 1 / f;
	afi = a * fi;
	cx  = ((w - 1) * (FLOAT)(0.5) - cx) * afi;
	cy  = ((h - 1) * (FLOAT)(0.5) + cy) *  fi;

	M[0*3+0] = -afi;		M[0*3+1] = 0;		M[0*3+2] = 0;
	M[1*3+0] = -k*fi;		M[1*3+1] = fi;		M[1*3+2] = 0;
	M[2*3+0] = cx+k*cy;		M[2*3+1] = -cy;		M[2*3+2] = 1;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPImmerseUsingMatrix3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPImmerseUsingMatrix3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,ImmerseUsingMatrix3x3)(
	long			width,			/* Width of the image */
	long			height,			/* Height of the image */
	const FLOAT		*R,				/* Rotation matrix */
	FLOAT			focalLength,	/* Focal length of the image plane, in pixels */
	const FLOAT		*center,		/* Center of image, relative to center of projection (can be NULL) */
	const FLOAT		*aspectSkew,	/* Aspect ratio and skew (can be NULL) */
	FLOAT			*M				/* The resulting matrix */
)
{
	FLOAT	P[3][3];
	FLOAT	cx, cy, a, k;

	/* Choose default values for center, aspect ratio and skew if not specified */
	if (center != NULL)		{	cx = center[0];		cy = center[1];		}
	else					{	cx = 0;				cy = 0;				}
	if (aspectSkew != NULL)	{	a  = aspectSkew[0];	k  = aspectSkew[1];	}
	else					{	a  = 1;				k  = 0;				}

	ComputeImmersionProjection(width, height, focalLength, cx, cy, a, k, P[0]);
	KPName3(KP,FLTPREC,LinearTransform)(P[0], R, M, 3, 3, 3);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPProjectUsingMatrix3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPProjectUsingMatrix3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,ProjectUsingMatrix3x3)(
	long			width,			/* Width of the image */
	long			height,			/* Height of the image */
	const FLOAT		*R,				/* Rotation matrix */
	FLOAT			focalLength,	/* Focal length of the image plane, in pixels */
	const FLOAT		*center,		/* Center of image, relative to center of projection (can be NULL) */
	const FLOAT		*aspectSkew,	/* Aspect ratio and skew (can be NULL) */
	FLOAT			*M				/* The resulting matrix */
)
{
	FLOAT	P[3][3];
	FLOAT	cx, cy, a, k;

	/* Choose default values for center, aspect ratio and skew if not specified */
	if (center != NULL)		{	cx = center[0];		cy = center[1];		}
	else					{	cx = 0;				cy = 0;				}
	if (aspectSkew != NULL)	{	a  = aspectSkew[0];	k  = aspectSkew[1];	}
	else					{	a  = 1;				k  = 0;				}

	ComputeProjectionProjection(width, height, focalLength, cx, cy, a, k, P[0]);
	KPName3(KP,FLTPREC,LinearTransform)(R, P[0], M, 3, 3, 3);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPImmerseUsingQuaternion3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPImmerseUsingQuaternion3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,ImmerseUsingQuaternion3x3)(
	long			width,			/* Width of the image */
	long			height,			/* Height of the image */
	const FLOAT		*quat,			/* Orientation is specified using a normalized WXYZ quaternion */
	FLOAT			focalLength,	/* Focal length of the image plane, in pixels */
	const FLOAT		*center,		/* Center of image, relative to center of projection (can be NULL) */
	const FLOAT		*aspectSkew,	/* Aspect ratio and skew (can be NULL) */
	FLOAT			*M				/* The resulting matrix */
)
{
	FLOAT R[3][3];
	KPName3(KP,FLTPREC,QuaternionWXYZToMatrix3x3)(quat, R[0]);
	KPName3(KP,FLTPREC,TransposeSquareMatrixInPlace)(R[0], 3);
	KPName3(KP,FLTPREC,ImmerseUsingMatrix3x3)(width, height, R[0], focalLength, center, aspectSkew, M);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPProjectUsingQuaternion3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC
/********************************************************************************
 * KPProjectUsingQuaternion3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,ProjectUsingQuaternion3x3)(
	long			width,			/* Width of the image */
	long			height,			/* Height of the image */
	const FLOAT		*quat,			/* Orientation is specified using a normalized WXYZ quaternion */
	FLOAT			focalLength,	/* Focal length of the image plane, in pixels */
	const FLOAT		*center,		/* Center of image, relative to center of projection (can be NULL) */
	const FLOAT		*aspectSkew,	/* Aspect ratio and skew (can be NULL) */
	FLOAT			*M				/* The resulting matrix */
)
{
	FLOAT R[3][3];
	KPName3(KP,FLTPREC,QuaternionWXYZToMatrix3x3)(quat, R[0]);
	KPName3(KP,FLTPREC,TransposeSquareMatrixInPlace)(R[0], 3);
	KPName3(KP,FLTPREC,ProjectUsingMatrix3x3)(width, height, R[0], focalLength, center, aspectSkew, M);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPImmerseUsingPanTiltRoll3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC
/********************************************************************************
 * KPImmerseUsingPanTiltRoll3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,ImmerseUsingPanTiltRoll3x3)(
	long			width,			/* Width of the image */
	long			height,			/* Height of the image */
	FLOAT			pan,			/* Rotation about the Y axis */
	FLOAT			tilt,			/* Rotation about the X axis */
	FLOAT			roll,			/* Rotation about the Z axis */
	FLOAT			focalLength,	/* Focal length of the image plane, in pixels */
	const FLOAT		*center,		/* Center of image, relative to center of projection (can be NULL) */
	const FLOAT		*aspectSkew,	/* Aspect ratio and skew (can be NULL) */
	FLOAT			*M				/* The resulting matrix */
)
{
	FLOAT R[3][3];
	KPName3(KP,FLTPREC,SetRotationPanTiltRoll3x3)(pan, tilt, roll, R[0]);
	KPName3(KP,FLTPREC,ImmerseUsingMatrix3x3)(width, height, R[0], focalLength, center, aspectSkew, M);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPProjectUsingPanTiltRoll3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPProjectUsingPanTiltRoll3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,ProjectUsingPanTiltRoll3x3)(
	long			width,			/* Width of the image */
	long			height,			/* Height of the image */
	FLOAT			pan,			/* Rotation about the Y axis */
	FLOAT			tilt,			/* Rotation about the X axis */
	FLOAT			roll,			/* Rotation about the Z axis */
	FLOAT			focalLength,	/* Focal length of the image plane, in pixels */
	const FLOAT		*center,		/* Center of image, relative to center of projection (can be NULL) */
	const FLOAT		*aspectSkew,	/* Aspect ratio and skew (can be NULL) */
	FLOAT			*M				/* The resulting matrix */
)
{
	FLOAT R[3][3];
	KPName3(KP,FLTPREC,SetRotationPanTiltRoll3x3)(pan, tilt, roll, R[0]);
	KPName3(KP,FLTPREC,TransposeSquareMatrixInPlace)(R[0], 3);
	KPName3(KP,FLTPREC,ProjectUsingMatrix3x3)(width, height, R[0], focalLength, center, aspectSkew, M);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPImmerseUsingPanTilt3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC
/********************************************************************************
 * KPImmerseUsingPanTilt3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,ImmerseUsingPanTilt3x3)(
	long			width,			/* Width of the image */
	long			height,			/* Height of the image */
	FLOAT			pan,			/* Rotation about the Y axis */
	FLOAT			tilt,			/* Rotation about the X axis */
	FLOAT			focalLength,	/* Focal length of the image plane, in pixels */
	const FLOAT		*center,		/* Center of image, relative to center of projection (can be NULL) */
	const FLOAT		*aspectSkew,	/* Aspect ratio and skew (can be NULL) */
	FLOAT			*M				/* The resulting matrix */
)
{
	FLOAT R[3][3];
	KPName3(KP,FLTPREC,SetRotationPanTilt3x3)(pan, tilt, R[0]);
	KPName3(KP,FLTPREC,ImmerseUsingMatrix3x3)(width, height, R[0], focalLength, center, aspectSkew, M);
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPProjectUsingPanTilt3x3
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPProjectUsingPanTilt3x3
 ********************************************************************************/

void
KPName3(KP,FLTPREC,ProjectUsingPanTilt3x3)(
	long			width,			/* Width of the image */
	long			height,			/* Height of the image */
	FLOAT			pan,			/* Rotation about the Y axis */
	FLOAT			tilt,			/* Rotation about the X axis */
	FLOAT			focalLength,	/* Focal length of the image plane, in pixels */
	const FLOAT		*center,		/* Center of image, relative to center of projection (can be NULL) */
	const FLOAT		*aspectSkew,	/* Aspect ratio and skew (can be NULL) */
	FLOAT			*M				/* The resulting matrix */
)
{
	FLOAT R[3][3];
	KPName3(KP,FLTPREC,SetRotationPanTilt3x3)(pan, tilt, R[0]);
	KPName3(KP,FLTPREC,TransposeSquareMatrixInPlace)(R[0], 3);
	KPName3(KP,FLTPREC,ProjectUsingMatrix3x3)(width, height, R[0], focalLength, center, aspectSkew, M);
}
#endif /* MINIMAL_CUBIC */



#if PRAGMA_MARK_SUPPORTED
#pragma mark KPEmbed3x3In4x4Matrix
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPEmbed3x3In4x4Matrix
 ********************************************************************************/

void
KPName3(KP,FLTPREC,Embed3x3In4x4Matrix)(const FLOAT *M3, FLOAT *M4)
{
	M4[0*4+0] = M3[0*3+0];	M4[0*4+1] = M3[0*3+1];	M4[0*4+2] = M3[0*3+2];	M4[0*4+3] = 0;
	M4[1*4+0] = M3[1*3+0];	M4[1*4+1] = M3[1*3+1];	M4[1*4+2] = M3[1*3+2];	M4[1*4+3] = 0;
	M4[2*4+0] = M3[2*3+0];	M4[2*4+1] = M3[2*3+1];	M4[2*4+2] = M3[2*3+2];	M4[2*4+3] = 0;
	M4[3*4+0] = 0;			M4[3*4+1] = 0;			M4[3*4+2] = 0;			M4[3*4+3] = 1;
}
#endif /* MINIMAL_CUBIC */


#if PRAGMA_MARK_SUPPORTED
#pragma mark KPEmbedTransposed3x3In4x4Matrix
#endif /* PRAGMA_MARK_SUPPORTED */
#if !MINIMAL_CUBIC || !defined(DOUBLE_PRECISION)
/********************************************************************************
 * KPEmbedTransposed3x3In4x4Matrix
 ********************************************************************************/

void
KPName3(KP,FLTPREC,EmbedTransposed3x3In4x4Matrix)(const FLOAT *M3, FLOAT *M4)
{
	M4[0*4+0] = M3[0+3*0];	M4[0*4+1] = M3[0+3*1];	M4[0*4+2] = M3[0+3*2];	M4[0*4+3] = 0;
	M4[1*4+0] = M3[1+3*0];	M4[1*4+1] = M3[1+3*1];	M4[1*4+2] = M3[1+3*2];	M4[1*4+3] = 0;
	M4[2*4+0] = M3[2+3*0];	M4[2*4+1] = M3[2+3*1];	M4[2*4+2] = M3[2+3*2];	M4[2*4+3] = 0;
	M4[3*4+0] = 0;			M4[3*4+1] = 0;			M4[3*4+2] = 0;			M4[3*4+3] = 1;
}
#endif /* MINIMAL_CUBIC */



/********************************************************************************
 * KPProjectiveFrameFromPoints3x3
 ********************************************************************************/

long
KPName3(KP,FLTPREC,ProjectiveFrameFromPoints3x3)(const FLOAT *pts, FLOAT *M)
{
	typedef FLOAT DetType;	/* $$$ This might need to be double */
	DetType sx, sy, x12, y12, x32, y32, d;
	long result = 1;

	/* Build affine frame */
	M[0*3+0] = pts[1*2+0] - pts[0*2+0];		M[0*3+1] = pts[1*2+1] - pts[0*2+1];		M[0*3+2] = 0;	/* vector p1 - p0 */
	M[1*3+0] = pts[3*2+0] - pts[0*2+0];		M[1*3+1] = pts[3*2+1] - pts[0*2+1];		M[1*3+2] = 0;	/* vector p3 - p0 */
	M[2*3+0] = 				pts[0*2+0];		M[2*3+1] =				pts[0*2+1];		M[2*3+2] = 1;	/* point       p0 */

	/* Compute deviations from affine, and make adjustments */
	sx = pts[0*2+0] - pts[1*2+0] + pts[2*2+0] - pts[3*2+0];					/* s = p0 - p1 + p2 - p3 */
	sy = pts[0*2+1] - pts[1*2+1] + pts[2*2+1] - pts[3*2+1];
	if ((sx != 0) || (sy != 0)) {											/* Non-affine */
		x12 = pts[1*2+0] - pts[2*2+0];		y12 = pts[1*2+1] - pts[2*2+1];	/* p12 = p1 - p2 */
		x32 = pts[3*2+0] - pts[2*2+0];		y32 = pts[3*2+1] - pts[2*2+1];	/* p32 = p3 - p2 */
		d        = (FLOAT)((double)x12 * y32 - (double)y12 * x32);			/* Discriminant */
		if (d != 0)		/* This will never be 0 unless p1, p2, and p3 are collinear */
			d = 1 / d;
		else
			result = 0;	/* The result is degenerate */
		M[0*3+2] = (FLOAT)((double)sx  * y32 - (double)sy  * x32) * d;		/* Projective coefficients */
		M[1*3+2] = (FLOAT)((double)x12 *  sy - (double)y12 *  sx) * d;

		M[0*3+0] += M[0*3+2] * pts[1*2+0];		M[0*3+1] += M[0*3+2] * pts[1*2+1];	/* Make projective adjustments ... */
		M[1*3+0] += M[1*3+2] * pts[3*2+0];		M[1*3+1] += M[1*3+2] * pts[3*2+1];	/*   ...  to the affine frame      */
	}
	return result;
}


/********************************************************************************
 * KPProjectionFromCorrespondences3x3
 ********************************************************************************/

#define M22_IS_ALWAYS_POSITIVE 1

long
KPName3(KP,FLTPREC,ProjectionFromCorrespondences3x3)(const FLOAT *fr, const FLOAT *to, FLOAT *M)
{
	FLOAT MF[3*3], MT[3*3];
	long result = KPName3(KP,FLTPREC,ProjectiveFrameFromPoints3x3)(fr, MF)
				& KPName3(KP,FLTPREC,ProjectiveFrameFromPoints3x3)(to, MT);
	KPName3(KP,FLTPREC,AdjointMatrix3x3)(MF, MF);	/* Adjoint is always defined */
	KPName3(KP,FLTPREC,LinearTransform)(MF, MT, M, 3, 3, 3);
	if (M[2*3+2] != 0) {
		#ifdef M22_IS_ALWAYS_POSITIVE
			KPName3(KP,FLTPREC,ScaleVector)(1 / M[2*3+2], M, M, 9);			/* Canonicalize M[2][2] = +1 */
		#elif !USE_SINGLE_PRECISION_TRANSCENDENTALS
			KPName3(KP,FLTPREC,ScaleVector)(1 / fabs(M[2*3+2]),  M, M, 9);	/* Canonicalize M[2][2] = +/-1 */
		#else /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
			KPName3(KP,FLTPREC,ScaleVector)(1 / fabsf(M[2*3+2]), M, M, 9);	/* Canonicalize M[2][2] = +/-1 */
		#endif /* USE_SINGLE_PRECISION_TRANSCENDENTALS */
	}

	return result;
}


/********************************************************************************
 * KPDirectProjectionFromCorrespondences3x3
 * This is another way to compute the same  matrix as above,
 * except it takes considerably more time.
 ********************************************************************************/

long
KPName3(KP,FLTPREC,DirectProjectionFromCorrespondences3x3)(const FLOAT *fr, const FLOAT *to, FLOAT *M)
{
	FLOAT A[8*8], b[8];
	double LU[8*9];
	long ok;

	/* Fill up the A matrix thusly:
	 *	u0		u1		u2		u3		0		0		0		0
	 *	v0		v1		v2		v3		0		0		0		0
	 *	1		1		1		1		0		0		0		0
	 *	0		0		0		0		u0		u1		u2		u3
	 *	0		0		0		0		v0		v1		v2		v3
	 *	0		0		0		0		1		1		1		1
	 *	-u0x0	-u1x1	-u2x2	-u3x3	-u0y0	-u1y1	-u2y2	-u3y3
	 *	-v0x0	-v1x1	-v2x2	-v3x3	-v0y0	-v1y1	-v2y2	-v3y3
	 * Note that this is the transpose of the matrix given in Heckbert's thesis,
	 * because we use row vectors rather than column vectors.
	 */
	FLOAT *p = A;
	*p++ = fr[0*2+0];	*p++ = fr[1*2+0];	*p++ = fr[2*2+0];	*p++ = fr[3*2+0];	*p++ = 0;			*p++ = 0;			*p++ = 0;			*p++ = 0;
	*p++ = fr[0*2+1];	*p++ = fr[1*2+1];	*p++ = fr[2*2+1];	*p++ = fr[3*2+1];	*p++ = 0;			*p++ = 0;			*p++ = 0;			*p++ = 0;
	*p++ = 1;			*p++ = 1;			*p++ = 1;			*p++ = 1;			*p++ = 0;			*p++ = 0;			*p++ = 0;			*p++ = 0;
	*p++ = 0;			*p++ = 0;			*p++ = 0;			*p++ = 0;			*p++ = fr[0*2+0];	*p++ = fr[1*2+0];	*p++ = fr[2*2+0];	*p++ = fr[3*2+0];
	*p++ = 0;			*p++ = 0;			*p++ = 0;			*p++ = 0;			*p++ = fr[0*2+1];	*p++ = fr[1*2+1];	*p++ = fr[2*2+1];	*p++ = fr[3*2+1];
	*p++ = 0;			*p++ = 0;			*p++ = 0;			*p++ = 0;			*p++ = 1;			*p++ = 1;			*p++ = 1;			*p++ = 1;
	*p++ = -fr[0*2+0]*to[0*2+0]; *p++ = -fr[1*2+0]*to[1*2+0]; *p++ = -fr[2*2+0]*to[2*2+0]; *p++ = -fr[3*2+0]*to[3*2+0]; *p++ = -fr[0*2+0]*to[0*2+1]; *p++ = -fr[1*2+0]*to[1*2+1]; *p++ = -fr[2*2+0]*to[2*2+1]; *p++ = -fr[3*2+0]*to[3*2+1];
	*p++ = -fr[0*2+1]*to[0*2+0]; *p++ = -fr[1*2+1]*to[1*2+0]; *p++ = -fr[2*2+1]*to[2*2+0]; *p++ = -fr[3*2+1]*to[3*2+0]; *p++ = -fr[0*2+1]*to[0*2+1]; *p++ = -fr[1*2+1]*to[1*2+1]; *p++ = -fr[2*2+1]*to[2*2+1]; *p++ = -fr[3*2+1]*to[3*2+1];
	p = b;
	*p++ = to[0*2+0]; *p++ = to[1*2+0]; *p++ = to[2*2+0]; *p++ = to[3*2+0];
	*p++ = to[0*2+1]; *p++ = to[1*2+1]; *p++ = to[2*2+1]; *p++ = to[3*2+1];
	if ((ok = KPName3(KP,FLTPREC,LUDecompose)(A, LU, 8)) != 0) {
		KPName3(KP,FLTPREC,LUSolve)(LU, b, M, 8);
		M[2*3+2] = 1;
		KPName3(KP,FLTPREC,TransposeSquareMatrixInPlace)(M, 3);
	}
	return ok;
}

