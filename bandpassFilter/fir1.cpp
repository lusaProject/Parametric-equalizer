//
// File: fir1.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 17-Mar-2021 14:44:58
//

// Include Files
#include "fir1.h"
#include "fir1_data.h"
#include "fir1_emxutil.h"
#include "fir1_initialize.h"
#include "fir1_rtwutil.h"
#include "firls.h"
#include "rt_nonfinite.h"
#include "string1.h"
#include "validatestring.h"
#include <cmath>
#include <cstring>

// Function Declarations
static void parseOptArgs(const char varargin_1[8], const char varargin_3[5],
  char ftype_Value_data[], int ftype_Value_size[2], double *scaling);

// Function Definitions

//
// Arguments    : const char varargin_1[8]
//                const char varargin_3[5]
//                char ftype_Value_data[]
//                int ftype_Value_size[2]
//                double *scaling
// Return Type  : void
//
static void parseOptArgs(const char varargin_1[8], const char varargin_3[5],
  char ftype_Value_data[], int ftype_Value_size[2], double *scaling)
{
  int scale_Value_size_idx_1;
  int kstr;
  char scale_Value_data[8];
  static const char varargin_1_f1_Value[5] = { 'S', 'C', 'A', 'L', 'E' };

  boolean_T ftypeFound;
  static const char varargin_2_f3_Value[8] = { 'B', 'A', 'N', 'D', 'P', 'A', 'S',
    'S' };

  boolean_T scaleFound;
  char strOption_Value_data[8];
  int strOption_Value_size[2];
  boolean_T equal;
  int exitg1;
  static const char b[7] = { 'N', 'O', 'S', 'C', 'A', 'L', 'E' };

  static const char varargin_2_f2_Value[4] = { 'H', 'I', 'G', 'H' };

  static const char varargin_2_f1_Value[3] = { 'L', 'O', 'W' };

  static const char varargin_2_f4_Value[4] = { 'S', 'T', 'O', 'P' };

  static const char varargin_2_f5_Value[4] = { 'D', 'C', '-', '0' };

  static const char varargin_2_f6_Value[4] = { 'D', 'C', '-', '1' };

  static const char b_cv[7] = { 'N', 'O', 'S', 'C', 'A', 'L', 'E' };

  *scaling = 1.0;
  scale_Value_size_idx_1 = 5;
  for (kstr = 0; kstr < 5; kstr++) {
    scale_Value_data[kstr] = varargin_1_f1_Value[kstr];
  }

  ftype_Value_size[0] = 1;
  ftype_Value_size[1] = 8;
  for (kstr = 0; kstr < 8; kstr++) {
    ftype_Value_data[kstr] = varargin_2_f3_Value[kstr];
  }

  ftypeFound = false;
  scaleFound = false;
  validatestring(varargin_1, strOption_Value_data, strOption_Value_size);
  equal = false;
  if (5 == strOption_Value_size[1]) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 5) {
        if (varargin_1_f1_Value[kstr] != strOption_Value_data[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (equal) {
    kstr = 0;
  } else {
    equal = false;
    if (7 == strOption_Value_size[1]) {
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 7) {
          if (b[kstr] != strOption_Value_data[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          equal = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (equal) {
      kstr = 0;
    } else {
      equal = false;
      if (3 == strOption_Value_size[1]) {
        kstr = 0;
        do {
          exitg1 = 0;
          if (kstr < 3) {
            if (varargin_2_f1_Value[kstr] != strOption_Value_data[kstr]) {
              exitg1 = 1;
            } else {
              kstr++;
            }
          } else {
            equal = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (equal) {
        kstr = 1;
      } else if (string_eq(varargin_2_f2_Value, strOption_Value_data,
                           strOption_Value_size)) {
        kstr = 1;
      } else {
        equal = false;
        if (8 == strOption_Value_size[1]) {
          kstr = 0;
          do {
            exitg1 = 0;
            if (kstr < 8) {
              if (varargin_2_f3_Value[kstr] != strOption_Value_data[kstr]) {
                exitg1 = 1;
              } else {
                kstr++;
              }
            } else {
              equal = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (equal) {
          kstr = 1;
        } else if (string_eq(varargin_2_f4_Value, strOption_Value_data,
                             strOption_Value_size)) {
          kstr = 1;
        } else if (string_eq(varargin_2_f5_Value, strOption_Value_data,
                             strOption_Value_size)) {
          kstr = 1;
        } else if (string_eq(varargin_2_f6_Value, strOption_Value_data,
                             strOption_Value_size)) {
          kstr = 1;
        } else {
          kstr = -1;
        }
      }
    }
  }

  switch (kstr) {
   case 0:
    scale_Value_size_idx_1 = strOption_Value_size[1];
    kstr = strOption_Value_size[0] * strOption_Value_size[1];
    if (0 <= kstr - 1) {
      std::memcpy(&scale_Value_data[0], &strOption_Value_data[0], kstr * sizeof
                  (char));
    }

    scaleFound = true;
    break;

   case 1:
    ftype_Value_size[0] = 1;
    ftype_Value_size[1] = strOption_Value_size[1];
    kstr = strOption_Value_size[0] * strOption_Value_size[1];
    if (0 <= kstr - 1) {
      std::memcpy(&ftype_Value_data[0], &strOption_Value_data[0], kstr * sizeof
                  (char));
    }

    ftypeFound = true;
    break;
  }

  b_validatestring(varargin_3, strOption_Value_data, strOption_Value_size);
  equal = false;
  if (5 == strOption_Value_size[1]) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 5) {
        if (varargin_1_f1_Value[kstr] != strOption_Value_data[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (equal) {
    kstr = 0;
  } else {
    equal = false;
    if (7 == strOption_Value_size[1]) {
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 7) {
          if (b[kstr] != strOption_Value_data[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          equal = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (equal) {
      kstr = 0;
    } else {
      equal = false;
      if (3 == strOption_Value_size[1]) {
        kstr = 0;
        do {
          exitg1 = 0;
          if (kstr < 3) {
            if (varargin_2_f1_Value[kstr] != strOption_Value_data[kstr]) {
              exitg1 = 1;
            } else {
              kstr++;
            }
          } else {
            equal = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (equal) {
        kstr = 1;
      } else if (string_eq(varargin_2_f2_Value, strOption_Value_data,
                           strOption_Value_size)) {
        kstr = 1;
      } else {
        equal = false;
        if (8 == strOption_Value_size[1]) {
          kstr = 0;
          do {
            exitg1 = 0;
            if (kstr < 8) {
              if (varargin_2_f3_Value[kstr] != strOption_Value_data[kstr]) {
                exitg1 = 1;
              } else {
                kstr++;
              }
            } else {
              equal = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (equal) {
          kstr = 1;
        } else if (string_eq(varargin_2_f4_Value, strOption_Value_data,
                             strOption_Value_size)) {
          kstr = 1;
        } else if (string_eq(varargin_2_f5_Value, strOption_Value_data,
                             strOption_Value_size)) {
          kstr = 1;
        } else if (string_eq(varargin_2_f6_Value, strOption_Value_data,
                             strOption_Value_size)) {
          kstr = 1;
        } else {
          kstr = -1;
        }
      }
    }
  }

  switch (kstr) {
   case 0:
    if (!scaleFound) {
      scale_Value_size_idx_1 = strOption_Value_size[1];
      kstr = strOption_Value_size[0] * strOption_Value_size[1];
      if (0 <= kstr - 1) {
        std::memcpy(&scale_Value_data[0], &strOption_Value_data[0], kstr *
                    sizeof(char));
      }
    }
    break;

   case 1:
    if (!ftypeFound) {
      ftype_Value_size[0] = 1;
      ftype_Value_size[1] = strOption_Value_size[1];
      kstr = strOption_Value_size[0] * strOption_Value_size[1];
      if (0 <= kstr - 1) {
        std::memcpy(&ftype_Value_data[0], &strOption_Value_data[0], kstr *
                    sizeof(char));
      }
    }
    break;
  }

  equal = false;
  if (scale_Value_size_idx_1 == 7) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 7) {
        if (scale_Value_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (equal) {
    *scaling = 0.0;
  }
}

//
// Arguments    : double varargin_1
//                const double varargin_2[2]
//                const char varargin_3[8]
//                const double varargin_4[100]
//                const char varargin_5[5]
//                double b[100]
//                double *a
// Return Type  : void
//
void fir1(double varargin_1, const double varargin_2[2], const char varargin_3[8],
          const double varargin_4[100], const char varargin_5[5], double b[100],
          double *a)
{
  char ftype_Value_data[8];
  int ftype_Value_size[2];
  double scaling;
  boolean_T equal;
  int idx;
  int exitg1;
  double freq[6];
  static const char b_cv[8] = { 'B', 'A', 'N', 'D', 'P', 'A', 'S', 'S' };

  static const char cv1[4] = { 'D', 'C', '-', '0' };

  int k;
  double N;
  signed char i;
  double magnitude[6];
  static const char cv2[4] = { 'H', 'I', 'G', 'H' };

  emxArray_real_T *hh;
  double r;
  emxArray_creal_T *y;
  if (isInitialized_fir1 == false) {
    fir1_initialize();
  }

  parseOptArgs(varargin_3, varargin_5, ftype_Value_data, ftype_Value_size,
               &scaling);
  equal = false;
  if (ftype_Value_size[1] == 8) {
    idx = 0;
    do {
      exitg1 = 0;
      if (idx < 8) {
        if (ftype_Value_data[idx] != b_cv[idx]) {
          exitg1 = 1;
        } else {
          idx++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (equal) {
    ftype_Value_size[1] = 4;
    ftype_Value_data[0] = 'D';
    ftype_Value_data[1] = 'C';
    ftype_Value_data[2] = '-';
    ftype_Value_data[3] = '0';
  }

  freq[0] = 0.0;
  freq[1] = varargin_2[0];
  freq[2] = varargin_2[0];
  freq[3] = varargin_2[1];
  freq[4] = varargin_2[1];
  freq[5] = 1.0;
  equal = false;
  if (ftype_Value_size[1] == 4) {
    idx = 0;
    do {
      exitg1 = 0;
      if (idx < 4) {
        if (ftype_Value_data[idx] != cv1[idx]) {
          exitg1 = 1;
        } else {
          idx++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (!equal) {
    equal = false;
    if (ftype_Value_size[1] == 4) {
      idx = 0;
      do {
        exitg1 = 0;
        if (idx < 4) {
          if (ftype_Value_data[idx] != cv2[idx]) {
            exitg1 = 1;
          } else {
            idx++;
          }
        } else {
          equal = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (!equal) {
      equal = true;
    } else {
      equal = false;
    }
  } else {
    equal = false;
  }

  idx = -1;
  for (k = 0; k < 3; k++) {
    i = static_cast<signed char>(rt_remd_snf(static_cast<double>(k) +
      static_cast<double>(equal), 2.0));
    idx++;
    magnitude[idx] = i;
    idx++;
    magnitude[idx] = i;
  }

  N = varargin_1;
  if ((!(varargin_1 != rt_roundd_snf(varargin_1))) && (!(varargin_1 <= 0.0)) &&
      (magnitude[5] != 0.0)) {
    if (rtIsNaN(varargin_1) || rtIsInf(varargin_1)) {
      r = rtNaN;
    } else {
      r = std::fmod(varargin_1, 2.0);
    }

    if (r == 1.0) {
      N = varargin_1 + 1.0;
    }
  }

  emxInit_real_T(&hh, 2);
  firls((N + 1.0) - 1.0, freq, magnitude, hh);
  for (idx = 0; idx < 100; idx++) {
    b[idx] = hh->data[idx] * varargin_4[idx];
  }

  if (scaling != 0.0) {
    if (equal) {
      scaling = b[0];
      for (k = 0; k < 99; k++) {
        scaling += b[k + 1];
      }

      for (idx = 0; idx < 100; idx++) {
        b[idx] /= scaling;
      }
    } else {
      if (rtIsNaN((N + 1.0) - 1.0)) {
        idx = hh->size[0] * hh->size[1];
        hh->size[0] = 1;
        hh->size[1] = 1;
        emxEnsureCapacity_real_T(hh, idx);
        hh->data[0] = rtNaN;
      } else if (rtIsInf((N + 1.0) - 1.0) && (0.0 == (N + 1.0) - 1.0)) {
        idx = hh->size[0] * hh->size[1];
        hh->size[0] = 1;
        hh->size[1] = 1;
        emxEnsureCapacity_real_T(hh, idx);
        hh->data[0] = rtNaN;
      } else {
        idx = hh->size[0] * hh->size[1];
        hh->size[0] = 1;
        k = static_cast<int>(std::floor((N + 1.0) - 1.0));
        hh->size[1] = k + 1;
        emxEnsureCapacity_real_T(hh, idx);
        for (idx = 0; idx <= k; idx++) {
          hh->data[idx] = idx;
        }
      }

      emxInit_creal_T(&y, 2);
      if (varargin_2[1] == 1.0) {
        scaling = 1.0;
      } else {
        scaling = (varargin_2[0] + varargin_2[1]) / 2.0;
      }

      scaling /= 2.0;
      idx = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = hh->size[1];
      emxEnsureCapacity_creal_T(y, idx);
      k = hh->size[0] * hh->size[1];
      for (idx = 0; idx < k; idx++) {
        y->data[idx].re = scaling * (hh->data[idx] * -0.0);
        y->data[idx].im = scaling * (hh->data[idx] * -6.2831853071795862);
      }

      idx = y->size[1];
      for (k = 0; k < idx; k++) {
        if (y->data[k].im == 0.0) {
          y->data[k].re = std::exp(y->data[k].re);
          y->data[k].im = 0.0;
        } else if (rtIsInf(y->data[k].im) && rtIsInf(y->data[k].re) && (y->
                    data[k].re < 0.0)) {
          y->data[k].re = 0.0;
          y->data[k].im = 0.0;
        } else {
          r = std::exp(y->data[k].re / 2.0);
          y->data[k].re = r * (r * std::cos(y->data[k].im));
          y->data[k].im = r * (r * std::sin(y->data[k].im));
        }
      }

      scaling = 0.0;
      N = 0.0;
      for (idx = 0; idx < 100; idx++) {
        scaling += y->data[idx].re * b[idx] - y->data[idx].im * 0.0;
        N += y->data[idx].re * 0.0 + y->data[idx].im * b[idx];
      }

      emxFree_creal_T(&y);
      scaling = rt_hypotd_snf(scaling, N);
      for (idx = 0; idx < 100; idx++) {
        b[idx] /= scaling;
      }
    }
  }

  emxFree_real_T(&hh);
  *a = 1.0;
}

//
// File trailer for fir1.cpp
//
// [EOF]
//
