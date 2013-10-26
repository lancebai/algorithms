//
//  main.cpp
//  tree_node_insertion
//
//  Created by Ann Wang on 13/10/19.
//  Copyright (c) 2013 Lance Bai. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <ctime>

typedef struct tree_node_{
  unsigned int uiVal;
  struct tree_node_ *left;
  struct tree_node_ *right;
}tree_node;

typedef void (*callback)(tree_node*);

static void print_node(tree_node *node)
{
  assert(node!= NULL);
  if(node){
    std::cout << "the val is:" << node->uiVal << std::endl;
  }
}

static void destroy_node(tree_node *node){
  assert(node!= NULL);
  if(node){
    std::cout<< "deleteing node with val:" << node->uiVal <<std::endl;
    node->left = NULL;
    node->right = NULL;
    delete node;
    node = NULL;
  }
}

typedef enum traversal_type_ {
  traversal_in_order = 0,
  traversal_pre_order, 
  traversal_post_order, 
  traversal_MAX
}traversal_type;

class tree{
private:
  tree_node* root;
  tree_node* allocate_newnode_and_setval(const unsigned int uiKeyVal);
  void traversal_imp(tree_node* node);
  void traversal_imp(traversal_type type, tree_node* node, callback cbf);
  void destroy_tree();
  unsigned int get_height_imp(const tree_node* node) const; 
  tree_node* find_value_imp(tree_node* node, const unsigned int uiVal) const;

public:
  tree():root(NULL){};
  ~tree(){ destroy_tree();}
  void insert_node(const unsigned int uiVal);
  //dump the tree node, by in-order traversal
  void traversal() { traversal_imp(root); }
  void traversal(traversal_type type, callback cbf) { traversal_imp(type, root, cbf); }
  tree_node* find_value(const unsigned int uiVal) const;
  void delete_node(const unsigned int uiVal);
  unsigned int get_height() const { get_height_imp(root);}
};




void tree::delete_node(const unsigned int uiVal)
{
  ;
}

tree_node* tree::find_value_imp(tree_node* node, const unsigned int uiVal) const
{
  if(NULL == node) {
    return NULL;
  }
  if(node->uiVal == uiVal) {
    return node;
  }
  else if(uiVal > node->uiVal) {
    return find_value_imp(node->right, uiVal); 
  }
  else{
    return find_value_imp(node->left, uiVal); 
  }
  
}


/** tree::find_value
  * find a specific value from the data
  *
  * @uiVal the searching value
  * @return address of the node if found
  *         NULL if not found
  */
tree_node* tree::find_value(const unsigned int uiVal) const
{
   return find_value_imp(root, uiVal);
}

tree_node* tree::allocate_newnode_and_setval(const unsigned int uiKeyVal)
{
  tree_node* node = new tree_node;

  if(node != NULL) {
    node->left = NULL;
    node->right = NULL;
    node->uiVal = uiKeyVal;
  }

  std::cout<< "inserting val:" << uiKeyVal << std::endl;
  return node;
}

void tree::insert_node(const unsigned int uiVal){

  if(root == NULL){
    root = allocate_newnode_and_setval(uiVal);
    return;
  }

  tree_node* new_node_position = root;
  tree_node* parent = NULL; // the parent node of new_node_position 
  //find the position
  while(new_node_position) {
    //assert(new_node_position->uiVal != uiVal);
    if(uiVal > new_node_position->uiVal){
      parent = new_node_position;
      new_node_position = new_node_position->right;
    }
    else {
      parent = new_node_position;
      new_node_position = new_node_position->left;
    }
  }
  //insert the node
  if(uiVal > parent->uiVal) {
    parent->right =  allocate_newnode_and_setval(uiVal); 
  }
  else{
    parent->left = allocate_newnode_and_setval(uiVal);
  }
}


void tree::traversal_imp(traversal_type type, tree_node* node, callback cbf)
{
  if(node == NULL){
    return;
  }
   
  switch(type) {  
    case traversal_in_order:
      traversal_imp(type, node->left, cbf);
      cbf(node);
      traversal_imp(type, node->right, cbf);
      break;
    case traversal_pre_order:
      traversal_imp(type, node->left, cbf);
      cbf(node);
      traversal_imp(type, node->right, cbf);
      break;
    case traversal_post_order:
      traversal_imp(type, node->left, cbf);
      traversal_imp(type, node->right, cbf);
      cbf(node);
      break;
    case traversal_MAX:
    default:
      std::cout << "not defined!" << std::endl;
      break;
  }
}




void tree::traversal_imp(tree_node* node)
{
  if(node == NULL){
    return;
  }
  traversal_imp(node->left);
  std::cout << node->uiVal<< " " ;
  traversal_imp(node->right);
}


#define MAX(a, b) ((a>=b)?a:b)
unsigned int tree::get_height_imp(const tree_node* node) const
{
  if(NULL == node){
    //reach the end of tree;
    return 0;
  }
  return MAX(get_height_imp(node->left), get_height_imp(node->right))+1;
}

void tree::destroy_tree()
{
  if(NULL == root) {return;}
  traversal(traversal_post_order, destroy_node);
}

int main(int argc, const char * argv[])
{

  std::srand((unsigned int)std::time(0)); // use current time as seed for random generator
  tree btree;
  for(int i = 0;i<200; i++){
    int random_variable = std::rand()%1000;
    btree.insert_node(random_variable);
    //std::cout << btree.find_value(random_variable) << std::endl;
  }
   
  std::cout << "the height of tree is" << btree.get_height() << std::endl;
  btree.traversal(traversal_in_order, print_node);
  
  for(int i = 0;i<200; i++){
    int random_variable = std::rand()%1000;
    //btree.insert_node(random_variable);
    std::cout << random_variable << " is at " << btree.find_value(random_variable) << std::endl;
  }

  return 0;
}

