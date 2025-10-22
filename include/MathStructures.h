//
// Created by Aris Lemmenes on 10/21/25.
//

#ifndef COELLIP_MATHSTRUCTURES_H
#define COELLIP_MATHSTRUCTURES_H


template <long long P>
struct Fp
{
    long long value;
    constexpr static long long mod = P;

    constexpr explicit Fp(long long v = 0)
        : value((v % P + P) % P)
    {
    }

    constexpr Fp operator+(const Fp& o) const
    {
        return Fp(value + o.value);
    }

    constexpr Fp operator-(const Fp& o) const
    {
        return Fp(value - o.value);
    }

    constexpr Fp operator*(const Fp& o) const
    {
        return Fp(value * o.value);
    }

    constexpr Fp operator-() const
    {
        return Fp(-value);
    }

    constexpr Fp pow(long long e) const
    {
        Fp r(1), b = *this;
        while (e)
        {
            if (e & 1) r = r * b;
            b = b * b;
            e >>= 1;
        }
        return r;
    }

    constexpr Fp inv() const
    {
        return pow(P - 2);
    }

    constexpr Fp operator/(const Fp& o) const
    {
        return *this * o.inv();
    }

    constexpr bool operator==(const Fp& o) const
    {
        return value == o.value;
    }

    constexpr bool operator!=(const Fp& o) const
    {
        return !(*this == o);
    }
    friend std::ostream& operator<<(std::ostream& os, const Fp<P>& a)
    {
        return os << a.value;
    }
};

template <typename F>
struct EllipticCurve
{
    F a, b;

    constexpr EllipticCurve(F a_, F b_) : a(a_), b(b_)
    {
    }

    [[nodiscard]] constexpr bool is_singular() const
    {
        return (F(4) * a.pow(3) + F(27) * b.pow(2)).value == 0;
    }

    constexpr F j_invariant() const
    {
        F a3, b2;
        if constexpr (std::is_class_v<F>)
        {
            a3 = a.pow(3);
            b2 = b.pow(2);
        }
        else
        {
            a3 = static_cast<F>(std::pow(a, 3));
            b2 = static_cast<F>(std::pow(b, 2));
        }
        F num = static_cast<F>(1728) * (static_cast<F>(4) * a3);
        F denom = (static_cast<F>(4) * a3) + (static_cast<F>(27) * b2);
        return num / denom;
    }
    friend std::ostream& operator<<(std::ostream& os, const EllipticCurve<F>& e)
    {
        return os << "y^2 = x^3 + " << e.a << "x + " << e.b;
    }
};


template <typename F>
struct GraphNode
{
    EllipticCurve<F> curve;
    F j;
    std::vector<std::shared_ptr<GraphNode>> neighbors;

    explicit GraphNode(EllipticCurve<F> c) : curve(c), j(c.j_invariant())
    {
    }
};

template <typename Field>
std::ostream& operator<<(std::ostream& os, const GraphNode<Field>& node)
{
    os << "GraphNode(" << node.curve << ")";

    if (!node.neighbors.empty())
    {
        os << "\n  Neighbors:";
        for (const auto& neighbor_ptr : node.neighbors)
        {
            if (neighbor_ptr)
            {
                os << "\n    -> " << neighbor_ptr->curve;
            }
            else
            {
                os << "\n    -> (null)";
            }
        }
    }
    else
    {
        os << "\n  (no neighbors)";
    }

    return os;
}

#endif //COELLIP_MATHSTRUCTURES_H
