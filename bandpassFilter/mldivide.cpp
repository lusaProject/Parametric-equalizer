//
// File: mldivide.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 17-Mar-2021 14:44:58
//

// Include Files
#include "mldivide.h"
#include "fir1.h"
#include "fir1_emxutil.h"
#include "rt_nonfinite.h"
#include "xzgeqp3.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const emxArray_real_T *A
//                emxArray_real_T *B
// Return Type  : void
//
void mldiv(const emxArray_real_T *A, emxArray_real_T *B)
{
  emxArray_real_T *b_A;
  emxArray_int32_T *jpvt;
  int n;
  int u0;
  int i;
  int minmana;
  int minmn;
  int k;
  int ldap1;
  int u1;
  emxArray_real_T *tau;
  int j;
  int mmj_tmp;
  int jj;
  int b_i;
  int rankR;
  double tol;
  int ix;
  double s;
  emxArray_real_T *b_B;
  emxInit_real_T(&b_A, 2);
  emxInit_int32_T(&jpvt, 2);
  if (A->size[0] == A->size[1]) {
    n = A->size[1];
    i = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity_real_T(b_A, i);
    minmn = A->size[0] * A->size[1];
    for (i = 0; i < minmn; i++) {
      b_A->data[i] = A->data[i];
    }

    minmana = A->size[1];
    i = jpvt->size[0] * jpvt->size[1];
    jpvt->size[0] = 1;
    jpvt->size[1] = A->size[1];
    emxEnsureCapacity_int32_T(jpvt, i);
    jpvt->data[0] = 1;
    minmn = 1;
    for (k = 2; k <= minmana; k++) {
      minmn++;
      jpvt->data[k - 1] = minmn;
    }

    ldap1 = A->size[1];
    u0 = A->size[1] - 1;
    u1 = A->size[1];
    if (u0 < u1) {
      u1 = u0;
    }

    for (j = 0; j < u1; j++) {
      mmj_tmp = n - j;
      u0 = j * (n + 1);
      jj = j * (ldap1 + 1);
      rankR = u0 + 2;
      if (mmj_tmp < 1) {
        minmana = -1;
      } else {
        minmana = 0;
        if (mmj_tmp > 1) {
          ix = u0;
          tol = std::abs(b_A->data[jj]);
          for (k = 2; k <= mmj_tmp; k++) {
            ix++;
            s = std::abs(b_A->data[ix]);
            if (s > tol) {
              minmana = k - 1;
              tol = s;
            }
          }
        }
      }

      if (b_A->data[jj + minmana] != 0.0) {
        if (minmana != 0) {
          minmn = j + minmana;
          jpvt->data[j] = minmn + 1;
          ix = j;
          for (k = 0; k < n; k++) {
            tol = b_A->data[ix];
            b_A->data[ix] = b_A->data[minmn];
            b_A->data[minmn] = tol;
            ix += n;
            minmn += n;
          }
        }

        i = jj + mmj_tmp;
        for (b_i = rankR; b_i <= i; b_i++) {
          b_A->data[b_i - 1] /= b_A->data[jj];
        }
      }

      minmn = u0 + n;
      minmana = jj + ldap1;
      for (u0 = 0; u0 <= mmj_tmp - 2; u0++) {
        tol = b_A->data[minmn];
        if (b_A->data[minmn] != 0.0) {
          ix = jj + 1;
          i = minmana + 2;
          b_i = mmj_tmp + minmana;
          for (rankR = i; rankR <= b_i; rankR++) {
            b_A->data[rankR - 1] += b_A->data[ix] * -tol;
            ix++;
          }
        }

        minmn += n;
        minmana += n;
      }
    }

    i = A->size[1];
    for (minmn = 0; minmn <= i - 2; minmn++) {
      b_i = jpvt->data[minmn];
      if (b_i != minmn + 1) {
        tol = B->data[minmn];
        B->data[minmn] = B->data[b_i - 1];
        B->data[b_i - 1] = tol;
      }
    }

    for (k = 0; k < n; k++) {
      minmn = n * k;
      if (B->data[k] != 0.0) {
        i = k + 2;
        for (b_i = i; b_i <= n; b_i++) {
          B->data[b_i - 1] -= B->data[k] * b_A->data[(b_i + minmn) - 1];
        }
      }
    }

    for (k = n; k >= 1; k--) {
      minmn = n * (k - 1);
      tol = B->data[k - 1];
      if (tol != 0.0) {
        B->data[k - 1] = tol / b_A->data[(k + minmn) - 1];
        for (b_i = 0; b_i <= k - 2; b_i++) {
          B->data[b_i] -= B->data[k - 1] * b_A->data[b_i + minmn];
        }
      }
    }
  } else {
    n = A->size[1];
    u0 = A->size[0];
    minmana = A->size[1];
    if (u0 < minmana) {
      minmana = u0;
    }

    i = jpvt->size[0] * jpvt->size[1];
    jpvt->size[0] = 1;
    jpvt->size[1] = A->size[1];
    emxEnsureCapacity_int32_T(jpvt, i);
    minmn = A->size[1];
    for (i = 0; i < minmn; i++) {
      jpvt->data[i] = 0;
    }

    for (k = 0; k < n; k++) {
      jpvt->data[k] = k + 1;
    }

    i = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity_real_T(b_A, i);
    minmn = A->size[0] * A->size[1];
    for (i = 0; i < minmn; i++) {
      b_A->data[i] = A->data[i];
    }

    emxInit_real_T(&tau, 1);
    i = tau->size[0];
    tau->size[0] = minmana;
    emxEnsureCapacity_real_T(tau, i);
    for (i = 0; i < minmana; i++) {
      tau->data[i] = 0.0;
    }

    qrpf(b_A, A->size[0], A->size[1], tau, jpvt);
    rankR = 0;
    if (b_A->size[0] < b_A->size[1]) {
      minmn = b_A->size[0];
      minmana = b_A->size[1];
    } else {
      minmn = b_A->size[1];
      minmana = b_A->size[0];
    }

    tol = 2.2204460492503131E-15 * static_cast<double>(minmana);
    if (1.4901161193847656E-8 < tol) {
      tol = 1.4901161193847656E-8;
    }

    tol *= std::abs(b_A->data[0]);
    while ((rankR < minmn) && (!(std::abs(b_A->data[rankR + b_A->size[0] * rankR])
             <= tol))) {
      rankR++;
    }

    emxInit_real_T(&b_B, 1);
    i = b_B->size[0];
    b_B->size[0] = B->size[0];
    emxEnsureCapacity_real_T(b_B, i);
    minmn = B->size[0];
    for (i = 0; i < minmn; i++) {
      b_B->data[i] = B->data[i];
    }

    i = B->size[0];
    B->size[0] = b_A->size[1];
    emxEnsureCapacity_real_T(B, i);
    minmn = b_A->size[1];
    for (i = 0; i < minmn; i++) {
      B->data[i] = 0.0;
    }

    minmn = b_A->size[0];
    u0 = b_A->size[0];
    minmana = b_A->size[1];
    if (u0 < minmana) {
      minmana = u0;
    }

    for (j = 0; j < minmana; j++) {
      if (tau->data[j] != 0.0) {
        tol = b_B->data[j];
        i = j + 2;
        for (b_i = i; b_i <= minmn; b_i++) {
          tol += b_A->data[(b_i + b_A->size[0] * j) - 1] * b_B->data[b_i - 1];
        }

        tol *= tau->data[j];
        if (tol != 0.0) {
          b_B->data[j] -= tol;
          i = j + 2;
          for (b_i = i; b_i <= minmn; b_i++) {
            b_B->data[b_i - 1] -= b_A->data[(b_i + b_A->size[0] * j) - 1] * tol;
          }
        }
      }
    }

    emxFree_real_T(&tau);
    for (b_i = 0; b_i < rankR; b_i++) {
      B->data[jpvt->data[b_i] - 1] = b_B->data[b_i];
    }

    emxFree_real_T(&b_B);
    for (j = rankR; j >= 1; j--) {
      i = jpvt->data[j - 1];
      B->data[i - 1] /= b_A->data[(j + b_A->size[0] * (j - 1)) - 1];
      for (b_i = 0; b_i <= j - 2; b_i++) {
        B->data[jpvt->data[b_i] - 1] -= B->data[jpvt->data[j - 1] - 1] *
          b_A->data[b_i + b_A->size[0] * (j - 1)];
      }
    }
  }

  emxFree_int32_T(&jpvt);
  emxFree_real_T(&b_A);
}

//
// File trailer for mldivide.cpp
//
// [EOF]
//
