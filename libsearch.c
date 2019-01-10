#include"libsearch.h"


int compare(Element *cmp1,Element *cmp2)
{
	if (NULL == cmp1 || NULL == cmp2)
	{
		debug("one is NULL");
		return -2;
	}
	if (cmp1->data == cmp2->data)
	{
		return 0;
	}
	else if (cmp1->data > cmp2->data)
	{
		return 1;
	}
	else 	
	{
		return -1;
	}
}

Element*  create_one_node(int value)
{
	Element *tmp = malloc(sizeof(Element));
	if (NULL == tmp)
	{
		return NULL;
	}
	tmp->data = value;
	return tmp;
}


int show(Element *tree)
{
	if (NULL == tree)
	{
		return 0;
	}
	show(tree->lchild);
	printf("The node date is %d\n",tree->data);
	show(tree->rchild);
	return 0;
}

/*
 * 二叉查找树
 * date : 2018/4/15
 * */
int search_tree(Element *tree,Element *src,Element *parent,Element **dst,comp compfun)
{
	debug("for opt nums ");
	if (NULL == tree)
	{
		*dst = parent;
		return -1;
	}
	
	if (0 == compfun(tree,src))
	{
		debug("found it");
		*dst = tree;
		return 0;
	}
	else if(1 == compfun(tree,src))
	{
		search_tree((tree)->lchild,src,tree,dst,compfun);
	}
	else if (-1 == compfun(tree,src))
	{
		search_tree((tree)->rchild,src,tree,dst,compfun);
	}
}


/*
 * 二叉查找树的插入
 * date : 2018/4/16
 * */
int search_tree_insert(Element **tree,Element *src,comp compare)
{
	if ( NULL == src || NULL == compare)
	{
		return -1;
	}
	if (NULL == *tree)
	{
		debug("search_tree fail");
		*tree = src;
		return -1;
	}
	Element *dst ;
	/*没有查找到的时候需要插入，否则就不需要插入*/
	if (-1  == search_tree(*tree,src,NULL,&dst,compare))
	{
		if(compare(src,dst)>0)
		{
			debug("start to insert");
			dst->rchild = src;
		}
		else
		{
			debug("start to insert");
			dst->lchild = src;
		}
	}
}


/*
 * 删除一个二叉树的节点
 * date : 2018/4/17
 * */
int tree_delete(Element **tree)
{
	if (NULL == tree)
	{
		return -1;
	}
	Element *q = NULL;
	if ((*tree)->lchild == NULL)
	{
		/*如果左子树是空的，就重接他的右子树。*/
		q =	*tree;*tree = (*tree)->rchild;free(q);
	}
	else if ((*tree)->rchild == NULL)
	{
		/*如果右子树是空的，就重接它的左子树*/
		q = *tree;*tree = (*tree)->lchild;free(q);
	}
	else
	{
		/*左右子数都不是空的*/
		Element *tmp_parent = NULL;
		q = *tree;tmp_parent = (*tree)->lchild;
		/*先向左，然后不断的向右*/
		while (tmp_parent->rchild)
		{
			q = tmp_parent;tmp_parent = tmp_parent->rchild;
		}
		//tmp_parent->lchild = (*tree)->lchild;
		//tmp_parent->rchild = (*tree)->rchild;
		//Element *tmp = *tree;
		//*tree = tmp_parent;
		/*此处需要优化,因为不通用,但是现在没想到好办法*/
		(*tree)->data = tmp_parent->data;
		if (q == *tree)
		{
			q->lchild = tmp_parent->lchild;
		}
		else
		{
			q->rchild = tmp_parent->lchild;
		}
		free(tmp_parent);
		tmp_parent = NULL;
	}
	return 0;
}


/*
 * 二叉查找树的删除操作
 * date : 2018/4/17
 * */
int search_tree_delete(Element **tree,Element *src,comp compare)
{
	if (NULL == tree || NULL == src || NULL == compare)
	{
		return -1;
	}
	if (compare(*tree,src) == 0)
	{
		debug("find and delete");
		return tree_delete(tree);	
	}
	else if (compare(*tree,src) == 1)
	{
		debug("find and rchild");
		search_tree_delete(&((*tree)->lchild),src,compare);
	}
	else if (compare(*tree,src) == -1)
	{
		debug("find and lchild");
		search_tree_delete(&((*tree)->rchild),src,compare);
	}
}

/*
 * 平衡二叉树的 实现。需要理解平衡二叉树的定义，最小不平衡子树，以及平衡因子。
 * date : 2018/4/21
 * */
