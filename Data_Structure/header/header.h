#ifndef HEADER_H
#define HEADER_H
#include<stdint.h>
#include<stdlib.h>
#include <stdbool.h>
typedef char  elem;
struct node{
 int64_t data;
 struct node* next;
};
typedef struct qnode
{
    char data;
    struct qnode* next;
};
struct dnode
{
    struct dnode *previous;
    int32_t data;
    struct dnode *next;
};
typedef struct node list;

typedef struct queue_header{
    list* front;
    list* back;
}queue;

void Push(struct node** headRef , int64_t newData);
int Length(struct node*head);
void ChangeToNull(struct node** headRef);
void ChangeCaller();
struct node* AddAtHead();
struct node* BuildWithSpecialCase();
struct node* BuildWithDummyNode();
struct node* BuildWithLocalRef();
void Print(struct node* head);
struct node* BuildOneTwoThree();


bool is_acyclic(list* head);
bool is_segment(list* start, list* end);
bool is_queue(queue* Q);
bool queue_empty(queue* Q);
queue* queue_new();
void enq(queue* Q, elem x);
elem deq(queue* Q);
void display(queue* Q);
struct TreeNode* pop(list** top);

extern struct TreeNode* tree;
void CountTest();
void GetNthTest();
void DeleteListTest();
void PopTest();
void InsertNthTest();
void SortedInsertTest();
void SortedInsert(struct node** headRef, struct node* newNode);
int DeleteList(struct node** head);
void InsertSortTest();
void AppendTest();
void RemoveDuplicatesTest();
void MoveNodeTest();
void PelindromeTest();
void CircularQueue_Q2();
void TodoListTest();
void BracketMatchingTest();
void linked_list_tree_implementation();
void Array_tree_implementaation();
void linked_list_tree_traversal();
void array_tree_traversal();
struct TreeNode* createNode(int value);
void preorder(struct TreeNode* root);
void inorder(struct TreeNode* root);
void postorder(struct TreeNode* root);
void BinarySearchTest();
void preorder_test();
void postorder_test();
void push(list** top, struct TreeNode* node);
void copyTree_test();
struct TreeNode* insert(struct TreeNode* root, int value);
void compareTree_test();
void threadedTree_test();
struct TreeNode* buildTree(int32_t arr[],int32_t index,int32_t nodes);
void CircularLinkedlistTest();
struct Node* createNode_function(int data);
void deleteNode_fun(struct Node** head, int data);
void display_fun(struct Node* head);
void SumTest();
void insertAtBeginning(struct Node**head , int data);
void insertAtEnd(struct Node** head, int data);
void d_append(struct dnode **head , int32_t number);

void d_addatbeg(struct dnode **head ,
                int32_t number);

void d_addafter(struct dnode *currentNode ,
                int32_t location ,
                int32_t number);

void d_display(struct dnode *currentNode);

int32_t d_count(struct dnode *currentNode);

void d_delete(struct dnode **head ,
              int32_t number);

void TestCase();
void Circular_Doubly_linked_list();
#endif
