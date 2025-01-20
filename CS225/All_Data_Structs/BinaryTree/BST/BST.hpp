#ifndef __BINARYTREE_BST_BST_HPP
#define __BINARYTREE_BST_BST_HPP
#include <memory>
#include "./../BinaryTreeUtils.hpp"


template <typename T>
class BST {
public:

using Node = typename BTNode::Node<T>;

BST() = default;

BST(const BST& other)   {root_ = utils.copy_tree(other.root_);} // still a move assign of root
BST& operator=(const BST& other)   {
    if (this != &other) {
        root_ = utils.copy_tree(other.root_);
    }
    return *this;
}


BST(BST&& other) noexcept : root_(std::move(other.root_))   {}
BST& operator=(BST&& other) {
    if (this != &other) {
        root_ = std::move(other.root_);
    }
    return *this;
}


void insert(const T& input) {root_ = insertHelper(input, root_);} // return type Node to update the parent, must assign to root_ in case root itself is updated
void clear() {root_.reset();}
bool remove(const T& input)    {bool isRemoved = false; root_ = removeHelper(input, root_, isRemoved); return isRemoved;}
bool empty() const  {return root_ == nullptr;};
bool contains(const T& element) const {return containsHelper(element, root_);}

void inorderTraversal(std::function<void(const T&)> func)   {utils.inorderTraversal(root_, func);}

size_t size() const {return utils.size(root_);}
int height() const  {return utils.height(root_);}

private:
std::unique_ptr<Node> root_;
BinaryTreeUtils<T> utils;
std::unique_ptr<Node> extractMin(std::unique_ptr<Node>& root);
std::unique_ptr<Node> insertHelper(const T& input, std::unique_ptr<Node>& root);
std::unique_ptr<Node> removeHelper(const T& input, std::unique_ptr<Node>& root, bool& success);
bool containsHelper(const T& elem, const std::unique_ptr<Node>& root) const;
};


// NOTE: For aliasing in class to work for member funcs outside of class, the alias needs to be scoped IN FUNCTION DECLARATION
// not necessary inside funcs, where the scope of the class is implicit.
template <typename T>
std::unique_ptr<typename BST<T>::Node> BST<T>::insertHelper(const T& input, std::unique_ptr<Node>& root)    {
    if (!root) {
        return std::make_unique<BTNode::Node<T>>(input);
    }   else if (input > root->data)
    {
        root->right = insertHelper(input, root->right);
    }   else if (input < root->data)
    {
        root->left = insertHelper(input, root->left);
    }
    return std::move(root); // in case not inserted yet, return by original unaltered node
    // this function returns by value, the moved root will be auto used for move construction of that copy
    // move to self doesn't alter anything
}


template <typename T>
std::unique_ptr<typename BST<T>::Node> BST<T>::extractMin(std::unique_ptr<Node>& root)   {
    if (!root) return std::move(root);
    auto current = &root; // ptr to unique_ptr!
    while ((*current)->left)    {
        current = &((*current)->left);
    }
    return std::move(*current);
}


template <typename T>
std::unique_ptr<typename BST<T>::Node> BST<T>::removeHelper(const T& input, std::unique_ptr<Node>& root, bool& success) {
    if (!root) return std::move(root);
    if (input > root->data)    {
        root->right = removeHelper(input, root->right, success); // update parent
    }   else if (input < root->data)
    {
        root->left = removeHelper(input, root->left, success);
    }   else    { // Found!
        if (!root->left && !root->right)    { // Case 1: No children
            success = true;
            return std::move(root->left);
        }   else if (!root->right)    { // Case 2: One child: child substitute
            success = true;
            return std::move(root->left);
        }   else if (!root->left)   {
            success = true;
            return std::move(root->right);
        }   else    { // Case 3: Two children
            // In this case, either the largest node in left subtree (in-order predeccessor)
            // or the smallest node in right subtree may substitute (in-order successor)
            auto minNode = extractMin(root);
            minNode->left = std::move(root->left);
            minNode->right = removeHelper(minNode->data, root->right, success);
            // In-prder prede/successor falls in previous two cases.
            return minNode; // compiler will elide copy here, explicitly using move could interfere
            // simply return by val for local objs (NOT for passed/captured!), compiler will move it
        }
    }
    return std::move(root); // for keeping the parent unaltered in stacked recursive calls when not found
}


template <typename T>
bool BST<T>::containsHelper(const T& elem, const std::unique_ptr<Node>& root) const    {
    if (root == nullptr)    return false; // Serves both as initial null check and Final Not Found case
    if (elem == root->data) {
        return true;
    }   else if (elem > root->data)
    {
        return containsHelper(elem, root->right);
    }   else// better to use else than else if in last case
    //so that the compiler knows it covers all cases and doesn't issue a warning
    {
        return containsHelper(elem, root->left);
    }
}

#endif // __BINARYTREE_BST_BST_HPP