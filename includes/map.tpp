#ifndef MAP_TPP
#define MAP_TPP
#include "utility.tpp"
#include <iostream>

namespace ft
{
	enum Rb_tree_color
	{
		RED = false,
		BLACK = true
	};
	template <class Key, class T, class Val, typename Compare, class Alloc>
	class Rb_tree
	{
	public:
		typedef Key 				key_type;
		typedef Val 				value_type;
		typedef value_type 			*pointer;
		typedef const value_type 		*const_pointer;
		typedef value_type			&reference;
		typedef const value_type 		&const_reference;
		typedef size_t 				size_type;
		typedef ptrdiff_t 			difference_type;
		typedef Alloc 				allocator_type;
	private:
		struct Rb_node
		{
			Rb_tree_color _color;
			Rb_node *parent;
			Rb_node *left;
			Rb_node *right;
			// Val data;
		public:
			Rb_node(/* args */) {}
			~Rb_node() {}
		};
		struct Node : public Rb_node
		{
			Val data;
		};
		typedef typename __gnu_cxx::__alloc_traits<Alloc>::template rebind<Node>::other Node_allocator;
		typedef __gnu_cxx::__alloc_traits<Node_allocator> Alloc_traits;

		struct map_impl : public Node_allocator, Rb_node
		{
			Compare comp;
			size_t node_count;
			map_impl() : Node_allocator()
			{
			}
			map_impl(const Compare &comp,
				const allocator_type &a) : Node_allocator(a), comp(comp)
			{
			}
			map_impl(const map_impl &src): Node_allocator(src), comp(src.comp)
			{

			}
		};
		map_impl _impl;

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
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

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
		// iterator begin();
		// const_iterator begin() const;
		// iterator end();
		// const_iterator end() const;
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		mapped_type &operator[](const key_type &k);
		// pair<iterator, bool> insert(const value_type &val);
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
		// iterator find(const key_type &k);
		// const_iterator find(const key_type &k) const;
		size_type count(const key_type &k) const;
		// iterator lower_bound(const key_type &k);
		// const_iterator lower_bound(const key_type &k) const;
		// iterator upper_bound(const key_type &k);
		// const_iterator upper_bound(const key_type &k) const;
		// pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
		// pair<iterator, iterator> equal_range(const key_type &k);
		allocator_type get_allocator() const;
	};
}
#endif