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


  initialize_engine();
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

  char song_path[300];

  snprintf(song_path, sizeof(song_path), "%s%s", MUSIC_DIR, song_name);

  ma_result res = ma_engine_play_sound(
    &engine,
    song_path,
    NULL
  );

  if(res != MA_SUCCESS){
    printf("Failed to play sound: %d\n", res);
  }

  printf("Press Enter to quit...");
  getch();

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
