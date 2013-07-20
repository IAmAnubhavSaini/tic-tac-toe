/*
 * Anubhav Saini
 * 
 * tttdbm.c : tic tac toe database management
 * this file deals with data and management
 */

#ifndef TTTDBMC
#define TTTDBMC
//#include "sqlite3.c"
//#include "sqlite3.h"

void create_local_db(char *address){
  FILE *fpdb = fopen(address, "w");
  fclose(fpdb);
}
FILE *connect_local_db(char *address){
  FILE *fpdb = fopen(address, "a+");
  if(fpdb != NULL)
    return fpdb;
  else
    return NULL;
}
void disconnect_local_db(FILE *db){
  fclose(db);
}

void write_player_info(Player *player, FILE *fpdb){
  /* errors:
   * #aaa111: fpdb or player is NULL
   */
  char *format = "\nName: %s, Id: %s, Symbol: %c.";
  if(fpdb != NULL && player != NULL){
    fprintf(fpdb, format, player->Name, player->Id, player->Symbol);
  }
  else{
    printf("\n*error: #aaa111. Contact developer.");
  }
}


#endif