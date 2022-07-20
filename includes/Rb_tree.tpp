#ifndef RB_TREE_TPP
#define RB_TREE_TPP
#include "utility.tpp"
#include "iterator.tpp"
#include "type_traits.tpp"
#include "algorithm.tpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

#define SSTR(x) static_cast<std::ostringstream &>(           \
                    (std::ostringstream() << std::dec << x)) \
                    .str()

namespace ft
{
    template <class Key, class Val, typename GetKey, typename Compare, class Alloc>
    class Rb_tree
    {
    private:
        enum Rb_tree_color
        {
            RED = true,
            BLACK = false
        };

        struct Rb_node
        {
            Rb_tree_color color;
            Rb_node *parent;
            Rb_node *left;
            Rb_node *right;

        public:
            Rb_node() : color(RED), parent(), left(), right() {}
            ~Rb_node() {}
            Rb_node &operator=(const Rb_node &rhs)
            {
                color = rhs.color;
                parent = rhs.parent;
                left = rhs.left;
                right = rhs.right;
                return (*this);
            }
        };

        template <typename V>
        struct Node : public Rb_node
        {
            V data;
            Node(V val) : Rb_node(), data(val)
            {
            }
        };

        template <typename T>
        class Rb_tree_iterator
        {
        private:
            template <typename X>
            struct Rb_tree_iterator_traits
            {
            };

            template <typename X>
            struct Rb_tree_iterator_traits<X *>
            {
                typedef Rb_node *node_type;
                typedef Node<X> *link_type;
            };

            template <typename X>
            struct Rb_tree_iterator_traits<const X *>
            {
                typedef const Rb_node *node_type;
                typedef const Node<X> *link_type;
            };

            typedef iterator_traits<T> _traits_type;
            typedef Rb_tree_iterator_traits<T> _traits_type_tree;
            typedef typename _traits_type_tree::node_type node_type;
            node_type _current;

        public:
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef typename _traits_type::value_type value_type;
            typedef typename _traits_type::difference_type difference_type;
            typedef typename _traits_type::reference reference;
            typedef typename _traits_type::pointer pointer;
            typedef typename _traits_type_tree::link_type link_type;

            Rb_tree_iterator()
                : _current()
            {
            }

            explicit Rb_tree_iterator(node_type src)
                : _current(src)
            {
            }

            Rb_tree_iterator(const Rb_tree_iterator<value_type *> &src)
                : _current(src.base()) {}

            Rb_tree_iterator &operator=(const Rb_tree_iterator &rhs)
            {
                _current = rhs._current;
                return (*this);
            }

            node_type base(void) const
            {
                return (_current);
            }

            reference
            operator*() const
            {
                return (static_cast<link_type>(_current)->data);
            }

            pointer
            operator->() const
            {
                return (&static_cast<link_type>(_current)->data);
            }

            void rb_increment()
            {
                if (_current->right)
                {
                    _current = _current->right;
                    while (_current->left)
                        _current = _current->left;
                }
                else
                {
                    Rb_node *p(_current->parent);

                    while (p->right == _current)
                    {
                        _current = p;
                        p = p->parent;
                    }
                    if (_current->right != p)
                        _current = p;
                }
            }

            Rb_tree_iterator &operator++()
            {
                rb_increment();
                return (*this);
            }

            Rb_tree_iterator operator++(int)
            {
                Rb_tree_iterator tmp(*this);
                rb_increment();
                return (tmp);
            }

            void rb_decrement()
            {
                if (_current->color == RED && _current->parent->parent == _current && _current->right)
                {
                    _current = _current->right;
                }
                else if (_current->left)
                {
                    _current = _current->left;
                    while (_current->right)
                        _current = _current->right;
                }
                else
                {
                    Rb_node *p(_current->parent);

                    while (p->left == _current)
                    {
                        _current = p;
                        p = p->parent;
                    }
                    _current = p;
                }
            }
            Rb_tree_iterator &operator--()
            {
                rb_decrement();
                return (*this);
            }
            Rb_tree_iterator operator--(int)
            {
                Rb_tree_iterator tmp(*this);
                rb_decrement();
                return (tmp);
            }

            bool operator!=(const Rb_tree_iterator<T> &rhs) const
            {
                return (_current != rhs._current);
            }

