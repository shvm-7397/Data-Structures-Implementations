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
	protected :
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

	Node* find_max(Node* node) const {
		Node* itr = node, *current ;
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

	virtual Node* unhook_leaf(Node* target) {
		Node* p = target->parent ; 
		int lh = - 1, rh = -1 ;
		if (p->left and p->left->key == target->key) {
			lh = target->h ;
			if (p->right) rh = p->right->h ;
			if (lh > rh) --p->h ;
			p->left = nullptr ; 
		}
		else if (p->right and p->right->key == target->key) {
			rh = target->h ;
			if (p->left) lh = p->left->h ;
			if (rh > lh) --p->h ;
			p->right = nullptr ;
		}
		target->set(target->key) ;
		update_height_up(p) ;
		return target ;
	}

	int find_height(Node* root) ;
	void pre_order(Node* root) const ;
	void in_order(Node* root) const ;
	void post_order(Node* root) const ;
	void level_order(Node* root) const ;
	virtual void update_height_up(Node* node) ; 
	void swap_nodes(Node*& target, Node*& replacement) ;

	public :
	
	BST() { root = nullptr ; height = -1 ; size = 0 ; cout<<"Base BST class constructor\n" ; }
	int& get_height() { return height ; }
	int& get_size() { return size ; }
	
	void calculate_Tree_height() { height = find_height(root) ; }
	void pre_order() const { 
		if (!root) return ;
		pre_order(root) ; 
	}
	void in_order() const { 
		if (!root) return ;
		in_order(root) ; 
	}
	void post_order() const { 
		if (!root) return ;
		post_order(root) ; 
	}
	void level_order() const { 
		if (!root) {
			cout<<"Tree is Empty\n" ;
			return ;
		}
		level_order(root) ; 
	}
	
	virtual void insert(const Comparable& k) ; 
	bool find(const Comparable& k) const ;

	Comparable& get_max() const { return find_max(root)->key ; } 
	Comparable& get_min() const { return find_min(root)->key ; }
	Comparable& previous(const Comparable& k) const ;
	Comparable& next(const Comparable& k) const ;
	pair<Comparable, Comparable> neighbours(const Comparable& k) const ;
	deque<Comparable> find(const Comparable& a, const Comparable& b) const ;
	virtual void remove(const Comparable& k) ;
} ;

template<class Comparable>
void BST<Comparable>::update_height_up(Node* node) {
	Node* itr = node ; 
	while (itr != root) {
		itr = itr->parent ;
		int lh = -1, rh = -1 ;
		if (itr->left) lh = itr->left->h ;
		if (itr->right) rh = itr->right->h ;
		itr->h = 1 + max(lh, rh) ; 
	}
	height = root->h ;	
}

template<class Comparable>
void BST<Comparable>::swap_nodes(Node*& target, Node*& replacement) {
	swap(target->key, replacement->key) ;
	swap(target, replacement) ;
}

