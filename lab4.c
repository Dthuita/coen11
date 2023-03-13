/*
  David Thuita
  COEN 11
  Lab 4
  Wednesday 5:15pm
*/
#include <stdio.h>
#include <string.h>

#define NAME 50

int counter=0;

typedef union Extras{
  char phone_num[10];
  int min_age;
  float avg_age;
}Extra;
typedef struct Lists{
  char name[NAME];
  int size;
  int max_age;
  Extra extra_info;
}List;

void insert();
void removeP();
void display();
void size_display();

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
   //enter name
   printf("enter name: ");
   scanf("%s", myList[counter].name);

   //enter size
   printf("enter size: ");
   scanf("%d", &myList[counter].size);
   while(myList[counter].size > 10){
     printf("re-enter size: ");
     scanf("%d", &myList[counter].size);
   }

   //enter union info
   int age=0;
   printf("enter max age: ");
   scanf("%d", &age);
   if(age < 18){
     printf("You are a MINOR. Enter parent's number: ");
     myList[counter].max_age = age;
     scanf("%s", myList[counter].extra_info.phone_num);
   }else if(age > 65){
     printf("You are a OLD. youngest person's age: ");
     myList[counter].max_age = age;
     scanf("%d", &myList[counter].extra_info.min_age);
   }else{
     printf("OK. Enter average age of group: ");
     myList[counter].max_age = age;
     scanf("%f", &myList[counter].extra_info.avg_age);
   }

   counter++;
}
void removeP(){
  //delete slots from top to bottom,
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
void size_display(){

  int rSize=0;
  printf("What size to display?");
  scanf("%d",&rSize);

  int p=0;
  for(; p < counter; p++){
    if(myList[p].size <= rSize){

      printf("%s | %d \n", myList[p].name, myList[p].size);

      if(myList[y].max_age < 18){
        printf("Max age: %d |", myList[y].max_age);
        printf("Phone num: %s \n", myList[y].extra_info.phone_num);
      }if(myList[y].max_age > 65){
        printf("Max age: %d |", myList[y].max_age);
        printf("min age: %d \n", myList[y].extra_info.min_age);
      }
      if(myList[y].max_age > 18 && myList[y].max_age < 65){
        printf("Max age: %d |", myList[y].max_age);
        printf("avg age: %f \n", myList[y].extra_info.avg_age);
      }
      
    }
  }
}
void display(){
  // add display of max age
  int y=0;
  for(; y < counter; y++){

    printf("%s | %d | ", myList[y].name, myList[y].size);

    if(myList[y].max_age < 18){
      printf("Max age: %d |", myList[y].max_age);
      printf("Phone num: %s \n", myList[y].extra_info.phone_num);
    }if(myList[y].max_age > 65){
      printf("Max age: %d |", myList[y].max_age);
      printf("min age: %d \n", myList[y].extra_info.min_age);
    }
    if(myList[y].max_age > 18 && myList[y].max_age < 65){
      printf("Max age: %d |", myList[y].max_age);
      printf("avg age: %f \n", myList[y].extra_info.avg_age);
    }

  }

}
