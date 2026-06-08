/*
Author: Nidhi Goswami
Date: 12-05-2026
Description : common function file for  all function 
*/

#include<stdio.h>
#include"header.h"
#include<stdlib.h>
#include<stdint.h>
/*
Author: Nidhi Goswami
Date: 12-05-2026
Description: this function is for add newnode in front of list 
*/
struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};
void Push(struct node** headRef, int64_t newData){

    struct node* newnode;
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode -> data = newData;
    newnode -> next = *headRef;
    *headRef = newnode;

}

int Length(struct node* head){
     int64_t count = 0;
     struct node* current = head;
     while(current != NULL){
        count++;
        current = current -> next;
     }
     return(count);
}

void ChangeToNull(struct node** headRef){
     *headRef = NULL;
}

void ChangeCaller(){
     struct node* head1;
     struct node* head2;
     ChangeToNull(&head1);
     ChangeToNull(&head2);
}

struct node* AddAtHead(){
    struct node* head = NULL;
    int32_t index;
    for(index=1; index<6;index++){
       Push(&head, index);
    }
    return(head);
}

struct node* BuildWithSpecialCase(){

    struct node* head = NULL;
    struct node* tail;
    int32_t index;

    Push(&head,1);
    tail = head;
    for(index=2;index<6;index++){
       Push(&(tail->next),index);
       tail = tail->next;
    }
    return(head);
}

struct node* BuildWithDummyNode(){
    struct node dummy;
    struct node* tail = &dummy;
    int32_t index;
    dummy.next = NULL;
    for(index=1;index<6;index++){
       Push(&(tail->next),index);
       tail = tail->next;
    }
    return(dummy.next);
}


struct node* BuildWithLocalRef(){
    struct node* head = NULL;
    struct node** lastPtrRef = &head;
    int32_t index;
    for(index=1;index<6;index++){
       Push(lastPtrRef,index);
       lastPtrRef=&((*lastPtrRef)->next);
    }
    return(head);
}


void Print(struct node* head)
{
    struct node* current = head;

    while(current != NULL)
    {
        printf("%d -> ", current->data);

        current = current->next;
    }

    printf("NULL\n");
}

struct node* BuildOneTwoThree(){

     struct node* head = NULL;
     Push(&head,3);
     Push(&head,2);
     Push(&head,1);
     return(head);

}

bool is_acyclic(list* head)
{
    list* slow = head;
    list* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return false;
        }
    }

    return true;
}


bool is_segment(list* start, list* end)
{
    if (start == NULL || end == NULL) {
        return false;
    }

    list* temp = start;

    while (temp != NULL) {
        if (temp == end) {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

bool is_queue(queue* Q){
     return Q!= NULL && is_acyclic(Q->front) && is_segment(Q-> front, Q->back);
}

bool queue_empty(queue* Q){
      return  Q->front == Q->back;
}


queue* queue_new(){
     queue* Q = malloc(sizeof(queue));
     list* dummy = malloc(sizeof(list));
     Q->front = dummy;
     Q->back = dummy;
     return Q;
}

void enq(queue* Q, elem x){
     list* new_dummy = malloc(sizeof(list));
     Q->back->data = x;
     Q->back->next=new_dummy;
     Q->back = new_dummy;
}

elem deq(queue* Q){
     elem x = Q->front->data;
     Q->front = Q->front->next;
     return x;
}

void display(queue* Q)
{
    if (queue_empty(Q)) {
        printf("Queue is Empty\n");
        return;
    }

    list* temp = Q->front;

    printf("Queue: ");

    while (temp != Q->back) {
        printf("%ld ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}



struct TreeNode* createNode(int32_t value)
{
    struct TreeNode* newNode =
        malloc(sizeof(struct TreeNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }


    newNode->data = value;

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void preorder(struct TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%d ", root->data);

    preorder(root->left);

    preorder(root->right);
}

void inorder(struct TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    inorder(root->left);

    printf("%d ", root->data);

    inorder(root->right);
}


void postorder(struct TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    postorder(root->left);

    postorder(root->right);

    printf("%d ", root->data);
}

struct TreeNode* pop(list** top)
{
    if (*top == NULL)
        return NULL;

    list* temp = *top;

    struct TreeNode* node =
        (struct TreeNode*)temp->data;

    *top = (*top)->next;

    free(temp);

    return node;
}

void push(list** top, struct TreeNode* node)
{
    Push(top, (int64_t)node);
}
struct TreeNode* insert(struct TreeNode* root, int value)
{
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);

    else
        root->right = insert(root->right, value);

    return root;
}

struct TreeNode* buildTree(int32_t arr[],
                           int32_t index,
                           int32_t nodes)
{
    if (index >= nodes)
    {
        return NULL;
    }

    struct TreeNode* root =
        createNode(arr[index]);

    root->left =
        buildTree(arr,
                  2 * index + 1,
                  nodes);

    root->right =
        buildTree(arr,
                  2 * index + 2,
                  nodes);

    return root;
}
