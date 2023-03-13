/*
  David Thuita
  COEN 11
  Lab 5
  Wednesday 5:15pm
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME 50

typedef struct Node{
  char name[NAME];
  int size;
  struct Node *next;
}Node;

Node *head = NULL;// create and allocate
Node *tail = NULL;// create and allocate


void insert();
void removeP();
void display();
void size_display();
void check_duplicate(char name[10]);

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

  //enter info
  int s=0; char name[10];
  printf("enter name: ");
  scanf("%s", name);
  printf("enter size: ");
  scanf("%d", &s );

  check_duplicate(name);

  //create and iniliztize new node
  Node *n = malloc(sizeof(Node));
  strcpy(n->name,name);
  n->size = s;
  n->next = NULL;

  //head and tail are empty(beginning list) put new node as both
  if(head == NULL && tail == NULL){
    tail = n;
    head = n;
    return;
  }else{
    tail->next = n; //gives values of n to tail next
    tail = n; //sets tail to n position
  }

}
void removeP(){

  int rSize;
  printf("enter size for removal: ");
  scanf("%d", &rSize);

  //erase spot
  Node *temp;
  Node *p_temp;

  temp = head;
  p_temp = head;

  int sum = rSize; //sum of sizes top to bottom being deleted

  while(temp != NULL){
    if(temp->size <= sum && sum > 0){

      sum -= temp->size;

      //middle, temp is beginning, end of list, special->one node
      if(head == tail){ //only one node in list
        free(temp);
        head = tail = NULL;
        return;
      }else if(head == temp){//node in beginning of list
        head = temp->next;
        free(temp);
        temp = p_temp = head;
      }else if(temp == tail){//node at end of list
        p_temp->next = NULL;
        free(temp);
        return;
      }else{ //node in middle of list
        p_temp->next = temp->next;
        free(temp);
        temp= p_temp->next;
      }
    }
    else{
      p_temp = temp;
      temp = temp->next;
    }
  }
}
void check_duplicate(char name[10]){
  Node *temp;

  temp = head;
  while(temp){ //cycle through list
      while( strcmp(temp->name, name) == 0 ){ //wait till input is not same
        printf("Already have that name. re-enter name: ");
        scanf("%s", name);
      }
    temp = temp->next;
  }

}
void size_display(){

  int rSize=0;
  printf("What size to display?");
  scanf("%d",&rSize);

  Node *temp;
  temp = head;

  while(temp){
    if(temp->size == rSize){
      printf("%s | %d \n", temp->name, temp->size);
      return;
    }
    temp = temp->next;
  }

}
void display(){
  Node *temp;
  temp = head;
  while(temp){
    printf("%s | %d \n", temp->name, temp->size);
    temp = temp->next;
  }
}
