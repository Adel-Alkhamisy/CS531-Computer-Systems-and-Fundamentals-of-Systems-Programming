//
//  HW2.c
//  CS531_HW2
//
//  Created by ADEL ALKHAMISY on 3/12/22.
//


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAXLEN 100

void readDataOfFile(void);


struct address_t{
    int octet[4];
    char alias[11];
    struct address_t *next;
};
struct address_t *head=NULL;

void readDataFromFile(void);
void split_IPv4_alias_pair(char line[]);
void create_linked_list(char IPv4[], char alias[]);
void add_address(int ipv4);
bool look_up_address(char alias[]);
void update_address(char ipv4[], char alias[]);
void delete_address(char alias[]);
void displayList(void);
void display_aliases_for_location(void);
void save_to_file(void);


bool check_alias(char alias[]){ // search for alias
    struct address_t *p=head;
    int match;
    while (p != NULL) {
        match=strcmp(p->alias, alias);
        if (match==0) {
            printf("%s is already exist!\n",alias);
            return false;
        }
        p=p->next;
        
    }
    
    return true;
}
bool check_address_format(char IPv4[]){ // check address format.
    int address[4];
    sscanf(IPv4, "%d.%d.%d.%d", address, address + 1, address + 2, address + 3);
    if (address[0] ==-1 || address[1] ==-1|| address[2] ==-1|| address[3]==-1) {
        printf("%s is an illegal address\n",IPv4);
    }
    if( address[0]>255 || address[0]<0 || address[1]>255 || address[1]<0 || address[2]>255 || address[2]<0 || address[3]>255 || address[3]<0)
      {
        printf("%s is an illegal address\n",IPv4);
          return false;
      }
    return true;
}

bool check_address(char ipv4[]){
    struct address_t *p = head;
    int octet[4];
    sscanf(ipv4, "%d.%d.%d.%d",octet,octet+1,octet+2,octet+3);
    while(p != NULL)
    {
        int count = 0;
        for(int x = 0 ; x < 4 ; x++){
            if(octet[x] == p->octet[x])
                count++;
        }
        if(count == 4){
            printf("%s is already exist!\n",ipv4);
            return false;
        }
        p = p-> next;
    }
    return true;
}

bool look_up_address(char alias[]){ // check for address in the list
    struct address_t *p = head;
    while(p != NULL){
        int match;
        match= strcmp(p->alias, alias);
        if(match == 0){
            int x=0;
            printf("Address:");
            for(;x< 3 ; x++)
                printf("%d.",p->octet[x]);
            printf("%d\n", p->octet[x]);
            return true;
        }
        p = p->next;
    }
    printf("Error: %s does not exist!\n",alias);
    return false;
}

void display_aliases_for_location(void){ // display_aliases_for_location
    int x,y;
    printf(" Enter two values separated by space  (0-255): \n");
    scanf("%d %d", &x, &y);
    if((x > 255 || x < 0) || (y > 255 || y < 0)){
        printf("invalid number\n");
        return;
        
    }
    struct address_t *p = head;
    while(p != NULL){
        int i =0;
        if(p->octet[i] == x  && p->octet[i+1] == y)
            printf("%s \n", p->alias);
        p = p->next;
    }
}


void displayList(void){ // display list
    struct address_t *p=head;
    int count=0;
    if (p == NULL) {
        printf("List is empty!\n");
    }
    while (p != NULL) {
        int x=0;
        for(x=0 ; x< 3 ; x++)
            printf("%d.",p->octet[x]);
        printf("%d", p->octet[x]);
        printf(" %s",p->alias);
        printf("\n");
        p=p->next;
        count++;
        
    }
    printf("Total node count: %d\n",count);
}

void update_address(char ipv4[], char alias[]){ // update address
    struct address_t *p = head;
    int x[4];
    
    while(p != NULL)
    {
        int match = strcmp(p->alias,alias);
        if(match == 0)
        {
            sscanf(ipv4, "%d.%d.%d.%d", x, x + 1, x + 2, x + 3);
            while (x[0]>255 || x[0]<0 || x[1]>255 || x[1]<0 || x[2]>255 || x[2]<0 || x[3]>255 || x[3]<0) {
                printf("%s is an illegal address - please reenter:\n",ipv4);
                scanf("%s",ipv4);
                sscanf(ipv4, "%d.%d.%d.%d", x, x + 1, x + 2, x + 3);
            }
            sscanf(ipv4, "%d.%d.%d.%d", p->octet,p->octet+1,p->octet+2,p->octet+3);
            break;
        }
        p = p->next;
    }
}

/* Delete a node if it is exist*/
void delete_address(char alias[]){
    struct address_t *p = head;
    struct address_t *prev=NULL;
    struct address_t *curr = NULL;
    int match;
    match = strcmp(p->alias,alias);
    if(match == 0){
        head = p->next;
        free(head);
        return;
    }

    while(p != NULL){
        match = strcmp(p->alias,alias);
        if(match == 0){
            curr = p->next;
            prev->next = curr;
            free(p);
        }
        else{
            prev = p;
        }
        p = p->next;
    }
}

