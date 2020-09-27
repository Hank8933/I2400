// 2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* next;
};

void input(Node** first)
{
	int n;
	cin >> n;

	Node* new_node = new Node;
	new_node->data = n;

	Node* tmp = *first;

	if (tmp == nullptr || tmp->data >= n) {  // 擺第一個
		new_node->next = *first;
		*first = new_node;
	}
	else {
		while (tmp->next && tmp->next->data <= n)
		{
			tmp = tmp->next;
		}
		Node* cur = tmp->next;
		tmp->next = new_node;
		new_node->next = cur;
	}
}

void delet(Node** first)
{
	int n;
	cin >> n;

	Node* tmp = *first;

	while (tmp) {
		if (tmp->data == n) {  // 刪第一個
			*first = tmp->next;
			tmp = tmp->next;
		}
		else if (tmp->next == nullptr) {
			break;
		}
		else if (tmp->next->data == n) {
			tmp->next = tmp->next->next;
		}
		else {
			tmp = tmp->next;
		}
	}
}

int main()
{
    char c;
	Node* first = nullptr;

	while (true)
	{
		int flag = 1;
		cout << "Input or Delete ? ";
		cin >> c;
		switch (c)
		{
		case 'I':
			cout << "Input an integer? ";
			input(&first);
			break;
		case 'D':
			cout << "Delete which integer? ";
			delet(&first);
			break;
		default:
			flag = 0;
			break;
		}
		if (flag) {
			Node* ptr = first;
			while (ptr) {
				cout << ptr->data << " ";
				ptr = ptr->next;
			}
			cout << endl;
		}
	}
}
