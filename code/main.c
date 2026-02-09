#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MUSIC_DIR "../music/"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

struct Node{
  char name[200];

  struct Node* prev;
  struct Node* next;
};

struct Node* start;


ma_engine engine;
ma_sound current;

int initialize_engine();
int deinitialize_engine();

int play_song();
void song_menu(char*);

//initial music files

void initialize_songs(){
  struct Node* m1 = (struct Node*)malloc(sizeof(struct Node));
  start = m1;

  struct Node* m2 = (struct Node*)malloc(sizeof(struct Node));


  strcpy(m1->name, "Spongebob soundtrack - Drunken Sailor.mp3");
  m1->prev = NULL;
  m1->next = m2;

  strcpy(m2->name, "C418_ Aria Math.mp3");
  m2->prev = m1; 
  m2->next = NULL;
}



int main(){


  initialize_songs();

  play_song();


  return 0;
}



int initialize_engine(){

  ma_result result;

  result = ma_engine_init(NULL, &engine);
  if (result != MA_SUCCESS) {
    return -1;  // Failed to initialize the engine.
  }

}

int deinitialize_engine(){
  ma_engine_uninit(&engine);
} 

int play_song(){

  initialize_engine();

  char song_path[300];
  struct Node* temp = start;

  song_menu(temp->name);
  snprintf(song_path, sizeof(song_path), "%s%s", MUSIC_DIR, start->name);

  if(
    ma_sound_init_from_file(&engine, song_path, MA_SOUND_FLAG_STREAM, NULL, NULL, &current) != MA_SUCCESS
  ){
    printf("Song Loading Failed\n");
    return -1;
  }

  ma_sound_start(&current);

  while(1){
    if(!ma_sound_is_playing(&current)){

      temp = temp->next;

      if(temp == NULL){
        break;
      }

      song_menu(temp->name);

      ma_sound_uninit(&current);
      snprintf(song_path, sizeof(song_path), "%s%s", MUSIC_DIR, temp->name);
      ma_sound_init_from_file(&engine, song_path, MA_SOUND_FLAG_STREAM, NULL, NULL, &current); 
      ma_sound_start(&current);
    }

    if(kbhit()){
      break;
    }
  }

  ma_sound_uninit(&current);
  deinitialize_engine();
}


void song_menu(char* curr_song){

  system("cls");

  struct Node* temp;
  int i = 1;

  printf("MUSIC PLAYER:\n");

  temp = start;

  while(temp != NULL){
    if(strcmp(temp->name, curr_song) == 0){
      printf(GREEN "%d. %s <-currently playing..." RESET "\n",i,temp->name);
    }else{
      printf("%d. %s\n",i,temp->name);
    }
    temp = temp->next;
    i++;
  }

  printf("Press Enter to quit...");
}
