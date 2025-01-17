/*
 * bigint.c
 *
 *  Created on: Jun. 15, 2024
 *      Author: dillonquick
 */
#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

BIGINT bigint(char *p) {
  BIGINT bn = {0};
  if (p == NULL) 
    return bn;
  else if (!(*p >= '0' && *p <= '9')) { // not begin with digits 
    return bn;
  }
  else if (*p == '0' && *(p+1) == '\0') { // just "0"
    dll_insert_end(&bn, new_node(*p -'0'));
    return bn;
  }  
  else { 
    while (*p) {
      if (*p >= '0' && *p <= '9') {
        dll_insert_end(&bn, new_node(*p -'0'));
      } else {
        dll_clean(&bn);
        break;
      }
      p++;
    }
    return bn;
  }
}

BIGINT bigint_add(BIGINT op1, BIGINT op2) {
  BIGINT result;
  result.length = 0;
  result.start = NULL;
  result.end = NULL;

  NODE *n1 = op1.end;
  NODE *n2 = op2.end;
  int carry = 0;

  while (n1 != NULL || n2 != NULL || carry != 0) {
    int sum = carry;
    if (n1 != NULL) {
      sum += n1->data;
      n1 = n1->prev;
    }
    if (n2 != NULL) {
      sum += n2->data;
      n2 = n2->prev;
    }
    carry = sum / 10;
    NODE *newnode = new_node(sum % 10);
    dll_insert_start(&result, newnode);
  }
  return result;
}

BIGINT bigint_fibonacci(int n) {
  BIGINT a = bigint("0");
  BIGINT b = bigint("1");

  if (n == 0) {
    return a;
  } else if (n == 1) {
    return b;
  }

  for (int i = 2; i <= n; i++) {
    BIGINT temp = bigint_add(a, b);
    dll_clean(&a);
    a = b;
    b = temp;
  }

  dll_clean(&a);
  return b;
}


