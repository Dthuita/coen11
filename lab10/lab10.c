/*
  David Thuita
  COEN 11
  Lab 7
  Wednesday 5:15pm
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NAME 50

typedef struct Node{
  char name[NAME];
  int size;
  struct Node *next;
}Node;

Node *head = NULL;// create and allocate
Node *tail = NULL;// create and allocate


pthread_mutex_t lock;

void *auto_save_thread(void *arg){
    char *b_file = (char*) arg;
    while(1){ //infinite loop

        sleep(15); //sleep for 15 sec

        pthread_mutex_lock(&lock); //lock values

        FILE *fptr= fopen(b_file,"wb");//open file
        
        Node *temp;
        temp = head;
        while(temp){//put nodes into binary file
            fwrite(temp, sizeof(Node*), 1, fptr);
            temp = temp->next;
        }
        fclose(fptr);//close file
        pthread_mutex_unlock(&lock); //unlock values
        printf("\n**auto saved complete** \n");
    }
        
}
int main(int argc, char *argv[]){

  //check if file exists
  if(argc == 1){
      printf("NO FILE DETECTED");
      return 1;
  }
  //read file, send file to read function
  read_file( argv[1] );

  //pthread mutex initialize
  if( pthread_mutex_init(&lock, NULL) == 2 ){
    printf("mutex lock not made");
  }

  //create and start pthread
  pthread_t a_save;
  pthread_create(&a_save, NULL, auto_save_thread, argv[2]);

  char cmd;
  char name[10];
  int s=0;

  while(1){

    printf("a-insert, r-remove, d-display, s-size, q-quit, o-read binary \n");
    printf("b-backward list, n-backward name, Enter command: ");
    scanf(" %c%*c", &cmd);//why?????

    switch(cmd){
      case 'a':
            pthread_mutex_lock(&lock); //lock values
            printf("enter name: ");
            scanf("%s", name);
            printf("enter size: ");
            scanf("%d", &s );
            check_duplicate(name);//check for dulicaptes
            insert(name, s);
            pthread_mutex_unlock(&lock); //unlock values
            break;
      case 'd':
            pthread_mutex_lock(&lock); //lock values
            display();
            pthread_mutex_unlock(&lock); //unlock values
            break;
      case 'r':
            pthread_mutex_lock(&lock); //lock values
            removeP();
            pthread_mutex_unlock(&lock); //unlock values
            break;
      case 's': //size command
            pthread_mutex_lock(&lock); //lock values
            size_display();
            pthread_mutex_unlock(&lock); //unlock values
            break;
      case 'b': //print list backwards
            pthread_mutex_lock(&lock); //lock values
            backward_display(head);
            pthread_mutex_unlock(&lock); //unlock values
            break;
      case 'n': //reverse name letter
            pthread_mutex_lock(&lock); //lock values
            reverse_dis();
            pthread_mutex_unlock(&lock); //unlock values
            break;
      case 'o': //read bin file
            pthread_mutex_lock(&lock); //lock values
            binary_dis(argv[2]);
            pthread_mutex_unlock(&lock); //unlock values
            break;
      case 'q':
            pthread_cancel(a_save);
            pthread_mutex_lock(&lock); //lock values
            quit_save(argv[1]);
            pthread_mutex_unlock(&lock); //unlock values
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
void binary_dis(char *file){

    //open and read file
    FILE *fptr = fopen(file, "r"); 

    Node* temp;
    temp = head;
    while(temp){
        fread(temp, sizeof(Node*), 1, fptr);
        printf("%s | %d \n", temp->name, temp->size);
        temp = temp->next;
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

