#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H

#include <initializer_list>
#include <string>
#include "NodeTraits.h"

enum class Order {
    Preorder, Inorder, Postorder
};

template<typename Node, bool isBinaryTreeNode>
class BinaryTreeClass;
template<typename Node>
using BinaryTree = BinaryTreeClass<Node, NodeTraits<Node>::isBinaryTreeNode>;
template<template<class> class Node, typename T>
class BinaryTreeClass<Node<T>, true>
{
public:
    BinaryTreeClass();
    BinaryTreeClass(std::initializer_list<T> _values);
    BinaryTreeClass(const BinaryTreeClass& _bt);                // Copy constructor
    BinaryTreeClass(BinaryTreeClass&& _bt) noexcept;            // Move constructor
    virtual ~BinaryTreeClass();                                 // Destructor
    BinaryTreeClass& operator=(const BinaryTreeClass& _bt);     // Copy assignment operator
    BinaryTreeClass& operator=(BinaryTreeClass&& _bt) noexcept; // Move assignment operator
    //    BinaryTreeClass& operator=(BinaryTreeClass);                // Move+Copy constructor with Copy-and-Swap idiom
    virtual void     Add(const T _value);
    virtual bool     Delete(const T _value);
    void             Clear();
    T                Max() const;
    T                Min() const;
    size_t           Size() const;
    size_t           Depth() const;
    std::string      BreadthFirstTraversal() const;
    std::string      DepthFirstTraversal() const;
    std::string      DepthFirstTraversal(const Order& _order) const;

protected:
    Node<T>        * Copy(Node<T> *_head);
    template<bool isStoringDepth>
    void             Add(Node<T> **_head,
                         const T   _value);
    bool             Delete(Node<T> **_head,
                            const T   _value);
    void             Clear(Node<T> *_head);
    size_t           Size(const Node<T> *_head) const;
    template<bool isStoringDepth>
    size_t           Depth(const Node<T> *_head) const;
    void             DepthFirstTraversal(const Node<T> *_node,
                                         const Order  & _order,
                                         std::string  & _output) const;

protected:
    Node<T> *mRoot;
};

#endif // BINARYTREE_BINARYTREE_H
