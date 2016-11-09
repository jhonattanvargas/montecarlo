#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Process has done i out of n rounds,
// and we want a bar of width w and resolution r.
static inline void loadBar(int x, int n, int r, int w)
{
    // Only update r times.
    if ( x % (n/r +1) != 0 ) return;

    // Calculuate the ratio of complete-to-incomplete.
    float ratio = x/(float)n;
    int   c     = ratio * w;

    // Show the percentage complete.
    printf("%3d%% [", (int)(ratio*100) );

    // Show the load bar.
    for (int x=0; x<c; x++)
       printf("=");

    for (int x=c; x<w; x++)
       printf(" ");

    // ANSI Control codes to go back to the
    // previous line and clear it.
    printf("]\n\033[F\033[J");
}

int main(int argc, const char *argv[]){

  if (argc != 2) {
    fprintf(stderr, "usage: ./progress <total_iteration>\n");
    exit(1);
  }

  int n = atoi(argv[1]);

  for (int i = 0; i < n; i++) {
    //printf("%s\n","hols" );
    loadBar(i,n,100,50);
  }
  return 0;
}
