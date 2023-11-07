
#include "bs_tree.h"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
bs_tree::bs_tree()
{ 
  T_nil = new bs_tree_node();
  T_nil->p = T_nil;
  T_nil->left = T_nil;
  T_nil->right = T_nil;

  T_root = T_nil;
} 

bs_tree::~bs_tree()
{ 
  remove_all(T_root);
} 

void bs_tree::insert(bs_tree_node* z, bs_tree_i_info& t_info) {
  bs_tree_node* x;
  bs_tree_node* y;

  y = T_nil;
  x = T_root;
  while (x != T_nil)
    {
      y = x;

      if (z->key < x->key)
        x = x->left;
      else if (z->key > x->key)
        x = x->right;
      else
        t_info.i_duplicate += 1;
    }

  z->p = y;
  if (y == T_nil)
    T_root = z;
  else
    {
      if (z->key < y->key)
        y->left = z;
      else
          y->right = z;
    }

  z->left = T_nil;
  z->right = T_nil;
}

void bs_tree::insert(int key, bs_tree_i_info& t_info)
{ 
  bs_tree_node* x;
  x = new bs_tree_node;
  x->key = key;
  
  insert(x, t_info);
}

// TODO: modified inorder tree walk method to save the 
// sorted numbers in the first argument: int* array.
// question 2
void bs_tree::inorder_tree_walk(bs_tree_node* node, int *array, int *index) {
  if (node != T_nil) {
    inorder_tree_walk(node->left, array, index);
    array[(*index)] = node->key;
    *index += 1;
    inorder_tree_walk(node->right, array, index);
  }
}

int bs_tree::convert(int* array, int n)
{
  int i=0;
  bs_tree_node* T_node = T_root;
  inorder_tree_walk(T_node, array, &i);
  return i;
}

void bs_tree::remove_all(bs_tree_node* x)
{
  if(x!=T_nil)
  {
    remove_all(x->left);
    remove_all(x->right);
    delete x;
 }
} 



