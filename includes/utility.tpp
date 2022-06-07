#ifndef UTILITY_TPP
#define UTILITY_TPP

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
};

template <class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y)
{
    return (pair<T1, T2>(x, y));
}

#endif