#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MUSIC_DIR "../music/"

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

int play_song(char*);
void song_menu();

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

  char curr_song[200]; 

  strcpy(curr_song, start->name);

  song_menu();
  play_song(curr_song);


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

int play_song(char* song_name){

  initialize_engine();

  char song_path[300];
  struct Node* temp = start;

  snprintf(song_path, sizeof(song_path), "%s%s", MUSIC_DIR, song_name);

  if(
    ma_sound_init_from_file(&engine, song_path, MA_SOUND_FLAG_STREAM, NULL, NULL, &current) != MA_SUCCESS
  ){
    printf("Song Loading Failed\n");
    return -1;
  }

  ma_sound_start(&current);

  printf("Press Enter to quit...");
  while(1){
    if(!ma_sound_is_playing(&current) && temp!=NULL){
      temp = temp->next;
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


void song_menu(){

  struct Node* temp;
  int i = 1;

  printf("MUSIC PLAYER:\n");

  temp = start;

  while(temp != NULL){
    printf("%d. %s\n",i,temp->name);
    temp = temp->next;
    i++;
  }

}
