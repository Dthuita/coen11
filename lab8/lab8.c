/*
  David Thuita
  COEN 11
  Lab 7
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


void insert(char *nam, int num);
void removeP();
void display();
void size_display();
void check_duplicate(char name[10]);
void read_file(char *file);
void quit_save(char *file);
void quit_recursion(Node *p);
void backward_display(Node *p);
void reverse_name(char *str);
void reverse_dis();


int main(int argc, char *argv[]){

  //check if file exists
  if(argc == 1){
      printf("NO FILE DETECTED");
      return 1;
  }
  //read file, send file to read function
  read_file(argv[1]);

  char cmd;
  char name[10];
  int s=0;

  while(1){

    printf("a-insert, r-remove, d-display, s-size, q-quit \n");
    printf("b-backward list, n-backward name, Enter command: ");
    scanf(" %c%*c", &cmd);//why?????

    switch(cmd){
      case 'a':
            printf("enter name: ");
            scanf("%s", name);
            printf("enter size: ");
            scanf("%d", &s );
            check_duplicate(name);//check for dulicaptes
            insert(name, s);
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
      case 'b': //print list backwards
            backward_display(head);
            break;
      case 'n': //reverse name letter
            reverse_dis();
            break;
      case 'q':
            quit_save(argv[1]);
            return(0);
            break;
      default:
            printf("Invalid command. Try again.\n\n");
            break;
    }

  }

}
void read_file(char *file){

    //open and read file
    FILE *fptr = fopen(file, "r");
    
    char ch[10]; int num;

    while( fscanf(fptr,"%s %d", ch, &num) == 2){
        check_duplicate(ch);//check duplicates
        insert(ch, num);//insert file info into nodes
    }
    
    fclose(fptr);
}
void insert(char *name, int s){

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
void backward_display(Node *p){
  if(p == NULL)
      return;
  if(p != NULL){
    backward_display(p->next);
    printf("%s | %d \n", p->name, p->size);
  }
}
void reverse_dis(){
  Node *temp;
  temp = head;
  while(temp){
    reverse_name(temp->name);
    printf("| %d \n", temp->size);
    temp = temp->next;
  }
}
void reverse_name(char *str){
  if(*str == '\0')
      return;
  if(*str != '\0'){
      reverse_name( str+1 );
      printf("%c", *str);
  }
}
void quit_save(char *file){

    //open and save file
    FILE *fptr = fopen(file, "w");
    
    char ch[10]; int num;

    Node *temp;
    temp = head;
    while(temp){
        fprintf(fptr, "%s %d \n", temp->name, temp->size); 
        temp = temp->next;
    }
    fclose(fptr);

    //free nodes
    quit_recursion(head);
}
void quit_recursion(Node *p){
  if(p == NULL)
      return;
  if(p != NULL){
    quit_recursion(p->next);
    free(p);
  }
}

