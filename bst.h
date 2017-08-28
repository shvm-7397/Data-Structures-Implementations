// BST Header 
// Shivam Sharma KNIT Sultanpur

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <deque>
#include <queue>
using namespace std ;


/*BST Class Template*/
template <class Comparable>
class BST {
	
	protected :	
	/*Type Node for BST*/
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
			h = rhs.h ;
			return *this ;
		}
		void set(const Comparable& k, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) { 
			key = k ; 
			parent = p ; 
			left = l ; 
			right = r ;
		}
		void set(const Comparable& k, const int& height, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) { 
			key = k ;
			h = height ; 
			parent = p ; 
			left = l ; 
			right = r ;
		}
		
	} ;
	/*End of Type Node*/

	// Data Members for class BST
	Node* root ;
	int height ;
	int size ;

	// Protected Methods for BST
	Node* merge_with_root(Node* sroot, Node* lroot, const Comparable& k) ;
	Node* merge(Node* sroot, Node* lroot) ;
	pair<Node*, Node*> split(Node* root, const Comparable& k) ;
	Node* clone(const BST<Comparable>& Obj) ; //Done
	Node* find(Node* root, const Comparable& k) const ; //Done
	Node* find_max(Node* node) const ; //Done
	Node* find_min(Node* root) const ; //Done
	Node* inorder_predecessor(Node* node) const ;	//Done
	Node* inorder_successor(Node* node) const ; //Done
	void pre_order(Node* root) const ; //Done
	void in_order(Node* root) const ; //Done
	void post_order(Node* root) const ; //Done
	void level_order(Node* root) const ; //Done
	void swap_nodes(Node*& target, Node*& replacement) ; //Done
	virtual void update_height_up(Node* node) ; //Done
	virtual Node* unhook_leaf(Node* target) ; //Done
	int find_height(Node* root) ; //Done
	/*End of Protected Members of class BST*/

	public :
	//Public Methods for BST
	BST() { root = nullptr ; height = -1 ; size = 0 ; }
	BST(const BST<Comparable>& Obj) : root{nullptr} {
		if (Obj.get_root(1)) this->root = this->clone(Obj) ; 
		this->height = Obj.get_height(1) ; 
		this->size = Obj.get_size(1) ; 
	}
	BST<Comparable>& operator=(const BST<Comparable>& Obj) {
		this->make_empty() ;
		if (Obj.get_root(1)) this->root = this->clone(Obj) ;
		else this->root = nullptr ;
		this->height = Obj.get_height(1) ; 
		this->size = Obj.get_size(1) ;
		return *this ;
	}
	
	/*lvalue accessors and mutators*/
	Node*& get_root() { return root ; }	
	int& get_height() { return height ; }
	int& get_size() { return size ; }
	/*End of lvaue accessors and mutators*/

	/*rvalue accessors*/
	Node* get_root(int a) const { return root ; }
	int get_height(int a) const { return height ; }
	int get_size(int a) const { return size ; }
	/*End of rvalue accessors*/

	void calculate_Tree_height() { height = find_height(root) ; }
	void pre_order() const ; //Done
	void in_order() const ; //Done
	void post_order() const ; 	//Done
	void level_order() const ; //Done  
	void make_empty() ; // Done
	
	/*public friends*/
	template<class Comp>
	friend BST<Comp> MergeWithRoot(BST<Comp> smaller, BST<Comp> larger, const Comp& k) ;	//Done
	template<class Comp>
	friend BST<Comp> Merge(BST<Comp> smaller, BST<Comp> larger) ;
	template<class Comp>
	friend pair<BST<Comp>, BST<Comp>> Split(BST<Comp> tree, const Comp& k) ;
	/*end of public friends*/

	virtual void insert(const Comparable& k) ;	//Done
	virtual void remove(const Comparable& k) ; //Done
	virtual void remove(Node*& root, const Comparable& k) ; //Done
	pair<bool, Comparable> get_max() const { 
		if (!root) return make_pair(false, Comparable()) ; 
		return make_pair(true, find_max(root)->key) ;
	} 
	pair<bool, Comparable> get_min() const {
		if (!root) return make_pair(false, Comparable()) ; 
		return make_pair(true, find_min(root)->key) ; 
	}
	pair<bool, Comparable> previous(const Comparable& k) const ;	//Done
	pair<bool, Comparable> next(const Comparable& k) const ;		//Done
	pair<bool, pair<Comparable, Comparable>> neighbours(const Comparable& k) const ;
	pair<bool, deque<Comparable>> find(const Comparable& a, const Comparable& b) const ;
	bool find(const Comparable& k) const ;
	/*End of Public methods for class BST*/
} ;
/*End of BST Class*/