template<class Comparable>
void BST<Comparable>::insert(const Comparable& k) {
	Node* newNode = new Node(k) ;
	if (!root) root = newNode ;
	else {
		Node* candidate = find(root, k) ;
		newNode->parent = candidate ;
		if (k < candidate->key) candidate->left = newNode ;
		else if (k > candidate->key) candidate->right = newNode ;
		update_height_up(newNode) ;	
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
			if (current == root) cout<<current->key<<"("<<current->h<<",root)" ; 
			else cout<<current->key<<"("<<current->h<<","<<current->parent->key<<")  " ;
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
	Node* of = find(root, k) ; Node* lower_bound = find_min(root) ;
	if (k <= lower_bound->key) return lower_bound->key ;
	if (of->key < k) return of->key ; 
	Node* prev = inorder_predecessor(of) ;
	return prev->key ;
}

template<class Comparable>
Comparable& BST<Comparable>::next(const Comparable& k) const {
	Node* of = find(root, k) ; Node* upper_bound = find_max(root) ;
	if (k >= upper_bound->key) return upper_bound->key ;
	if (of->key > k) return of->key ;
	Node* after = inorder_successor(of) ;
	return after->key ;
}

template<class Comparable>
pair<Comparable, Comparable> BST<Comparable>::neighbours(const Comparable& k) const {
	Node* lower_bound = find_min(root), *upper_bound = find_max(root) ;
	pair<Comparable, Comparable> answer ;
	if (k < lower_bound->key or k > upper_bound->key) return pair<Comparable, Comparable>(lower_bound->key, upper_bound->key) ; 
	Node* candidate = find(root, k) ;
	Node* one_before, *one_after ;
	if (candidate->key == k) {
		if (k > lower_bound->key) one_before = inorder_predecessor(candidate) ;
		else one_before = lower_bound ;
		if (k < upper_bound->key) one_after = inorder_successor(candidate) ;
		else one_after = upper_bound ;
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
	// Range find()
	Node* lower_bound = find_min(root), *upper_bound = find_max(root) ;
	deque<Comparable> inbetween ;
	if (a >= upper_bound->key or b <= lower_bound->key) return inbetween ;
	Node* lower = find(root, a) ;
	if (lower->key == a) {
		while (lower->key >= a and lower->key <= b) {
			inbetween.push_back(lower->key) ;
			if (lower->key == upper_bound->key) break ;
			lower = inorder_successor(lower) ; 
		}
	}
	else if (lower->key < a) {
		while (lower->key <= b) {
			if (lower->key >= a) inbetween.push_back(lower->key) ;
			if (lower->key == upper_bound->key) break ;
			lower = inorder_successor(lower) ; 
		}	
	}
	else {
		Node* less = lower ;
		while (lower->key <= b) {
			inbetween.push_back(lower->key) ;
			if (lower->key == upper_bound->key) break ;
			lower = inorder_successor(lower) ;
		}
	}
	return inbetween ;
}

template<class Comparable>
void BST<Comparable>::remove(const Comparable& k) {
	Node* target = find(root, k) ;
	if (target->key != k) return ; // key not present
	
	if (size == 1) {
		// If there was just one node
		root = nullptr ;
		delete target ;
		--size ;
		return ;
	}

	if (target->h == 0) target = unhook_leaf(target) ; // target a leaf node
	else {
		// target not a leaf node
		Node* predecessor = nullptr, *successor = nullptr ;
		if (target->left) predecessor = inorder_predecessor(target) ;
		if (target->right) successor = inorder_successor(target) ;
		if (predecessor and predecessor->h == 0) {		// predecessor is a leaf
			swap_nodes(target, predecessor) ;
			target = unhook_leaf(target) ;
		}
		else if (successor and successor->h == 0) {		// successor is a leaf
			swap_nodes(target, successor) ;
			target = unhook_leaf(target) ;
		}
		else {
			// Neither predecessor nor successor a leaf
			Node* p = nullptr, *child = nullptr ;
			if (predecessor) {
				swap_nodes(target, predecessor) ;
				p = target->parent ;
				child = target->left ;
				child->set(child->key, p, child->left, child->right) ;
				if (p->left and p->left->key == target->key) p->set(p->key, p->parent, child, p->right) ;
				if (p->right and p->right->key == target->key) p->set(p->key, p->parent, p->left, child) ;
			}
			else if (successor) {
				swap_nodes(target, successor) ;
				p = target->parent ;
				child = target->right ;
				child->set(child->key, p, child->left, child->right) ;
				if (p->left and p->left->key == target->key) p->set(p->key, p->parent, child, p->right) ;
				if (p->right and p->right->key == target->key) p->set(p->key, p->parent, p->left, child) ;
			}
			target->set(target->key) ;
			update_height_up(child) ;
		}
	}
	delete target ;
	--size ;
}


#endif		// end of BST
