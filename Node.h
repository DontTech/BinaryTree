#pragma once

template <typename T>
struct SimpleBTNode {
    SimpleBTNode* left;
    SimpleBTNode* right;
    T value;
};

template <typename T>
struct NodeTraits<SimpleBTNode<T>> {
    static const bool isBinaryTreeNode = true;
    static const bool isStoringDepth = false;
    static const bool isPointingToParent = false;
};

template <typename T>
struct BTNodeWithDepth {
    BTNodeWithDepth* left;
    BTNodeWithDepth* right;
    T value;
    size_t depth;
};

template <typename T>
struct NodeTraits<BTNodeWithDepth<T>> {
    static const bool isBinaryTreeNode = true;
    static const bool isStoringDepth = true;
    static const bool isPointingToParent = false;
};

template <typename T>
struct BTNodeTwoWay {
    BTNodeTwoWay* left;
    BTNodeTwoWay* right;
    T value;
    BTNodeTwoWay* parent;
};

template <typename T>
struct NodeTraits<BTNodeTwoWay<T>> {
    static const bool isBinaryTreeNode = true;
    static const bool isStoringDepth = false;
    static const bool isPointingToParent = true;
};
