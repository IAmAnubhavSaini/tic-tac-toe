char *generate_random_id(int size){
/* Read logic at
 * http://stackoverflow.com/questions/2999075/generate-a-random-number-within-range/2999130#2999130
 * OR
 * we could have used:
 * #include <time.h>
 * #include <stdlib.h>
 * srand(time(NULL));
 * int r = rand();
 * FROM
 * http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
 *
 */
  char *id = (char*)malloc(sizeof(char)*(size+1));
  char *valid_chars = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_-";
  int i=0;
  int limit = 63; //validchars count is 64, max index in 63 
  int divisor = RAND_MAX/(limit+1);
  int index = 0;
  
  for(i = 0; i< size; i++){
    do{
      index = rand()/divisor;
    }while(index>limit);

    id[i] = valid_chars[index];
  }
  id[i] = '\0';
  return id;
}