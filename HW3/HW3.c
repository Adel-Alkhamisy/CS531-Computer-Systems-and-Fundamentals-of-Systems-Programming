//
//  main.c
//  CS531_HW3_V3
//
//  Created by ADEL ALKHAMISY on 10/14/22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<stdbool.h>
#define MAXLEN 100

struct address_t{
    int octet[4];
    char alias[11];
    struct address_t *leftChild, *rightChild, *parent;
    int height, depth;
};

struct address_t *root=NULL;
int NodeHeight(struct address_t *p);
int NodeDepth(struct address_t *p);
bool check_address(char ipv4[],struct address_t *p);
bool lookup_alias(char alias[]);
bool look_up_address(char alias[]);
void add_address(struct address_t *t, char ipv4[], char alias[]);
void update_address(char ipv4[], char alias[]);
void display_aliases_for_location(struct address_t* t, int x, int y);
struct address_t* get_successor(struct address_t* p);
struct address_t* deleteAddress(struct address_t* t,char alias[]);
void split_IPv4_alias_pair(char line[]);
void readDataFromFile(void);
void save_to_file(struct address_t *p,FILE *filePath);
void displayList(struct address_t *p);







// to compute Height of a node in BST
int NodeHeight(struct address_t *p)
{
    if (p == NULL)
            return-1;
    else {
        /* compute the depth of each subtree */
        int ld = NodeHeight(p->leftChild);
        int rd = NodeHeight(p->rightChild);
     
        /* use the larger one */
        if (ld > rd)
            return (ld + 1);
        else
            return (rd + 1);
        }
}

// to compute node depth in BST
int NodeDepth(struct address_t *p)
{
    if(p==NULL)
        return 1;
    else
        return NodeDepth(p->parent)+1;
}

// if address found return true, otherwise return false
bool check_address(char ipv4[],struct address_t *p)
{
    if (p!=NULL) {
        char *pos;
        if ((pos=strchr(ipv4, '\n')) != NULL)
            *pos = '\0';
        int octet[4];
        sscanf(ipv4, "%d.%d.%d.%d",octet,octet+1,octet+2,octet+3);
        int count = 0;
        for(int x = 0 ; x < 4 ; x++){
            if(octet[x] == *(p->octet+x))
                count++;
        }
        if(count == 4){
            printf("%s is already exist!\n",ipv4);
            return true;
        }
        // using logical Or to cast the "true" if we found the address
        return check_address(ipv4, p->leftChild) ||  check_address(ipv4, p->rightChild);
    }
    
    return false;
}

// look up alias in BST, if alias found return true, otherwise return false
bool lookup_alias(char alias[]){
    struct address_t *t=root;
    
    while (t!=NULL) {
        if (strcmp(alias, t->alias)==0) {
            return true;
        }
        else if (strcmp(alias, t->alias)<0) {
            t=t->leftChild;
        }
        else {
            t=t->rightChild;
        }
    }
    return false;
}

// to look for address in the BST

bool look_up_address(char alias[]){
    struct address_t *t=root;
    struct address_t *r=NULL;
    char *pos;
    if ((pos=strchr(alias, '\n')) != NULL)
        *pos = '\0';
    
    while (t!=NULL) {
        r=t;
        if (strcmp(alias, t->alias)==0) {
            printf("The Address of alias %s: ",alias);
            int x=0;
            for(;x< 3 ; x++)
                printf("%d.",r->octet[x]);
            printf("%d\n", r->octet[x]);
            return true;
        }
        else if (strcmp(alias, t->alias)<0) {
            t=t->leftChild;
        }
        else {
            t=t->rightChild;
            
        }
    }
    printf("Error: %s does not exist!\n",alias);
    return false;
}
// to insert new node in BST
void add_address(struct address_t *t, char ipv4[], char alias[])
{
    struct address_t *r=NULL; struct address_t *newNode;
    int d=0;
    while (t!=NULL) {
        r=t;
        if (strcmp(alias, t->alias)==0) {
            printf("The alias %s is already exsits!\n",alias);
            return;
        }
        else if (strcmp(alias, t->alias)<0) {
            t=t->leftChild;
            d=d+1;
            r->height=NodeHeight(r);
        }
        else {
            t=t->rightChild;
            d=d+1;
            r->height=NodeHeight(r);
            
        }
        bool flag=check_address(ipv4,root);
        if (flag) {
            printf("The address is already exsits!\n");
            return;
        }
    }
    newNode=(struct address_t*) malloc(sizeof(struct address_t));
    sscanf(ipv4, "%d.%d.%d.%d", newNode->octet,newNode->octet+1,newNode->octet+2,newNode->octet+3);
    strcpy(newNode->alias,alias);
    newNode->leftChild=newNode->rightChild=NULL;
    newNode->parent=r;
    newNode->height=0;
    newNode->depth=d;
    
    if (root==NULL) {
        root=newNode;
    }
    else if (strcmp(newNode->alias, r->alias)<0) {
        r->leftChild=newNode;
    }
    else
    {
        r->rightChild=newNode;
        
    }
    
}

