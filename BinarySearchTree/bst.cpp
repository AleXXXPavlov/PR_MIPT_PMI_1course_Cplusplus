// BINARY SEARCH TREE

#include "bst.h"

// ----------------------------------------------- Public-методы -----------------------------------------------

bool BST::insert(keytype key) {
	if (root_ == nullptr) {
		root_ = new Node(key);
		return true;
	}

	Node* curr_parent = root_;
	for (;;) {
		Node* curr_node = (key <= curr_parent->key_) ? curr_parent->left_ : curr_parent->right_;

		if (curr_node == nullptr) {
			if (key <= curr_parent->key_) curr_parent->left_ = new Node(key);
			else						  curr_parent->right_ = new Node(key);

			return true;
		}
		curr_parent = curr_node;
	}

	return true;
}

bool BST::find(keytype key, Node* node = nullptr) const {
	Node* add_node = node;
	while (add_node != nullptr) {
		if (add_node->key_ == key)	   return true;
		else if (add_node->key_ > key) add_node = add_node->right_;								// поиск в правом поддереве	
		else						   add_node = add_node->left_;								// поиск в левом поддереве
	}

	return false;             
}

bool BST::remove(Node* node) {
	if (node == nullptr) return false;											// нельзя удалить какой-либо элемент из несуществующего дерева
	// если нет потомков
	if (node->left_ == nullptr && node->right_ == nullptr) {
		Node* parent = SearchParent(node);
		parent->left_ == node ? parent->left_ = nullptr : parent->right_ = nullptr;

		delete node; 
		node = nullptr;
		return true;
	}
	// если существует ровно одно поддерево потомков
	else if ((node->left_ != nullptr && node->right_ == nullptr) || (node->right_ == nullptr && node->left_ == nullptr)) {
		Node* child;															// единственный потомок
		node->left_ == nullptr ? child = node->right_ : child = node->left_;
		node = child;

		delete child;
		child = nullptr;
	}
	// если существуют оба потомка
	else {
		Node* node_max_left = SearchMaxLeft(node->right_);						// самый левый элемент правого поддерева удаляемого элемента
		Node* parent = SearchParent(node_max_left);
		
		// если у самого левого элемента нет поддеревьев 
		if (node_max_left->right_ == nullptr) {
			node->key_ = node_max_left->key_;
			
			delete node_max_left;
			node_max_left = nullptr;
			parent->left_ = nullptr;
		}
		// если есть правое поддерево
		else {
			node->key_ = node_max_left->key_;
			node_max_left = node_max_left->right_;
		}

		return true;
	}
}

bool BST::RemoveTree(Node* node) {
	if (node == nullptr) return true;

	if (node->left_ != nullptr)	 RemoveTree(node->left_);
	if (node->right_ != nullptr) RemoveTree(node->right_);

	delete node;
	node = nullptr;
	return true;
}

void BST::Print_Key(Node* Obj) const {
	std::cout << Obj->key_ << std::endl;
}

void BST::Inorder_Walk(Node* Obj, void(*myFcn)(Node*)) {
	if (Obj != nullptr) {
		Inorder_Walk(Obj->left_, myFcn);
		myFcn(Obj);
		Inorder_Walk(Obj->right_, myFcn);
	}
}

void BST::Preorder_Walk(Node* Obj, void(*myFcn)(Node*)) {
	if (Obj != nullptr) {
		myFcn(Obj);
		Preorder_Walk(Obj->left_, myFcn);
		Preorder_Walk(Obj->right_, myFcn);
	}
}

void BST::Postorder_Walk(Node* Obj, void(*myFcn)(Node*)) {
	if (Obj != nullptr) {
		Postorder_Walk(Obj->left_, myFcn);
		Postorder_Walk(Obj->right_, myFcn);
		myFcn(Obj);
	}
}

// ----------------------------------------------- Private-методы -----------------------------------------------
Node* BST::SearchMaxLeft(Node* node) const {
	if (node == nullptr)		return nullptr;						// нельзя найти минимальный элемент в несуществующем дереве

	if (node->left_ != nullptr) SearchMaxLeft(node->left_);			// поиск самого левого элемента в левом поддереве
	else						return node;
}

Node* BST::SearchMaxRight(Node* node) const {
	if (node == nullptr)		return nullptr;						// нельзя найти максимальный элемент в несуществующем дереве

	if (node->right_ != nullptr) SearchMaxLeft(node->right_);		// поиск самого левого элемента в левом поддереве
	else						return node;
}

Node* BST::SearchParent(Node* node) const {
	
	static Node* parent = root_;
	if (node == nullptr || node == root_) {
		delete parent;
		return nullptr;												// нельзя найти родителя у несуществующего элемента или у корня дерева
	}
	
	Node* child;
	node->key_ > parent->key_ ? child = parent->right_ : child = parent->left_;

	if (node->key_ > child->key_) {
		parent = child;
		return SearchParent(parent->right_);
	}
	else if (node->key_ < child->key_) {
		parent = child;
		return SearchParent(parent->left_);
	}
	else {
		return parent; 
	}
}

// ---------------------------------------------------------------------------------------------------------

