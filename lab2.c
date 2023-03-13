#include <stdio.h>

char *name[10];
int size[10];
int counter;

void insert();
void removeP();
void display();

int main()
{
       int x=0;
       while(x < 1){
           char ans;
           printf("a-insert, r-remove, d-display, q-quit,  Enter command: ");
           scanf("%c%*c", &ans);
           
           if( strcmp(ans,"a") == 0 ){
              //insert();
           }
           if( strcmp(ans,"r") == 0 ){
               //removeP();
           }
           if( strcmp(ans,"d") == 0 ){
               //display();
           }
           if( strcmp(ans,"q") == 0 ){
               x=1;
           }
           //printf("%c", ans);
           //ans = "";
       }
}

void insert(){

    //enter info
    printf("enter name: " );
    scanf("%c", name[counter]);
    printf("enter size: ");
    scanf("%d", size[counter]);
}
void removeP(){

    int rSize;
    printf("enter size for removal: ");
    scanf("%d", rSize);
    
    //erase spot
    int p=0;
    for(; p < counter; p++){

        if(size[p] == rSize){
            size[p] = 0;
            name[p] = " ";
        }
    }
    //shift array
    int k = counter;
    for(; k > 0; k--){
        name[k] = name[k-1];
        size[k] = size[k-1];
    }
}
void display(){
    
    int y=0;
    for(; y < counter; y++){
        printf("%c | %d", name[y], size[y]);
    }
}
