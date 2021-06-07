//
// File: xzgeqp3.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 17-Mar-2021 14:44:58
//

// Include Files
#include "xzgeqp3.h"
#include "fir1.h"
#include "fir1_emxutil.h"
#include "fir1_rtwutil.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include <cmath>

// Function Definitions

//
// Arguments    : emxArray_real_T *A
//                int m
//                int n
//                emxArray_real_T *tau
//                emxArray_int32_T *jpvt
// Return Type  : void
//
void qrpf(emxArray_real_T *A, int m, int n, emxArray_real_T *tau,
          emxArray_int32_T *jpvt)
{
  emxArray_real_T *work;
  int ma;
  int minmn;
  int i;
  int itemp;
  emxArray_real_T *vn1;
  emxArray_real_T *vn2;
  int j;
  int b_i;
  double smax;
  int ip1;
  int iy;
  int ii;
  int nmi;
  int mmi;
  int ix;
  int pvt;
  double temp2;
  double s;
  int jA;
  int lastv;
  boolean_T exitg2;
  int exitg1;
  emxInit_real_T(&work, 1);
  ma = A->size[0];
  if (m < n) {
    minmn = m;
  } else {
    minmn = n;
  }

  i = work->size[0];
  work->size[0] = A->size[1];
  emxEnsureCapacity_real_T(work, i);
  itemp = A->size[1];
  for (i = 0; i < itemp; i++) {
    work->data[i] = 0.0;
  }

  emxInit_real_T(&vn1, 1);
  i = vn1->size[0];
  vn1->size[0] = A->size[1];
  emxEnsureCapacity_real_T(vn1, i);
  itemp = A->size[1];
  for (i = 0; i < itemp; i++) {
    vn1->data[i] = 0.0;
  }

  emxInit_real_T(&vn2, 1);
  i = vn2->size[0];
  vn2->size[0] = A->size[1];
  emxEnsureCapacity_real_T(vn2, i);
  itemp = A->size[1];
  for (i = 0; i < itemp; i++) {
    vn2->data[i] = 0.0;
  }

  for (j = 0; j < n; j++) {
    smax = xnrm2(m, A, j * ma + 1);
    vn1->data[j] = smax;
    vn2->data[j] = smax;
  }

  for (b_i = 0; b_i < minmn; b_i++) {
    ip1 = b_i + 2;
    iy = b_i * ma;
    ii = iy + b_i;
    nmi = n - b_i;
    mmi = m - b_i;
    if (nmi < 1) {
      itemp = -1;
    } else {
      itemp = 0;
      if (nmi > 1) {
        ix = b_i;
        smax = std::abs(vn1->data[b_i]);
        for (j = 2; j <= nmi; j++) {
          ix++;
          s = std::abs(vn1->data[ix]);
          if (s > smax) {
            itemp = j - 1;
            smax = s;
          }
        }
      }
    }

    pvt = b_i + itemp;
    if (pvt + 1 != b_i + 1) {
      ix = pvt * ma;
      for (j = 0; j < m; j++) {
        smax = A->data[ix];
        A->data[ix] = A->data[iy];
        A->data[iy] = smax;
        ix++;
        iy++;
      }

      itemp = jpvt->data[pvt];
      jpvt->data[pvt] = jpvt->data[b_i];
      jpvt->data[b_i] = itemp;
      vn1->data[pvt] = vn1->data[b_i];
      vn2->data[pvt] = vn2->data[b_i];
    }

    if (b_i + 1 < m) {
      temp2 = A->data[ii];
      itemp = ii + 2;
      tau->data[b_i] = 0.0;
      if (mmi > 0) {
        smax = xnrm2(mmi - 1, A, ii + 2);
        if (smax != 0.0) {
          s = rt_hypotd_snf(A->data[ii], smax);
          if (A->data[ii] >= 0.0) {
            s = -s;
          }

          if (std::abs(s) < 1.0020841800044864E-292) {
            pvt = -1;
            i = ii + mmi;
            do {
              pvt++;
              for (j = itemp; j <= i; j++) {
                A->data[j - 1] *= 9.9792015476736E+291;
              }

              s *= 9.9792015476736E+291;
              temp2 *= 9.9792015476736E+291;
            } while (!(std::abs(s) >= 1.0020841800044864E-292));

            s = rt_hypotd_snf(temp2, xnrm2(mmi - 1, A, ii + 2));
            if (temp2 >= 0.0) {
              s = -s;
            }

            tau->data[b_i] = (s - temp2) / s;
            smax = 1.0 / (temp2 - s);
            for (j = itemp; j <= i; j++) {
              A->data[j - 1] *= smax;
            }

            for (j = 0; j <= pvt; j++) {
              s *= 1.0020841800044864E-292;
            }

            temp2 = s;
          } else {
            tau->data[b_i] = (s - A->data[ii]) / s;
            smax = 1.0 / (A->data[ii] - s);
            i = ii + mmi;
            for (j = itemp; j <= i; j++) {
              A->data[j - 1] *= smax;
            }

            temp2 = s;
          }
        }
      }

      A->data[ii] = temp2;
    } else {
      tau->data[b_i] = 0.0;
    }

    if (b_i + 1 < n) {
      temp2 = A->data[ii];
      A->data[ii] = 1.0;
      jA = (ii + ma) + 1;
      if (tau->data[b_i] != 0.0) {
        lastv = mmi - 1;
        itemp = (ii + mmi) - 1;
        while ((lastv + 1 > 0) && (A->data[itemp] == 0.0)) {
          lastv--;
          itemp--;
        }

        nmi -= 2;
        exitg2 = false;
        while ((!exitg2) && (nmi + 1 > 0)) {
          itemp = jA + nmi * ma;
          j = itemp;
          do {
            exitg1 = 0;
            if (j <= itemp + lastv) {
              if (A->data[j - 1] != 0.0) {
                exitg1 = 1;
              } else {
                j++;
              }
            } else {
              nmi--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = -1;
        nmi = -1;
      }

      if (lastv + 1 > 0) {
        if (nmi + 1 != 0) {
          for (iy = 0; iy <= nmi; iy++) {
            work->data[iy] = 0.0;
          }

          iy = 0;
          i = jA + ma * nmi;
          for (itemp = jA; ma < 0 ? itemp >= i : itemp <= i; itemp += ma) {
            ix = ii;
            smax = 0.0;
            pvt = itemp + lastv;
            for (j = itemp; j <= pvt; j++) {
              smax += A->data[j - 1] * A->data[ix];
              ix++;
            }

            work->data[iy] += smax;
            iy++;
          }
        }

        if (!(-tau->data[b_i] == 0.0)) {
          itemp = 0;
          for (j = 0; j <= nmi; j++) {
            if (work->data[itemp] != 0.0) {
              smax = work->data[itemp] * -tau->data[b_i];
              ix = ii;
              i = lastv + jA;
              for (pvt = jA; pvt <= i; pvt++) {
                A->data[pvt - 1] += A->data[ix] * smax;
                ix++;
              }
            }

            itemp++;
            jA += ma;
          }
        }
      }

      A->data[ii] = temp2;
    }

    for (j = ip1; j <= n; j++) {
      itemp = b_i + (j - 1) * ma;
      smax = vn1->data[j - 1];
      if (smax != 0.0) {
        s = std::abs(A->data[itemp]) / smax;
        s = 1.0 - s * s;
        if (s < 0.0) {
          s = 0.0;
        }

        temp2 = smax / vn2->data[j - 1];
        temp2 = s * (temp2 * temp2);
        if (temp2 <= 1.4901161193847656E-8) {
          if (b_i + 1 < m) {
            smax = xnrm2(mmi - 1, A, itemp + 2);
            vn1->data[j - 1] = smax;
            vn2->data[j - 1] = smax;
          } else {
            vn1->data[j - 1] = 0.0;
            vn2->data[j - 1] = 0.0;
          }
        } else {
          vn1->data[j - 1] = smax * std::sqrt(s);
        }
      }
    }
  }

  emxFree_real_T(&vn2);
  emxFree_real_T(&vn1);
  emxFree_real_T(&work);
}

//
// File trailer for xzgeqp3.cpp
//
// [EOF]
//
