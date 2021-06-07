//
// File: validatestring.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 17-Mar-2021 14:44:58
//

// Include Files
#include "validatestring.h"
#include "fir1.h"
#include "rt_nonfinite.h"
#include <cstring>

// Variable Definitions
static const char cv[128] = { '\x00', '\x01', '\x02', '\x03', '\x04', '\x05',
  '\x06', '\x07', '\x08', '\x09', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f',
  '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19',
  '\x1a', '\x1b', '\x1c', '\x1d', '\x1e', '\x1f', ' ', '!', '\"', '#', '$', '%',
  '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4',
  '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'a', 'b', 'c', 'd',
  'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c',
  'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
  't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '\x7f' };

// Function Definitions

//
// Arguments    : const char str_Value[5]
//                char out_data[]
//                int out_size[2]
// Return Type  : void
//
void b_validatestring(const char str_Value[5], char out_data[], int out_size[2])
{
  int partial_match_size_idx_1;
  boolean_T b_bool;
  int kstr;
  int exitg1;
  static const char b_cv[8] = { 'B', 'A', 'N', 'D', 'P', 'A', 'S', 'S' };

  boolean_T matched;
  int nmatched;
  char partial_match_data[8];
  static const char vstr[8] = { 'B', 'A', 'N', 'D', 'P', 'A', 'S', 'S' };

  static const char cv1[7] = { 'N', 'O', 'S', 'C', 'A', 'L', 'E' };

  static const char b_vstr[7] = { 'N', 'O', 'S', 'C', 'A', 'L', 'E' };

  static const char cv2[5] = { 'S', 'C', 'A', 'L', 'E' };

  static const char c_vstr[5] = { 'S', 'C', 'A', 'L', 'E' };

  partial_match_size_idx_1 = 0;
  b_bool = false;
  kstr = 0;
  do {
    exitg1 = 0;
    if (kstr < 5) {
      if (cv[static_cast<unsigned char>(str_Value[kstr]) & 127] != cv[
          static_cast<int>(b_cv[kstr])]) {
        exitg1 = 1;
      } else {
        kstr++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  if (b_bool) {
    partial_match_size_idx_1 = 8;
    for (kstr = 0; kstr < 8; kstr++) {
      partial_match_data[kstr] = vstr[kstr];
    }

    matched = true;
    nmatched = 1;
  } else {
    matched = false;
    nmatched = 0;
  }

  b_bool = false;
  kstr = 0;
  do {
    exitg1 = 0;
    if (kstr < 5) {
      if (cv[static_cast<unsigned char>(str_Value[kstr]) & 127] != cv[
          static_cast<int>(cv1[kstr])]) {
        exitg1 = 1;
      } else {
        kstr++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  if (b_bool) {
    if (!matched) {
      partial_match_size_idx_1 = 7;
      for (kstr = 0; kstr < 7; kstr++) {
        partial_match_data[kstr] = b_vstr[kstr];
      }
    }

    nmatched++;
  }

  b_bool = false;
  kstr = 0;
  do {
    exitg1 = 0;
    if (kstr < 5) {
      if (cv[static_cast<unsigned char>(str_Value[kstr]) & 127] != cv[
          static_cast<int>(cv2[kstr])]) {
        exitg1 = 1;
      } else {
        kstr++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  if (b_bool) {
    nmatched = 1;
    partial_match_size_idx_1 = 5;
    for (kstr = 0; kstr < 5; kstr++) {
      partial_match_data[kstr] = c_vstr[kstr];
    }
  } else {
    if (nmatched == 0) {
      partial_match_size_idx_1 = 0;
    }
  }

  if ((nmatched == 0) || (partial_match_size_idx_1 == 0)) {
    out_size[0] = 1;
    out_size[1] = 0;
  } else {
    if (nmatched <= 1) {
      out_size[0] = 1;
      out_size[1] = partial_match_size_idx_1;
      if (0 <= partial_match_size_idx_1 - 1) {
        std::memcpy(&out_data[0], &partial_match_data[0],
                    partial_match_size_idx_1 * sizeof(char));
      }
    }
  }
}

//
// Arguments    : const char str_Value[8]
//                char out_data[]
//                int out_size[2]
// Return Type  : void
//
void validatestring(const char str_Value[8], char out_data[], int out_size[2])
{
  boolean_T b_bool;
  int kstr;
  int exitg1;
  static const char b_cv[8] = { 'B', 'A', 'N', 'D', 'P', 'A', 'S', 'S' };

  int i;
  static const char vstr[8] = { 'B', 'A', 'N', 'D', 'P', 'A', 'S', 'S' };

  b_bool = false;
  kstr = 0;
  do {
    exitg1 = 0;
    if (kstr < 8) {
      if (cv[static_cast<unsigned char>(str_Value[kstr]) & 127] != cv[
          static_cast<int>(b_cv[kstr])]) {
        exitg1 = 1;
      } else {
        kstr++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  if (b_bool) {
    kstr = 1;
    out_size[0] = 1;
    out_size[1] = 8;
    for (i = 0; i < 8; i++) {
      out_data[i] = vstr[i];
    }
  } else {
    kstr = 0;
    out_size[0] = 1;
    out_size[1] = 0;
  }

  if ((kstr == 0) || (out_size[1] == 0)) {
    out_size[0] = 1;
    out_size[1] = 0;
  }
}

//
// File trailer for validatestring.cpp
//
// [EOF]
//
