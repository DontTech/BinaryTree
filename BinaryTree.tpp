#ifndef BINARYTREE_BINARYTREE_TPP
#define BINARYTREE_BINARYTREE_TPP

#include "BinaryTree.h"
#include <queue>
#include <stack>
#include <stdexcept>

template <template <class> class Node, typename T, bool isStoringDepth>
struct BinaryTreeClassHelper {
    static void Add(Node<T>** _head, T _value)
    {
        if (*_head == nullptr) {
            auto* node = new Node<T>();
            node->left = nullptr;
            node->right = nullptr;
            node->value = _value;
            *_head = node;
        } else {
            if ((*_head)->value < _value) {
                BinaryTreeClassHelper<Node, T, isStoringDepth>::Add(&((*_head)->right), _value);
            } else {
                BinaryTreeClassHelper<Node, T, isStoringDepth>::Add(&((*_head)->left), _value);
            }
        }
    }

    static size_t Depth(const Node<T>* _head)
    {
        if (_head == nullptr) {
            return 0;
        } else {
            return 1 + std::max<size_t>(BinaryTreeClassHelper<Node, T, isStoringDepth>::Depth(_head->left), BinaryTreeClassHelper<Node, T, isStoringDepth>::Depth(_head->right));
        }
    }
};

template <template <class> class Node, typename T>
struct BinaryTreeClassHelper<Node, T, true> {
    static void Add(Node<T>** _head, T _value)
    {
        if (*_head == nullptr) {
            auto* node = new Node<T>();
            node->left = nullptr;
            node->right = nullptr;
            node->value = _value;
            node->depth = 1;
            *_head = node;
        } else {
            if ((*_head)->value < _value) {
                BinaryTreeClassHelper<Node, T, true>::Add(&((*_head)->right), _value);
                (*_head)->depth = (*_head)->right->depth + 1;
            } else {
                BinaryTreeClassHelper<Node, T, true>::Add(&((*_head)->left), _value);
                (*_head)->depth = (*_head)->left->depth + 1;
            }
        }
    }

