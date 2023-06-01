/*
* main.c
* HW1
*
* Created by ADEL HAMAD H ALKHAMISY on 2/9/22.
* 
*/

/*
* This program asks the user to enter 10 strings. Then, it stores the strings in an array of characters
* and sorts
* the array in ascending or descending order according to the user specification. Also, it prints the string
* with the lowest and highest ascii values.
*The program rejects:
* 1. Strings less than 2 or greater than 25
* 2. A duplicated string.
* 3. string that contains ’!’, ’@’, ’#’, ’$’, ‘%’, ‘^’, ’(’, or ’)’
*
**/
#include <stdio.h>
#include <string.h>

/*Ask the user to enter 10 character strings*/
void inputStings(void);

/*Check string length to make sure it is within [2...25]*/
int checkStringLen(char str[]);

/* Ensure no illegal characters are accepted: ’!’, ’@’, ’#’, ’$’, ‘%’, ‘^’, ’(’, or ’)’ */
int checkLegalCharacters(char str[]);

/* Ensure no duplicate strings are accepted*/
int checkDuplicate(char str[]);

/* Sort and display the output*/
void ascendingORdescendingSort(char sortOrder);

/* print array of character*/
void printArray(char x);
/* Two dimensional Array of character to store 10 strings each one with a length of 26 char*/
char str[10][26];

int main(void) {
    /* choiceOfOrder is a variable to store the value A or D which is the user choice of Ascending (A) or Descending (D)*/
    char choiceOfOrder[26];
    printf("Enter 10 Character Strings: \n");
    /* Call to inputStings() function that deal with inserting a new string in str[10][26] array of characters*/
    inputStings();
    
    printf("Please enter character A(for Ascending) or D(for Descending)\n");
    printf("Print character strings in Ascending or Descending order: ");
    scanf("%s",choiceOfOrder);
    
    if(choiceOfOrder[0]=='A' || choiceOfOrder[0]=='D'){
        ascendingORdescendingSort(choiceOfOrder[0]);
        /* print array*/
        if(choiceOfOrder[0]=='A'){
            printArray(choiceOfOrder[0]);
        }
        if (choiceOfOrder[0]=='D'){
            printArray(choiceOfOrder[0]);
        }
    }else{
        while(choiceOfOrder[0]!='A' && choiceOfOrder[0]!='D'){
        printf("Error: Please enter character A(for Ascending) or D(for Descending): ");
            
            scanf("%s",choiceOfOrder);
        }
        ascendingORdescendingSort(choiceOfOrder[0]);
        /* print array*/
        if(choiceOfOrder[0]=='A'){
            printArray(choiceOfOrder[0]);
        }
        if (choiceOfOrder[0]=='D'){
            printArray(choiceOfOrder[0]);
        }
        
    }
    
    /* Call to ascendingORdescendingSort() function to order the strings in an ascending order, so the String
     * with lowest ascii value will be the first string in str array, and String with highest ascii value will
     * be the last string in array*/
    ascendingORdescendingSort('A');
    printf("String with lowest ascii value: %s", str[0]);
    printf("String with highest ascii value: %s", str[9]);
    
    return 0;
}


/*
 * Function:  inputStings()
 * -------------------------
 * it asks the user to enter 10 character strings, then it will make calls to the following functions before
 * entering the new string in the array of characters:
 * 1. int checkStringLen(char str[]), to make sure the entered stings length between [2,25] characters.
 *      It will return 0 if the string is empty or it contains characters <2 or > 25. Then inputStings() will
 *      keep asking the user to enter a new string.
 * 2. int checkLegalCharacters(char str[]), to make sure there is no illegal character in the string.
 *        If there are illegal character, it
 *        will show an error message, and inputStings() will ask the user to enter a new string.
 * 3. int checkDuplicate(char str[]), to make sure there is no duplicate string. If there is a duplicate string,
 *        it will show an error message and inputStings() will ask the user to enter a new string.
 *
 * Finally, if the new string passed all the previous  functions call without an error,
 * inputStings() will enter the new string in the next available
 * cell in str[2][26] array of characters.
 *
 *  Parameters: Void
 *
 *  return: Void
 *
 *
 */

void inputStings(void){
    char temp[100];
    int length;
    int legalChar;
    int flag;
    for(int i=0; i<10; i++){
        
    
        printf(" Enter string %d: ",i+1);
        fgets(temp, sizeof(temp), stdin);
        /* Check string length*/
        length=checkStringLen(temp);
        /* Check if string has illegal characters*/
        legalChar=checkLegalCharacters(temp);
        /*Check if the string already exists*/
        flag=checkDuplicate(temp);
        while(length==0 || legalChar==0 || flag==0){
            if(length==0){
            printf(" Enter string %d: ",i+1);
                fgets(temp, sizeof(temp), stdin);
                
                /* Reset variable length */
                length=checkStringLen(temp);
                /* Reset variable legalChar */
                legalChar=checkLegalCharacters(temp);
                /* Reset variable flag*/
                flag=checkDuplicate(temp);
            }
            if(legalChar==0){
                printf(" Enter string %d: ",i+1);
                fgets(temp, sizeof(temp), stdin);
                
                /* Reset variable length */
                length=checkStringLen(temp);
                /* Reset variable legalChar */
                legalChar=checkLegalCharacters(temp);
                /* Reset variable flag*/
                flag=checkDuplicate(temp);
            }
            if(flag==0){
                printf(" Enter string %d: ",i+1);
                fgets(temp, sizeof(temp), stdin);
                /* Reset variable length */
                length=checkStringLen(temp);
                /* Reset variable legalChar */
                legalChar=checkLegalCharacters(temp);
                /* Reset variable flag*/
                flag=checkDuplicate(temp);
            }
            
        }
        /* Store the string in the array if its length between [2-25], does not have illegal characters,
         * and unique*/
        if(length!=0 && legalChar != 0 && flag==1){
            strcpy(&str[i][0],temp);
        }
    
    
    }
}


