#ifndef BINARYTREE_BINARYTREE_TPP
#define BINARYTREE_BINARYTREE_TPP

#include <queue>
#include <stack>
#include <stdexcept>
#include "BinaryTree.h"

template < typename Node, bool isStoringDepth > struct BinaryTreeClassHelper
{
    static void Add(Node **_head, int _value)
    {
        if (*_head == nullptr)
        {
            auto *node = new Node();
            node->left  = nullptr;
            node->right = nullptr;
            node->value = _value;
            *_head = node;
        }
        else
        {
            if ((*_head)->value < _value)
            {
                BinaryTreeClassHelper < Node, isStoringDepth > ::Add(&((*_head)->right), _value);
            }
            else
            {
                BinaryTreeClassHelper < Node, isStoringDepth > ::Add(&((*_head)->left), _value);
            }
        }
    }

    static size_t Depth(const Node *_head)
    {
        if (_head == nullptr)
        {
            return 0;
        }
        else
        {
            return 1 + std::max < size_t >
                   (BinaryTreeClassHelper < Node, isStoringDepth > ::Depth(_head->left), BinaryTreeClassHelper < Node,
                    isStoringDepth > ::Depth(_head->right));
        }
    }
};

template < typename Node > struct BinaryTreeClassHelper < Node, true >
{
    static void Add(Node **_head, int _value)
    {
        if (*_head == nullptr)
        {
            auto *node = new Node();
            node->left  = nullptr;
            node->right = nullptr;
            node->value = _value;
            node->depth = 1;
            *_head      = node;
        }
        else
        {
            if ((*_head)->value < _value)
            {
                BinaryTreeClassHelper < Node, true > ::Add(&((*_head)->right), _value);
                (*_head)->depth = (*_head)->right->depth + 1;
            }
            else
            {
                BinaryTreeClassHelper < Node, true > ::Add(&((*_head)->left), _value);
                (*_head)->depth = (*_head)->left->depth + 1;
            }
        }
    }

    static size_t Depth(const Node *_head)
    {
        if (_head == nullptr)
        {
            return 0;
        }
        else
        {
            return _head->depth;
        }
    }
};
template < typename Node > BinaryTreeClass < Node, true > ::BinaryTreeClass() : mRoot(nullptr) {}
template < typename Node > BinaryTreeClass < Node,
true > ::BinaryTreeClass(const std::initializer_list < int > _values) : mRoot(nullptr) {
    for (auto value : _values)
    {
        Add < NodeTraits < Node > ::isStoringDepth > (&mRoot, value);
    }
}
template < typename Node > BinaryTreeClass < Node, true > ::BinaryTreeClass(const BinaryTreeClass &_bt) : BinaryTreeClass() {
    mRoot = Copy(_bt.mRoot);
}
template < typename Node > BinaryTreeClass < Node, true > ::BinaryTreeClass(BinaryTreeClass && _bt) noexcept {
    using std::swap;
    swap(mRoot, _bt.mRoot);
}
template < typename Node > BinaryTreeClass < Node, true > ::~BinaryTreeClass() {
    Clear();
}
template < typename Node > BinaryTreeClass < Node, true > &BinaryTreeClass < Node,
true > ::operator = (const BinaryTreeClass &_bt) {
    if (this != &_bt)
    {
        Clear();
        mRoot = Copy(_bt.mRoot);
    }

    return *this;
}
template < typename Node > BinaryTreeClass < Node, true > &BinaryTreeClass < Node,
true > ::operator = (BinaryTreeClass && _bt)noexcept {
    if (this != &_bt)
    {
        Clear();
        using std::swap;
        swap(mRoot, _bt.mRoot);
    }

    return *this;
}
template < typename Node > void BinaryTreeClass < Node, true > ::Add(const int _value) {
    Add < NodeTraits < Node > ::isStoringDepth > (&mRoot, _value);
}
template < typename Node > bool BinaryTreeClass < Node, true > ::Delete(const int _value) {
    return Delete(&mRoot, _value);
}
template < typename Node > void BinaryTreeClass < Node, true > ::Clear() {
    // Faster than calling Delete() repeatedly as we don't care about the structural consistency while clearing
    Clear(mRoot);
    mRoot = nullptr;
}
template < typename Node > int BinaryTreeClass < Node, true > ::Max() const {
    if (mRoot == nullptr)
    {
        throw std::logic_error("No element to calculate max.");
    }
    else
    {
        Node *node = mRoot;
        while (node->right != nullptr)
        {
            node = node->right;
        }

        return node->value;
    }
}
template < typename Node > int BinaryTreeClass < Node, true > ::Min() const {
    if (mRoot == nullptr)
    {
        throw std::logic_error("No element to calculate min.");
    }
    else
    {
        Node *node = mRoot;
        while (node->left != nullptr)
        {
            node = node->left;
        }

        return node->value;
    }
}
template < typename Node > size_t BinaryTreeClass < Node, true > ::Size() const {
    return Size(mRoot);
}
template < typename Node > size_t BinaryTreeClass < Node, true > ::Depth() const {
    return Depth < NodeTraits < Node > ::isStoringDepth > (mRoot);
}
template < typename Node > std::string BinaryTreeClass < Node, true > ::BreadthFirstTraversal() const {
    std::string output = "BFS:";
    if (nullptr == mRoot)
    {
        return output;
    }

    std::queue < Node * > q;
    q.push(mRoot);
    while (!q.empty())
    {
        Node *node = q.front();
        q.pop();
        if (nullptr != node->left)
        {
            q.push(node->left);
        }
        if (nullptr != node->right)
        {
            q.push(node->right);
        }

        output += " " + std::to_string(node->value);
    }

    return output;
}
template < typename Node > std::string BinaryTreeClass < Node, true > ::DepthFirstTraversal() const {
    std::string output = "DFS (preorder):";
    if (nullptr == mRoot)
    {
        return output;
    }

    std::stack < Node * > s;
    s.push(mRoot);
    while (!s.empty())
    {
        Node *node = s.top();
        s.pop();
        if (nullptr != node->right)
        {
            s.push(node->right);
        }
        if (nullptr != node->left)
        {
            s.push(node->left);
        }

        output += " " + std::to_string(node->value);
    }

    return output;
}
template < typename Node > std::string BinaryTreeClass < Node, true > ::DepthFirstTraversal(const Order &_order) const {
    std::string output = "DFS ";

    switch (_order) {
    case Order::Inorder:
        output += "(inorder):";
        break;

    case Order::Postorder:
        output += "(postorder):";
        break;

    case Order::Preorder:
        output += "(preorder):";
        break;
    }

    DepthFirstTraversal(mRoot, _order, output);
    return output;
}
template < typename Node > Node * BinaryTreeClass < Node, true > ::Copy(Node * _head) {
    if (_head == nullptr)
    {
        return nullptr;
    }

    auto *node = new Node();
    node->left  = Copy(_head->left);
    node->right = Copy(_head->right);
    node->value = _head->value;
    return node;
}
template < typename Node > template < bool isStoringDepth > void BinaryTreeClass < Node, true > ::Add(Node * *_head,
                                                                                                      const int _value) {
    BinaryTreeClassHelper < Node, isStoringDepth > ::Add(_head, _value);
}
template < typename Node > bool BinaryTreeClass < Node, true > ::Delete(Node * *_head, const int _value) {
    if (*_head == nullptr)
    {
        return false;
    }
    if ((*_head)->value == _value)
    {
        Node *delNode = *_head;
        Node *parentNode;
        if (Depth < NodeTraits < Node > ::isStoringDepth > ((*_head)->left) < Depth < NodeTraits < Node > ::isStoringDepth >
            ((*_head)->right))
        {
            // Replace with next largest number (leftmost node on right side)
            parentNode = (*_head)->right;
            if (parentNode == nullptr)
            {
                // Nothing on the right
                *_head = delNode->left;
            }
            else
            {
                // There is something on the right
                if (parentNode->left == nullptr)
                {
                    // parentNode is the leftmost
                    parentNode->left = delNode->left;
                    *_head           = parentNode;
                }
                else
                {
                    // We need to find the leftmost node
                    Node *childNode = parentNode->left;
                    while (childNode->left != nullptr)
                    {
                        parentNode = childNode;
                        childNode  = parentNode->left;
                    }

                    parentNode->left = childNode->right;
                    childNode->left  = delNode->left;
                    childNode->right = delNode->right;
                    *_head           = childNode;
                }
            }
        }
        else
        {
            // Replace with next smallest number (rightmost node on left side)
            parentNode = (*_head)->left;
            if (parentNode == nullptr)
            {
                // Nothing on the left
                *_head = delNode->right;
            }
            else
            {
                // There is something on the left
                if (parentNode->right == nullptr)
                {
                    // parentNode is the rightmost
                    parentNode->right = delNode->right;
                    *_head            = parentNode;
                }
                else
                {
                    // We need to find the rightmost node
                    Node *childNode = parentNode->right;
                    while (childNode->right != nullptr)
                    {
                        parentNode = childNode;
                        childNode  = parentNode->right;
                    }

                    parentNode->right = childNode->left;
                    childNode->left   = delNode->left;
                    childNode->right  = delNode->right;
                    *_head            = childNode;
                }
            }
        }

        delete delNode;
        return true;
    }
    else if ((*_head)->value < _value)
    {
        return Delete(&((*_head)->right), _value);
    }
    else
    {
        return Delete(&((*_head)->left), _value);
    }
}
template < typename Node > void BinaryTreeClass < Node, true > ::Clear(Node * _head) {
    if (_head == nullptr)
    {
        return;
    }

    Clear(_head->left);
    Clear(_head->right);
    delete _head;
}
template < typename Node > size_t BinaryTreeClass < Node, true > ::Size(const Node * _head) const {
    if (_head == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + Size(_head->left) + Size(_head->right);
    }
}
template < typename Node > template < bool isStoringDepth > size_t BinaryTreeClass < Node,
true > ::Depth(const Node * _head) const {
    BinaryTreeClassHelper < Node, isStoringDepth > ::Depth(_head);
}
template < typename Node > void BinaryTreeClass < Node, true > ::DepthFirstTraversal(const Node * _node,
                                                                                     const Order &_order,
                                                                                     std::string& _output) const {
    if (nullptr == _node)
    {
        return;
    }

    std::string leftStr, rightStr;
    DepthFirstTraversal(_node->left,  _order, leftStr);
    DepthFirstTraversal(_node->right, _order, rightStr);

    switch (_order) {
    case Order::Inorder:
        _output += leftStr + " " + std::to_string(_node->value) + rightStr;
        break;

    case Order::Postorder:
        _output += leftStr + rightStr + " " + std::to_string(_node->value);
        break;

    case Order::Preorder:
        _output += " " + std::to_string(_node->value) + leftStr + rightStr;
        break;
    }
}

#endif // BINARYTREE_BINARYTREE_TPP