//Method Definitions
/*Protected Methods*/
template<class Comparable>
typename BST<Comparable>::Node* BST<Comparable>::merge_with_root(typename BST<Comparable>::Node* sroot, typename BST<Comparable>::Node* lroot, const Comparable& k) { 
	/*This method demands that the incoming roots should be the roots of the tree. that is their parents should be null*/
	typename BST<Comparable>::Node* temp = new typename BST<Comparable>::Node() ;
	temp->set(k, 0) ;
	if (sroot) {
		temp->left = sroot ;
		temp->h = max(temp->h, 1 + sroot->h) ;
		sroot->parent = temp ;
	}
	if (lroot) {
		temp->right = lroot ;
		temp->h = max(temp->h, 1 + lroot->h) ;
		lroot->parent = temp ;
	}
	return temp ;
}

template<class Comparable>
typename BST<Comparable>::Node* BST<Comparable>::merge(typename BST<Comparable>::Node* sroot, typename BST<Comparable>::Node* lroot) {
	/*This method demands that the incoming roots should be the roots of the tree. that is their parents should be null*/
	if (!sroot) return lroot ;
	Comparable max_in_left = find_max(sroot)->key ;
	if (!sroot->right) {
		sroot->right = lroot ;
		if (lroot) lroot->parent = sroot ;
		if (sroot->left) sroot->h = max(sroot->h, 1 + sroot->left->h) ;
		if (sroot->right) sroot->h = max(sroot->h, 1 + sroot->right->h) ;
		return sroot ;
	}
	remove(sroot, max_in_left) ;
	return merge_with_root(sroot, lroot, max_in_left) ; 
}		

template<class Comparable>
pair<typename BST<Comparable>::Node*, typename BST<Comparable>::Node*> BST<Comparable>::split(typename BST<Comparable>::Node* root, const Comparable& k) {
	if (!root) return make_pair(nullptr, nullptr) ;
	if (k == root->key) {
		typename BST<Comparable>::Node* small = root->left, *large = root->right ;
		if (small) small->set(small->key, small->h, nullptr, small->left, small->right) ;
		if (large) large->set(large->key, large->h, nullptr, large->left, large->right) ;
		if (root->parent and root == root->parent->left) {
			root->parent->left = nullptr ;
			if (root->parent->right) root->parent->h = 1 + root->parent->right->h ;
			else root->parent->h = 0 ;
		}
		else if (root->parent and root == root->parent->right) {
			root->parent->right = nullptr ;
			if (root->parent->left) root->parent->h = 1 + root->parent->left->h ;
			else root->parent->h = 0 ;
		} 
		root->set(root->key, root->h) ;
		delete root ;
		return make_pair(small, large) ;
	}
	else if (k < root->key) {
		pair<typename BST<Comparable>::Node*, typename BST<Comparable>::Node*> descend = split(root->left, k) ;
		if (root->parent and root == root->parent->left) {
			root->parent->left = nullptr ;
			if (root->parent->right) root->parent->h = 1 + root->parent->right->h ;
			else root->parent->h = 0 ; 	
		} 
		else if (root->parent and root == root->parent->right) {	
			root->parent->right = nullptr ;
			if (root->parent->left) root->parent->h = 1 + root->parent->left->h ;
			else root->parent->h = 0 ;
		} 
		root->parent = nullptr ;
		typename BST<Comparable>::Node* newSecond = merge(descend.second, root) ;
		return make_pair(descend.first, newSecond) ;
	}
	else if (k > root->key) {
		pair<typename BST<Comparable>::Node*, typename BST<Comparable>::Node*> descend = split(root->right, k) ;
		if (root->parent and root == root->parent->left) {
			root->parent->left = nullptr ;
			if (root->parent->right) root->parent->h = 1 + root->parent->right->h ;
			else root->parent->h = 0 ; 	
		} 
		else if (root->parent and root == root->parent->right) {
			root->parent->right = nullptr ;
			if (root->parent->left) root->parent->h = 1 + root->parent->left->h ;
			else root->parent->h = 0 ;	
		} 
		root->parent = nullptr ;
		typename BST<Comparable>::Node* newFirst = merge(root, descend.first) ;
		return make_pair(newFirst, descend.second) ;
	}
}



