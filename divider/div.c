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
  FILE *DIV = fopen("divisor.tv","w");
 
  int n = 0x1f40;
  
  printf("     N    D  Q    R\n"); 
  for (i=1; i<=8000; i++) {
    // make a division
    intdiv(n, n+i, &q, &r);

    // show result
    printf("# %4x %4x %2x %4x\n", n, n+i, q, r);

    // save testvectors
    fprintf(DIV,"%04x%04x%02x%04x\n", n, n+i, q, r);
    
    // verify result
    assert((n * 256) == ((n+i) * q + r));
  }

  fclose(DIV);
  
  return 0;
}

