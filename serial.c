#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#define BILLION  1E9;

static inline void loadBar(unsigned long long x, unsigned long long n, int r, int w, long incircle)
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
    double pi = 4. * (double) incircle / (double) x;
    printf("] %1.10lf \n\033[F\033[J",pi);
}

int main(int argc, const char *argv[]){

  if (argc != 2) {
    fprintf(stderr, "usage: ./pi <total points>\n");
    exit(1);
  }

  unsigned long long incircle = 0;
  unsigned long long totalpoints = atol(argv[1]);
  unsigned long long i;

  srand((unsigned)time(NULL));
  unsigned int rand_state = rand();
  //inicio de tiempo de ejecución
  struct timespec requestStart, requestEnd;
  clock_gettime(CLOCK_REALTIME, &requestStart);

  for (i = 0; i < totalpoints; i++) {
    double x = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
    double y = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
    //double x = (double)rand() / (RAND_MAX);
    //double y = pow( 1 - x*x , 0.5 );
    //c = c + y;
    if (x * x + y * y < 1) {
      incircle++;
    }
    //pi = c / totalpoints * 4.0;
    loadBar(i,totalpoints,100,50,incircle);
  }

  //fin del tiempo de ejecución
  clock_gettime(CLOCK_REALTIME, &requestEnd);
  // Calculate time it took
  //printf("total points: %lli\n",totalpoints );
  //printf("incircle: %lli\n",incircle );
  //printf("percentage in circle :%3.2f\n", (double)incircle * 100 / (double)totalpoints );
  printf("Pi: %1.10lf\n", (4. * (double)incircle) / (double)totalpoints);
  //printf("Pi c: %1.10lf\n",pi );

  double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
    + ( requestEnd.tv_nsec - requestStart.tv_nsec )
    / BILLION;
  printf( "Time taken: %lf\n", accum );

  return 0;

}
