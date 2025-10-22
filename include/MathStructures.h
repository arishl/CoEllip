//
// Created by Aris Lemmenes on 10/21/25.
//

#ifndef COELLIP_MATHSTRUCTURES_H
#define COELLIP_MATHSTRUCTURES_H


template <long long P>
struct Fp {
    long long value;
    constexpr static long long mod = P;
    constexpr explicit Fp(long long v = 0) : value((v % P + P) % P) {}
    constexpr Fp operator+(const Fp &o) const { return Fp(value + o.value); }
    constexpr Fp operator-(const Fp &o) const { return Fp(value - o.value); }
    constexpr Fp operator*(const Fp &o) const { return Fp(value * o.value); }
    constexpr Fp operator-() const { return Fp(-value); }
    constexpr Fp pow(long long e) const {
        Fp r(1), b = *this;
        while (e) { if (e & 1) r = r * b; b = b * b; e >>= 1; }
        return r;
    }
    constexpr Fp inv() const { return pow(P - 2); }
    constexpr Fp operator/(const Fp &o) const { return *this * o.inv(); }
    constexpr bool operator==(const Fp &o) const { return value == o.value; }
    constexpr bool operator!=(const Fp &o) const { return !(*this == o); }
};

template <typename F>
struct EllipticCurve {
    F a, b;
    constexpr EllipticCurve(F a_, F b_) : a(a_), b(b_) {}
    [[nodiscard]] constexpr bool is_singular() const {
        return (F(4) * a.pow(3) + F(27) * b.pow(2)).value == 0;
    }
    constexpr F j_invariant() const {
        F num = F(1728) * (F(4) * a.pow(3));
        F denom = (F(4) * a.pow(3)) + (F(27) * b.pow(2));
        return num / denom;
    }
};

template <typename F>
struct GraphNode {
    EllipticCurve<F> curve;
    F j;
    std::vector<std::shared_ptr<GraphNode>> neighbors;
    explicit GraphNode(EllipticCurve<F> c) : curve(c), j(c.j_invariant()) {}
};

#endif //COELLIP_MATHSTRUCTURES_H