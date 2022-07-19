#ifndef UTILITY_TPP
#define UTILITY_TPP
namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        T1 first;
        T2 second;
        pair() : first(), second()
        {
        }

        template <class U, class V>
        pair(const pair<U, V> &pr)
            : first(pr.first), second(pr.second)
        {
        }

        pair(const T1 &a, const T2 &b)
            : first(a), second(b)
        {
        }

        friend bool
        operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return (lhs.first == rhs.first && lhs.second == rhs.second);
        }

        friend bool
        operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return (lhs.first < rhs.first || lhs.second < rhs.second);
        }

        friend bool
        operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return (!(lhs == rhs));
        }

        friend bool
        operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return (rhs < lhs);
        }

        friend bool
        operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return (!(rhs < lhs));
        }

        friend bool
        operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return (!(lhs < rhs));
        }
    };

    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return (pair<T1, T2>(x, y));
    }
}

#endif