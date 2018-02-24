#include <iostream>
#include <random>
#include <chrono>
#include <stdexcept>
#include "BinaryTree.tpp"
#include "Node.h"

#ifdef _WIN32
# define _CRTDBG_MAP_ALLOC
# include <stdlib.h>
# include <crtdbg.h>
#endif // ifdef _WIN32
int main()
{
#ifdef _WIN32

    // For checking memory leaks. Run in 'Debug' mode inside Visual Studio
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif // ifdef _WIN32
    BinaryTree<SimpleBTNode<int> > bt = { 10, 5, 15, 3, 7 };
    std::cout << "Size = " << bt.Size() << std::endl;
    std::cout << "Depth = " << bt.Depth() << std::endl;
    std::cout << "Max, Min = " << bt.Max() << ", " << bt.Min() << std::endl;
    std::cout << bt.BreadthFirstTraversal() << std::endl;
    std::cout << bt.DepthFirstTraversal() << std::endl;
    std::cout << bt.DepthFirstTraversal(Order::Preorder) << std::endl;
    std::cout << bt.DepthFirstTraversal(Order::Inorder) << std::endl;
    std::cout << bt.DepthFirstTraversal(Order::Postorder) << std::endl;
    BinaryTree<BTNodeWithDepth<int> > btd = { 10, 5, 15, 3, 7 };
    std::cout << "Size = " << btd.Size() << std::endl;
    std::cout << "Depth = " << btd.Depth() << std::endl;
    std::cout << "Max, Min = " << btd.Max() << ", " << btd.Min() << std::endl;
    std::cout << btd.BreadthFirstTraversal() << std::endl;
    std::cout << btd.DepthFirstTraversal() << std::endl;
    std::cout << btd.DepthFirstTraversal(Order::Preorder) << std::endl;
    std::cout << btd.DepthFirstTraversal(Order::Inorder) << std::endl;
    std::cout << btd.DepthFirstTraversal(Order::Postorder) << std::endl;

    // Recreate with random numbers
    bt = BinaryTree<SimpleBTNode<int> >();
    std::cout << "Now recreating with random numbers" << std::endl;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 random_engine(static_cast<unsigned long>(seed));
    const size_t MAX_DELETE = 3;
    const int    MAX_NUMBER = 20;
    int numbersToDelete[MAX_DELETE];
    size_t idx = 0;
    for (size_t i = 0; i < 10; ++i)
    {
        int number = static_cast<int>(random_engine()) % MAX_NUMBER;
        bt.Add(number);
        if ((idx < MAX_DELETE) && (random_engine() % 1 == 0))
        {
            numbersToDelete[idx] = number;
            ++idx;
        }
    }

    std::cout << bt.DepthFirstTraversal(Order::Preorder) << std::endl;
    std::cout << bt.DepthFirstTraversal(Order::Postorder) << std::endl;
    std::cout << "Size = " << bt.Size() << std::endl;
    std::cout << "Depth = " << bt.Depth() << std::endl;
    std::cout << "Max, Min = " << bt.Max() << ", " << bt.Min() << std::endl;
    std::cout << "Deleting " << idx << " randomly selected numbers: " << std::endl;
    for (size_t i = 0; i < idx; ++i)
    {
        bool deleted = bt.Delete(numbersToDelete[i]);
        std::cout << "Deleting " << numbersToDelete[i] << ": " << (deleted ? "deleted" : "not found") << std::endl;
        if (!deleted)
        {
            throw std::logic_error("How is this even possible?");
        }

        std::cout << bt.DepthFirstTraversal(Order::Preorder) << std::endl;
        std::cout << bt.DepthFirstTraversal(Order::Inorder) << std::endl;
        std::cout << bt.DepthFirstTraversal(Order::Postorder) << std::endl;
        std::cout << "Size = " << bt.Size() << std::endl;
        std::cout << "Depth = " << bt.Depth() << std::endl;
    }
    for (size_t i = 0; i < idx; ++i)
    {
        int number = static_cast<int>(random_engine()) % MAX_NUMBER;
        std::cout << "Deleting a randomly generated number " << number << ": " <<
        (bt.Delete(number) ? "deleted" : "not found") << std::endl;
    }

    std::cout << bt.DepthFirstTraversal(Order::Preorder) << std::endl;
    std::cout << bt.DepthFirstTraversal(Order::Inorder) << std::endl;
    std::cout << bt.DepthFirstTraversal(Order::Postorder) << std::endl;
    std::cout << "Size = " << bt.Size() << std::endl;
    std::cout << "Depth = " << bt.Depth() << std::endl;
    std::cout << "Max, Min = " << bt.Max() << ", " << bt.Min() << std::endl;
    return 0;
}