template<class Comparable>
typename BST<Comparable>::Node* BST<Comparable>::clone(const BST<Comparable>& Obj) {
	queue<Node*> q, Q ;
	Node* newNode = new Node() ;
	const Comparable rk = Obj.get_root(1)->key ;
	const int rh = Obj.get_root(1)->h ;
	newNode->set(rk, rh) ;
	this->root = newNode ;
	Q.push(this->root) ;
	Q.push(nullptr) ;
	q.push(Obj.get_root(1)) ;
	q.push(nullptr) ;
	while (!q.empty()) {
		Node* current = q.front() ;
		Node* Current = Q.front() ;
		Q.pop() ;
		q.pop() ;
		if (!current) {
			q.push(nullptr) ;
			Q.push(nullptr) ;
		}
		else {
			if (current->left) {
				Node* left_child = new Node() ;
				left_child->set(current->left->key, current->left->h, Current) ;
				Current->set(Current->key, Current->h, Current->parent, left_child) ;
				q.push(current->left) ;
				Q.push(left_child) ;	
			} 
			if (current->right) {
				Node* right_child = new Node() ;
				right_child->set(current->right->key, current->right->h, Current) ;
				Current->set(Current->key, Current->h, Current->parent, Current->left, right_child) ;
				q.push(current->right) ;
				Q.push(right_child) ;	
			} 
		}
		if (q.size() == 1 and q.front() == nullptr) {
			q.pop() ;
			Q.pop() ;	
		} 
	}
	return this->root ; 
}

