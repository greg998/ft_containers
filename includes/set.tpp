#ifndef SET_TPP
#define SET_TPP

#include <iostream>
#include "Rb_tree.tpp"
#include "iterator.tpp"
#include "utility.tpp"

namespace ft
{
    template <class T,                        // set::key_type/value_type
              class Compare = std::less<T>,   // set::key_compare/value_compare
              class Alloc = std::allocator<T> // set::allocator_type
              >
    class set
    {
    public:
        typedef T key_type;
        typedef T value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;

        class value_compare
        {
        protected:
            Compare comp;

        public:
            value_compare(Compare c)
                : comp(c) {}
            bool operator()(const value_type &lhs, const value_type &rhs) const
            {
                return (comp(lhs, rhs));
            }
        };

    private:
        template<class Val>
		struct GetKey
		{
			const Val &operator()(const Val &val) const
			{
				return (val);
			}
			Val &operator()(Val &val) const
			{
				return (val);
			}
		};
        typedef typename __gnu_cxx::__alloc_traits<Alloc>::template rebind<T>::other Key_alloc_type;
        typedef Rb_tree<key_type, value_type, GetKey<key_type>, key_compare, Key_alloc_type> tree_type;

        tree_type _base_tree;

    public:
        typedef typename tree_type::reference reference;
        typedef typename tree_type::const_reference const_reference;
        typedef typename tree_type::pointer pointer;
        typedef typename tree_type::const_pointer const_pointer;
        typedef typename tree_type::const_iterator iterator;
        typedef typename tree_type::const_iterator const_iterator;
        typedef typename tree_type::const_reverse_iterator reverse_iterator;
        typedef typename tree_type::const_reverse_iterator const_reverse_iterator;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        explicit set(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
            : _base_tree(comp, alloc)
        {
        }

        template <class InputIterator>
        set(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
            : _base_tree(comp, alloc)
        {
            insert(first, last);
        }

        set(const set &x)
            : _base_tree(x._base_tree)
        {
        }

        ~set()
        {
        }
        set &operator=(const set &x)
        {
            _base_tree = x._base_tree;
            return (*this);
        }

        iterator begin()
        {
            return (_base_tree.begin());
        }

        const_iterator begin() const
        {
            return (_base_tree.begin());
        }

        iterator end()
        {
            return (_base_tree.end());
        }

        const_iterator end() const
        {
            return (_base_tree.end());
        }

        reverse_iterator rbegin()
        {
            return (reverse_iterator(end()));
        }

        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(end()));
        }

        reverse_iterator rend()
        {
            return (reverse_iterator(begin()));
        }

        const_reverse_iterator rend() const
        {
            return (const_reverse_iterator(begin()));
        }

        bool empty() const
        {
            return (_base_tree.empty());
        }

        size_type size() const
        {
            return (_base_tree.size());
        }

        size_type max_size() const
        {
            return (_base_tree.max_size());
        }

        pair<iterator, bool> insert(const value_type &val)
        {
            return (_base_tree.insert(val));
        }

        iterator insert(iterator position, const value_type &val)
        {
            return (_base_tree.insert(position, val));
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            _base_tree.insert(first, last);
        }

        void erase(const_iterator position)
        {
            return (_base_tree.erase(position));
        }

        size_type erase(const key_type &k)
        {
            return (_base_tree.erase(k));
        }

        void erase(iterator first, iterator last)
        {
            return (_base_tree.erase(first, last));
        }

        void swap(set &x)
        {
            _base_tree.swap(x._base_tree);
        }

        void clear()
        {
            return (_base_tree.clear());
        }

        key_compare key_comp() const
        {
            return (_base_tree.key_comp());
        }

        value_compare value_comp() const
        {
            return (value_compare(key_comp()));
        }

        iterator find(const key_type &k)
        {
            return (_base_tree.find(k));
        }

        const_iterator find(const key_type &k) const
        {
            return (_base_tree.find(k));
        }

        size_type count(const key_type &k) const
        {
            return (_base_tree.count(k));
        }

        iterator lower_bound(const key_type &k)
        {
            return (_base_tree.lower_bound(k));
        }

        const_iterator lower_bound(const key_type &k) const
        {
            return (_base_tree.lower_bound(k));
        }

        iterator upper_bound(const key_type &k)
        {
            return (_base_tree.upper_bound(k));
        }

        const_iterator upper_bound(const key_type &k) const
        {
            return (_base_tree.upper_bound(k));
        }

        pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            return (_base_tree.equal_range(k));
        }

        pair<iterator, iterator> equal_range(const key_type &k)
        {
            return (_base_tree.equal_range(k));
        }

        allocator_type get_allocator() const
        {
            return (_base_tree.get_allocator());
        }

        friend bool operator==(const set<T, Compare, Alloc> &lhs,
                               const set<T, Compare, Alloc> &rhs)
        {
            return (lhs._base_tree == rhs._base_tree);
        }

        friend bool operator<(const set<T, Compare, Alloc> &lhs,
                              const set<T, Compare, Alloc> &rhs)
        {
            return (lhs._base_tree < rhs._base_tree);
        }

        friend bool operator!=(const set<T, Compare, Alloc> &lhs,
                               const set<T, Compare, Alloc> &rhs)
        {
            return (!(lhs._base_tree == rhs._base_tree));
        }

        friend bool operator<=(const set<T, Compare, Alloc> &lhs,
                               const set<T, Compare, Alloc> &rhs)
        {
            return (!(rhs._base_tree < lhs._base_tree));
        }

        friend bool operator>(const set<T, Compare, Alloc> &lhs,
                              const set<T, Compare, Alloc> &rhs)
        {
            return (rhs._base_tree < lhs._base_tree);
        }

        friend bool operator>=(const set<T, Compare, Alloc> &lhs,
                               const set<T, Compare, Alloc> &rhs)
        {
            return (!(lhs._base_tree < rhs._base_tree));
        }
    };

    template <class T, class Compare, class Alloc>
    void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
    {
        x.swap(y);
    }
}

#endif