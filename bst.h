//Written by Shivam Sharma. KNIT Sultanpur

/*

A header for Binary Search Tree implementation in C++ 
Implemented using a Template with typename Comparable.
Initial rollout supports -

1. Tree Creation
2. Insertion
3. Deletion
4. Min Max Query
5. Pre-Order Traversal

*/

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <cmath>

using namespace std ;

template <typename Comparable>
class BinarySearchTree {
	struct tree_node {
		Comparable key ;
		tree_node* left_subtree ;
		tree_node* right_subtree ;

		tree_node(const Comparable& d = Comparable{ }, tree_node* left = nullptr, tree_node* right = nullptr) : key(d), left_subtree(left), right_subtree(right) { }
		tree_node(Comparable&& d, tree_node* left = nullptr, tree_node* right = nullptr) : key(move(d)), left_subtree(left), right_subtree(right) { }
	} ;
	tree_node* root ;
	bool search(tree_node* root, const Comparable& d)
	{
		if (!root) return false ;
		else if (d < root->key) return search(root->left_subtree,d) ;
		else if (d > root->key) return search(root->right_subtree,d) ;
		else return true ;
	}
	tree_node* insert(tree_node* root, const Comparable& d)
	{
		if (!root) {
			tree_node* temp = new tree_node(d) ;
			return temp ;
		}
		else if (d < root->key) root->left_subtree = insert(root->left_subtree,d) ;
		else if (d > root->key) root->right_subtree = insert(root->right_subtree,d) ;
		return root ;
	}
	void print_tree(tree_node* root)
	{
		if (!root) return ;
		cout<<root->key<<"  " ;
		print_tree(root->left_subtree) ;
		print_tree(root->right_subtree) ;
	}
	Comparable& find_max(tree_node* root)
	{
		if (!root->right_subtree) return root->key ;
		else return find_max(root->right_subtree) ;
	}
	Comparable& find_min(tree_node* root)
	{
		if (!root->left_subtree) return root->key ;
		else return find_min(root->left_subtree) ;
	}
	tree_node* inorder_predeccesor(tree_node* root)
	{
		if (!root->left_subtree and !root->right_subtree) return root ;
		return inorder_predeccesor(root->right_subtree) ;
	}
	tree_node* remove(tree_node* root, Comparable d)
	{
		if (root->key == d) {
			if (!root->left_subtree and !root->right_subtree) return nullptr ;
			if (!root->left_subtree and root->right_subtree) {
				tree_node* ret_val = root->right_subtree ;
				root->right_subtree = nullptr ;
				return ret_val ;
			}
			if (root->left_subtree and !root->right_subtree) {
				tree_node* ret_val = root->left_subtree ;
				root->left_subtree = nullptr ;
				return ret_val ;
			}
			tree_node* inorder_pre = inorder_predeccesor(root->left_subtree) ;
			root = remove(root,inorder_pre->key) ;
			inorder_pre->left_subtree = root->left_subtree ;
			inorder_pre->right_subtree = root->right_subtree ;
			root->left_subtree = root->right_subtree = nullptr ;
			return inorder_pre ;
		}
		else if (d < root->key) root->left_subtree = remove(root->left_subtree,d) ;
		else if (d > root->key) root->right_subtree = remove(root->right_subtree,d) ;
	}

	public :
	BinarySearchTree() { root = nullptr ; cout<<"Tree created\n" ; }
	//BinarySearchTree(const BinarySearchTree& rhs) ;
	//BinarySearchTree(BinarySearchTree&& rhs) ;
	//~BinarySearchTree() ;

	bool contains(const Comparable& d) { return search(root,d) ; }
	void insert(const Comparable& d) { root = insert(root,d) ; cout<<"Value inserted\n" ; }
	void print_tree() { print_tree(root) ; }
	Comparable& find_max() { return find_max(root) ; }
	Comparable& find_min() { return find_min(root) ; }
	void remove(Comparable& d) { root = remove(root,d) ; }

} ;

#endif  // BST_H_
