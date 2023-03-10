#include "DoubleList.h"
#include <iostream>

DoubleList::DoubleList() {
	_head = nullptr;
	_tail = nullptr;
	_size = 0;
}
DoubleList::~DoubleList() {
	clean();
}

bool DoubleList::is_empty() {
	return (this->_head == nullptr && this->_tail == nullptr);
}
bool DoubleList::insertBegin(Node* newNode) {
	if (newNode == nullptr) {
		return false;
	}
	if (is_empty()) {
		this->_head = newNode;
		this->_tail = newNode;
		return true;
	}
	else {
		newNode->_next = this->_head;
		this->_head->_prev = newNode;
		this->_head = newNode;
		return true;
	}
	return false;
}
bool DoubleList::insertBegin(int key) {
	try {
		Node* temp = new Node(key);
		if (!insertBegin(temp))
		{
			throw std::exception("Failed to insert element into list");
			return false;
		}
		this->_size++;
		return true;
	}
	catch (std::bad_alloc e) {
		std::cerr << "Error:" << e.what();
		exit(-1);
	}
}
bool DoubleList::insertEnd(Node* newNode) {
	if (newNode == nullptr) {
		return false;
	}
	if (is_empty()) {
		this->_head = newNode;
		this->_tail = newNode;
		return true;
	}
	else {
		newNode->_prev = this->_tail;
		this->_tail->_next = newNode;
		this->_tail = newNode;
		return true;
	}
	return false;
}
bool DoubleList::insertEnd(int key) {
	try {
		Node* temp = new Node(key);
		if (!insertEnd(temp)) {
			throw std::exception("Failed to insert element into list");
			return false;
		}
		this->_size++;
		return true;
	}
	catch (std::bad_alloc &e) {
		std::cerr << "Error:" << e.what();
		exit(-1);
	}
}
void DoubleList::output_all() {
	if (is_empty()) {
		std::cout << "List is empty.";
	}
	Node* temp = this->_head;
	while (temp != nullptr) {
		std::cout << temp->_key << " ";
		temp = temp->_next;
	}
}
bool DoubleList::delBegin() {
	if (this->_head == nullptr) {
		return false;
	}
	Node* temp = this->_head;
	if (temp->_next != nullptr) {
		temp->_next->_prev = nullptr;
	}
	else if (temp->_next == nullptr) {
		this->_tail = temp->_next;
	}
	this->_head = temp->_next;
	delete temp;
	this->_size--;
	return true;
}
bool DoubleList::delEnd() {
	if (this->_tail == nullptr) {
		return false;
	}
	Node* temp = this->_tail;
	if (temp->_prev != nullptr) {
		temp->_prev->_next = nullptr;
	}
	else if (temp->_prev == nullptr) {
		this->_head = temp->_prev;
	}
	this->_tail = temp->_prev;
	delete temp;
	this->_size--;
	return true;
}
bool DoubleList::del(Node* delNode) {
	if (is_empty()) {
		return false;
	}
	if (delNode == nullptr) {
		return false;
	}
	if (delNode == this->_head) {
		return delBegin();
	}
	if (delNode == this->_tail) {
		return delEnd();
	}
	else {
		Node* temp = this->_head;
		while (temp != delNode) {
			temp = temp->_next;
		}
		Node* tempPrev = temp->_prev;
		Node* tempNext = temp->_next;
		tempPrev->_next = tempNext;
		tempNext->_prev = tempPrev;
		delete temp;
		this->_size--;
		return true;
	}
	throw std::exception("Failed to delet node.");
	return false;
}
bool DoubleList::del(int key) {
	try {
		if (is_empty()) {
			throw std::exception("Failed to delete key - list is empty");
			return false;
		}
		if (!search(key)) {
			throw std::exception("Failed to delete key - it isn't in");
			return false;
		}
		Node* temp = searchNode(key);
		if (!this->del(temp)) {
			throw std::exception("Failed to delete key from list");
			return false;
		}
		return true;
	}
	catch (std::exception e) {
		std::cerr << "Error:" << e.what();
		exit(-1);
	}
}
void DoubleList::clean() {
	while (!is_empty()) {
		delEnd();
	}
}
DoubleList::Node* DoubleList::searchNode(int key)const {
	Node* temp = this->_head;
	while (temp != nullptr) {
		if (temp->_key == key) {
			return temp;
		}
		temp = temp->_next;
	}
	return nullptr;
}
bool DoubleList::search(int key) const {
	if (searchNode(key) == nullptr) {
		return false;
	}
	return true;
}
bool DoubleList::reverse() {

	Node* tempH = this->_head;
	while (tempH != nullptr) {
		Node* tempCur = tempH->_prev;
		tempH->_prev = tempH->_next;
		tempH->_next = tempCur;
		tempH = tempH->_prev;
	}
	Node* tempT = this->_tail;
	this->_tail = this->_head;
	this->_head = tempT;
	return true;
}