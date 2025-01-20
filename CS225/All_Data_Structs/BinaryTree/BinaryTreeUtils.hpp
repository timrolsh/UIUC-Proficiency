#ifndef BINARYTREEUTILS_HPP
#define BINARYTREEUTILS_HPP
#include <functional>
#include <algorithm>
#include <memory>
#include "./../Stack/Stack.hpp"
#include "./../Queue/Queue.hpp"

namespace BTNode   {
    template <typename T>
    struct Node {
        T data;
        std::unique_ptr<Node<T>> left;
        std::unique_ptr<Node<T>> right;
        Node(const T& input) : data(input), left(nullptr), right(nullptr)  {}
    };
}


template <typename T>
class BinaryTreeUtils   {
public:

using Node = typename BTNode::Node<T>; // always add typename if using fails


std::unique_ptr<Node> copy_tree(const std::unique_ptr<Node>& other_root);

size_t size(const std::unique_ptr<Node>& root) const;
int height(const std::unique_ptr<Node>& root) const;

void inorderTraversal(const std::unique_ptr<Node>& root, std::function<void(const T&)> func);
void preorderTraversal(const std::unique_ptr<Node>& root, std::function<void(const T&)> func);
void postorderTraversal(const std::unique_ptr<Node>& root, std::function<void(const T&)> func);
void BFSTraversal(const std::unique_ptr<Node>& root, std::function<void(const T&)> func);
};


template <typename T>
std::unique_ptr<typename BinaryTreeUtils<T>::Node> BinaryTreeUtils<T>::copy_tree(const std::unique_ptr<Node>& other_root)    {
    if (!other_root)  return nullptr;
    auto current = std::make_unique<Node>(other_root->data);
    current->left = copy_tree(other_root->left);  // T
    current->right = copy_tree(other_root->right);// |
    return current; //         <---------------------|  
}


template <typename T>
void BinaryTreeUtils<T>::inorderTraversal(const std::unique_ptr<Node>& root, std::function<void(const T&)> func)   {
    if (!root) return;
    Stack<Node*> stack;
    auto current = root.get();
    while (!stack.empty() || current)  {
        while (current)    {
            stack.push(current);
            current = current->left.get();
        }
        current = stack.top();
        stack.pop();
        func(current->data);
        current = current->right.get();
    }
}

template <typename T>
void BinaryTreeUtils<T>::postorderTraversal(const std::unique_ptr<Node>& root, std::function<void(const T&)> func)   {
    if (!root) return;
    Stack<Node*> stack;
    auto current = root.get();
    while (!stack.empty() || current)   {
        while (current)  {
            stack.push(current);
            current = current->right.get();
        }
        current = stack.top();
        stack.pop();
        func(current->data);
        current = current->left.get();
    }
}

template <typename T>
void BinaryTreeUtils<T>::preorderTraversal (const std::unique_ptr<Node>& root, std::function<void(const T&)> func)  {
    if (!root) return;
    Stack<Node*> stack;
    auto current = root.get();
    stack.push(current);
    while (!stack.empty())   {
        current = stack.pop();
        func(current->data);
        if (current->right) stack.push(current->right.get());
        if (current->left) stack.push(current->left.get());
    }
}

template <typename T>
void BinaryTreeUtils<T>::BFSTraversal(const std::unique_ptr<Node>& root, std::function<void(const T&)> func)  {
    if (!root) return;
    Queue<Node*> queue;
    auto current = root.get();
    queue.push(current);
    while (!queue.empty())   {
        current = queue.front();
        queue.pop();
        func(current->data);
        if (current->left.get()) queue.push(current->left.get()); // Don't forget the null check before pushing!
        if (current->right.get()) queue.push(current->right.get());
    }
}


template <typename T>
size_t BinaryTreeUtils<T>::size(const std::unique_ptr<Node>& root) const {
    if (!root) return 0;
    return 1 + size(root->left) + size(root->right);
}

template <typename T>
int BinaryTreeUtils<T>::height(const std::unique_ptr<Node>& root) const {
    if (!root)  return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

#endif