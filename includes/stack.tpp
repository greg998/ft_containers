#ifndef STACK_TPP
#define STACK_TPP
#include "vector.tpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
    protected:
        Container c;

    public:
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;
        typedef T value_type;
        typedef Container container_type;
        typedef size_t size_type;

        explicit stack(const container_type &ctnr = container_type())
            : c(ctnr)
        {
        }

        stack(const stack &other)
            : c(other.c)
        {
        }

        stack &operator=(const stack &rhs)
        {
            if (this != &rhs)
            {
                c = rhs.c;
            }
            return (*this);
        }

        ~stack() {}

        bool empty() const
        {
            return (c.empty());
        }

        size_type size() const
        {
            return (c.size());
        }

        reference top()
        {
            return (c.back());
        }

        const_reference top() const
        {
            return (c.back());
        }

        void push(const value_type &val)
        {
            c.push_back(val);
        }

        void pop()
        {
            c.pop_back();
        }

        inline friend bool
        operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
        {
            return (lhs.c == rhs.c);
        }
        inline friend bool
        operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
        {
            return (lhs.c < rhs.c);
        }
    };

    template <typename T, typename Container>
    inline bool
    operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (!(lhs == rhs));
    }

    template <typename T, typename Container>
    inline bool
    operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (!(rhs < lhs));
    }

    template <typename T, typename Container>
    inline bool
    operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (rhs < lhs);
    }

    template <typename T, typename Container>
    inline bool
    operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (!(lhs < rhs));
    }
}

#endif