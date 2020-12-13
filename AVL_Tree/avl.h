#ifndef _AVL_
#define _AVL_


#include <stack>

// --------------------------------------------------------------------------------------------------------------------------

template<typename T>
class AVL_Node {
public:
	T key;												// значение узла
	int height;											// высота дерева, чьим корнем ялвяется этот узел
	AVL_Node* left;											// указатель на левого потомка
	AVL_Node* right;										// указатель на правого потомка

	AVL_Node(T const&);										// конструктор с параметром

	// основные методы для работы
	AVL_Node* insert(T const&);									// вставка листа в дерево, чьим корнем является этот узел
	AVL_Node* remove(T const&);									// удаление узла
	T next(T const&) const;										// минимальный элемент в дереве, больший данного
	T prev(T const&) const;										// максимальный элемент в дереве, меньший данного

	// методы для сохранения баланса дерева
	int BalanceFactor() const;									// получение модуля разности высот правого и левого поддерева
	void ChangeHeight();										// смена высоты, для поддержания баланса дерева
	AVL_Node* BalanceTree();									// балансировка дерева, при разности высот в поддеревьях большей единице
	AVL_Node* LeftRotate();										// левый поворот дерева, чьим корнем является этот узел
	AVL_Node* RightRotate();									// правый поворот дерева, чьим корнем является этот узел

	// дополнительные методы
	AVL_Node* FindMinimum() const;									// поиск минимального элемента в дереве
	AVL_Node* FindMaximum() const;									// поиск максимального элемента в дереве
	AVL_Node* RemoveMinimum();									// удаление минимального элемента в дереве
};

template<typename T>
class AVL_Tree {
public:
	AVL_Node<T>* root;										// корень дерева

	AVL_Tree();											// конструктор по-умолчанию

	// основные методы для работы с деревом
	bool insert(T const&);										// вставка листа в дерево
	bool find(T const&) const;									// поиск элемента в дереве
	bool remove(T const&);										// удаление элемента в дереве
	T next(T const&) const;										// поиск минимального элемента в дереве, большего данного
	T prev(T const&) const;										// поиск максимального элемента в дереве, меньшего данного

	// Обход дерева 
	void Print_AVL_Node(AVL_Node<T>*) const;							// функция, применяемая при обходе дерева

private:
	void Inorder_Walk(AVL_Node<T>*, void(*myFcn)(AVL_Node<T>*));					// обход по порядку: левое поддерево, вершина, правое поддерево
	void Preorder_Walk(AVL_Node<T>*, void(*myFcn)(AVL_Node<T>*));					// обход по порядку: вершина, левое поддерево, правое поддерево
	void Postorder_Walk(AVL_Node<T>*, void(*myFcn)(AVL_Node<T>*));					// обход по порядку: левое поддерево, правое поддерево, вершина
};

#endif 
