#pragma once
class DoubleList
{
private:
	class Node
	{
	public:
		int _key;
		Node* _prev;
		Node* _next;
		Node(int key = 0, Node* prev = nullptr, Node* next = nullptr) {
			_key = key;
			_prev = prev;
			_next = next;
		}
	};
	Node* _head;
	Node* _tail;
	size_t _size;

	bool delBegin();
	bool delEnd();
	bool del(Node* delNode);
	bool insertBegin(Node* newNode);
	bool insertEnd(Node* newNode);
	Node* searchNode(int key)const;
public:

	DoubleList();
	~DoubleList();
	DoubleList(const DoubleList& other) = delete;
	DoubleList(DoubleList&& other) = delete;
	DoubleList& operator=(const DoubleList& other) = delete;
	DoubleList& operator=(DoubleList& other) = delete;

	void clean();
	bool is_empty();
	void output_all();
	bool insertBegin(int key);
	bool insertEnd(int key);
	bool search(int key) const;
	bool del(int key);
	bool reverse();
};