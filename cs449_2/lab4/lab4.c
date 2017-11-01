#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int grade;
  struct Node* next;
} Node;


void free_list(Node* n) {
  for( ; n != NULL; n = n-> next) {
    printf("%x", n-> grade);
    free(n);
  }
}


void print_list(Node* n) {
  for( ; n != NULL; n = n-> next ) {
    printf("%x", n-> grade);
  }
}

Node* create_Node(int a) {
  Node* new_node = malloc(sizeof(Node));
  new_node-> grade = a;
  new_node-> next = NULL;
  return new_node;
}

int main() {
  /*Driver*/
  // make a new node
  Node* new_node = NULL;
  // read an integer
  char line[100];
  fgets(line, sizeof(line), stdin);
  int number;
  sscanf(line, "%d", &number);
  // loop till number == -1
  while (number != -1) {
    Node* create_Node(number);
    char line[100];
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &number);
    //new_node = new_node-> next;
  }
  // print list
  print_list(new_node);
  // free list
  free_list(new_node);

  /*Test Functions*/

  // Node* new_Node = create_node(500);
  // printf("value = %d, next = %p\n", new_Node->grade, new_Node->next);
  //
  //
  // Node* a = create_node(10);
  // Node* b = create_node(20);
  // Node* c = create_node(30);
  // a->next = b;
  // b->next = c;
  // print_list(a);
  //
  // free_list(new_Node);


}
