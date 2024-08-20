#include <stdio.h>
#include <malloc.h>

typedef struct Node Node;
struct Node{
    int data;
    Node *next;
};
Node *head = NULL;
Node *last = NULL; // always point at the end of the linked list
int linkedListSize = 0; // IDK, if this the best practice but I'll see
int valid_position(int pos){
    // linkedListSize+1 cus you might add something at the end using insert_th_position()
    // ignore the comment at line 13 #fixed in insert_th_position()
    if(pos > linkedListSize || pos <= 0) return 0;
    return 1;
}
int insert_begin(int num){
    Node* new_node = malloc(sizeof(Node));
    if(new_node == NULL){
        printf("Memory is full\n");
        return 0;
    }
    new_node->data = num;
    new_node->next = head;
    head = new_node;
    linkedListSize++;
    return 1;
}
int insert_end(int num){
    // in constant time
    Node* new_node = malloc(sizeof(Node));
    // faild to allocate memory in the heap.
    if(new_node == NULL){
        printf("Memory is full\n");
        return 0;
    }
    new_node->data = num;
    new_node->next = NULL;

    // if linkedList is empty
    if(head == NULL) {
        head = new_node;
        last = new_node;
        linkedListSize++;
        return 1;
    }

    // if Not empty
    last->next = new_node;
    last = new_node;
    linkedListSize++;
    return 1;
}
int insert_th_position(int num, int pos){
    if(pos == linkedListSize+1) return insert_end(num); // at the end
    else if(pos == 1) return insert_begin(num); // at beginning
    else if(!valid_position(pos)) return 0; // invalid position.
    

    // our new node.
    Node* new_node = malloc(sizeof(Node));
    if(new_node == NULL){
        printf("Memory is full\n");
        return 0;
    }
    new_node->data = num;

    // first position
    if(pos == 1){
        new_node->next = head;
        head = new_node;
        linkedListSize++;
        return 1;
    }

    // any position
    Node* current = head;
    for(int i = 0; i < pos-2;i++){
        // current has to reach the previous node from the given position
        // that's why i<pos-2
        // cus pos-2 has the address of pos-1
        // after this loop, current will equal to (pos-1)
        current = current->next;
    }

    // connecting the new node to the rest of the chain.
    // [new node]
    // head->[node]...->[cnt_node (pos-1)]->[node (pos)]->[node]...->NULL
    // head->[node]...->[cnt_node (pos-1)]->[new_node (pos)]->[given position]->[node]...->NULL
    new_node->next = current->next;

    //connecting the current node (pos-1) to the new node (pos).
    current->next = new_node;
    linkedListSize++;
    return 1;
}
int delete_node(int pos){
    // if linked list is empty
    if(!linkedListSize) return 2;
    
    // invalid position
    if(!valid_position(pos)) return 0;

    Node* current = head;
    if(pos == 1){
        head = head->next;
        free(current);
        current = NULL; // not to be a dangling pointer (good practice)
        // the pointer will be deleted after function's execution anyways.

        // if linked list has only one element to be deleted
        if(linkedListSize == 1) last = head; 
        linkedListSize--;
        
        return 1;
    }
    for(int i = 0; i < pos-2;i++){
        current = current->next;
    }

    // to save the last position
    if(pos == linkedListSize){
        last = current;
    }
    
    // holds the address of the node that will be deleted.
    Node* tmp = current->next;

    // [curret]-X>[deleted]->[node]...->NULL
    //        |_______________↑
    current->next = current->next->next;

    // free up the occupied space
    // [curret]               [node]...->NULL
    //        |_______________↑
    free(tmp);
    tmp = NULL;// not to be a dangling pointer (good practice)
    // the pointer will be deleted after function's execution anyways.
    
    linkedListSize--;
    return 1;
}
void printLinked(){
    printf("===> This is your linked list <===\n");
    Node *temp = head;
    printf("head->");

    // if temp hasn't reached the last node yet.
    while(temp != NULL){
        printf("[%d]->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n\n");
}
int main() {
    printf("=====Small project on linked lists=====\n");
    printf("How many numbers will you insert?\n");
    int size;
    scanf("%d",&size);
    printf("Enter %d number%c:\n",size,size==1?'\0':'s');
    for(int i = 0;i<size;i++){
        int input;
        scanf("%d", &input);
        insert_end(input);
    }
    printLinked();

    size_t op;
    do{
        // printf("%d\n", last->data);
        int user_input;
        int element_position;
        printf("Choose an operation.\n");
        printf("1-Insert at beginning.\n");
        printf("2-Insert at end.\n");
        printf("3-Insert at a position.\n");
        printf("4-Delete an element.\n");
        printf("5-Exit\n");
        scanf("%zu",&op);

        if(op<4LL){
            printf("Enter a number:\n");
            scanf("%d",&user_input);

            if(op == 1LL) insert_begin(user_input);
            else if(op == 2LL) insert_end(user_input);
            else
                do{
                    printf("Enter a valid position:\n");
                    scanf("%d",&element_position);
                }while(!insert_th_position(user_input,element_position));
            
        }else if(op == 4LL){
        
            if(linkedListSize)
                do{
                    printf("Enter a valid position:\n");
                    scanf("%d",&element_position);
                }while(!delete_node(element_position));
            
            else printf("\n====The linked list is empty====\n");
        
        }else if(op == 5LL) exit(1);
        else {
            printf("Invalid\n");
            continue; // not to print the linked list
        }
        printLinked();
    }while(1);

    // will be added later on. ignore this section
//    printf("[curret]-X>[deleted]->[node]...->NULL\n"
//                  "       |_______________^\n\n");
//    printf("[curret]   [deleted]->[node]...->NULL\n"
//                  "       |_______________^\n\n");
//    printf("[curret]              [node]...->NULL\n"
//                  "       |_______________^\n");
}