/*
 * Function: int checkStringLen(char str[])
 *-----------------------------------------
 * It Checks the string length to make sure it is within [2...25] characters.
 * It returns 0 if it finds '\n' or '\0' in the first index or if the string length is less than 2 or
 * greater than 25. Otherwise, it returns 1.
 *
 * Parameters: str[], the array of characters that will be checked.
 *
 * return: zero if it finds '\n' or '\0' in the first index or if the string length <2 or greater than 25.
 *  Otherwise, it return 1.
 */
int checkStringLen(char str[]){
    int strLength;
    strLength=(int)strlen(str);
    if(str[0]=='\n'|| str[0]=='\0'){
        printf("Empty String: Please enter a string \n");
        return 0;
    }
    /* Numbers 3 and 26 used instead of 2 and 25 because the string contains '\n' at the end of string*/
    if((strLength<3 || strLength>26)){
        printf("Error: string should be between [2..25] character - please re-enter \n");
        return 0;
    }
    else{
        return 1;
    }
    
}



/*
 * Function: int int checkLegalCharacters(char x[])
 *-----------------------------------------
 * It searches the string for illegal characters: ’!’, ’@’, ’#’, ’$’, ‘%’, ‘^’, ’(’, or ’)’, if an illegal
 * character is found in the string, it will show an error message to the user and return 0.
 * Otherwise, it returns 1.
 *
 * Parameters: x[], the array of characters that will be checked.
 *
 * return: zero if it finds any illegal character. Otherwise, it returns 1.
 */

int checkLegalCharacters(char x[]){

    
    for(int i=0; i<strlen(x);i++){
        if(x[i]=='!' || x[i]=='@' || x[i]=='#' || x[i]=='$' || x[i]=='%' || x[i]=='^' || x[i]=='(' || x[i]==')'){
            printf("Error: %c is an illegal character - please re-enter \n", x[i]);
            return 0;
            break;
        }
    }
    return 1;
}



/*
 * Function: int checkDuplicate(char a[])
 *-----------------------------------------
 * It checks the string to make sure there is no duplicated string. If there is a duplicate string,
 * it will show an error message
 *      and returns 0. Otherwise, it returns 1.
 *
 * Parameters: a[], the array of characters that will be checked.
 *
 * return: zero if the new string already exists in str[10][26]. Otherwise, it returns 1.
 */

int checkDuplicate(char a[]){
    char b[26];
    strcpy(b,a);
    for(int i=0;i<10;i++){
        if(strcmp(b, str[i])==0){
            printf("Error: duplicate string - please re-enter \n");
            return 0;
        }
    }
    return 1;
}



/*
 * Function: void ascendingORdescendingSort(char sortOrder)
 *--------------------------------------------------------
 * It sorts the str[10][26] array in either ascending or descending order according to the user specification.
 * It utilizes the Bubble Sort algorithm to sort the array. If it receives 'A', then it sorts the array
 * in ascending order. If it receives 'D', then it sorts the array in descending order.
 *
 * Parameters: char sortOrder, it is either 'A' for ascending sort or 'D' for descending sort.
 *
 * return: void.
 */

void ascendingORdescendingSort(char sortOrder){
    char temp[26];
    switch(sortOrder){
        case 'A':
            /* Sort array*/
            for(int x=0;x<10;x++){
                for(int y=0;y<10-x-1; y++){
                        if(strcmp(str[y],str[y+1])>0)
                            {
                                /* Swap */
                                strcpy(temp,str[y]);
                                strcpy(str[y],str[y+1]);
                                strcpy(str[y+1],temp);
                            }
                    }
            }
            break;
            
        case 'D':
            /* Sort array*/
            for(int x=0;x<10;x++){
                for(int y=0;y<10-x-1; y++){
                        if(strcmp(str[y],str[y+1])<0)
                            {
                                /* Swap */
                                strcpy(temp,str[y]);
                                strcpy(str[y],str[y+1]);
                                strcpy(str[y+1],temp);
                            }
                    }
            }
            break;
            
    }
}
/* Print array*/
void printArray(char x){
    if(x=='A'){
        printf("Ascending Order:\n");
        printf("------------------\n");
    }
    if(x=='D'){
        printf("Descending Order:\n");
        printf("------------------\n");
    }
    /* Display array*/
    for(int i=0;i<10;i++){
        printf("%s", str[i]);
    }
}