void update_address(char ipv4[], char alias[]){ // update address
    struct address_t *t=root;
    struct address_t *r=NULL;
    char *pos;
    if ((pos=strchr(alias, '\n')) != NULL)
        *pos = '\0';
    if (root==NULL) {
        printf("The BST is empty!");
        return;
    }
    int x[4];
    while (t!=NULL) {
        r=t;
        if (strcmp(alias, t->alias)==0) {
            sscanf(ipv4, "%d.%d.%d.%d", x, x + 1, x + 2, x + 3);
            while (x[0]>255 || x[0]<0 || x[1]>255 || x[1]<0 || x[2]>255 || x[2]<0 || x[3]>255 || x[3]<0) {
                printf("%s is an illegal address - please reenter:\n",ipv4);
                scanf("%s",ipv4);
                sscanf(ipv4, "%d.%d.%d.%d", x, x + 1, x + 2, x + 3);
            }
            bool flag=check_address(ipv4,root);
            if (flag) {
                printf("The address is already exsits!\n");
                return;
            }
            printf("The alias %s has been updated!\n",alias);
            printf("old address: %d.%d.%d.%d\n ",r->octet[0],r->octet[1],r->octet[2],r->octet[3]);
            sscanf(ipv4, "%d.%d.%d.%d", r->octet,r->octet+1,r->octet+2,r->octet+3);
            printf("new address: %d.%d.%d.%d \n",r->octet[0],r->octet[1],r->octet[2],r->octet[3]);
            break;
        }
        else if (strcmp(alias, t->alias)<0) {
            t=t->leftChild;
        }
        else {
            t=t->rightChild;
            
        }
    }
    if (t==NULL) {
        printf("The alias %s doesn't exist!\n",alias);
    }
}
void display_aliases_for_location(struct address_t* t, int x, int y){ // display_aliases_for_location
    
    if (t)
    {
        int i =0;
        if(t->octet[0]==x && t->octet[i+1]==y ){
            printf("%s \n", t->alias);
        }
        display_aliases_for_location(t->leftChild,x,y);
        display_aliases_for_location(t->rightChild,x,y);
    }
}


// find leftmost node in BST (successor)
struct address_t* get_successor(struct address_t* p)
{
    struct address_t* t = p;
  
    while (t && t->leftChild != NULL)
        t = t->leftChild;
  
    return t;
}

// to delete a node
 struct address_t* deleteAddress(struct address_t* t,char alias[])
{

    if (root==NULL) {
        printf("BST is empty!");
        return NULL;
    }
    if(t == NULL){
        printf("BST is empty!");
        return NULL;
    }


    int diff = strcmp(alias,(t)->alias);
    if (diff > 0)
        t->rightChild = deleteAddress(t->rightChild, alias);
    else if(diff < 0)
        t->leftChild = deleteAddress(t->leftChild, alias);
    else
    {

        if(t->leftChild == NULL && t->rightChild == NULL)
        {
            
            free(t);
            return NULL;
        }


        else if(t->leftChild == NULL || t->rightChild == NULL)
        {
            struct address_t *temp;
            if(t->leftChild == NULL)
                temp = t->rightChild;
            else
                temp = t->leftChild;
            free(t);
            return temp;
        }

        else
        {
            struct address_t *succ = get_successor(t->rightChild);
            strcpy(t->alias,succ->alias);
            for (int i=0; i<4; i++) {
                t->octet[i]=succ->octet[i];
            }
            t->rightChild = deleteAddress(t->rightChild, succ->alias);
        }
    }
    return t;
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
    add_address(root,IPv4,alias);
}


