//
// File: firls.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 17-Mar-2021 14:44:58
//

// Include Files
#include "firls.h"
#include "fir1.h"
#include "fir1_emxutil.h"
#include "fir1_rtwutil.h"
#include "mldivide.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static int div_s32_floor(int numerator, int denominator);

// Function Definitions

//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      absNumerator = static_cast<unsigned int>(numerator);
    }

    if (denominator < 0) {
      absDenominator = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      absDenominator = static_cast<unsigned int>(denominator);
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -static_cast<int>(tempAbsQuotient);
    } else {
      quotient = static_cast<int>(tempAbsQuotient);
    }
  }

  return quotient;
}

//
// Arguments    : double varargin_1
//                const double varargin_2[6]
//                const double varargin_3[6]
//                emxArray_real_T *h
// Return Type  : void
//
void firls(double varargin_1, const double varargin_2[6], const double
           varargin_3[6], emxArray_real_T *h)
{
  double N;
  int ixLead;
  emxArray_real_T *m;
  double max_freq[6];
  emxArray_real_T *k;
  double min_freq[6];
  emxArray_real_T *b;
  emxArray_real_T *I1;
  emxArray_real_T *I2;
  emxArray_real_T *G;
  emxArray_real_T *y;
  emxArray_real_T *a;
  emxArray_real_T *x;
  emxArray_real_T *b_x;
  emxArray_real_T *c_x;
  emxArray_real_T *d_x;
  emxArray_real_T *b_k;
  double work;
  int iyLead;
  int b_m;
  boolean_T fullband;
  double tmp2;
  boolean_T exitg1;
  double dF[5];
  double L;
  boolean_T Nodd;
  double b0;
  int i;
  int loop_ub;
  int s;
  unsigned int unnamed_idx_1;
  int b_loop_ub;
  int c_loop_ub;
  double m_s_tmp_tmp;
  double b1;
  double b_a;
  N = varargin_1;
  for (ixLead = 0; ixLead < 6; ixLead++) {
    max_freq[ixLead] = varargin_2[ixLead];
    min_freq[ixLead] = varargin_2[ixLead];
  }

  emxInit_real_T(&m, 2);
  emxInit_real_T(&k, 1);
  emxInit_real_T(&b, 1);
  emxInit_real_T(&I1, 2);
  emxInit_real_T(&I2, 2);
  emxInit_real_T(&G, 2);
  emxInit_real_T(&y, 1);
  emxInit_real_T(&a, 1);
  emxInit_real_T(&x, 2);
  emxInit_real_T(&b_x, 2);
  emxInit_real_T(&c_x, 2);
  emxInit_real_T(&d_x, 2);
  emxInit_real_T(&b_k, 1);
  if ((!(max_freq[0] > 1.0)) && (!(min_freq[0] < 0.0))) {
    if ((!(varargin_1 != rt_roundd_snf(varargin_1))) && (!(varargin_1 <= 0.0)) &&
        (varargin_3[5] != 0.0)) {
      if (rtIsNaN(varargin_1) || rtIsInf(varargin_1)) {
        work = rtNaN;
      } else {
        work = std::fmod(varargin_1, 2.0);
      }

      if (work == 1.0) {
        N = varargin_1 + 1.0;
      }
    }

    N++;
    for (ixLead = 0; ixLead < 6; ixLead++) {
      max_freq[ixLead] = varargin_2[ixLead] / 2.0;
    }

    ixLead = 1;
    iyLead = 0;
    work = 0.0;
    for (b_m = 0; b_m < 5; b_m++) {
      tmp2 = work;
      work = max_freq[ixLead];
      dF[iyLead] = max_freq[ixLead] - tmp2;
      ixLead++;
      iyLead++;
    }

    fullband = true;
    ixLead = 0;
    exitg1 = false;
    while ((!exitg1) && (ixLead < 2)) {
      if (dF[(ixLead << 1) + 1] != 0.0) {
        fullband = false;
        exitg1 = true;
      } else {
        ixLead++;
      }
    }

    L = (N - 1.0) / 2.0;
    Nodd = (rt_remd_snf(N, 2.0) == 1.0);
    b0 = 0.0;
    if (!Nodd) {
      if (rtIsNaN(L)) {
        i = m->size[0] * m->size[1];
        m->size[0] = 1;
        m->size[1] = 1;
        emxEnsureCapacity_real_T(m, i);
        m->data[0] = rtNaN;
      } else if (rtIsInf(L) && (0.0 == L)) {
        i = m->size[0] * m->size[1];
        m->size[0] = 1;
        m->size[1] = 1;
        emxEnsureCapacity_real_T(m, i);
        m->data[0] = rtNaN;
      } else {
        i = m->size[0] * m->size[1];
        m->size[0] = 1;
        loop_ub = static_cast<int>(std::floor(L));
        m->size[1] = loop_ub + 1;
        emxEnsureCapacity_real_T(m, i);
        for (i = 0; i <= loop_ub; i++) {
          m->data[i] = i;
        }
      }

      i = m->size[0] * m->size[1];
      s = m->size[0] * m->size[1];
      m->size[0] = 1;
      emxEnsureCapacity_real_T(m, s);
      loop_ub = i - 1;
      for (i = 0; i <= loop_ub; i++) {
        m->data[i] += 0.5;
      }
    } else if (rtIsNaN(L)) {
      i = m->size[0] * m->size[1];
      m->size[0] = 1;
      m->size[1] = 1;
      emxEnsureCapacity_real_T(m, i);
      m->data[0] = rtNaN;
    } else if (rtIsInf(L) && (0.0 == L)) {
      i = m->size[0] * m->size[1];
      m->size[0] = 1;
      m->size[1] = 1;
      emxEnsureCapacity_real_T(m, i);
      m->data[0] = rtNaN;
    } else {
      i = m->size[0] * m->size[1];
      m->size[0] = 1;
      loop_ub = static_cast<int>(std::floor(L));
      m->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(m, i);
      for (i = 0; i <= loop_ub; i++) {
        m->data[i] = i;
      }
    }

    i = k->size[0];
    k->size[0] = m->size[1];
    emxEnsureCapacity_real_T(k, i);
    loop_ub = m->size[1];
    for (i = 0; i < loop_ub; i++) {
      k->data[i] = m->data[i];
    }

    fullband = !fullband;
    i = static_cast<int>(std::floor(L + 1.0));
    s = I1->size[0] * I1->size[1];
    I1->size[0] = i;
    I1->size[1] = i;
    emxEnsureCapacity_real_T(I1, s);
    ixLead = i * i;
    for (s = 0; s < ixLead; s++) {
      I1->data[s] = 0.0;
    }

    s = I2->size[0] * I2->size[1];
    I2->size[0] = i;
    I2->size[1] = i;
    emxEnsureCapacity_real_T(I2, s);
    for (s = 0; s < ixLead; s++) {
      I2->data[s] = 0.0;
    }

    s = G->size[0] * G->size[1];
    G->size[0] = i;
    G->size[1] = i;
    emxEnsureCapacity_real_T(G, s);
    loop_ub = i * i;
    for (i = 0; i < loop_ub; i++) {
      G->data[i] = 0.0;
    }

    if (fullband) {
      unnamed_idx_1 = static_cast<unsigned int>(m->size[1]);
      loop_ub = k->size[0];
      i = I1->size[0] * I1->size[1];
      I1->size[0] = k->size[0];
      I1->size[1] = static_cast<int>(unnamed_idx_1);
      emxEnsureCapacity_real_T(I1, i);
      b_loop_ub = static_cast<int>(unnamed_idx_1);
      for (i = 0; i < b_loop_ub; i++) {
        for (s = 0; s < loop_ub; s++) {
          I1->data[s + I1->size[0] * i] = k->data[s] + m->data[i];
        }
      }

      unnamed_idx_1 = static_cast<unsigned int>(m->size[1]);
      loop_ub = k->size[0];
      i = I2->size[0] * I2->size[1];
      I2->size[0] = k->size[0];
      I2->size[1] = static_cast<int>(unnamed_idx_1);
      emxEnsureCapacity_real_T(I2, i);
      b_loop_ub = static_cast<int>(unnamed_idx_1);
      for (i = 0; i < b_loop_ub; i++) {
        for (s = 0; s < loop_ub; s++) {
          I2->data[s + I2->size[0] * i] = k->data[s] - m->data[i];
        }
      }
    }

    if (Nodd) {
      if (2 > k->size[0]) {
        i = 0;
        s = 0;
      } else {
        i = 1;
        s = k->size[0];
      }

      loop_ub = s - i;
      s = b_k->size[0];
      b_k->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_k, s);
      for (s = 0; s < loop_ub; s++) {
        b_k->data[s] = k->data[i + s];
      }

      i = k->size[0];
      k->size[0] = b_k->size[0];
      emxEnsureCapacity_real_T(k, i);
      loop_ub = b_k->size[0];
      for (i = 0; i < loop_ub; i++) {
        k->data[i] = b_k->data[i];
      }
    }

    i = b->size[0];
    b->size[0] = k->size[0];
    emxEnsureCapacity_real_T(b, i);
    loop_ub = k->size[0];
    for (i = 0; i < loop_ub; i++) {
      b->data[i] = 0.0;
    }

    loop_ub = k->size[0];
    b_loop_ub = k->size[0];
    c_loop_ub = k->size[0];
    for (b_m = 0; b_m < 3; b_m++) {
      s = b_m << 1;
      m_s_tmp_tmp = max_freq[s + 1];
      work = m_s_tmp_tmp - max_freq[s];
      tmp2 = (varargin_3[s + 1] - varargin_3[s]) / work;
      N = tmp2 * max_freq[s];
      b1 = varargin_3[s] - N;
      if (Nodd) {
        b0 += b1 * work + tmp2 / 2.0 * (m_s_tmp_tmp * m_s_tmp_tmp - max_freq[s] *
          max_freq[s]);
      }

      i = a->size[0];
      a->size[0] = k->size[0];
      emxEnsureCapacity_real_T(a, i);
      for (i = 0; i < loop_ub; i++) {
        a->data[i] = 6.2831853071795862 * k->data[i];
      }

      i = y->size[0];
      y->size[0] = a->size[0];
      emxEnsureCapacity_real_T(y, i);
      ixLead = a->size[0];
      for (i = 0; i < ixLead; i++) {
        y->data[i] = a->data[i] * m_s_tmp_tmp;
      }

      ixLead = y->size[0];
      for (iyLead = 0; iyLead < ixLead; iyLead++) {
        y->data[iyLead] = std::cos(y->data[iyLead]);
      }

      ixLead = a->size[0];
      for (i = 0; i < ixLead; i++) {
        a->data[i] *= max_freq[s];
      }

      ixLead = a->size[0];
      for (iyLead = 0; iyLead < ixLead; iyLead++) {
        a->data[iyLead] = std::cos(a->data[iyLead]);
      }

      b_a = tmp2 / 39.478417604357432;
      ixLead = b->size[0];
      for (i = 0; i < ixLead; i++) {
        b->data[i] += b_a * (y->data[i] - a->data[i]) / (k->data[i] * k->data[i]);
      }

      b_a = m_s_tmp_tmp * (tmp2 * m_s_tmp_tmp + b1);
      i = a->size[0];
      a->size[0] = k->size[0];
      emxEnsureCapacity_real_T(a, i);
      for (i = 0; i < b_loop_ub; i++) {
        a->data[i] = 2.0 * k->data[i] * m_s_tmp_tmp;
      }

      i = a->size[0];
      for (iyLead = 0; iyLead < i; iyLead++) {
        if (std::abs(a->data[iyLead]) < 1.0020841800044864E-292) {
          a->data[iyLead] = 1.0;
        } else {
          tmp2 = 3.1415926535897931 * a->data[iyLead];
          tmp2 = std::sin(tmp2) / tmp2;
          a->data[iyLead] = tmp2;
        }
      }

      work = max_freq[s] * (N + b1);
      i = y->size[0];
      y->size[0] = k->size[0];
      emxEnsureCapacity_real_T(y, i);
      for (i = 0; i < c_loop_ub; i++) {
        y->data[i] = 2.0 * k->data[i] * max_freq[s];
      }

      i = y->size[0];
      for (iyLead = 0; iyLead < i; iyLead++) {
        if (std::abs(y->data[iyLead]) < 1.0020841800044864E-292) {
          y->data[iyLead] = 1.0;
        } else {
          tmp2 = 3.1415926535897931 * y->data[iyLead];
          tmp2 = std::sin(tmp2) / tmp2;
          y->data[iyLead] = tmp2;
        }
      }

      ixLead = b->size[0];
      for (i = 0; i < ixLead; i++) {
        b->data[i] += b_a * a->data[i] - work * y->data[i];
      }

      if (fullband) {
        i = x->size[0] * x->size[1];
        x->size[0] = I1->size[0];
        x->size[1] = I1->size[1];
        emxEnsureCapacity_real_T(x, i);
        ixLead = I1->size[0] * I1->size[1];
        for (i = 0; i < ixLead; i++) {
          x->data[i] = 2.0 * I1->data[i] * m_s_tmp_tmp;
        }

        i = x->size[0] * x->size[1];
        for (iyLead = 0; iyLead < i; iyLead++) {
          if (std::abs(x->data[iyLead]) < 1.0020841800044864E-292) {
            x->data[iyLead] = 1.0;
          } else {
            x->data[iyLead] *= 3.1415926535897931;
            x->data[iyLead] = std::sin(x->data[iyLead]) / x->data[iyLead];
          }
        }

        i = b_x->size[0] * b_x->size[1];
        b_x->size[0] = I2->size[0];
        b_x->size[1] = I2->size[1];
        emxEnsureCapacity_real_T(b_x, i);
        ixLead = I2->size[0] * I2->size[1];
        for (i = 0; i < ixLead; i++) {
          b_x->data[i] = 2.0 * I2->data[i] * m_s_tmp_tmp;
        }

        i = b_x->size[0] * b_x->size[1];
        for (iyLead = 0; iyLead < i; iyLead++) {
          if (std::abs(b_x->data[iyLead]) < 1.0020841800044864E-292) {
            b_x->data[iyLead] = 1.0;
          } else {
            b_x->data[iyLead] *= 3.1415926535897931;
            b_x->data[iyLead] = std::sin(b_x->data[iyLead]) / b_x->data[iyLead];
          }
        }

        i = c_x->size[0] * c_x->size[1];
        c_x->size[0] = I1->size[0];
        c_x->size[1] = I1->size[1];
        emxEnsureCapacity_real_T(c_x, i);
        ixLead = I1->size[0] * I1->size[1];
        for (i = 0; i < ixLead; i++) {
          c_x->data[i] = 2.0 * I1->data[i] * max_freq[s];
        }

        i = c_x->size[0] * c_x->size[1];
        for (iyLead = 0; iyLead < i; iyLead++) {
          if (std::abs(c_x->data[iyLead]) < 1.0020841800044864E-292) {
            c_x->data[iyLead] = 1.0;
          } else {
            c_x->data[iyLead] *= 3.1415926535897931;
            c_x->data[iyLead] = std::sin(c_x->data[iyLead]) / c_x->data[iyLead];
          }
        }

        i = d_x->size[0] * d_x->size[1];
        d_x->size[0] = I2->size[0];
        d_x->size[1] = I2->size[1];
        emxEnsureCapacity_real_T(d_x, i);
        ixLead = I2->size[0] * I2->size[1];
        for (i = 0; i < ixLead; i++) {
          d_x->data[i] = 2.0 * I2->data[i] * max_freq[s];
        }

        i = d_x->size[0] * d_x->size[1];
        for (iyLead = 0; iyLead < i; iyLead++) {
          if (std::abs(d_x->data[iyLead]) < 1.0020841800044864E-292) {
            d_x->data[iyLead] = 1.0;
          } else {
            d_x->data[iyLead] *= 3.1415926535897931;
            d_x->data[iyLead] = std::sin(d_x->data[iyLead]) / d_x->data[iyLead];
          }
        }

        b_a = 0.5 * m_s_tmp_tmp;
        work = 0.5 * max_freq[s];
        ixLead = G->size[0] * G->size[1];
        for (i = 0; i < ixLead; i++) {
          G->data[i] += b_a * (x->data[i] + b_x->data[i]) - work * (c_x->data[i]
            + d_x->data[i]);
        }
      }
    }

    if (Nodd) {
      i = k->size[0];
      k->size[0] = b->size[0] + 1;
      emxEnsureCapacity_real_T(k, i);
      k->data[0] = b0;
      loop_ub = b->size[0];
      for (i = 0; i < loop_ub; i++) {
        k->data[i + 1] = b->data[i];
      }

      i = b->size[0];
      b->size[0] = k->size[0];
      emxEnsureCapacity_real_T(b, i);
      loop_ub = k->size[0];
      for (i = 0; i < loop_ub; i++) {
        b->data[i] = k->data[i];
      }
    }

    if (fullband) {
      mldiv(G, b);
    } else {
      loop_ub = b->size[0];
      for (i = 0; i < loop_ub; i++) {
        b->data[i] *= 4.0;
      }

      if (Nodd) {
        b->data[0] /= 2.0;
      }
    }

    if (Nodd) {
      if (2.0 > L + 1.0) {
        s = 0;
        ixLead = 1;
        iyLead = -1;
        b_m = 0;
        i = 0;
      } else {
        i = static_cast<int>((L + 1.0));
        s = i - 1;
        ixLead = -1;
        iyLead = 1;
        b_m = 1;
      }

      c_loop_ub = h->size[0] * h->size[1];
      h->size[0] = 1;
      loop_ub = div_s32_floor(iyLead - s, ixLead);
      h->size[1] = ((loop_ub + i) - b_m) + 2;
      emxEnsureCapacity_real_T(h, c_loop_ub);
      for (iyLead = 0; iyLead <= loop_ub; iyLead++) {
        h->data[iyLead] = b->data[s + ixLead * iyLead] / 2.0;
      }

      h->data[loop_ub + 1] = b->data[0];
      b_loop_ub = i - b_m;
      for (i = 0; i < b_loop_ub; i++) {
        h->data[(i + loop_ub) + 2] = b->data[b_m + i] / 2.0;
      }
    } else {
      i = a->size[0];
      a->size[0] = b->size[0];
      emxEnsureCapacity_real_T(a, i);
      loop_ub = b->size[0];
      for (i = 0; i < loop_ub; i++) {
        a->data[i] = b->data[i];
      }

      b_m = b->size[0] - 1;
      iyLead = b->size[0] >> 1;
      for (ixLead = 0; ixLead < iyLead; ixLead++) {
        work = a->data[ixLead];
        c_loop_ub = b_m - ixLead;
        a->data[ixLead] = a->data[c_loop_ub];
        a->data[c_loop_ub] = work;
      }

      i = h->size[0] * h->size[1];
      h->size[0] = 1;
      h->size[1] = a->size[0] + b->size[0];
      emxEnsureCapacity_real_T(h, i);
      loop_ub = a->size[0];
      for (i = 0; i < loop_ub; i++) {
        h->data[i] = 0.5 * a->data[i];
      }

      loop_ub = b->size[0];
      for (i = 0; i < loop_ub; i++) {
        h->data[i + a->size[0]] = 0.5 * b->data[i];
      }
    }
  }

  emxFree_real_T(&b_k);
  emxFree_real_T(&d_x);
  emxFree_real_T(&c_x);
  emxFree_real_T(&b_x);
  emxFree_real_T(&x);
  emxFree_real_T(&a);
  emxFree_real_T(&y);
  emxFree_real_T(&G);
  emxFree_real_T(&I2);
  emxFree_real_T(&I1);
  emxFree_real_T(&b);
  emxFree_real_T(&k);
  emxFree_real_T(&m);
}

//
// File trailer for firls.cpp
//
// [EOF]
//
