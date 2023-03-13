/* David Thuita
 * COEN 11
 * Lab 1
 * Wednesday 5:15pm
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int division(int divisor,int quotient);

int main(){

    int divisor, quotient;
    srand((int)time(NULL));

    int i;
    for(i=0; i < 10; i++){
       divisor = rand() % 12 +1;
       quotient = rand() % 13;

       if( division(divisor, quotient) != 0 ){
           printf("Correct \n");
       }else{
           printf("Incorrect. %d is the correct answer \n", quotient);                                                  
       }           
    }
    
    return 0;
}
int division(int divisor,int quotient){
    int dividend = quotient*divisor;
    int ans;

    printf("%d divided by %d is what?\n", dividend, divisor);
    scanf("%d", &ans);

    if(ans == quotient){
        return 1;
    }else{
        return 0;
    } 
}