// read data from file
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
void save_to_file(struct address_t *p,FILE *filePath){
    if (root == NULL) {
        printf("List is empty!\n");
        return;;
    }
    if (p) {
        save_to_file(p->leftChild,filePath);
        fprintf(filePath,"%d.%d.%d.%d %s",p->octet[0],p->octet[1],p->octet[2],p->octet[3], p->alias);
        fprintf(filePath,"\n");
        save_to_file(p->rightChild,filePath);
    }
    
}

void displayList(struct address_t *p){
    if (root == NULL) {
        printf("List is empty!\n");
        return;;
    }
    
    if(p)
    {
        displayList(p->leftChild);
        
        printf("%s ",p->alias);
        
        int x=0;
        for(x=0 ; x< 3 ; x++)
            printf("%d.",p->octet[x]);
        printf("%d", p->octet[x]);
        printf("  height: %d",p->height);
        printf("  depth: %d",p->depth);
        if(p->parent!=NULL) {
            printf("  parent: %s",p->parent->alias);
        }
        else if(p->parent==NULL)
        {
            printf("  parent: NONE");
        }
        printf("\n");
        
        displayList(p->rightChild);
    }
}

int main(){
    readDataFromFile();
    displayList(root);
    int option=0;
    char filePath[30];
    char IPv4[16];
    char alias[11];
    int b[4];
    char aliasNull[12];
    int x,y;
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
                printf("Enter alias: ");
                scanf("%s", alias);
                while(strlen(alias)>10){
                    printf("Invalid alias - please reenter:");
                    scanf("%s", alias);
                    getchar();
                }
                printf("Enter IPv4 address: ");
                scanf("%s", IPv4);
                sscanf(IPv4, "%d.%d.%d.%d", b, b + 1, b + 2, b + 3);

                while( b[0]>255 || b[0]<0 || b[1]>255 || b[1]<0 || b[2]>255 || b[2]<0 || b[3]>255 || b[3]<0)
                  {
                      printf("%s is an illegal address - please reenter:\n",IPv4);
                      scanf("%s", IPv4);
                      getchar();
                      sscanf(IPv4, "%d.%d.%d.%d", b, b + 1, b + 2, b + 3);
                  }
                    add_address(root, IPv4, alias);
                    break;
//
            case 2:
                printf("Enter alias: ");
                scanf("%s", alias);
                strcpy(aliasNull, strcat(alias, "\0"));
                look_up_address(aliasNull);
                break;
//
            case 3:
                printf("Enter alias: ");
                scanf("%s", alias);
                printf("Enter new address for %s:",alias);
                scanf("%s", IPv4);
                update_address(IPv4,alias);
                break;
                
            case 4:
                printf("Enter alias for deletion: ");
                scanf("%s", alias);
                getchar();
                bool flag=lookup_alias(alias);
                if (flag) {
                    printf("do you want to delete %s?(y/n)",alias);
                    char command[4];
                   scanf("%s",command);
                    if (strcmp(command, "y")==0) {
                        struct address_t* temp=deleteAddress(root, alias);
                        printf("Alias %s with address %d.%d.%d.%d is deleted\n",alias,temp->octet[0],temp->octet[1],temp->octet[2],temp->octet[3]);
                    }
                
                }
                else{
                    printf("%s doesn't exist!",alias);
                }
                
                displayList(root);
                
                break;
//
                case 5:
                    displayList(root);
                break;
            case 6:
                printf(" Enter two values separated by space  (0-255):");
                scanf("%d %d", &x, &y);
                while((x > 255 || x < 0) || (y > 255 || y < 0)){
                    printf("invalid number\n");
                    printf(" Enter two values separated by space  (0-255): \n");
                    scanf("%d %d", &x, &y);
                }
                display_aliases_for_location(root,x,y);
                break;
                case 7:
                  printf("Enter file name (Example CS531.txt): ");
                  scanf("%s",filePath);
                  FILE *file_ptr=fopen(filePath, "w");
                  if(file_ptr==NULL){
                      printf("Unable to open file!\n");
                      exit(EXIT_FAILURE);
                    }
                    save_to_file(root,file_ptr);
                    fclose(file_ptr);
                break;
            case 8:
                printf("Goodbye!\n");
                break;
        }
    }
    
}