            bool
            operator==(const Rb_tree_iterator<T> &rhs) const
            {
                return (_current == rhs._current);
            }
        };

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
        typedef typename Alloc::template rebind<Node<Val> >::other Node_allocator;

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

            map_impl(const map_impl &src) : Node_allocator(src)
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

        Rb_node *&_root()
        {
            return (_impl.header.parent);
        }

        const Rb_node *_root() const
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

        static link_type _left(Rb_node *n)
        {
            return (static_cast<link_type>(n->left));
        }

        static const_link_type _left(const Rb_node *n)
        {
            return (static_cast<const_link_type>(n->left));
        }

        static link_type _right(Rb_node *n)
        {
            return (static_cast<link_type>(n->right));
        }

        static const_link_type _right(const Rb_node *n)
        {
            return (static_cast<const_link_type>(n->right));
        }

        static const_reference _value(const Rb_node *n)
        {
            return (static_cast<const_link_type>(n)->data);
        }

        static const key_type &_getKey(const Rb_node *n)
        {
            return (GetKey()(_value(n)));
        }

        void _destroy(link_type root)
        {
            if (root)
            {
                _destroy(_left(root));
                _destroy(_right(root));
            }
            get_allocator().destroy(&root->data);
        }

        void _del_node(link_type root)
        {
            get_allocator().destroy(&root->data);
            get_Node_allocator().deallocate(root, 1);
        }

        void _destroy_and_deallocate(link_type root)
        {
            if (root)
            {
                _destroy_and_deallocate(_left(root));
                _destroy_and_deallocate(_right(root));
                _del_node(root);
            }
        }

        link_type _deep_copy(const_link_type n, Rb_node *p)
        {
            link_type copy(_alloc_node(n->data, p, 0, 0));

            if (n->right)
                copy->right = _deep_copy(_right(n), copy);
            if (n->left)
                copy->left = _deep_copy(_left(n), copy);
            return (copy);
        }

        void _deep_copy(const Rb_node *n)
        {
            _root() = _deep_copy(static_cast<const_link_type>(n), _end());
            _impl.header.right = _rightmost(_root());
            _impl.header.left = _leftmost(_root());
        }

        link_type _alloc_node(const value_type &val, Rb_node *p, Rb_node *l, Rb_node *r, Rb_tree_color c = RED)
        {
            link_type newNode = get_Node_allocator().allocate(1);
            get_Node_allocator().construct(newNode, val);
            newNode->parent = p;
            newNode->left = l;
            newNode->right = r;
            newNode->color = c;
            return (newNode);
        }

        static Rb_node *_leftmost(Rb_node *n)
        {
            while (n->left)
                n = n->left;
            return (n);
        }

        static Rb_node *_rightmost(Rb_node *n)
        {
            while (n->right)
                n = n->right;
            return (n);
        }

        void _rotateRight(Rb_node *const n)
        {
            Rb_node *const newRoot(n->left);

            n->left = newRoot->right;
            if (n->left)
                n->left->parent = n;

            newRoot->right = n;
            newRoot->parent = n->parent;

            if (n == _root())
                _root() = newRoot;
            else if (n->parent->left == n)
                n->parent->left = newRoot;
            else
                n->parent->right = newRoot;
            n->parent = newRoot;
        }

        void _rotateLeft(Rb_node *const n)
        {
            Rb_node *const newRoot(n->right);

            n->right = newRoot->left;
            if (n->right)
                n->right->parent = n;

            newRoot->left = n;
            newRoot->parent = n->parent;

            if (n == _root())
                _root() = newRoot;
            else if (n->parent->left == n)
                n->parent->left = newRoot;
            else
                n->parent->right = newRoot;
            n->parent = newRoot;
        }

