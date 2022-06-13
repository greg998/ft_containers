#ifndef MAP_TPP
#define MAP_TPP
#include "utility.tpp"
#include "Rb_tree_iterator.tpp"
#include <iostream>

namespace ft
{

	template <class Key, class T, class Val, typename Compare, class Alloc>
	class Rb_tree
	{
	public:
		typedef Key key_type;
		typedef Val value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Alloc allocator_type;
		typedef Rb_tree_iterator<pointer, value_type> iterator;
		typedef Rb_tree_iterator<const_pointer, value_type> const_iterator;

	private:
		typedef typename __gnu_cxx::__alloc_traits<Alloc>::template rebind<Node<Val> >::other Node_allocator;
		typedef __gnu_cxx::__alloc_traits<Node_allocator> Alloc_traits;

		// inherit Rb_node for use _impl address for iterator end
		struct Header
		{
			Rb_node header;
			size_t node_count;
			Header()
			{
				header.color = RED;
				header.parent = 0;
				header.left = &header;
				header.right = &header;
				node_count = 0;
			}
		};

		struct map_impl : public Node_allocator, Header
		{
			Compare comp;
			map_impl() : Node_allocator(), Rb_node()
			{
			}
			map_impl(const Compare &comp,
					 const allocator_type &a) : Node_allocator(a), Header(), comp(comp)
			{
			}
			map_impl(const map_impl &src) : Node_allocator(src), Header(), comp(src.comp)
			{
			}
		};
		map_impl _impl;
		typedef Node<Val> *link_type;
		typedef const Node<Val> *const_link_type;

		Rb_node *&root()
		{
			return (_impl.header.parent);
		}
		const Rb_node *root() const
		{
			return (_impl.parent);
		}
		Rb_node *&_begin()
		{
			return (_impl.header.left);
		}
		const Rb_node *_begin() const
		{
			return (_impl.left);
		}
		Rb_node *_end()
		{
			return (_impl.right);
		}
		const Rb_node *end() const
		{
			return (_impl.right);
		}

		static link_type left(Rb_node *n)
		{
			return (static_cast<link_type>(n->left));
		}
		static const_link_type left(const Rb_node *n)
		{
			return (static_cast<const_link_type>(n->left));
		}
		static link_type right(Rb_node *n)
		{
			return (static_cast<link_type>(n->right));
		}
		static const_link_type right(const Rb_node *n)
		{
			return (static_cast<const_link_type>(n->right));
		}
		static const_reference value(const Rb_node *n)
		{
			return (static_cast<const_link_type>(n)->data);
		}

	public:
		Rb_tree(void)
			: _impl()
		{
		}
		Rb_tree(const Compare &comp,
				const allocator_type &a = allocator_type())
			: _impl(comp, Node_allocator(a)) {}
		Rb_tree(const Rb_tree &src)
			: _impl(src._impl)
		{
		}

		iterator begin()
		{
			return (iterator(_impl.left));
		}

		iterator end()
		{
			return (iterator(&_impl.header));
		}

		iterator find(const key_type &k)
		{
			Rb_node *tmp = root();
			while (tmp)
			{
				if (_impl.comp(k, value(tmp).first))
				{
					tmp = tmp->left;
				}
				else if (_impl.comp(value(tmp).first, k))
				{
					tmp = tmp->right;
				}
				else
				{
					// iterator it (tmp);
					// std::cout << "tmp " << it->first;
					return (iterator(tmp));
				}
			}
			return (end());
		}
		const_iterator find(const key_type &k) const
		{
			Rb_node *tmp = root();
			while (tmp)
			{
				if (_impl.comp(k, value(tmp).first))
				{
					tmp = tmp->left;
				}
				else if (_impl.comp(value(tmp).first, k))
				{
					tmp = tmp->right;
				}
				else
					return (const_iterator(tmp));
			}
			return (end());
		}

		pair<iterator, bool> insert(const value_type &val)
		{
			iterator it = find(val.first);

			if (it != end())
				return (ft::make_pair(it, false));
			link_type newNode = get_Node_allocator().allocate(1);
			// Node<Val> a(val);
			get_Node_allocator().construct(newNode, val);
			Rb_node *tmp(root());

			if (!tmp)
			{
				root() = newNode;
				_begin() = newNode;
			}
			else
			{
				while (1)
				{
					if (_impl.comp(val.first, value(tmp).first))
					{
						if (tmp->left)
							tmp = tmp->left;
						else
						{
							//if (value(_begin))
							tmp->left = newNode;
							break;
						}
					}
					else
					{
						if (tmp->right)
							tmp = tmp->right;
						else
						{
							tmp->right = newNode;
							break;
						}
					}
				}
			}
			_impl.node_count++;
			// std::cout << value(_impl.tmp).first;
			return (ft::make_pair(iterator(newNode), true));
		}

		Node_allocator &
		get_Node_allocator()
		{
			return this->_impl;
		}

		const Node_allocator &
		get_Node_allocator() const
		{
			return this->_impl;
		}
		allocator_type get_allocator() const
		{
			return (allocator_type(get_Node_allocator()));
		}
	};
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
		typedef typename Alloc::reference reference;
		typedef typename Alloc::const_reference const_reference;
		typedef typename Alloc::pointer pointer;
		typedef typename Alloc::const_pointer const_pointer;
		// iterator
		typedef Rb_tree_iterator<pointer, value_type> iterator;
		typedef Rb_tree_iterator<const_pointer, value_type> const_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		class value_compare
		{
		protected:
			Compare comp;
			value_compare(Compare c)
				: comp(c) {}

		public:
			bool operator()(const value_type &lhs, const value_type &rhs) const
			{
				return (comp(lhs.first, rhs.first));
			}
		};

	private:
		typedef typename __gnu_cxx::__alloc_traits<Alloc>::template rebind<value_type>::other Pair_alloc_type;
		typedef Rb_tree<key_type, mapped_type, value_type, key_compare, Pair_alloc_type> tree_type;

		tree_type _base_tree;

	public:
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type())
			: _base_tree(comp, alloc)
		{
		}
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type());
		map(const map &x);

		~map()
		{
		}
		map &operator=(const map &x);
		iterator begin()
		{
			return (_base_tree.begin());
		}
		// const_iterator begin() const;
		iterator end()
		{
			return (_base_tree.end());
		}
		// const_iterator end() const;
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		mapped_type &operator[](const key_type &k)
		{
			iterator it = find(k);

			return (it->second);
		}
		pair<iterator, bool> insert(const value_type &val)
		{
			return _base_tree.insert(val);
		}
		// iterator insert(iterator position, const value_type &val);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);
		// void erase(iterator position);
		size_type erase(const key_type &k);
		// void erase(iterator first, iterator last);
		void swap(map &x);
		void clear();
		key_compare key_comp() const;
		// value_compare value_comp() const;
		iterator find(const key_type &k)
		{
			return (_base_tree.find(k));
		}
		const_iterator find(const key_type &k) const;
		size_type count(const key_type &k) const;
		// iterator lower_bound(const key_type &k);
		// const_iterator lower_bound(const key_type &k) const;
		// iterator upper_bound(const key_type &k);
		// const_iterator upper_bound(const key_type &k) const;
		// pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
		// pair<iterator, iterator> equal_range(const key_type &k);
		allocator_type get_allocator() const
		{
			return (_base_tree.get_allocator());
		}
	};
}
#endif