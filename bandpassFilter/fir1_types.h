//
// File: fir1_types.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 17-Mar-2021 14:44:58
//
#ifndef FIR1_TYPES_H
#define FIR1_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_creal_T
{
  creal_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif

//
// File trailer for fir1_types.h
//
// [EOF]
//
