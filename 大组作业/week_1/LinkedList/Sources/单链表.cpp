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

// 析构函数
LinkedList::~LinkedList() {
    Node* cur = head;
    while (cur) {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }
}

// 插入节点（假设链表是有序的）
void LinkedList::insert(int val) {
    Node* newnode = new Node(val);
    if (!head) { // 链表为空
        head = newnode;
        return;
    }

    // 插入到链表头部
    if (val < head->data) {
        newnode->next = head;
        head = newnode;
        return;
    }

    // 插入到链表中间或尾部
    Node* cur = head;
    while (cur->next && cur->next->data < val) {
        cur = cur->next;
    }
    newnode->next = cur->next;
    cur->next = newnode;
}

// 删除节点
void LinkedList::remove(int val) {
    // 删除链表头部的匹配节点
    while (head && head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    if (!head) { // 链表为空
        cout << "zhaobudao" << endl;
        return;
    }

    // 删除链表中间或尾部的匹配节点
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

// 修改节点值
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

// 打印链表
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

    cout << "初始链表: ";
    list.print();

    list.remove(3);
    cout << "删除节点3后: ";
    list.print();

    list.change(2, 10);
    cout << "修改节点2为10后: ";
    list.print();

	list.reverse();
	cout << "反转链表后: ";
	list.print();
    return 0;
}