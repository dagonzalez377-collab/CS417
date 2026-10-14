#ifndef TREE_H
#define TREE_H

#include <iostream>

// Template binary search tree
template <typename type>
class Tree {
private:
    struct Node {
        type data;
        Node* left;
        Node* right;
        Node(const type& d) : data(d), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // ---- helpers ----
    Node* copyNodes(Node* n) {
        if (n == nullptr) return nullptr;
        Node* c = new Node(n->data);
        c->left = copyNodes(n->left);
        c->right = copyNodes(n->right);
        return c;
    }

    void destroy(Node* n) {
        if (n == nullptr) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

    Node* insertNode(Node* n, const type& key) {
        if (n == nullptr) return new Node(key);
        if (key < n->data)
            n->left = insertNode(n->left, key);
        else if (n->data < key)
            n->right = insertNode(n->right, key);
        // equal keys are ignored (no duplicates)
        return n;
    }

    Node* deleteNode(Node* n, const type& key) {
        if (n == nullptr) return nullptr;
        if (key < n->data) {
            n->left = deleteNode(n->left, key);
        } else if (n->data < key) {
            n->right = deleteNode(n->right, key);
        } else {
            // found node to delete
            if (n->left == nullptr) {
                Node* r = n->right;
                delete n;
                return r;
            }
            if (n->right == nullptr) {
                Node* l = n->left;
                delete n;
                return l;
            }
            // two children: replace with inorder successor
            Node* succ = n->right;
            while (succ->left != nullptr) succ = succ->left;
            n->data = succ->data;
            n->right = deleteNode(n->right, succ->data);
        }
        return n;
    }

    void inorderPrint(Node* n) {
        if (n == nullptr) return;
        inorderPrint(n->left);
        std::cout << n->data << std::endl;
        inorderPrint(n->right);
    }

    void preorderPrint(Node* n) {
        if (n == nullptr) return;
        std::cout << n->data << std::endl;
        preorderPrint(n->left);
        preorderPrint(n->right);
    }

    void postorderPrint(Node* n) {
        if (n == nullptr) return;
        postorderPrint(n->left);
        postorderPrint(n->right);
        std::cout << n->data << std::endl;
    }

public:
    // Default constructor: empty tree
    Tree() : root(nullptr) {}

    // Constructor: tree with one node
    Tree(const type key) : root(new Node(key)) {}

    // Copy constructor: copy of another tree
    Tree(const Tree<type>& other) : root(copyNodes(other.root)) {}

    // Assignment operator and destructor
    Tree<type>& operator=(const Tree<type>& other) {
        if (this != &other) {
            destroy(root);
            root = copyNodes(other.root);
        }
        return *this;
    }

    ~Tree() { destroy(root); }

    // find key in the tree; returns a default-constructed type if not found
    type find(type key) {
        Node* n = root;
        while (n != nullptr) {
            if (key < n->data)
                n = n->left;
            else if (n->data < key)
                n = n->right;
            else
                return n->data;
        }
        return type();
    }

    // insert a new node, preserving the sorted property
    void insert(type key) {
        root = insertNode(root, key);
    }

    // delete an existing node, preserving the sorted property
    // ("delete" is a reserved word in C++, so the method is named remove)
    void remove(type key) {
        root = deleteNode(root, key);
    }

    void inorder() { inorderPrint(root); }
    void postorder() { postorderPrint(root); }
    void preorder() { preorderPrint(root); }
};

#endif
