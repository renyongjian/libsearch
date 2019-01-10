#include"libsearch.h"

int main(int argc, const char *argv[])
{
	
	int arr[] = {2,3,4,1,7,6,9,8,12,19,18,13};
	int arr_len = sizeof(arr)/sizeof(int);
	Element *tree = NULL;
	int i;
	int taller=0;
	for (i = 0; i<arr_len; i++)
	{
		Element *tmp = create_one_node(arr[i]);	
		if (NULL == tmp)
		{
			return -1;
		}
		debug("start insert");
		/*测试普通的方法插入*/
		search_tree_insert(&tree,tmp,compare);
		/*测试使用平衡二叉树插入。*/
//		search_tree_insert_avl(&tree,tmp,compare,&taller);
	}
	show(tree);
	Element *tmp1 = create_one_node(arr[i]);	
	if (NULL == tmp1)
	{
		return -1;
	}
	tmp1->data = 9;
	tmp1->lchild = tmp1->rchild = NULL;
	search_tree_delete(&tree,tmp1,compare);
	show(tree);
	return 0;
}
