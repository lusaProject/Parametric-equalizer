//
// File: fir1_emxutil.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 17-Mar-2021 14:44:58
//
#ifndef FIR1_EMXUTIL_H
#define FIR1_EMXUTIL_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "fir1_types.h"

// Function Declarations
extern void emxEnsureCapacity_creal_T(emxArray_creal_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxFree_creal_T(emxArray_creal_T **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_creal_T(emxArray_creal_T **pEmxArray, int numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

//
// File trailer for fir1_emxutil.h
//
// [EOF]
//
