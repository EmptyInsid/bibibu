#pragma once
class DoubleList
{
private:
	class Node {
	public:
		Node* _prev;
		Node* _next;
		int _key;
		Node(int key=0, Node* prev = nullptr, Node* next = nullptr) {
			_key = key;
			_prev = prev;
			_next = next;
		}
	};
	Node* _head;
	Node* _tail;
	size_t _size;

	bool insertNodeBegin(Node* newNode);
	bool insertNodeEnd(Node* newNode);
	bool delNodeBegin();
	bool delNodeEnd();
	bool delNode(Node* delNode);
	Node* searchNode(int key);
public:
	DoubleList();
	~DoubleList();

	DoubleList(const DoubleList& other) = delete;
	DoubleList(DoubleList&& other) = delete;
	DoubleList* operator=(const DoubleList& other) = delete;
	DoubleList* operator=(DoubleList& other) = delete;

	bool isEmpty();
	void clean();
	void outAll();
	int getSize();

	bool insertBegin(int key);
	bool insertEnd(int key);
	bool delBegin();
	bool delEnd();
	bool del(int key);
	bool search(int key);

	void reverse();
	void replaceByAvarage();

};

