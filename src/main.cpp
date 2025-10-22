#include <iostream>
#include "../include/MathStructures.h"

int main() {
    constexpr long long p = 10177;
    using F = Fp<p>;
    EllipticCurve<F> E(F(2), F(3));

    if (E.is_singular()) {
        std::cerr << "Curve is singular!\n";
        return 1;
    }

    std::cout << "E: y^2 = x^3 + " << E.a.value << "x + " << E.b.value << " over F_" << p << "\n";
    std::cout << "j-invariant: " << E.j_invariant().value << "\n";

    return 0;
}