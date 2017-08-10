// BST Header 
// Shivam Sharma KNIT Sultanpur

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <deque>
#include <queue>
using namespace std ;

template <class Comparable>
class BST {
	
	// Type Node for Tree
	struct Node {
		Comparable key ;
		Node* parent ;
		Node* left ;
		Node* right ;
		int h ;

		Node() : key{Comparable{ }}, left{nullptr}, right{nullptr}, h{-1}, parent{nullptr} { }																	// default constructor
		Node(const Comparable& k, Node* parent = nullptr, Node* l = nullptr, Node* r = nullptr) : key{k}, left{l}, right{r}, h{0}, parent{nullptr} { }			// with inital values
		Node(const Comparable&& k, Node* parent = nullptr, Node* l = nullptr, Node* r = nullptr) : key{k}, left{l}, right{r}, h{0}, parent{nullptr} { }			// move constructor
		Node(const Node& rhs) : key{rhs.key}, left{rhs.left}, right{rhs.right}, h{rhs.h}, parent{rhs.parent} { } 							// copy constructor
		Node(const Node&& rhs) : key{move(rhs.key)}, left{move(rhs.left)}, right{move(rhs.right)}, h{move(rhs.h)}, parent{rhs.parent} { }	// copy move constructor
		Node& operator=(const Node& rhs) {																				// overloaded assigment 
			key = rhs.key ;
			parent = rhs.parent ;
			left = rhs.left ;
			right = rhs.right ;
			return *this ;
		}
		void set(const Comparable& k, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) { 
			key = k ; 
			parent = p ; 
			left = l ; 
			right = r ;
		}
	} ;
	Node* root ;
	int height ;
	int size ;


	Node* find(Node* root, const Comparable& k) const {
		if (k == root->key) return root ;
		Node* itr = root, *current ;
		while (true) {
			current = itr ;
			if (current->key == k) return current ;
			if (k > current->key) {
				if (!current->right) return current ;
				itr = itr->right ;
			}
			else if (k < current->key) {
				if (!current->left) return current ;
				itr = itr->left ;
			}
		}	
	}

	Node* find_max(Node* root) const {
		Node* itr = root, *current ;
		while (itr) {
			current = itr ;
			itr = itr->right ;
		}	
		return current ;
	}
	Node* find_min(Node* root) const {
		Node* itr = root, *current ;
		while (itr) {
			current = itr ;
			itr = itr->left ;
		}	
		return current ;
	}

	Node* inorder_predecessor(Node* node) const {
		if (!node->left) {
			Node* current = node, *p = node->parent ;
			while (current->key < p->key) {
				current = p ;
				p = current->parent ;
			}
			return p ;
		}
		return find_max(node->left) ;
	}
	Node* inorder_successor(Node* node) const {
		if (!node->right) {
			Node* current = node, *p = node->parent ;
			while (current->key > p->key) {
				current = p ;
				p = current->parent ;
			}
			return p ;	
		}
		return find_min(node->right) ;
	}

	Node* unhook_node(Node* node) {
		Node* p = node->parent ;
		if (!node->left and !node->right) {
			// Node is a leaf node. So its parent's left or right has to be set null
			if (node->key < p->key) p->left = nullptr ;
			else if (node->key > p->key) p->right = nullptr ;
		}
		node->set(node->key) ;	// Setting all three pointers of node as nullptr
		return node ;
	}
	int find_height(Node* root) ;
	void pre_order(Node* root) const ;
	void in_order(Node* root) const ;
	void post_order(Node* root) const ;
	void level_order(Node* root) const ; 

	public :
	
	BST() { root = nullptr ; height = -1 ; size = 0 ;}
	int& get_height() { return height ; }
	int& get_size() { return size ; }
	
	void calculate_Tree_height() { height = find_height(root) ; }
	void pre_order() const { pre_order(root) ; }
	void in_order() const { in_order(root) ; }
	void post_order() const { post_order(root) ; }
	void level_order() const { level_order(root) ; }
	
	void insert(const Comparable& k) ; 
	bool find(const Comparable& k) const ;

	Comparable& get_max() const { return find_max(root)->key ; } 
	Comparable& get_min() const { return find_min(root)->key ; }
	Comparable& previous(const Comparable& k) const ;
	Comparable& next(const Comparable& k) const ;
	pair<Comparable, Comparable> neighbours(const Comparable& k) const ;
	deque<Comparable> find(const Comparable& a, const Comparable& b) const ;
	void remove(const Comparable& k) ;
} ;

template<class Comparable>
void BST<Comparable>::insert(const Comparable& k) {
	Node* newNode = new Node(k) ;
	if (!root) root = newNode ;
	else {
		Node* candidate = find(root, k) ;
		newNode->parent = candidate ;
		if (k < candidate->key) candidate->left = newNode ;
		else if (k > candidate->key) candidate->right = newNode ;
		
	}
	++size ;
}

