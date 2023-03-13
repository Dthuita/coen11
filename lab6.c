/*
 * David Thuita
 * COEN 11
 * Lab 6 
 * Wednesday 5:15pm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char name[10];
    int size;
    struct Node *next;
}NODE;
typedef struct List{
    NODE *head;
    NODE *tail;
}LIST;
//create array and inizitalie array with head and tail nodes
LIST list_array[4]= {{NULL,NULL}, {NULL, NULL}, {NULL,NULL}, {NULL,NULL}};



//prototypes
void insert();
void opening();
void display();
void size_display();
void quit_free();
void check_duplicate(char name[10], int z);

int main(){
    
    int cmd;
    while(1){

        printf("1-insert, 2-opening, 3-display, 4-size, 0-quit \n");
        printf("Enter command: ");
        scanf("%d", &cmd);

        switch(cmd){
            case 1:
                insert();
                break;
            case 2:
                opening();
                break;
            case 3:
                display();
                break;
            case 4:
                size_display();
                break;
            case 0:
                quit_free();
                return(0);
                break;
            default:
                printf("Invalid command. Try again \n\n");
                break;

        }
    }

}
void insert(){

    //enter info
    int s=0; char name[10];
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter size: ");
    scanf("%d", &s);

    //checks for duplicates
    //check_duplicate(name); -> need to write

    //creates and iniztiles new node
    NODE *n = malloc(sizeof(NODE));
    strcpy( n->name, name);
    n->size = s;
    n->next = NULL;

    //find the array spot
    switch(s){
        case 1://fill for size 1-2
        case 2:
                check_duplicate(name, 0);
                if(list_array[0].head == NULL && list_array[0].tail == NULL){
                    list_array[0].tail = n;
                    list_array[0].head = n;
                }else{
                    list_array[0].tail->next = n;
                    list_array[0].tail = n;
                }
                break;
        case 3://fill for size 3-4
        case 4:
                check_duplicate(name, 1);
                if(list_array[1].head == NULL && list_array[1].tail == NULL){
                    list_array[1].tail = n;
                    list_array[1].head = n;
                }else{
                    list_array[1].tail->next = n;
                    list_array[1].tail = n;
                }
                break;
        case 5://fill for size 5-6
        case 6:
                check_duplicate(name, 2);
                if(list_array[2].head == NULL && list_array[2].tail == NULL){
                    list_array[2].tail = n;
                    list_array[2].head = n;
                }else{
                    list_array[2].tail->next = n;
                    list_array[2].tail = n;
                }
                break;
        default: //fill for size >6
                check_duplicate(name, 3);
                if(list_array[3].head == NULL && list_array[3].tail == NULL){
                    list_array[3].tail = n;
                    list_array[3].head = n;
                }else{
                    list_array[3].tail->next = n;
                    list_array[3].tail = n;
                }
                break;
        }
        
}
void opening(){

  int rSize;
  printf("enter size for removal: ");
  scanf("%d", &rSize);

  int p=0;
  //check size
  if(rSize <= 2){
    p=0;
  }if(rSize <= 4){
    p=1;
  }if(rSize <= 6){
    p=2;
  }if(rSize > 6){
    p=3;
  }

  //erase spot
  NODE *temp;
  NODE *p_temp;

  int sum = rSize; //sum of sizes top to bottom being deleted

  int z=0;
  for(;z <= p; z++){
     temp = list_array[z].head;
     p_temp = list_array[z].head;

     while(temp != NULL){
       if(temp->size <= sum && sum > 0){

         sum -= temp->size;//sub from total

         //middle, temp is beginning, end of list, special->one node
         if(list_array[z].head == list_array[z].tail){ //only one node in list
             free(temp);
             list_array[z].head = list_array[z].tail = NULL;
             break;
          }else if(list_array[z].head == temp){//node in beginning of list
             list_array[z].head = temp->next;
             free(temp);
             temp = p_temp = list_array[z].head;
          }else if(temp == list_array[z].tail){//node at end of list
             p_temp->next = NULL;
             free(temp);
             list_array[z].tail = p_temp;
             break;
          }else{ //node in middle of list
             p_temp->next = temp->next;
             free(temp);
             temp= p_temp->next;
          }
        }else{
          p_temp = temp;
          temp = temp->next;
        }
     }
  }

}
void check_duplicate(char name[10], int z){
  NODE *temp;

  temp = list_array[z].head;
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
    
  printf("size entered: %d \n", rSize);

  int z=0;
  if(rSize <= 2){
    z=0;
  }if(rSize > 2  && rSize <= 4 ){
    z=1;
  }if(rSize > 4 && rSize <= 6){
    z=2;
  }if(rSize > 6){
    z=3;
  }

  printf("size selected: %d \n", z);

  NODE *temp; 
    temp = list_array[z].head;
    while(temp){
        printf("%s | %d \n", temp->name, temp->size);
        temp = temp->next;
    }

}
void quit_free(){
  NODE *temp1, *temp2;
  int z=0;
  for(;z < 3; z++){
    temp1 = list_array[z].head;
    while(temp1){
        temp2 = temp1->next;
        free(temp1);
        temp1 = temp2;
    }
  }
}
void display(){
  NODE *temp;
  int z=0;
  for(;z < 4; z++){
    temp = list_array[z].head;
    while(temp){
        printf("%s | %d | %d  \n", temp->name, temp->size, z);
        temp = temp->next;
    }
  }
}
