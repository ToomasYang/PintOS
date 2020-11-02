#ifndef THREADS_FIXED_POINT_H
#define THREADS_FIXED_POINT_H

#define fp_t int
#define P 17
#define Q 14
#define F 1 << (Q)

#define INT_TO_FP(n) (n * F)
#define FP_TO_INT_ZERO(x) (x / F)
#define FP_TO_INT_NEAR(x) ((x) >= 0 ? ((x + F / 2) / F) : ((x - F / 2) / F))
#define ADD(x, y) (x + y)
#define SUB(x, y) (x - y)
#define INT_ADD(x, n) (x + n * F)
#define INT_SUB(x, n) (x - n * F)
#define MULT(x, y) (((int64_t)x) * y / F)
#define INT_MULT(x, n) (x * n)
#define DIV(x, y) (((int64_t)x) * F / y)
#define INT_DIV(x, n) (x / n)

#endif