template<class Comparable>
int BST<Comparable>::find_height(Node* root) {
	/*Finds and Stores the height of each node*/
	if (!root) return -1 ;
	int left_height = find_height(root->left) ;
	int right_height = find_height(root->right) ;
	root->h =  1 + max(left_height, right_height) ;
	return root->h ;	
}

template<class Comparable>
void BST<Comparable>::pre_order(Node* root) const {
	if (!root) return ;
	cout<<root->key<<"  " ;
	pre_order(root->left) ;
	pre_order(root->right) ;
}

template<class Comparable>
void BST<Comparable>::in_order(Node* root) const {
	if (!root) return ;
	in_order(root->left) ;
	cout<<root->key<<"  " ;
	in_order(root->right) ; 
}

template<class Comparable> 
void BST<Comparable>::post_order(Node* root) const {
	if (!root) return ;
	post_order(root->left) ;
	post_order(root->right) ;
	cout<<root->key<<"  " ;
}

template<class Comparable>
void BST<Comparable>::level_order(Node* root) const {
	queue<Node*> q ;
	q.push(root) ;
	q.push(nullptr) ;
	while (!q.empty()) {
		Node* current = q.front() ;
		q.pop() ;
		if (!current) {
			cout<<"\n" ;
			q.push(nullptr) ;
		}
		else {
			cout<<current->key<<"  " ;
			if (current->left) q.push(current->left) ;
			if (current->right) q.push(current->right) ;
		}
		if (q.size() == 1 and q.front() == nullptr) {
			q.pop() ;
			cout<<"\n" ;	
		} 
	}
}

template<class Comparable>
bool BST<Comparable>::find(const Comparable& k) const {
	Node* candidate = find(root, k) ;
	if (candidate->key == k) return true ;
	return false ;
}

template<class Comparable>
Comparable& BST<Comparable>::previous(const Comparable& k) const {
	Node* of = find(root, k) ;
	if (of->key < k) return of->key ; 
	Node* prev = inorder_predecessor(of) ;
	return prev->key ;
}

template<class Comparable>
Comparable& BST<Comparable>::next(const Comparable& k) const {
	Node* of = find(root, k) ;
	if (of->key > k) return of->key ;
	Node* after = inorder_successor(of) ;
	return after->key ;
}

template<class Comparable>
pair<Comparable, Comparable> BST<Comparable>::neighbours(const Comparable& k) const {
	Node* candidate = find(root, k) ;
	Node* one_before, *one_after ;
	if (candidate->key == k) {
		one_before = inorder_predecessor(candidate) ;
		one_after = inorder_successor(candidate) ;
	}
	else {
		if (candidate->key < k) {
			one_before = candidate ;
			one_after = inorder_successor(candidate) ;
		}
		else {
			one_after = candidate ;
			one_before = inorder_predecessor(candidate) ;
		}
	}
	return pair<Comparable, Comparable>(one_before->key, one_after->key) ;
}

template<class Comparable>
deque<Comparable> BST<Comparable>::find(const Comparable& a, const Comparable& b) const {
	deque<Comparable> inbetween ;
	Node* lower = find(root, a) ;
	if (lower->key == a) {
		while (lower->key >= a and lower->key <= b) {
			inbetween.push_back(lower->key) ;
			lower = inorder_successor(lower) ; 
		}
	}
	else if (lower->key < a) {
		while (lower->key <= b) {
			if (lower->key >= a) inbetween.push_back(lower->key) ;
			lower = inorder_successor(lower) ; 
		}	
	}
	else {
		Node* less = lower ;
		while (lower->key > a) lower = inorder_predecessor(lower) ;
		while (lower->key <= b) {
			inbetween.push_back(lower->key) ;
			lower = inorder_successor(lower) ;
		}
	}
	return inbetween ;
}

template<class Comparable>
void BST<Comparable>::remove(const Comparable& k) {
	Node* target = find(root, k) ;
	if (target->left or target->right) {
		// Not a leaf
		Node* replacement, *p = target->parent ;
		if (target->left) {
			replacement = inorder_predecessor(target) ;
			replacement = unhook_node(replacement) ;
			replacement->set(replacement->key, p, target->left, target->right) ;
		}
		else if (!target->left) {
			replacement = target->right ;
			replacement->set(replacement->key, p, replacement->left, replacement->right) ;
		}
		if (target->key < p->key) p->left = replacement ;	
		else p->right = replacement ;
	}
	target = unhook_node(target) ;
	delete target ;
	--size ;
}

#endif		// end of BST