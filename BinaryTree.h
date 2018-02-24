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
template<typename Node>
class BinaryTreeClass<Node, true>
{
public:
    BinaryTreeClass();
    BinaryTreeClass(std::initializer_list<int> _values);
    BinaryTreeClass(const BinaryTreeClass& _bt);                // Copy constructor
    BinaryTreeClass(BinaryTreeClass&& _bt) noexcept;            // Move constructor
    virtual ~BinaryTreeClass();                                 // Destructor
    BinaryTreeClass& operator=(const BinaryTreeClass& _bt);     // Copy assignment operator
    BinaryTreeClass& operator=(BinaryTreeClass&& _bt) noexcept; // Move assignment operator
    //    BinaryTreeClass& operator=(BinaryTreeClass);                // Move+Copy constructor with Copy-and-Swap idiom
    virtual void     Add(const int _value);
    virtual bool     Delete(const int _value);
    void             Clear();
    int              Max() const;
    int              Min() const;
    size_t           Size() const;
    size_t           Depth() const;
    std::string      BreadthFirstTraversal() const;
    std::string      DepthFirstTraversal() const;
    std::string      DepthFirstTraversal(const Order& _order) const;

protected:
    Node           * Copy(Node *_head);
    template<bool isStoringDepth>
    void             Add(Node    **_head,
                         const int _value);
    bool             Delete(Node    **_head,
                            const int _value);
    void             Clear(Node *_head);
    size_t           Size(const Node *_head) const;
    template<bool isStoringDepth>
    size_t           Depth(const Node *_head) const;
    void             DepthFirstTraversal(const Node  *_node,
                                         const Order& _order,
                                         std::string& _output) const;

protected:
    Node *mRoot;
};

#endif // BINARYTREE_BINARYTREE_H
