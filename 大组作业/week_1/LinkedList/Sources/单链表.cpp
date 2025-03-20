#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}
    ~LinkedList();

    void insert(int val);
    void remove(int val);
    void change(int val1, int val2);
    void print();
	void reverse();
};

// ��������
LinkedList::~LinkedList() {
    Node* cur = head;
    while (cur) {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }
}

// ����ڵ㣨��������������ģ�
void LinkedList::insert(int val) {
    Node* newnode = new Node(val);
    if (!head) { // ����Ϊ��
        head = newnode;
        return;
    }

    // ���뵽����ͷ��
    if (val < head->data) {
        newnode->next = head;
        head = newnode;
        return;
    }

    // ���뵽�����м��β��
    Node* cur = head;
    while (cur->next && cur->next->data < val) {
        cur = cur->next;
    }
    newnode->next = cur->next;
    cur->next = newnode;
}

// ɾ���ڵ�
void LinkedList::remove(int val) {
    // ɾ������ͷ����ƥ��ڵ�
    while (head && head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    if (!head) { // ����Ϊ��
        cout << "zhaobudao" << endl;
        return;
    }

    // ɾ�������м��β����ƥ��ڵ�
    Node* cur = head;
    while (cur->next) {
        if (cur->next->data == val) {
            Node* temp = cur->next;
            cur->next = cur->next->next;
            delete temp;
        }
        else {
            cur = cur->next;
        }
    }
}

// �޸Ľڵ�ֵ
void LinkedList::change(int val1, int val2) {
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

// ��ӡ����
void LinkedList::print() {
    Node* cur = head;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

void LinkedList::reverse() {
	Node* pre = nullptr;
	Node* cur = head;
	while (cur) {
		Node* temp = cur->next;
		cur->next = pre;
		pre = cur;
		cur = temp;
	}
	head = pre;
}

int main() {
    LinkedList list;
    list.insert(3);
    list.insert(1);
    list.insert(2);
    list.insert(5);
    list.insert(4);

    cout << "��ʼ����: ";
    list.print();

    list.remove(3);
    cout << "ɾ���ڵ�3��: ";
    list.print();

    list.change(2, 10);
    cout << "�޸Ľڵ�2Ϊ10��: ";
    list.print();

	list.reverse();
	cout << "��ת�����: ";
	list.print();
    return 0;
}