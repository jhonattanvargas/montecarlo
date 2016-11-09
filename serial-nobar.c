#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BILLION  1E9;


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
    if (x * x + y * y < 1) {
      incircle++;
    }
  }

  //fin del tiempo de ejecución
  clock_gettime(CLOCK_REALTIME, &requestEnd);
  printf("Pi: %1.10lf\n", (4. * (double)incircle) / (double)totalpoints);

  double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
    + ( requestEnd.tv_nsec - requestStart.tv_nsec )
    / BILLION;
  printf( "Time taken: %lf\n", accum );

  return 0;

}
