//
// File: string1.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 17-Mar-2021 14:44:58
//

// Include Files
#include "string1.h"
#include "fir1.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const char obj1_Value[4]
//                const char obj2_Value_data[]
//                const int obj2_Value_size[2]
// Return Type  : boolean_T
//
boolean_T string_eq(const char obj1_Value[4], const char obj2_Value_data[],
                    const int obj2_Value_size[2])
{
  boolean_T equal;
  int kstr;
  int exitg1;
  equal = false;
  if (4 == obj2_Value_size[1]) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 4) {
        if (obj1_Value[kstr] != obj2_Value_data[kstr]) {
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

  return equal;
}

//
// File trailer for string1.cpp
//
// [EOF]
//
