#include<iostream>

using namespace std;
struct Node {
	int data;
	Node* front;
	Node* next;

	Node(int val) : data(val), front(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
	Node* head;
	Node* tail;

public:
	DoublyLinkedList() : head(nullptr), tail(nullptr) {}

	~DoublyLinkedList();

	void insert(int val);
	void remove(int val);
	void change(int val1, int val2);
	void print();
	void reverse();
};

DoublyLinkedList::~DoublyLinkedList() {
	Node* cur = head;
	while (cur) {
		Node* temp = cur;
		cur = cur->next;
		delete temp;
	}
}

void DoublyLinkedList::insert(int val) {
	Node* newnode = new Node(val);
	if (!head) {
		head = newnode;
		tail = newnode;
		return;
	}
	if (val < head->data) {
		newnode->next = head;
		head->front = newnode;
		head = newnode;
		return;
	}
	if (val > tail->data) {
		newnode->front = tail;
		tail->next = newnode;
		tail = newnode;
		return;
	}
	Node* cur = head;
	while (cur->next && cur->next->data < val) {
		cur = cur->next;
	}
	newnode->next = cur->next;
	newnode->front = cur;
	cur->next->front = newnode;
	cur->next = newnode;
}

void DoublyLinkedList::remove(int val) {
	while (head && head->data == val) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	if (!head) {
		cout << "kong" << endl;
		return;
	}
	Node* cur = head;
	while (cur->next) {
		if (cur->next->data == val) {
			Node* temp = cur->next;
			cur->next = cur->next->next;
			if (cur->next) {
				cur->next->front = cur;
			}
			delete temp;
		}
		else {
			cur = cur->next;
		}
	}
}

void DoublyLinkedList::change(int val1, int val2) {
	Node* cur = head;
	while (cur) {
		if (cur->data == val1) {
			cur->data = val2;
			return;
		}
		cur = cur->next;
	}
	cout << "zhaobudao" << endl;
}

void DoublyLinkedList::print() {
	Node* cur = head;
	while (cur) {
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;
}

void DoublyLinkedList::reverse() {
	Node* cur = head;
	Node* temp = nullptr;

	while (cur) {
		temp = cur->front;
		cur->front = cur->next;
		cur->next = temp;
		cur = cur->front;
	}
	if (temp != nullptr) {
		tail = head;
		head = temp->front;
	}
}

int main() {
	DoublyLinkedList list;
	list.insert(1);
	list.insert(3);
	list.insert(2);
	list.insert(4);
	list.insert(5);
	list.print();
	list.reverse();
	list.print();
	list.remove(3);
	list.print();
	list.change(2, 6);
	list.print();
	return 0;
}