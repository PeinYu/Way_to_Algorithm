//并查集
//disjoint_set.cpp

//一个集合中的成员分为若干个家族
//多次声明一对成员属于同一个家族之后
//再给出多对成员，查询它们是否属于同一家族

//并查集用于处理大量不相交集合的合并及查询，在使用中常以森林来表示
//集合中成员的分组是并查集的典型应用场景
//
//初始时将集合中每个点都设置为只包含自己的集合，然后每次合并都将两个集合合并为一个
//在并查集中的节点中设置一个父节点指针
//属于同一集合的节点父指针指向同一个父节点，而不属于同一集合的点指向不同的父节点
//并查集的两个操作是合并和查询
//初始化：将集合中每个节点的父指针指向自己
//查询：判断两节点的父节点是否相同
//合并：将两节点的父节点指针设置为相同的父节点
//在合并中还有一处细节，即假设p和q两节点原分别属于u和v两个家族
//当将p和q合并时，选择将q的家族合并入p的家族中去
//在合并之前p的家族首领是u，而q的家族首领是v，将q家族合并入p家族后首领只有一个即u
//在本文代码的合并函数中会体现这个细节

#include "general_head.h"
#include "data_structure.h"
dis_node _disjoint_set[MAX];

void disjoint_set_init()
{//并查集初始化
	for(int i = 0; i < MAX; ++ i){
		_disjoint_set[i].d_idx = i;
		_disjoint_set[i].d_fa = &_disjoint_set[i];
	}
}
dis_node* _disjoint_set_find_father(dis_node *p)
{//查询节点p的父节点
	if(p->d_fa != p)
		//属于同一集合的所有节点拥有相同的父节点
		//若节点p的父节点是p自己则该节点为所在集合的父节点
		//若节点p的父节点不是p自己
		//则递归的将p的父节点设置为自己父节点的父节点
		//这样的设置将查询的路径缩短了，使用了压缩路径技术
		p->d_fa = _disjoint_set_find_father(p->d_fa);
	return(p->d_fa);
}
void disjoint_set_union(int p1, int p2)
{//将p2的家族合并入p1的家族，最早的祖先节点是p1家族的
	//pf1是p1的父节点，pf2是p2的父节点
	dis_node *pf1 = _disjoint_set_find_father(&_disjoint_set[p1]);
	dis_node *pf2 = _disjoint_set_find_father(&_disjoint_set[p2]);
	//将pf1设置为pf2的父节点
	//以后_disjoint_set_find_father操作会
	//使p2家族中的所有节点的父节点最终都指向p1的父节点
	pf2->d_fa = pf1;
}
bool disjoint_set_query(int p1, int p2)
{//查询p1和p2是否属于同一个家族
	if(_disjoint_set_find_father(&_disjoint_set[p1]) ==
			_disjoint_set_find_father(&_disjoint_set[p2]))
		//如果它们的父节点是同一节点则属同一家族，否则不是
		return(true);
	else
		return(false);
}
