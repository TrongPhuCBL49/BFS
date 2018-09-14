#include <iostream>
#include <fstream>

using namespace std;

template <typename Type> class NODE
{
public:
	Type Info;
	NODE* Next;
};
template <typename Type> class QUEUE
{
public:
	NODE<Type>* Head;
	NODE<Type>* Tail;
	void Init()
	{
		this->Head = this->Tail = NULL;
	}
	bool IsEmpty()
	{
		return (this->Head == NULL);
	}
	void Push(Type x)
	{
		NODE<Type>* p = CreateNode<Type>(x);
		if (p == NULL)
			return;
		if (this->IsEmpty())
			this->Head = this->Tail = p;
		else
		{
			this->Tail->Next = p;
			this->Tail = p;
		}
	}
	Type Pop()
	{
		NODE<Type>* p = this->Head;
		Type x = p->Info;
		this->Head = this->Head->Next;
		delete p;
		return x;
	}
};
template <typename Type> NODE<Type>* CreateNode(Type x)
{
	NODE<Type>* p = new NODE<Type>;
	if (p == NULL)
		return NULL;
	p->Info = x;
	p->Next = NULL;
	return p;
}

int n, m;
QUEUE<int> *V;
QUEUE<int> ListE;

void Input()
{
	ifstream fi;
	fi.open("bai2.inp");
	fi >> n >> m;
	//Lưu cạnh bằng danh sách kề
	//V->Init();
	V = new QUEUE<int>[n];
	for (int i = 0; i < n; i++)
		V[i].Init(); //Khởi tạo danh sách kề cho từng đỉnh
	int e1, e2;
	for (int i = 0; i < m; i++)
	{
		fi >> e1 >> e2;
		V[e1].Push(e2);
		V[e2].Push(e1);
	}
	fi.close();
}
void BFS(int v)
{
	ListE.Init(); //Khởi tạo danh sách đỉnh đã xét
	int *Free = new int[n];
	for (int i = 0; i < n; i++)
		Free[i] = 1; //Đánh dấu tất cả các đỉnh là chưa xét => đỉnh tự do
	QUEUE<int> myQueue; //Hàng đợi
	myQueue.Init();
	myQueue.Push(v); //Push đỉnh đầu tiên vào hàng đợi
	Free[v] = 0; //Đánh dấu đã xét đỉnh v
	while (!myQueue.IsEmpty())
	{
		int e1 = myQueue.Pop(); //Pop dữ liệu trong hàng đợi ra gán vào e1
		ListE.Push(e1); //Push các đỉnh được xét vào danh sách đã duyệt
		while (!V[e1].IsEmpty())
		{
			int e2 = V[e1].Pop(); //Xét các đỉnh e2 kề với e1
			if (Free[e2])
			{
				myQueue.Push(e2);
				Free[e2] = 0;
			}
		}
	}
}
void Output()
{
	ofstream fo;
	fo.open("bai2.out");
	fo << ListE.Pop();
	while (!ListE.IsEmpty())
		fo << " -> " << ListE.Pop();
	fo.close();
}

void main()
{
	Input();
	BFS(0);
	Output();
}