/* Create the Linked List and adds at the begining*/
void create_linked_list(char IPv4[], char alias[]){
    struct address_t *node = (struct address_t*) malloc(sizeof(struct address_t));
    sscanf(IPv4, "%d.%d.%d.%d", node->octet,node->octet+1,node->octet+2,node->octet+3);
    strcpy(node->alias,alias);
    node->next = head;
    head = node;
}

/* split IPv4 pair in two separate string and send them to create list function*/
void split_IPv4_alias_pair(char line[]){
    char IPv4[16];
    char alias[11];
    char *pt;
    sscanf(line, "%s %s",IPv4,alias);
    printf("%s %s\n",IPv4,alias);
    if ((pt=strchr(alias, '\n')) != NULL || (pt=strchr(alias, 13)) || (pt=strchr(alias, EOF)) != NULL){
        *pt = '\0';
    }
    create_linked_list(IPv4,alias);
}
/* This function read data from file*/
void readDataFromFile(void){
    char buffer[MAXLEN];
    FILE *file_ptr=fopen("CS531_Inet.txt", "r");
    if(file_ptr==NULL){
        printf("File does not exist!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(buffer,MAXLEN,file_ptr) != NULL)
    {
        split_IPv4_alias_pair(buffer);
    }
    fclose(file_ptr);
}

/* This function save data to file*/
void save_to_file(void){
    struct address_t *p = head;
    char fileName[30];
    printf("Enter file name (Example CS531.txt): ");
    scanf("%s",fileName);
    FILE *file_ptr=fopen(fileName, "w");
    if(file_ptr==NULL){
        printf("Unable to open file!\n");
        exit(EXIT_FAILURE);
    }
    while(p != NULL)
    {
        fprintf(file_ptr,"%d.%d.%d.%d %s",p->octet[0],p->octet[1],p->octet[2],p->octet[3], p->alias);
        fprintf(file_ptr,"\n");
        p = p->next;
    }
    fclose(file_ptr);
}

int main(){
    readDataFromFile();
    int option=0;
    char IPv4[16];
    char alias[11];
    int b[4];
    char aliasNull[12];
    while (option != 8) {
        printf("1) Add address\n");
        printf("2) Look up address\n");
        printf("3) Update address\n");
        printf("4) Delete address\n");
        printf("5) Display list\n");
        printf("6) Display aliases for location\n");
        printf("7) Save to file\n");
        printf("8) Quit\n");
        
        printf("Enter option:");
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                printf("Enter alias:");
                scanf("%s", alias);
                while(strlen(alias)>10){
                    printf("Invalid alias - please reenter:");
                    scanf("%s", alias);
                    getchar();
                }
                if(!check_alias(alias)){
                    break;
                }
                printf("Enter address for %s:",alias);
                scanf("%s", IPv4);
                sscanf(IPv4, "%d.%d.%d.%d", b, b + 1, b + 2, b + 3);
                
                while( b[0]>255 || b[0]<0 || b[1]>255 || b[1]<0 || b[2]>255 || b[2]<0 || b[3]>255 || b[3]<0)
                  {
                      printf("%s is an illegal address - please reenter:\n",IPv4);
                      scanf("%s", IPv4);
                      getchar();
                      sscanf(IPv4, "%d.%d.%d.%d", b, b + 1, b + 2, b + 3);
                  }
                if (!check_address(IPv4)) {
                    break;
                }
                if (check_alias(alias) && check_address(IPv4)) {
                    create_linked_list(IPv4, alias);
                    break;
                }
            
            case 2:
                printf("Enter alias: ");
                scanf("%s", alias);
                strcpy(aliasNull, strcat(alias, "\0"));
                look_up_address(aliasNull);
                break;
                
            case 3:
                printf("Enter alias: ");
                scanf("%s", alias);
                bool lookup_address = look_up_address(alias);
                if(lookup_address){
                    printf("Enter new address for %s:",alias);
                    scanf("%s", IPv4);
                    bool checkAddress = check_address(IPv4);
                    if(checkAddress)
                        update_address(IPv4,alias);
                }
                break;
                
            case 4:
                printf("Enter alias for deletion: ");
                scanf("%s", alias);
                lookup_address = look_up_address(alias);
                if(lookup_address)
                {
                    printf("Alias %s is deleted\n",alias);
                    delete_address(alias);
                }else{
                    displayList();
                }
                break;
                
            case 5:
                displayList();
                break;
            case 6:
                display_aliases_for_location();
                break;
            case 7:
                save_to_file();
                break;
            case 8:
                printf("Exit");
                break;
        }
    }
    
    }
