#pragma once
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;
template <typename T, typename R = T>

class Arbolito {
	struct Node {
		T e;
		Node* left;
		Node* right;
		int h;

		Node(T e) : e(e), left(nullptr), right(nullptr), h(0) {}

		static int height(Node* n) {
			return n == nullptr ? -1 : n->h;
		}
		void updateH() {
			h = max(Node::height(left), Node::height(right)) + 1;
		}
	};

	Node* root;
	int length;
	function<R(T)> key;

	void destroy(Node* n) {
		if (n != nullptr) {
			destroy(n->left);
			destroy(n->right);
			delete n;
		}
	}

	void rotAB(Node*& n) {
		Node* aux = n->left;
		n->left = aux->right;
		n->updateH();
		aux->right = n;
		n = aux;
		n->updateH();
	}

	void rotBA(Node*& n) {
		Node* aux = n->right;
		n->right = aux->left;
		n->updateH();
		aux->left = n;
		n = aux;
		n->updateH();
	}

	void balance(Node*& n) {
		int delta = Node::height(n->left) - Node::height(n->right);
		if (delta < -1) {
			if (Node::height(n->right->left) > Node::height(n->right->right)) {
				rotAB(n->right);
			}
			rotBA(n);
		}
		else if (delta > 1) {
			if (Node::height(n->left->right) > Node::height(n->left->left)) {
				rotBA(n->left);
			}
			rotAB(n);
		}
	}

	void add(Node*& n, T e) {
		if (n == nullptr) {
			n = new Node(e);
			return;
		}
		else if (key(e) < key(n->e)) {
			add(n->left, e);
		}
		else {
			add(n->right, e);
		}
		balance(n);
		n->updateH();
	}
	public:
		Arbolito(function <R(T)> key = [](T a) {return a; }) : root(nullptr), length(0), key(key) {}
		~Arbolito() { destroy(root); }
		int Height() {
			return Node::height(root);
		}
		int size() {
			return length;
		}
		void Add(T e) {
			add(root, e);
			length++;
		}
};