#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

enum PointerTag
{
	THREAD,
	LINK,
};

template <class T>
struct BinaryTreeNodeThd
{
	T _data;
	BinaryTreeNodeThd<T>*_left;
	BinaryTreeNodeThd<T>*_right;
	PointerTag _leftTag;
	PointerTag _rightTag;

	BinaryTreeNodeThd(const T&data)//线索化 ：利用二叉树中指向左右子树的空指针来存放节点的前驱和后继信息
		:_data(data)
		, _left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}

};

template <class T>
class BinaryTreeThd
{
	typedef BinaryTreeNodeThd<T>  Node;

private:
	Node* _root;
public:
	
	BinaryTreeThd()
		:_root(NULL)
	{}

	BinaryTreeThd(const T* a, size_t size,size_t index,const T& invalid)
	{
		
		_root = _CreateBinaryTreeThd(a, size, index, invalid);
	}

	//中序线索化
	void InorderThreading()
	{
	  Node* prev=NULL;
	  _InorderThreading(_root,prev);
	}

	//先序线索化
	void PrevtorderThreading()
	{
	Node* prev=NULL;
	_PrevorderThreading(_root,prev);
	}

	//中序线索化遍历
	void _InorderThd()
	{
		Node* cur=_root;
		while(cur)
		{
		//	访问最左边的叶子节点
	     while(cur->_leftTag ==LINK)
		 {
		 cur=cur->_left ;
		 }

		 cout<<cur->_data <<" ";

		 while(cur->_rightTag ==THREAD)
		 {
			cur=cur->_right ;
			cout<<cur->_data <<" ";
		 }
		 //访问右子树
		 cur=cur->_right ;
		}
	}

	//先序线索化遍历二叉树
	void _Prevorderthd( )
	{
	Node*cur=_root;
	if(cur==NULL)
	{
		return;
	}
	while(cur)
	{ //输出左边的节点
		while(cur->_leftTag ==LINK)
			{
			cout<<cur->_data <<" ";
			cur=cur->_left ;
			}
			cout<<cur->_data <<" ";
			//转移到右边的节点
			cur=cur->_right;

			/*while(cur->_rightTag ==THREAD )
			{
			cur=cur->_right ;
			cout<<cur->_data<<" " ;
			}*/
		}
	}
protected:
	//
	Node* _CreateBinaryTreeThd(const T*a, size_t size, size_t& index, const T& invalid)
	{
		Node* root=NULL;
		if(index<size&&a[index]!=invalid)
		{
			root=new Node(a[index]);
			root->_left = _CreateBinaryTreeThd(a,size,++index,invalid);
			root->_right =_CreateBinaryTreeThd(a,size,++index,invalid);
		}
		return root;
	}

	//中序线索化子树
	void _InorderThreading(Node* cur,Node*& prev)
	{
		if(cur==NULL)
		{
		 return;
		}
		//递归遍历左子树
		_InorderThreading(cur->_left ,prev);
		if(cur->_left ==NULL)
		{
		 cur->_leftTag =THREAD;
		 cur->_left =prev;
		}
		if(prev&&prev->_right ==NULL)
		{
		prev->_rightTag =THREAD ;
		prev->_right =cur;
		}
		prev=cur;
		//递归遍历右子树
		_InorderThreading(cur->_right ,prev);
	}

	//先序线索化子树
	void _PrevorderThreading(Node* cur,Node*& prev)
	{
	 if(cur==NULL)
		 return;
	 //置前线索化
	 if(cur->_left ==NULL)
	 {
		 cur->_leftTag =THREAD ;
		 cur->_left =prev;
	 }
	 //置后线索化
	 if(prev&&prev->_right ==NULL)
	 {
	 prev->_rightTag =THREAD;
	 prev->_right =cur;
	 }

	 prev=cur;

	 if(cur->_leftTag ==LINK)
	 {
		 _PrevorderThreading(cur->_left ,prev);
	 }
	
	  if(cur->_rightTag ==LINK)
	 {
		_PrevorderThreading(cur->_right ,prev);
	 }

	}
};

void test()
{
	int a1[10]={1,2,3,'#','#',4,'#','#',5,6};
	int a2[15]={1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	BinaryTreeThd<int>btt1(a1,10,0,'#');
	BinaryTreeThd<int>btt2(a2,15,0,'#');
	cout<<"中序线索化遍历二叉树：";
	btt1.InorderThreading ();
	btt1._InorderThd();
	cout<<endl;
	btt2.InorderThreading ();
	btt2._InorderThd();
	cout<<endl;
	cout<<"先序线索化遍历二叉树：";
	btt1.PrevtorderThreading();
	btt1. _Prevorderthd();
	cout<<endl;
	btt2.PrevtorderThreading();
	btt2. _Prevorderthd();
	cout<<endl;
}
int main()
{
  test();
 system("pause");
  return 0;
}