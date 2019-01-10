#ifndef LIBSEARCH_H
#define LIBSEARCH_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifdef DEBUG
#define debug(format,args...) do{fprintf(stderr,"Debug>>>%s->%s()->line.%d:"format"\n",__FILE__,__FUNCTION__,__LINE__,##args);}while(0);
#endif

typedef struct Element
{
	int data;
	int bf;
	struct Element *lchild,*rchild;
}Element;


typedef int (*comp)(void *,void*);
int compare(Element *cmp1,Element *cmp2);
Element *create_one_node(int value);
int show(Element *tree);
int search_tree(Element *tree,Element *src,Element *parent,Element **dst,comp compfun);
int search_tree_insert(Element **tree,Element *src,comp compare);
int tree_delete(Element **tree);
int search_tree_delete(Element **tree,Element *src,comp compare);
int search_tree_insert_avl(Element **tree,Element *src,comp compare,int *taller);
int avl_tree_right_rotate(Element **tree);
int avl_tree_right_balance(Element **tree);
int avl_tree_left_balance(Element **tree);
int avl_tree_left_rotate(Element **tree);
#endif 
