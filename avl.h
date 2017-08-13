// AVL Header 
// Shivam Sharma KNIT Sultanpur

#ifndef AVL_H_
#define AVL_H_ 

#include <iostream>
#include <cmath>
#include "bst.h"

template<class Comparable>
class AVL : public BST<Comparable> {

	protected :
	virtual void update_height_up(typename BST<Comparable>::Node*& node) ;
	typename BST<Comparable>::Node* unhook_leaf(typename BST<Comparable>::Node* target) ;
	typename BST<Comparable>::Node* left_left(typename BST<Comparable>::Node*& target) ;
	typename BST<Comparable>::Node* left_right(typename BST<Comparable>::Node*& target) ;
	typename BST<Comparable>::Node* right_right(typename BST<Comparable>::Node*& target) ;
	typename BST<Comparable>::Node* right_left(typename BST<Comparable>::Node*& target) ;
	void fix_avl(typename BST<Comparable>::Node*& target) ;

	public :
	AVL() : BST<Comparable>() { }
	virtual void insert(const Comparable& k) ;
	virtual void remove(const Comparable& k) ; 

} ;

template<class Comparable>
typename BST<Comparable>::Node* AVL<Comparable>::unhook_leaf(typename BST<Comparable>::Node* target) {
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
	update_height_up(target) ;
	target->set(target->key) ;
	return target ;
}

template<class Comparable>
typename BST<Comparable>::Node* AVL<Comparable>::left_left(typename BST<Comparable>::Node*& target) {
	typename BST<Comparable>::Node* p = target->parent ;
	typename BST<Comparable>::Node* child = target->left ;
	typename BST<Comparable>::Node* a = target->right ;
	typename BST<Comparable>::Node* b = child->right ;
	typename BST<Comparable>::Node* z = child->left ;

	if (z) z->set(z->key, nullptr, z->left, z->right) ;
	if (b) b->set(b->key, nullptr, b->left, b->right) ;
	if (a) a->set(a->key, nullptr, a->left, a->right) ;

	swap(target->key, child->key) ;
	
	target->set(target->key, p, z, child) ;
	child->set(child->key, target, b, a) ;
	if (z) z->set(z->key, target, z->left, z->right) ;
	if (b) b->set(b->key, child, b->left, b->right) ;
	if (a) a->set(a->key, child, a->left, a->right) ;

	swap(target, child) ;
	return target ; 	
}

template<class Comparable>
typename BST<Comparable>::Node* AVL<Comparable>::right_right(typename BST<Comparable>::Node*& target) {
	typename BST<Comparable>::Node* p = target->parent ;
	typename BST<Comparable>::Node* child = target->right ;
	typename BST<Comparable>::Node* a = target->left ;
	typename BST<Comparable>::Node* b = child->left ;
	typename BST<Comparable>::Node* z = child->right ;

	if (z) z->set(z->key, nullptr, z->left, z->right) ;
	if (b) b->set(b->key, nullptr, b->left, b->right) ;
	if (a) a->set(a->key, nullptr, a->left, a->right) ;

	swap(target->key, child->key) ;

	target->set(target->key, p, child, z) ;
	child->set(child->key, target, a, b) ;
	if (z) z->set(z->key, target, z->left, z->right) ;
	if (b) b->set(b->key, child, b->left, b->right) ;
	if (a) a->set(a->key, child, a->left, a->right) ;

	swap(target, child) ;
	return target ;
}

template<class Comparable>
typename BST<Comparable>::Node* AVL<Comparable>::left_right(typename BST<Comparable>::Node*& target) {
	typename BST<Comparable>::Node* ll_child = right_right(target->left) ;
	target->left = ll_child->parent ;
	return left_left(target) ;
}

template<class Comparable>
typename BST<Comparable>::Node* AVL<Comparable>::right_left(typename BST<Comparable>::Node*& target) {
	typename BST<Comparable>::Node* rr_child = left_left(target->right) ;
	target->right = rr_child->parent ;
	return right_right(target) ;
}

