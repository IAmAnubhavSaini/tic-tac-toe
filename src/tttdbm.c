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
#define MAX_PLAYER_INFO_STORAGE 10
#define MAX_PLAYER_INFO_LENGTH  50
static FILE *database = "";//we are not going to use it yet.
void create_local_db(char *address){
  FILE *fpdb = fopen(address, "w");
  fclose(fpdb);
}
FILE *connect_local_db(char *address){
  FILE *fpdb = fopen(address, "a+");
  if(fpdb != NULL){
    database = fpdb;
    return fpdb;
  }
  else
    return NULL;
}
void disconnect_local_db(FILE *db){
  database = "";
  fclose(db);
}

void write_player_info(Player *player, FILE *fpdb){
  /* errors:
  * #wpi111: fpdb or player is NULL
  */
  char *format = "\nName: %s, Id: %s, Symbol: %c.";
  if(fpdb != NULL && player != NULL){
    fprintf(fpdb, format, player->Name, player->Id, player->Symbol);
  }
  else{
    printf("\n*error: #wpi111. Contact developer.*\n");
  }
}

char *[]read_player_info(FILE *fpdb){
  /* errors:
  * #rpi111: fpdb is NULL
  */
  char *players[MAX_PLAYER_INFO_STORAGE];
  int i = 0;
  int lim = MAX_PLAYER_INFO_STORAGE - 1;
  if(fpdb != NULL){
    for(i = 0; i <= lim; i++){
      //storage is managed by getline automatically.
      players[i] = getline(fpdb);
    }
  }
  else{
    printf("\n*error: #rpi111. Contact developer.*\n");
  }
}

//helper functions
char *getline(FILE *fpdb){
  char c;
  char info[MAX_PLAYER_INFO_LENGTH];
  while((c = fgetc(fpdb)) != EOF && c != '\n'){
    *info++ = c;
  }
  *info = '\0';
  return info;
}

//TODO: 
// 1. search for player info
// 2. initialize player info object from file
#endif