#include <malloc.h>

typedef struct LinkedList{
    
    int val;
    struct LinkedList *next;

}LinkedList;

void addClient(LinkedList *root, int client){

    if(root == NULL){
        root = (LinkedList*)malloc(sizeof(LinkedList));
        root->val = client;
        root->next = NULL;
        return;
    }

    LinkedList *temp = root;

    while(temp != NULL){
        temp = temp->next;
    }

    temp = (LinkedList*)malloc(sizeof(LinkedList));
    temp->val = client;
    temp->next = NULL;

}