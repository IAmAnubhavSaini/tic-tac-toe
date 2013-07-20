#include <time.h>
#include <stdlib.h>

void initiate_randomness(void){
#ifndef INITIATED_RANDOMNESS
  srand(time(NULL));
#define INITIATED_RANDOMNESS
#endif
}
int generate_random_number(void){
  initiate_randomness();
  int r = rand();
  return r;
}
int generate_limited_random_number(int limit){
  int divisor = RAND_MAX/(limit+1);
  int number = 0;
  initiate_randomness();
  do{
    number = rand()/divisor;
  }while(number > limit);
  return number;
}
