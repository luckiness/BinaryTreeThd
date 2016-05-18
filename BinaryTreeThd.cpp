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

	BinaryTreeNodeThd(const T&data)//������ �����ö�������ָ�����������Ŀ�ָ������Žڵ��ǰ���ͺ����Ϣ
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

	//����������
	void InorderThreading()
	{
	  Node* prev=NULL;
	  _InorderThreading(_root,prev);
	}

	//����������
	void PrevtorderThreading()
	{
	Node* prev=NULL;
	_PrevorderThreading(_root,prev);
	}

	//��������������
	void _InorderThd()
	{
		Node* cur=_root;
		while(cur)
		{
		//	��������ߵ�Ҷ�ӽڵ�
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
		 //����������
		 cur=cur->_right ;
		}
	}

	//��������������������
	void _Prevorderthd( )
	{
	Node*cur=_root;
	if(cur==NULL)
	{
		return;
	}
	while(cur)
	{ //�����ߵĽڵ�
		while(cur->_leftTag ==LINK)
			{
			cout<<cur->_data <<" ";
			cur=cur->_left ;
			}
			cout<<cur->_data <<" ";
			//ת�Ƶ��ұߵĽڵ�
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

	//��������������
	void _InorderThreading(Node* cur,Node*& prev)
	{
		if(cur==NULL)
		{
		 return;
		}
		//�ݹ����������
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
		//�ݹ����������
		_InorderThreading(cur->_right ,prev);
	}

	//��������������
	void _PrevorderThreading(Node* cur,Node*& prev)
	{
	 if(cur==NULL)
		 return;
	 //��ǰ������
	 if(cur->_left ==NULL)
	 {
		 cur->_leftTag =THREAD ;
		 cur->_left =prev;
	 }
	 //�ú�������
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
	cout<<"����������������������";
	btt1.InorderThreading ();
	btt1._InorderThd();
	cout<<endl;
	btt2.InorderThreading ();
	btt2._InorderThd();
	cout<<endl;
	cout<<"����������������������";
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