#pragma once
#include <iostream>
using namespace std;

template<typename T>
class TList {
protected:
	struct Node {
		Node* next;
		T value;

		Node(Node* next, T value) :next(next), value(value) {}
	};

	size_t sz = 0;
	Node* head = nullptr;

public:

	TList(int n = 0, T val = 0) {//constructor
		if (n < 0) throw "incorrect size";
		this->sz = n;
		head = new Node(this->head, val);
		this->head->next = this->head;
		while (n--) {
			Node* temp = new Node(this->head->next, 0);
			this->head->next = temp;
		}
	}

	~TList() {//destructor
		this->clear();
	}

	void clear() {
		Node* curr;
		while (this->head && this->head->next != this->head) {
			curr = this->head->next->next;
			delete this->head->next;
			this->head->next = curr;
		}
		delete this->head;
		sz = 0;
	}

	TList(const TList& other) {//copy constructor
		head = new Node(this->head, other.head->value);
		this->head->next = this->head;
		if (other.sz != 0) {
			this->sz = other.sz;
			Node* curr1 = other.head->next; 
			Node* curr2 = new Node(this->head, curr1->value); 
			this->head->next = curr2;

			while (!curr1) {
				Node* next1 = curr1->next;
				if (!next1) break; 
				curr2->next = new Node(this->head, next1->value); 
				curr2 = curr2->next; 
				curr1 = curr1->next; 
			}
		}
	}

	TList& operator=(const TList& other) {//operator= тут какая-то лажа, требуется отладка
		if (this == &other) return *this;
		this->clear();
		this->sz = other.sz;
		head = new Node(this->head, other.head->value);
		this->head->next = this->head;
		if (other.sz != 0) {
			Node* curr1 = other.head->next;
			Node* curr2 = new Node(this->head, curr1->value);
			this->head->next = curr2;
			while (curr1->next!= other.head) {
				curr2->next = new Node(this->head, curr1->next->value);
				curr2 = curr2->next;
				curr1 = curr1->next;
			}
		}
		return *this;
	}

	TList(TList&& other) {//move constructor
		this->sz = other.sz;
		this->head = other.head;

		other.sz = 0;
		other.head = nullptr;
	}

	TList& operator=(TList&& other) {
		this->sz = other.sz;
		this->head = other.head;

		other.sz = 0;
		other.head = nullptr;

		return *this;
	}

	size_t size() const {
		return this->sz;
	}

	class iterator {
	public:
		Node* it = nullptr;
	public:
		iterator(Node* node) : it(node) {}

		Node& operator*() { return *(this->it); }
		Node operator*() const { return *(this->it); }

		iterator& operator++() {
			this->it = this->it->next;
			return *this;
		}

		bool operator!=(iterator iter) const {
			return (this->it != iter.it);
		}

		bool operator==(iterator iter) const {
			return (this->it == iter.it);
		}
	};

	iterator begin() const {
		return iterator(this->head->next);
	}

	iterator end() const { return iterator(this->head); }

	T& at(iterator it) { return (*it).value; }
	T at(iterator it) const { return (*it).value; }

	//insert'ы и erase'ы

	iterator insert(T data, iterator prev) {
		Node* tmp = new Node(nullptr, data);
		tmp->next = prev.it->next;
		prev.it->next = tmp;
		this->sz++;
		return iterator(tmp);
	}

	iterator erase(iterator prev) {
		if (prev.it->next == this->head) throw "you can't erase head";
		Node* tmp = prev.it->next;
		prev.it->next = prev.it->next->next;
		delete tmp;
		this->sz--;

		return iterator(prev.it->next);
	}


	//сравнение
	bool operator==(const TList& other) const {
		if (this->sz != other.sz) return false;

		TList::iterator curr1 = this->begin(), curr2 = other.begin();
		for (; curr1 != this->end();) {
			if (this->at(curr1) != this->at(curr2)) return false;
			++curr1;
			++curr2;
		}
		return true;
	}

	bool operator!=(const TList& other) const{
		return !((*this) == other);
	}

	friend ostream& operator<<(ostream& ostr, const TList& l)
	{
		TList::iterator it = l.begin();
		for (; it != l.end(); ++it) {
			ostr << l.at(it) << " ";
		}

		return ostr;
	}
};