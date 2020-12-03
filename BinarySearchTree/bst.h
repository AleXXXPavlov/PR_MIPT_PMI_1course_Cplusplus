#ifndef _BST_
#define _BST_

#include <iostream>

using keytype = int;

class Node {
public:
	keytype key_ = 0;									// �������� 
	Node* left_ = nullptr;								// ��������� �� ������ ������� 
	Node* right_ = nullptr;								// ��������� �� ������� �������

	Node() = default;
	Node(keytype key) {
		key_ = key;
	}

	Node& operator= (Node* Obj) {
		key_ = Obj->key_;
		left_ = Obj->left_;
		right_ = Obj->right_;

		return *this;
	}

	bool operator== (Node* Obj) {
		return ((key_ == Obj->key_) && (left_ == Obj->left_));
	}

	~Node() {
		key_ = 0;
		left_ = nullptr;
		right_ = nullptr;
	}
};

class BST {
public:
	Node* root_ = nullptr;									// ������ ������

	// �������� ������ ��� ������ � �������
	bool insert(keytype);									// ���������� � ������ ��������, ���� ��� �������, ����� ������� ������
	Node* find(keytype, Node*) const;						// ����������� ������ �� �������, ���� �� ���� � ������, � ��������� ������, nullptr
	bool remove(keytype);									// �������� �������� �� ������
	bool RemoveTree(Node*);									// ��� �������� ��������� ��� ������ ������

	// ����� ������ 
	keytype Get_Key(Node*) const;							// �������, ����������� ��� ������ ������

	void Inorder_Walk(Node*, keytype(*myFcn)(Node*));		// ����� �� �������: ����� ���������, �������, ������ ���������
	void Preorder_Walk(Node*, keytype(*myFcn)(Node*));		// ����� �� �������: �������, ����� ���������, ������ ���������
	void Postorder_Walk(Node*, keytype(*myFcn)(Node*));		// ����� �� �������: ����� ���������, ������ ���������, �������

private:
	Node* SearchMaxLeft(Node*) const;						// ����������� ������� ���������������� ���������
	Node* SearchMaxRight(Node*) const;						// ������������ ������� ���������������� ���������
	Node* SearchParent(Node*) const;						// ����� ��������
};

#endif 