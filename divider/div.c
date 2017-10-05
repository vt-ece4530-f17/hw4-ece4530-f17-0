#include <stdio.h>
#include <assert.h>

void intdiv(int n,   // numerator,   16 bit
	    int d,   // denominator, 16 bit
	    int *q,  // quotient,    8 bit
	    int *r   // remainder,   16 bit
	             // this function computes the relation 256.n = d.q + r
	    ) {
  unsigned i;
  int qt, rt;
  qt = 0;
  rt = 0;
  if (d == 0)
    return;
  
  rt = 2 * n - d;
  for (i=0; i<7; i++) {
    if (rt < 0) {
      qt = 2 * qt;
      rt = 2 * rt + d;
    } else {
      qt = 2 * qt + 1;
      rt = 2 * rt - d;
    }
  }
  if (rt < 0) {
    qt = 2 * qt;
    rt = rt + d;
  } else {
    qt = 2 * qt + 1;
  }

  *q = qt;
  *r = rt;
}

int main() {
  int q, r, i;

  int n = 0x1f40;
  int d[20] = {
    0x1f41, 0x20d0, 0x225f, 0x23ee,
    0x257d, 0x270c, 0x289b, 0x2a2a, 
    0x2bb9, 0x2d48, 0x2ed7, 0x3066, 
    0x31f5, 0x3384, 0x3513, 0x36a2, 
    0x3831, 0x39c0, 0x3b4f, 0x3cde}; 
  
  printf("     N     D     Q     R\n"); 
  for (i=0; i<20; i++) {
    // make a division
    intdiv(n, d[i], &q, &r);

    // show result
    printf("# %4x %4x %2x %4x\n", n, d[i], q, r);
    
    // verify result
    assert((n * 256) == (d[i] * q + r));
  }
  
  return 0;
}

