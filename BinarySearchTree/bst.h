#ifndef _BST_
#define _BST_

#include <iostream>

using keytype = int;

class Node {
public:
	keytype key_ = 0;									// значение 
	Node* left_ = nullptr;								// указатель на левого потомка 
	Node* right_ = nullptr;								// указатель на правого потомка

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
	Node* root_ = nullptr;									// корень дерева

	// Основные методы для работы с деревом
	bool insert(keytype);									// добавление в дерево элемента, если оно непусто, иначе создать корень
	bool find(keytype, Node*) const;						// возвращение ссылки на элемент, если он есть в дереве, в противном случае, nullptr
	bool remove(Node*);									// удаление элемента из дерева
	bool RemoveTree(Node*);									// для удаления поддерева или целого дерева

	// Обход дерева 
	void Print_Key(Node*) const;							// функция, применяемая при обходе дерева

	void Inorder_Walk(Node*, keytype(*myFcn)(Node*));		// обход по порядку: левое поддерево, вершина, правое поддерево
	void Preorder_Walk(Node*, keytype(*myFcn)(Node*));		// обход по порядку: вершина, левое поддерево, правое поддерево
	void Postorder_Walk(Node*, keytype(*myFcn)(Node*));		// обход по порядку: левое поддерево, правое поддерево, вершина

private:
	Node* SearchMaxLeft(Node*) const;						// минимальный элемент рассматриваемого поддерева
	Node* SearchMaxRight(Node*) const;						// максимальный элемент рассматриваемого поддерева
	Node* SearchParent(Node*) const;						// поиск родителя
};

#endif 
