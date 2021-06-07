//
// File: fir1_initialize.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 17-Mar-2021 14:44:58
//

// Include Files
#include "fir1_initialize.h"
#include "fir1.h"
#include "fir1_data.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void fir1_initialize()
{
  rt_InitInfAndNaN();
  isInitialized_fir1 = true;
}

//
// File trailer for fir1_initialize.cpp
//
// [EOF]
//
