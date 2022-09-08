#include <algorithm>
#include <cstdio>
#include <iostream>
#include <sstream>

#define pow2(n) (1 << (n))
#define endl "\n"

using namespace std;

struct avl // node declaration
{
	int d;
	struct avl *l;
	struct avl *r;
} * r;

class avl_tree {
public: // declaring  functions
	int height(avl *);
	int difference(avl *);
	avl *right_right_rotation(avl *);
	avl *left_left_rotation(avl *);
	avl *left_right_rotation(avl *);
	avl *right_left_rotation(avl *);
	avl *balance(avl *);
	avl *insert(avl *, int);
	void showtree(avl *, int);
	void inorder(avl *);
	void preorder(avl *);
	void postorder(avl *);
	avl_tree() { r = NULL; }
};


int avl_tree::height(avl *t) {
	int h = 0;
	if (t != NULL) {
		int l_height = height(t->l);
		int r_height = height(t->r);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}
int avl_tree::difference(
	avl *t) // calculte difference between left and right tree
{
	int l_height = height(t->l);
	int r_height = height(t->r);
	int b_factor = l_height - r_height;
	return b_factor;
}
avl *avl_tree::right_right_rotation(avl *parent) // right right rotation
{
	avl *t;
	t = parent->r;
	parent->r = t->l;
	t->l = parent;
	cout << "Right-Right Rotation";
	return t;
}
avl *avl_tree::left_left_rotation(avl *parent) // left left rotation
{
	avl *t;
	t = parent->l;
	parent->l = t->r;
	t->r = parent;
	cout << "Left-Left Rotation";
	return t;
}
avl *avl_tree::left_right_rotation(avl *parent) // left right rotation
{
	avl *t;
	t = parent->l;
	parent->l = right_right_rotation(t);
	cout << "Left-Right Rotation";
	return left_left_rotation(parent);
}
avl *avl_tree::right_left_rotation(avl *parent) // right left rotation
{
	avl *t;
	t = parent->r;
	parent->r = left_left_rotation(t);
	cout << "Right-Left Rotation";
	return right_right_rotation(parent);
}
avl *avl_tree::balance(avl *t) {
	int bal_factor = difference(t);
	if (bal_factor > 1) {
		if (difference(t->l) > 0)
			t = left_left_rotation(t);
		else
			t = left_right_rotation(t);
	} else if (bal_factor < -1) {
		if (difference(t->r) > 0)
			t = right_left_rotation(t);
		else
			t = right_right_rotation(t);
	}
	return t;
}
avl *avl_tree::insert(avl *r, int v) {
	if (r == NULL) {
		r = new avl;
		r->d = v;
		r->l = NULL;
		r->r = NULL;
		return r;
	} else if (v < r->d) {
		r->l = insert(r->l, v);
		r = balance(r);
	} else if (v >= r->d) {
		r->r = insert(r->r, v);
		r = balance(r);
	}
	return r;
}
void avl_tree::showtree(avl *p, int l) // showtree the tree
{
	int i;
	if (p != NULL) {
		showtree(p->r, l + 1);
		cout << " ";
		if (p == r) cout << "Root -> ";
		for (i = 0; i < l && p != r; i++)
			cout << " ";
		cout << p->d;
		showtree(p->l, l + 1);
	}
}
void avl_tree::inorder(avl *t) // inorder traversal
{
	if (t == NULL) return;
	inorder(t->l);
	cout << t->d << " ";
	inorder(t->r);
}
void avl_tree::preorder(avl *t) // preorder traversal
{
	if (t == NULL) return;
	cout << t->d << " ";
	preorder(t->l);
	preorder(t->r);
}
void avl_tree::postorder(avl *t) // postorder traversal
{
	if (t == NULL) return;
	postorder(t->l);
	postorder(t->r);
	cout << t->d << " ";
}
int main() {
	int c, i;
	avl_tree avl;
	while (true) {
		cout << "1.Insert Element into the tree" << endl;
		cout << "2.Show  Balanced AVL Tree" << endl;
		cout << "3.InOrder traversal" << endl;
		cout << "4.PreOrder traversal" << endl;
		cout << "5.PostOrder traversal" << endl;
		cout << "6.Exit" << endl;
		cout << "Enter your Choice: ";
		cin >> c;

		if (c == 1) {
			cout << "Enter value to be inserted: ";
			cin >> i;
			r = avl.insert(r, i);
			continue;
		} else if (c == 2) {
			if (r == NULL) {
				cout << "Tree is Empty" << endl;
				continue;
			}
			cout << "Balanced AVL Tree:" << endl;
			avl.showtree(r, 1);
			cout << endl;
			continue;
		} else if (c == 3) {
			cout << "Inorder Traversal:" << endl;
			avl.inorder(r);
			cout << endl;
			continue;
		} else if (c == 4) {
			cout << "Preorder Traversal:" << endl;
			avl.preorder(r);
			cout << endl;
			continue;
		} else if (c == 5) {
			cout << "Postorder Traversal:" << endl;
			avl.postorder(r);
			cout << endl;
			continue;
		} else if (c == 6) {
			return 0;
		} else {
			cout << "Wrong Choice" << endl;
		}
	}

	return 0;
}
