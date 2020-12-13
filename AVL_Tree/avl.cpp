// AVL_Tree

#include "avl.h"

// -----------------------------------------------------------------------------------------------------------------------------

template <typename T>
AVL_Node<T>::AVL_Node(T const& key) {
	this->key = key;
	height = 1;
	left = nullptr;
	right = nullptr;
}

template<typename T>
int AVL_Node<T>::BalanceFactor() const {
	int r_height = (right == nullptr ? 0 : right->height);
	int l_height = (left == nullptr ? 0 : left->height);

	return l_height - r_height;
}

template<typename T>
void AVL_Node<T>::ChangeHeight() {
	int r_height = (right == nullptr ? 0 : right->height);
	int l_height = (left == nullptr ? 0 : left->height);

	height = std::max(r_height, l_height) + 1;
}

template<typename T>
AVL_Node<T>* AVL_Node<T>::BalanceTree() {
	ChangeHeight();

	switch (BalanceFactor()) {
	case 2:																
		if (left->BalanceFactor() > 0) {
			left = left->LeftRotate();
		}
		return RightRotate();
	case -2:															
		if (right->BalanceFactor() > 0) {
			right = right->RightRotate();
		}
		return LeftRotate();
	default:															
		return this;
	}
}

template<typename T>
AVL_Node<T>* AVL_Node<T>::LeftRotate() {
	AVL_Node<T>* curr_right = right;

	right = curr_right->left;
	ChangeHeight();

	curr_right->left = this;
	curr_right->ChangeHeight();

	return curr_right;
}

template<typename T>
AVL_Node<T>* AVL_Node<T>::RightRotate() {
	AVL_Node<T>* curr_left = left;

	left = curr_left->right;
	ChangeHeight();

	curr_left->right = this;
	curr_left->ChangeHeight();

	return curr_left;
}

template<typename T>
AVL_Node<T>* AVL_Node<T>::FindMinimum() const {
	AVL_Node* curr_node = const_cast<AVL_Node*>(this);
	if (curr_node != nullptr) {
		for (;;) {
			if (curr_node->left == nullptr) {
				break;
			}
			curr_node = curr_node->left;
		}
	}

	return curr_node;
}

template<typename T>
AVL_Node<T>* AVL_Node<T>::FindMaximum() const {
	AVL_Node* curr_node = const_cast<AVL_Node*>(this);
	if (curr_node != nullptr) {
		for (;;) {
			if (curr_node->right == nullptr) {
				break;
			}
			curr_node = curr_node->right;
		}
	}

	return curr_node;
}

template<typename T>
AVL_Node<T>* AVL_Node<T>::RemoveMinimum() {
	AVL_Node* curr_node = this;

	if (curr_node == nullptr) {
		return nullptr;
	}
	else if (curr_node->left == nullptr) {
		--curr_node->right->height;
		AVL_Node* copy_right = curr_node->right;
		delete curr_node;

		return copy_right;
	}
	else {
		std::stack<AVL_Node<T>*> ptrs_parents;
		ptrs_parents.push(curr_node);

		while (curr_node->left->left != nullptr) {
			curr_node = curr_node->left;
			ptrs_parents.push(curr_node);
		}

		AVL_Node* copy_left = curr_node->left;
		curr_node->left = copy_left->right;
		delete copy_left->left;

		while (!ptrs_parents.empty()) {
			curr_node = ptrs_parents.top();
			ptrs_parents.pop();
			curr_node->BalanceTree();
		}

		return curr_node->left;
	}
}

template<typename T>
AVL_Node<T>* AVL_Node<T>::insert(T const& key) {
	AVL_Node<T>* curr_node;
	AVL_Node<T>* curr_parent = this;

	for (;;) {
		curr_node = (key > curr_parent->key) ? curr_parent->right : curr_parent->left;

		if (curr_node == nullptr) {
			if (key > curr_parent->key) {
				curr_parent->right = new AVL_Node<T>(key);
			}
			else {
				curr_parent->left = new AVL_Node<T>(key);
			}
			break;
		}

		curr_parent = curr_node;
	}

	return BalanceTree();
}

