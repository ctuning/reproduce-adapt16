#include "base_hf1.h"

void hot_function1(const long* in,long* out,long in_len,
                    const long* coef,long coef_len,
                    long scale)
{
  long i,j,coef_len2,acc_length;
  long acc;
  const long *in_ptr, *data_ptr, *coef_start, *coef_ptr, *in_end;

  /* set up for coefficients */
  coef_start = coef;
  coef_len2 = (coef_len + 1) >> 1;

  /* set up input data pointers */
  in_end = in + in_len - 1;
  in_ptr = in + coef_len2 - 1;

  /* initial value of accumulation length for startup */
  acc_length = coef_len2;

  for(i = 0 ; i < in_len ; i++) {

    /* set up pointer for accumulation */
    data_ptr = in_ptr;
    coef_ptr = coef_start;

    /* do accumulation and write result with scale factor */

    acc = (long)(*coef_ptr++) * (*data_ptr--);
    for(j = 1 ; j < acc_length ; j++)
      acc += (long)(*coef_ptr++) * (*data_ptr--);
    *out++ = (int)(acc/scale);

    /* check for end case */

    if(in_ptr == in_end) {
      acc_length--;       /* one shorter each time */
      coef_start++;       /* next coefficient each time */
    }

    /* if not at end, then check for startup, add to input pointer */

    else {
      if(acc_length < coef_len) acc_length++;
      in_ptr++;
    }
  }
}

