#ifndef MAP_TPP
#define MAP_TPP
#include "utility.tpp"
#include "Rb_tree_iterator.tpp"
#include "iterator.tpp"
#include "type_traits.tpp"
#include "algorithm.tpp"
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
		typedef Rb_tree_iterator<pointer> iterator;
		typedef Rb_tree_iterator<const_pointer> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
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
				reset();
			}
			void reset()
			{
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
			map_impl(const map_impl &src)
			{
				*this = src;
			}
			map_impl &operator=(const map_impl &src)
			{
				this->node_count = src.node_count;
				this->header = src.header;
				this->comp = src.comp;
				return (*this);
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
			return (_impl.header.parent);
		}
		Rb_node *&_begin()
		{
			return (_impl.header.left);
		}
		const Rb_node *_begin() const
		{
			return (_impl.header.left);
		}
		Rb_node *_end()
		{
			return (&_impl.header);
		}
		const Rb_node *_end() const
		{
			return (&_impl.header);
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
		void	destroy(link_type root)
		{
			if (root)
			{
				destroy(left(root));
				destroy(right(root));
			}
			get_allocator().destroy(&root->data);	
		}
		void	del_node(link_type root)
		{
			get_allocator().destroy(&root->data);	
			get_Node_allocator().deallocate(root, 1);
		}

		void	destroy_and_deallocate(link_type root)
		{
			if (root)
			{
				destroy_and_deallocate(left(root));
				destroy_and_deallocate(right(root));
				del_node(root);
			}
		}

		link_type _deep_copy(const_link_type n, Rb_node *p)
		{
			link_type copy (alloc_node(n->data, p, 0, 0));

			if (n->right)
				copy->right = _deep_copy(right(n), copy);
			if (n->left)
				copy->left = _deep_copy(left(n), copy);
			return (copy);
		}

		void _deep_copy(const Rb_node *n)
		{
			root() = _deep_copy(static_cast<const_link_type>(n), _end());
			_impl.header.right = rightmost(root());
			_impl.header.left = leftmost(root());
		}

		link_type	alloc_node(const value_type &val, Rb_node *p, Rb_node *l, Rb_node *r, Rb_tree_color c = RED)
		{
			link_type newNode = get_Node_allocator().allocate(1);
			get_Node_allocator().construct(newNode, val);
			newNode->parent = p;
			newNode->left = l;
			newNode->right = r;
			newNode->color = c;
			return (newNode);
		}

		static	Rb_node *leftmost(Rb_node *n)
		{
			while (n->left)
				n = n->left;
			return (n);
		}
		static	Rb_node *rightmost(Rb_node *n)
		{
			while (n->right)
				n = n->right;
			return (n);
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
			if (src.root())
				_deep_copy(src.root());
		}

		Rb_tree &operator=(const Rb_tree &rhs)
		{
			if (this != &rhs)
			{
				clear();
				_impl.node_count = rhs._impl.node_count;
				_impl.comp = rhs._impl.comp;
				if (rhs.root())
					_deep_copy(rhs.root());
			}
			return (*this);
		}

		~Rb_tree()
		{
			destroy_and_deallocate(static_cast<link_type>(root()));
		}

		iterator begin()
		{
			return (iterator(_begin()));
		}

		const_iterator begin() const
		{
			return (const_iterator(_begin()));
		}

		iterator end()
		{
			return (iterator(_end()));
		}

		const_iterator end() const
		{
			return (const_iterator(_end()));
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
			return (_impl.node_count == 0);
		}

		size_type size() const
		{
			return (_impl.node_count);
		}

		size_type max_size() const
		{
			return (get_Node_allocator().max_size());
		}

		pair<Rb_node*, bool> getNodeToInsert(const key_type &key)
		{
			Rb_node *tmp(root());
			Rb_node *prev(_end());

			bool comp = true;
			while (tmp)
			{
				comp = _impl.comp(key, value(tmp).first);
				prev = tmp;
				if (comp)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			iterator p(prev);
			if (comp)
			{
				if (p == begin())
				{
					return (ft::make_pair(prev, true));
				}
				else
					p--;
			}
			if (_impl.comp(p->first, key))
				return (ft::make_pair(prev, true));
			return (ft::make_pair(prev, false));
		}

		pair<Rb_node*, bool> getNodeToInsertWithHint
			(iterator pos, const key_type &key)
		{
			if (pos.base() == _end())
			{
				if (_impl.comp(value(_impl.header.right).first, key))
					return (ft::make_pair(_impl.header.right, true));
				else
					return(getNodeToInsert(key));
			}
			else if (_impl.comp(key, value(pos.base()).first))
			{
				if (pos.base() == _begin())
					return (ft::make_pair(_impl.header.left, true));
				iterator prev (pos);
				--prev;
				if (_impl.comp(value(prev.base()).first, key))
				{
					if (prev.base()->right)
						return (ft::make_pair(pos.base(), true));
					else
						return (ft::make_pair(prev.base(), true));
				}
				else
					return (getNodeToInsert(key));
			}
			else if (_impl.comp(value(pos.base()).first, key))
			{
				if (pos.base() == _impl.header.right)
					return (ft::make_pair(_impl.header.right, true));
				iterator after (pos);
				++after;
				if (_impl.comp(key, value(after.base()).first))
				{
					if (pos.base()->right)
						return (ft::make_pair(after.base(), true));
					else
						return (ft::make_pair(pos.base(), true));
				}
				else
					return (getNodeToInsert(key));

			}
			return (ft::make_pair(pos.base(), false));
		}

		
		link_type	_insert(Rb_node *n, const value_type &val)
		{

			link_type newNode (alloc_node(val, n, 0, 0, RED));
			if (_impl.comp(val.first, value(n).first) || n == _end())
			{
				n->left = newNode;
				if (n == _end()) // newNode is first node
				{
					root() = newNode;
					_impl.header.right = newNode;
				}
				else if (n == _impl.header.left)
					_impl.header.left = newNode;
			}
			else
			{
				n->right = newNode;
				if (n == _impl.header.right)
					_impl.header.right = newNode;
			}
			_impl.node_count++;
			return (newNode);
		}

		pair<iterator, bool> insert(const value_type &val)
		{
			// Node<Val> a(val);
			pair<Rb_node*, bool> p (getNodeToInsert(val.first));
			Rb_node *n (p.first);
			if (!p.second) // n key found in tree
				return (ft::make_pair(iterator(n), false));
			return (ft::make_pair(iterator(_insert(n, val)), true));
		}

		iterator insert(iterator position, const value_type &val)
		{
			pair<Rb_node*, bool> p (getNodeToInsertWithHint(position, val.first));
			Rb_node *n (p.first);

			if (!p.second) // n key found in tree
				return (iterator(n));
			return (iterator(_insert(n, val)));
		}

		template<class InputIterator>
		void insert(InputIterator first,
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
		{
			while (first != last) 
            	insert(*first++);
		}

		void erase(iterator position)
		{
			erase(position->first);
		}
		size_type erase(const key_type &k)
		{
			iterator it (find(k));
			if (it == end())
				return (size_type(0));

			Rb_node *n (it.base());
			Rb_node *p (n->parent);
			if (n == root())
			{
				//std::cout << "root " << value(n->right).first << std::endl;
				if (n->left)
				{ 
					root() = n->left;
					root()->parent = &_impl.header;
					p = root();
					if (n->right)
					{
						while (p->right)
							p = p->right;
						p->right = n->right;
						p->right->parent = p;
						
					}
					else if (n == _impl.header.right)
						_impl.header.right = p;
					

				}
				else
				{
					root() = n->right;
					root()->parent = &_impl.header;
					_impl.header.left = root();
				}
				
			}
			else if (p->right == n)
			{
				if (n->left)
				{
					p->right = n->left;
					p->right->parent = p;
					if (n->right)
					{
						while (p->right)
							p = p->right;
						p->right = n->right;
						p->right->parent = p;
					}
					
				}
				else
				{
					p->right = n->right;
					if (p->right)
						p->right->parent = p;
					else if (n == _impl.header.right)
						_impl.header.right = p;
				}
				if (p->right && n == _impl.header.right)
					_impl.header.right = p->right;
				
				
			}
			else
			{
				if (n->right)
				{
					p->left = n->right;
					p->left->parent = p;
					if (n->left)
					{
						while (p->left)
							p = p->left;
						p->left = n->left;
						p->left->parent = p;
					}
				}
				else
				{
					p->left = n->left;
					if (p->left)
						p->left->parent = p;
					else if (n == _impl.header.left)
						_impl.header.left = p;
				}
				if (p->left && n == _impl.header.left)
					_impl.header.left = p->left;
			}
			del_node(static_cast<link_type>(n));
			_impl.node_count--;
			return (size_type(1));
		}
		void erase(iterator first, iterator last)
		{
			if (first == begin() && last == end())
      			clear();
			else
			{
				while (first != last)
					erase(first++);
			}
		}
		void swap(Rb_tree &x)
		{
			std::swap(root(), x.root());
			std::swap(_impl.header.left, x._impl.header.left);
			std::swap(_impl.header.right, x._impl.header.right);
			std::swap(_impl.node_count, x._impl.node_count);

			if (root())
				root()->parent = _end();
			else
				_impl.reset();
			if (x.root())
				x.root()->parent = x._end();
			else
				x._impl.reset();
			std::swap(_impl.comp, x._impl.comp);
		}
		void clear()
		{
			destroy_and_deallocate(static_cast<link_type>(root()));
			_impl.reset();
		}

		Compare key_comp() const
		{
			return (_impl.comp);
		}

		iterator find(const key_type &k)
		{
			Rb_node *tmp (root());
			while (tmp)
			{
				if (_impl.comp(k, value(tmp).first))
					tmp = tmp->left;
				else if (_impl.comp(value(tmp).first, k))
					tmp = tmp->right;
				else
					return (iterator(tmp));
			}
			return (end());
		}
		const_iterator find(const key_type &k) const
		{
			const Rb_node *tmp (root());
			while (tmp)
			{
				if (_impl.comp(k, value(tmp).first))
					tmp = tmp->left;
				else if (_impl.comp(value(tmp).first, k))
					tmp = tmp->right;
				else
					return (const_iterator(tmp));
			}
			return (end());
		}

		size_type count(const key_type &k) const
		{
			const_iterator it = find(k);
			if (it != end())
				return (size_type(1));
			return (size_type(0));
		}
		const_iterator lower_bound(const key_type &k) const
		{
			const Rb_node *tmp (root());
			const Rb_node *ret (_end());
			while (tmp)
			{
				if (!_impl.comp(value(tmp).first, k)) //k <=
				{
					ret = tmp;
					tmp = tmp->left;
				}
				else
					tmp = tmp->right;
			}
			return (const_iterator(ret));
		}
		iterator lower_bound(const key_type &k)
		{
			Rb_node *tmp (root());
			Rb_node *ret (_end());
			while (tmp)
			{
				if (!_impl.comp(value(tmp).first, k)) //k <=
				{
					ret = tmp;
					tmp = tmp->left;
				}
				else
					tmp = tmp->right;
			}
			return (iterator(ret));
		}
		iterator upper_bound(const key_type &k)
		{
			Rb_node *tmp (root());
			Rb_node *ret (_end());
			while (tmp)
			{
				if (_impl.comp(k, value(tmp).first)) // k <
				{
					ret = tmp;
					tmp = tmp->left;
				}
				else
					tmp = tmp->right;
			}
			return (iterator(ret));
		}
		const_iterator upper_bound(const key_type &k) const
		{
			const Rb_node *tmp (root());
			const Rb_node *ret (_end());
			while (tmp)
			{
				if (_impl.comp(k, value(tmp).first)) // k <
				{
					ret = tmp;
					tmp = tmp->left;
				}
				else
					tmp = tmp->right;
			}
			return (const_iterator(ret));
		}
		pair<iterator, iterator> equal_range(const key_type &k)
		{
			Rb_node *tmp (root());
			Rb_node *upper (_end());
			Rb_node *lower (_end());
			while (tmp)
			{
				if (!_impl.comp(value(tmp).first, k)) // k <=
				{
					if (_impl.comp(k, value(tmp).first)) // k <
					{
						upper = tmp;
						tmp = tmp->left;
					}
					else // not k < => equal k
					{
						lower = tmp;
						tmp = tmp->right;
					}
				}
				else
					tmp = tmp->right;
			}
			if (lower == _end())
				return (ft::make_pair(iterator(upper), iterator(upper)));
			return (ft::make_pair(iterator(lower), iterator(upper)));
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			const Rb_node *tmp (root());
			const Rb_node *upper (_end());
			const Rb_node *lower (_end());
			while (tmp)
			{
				if (!_impl.comp(value(tmp).first, k)) // k <=
				{
					if (_impl.comp(k, value(tmp).first)) // k <
					{
						upper = tmp;
						tmp = tmp->left;
					}
					else // not k < => equal k
					{
						lower = tmp;
						tmp = tmp->right;
					}
				}
				else
					tmp = tmp->right;
			}
			if (lower == _end())
				return (ft::make_pair(const_iterator(upper), const_iterator(upper)));
			return (ft::make_pair(const_iterator(lower), const_iterator(upper)));
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

		friend bool
		operator==(const Rb_tree &lhs, const Rb_tree &rhs)
		{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		friend bool
		operator<(const Rb_tree &lhs, const Rb_tree &rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
												rhs.begin(), rhs.end()));
		}

		friend bool
		operator!=(const Rb_tree &lhs, const Rb_tree &rhs)
		{
			return (!(lhs == rhs));
		}

		friend bool
		operator<=(const Rb_tree &lhs, const Rb_tree &rhs)
		{
		return (!(rhs < lhs));
		}

		friend bool
		operator>(const Rb_tree &lhs, const Rb_tree &rhs)
		{
		return (rhs < lhs);
		}

		friend bool
		operator>=(const Rb_tree &lhs, const Rb_tree &rhs)
		{
		return (!(lhs < rhs));
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
		typedef typename __gnu_cxx::__alloc_traits<Alloc>::template rebind<value_type>::other Pair_alloc_type;
		typedef Rb_tree<key_type, mapped_type, value_type, key_compare, Pair_alloc_type> tree_type;

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
	};
}
#endif