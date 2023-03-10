#include "DoubleList.h"
#include <iostream>

DoubleList::DoubleList() {
	_size = 0;
	_head = nullptr;
	_tail = nullptr;
}
DoubleList::~DoubleList() {
	clean();
}

bool DoubleList::isEmpty() {
	return (_head == nullptr && _tail == nullptr);
}
void DoubleList::outAll() {
	if (isEmpty()) {
		std::cout << "List is empty.";
	}
	else {
		Node* temp = this->_head;
		while (temp != nullptr) {
			std::cout << temp->_key << " ";
			temp = temp->_next;
		}
	}
}
int DoubleList::getSize() {
	return this->_size;
}

bool DoubleList::insertNodeBegin(Node* newNode) {
	if (newNode == nullptr) {
		return false;
	}
	if (isEmpty()) {
		_head = newNode;
		_tail = newNode;
		_size++;
		return true;
	}
	newNode->_next = this->_head;
	this->_head->_prev = newNode;
	this->_head = newNode;
	this->_size++;
	return true;
}
bool DoubleList::insertNodeEnd(Node* newNode) {
	if (newNode == nullptr) {
		return false;
	}
	if (isEmpty()) {
		_head = newNode;
		_tail = newNode;
		_size++;
		return true;
	}
	newNode->_prev = this->_tail;
	this->_tail->_next = newNode;
	this->_tail = newNode;
	this->_size++;
	return true;
}
bool DoubleList::insertBegin(int key) {
	try {
		Node* temp = new Node(key);
		if (!insertNodeBegin(temp)) {
			throw std::exception("failed to insert node in head");
			return false;
		}
		return true;
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error: " << e.what();
		exit(-1);
	}
}
bool DoubleList::insertEnd(int key) {
	try {
		Node* temp = new Node(key);
		if (!insertNodeEnd(temp)) {
			throw std::exception("failed to insert node in tail");
			return false;
		}
		return true;
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error: " << e.what();
		exit(-1);
	}
}

bool DoubleList::delNodeBegin() {
	if (this->_head == nullptr) {
		return false;
	}
	Node* temp = this->_head;
	if (temp->_next != nullptr) {
		temp->_next->_prev = nullptr;
		this->_head = temp->_next;
	}
	else {
		this->_head = nullptr;
		this->_tail = nullptr;
	}
	delete temp;
	this->_size--;
	return true;
}
bool DoubleList::delNodeEnd() {
	if (this->_tail == nullptr) {
		return false;
	}
	Node* temp = this->_tail;
	if (temp->_prev != nullptr) {
		temp->_prev->_next = nullptr;
		this->_tail = temp->_prev;
	}
	else {
		this->_head = nullptr;
		this->_tail = nullptr;
	}
	delete temp;
	this->_size--;
	return true;
}
bool DoubleList::delNode(Node* delNode) {
	if (isEmpty()) {
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
bool DoubleList::delBegin() {
	if (!delNodeBegin()) {
		throw std::exception("failed to delete node in begin");
		return false;
	}
	return true;
}
bool DoubleList::delEnd() {
	if (!delNodeEnd()) {
		throw std::exception("failed to delete node in begin");
		return false;
	}
	return true;
}
bool DoubleList::del(int key) {
	try {
		if (isEmpty()) {
			throw std::exception("failed to delete empty list.");
			return false;
		}
		if (!search(key)) {
			throw std::exception("failed to delete unreal key.");
			return false;
		}
		Node* temp = searchNode(key);
		if (!delNode(temp)) {
			throw std::exception("failed to delete node.");
			return false;
		}
		return true;
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
		exit(-1);
	}
	
}

void DoubleList::clean() {
	while (!isEmpty()) {
		delNodeEnd();
	}
}

DoubleList::Node* DoubleList::searchNode(int key) {
	if (isEmpty()) {
		return nullptr;
	}
	Node* temp = this->_head;
	while (temp != nullptr) {
		if (temp->_key == key) {
			return temp;
		}
		temp = temp->_next;
	}
	return nullptr;
}
bool DoubleList::search(int key) {
	if (searchNode(key) == nullptr) {
		return false;
	}
	return true;
}

void DoubleList::reverse() {
	if (isEmpty()) {
		return;
	}
	Node* tempH = this->_head;
	while (tempH != nullptr) {
		Node* tempPrev = tempH->_prev;
		tempH->_prev = tempH->_next;
		tempH->_next = tempPrev;
		tempH = tempH->_prev;
	}
	Node* tempT = this->_tail;
	this->_tail = this->_head;
	this->_head = tempT;
	return;

}

void DoubleList::replaceByAvarage() {
	if (isEmpty()) {
		return;
	}
	if (this->_size % 2 != 0) {
		delEnd();
	}
	Node* tempH = this->_head;
	while (tempH != nullptr) {
		tempH->_key = (tempH->_key + tempH->_next->_key) / 2;
		tempH->_next = tempH->_next->_next;
		this->_size--;
		tempH = tempH->_next;
	}
}