template<class Comparable>
void AVL<Comparable>::fix_avl(typename BST<Comparable>::Node*& target) {
	int lh = -1, rh = -1, ll_h = -1, lr_h = -1, rl_h = -1, rr_h = -1 ;
	if (target->left) lh = target->left->h ;
	if (target->right) rh = target->right->h ;
	if (lh > rh) {
		// first left
		typename BST<Comparable>::Node* l_child = target->left ;
		if (l_child->left) ll_h = l_child->left->h ;
		if (l_child->right) lr_h = l_child->right->h ;

		if (ll_h >= lr_h) target = left_left(target) ;
		else if (lr_h > ll_h) target = left_right(target) ;

	}
	else {
		// first right
		typename BST<Comparable>::Node* r_child = target->right ;
		if (r_child->left) rl_h = r_child->left->h ;
		if (r_child->right) rr_h = r_child->right->h ;
		
		if (rr_h >= rl_h) target = right_right(target) ;		
		else if (rl_h > rr_h) target = right_left(target) ;
	} 
}

template<class Comparable>
void AVL<Comparable>::update_height_up(typename BST<Comparable>::Node*& node) {
	typename BST<Comparable>::Node* target = node ; 
	while (target != BST<Comparable>::root) {
		target = target->parent ;
		int lh = -1, rh = -1 ;
		if (target->left) lh = target->left->h ;
		if (target->right) rh = target->right->h ;
		if (abs(lh - rh) > 1) {
			// AVL Violation
			fix_avl(target) ;
			lh = rh = -1 ;
			if (target->left) lh = target->left->h ;
			if (target->right) rh = target->right->h ;
		} 
		target->h = 1 + max(lh, rh) ; 
	}
	BST<Comparable>::height = BST<Comparable>::root->h ;
} 

template<class Comparable>
void AVL<Comparable>::insert(const Comparable& k) {
	typename BST<Comparable>::Node* newNode = new typename BST<Comparable>::Node(k) ;
	if (!BST<Comparable>::root) BST<Comparable>::root = newNode ;
	else {
		typename BST<Comparable>::Node* candidate = BST<Comparable>::find(BST<Comparable>::root, k) ;
		newNode->parent = candidate ;
		if (k < candidate->key) candidate->left = newNode ;
		else if (k > candidate->key) candidate->right = newNode ;
		update_height_up(newNode) ;	
	}
	BST<Comparable>::size++ ;
}

template<class Comparable>
void AVL<Comparable>::remove(const Comparable& k) {
	typename BST<Comparable>::Node* target = BST<Comparable>::find(BST<Comparable>::root, k) ;
	if (target->key != k) return ; // key not present
	
	if (BST<Comparable>::size == 1) {
		// If there was just one node
		BST<Comparable>::root = nullptr ;
		BST<Comparable>::size-- ;
		delete target ;
		return ;
	}

	if (target->h == 0) target = unhook_leaf(target) ; // target a leaf node
	else {
		// target not a leaf node
		typename BST<Comparable>::Node* predecessor = nullptr, *successor = nullptr ;
		if (target->left) predecessor = BST<Comparable>::inorder_predecessor(target) ;
		if (target->right) successor = BST<Comparable>::inorder_successor(target) ;
		if (predecessor and predecessor->h == 0) {		// predecessor is a leaf
			BST<Comparable>::swap_nodes(target, predecessor) ;
			target = unhook_leaf(target) ;
		}
		else if (successor and successor->h == 0) {		// successor is a leaf
			BST<Comparable>::swap_nodes(target, successor) ;
			target = unhook_leaf(target) ;
		}
		else {
			// Neither predecessor nor successor a leaf
			typename BST<Comparable>::Node* p = nullptr, *child = nullptr ;
			if (predecessor) {
				BST<Comparable>::swap_nodes(target, predecessor) ;
				p = target->parent ;
				child = target->left ;
				child->set(child->key, p, child->left, child->right) ;
				if (p->left and p->left->key == target->key) p->set(p->key, p->parent, child, p->right) ;
				if (p->right and p->right->key == target->key) p->set(p->key, p->parent, p->left, child) ;
			}
			else if (successor) {
				BST<Comparable>::swap_nodes(target, successor) ;
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
	BST<Comparable>::size-- ;
}


#endif			// end of avl