        pair<Rb_node *, bool> _getNodeToInsert(const key_type &key)
        {
            Rb_node *tmp(_root());
            Rb_node *prev(_end());

            bool comp = true;
            while (tmp)
            {
                comp = _impl.comp(key, _getKey(tmp));
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
            if (_impl.comp(_getKey(p.base()), key))
                return (ft::make_pair(prev, true));
            return (ft::make_pair(prev, false));
        }

        pair<Rb_node *, bool> _getNodeToInsertWithHint(iterator pos, const key_type &key)
        {
            if (pos.base() == _end())
            {
                if (size() > 0 && _impl.comp(_getKey(_impl.header.right), key))
                    return (ft::make_pair(_impl.header.right, true));
                else
                    return (_getNodeToInsert(key));
            }
            else if (_impl.comp(key, _getKey(pos.base())))
            {
                if (pos.base() == _begin())
                    return (ft::make_pair(_impl.header.left, true));
                iterator prev(pos);
                --prev;
                if (_impl.comp(_getKey(prev.base()), key))
                {
                    if (prev.base()->right)
                        return (ft::make_pair(pos.base(), true));
                    else
                        return (ft::make_pair(prev.base(), true));
                }
                else
                    return (_getNodeToInsert(key));
            }
            else if (_impl.comp(_getKey(pos.base()), key))
            {
                if (pos.base() == _impl.header.right)
                    return (ft::make_pair(_impl.header.right, true));
                iterator after(pos);
                ++after;
                if (_impl.comp(key, _getKey(after.base())))
                {
                    if (pos.base()->right)
                        return (ft::make_pair(after.base(), true));
                    else
                        return (ft::make_pair(pos.base(), true));
                }
                else
                    return (_getNodeToInsert(key));
            }
            return (ft::make_pair(pos.base(), false));
        }

        void _rebalance(Rb_node *n)
        {
            while (n != _root() && n->parent->color == RED)
            {
                Rb_node *gp(n->parent->parent); // grand parent of n
                if (n->parent == gp->right)     // uncle of n is gp->left
                {
                    Rb_node *u(gp->left); // uncle of n
                    if (u && u->color == RED)
                    {
                        n->parent->color = BLACK;
                        u->color = BLACK;
                        gp->color = RED;
                        n = gp;
                    }
                    else
                    {
                        if (n->parent->left == n)
                        {
                            n = n->parent;
                            _rotateRight(n);
                        }
                        _rotateLeft(gp);
                        gp->color = RED;
                        n->parent->color = BLACK;
                    }
                }
                else // uncle of n is gp->right
                {
                    Rb_node *u(gp->right); // uncle of n
                    if (u && u->color == RED)
                    {
                        n->parent->color = BLACK;
                        u->color = BLACK;
                        gp->color = RED;
                        n = gp;
                    }
                    else
                    {
                        if (n->parent->right == n)
                        {
                            n = n->parent;
                            _rotateLeft(n);
                        }
                        _rotateRight(gp);
                        gp->color = RED;
                        n->parent->color = BLACK;
                    }
                }
            }
            _root()->color = BLACK;
        }

        link_type _insert(Rb_node *n, const value_type &val)
        {
            link_type newNode(_alloc_node(val, n, 0, 0, RED));
            if (n == _end() || _impl.comp(GetKey()(val), _getKey(n)))
            {
                n->left = newNode;
                if (n == _end()) // newNode is first node
                {
                    _root() = newNode;
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
            _rebalance(newNode);
            return (newNode);
        }

        void _erase(Rb_node *n)
        {
            Rb_node *p(n->parent);
            Rb_node *successor1(0); // successor of n if n has 1 child max
            Rb_node *successor2(0); // successor of n if n has 2 child
            Rb_node *db;            // node who might be double black
            Rb_node *db_parent;

            if (!n->left)
                successor1 = n->right;
            else if (!n->right)
                successor1 = n->left;
            else
            {
                successor2 = n->right;
                successor2 = _leftmost(successor2);
                db = successor2->right;
            }
            if (successor2)
            {
                if (successor2 != n->right)
                {
                    Rb_node *r(successor2->right);
                    if (r)
                        r->parent = successor2->parent;
                    successor2->parent->left = r;
                    successor2->right = n->right;
                    successor2->right->parent = successor2;
                    db_parent = successor2->parent;
                }
                else
                    db_parent = successor2;
                successor2->left = n->left;
                successor2->left->parent = successor2;
                successor2->parent = p;
                if (n == _root())
                    _root() = successor2;
                else if (p->left == n)
                    p->left = successor2;
                else
                    p->right = successor2;
                std::swap(n->color, successor2->color);
            }
            else
            {
                if (successor1)
                    successor1->parent = p;
                if (n == _root())
                    _root() = successor1;
                else if (p->left == n)
                    p->left = successor1;
                else
                    p->right = successor1;
                if (n == _impl.header.left)
                {
                    if (!n->right)
                        _impl.header.left = n->parent;
                    else
                        _impl.header.left = _leftmost(successor1);
                }
                if (n == _impl.header.right)
                {
                    if (!n->left)
                        _impl.header.right = n->parent;
                    else
                        _impl.header.right = _rightmost(successor1);
                }
                db = successor1;
                db_parent = n->parent;
            }
            if (n->color == BLACK) // db can be double black
            {
                while (db != _root() && (db == 0 || db->color == BLACK)) // while db is double black
                {
                    if (db_parent->left == db)
                    {
                        Rb_node *s(db_parent->right); // sibling of double black node
                        if (s->color == RED)
                        {
                            std::swap(s->color, db_parent->color);
                            _rotateLeft(db_parent);
                            s = db_parent->right;
                        }
                        // s is always black here
                        if ((s->left && s->left->color == RED) || (s->right && s->right->color == RED))
                        {
                            if (!s->right || s->right->color == BLACK) // r is left
                            {
                                std::swap(s->color, s->left->color);
                                _rotateRight(s);
                                s = db_parent->right;
                            }
                            s->color = db_parent->color;
                            db_parent->color = BLACK;
                            s->right->color = BLACK;
                            _rotateLeft(db_parent);
                            break;
                        }
                        else
                        {
                            s->color = RED;
                            db = db_parent;
                            db_parent = db->parent;
                        }
                    }
                    else
                    {
                        Rb_node *s(db_parent->left); // sibling of double black node
                        if (s->color == RED)
                        {
                            std::swap(s->color, db_parent->color);
                            _rotateRight(db_parent);
                            s = db_parent->left;
                        }
                        // s is always black here
                        if ((s->left && s->left->color == RED) || (s->right && s->right->color == RED))
                        {
                            if (!s->left || s->left->color == BLACK) // r is right
                            {
                                std::swap(s->color, s->right->color);
                                _rotateLeft(s);
                                s = db_parent->left;
                            }
                            s->color = db_parent->color;
                            db_parent->color = BLACK;
                            s->left->color = BLACK;
                            _rotateRight(db_parent);
                            break;
                        }
                        else
                        {
                            s->color = RED;
                            db = db_parent;
                            db_parent = db->parent;
                        }
                    }
                }
                if (db)
                    db->color = BLACK;
            }
            _del_node(static_cast<link_type>(n));
            _impl.node_count--;
        }

        Node_allocator &
        get_Node_allocator()
        {
            return (this->_impl);
        }

        const Node_allocator &
        get_Node_allocator() const
        {
            return (this->_impl);
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
            if (src._root())
                _deep_copy(src._root());
        }

        Rb_tree &operator=(const Rb_tree &rhs)
        {
            if (this != &rhs)
            {
                clear();
                _impl.node_count = rhs._impl.node_count;
                _impl.comp = rhs._impl.comp;
                if (rhs._root())
                    _deep_copy(rhs._root());
            }
            return (*this);
        }

        ~Rb_tree()
        {
            _destroy_and_deallocate(static_cast<link_type>(_root()));
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

        pair<iterator, bool> insert(const value_type &val)
        {
            pair<Rb_node *, bool> p(_getNodeToInsert(GetKey()(val)));
            Rb_node *n(p.first);
            if (!p.second) // n key found in tree
                return (ft::make_pair(iterator(n), false));
            return (ft::make_pair(iterator(_insert(n, val)), true));
        }

        iterator insert(const_iterator position, const value_type &val)
        {
            pair<Rb_node *, bool> p(_getNodeToInsertWithHint(iterator(const_cast<Rb_node *>(position.base())), GetKey()(val)));
            Rb_node *n(p.first);

            if (!p.second) // n key found in tree
                return (iterator(n));
            return (iterator(_insert(n, val)));
        }

        template <class InputIterator>
        void insert(InputIterator first,
                    typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
        {
            while (first != last)
                insert(*first++);
        }

        void erase(iterator position)
        {
            _erase(position.base());
        }

        void erase(const_iterator position)
        {
            _erase(const_cast<Rb_node *>(position.base()));
        }

        size_type erase(const key_type &k)
        {
            const_iterator it(find(k));
            if (it == end())
                return (size_type(0));
            const Rb_node *n(it.base());
            _erase(const_cast<Rb_node *>(n));
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

        void erase(const_iterator first, const_iterator last)
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
            std::swap(_root(), x._root());
            std::swap(_impl.header.left, x._impl.header.left);
            std::swap(_impl.header.right, x._impl.header.right);
            std::swap(_impl.node_count, x._impl.node_count);

            if (_root())
                _root()->parent = _end();
            else
                _impl.reset();
            if (x._root())
                x._root()->parent = x._end();
            else
                x._impl.reset();
            std::swap(_impl.comp, x._impl.comp);
        }

        void clear()
        {
            _destroy_and_deallocate(static_cast<link_type>(_root()));
            _impl.reset();
        }

        Compare key_comp() const
        {
            return (_impl.comp);
        }

        iterator find(const key_type &k)
        {
            Rb_node *tmp(_root());
            while (tmp)
            {
                if (_impl.comp(k, _getKey(tmp)))
                    tmp = tmp->left;
                else if (_impl.comp(_getKey(tmp), k))
                    tmp = tmp->right;
                else
                    return (iterator(tmp));
            }
            return (end());
        }

        const_iterator find(const key_type &k) const
        {
            const Rb_node *tmp(_root());
            while (tmp)
            {
                if (_impl.comp(k, _getKey(tmp)))
                    tmp = tmp->left;
                else if (_impl.comp(_getKey(tmp), k))
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
            const Rb_node *tmp(_root());
            const Rb_node *ret(_end());
            while (tmp)
            {
                if (!_impl.comp(_getKey(tmp), k)) // k <=
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
            Rb_node *tmp(_root());
            Rb_node *ret(_end());
            while (tmp)
            {
                if (!_impl.comp(_getKey(tmp), k)) // k <=
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
            Rb_node *tmp(_root());
            Rb_node *ret(_end());
            while (tmp)
            {
                if (_impl.comp(k, _getKey(tmp))) // k <
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
            const Rb_node *tmp(_root());
            const Rb_node *ret(_end());
            while (tmp)
            {
                if (_impl.comp(k, _getKey(tmp))) // k <
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
            Rb_node *tmp(_root());
            Rb_node *upper(_end());
            Rb_node *lower(_end());
            while (tmp)
            {
                if (!_impl.comp(_getKey(tmp), k)) // k <=
                {
                    if (_impl.comp(k, _getKey(tmp))) // k <
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
            const Rb_node *tmp(_root());
            const Rb_node *upper(_end());
            const Rb_node *lower(_end());
            while (tmp)
            {
                if (!_impl.comp(_getKey(tmp), k)) // k <=
                {
                    if (_impl.comp(k, _getKey(tmp))) // k <
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

        // std::string createDotString() const
        // {
        //     std::string finalS = "digraph rbt{\n";
        //     finalS += createDotString(_root());
        //     finalS += "}\n";
        //     return finalS;
        // }

        // std::string createDotString(const Rb_node *root) const
        // { // function to help visualize tree
        //     if (root == NULL)
        //     {
        //         return "";
        //     }
        //     std::string currentNodeS = "";

        //     if (root->left)
        //     { // order important to maintain bst property in dot (left node comes first)
        //         currentNodeS += SSTR(_getKey(root)) + std::string("->") + SSTR(_value(root->left).first) + std::string(";\n");
        //     }
        //     if (root->right)
        //     {
        //         currentNodeS += SSTR(_getKey(root)) + std::string("->") + SSTR(_value(root->right).first) + std::string(";\n");
        //     }
        //     if (root->color == BLACK)
        //     {
        //         currentNodeS += SSTR(_getKey(root)) + std::string("[style = \"filled\" fillcolor = \"black\" fontcolor=\"white\"];\n");
        //     }
        //     else
        //     {
        //         currentNodeS += SSTR(_getKey(root)) + std::string("[style = \"filled\" fillcolor = \"red\" fontcolor=\"white\"];\n");
        //     }
        //     currentNodeS += createDotString(root->left);
        //     currentNodeS += createDotString(root->right);
        //     return (currentNodeS);
        // }

        // void tree_draw(const std::string &name) const
        // {
        //     std::string dotString(createDotString());
        //     std::ofstream myfile;
        //     myfile.open("rbt.dot");
        //     myfile << dotString;
        //     myfile.close();
        //     system(std::string("dot -Tpng rbt.dot -o " + name + ".png").c_str());
        //     remove("rbt.dot");
        // }
    };
}

#endif