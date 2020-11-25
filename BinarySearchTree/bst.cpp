// BINARY SEARCH TREE

#include <iostream>

using keytype = int;

class BST {
public:
	class Node {
	public:
		keytype key_ = 0;									// значение 
		Node* left_ = nullptr;								// указатель на левого потомка 
		Node* right_ = nullptr;								// указатель на правого потомка
				
		Node(keytype key) {
			key_ = key;
		}
	};

	Node* root_ = nullptr;									// корень дерева

	// Основные методы для работы с деревом
	bool insert(keytype);									// добавление в дерево элемента, если оно непусто, иначе создать корень
	BST::Node* find(keytype, Node*) const;					// возвращение ссылки на элемент, если он есть в дереве, в противном случае, nullptr
	bool remove(keytype, Node*);							// удаление элемента из дерева

	// Обход дерева 
	keytype Get_Key(Node*) const;							// функция, применяемая при обходе дерева

	void Inorder_Walk(Node*, keytype (*myFcn)(Node*));		// обход по порядку: левое поддерево, вершина, правое поддерево
	void Preorder_Walk(Node*, keytype(*myFcn)(Node*));		// обход по порядку: вершина, левое поддерево, правое поддерево
	void Postorder_Walk(Node*, keytype(*myFcn)(Node*));		// обход по порядку: левое поддерево, правое поддерево, вершина

private:
	Node* SearchMaxLeft(Node*) const;						// минимальный элемент рассматриваемого поддерева
	Node* SearchMaxRight(Node*) const;						// максимальный элемент рассматриваемого поддерева
	Node* SearchParent(Node*) const;						// поиск родителя
};

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

BST::Node* BST::find(keytype key, Node* node = nullptr) const {
	// если дерево пусто
	if (root_ == nullptr) {
		return nullptr;
	}

	if (node == nullptr) node = root_;								// поиск элемента для удаления начинаеться с корня дерева

	// сравнение со значением в корне
	if (key > node->key_)		return find(key, node->right_);		// поиск в правом поддереве			
	else if (key < node->key_)  return find(key, node->left_);		// поиск в левом поддереве
	else						return node;						// при равенстве возвращаем ссылку на корень поддерева
}

bool BST::remove(keytype key, Node* node = nullptr) {
	Node* node_rem = find(key, node);

	if (node_rem == nullptr) return false;										// нельзя удалить какой-либо элемент из несуществующего дерева

	// если нет потомков
	if (node->left_ == nullptr && node->right_ == nullptr) {
		delete[] node;
		node = nullptr;
		return true;
	}
	// если существует ровно одно поддерево потомков
	else if ((node->left_ == nullptr) + (node->right_ == nullptr) == 1) {
		Node* child;															// единственный потомок
		node->left_ == nullptr ? child = node->right_ : child = node->left_;

		node->key_ = child->key_;
		node->right_ = child->right_;
		node->left_ = child->left_;

		delete[] child;
		child = nullptr;
	}
	// если существуют оба потомка
	else {
		Node* node_max_left = SearchMaxLeft(node->right_);						// самый левый элемент правого поддерева удаляемого элемента

		// если у самого левого элемента нет поддеревьев 
		if (node_max_left->right_ == nullptr) {
			node->key_ = node_max_left->key_;

			delete[] node_max_left;
			node_max_left = nullptr;
		}
		// если есть правое поддерево
		else {
			node->key_ = node_max_left->key_;

			Node* parent_nml = SearchParent(node_max_left);
			parent_nml->left_ = node_max_left->right_;

			delete[] node_max_left;
			node_max_left = nullptr;
		}
	}
}

keytype BST::Get_Key(Node* Obj) const {
	return Obj->key_;
}

void BST::Inorder_Walk(Node* Obj, keytype (*myFcn)(Node*)) {
	if (Obj != nullptr) {
		Inorder_Walk(Obj, myFcn);
		std::cout << myFcn(Obj) << std::endl;
		Inorder_Walk(Obj, myFcn);
	}
}

void BST::Preorder_Walk(Node* Obj, keytype(*myFcn)(Node*)) {
	if (Obj != nullptr) {
		std::cout << myFcn(Obj) << std::endl;
		Preorder_Walk(Obj, myFcn);
		Preorder_Walk(Obj, myFcn);
	}
}

void BST::Postorder_Walk(Node* Obj, keytype(*myFcn)(Node*)) {
	if (Obj != nullptr) {
		Postorder_Walk(Obj, myFcn);
		Postorder_Walk(Obj, myFcn);
		std::cout << myFcn(Obj) << std::endl;		
	}
}

// ----------------------------------------------- Private-методы -----------------------------------------------
BST::Node* BST::SearchMaxLeft(Node* node) const {
	if (node == nullptr)		return nullptr;						// нельзя найти минимальный элемент в несуществующем дереве

	if (node->left_ != nullptr) SearchMaxLeft(node->left_);			// поиск самого левого элемента в левом поддереве
	else						return node;
}

BST::Node* BST::SearchMaxRight(Node* node) const {
	if (node == nullptr)		return nullptr;						// нельзя найти максимальный элемент в несуществующем дереве

	if (node->right_ != nullptr) SearchMaxLeft(node->right_);		// поиск самого левого элемента в левом поддереве
	else						return node;
}

BST::Node* BST::SearchParent(Node* node) const {
	if (node == nullptr || node == root_) return nullptr;			// нельзя найти родителя у несуществующего элемента или у корня дерева

	static Node* parent = root_;
	Node* child;
	node->key_ > parent->key_ ? child = node->right_ : child = node->left_;

	if (node->key_ > child->key_) {
		parent = child;
		return SearchParent(child->right_);
	}
	else if (node->key_ < child->key_) {
		parent = child;
		return SearchParent(child->left_);
	}
	else {
		return parent;
	}
}

// ---------------------------------------------------------------------------------------------------------
