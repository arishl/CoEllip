#include <iostream>
#include "../include/MathStructures.h"

int main()
{
    constexpr long long p = 10177;
    using F = int;
    const auto A = std::make_shared<GraphNode<F>>(EllipticCurve<F>{F{5}, F{3}});
    const auto B = std::make_shared<GraphNode<F>>(EllipticCurve<F>{F{5}, F{7}});
    const auto C = std::make_shared<GraphNode<F>>(EllipticCurve<F>{F{9}, F{2}});

    A->neighbors.push_back(B);
    A->neighbors.push_back(C);
    B->neighbors.push_back(A);

    std::cout << *A << "\n";
    return 0;
}
