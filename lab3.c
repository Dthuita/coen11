/*
  David Thuita
  COEN 11
  Lab 3
  Wednesday 5:15pm
*/
#include <stdio.h>
#include <string.h>

#define NAME 50

int counter=0;
//char name[LENG][NAME];
//int size[LENG];

typedef struct Lists{
  char name[NAME];
  int size;
}List;

void insert();
void removeP();
void display();
void size_display();
int check_duplicate();

List myList[10];

int main(){

  char cmd;
  while(1){

    printf("a-insert, r-remove, d-display, s-size, q-quit, Enter command: ");
    scanf(" %c%*c", &cmd);//why?????

    switch(cmd){
      case 'a':
            insert();
            break;
      case 'd':
            display();
            //printf("%s | %d \n", name[counter], size[counter]);
            break;
      case 'r':
            removeP();
            break;
      case 's': //size command
            size_display();
            break;
      case 'q':
            return(0);
            break;
      default:
            printf("Invalid command. Try again.\n\n");
            break;
    }

  }

}
void insert(){
  if(counter == 10){
    printf("List is full!!");
    return;
  }
   //enter info
   printf("enter name: ");
   scanf("%s", myList[counter].name);
   printf("enter size: ");
   scanf("%d", &myList[counter].size);

   //check name duplicate
   while( check_duplicate() == 0){
     printf("Invalid name. re-enter name: ");
     scanf("%s", myList[counter].name);
   }
   //check size invalid
   while(myList[counter].size > 10){
     printf("re-enter size: ");
     scanf("%d", &myList[counter].size);
   }

   counter++;
}
void removeP(){
  //tell user who's removed
  int rSize;
  printf("enter size for removal: ");
  scanf("%d", &rSize);

  //erase spot
  int sum=rSize; //sum of sizes top to bottom being deleted
  int p=0;
  for(; p < counter; p++){

    if(myList[p].size <= sum && sum > 0){
      sum -= myList[p].size;

      //shift array
      int z = p;
      for(; z < counter-1; z++){
        myList[z] = myList[z+1];
      }
      p--;
      counter--;
    }

  }

}
int check_duplicate(){
  int z = counter;
  for(int x=0; x < counter; x++){
    if( strcmp(myList[x].name, myList[counter].name) == 0){
      return 0;
    }
  }
  return 1;
}
void size_display(){

  int rSize=0;
  printf("What size to display?");
  scanf("%d",&rSize);

  int p=0;
  for(; p < counter; p++){
    if(myList[p].size <= rSize){

      printf("%s | %d \n", myList[p].name, myList[p].size);

    }
  }
}
void display(){

  int y=0;
  for(; y < counter; y++){
    printf("%s | %d \n", myList[y].name, myList[y].size);
  }

}