    static size_t Depth(const Node<T>* _head)
    {
        if (_head == nullptr) {
            return 0;
        } else {
            return _head->depth;
        }
    }
};
template <template <class> class Node, typename T>
BinaryTreeClass<Node<T>, true>::BinaryTreeClass()
    : mRoot(
        nullptr)
{
}
template <template <class> class Node, typename T>
BinaryTreeClass<Node<T>, true>::BinaryTreeClass(
    const std::initializer_list<T> _values)
    : mRoot(nullptr)
{
    for (auto value : _values) {
        Add<NodeTraits<Node<T>>::isStoringDepth>(&mRoot, value);
    }
}
template <template <class> class Node, typename T>
BinaryTreeClass<Node<T>, true>::BinaryTreeClass(
    const BinaryTreeClass& _bt)
    : BinaryTreeClass()
{
    mRoot = Copy(_bt.mRoot);
}
template <template <class> class Node, typename T>
BinaryTreeClass<Node<T>, true>::BinaryTreeClass(
    BinaryTreeClass&& _bt) noexcept
{
    using std::swap;
    swap(mRoot, _bt.mRoot);
}
template <template <class> class Node, typename T>
BinaryTreeClass<Node<T>, true>::~BinaryTreeClass()
{
    Clear();
}
template <template <class> class Node, typename T>
BinaryTreeClass<Node<T>, true>& BinaryTreeClass<Node<T>,
    true>::operator=(const BinaryTreeClass& _bt)
{
    if (this != &_bt) {
        Clear();
        mRoot = Copy(_bt.mRoot);
    }

    return *this;
}
template <template <class> class Node, typename T>
BinaryTreeClass<Node<T>, true>& BinaryTreeClass<Node<T>,
    true>::operator=(BinaryTreeClass&& _bt) noexcept
{
    if (this != &_bt) {
        Clear();
        using std::swap;
        swap(mRoot, _bt.mRoot);
    }

    return *this;
}
template <template <class> class Node, typename T>
void BinaryTreeClass<Node<T>, true>::Add(const T _value)
{
    Add<NodeTraits<Node<T>>::isStoringDepth>(&mRoot, _value);
}
template <template <class> class Node, typename T>
bool BinaryTreeClass<Node<T>, true>::Delete(const T _value)
{
    return Delete(&mRoot, _value);
}
template <template <class> class Node, typename T>
void BinaryTreeClass<Node<T>, true>::Clear()
{
    // Faster than calling Delete() repeatedly as we don't care about the structural consistency while clearing
    Clear(mRoot);
    mRoot = nullptr;
}
template <template <class> class Node, typename T>
T BinaryTreeClass<Node<T>, true>::Max() const
{
    if (mRoot == nullptr) {
        throw std::logic_error("No element to calculate max.");
    } else {
        Node<T>* node = mRoot;
        while (node->right != nullptr) {
            node = node->right;
        }

        return node->value;
    }
}
template <template <class> class Node, typename T>
T BinaryTreeClass<Node<T>, true>::Min() const
{
    if (mRoot == nullptr) {
        throw std::logic_error("No element to calculate min.");
    } else {
        Node<T>* node = mRoot;
        while (node->left != nullptr) {
            node = node->left;
        }

        return node->value;
    }
}
template <template <class> class Node, typename T>
size_t BinaryTreeClass<Node<T>, true>::Size() const
{
    return Size(mRoot);
}
template <template <class> class Node, typename T>
size_t BinaryTreeClass<Node<T>, true>::Depth() const
{
    return Depth<NodeTraits<Node<T>>::isStoringDepth>(mRoot);
}
template <template <class> class Node, typename T>
std::string BinaryTreeClass<Node<T>,
    true>::BreadthFirstTraversal() const
{
    std::string output = "BFS:";
    if (nullptr == mRoot) {
        return output;
    }

    std::queue<Node<T>*> q;
    q.push(mRoot);
    while (!q.empty()) {
        Node<T>* node = q.front();
        q.pop();
        if (nullptr != node->left) {
            q.push(node->left);
        }
        if (nullptr != node->right) {
            q.push(node->right);
        }

        output += " " + std::to_string(node->value);
    }

    return output;
}
template <template <class> class Node, typename T>
std::string BinaryTreeClass<Node<T>,
    true>::DepthFirstTraversal() const
{
    std::string output = "DFS (preorder):";
    if (nullptr == mRoot) {
        return output;
    }

    std::stack<Node<T>*> s;
    s.push(mRoot);
    while (!s.empty()) {
        Node<T>* node = s.top();
        s.pop();
        if (nullptr != node->right) {
            s.push(node->right);
        }
        if (nullptr != node->left) {
            s.push(node->left);
        }

        output += " " + std::to_string(node->value);
    }

    return output;
}
template <template <class> class Node, typename T>
std::string BinaryTreeClass<Node<T>,
    true>::DepthFirstTraversal(const Order& _order) const
{
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
template <template <class> class Node, typename T>
Node<T>* BinaryTreeClass<Node<T>, true>::Copy(
    Node<T>* _head)
{
    if (_head == nullptr) {
        return nullptr;
    }

    auto* node = new Node<T>();
    node->left = Copy(_head->left);
    node->right = Copy(_head->right);
    node->value = _head->value;
    return node;
}
template <template <class> class Node, typename T>
template <bool isStoringDepth>
void BinaryTreeClass<Node<T>,
    true>::Add(Node<T>** _head, const T _value)
{
    BinaryTreeClassHelper<Node, T, isStoringDepth>::Add(_head, _value);
}
template <template <class> class Node, typename T>
bool BinaryTreeClass<Node<T>, true>::Delete(Node<T>** _head,
    const T _value)
{
    if (*_head == nullptr) {
        return false;
    }
    if ((*_head)->value == _value) {
        Node<T>* delNode = *_head;
        Node<T>* parentNode;
        if (Depth<NodeTraits<Node<T>>::isStoringDepth>((*_head)->left) < Depth<NodeTraits<Node<
                T>>::isStoringDepth>((*_head)->right)) {
            // Replace with next largest number (leftmost node on right side)
            parentNode = (*_head)->right;
            if (parentNode == nullptr) {
                // Nothing on the right
                *_head = delNode->left;
            } else {
                // There is something on the right
                if (parentNode->left == nullptr) {
                    // parentNode is the leftmost
                    parentNode->left = delNode->left;
                    *_head = parentNode;
                } else {
                    // We need to find the leftmost node
                    Node<T>* childNode = parentNode->left;
                    while (childNode->left != nullptr) {
                        parentNode = childNode;
                        childNode = parentNode->left;
                    }

                    parentNode->left = childNode->right;
                    childNode->left = delNode->left;
                    childNode->right = delNode->right;
                    *_head = childNode;
                }
            }
        } else {
            // Replace with next smallest number (rightmost node on left side)
            parentNode = (*_head)->left;
            if (parentNode == nullptr) {
                // Nothing on the left
                *_head = delNode->right;
            } else {
                // There is something on the left
                if (parentNode->right == nullptr) {
                    // parentNode is the rightmost
                    parentNode->right = delNode->right;
                    *_head = parentNode;
                } else {
                    // We need to find the rightmost node
                    Node<T>* childNode = parentNode->right;
                    while (childNode->right != nullptr) {
                        parentNode = childNode;
                        childNode = parentNode->right;
                    }

                    parentNode->right = childNode->left;
                    childNode->left = delNode->left;
                    childNode->right = delNode->right;
                    *_head = childNode;
                }
            }
        }

        delete delNode;
        return true;
    } else if ((*_head)->value < _value) {
        return Delete(&((*_head)->right), _value);
    } else {
        return Delete(&((*_head)->left), _value);
    }
}
template <template <class> class Node, typename T>
void BinaryTreeClass<Node<T>, true>::Clear(Node<T>* _head)
{
    if (_head == nullptr) {
        return;
    }

    Clear(_head->left);
    Clear(_head->right);
    delete _head;
}
template <template <class> class Node, typename T>
size_t BinaryTreeClass<Node<T>, true>::Size(
    const Node<T>* _head) const
{
    if (_head == nullptr) {
        return 0;
    } else {
        return 1 + Size(_head->left) + Size(_head->right);
    }
}
template <template <class> class Node, typename T>
template <bool isStoringDepth>
size_t BinaryTreeClass<Node<T>,
    true>::Depth(const Node<T>* _head) const
{
    BinaryTreeClassHelper<Node, T, isStoringDepth>::Depth(_head);
}
template <template <class> class Node, typename T>
void BinaryTreeClass<Node<T>, true>::DepthFirstTraversal(
    const Node<T>* _node,
    const Order& _order,
    std::string& _output) const
{
    if (nullptr == _node) {
        return;
    }

    std::string leftStr, rightStr;
    DepthFirstTraversal(_node->left, _order, leftStr);
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