int search_tree_insert_avl(Element **tree,Element *src,comp compare,int *taller)
{
	debug("for opt nums ");
	if (NULL == tree || NULL == src || NULL == compare || NULL == taller)
	{
		debug("insert fail");
		return -1;
	}
	if (NULL == *tree)
	{
		/*如果树是空的，就插入节点，这个时候树就会长高*/
		*tree = src;
		debug("has insert");
		*taller = 1;
	}
	else
	{
		if ( 0 == compare(*tree,src))
		{
			/*原来已经存在这个元素，就不插入*/
			*taller = 0;
			return -1;
		}
		if (compare(*tree,src)>0)
		{
			/*需要插入到左子树*/
			if (-1 == search_tree_insert_avl(&(*tree)->lchild,src,compare,taller))
			{

				debug("insert fail");
				/*没有插入*/
				return -1;
			}
			if (1 == *taller)
			{
				switch((*tree)->bf)
				{
					case 1:
						avl_tree_left_balance(tree);
						*taller = 0;
						break;
					case 0:
						(*tree)->bf = 1;
						*taller = 1;
						break;
					case -1:
						(*tree)->bf = 0;
						*taller = 0;
						break;

				}
			}
		}
		else
		{
			/*查找右子树*/
			if (-1 == search_tree_insert_avl(&(*tree)->rchild,src,compare,taller))
			{
				return -1;
			}
			if (*taller == 1)
			{
				switch((*tree)->bf)
				{
					case 1:
						(*tree)->bf = 0;
						*taller = 0;
						break;
					case 0:
						(*tree)->bf = -1;
						*taller = 1;
						break;
					case -1:/*之前右子树已经比较高了，插入之后打破平衡，需要平衡处理*/
						avl_tree_right_balance(tree);
						taller = 0;
						break;
				}
			}

		}
	}
	return 0;
}

/*
 * 左旋操作。左子树打破平衡的时候使用。
 * date : 2018/4/19 
 * */
int avl_tree_right_rotate(Element **tree)
{
	if (NULL == tree || NULL == *tree)
	{
		return -1;
	}
	/*先不考虑平衡因子的问题*/
	Element *tmp = NULL;
	tmp = (*tree)->lchild;
	(*tree)->lchild = tmp->rchild;
	tmp->rchild = *tree;
	*tree = tmp;
}

/*
 * 右旋操作。右子树打破平衡的时候使用。和左旋的代码是十分的类似的。
 * date : 2018/4/19 
 * */
int avl_tree_left_rotate(Element **tree)
{
	if (NULL == tree || NULL == *tree)
	{
		return -1;
	}
	Element *tmp = NULL;
	tmp = (*tree)->rchild;
	(*tree)->rchild = tmp->lchild;
	tmp->lchild = (*tree);
	*tree = tmp;
}


/*
 * 二叉树的左边平衡操作。
 * date : 2018/4/19 
 * */
int avl_tree_left_balance(Element **tree)
{
	if (NULL == tree || *tree == NULL)
	{
		return -1;
	}
	Element *L,*Lr;
	L = (*tree)->lchild;
	switch(L->bf)
	{
		case 1:/*新节点就插入在左孩子的左子树上*/
			L->bf = (*tree)->bf = 0;
			avl_tree_right_rotate(tree);
			break;
		case -1:
			Lr = L->rchild;
			switch(Lr->bf)
			{
				case 1:
					/*应急情况，理论上是不会发生的*/
					debug("it is 1");
					(*tree)->bf = -1;
					L->bf=0;
					break;
				case 0:
					debug("it is 0");
					(*tree)->bf = L->bf=0;
					break;
				case -1:
					/*应急情况，理论上是不会发生的*/
					debug("it is -1");
					(*tree)->bf = 0;
					L->bf = 1;
					break;
			}
			Lr->bf = 0;
			avl_tree_left_rotate(&(*tree)->lchild);
			avl_tree_right_rotate(tree);
	}
}

/*
 * 平衡树的右子树平衡操作
 * date : 2018/4/21
 * */
int avl_tree_right_balance(Element **tree)
{
	if (NULL == tree || *tree == NULL)
	{
		return -1;
	}
	Element *R,*Rl;
	R = (*tree)->rchild;
	switch(R->bf)
	{
		case -1:/*新节点就插入在右孩子的右子树上*/
			R->bf = (*tree)->bf = 0;
			avl_tree_left_rotate(tree);
			break;
		case 1:
			Rl = R->lchild;
			switch(Rl->bf)
			{
				case 1:
					/*应急情况，理论上是不会发生的*/
					debug("it is 1");
					(*tree)->bf = 1;
					R->bf=0;
					break;
				case 0:
					debug("it is 0");
					(*tree)->bf = R->bf=0;
					break;
				case -1:
					/*应急情况，理论上是不会发生的*/
					debug("it is -1");
					(*tree)->bf = 0;
					R->bf = -11;
					break;
			}
			Rl->bf = 0;
			avl_tree_right_rotate(&(*tree)->rchild);
			avl_tree_left_rotate(tree);
	}
}