template<class Comparable>
typename BST<Comparable>::Node* BST<Comparable>::find(Node* root, const Comparable& k) const {
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

template<class Comparable>
typename BST<Comparable>::Node* BST<Comparable>::find_max(typename BST<Comparable>::Node* node) const {
	typename BST<Comparable>::Node* itr = node, *current = nullptr ;
	while (itr) {
		current = itr ;
		itr = itr->right ;
	}	
	return current ;
}

template<class Comparable>
typename BST<Comparable>::Node* BST<Comparable>::find_min(typename BST<Comparable>::Node* root) const {
	typename BST<Comparable>::Node* itr = root, *current = nullptr ;
	while (itr) {
		current = itr ;
		itr = itr->left ;
	}	
	return current ;
}

template<class Comparable>
typename BST<Comparable>::Node* BST<Comparable>::inorder_predecessor(typename BST<Comparable>::Node* node) const {
	if (!node->left) {
		typename BST<Comparable>::Node* current = node, *p = node->parent ;
		while (current->key < p->key) {
			current = p ;
			p = current->parent ;
		}
		return p ;
	}
	return find_max(node->left) ;
}

template<class Comparable>
typename BST<Comparable>::Node* BST<Comparable>::inorder_successor(typename BST<Comparable>::Node* node) const {
	Node* top = find_max(node) ;
	if (top->key == root->key) return nullptr ;	
	if (!node->right) {
		typename BST<Comparable>::Node* current = node, *p = node->parent ;
		while (current->key > p->key) {
			current = p ;
			p = current->parent ;
		}
		return p ;	
	}
	return find_min(node->right) ;
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
void BST<Comparable>::swap_nodes(Node*& target, Node*& replacement) {
	swap(target->key, replacement->key) ;
	swap(target, replacement) ;
}

template<class Comparable>
void BST<Comparable>::update_height_up(Node* node) {
	Node* itr = node ; 
	while (itr->parent) {
		itr = itr->parent ;
		int lh = -1, rh = -1 ;
		if (itr->left) lh = itr->left->h ;
		if (itr->right) rh = itr->right->h ;
		itr->h = 1 + max(lh, rh) ; 
	}
	height = itr->h ;	
}

template<class Comparable>
typename BST<Comparable>::Node* BST<Comparable>::unhook_leaf(typename BST<Comparable>::Node* target) {
	typename BST<Comparable>::Node* p = target->parent ;
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
	target->set(target->key, 0, nullptr, nullptr, nullptr) ;
	update_height_up(p) ;
	return target ;
}

template<class Comparable>
int BST<Comparable>::find_height(Node* root) {
	if (!root) return -1 ;
	int left_height = find_height(root->left) ;
	int right_height = find_height(root->right) ;
	root->h =  1 + max(left_height, right_height) ;
	return root->h ;	
}	
/*End of Protected Methods*/

/*Public Methods*/
template<class Comparable>
void BST<Comparable>::pre_order() const { 
	if (!root) return ;
	pre_order(root) ; 
}

template<class Comparable>
void BST<Comparable>::in_order() const { 
	if (!root) return ;
	in_order(root) ; 
}

template<class Comparable>
void BST<Comparable>::post_order() const { 
	if (!root) return ;
	post_order(root) ; 
}

template<class Comparable>
void BST<Comparable>::level_order() const { 
	if (!root) {
		cout<<"Tree is Empty\n" ;
		return ;
	}
	level_order(root) ; 
}

template<class Comparable>
void BST<Comparable>::make_empty() {
	while (root) {
		cout<<"current root = "<<root->key<<"\n" ;
		remove(root->key) ;	
		cout<<"size = "<<size<<"\n" ;
	} 
}

/*Friend 1*/
template<class Comparable>
BST<Comparable> MergeWithRoot(BST<Comparable> smaller, BST<Comparable> larger, const Comparable& k) {
	typename BST<Comparable>::Node* sroot = smaller.get_root(1) ;
	typename BST<Comparable>::Node* lroot = larger.get_root(1) ;
	typename BST<Comparable>::Node* newRoot = BST<Comparable>().merge_with_root(sroot, lroot, k) ;
	BST<Comparable> merged ; 
	merged.get_root() = newRoot ;
	if (newRoot) merged.get_height() = newRoot->h ;
	merged.get_size() = 1 + smaller.get_size(1) + larger.get_size(1) ;
	return merged ;	
} 
/*End of Friend 1*/

/*Friend 2*/
template<class Comparable>
BST<Comparable> Merge(BST<Comparable> smaller, BST<Comparable> larger) {
	BST<Comparable> merged ;
	typename BST<Comparable>::Node* sroot = smaller.get_root(1) ;
	typename BST<Comparable>::Node* lroot = larger.get_root(1) ;
	if (!sroot and !lroot) return merged ;
	
	typename BST<Comparable>::Node* newRoot = BST<Comparable>().merge(sroot, lroot) ;	 
	merged.get_root() = newRoot ;
	if (newRoot) merged.get_height() = newRoot->h ;
	merged.get_size() = smaller.get_size(1) + larger.get_size(1) ;
	return merged ;
}	
/*End of Friend 2*/

/*Friend 3 */
template<class Comparable>
pair<BST<Comparable>, BST<Comparable>> Split(BST<Comparable> target, const Comparable& k) {
	pair<BST<Comparable>, BST<Comparable>> broken ;
	if (!target.get_root(1)) return broken ;
	pair<typename BST<Comparable>::Node*, typename BST<Comparable>::Node*> splitted_up_roots ;
	splitted_up_roots = target.split(target.get_root(1), k) ;
	if (splitted_up_roots.first) {
		broken.first.get_root() = splitted_up_roots.first ;
		broken.first.get_height() = splitted_up_roots.first->h ;
	}
	if (splitted_up_roots.second) {
		broken.second.get_root() = splitted_up_roots.second ;
		broken.second.get_height() = splitted_up_roots.second->h ;
	}
	return broken ;
}
/*Friend 4*/

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
void BST<Comparable>::remove(const Comparable& k) {
	if (!root) return ;
	remove(root, k) ;
} 

template<class Comparable>
void BST<Comparable>::remove(Node*& root, const Comparable& k) {
	Node* target = find(root, k) ;
	if (target->key != k) return ; // key not present

	if ((target == root) and (!target->left and !target->right)) {
		// If there was just one node
		delete target ;
		root = nullptr ;
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

template<class Comparable>
pair<bool, Comparable> BST<Comparable>::previous(const Comparable& k) const {
	if (!root) return make_pair(false, Comparable()) ;	
	Node* of = find(root, k) ; Node* lower_bound = find_min(root) ;
	if (k <= lower_bound->key) return make_pair(true, lower_bound->key) ;
	if (of->key < k) return make_pair(true, of->key) ; 
	Node* prev = inorder_predecessor(of) ;
	return make_pair(true, prev->key) ;
}

template<class Comparable>
pair<bool, Comparable> BST<Comparable>::next(const Comparable& k) const {
	if (!root) return make_pair(false, Comparable()) ;
	Node* of = find(root, k) ; Node* upper_bound = find_max(root) ;
	if (k >= upper_bound->key) return make_pair(true, upper_bound->key) ;
	if (of->key > k) return make_pair(true, of->key) ;
	Node* after = inorder_successor(of) ;
	return make_pair(true, after->key) ;
}

template<class Comparable>
pair<bool, pair<Comparable, Comparable>> BST<Comparable>::neighbours(const Comparable& k) const {
	if (!root) return make_pair(false, make_pair(Comparable(), Comparable())) ;
	Node* lower_bound = find_min(root), *upper_bound = find_max(root) ;
	if (k < lower_bound->key or k > upper_bound->key) return make_pair(false, make_pair(Comparable(), Comparable())) ; 

	Node* candidate = find(root, k), *one_before, *one_after ;
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
	return make_pair(true, make_pair(one_before->key, one_after->key)) ;
}

template<class Comparable>
pair<bool, deque<Comparable>> BST<Comparable>::find(const Comparable& a, const Comparable& b) const {
	// Range find()
	if (!root) make_pair(false, deque<Comparable>()) ;
	Node* lower_bound = find_min(root), *upper_bound = find_max(root) ;
	if (a >= upper_bound->key or b <= lower_bound->key) make_pair(false, deque<Comparable>()) ; 
	
	deque<Comparable> inbetween ;
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
	return make_pair(true, inbetween) ;
}

template<class Comparable>
bool BST<Comparable>::find(const Comparable& k) const {
	Node* candidate = find(root, k) ;
	if (candidate->key == k) return true ;
	return false ;
}
/*End of Public Methods*/


#endif		// end of BST