#ifndef MAP_TPP
#define MAP_TPP
#include "utility.tpp"
#include "Rb_tree_iterator.tpp"
#include "iterator.tpp"
#include "type_traits.tpp"
#include "algorithm.tpp"
#include "Rb_tree.tpp"
#include <iostream>

namespace ft
{	
	template <class Key,									   // map::key_type
			  class T,										   // map::mapped_type
			  class Compare = std::less<Key>,				   // map::key_compare
			  class Alloc = std::allocator<pair<const Key, T> > // map::allocator_type
			  >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
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
				return (comp(lhs.first, rhs.first));
			}
		};

	private:
		template<class Val>
		struct GetKey
		{
			const typename Val::first_type &operator()(const Val &val) const
			{
				return (val.first);
			}
			// typename Val::first_type &operator()(Val &val) const
			// {
			// 	return (val.first);
			// }
		};
		typedef typename __gnu_cxx::__alloc_traits<Alloc>::template rebind<value_type>::other Pair_alloc_type;
		typedef Rb_tree<key_type, value_type, GetKey<value_type>, key_compare, Pair_alloc_type> tree_type;

		tree_type _base_tree;

	public:
		typedef typename tree_type::reference reference;
		typedef typename tree_type::const_reference const_reference;
		typedef typename tree_type::pointer pointer;
		typedef typename tree_type::const_pointer const_pointer;
		// iterator
		typedef typename tree_type::iterator iterator;
		typedef typename tree_type::const_iterator const_iterator;
		typedef typename tree_type::reverse_iterator reverse_iterator;
		typedef typename tree_type::const_reverse_iterator const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type())
			: _base_tree(comp, alloc)
		{
		}
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _base_tree(comp, alloc)
		{
			insert(first, last);
		}
		map(const map &x)
			: _base_tree(x._base_tree)
		{
		}

		~map()
		{
		}
		map &operator=(const map &x)
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
		mapped_type &operator[](const key_type &k)
		{
			iterator it = lower_bound(k);
			if (it == end() || key_comp()(k, it->first))
				it = insert(it, value_type(k, mapped_type()));
			return (it->second);
		}
		pair<iterator, bool> insert(const value_type &val)
		{
			return _base_tree.insert(val);
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
		void erase(iterator position)
		{
			return (_base_tree.erase(position));
		}
		size_type erase(const key_type &k)
		{
			return (_base_tree.erase(k));
		}
		void erase(iterator first, iterator last)
		{
			return (_base_tree.erase(first,last));
		}
		void swap(map &x)
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

  		friend bool operator== ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
		{
			return (lhs._base_tree == rhs._base_tree);
		}
  		friend bool operator< ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
		{
			return (lhs._base_tree < rhs._base_tree);
		}

  		friend bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(lhs._base_tree == rhs._base_tree));
		}

  		friend bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(rhs._base_tree < lhs._base_tree));
		}

  		friend bool operator> ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
		{
			return (rhs._base_tree < lhs._base_tree);
		}

  		friend bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(lhs._base_tree < rhs._base_tree));
		}

		void    tree_draw() const
		{
			_base_tree.tree_draw();
		}
	};
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}
#endif