template<typename T>
AVL_Node<T>* AVL_Node<T>::remove(const T& key) {
	if (this == nullptr) {
		return nullptr;
	}
	if (key < this->key) {
		left = left->remove(key);
		return BalanceTree();
	}
	else if (key > this->key) {
		right = right->remove(key);
		return BalanceTree();
	}
	else {
		AVL_Node* l_child = left;
		AVL_Node* r_child = right;

		delete this;
		if (r_child == nullptr) {
			return l_child;
		}

		AVL_Node* rmin_child = r_child->FindMinimum();
		rmin_child->right = r_child->RemoveMinimum();
		rmin_child->left = l_child;
		return rmin_child->BalanceTree();
	}
}

template<typename T>
T AVL_Node<T>::next(T const& key) const {
	AVL_Node* curr_node = const_cast<AVL_Node*>(this);
	
	while (key != curr_node->key && curr_node != nullptr) {
		key > curr_node->key ? curr_node = curr_node->right : curr_node = curr_node->left;
	}

	if (curr_node == nullptr) return 0;
	else {
		AVL_Node* min_node = curr_node->right->FindMinimum();
		if (min_node == nullptr) return 0;
		else {
			return min_node->key;
		}
	}
}

template<typename T>
T AVL_Node<T>::prev(T const& key) const {
	AVL_Node* curr_node = const_cast<AVL_Node*>(this);

	while (key != curr_node->key && curr_node != nullptr) {
		key > curr_node->key ? curr_node = curr_node->right : curr_node = curr_node->left;
	}

	if (curr_node == nullptr) return 0;
	else {
		AVL_Node* max_node = curr_node->left->FindMaximum();
		if (max_node == nullptr) return 0;
		else {
			return max_node->key;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------

template<typename T>
AVL_Tree<T>::AVL_Tree() {
	root = nullptr;
}

template<typename T>
bool AVL_Tree<T>::insert(T const& key) {
	if (root == nullptr) {
		root = new AVL_Node<T>(key);
	}
	else {
		root = root->insert(key);
	}
	return true;
}

template<typename T>
bool AVL_Tree<T>::find(T const& key) const {
	AVL_Node<T>* curr_node = root;

	while (curr_node != nullptr) {
		if (key == curr_node->key) {
			return true;
		}
		else if (key > curr_node->key) {
			curr_node = curr_node->right;
		}
		else {
			curr_node = curr_node->left;
		}
	}
	return false;
}

template<typename T>
bool AVL_Tree<T>::remove(T const& key) {
	root = root->remove(key);
	if (root != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
T AVL_Tree<T>::next(T const& key) const {
	return root->next(key);
}

template<typename T>
T AVL_Tree<T>::prev(T const& key) const {
	return root->prev(key);
}

template<typename T>
void AVL_Tree<T>::Print_AVL_Node(AVL_Node<T>* node) const {
	std::cout << "\nAVL_Node_Height: " << node->height << "\nAVL_Node_Key:\n" << node->key << std::endl;
}

template<typename T>
void AVL_Tree<T>::Inorder_Walk(AVL_Node<T>* Obj, void(*myFcn)(AVL_Node<T>*)) {
	if (Obj != nullptr) {
		Inorder_Walk(Obj->left, myFcn);
		myFcn(Obj);
		Inorder_Walk(Obj->right, myFcn);
	}
}

template<typename T>
void AVL_Tree<T>::Preorder_Walk(AVL_Node<T>* Obj, void(*myFcn)(AVL_Node<T>*)) {
	if (Obj != nullptr) {
		myFcn(Obj);
		Preorder_Walk(Obj->left, myFcn);
		Preorder_Walk(Obj->right, myFcn);
	}
}

template<typename T>
void AVL_Tree<T>::Postorder_Walk(AVL_Node<T>* Obj, void(*myFcn)(AVL_Node<T>*)) {
	if (Obj != nullptr) {
		Postorder_Walk(Obj->left, myFcn);
		Postorder_Walk(Obj->right, myFcn);
		myFcn(Obj);
	}
}

