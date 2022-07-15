#ifndef RB_TREE_ITERATOR_TPP
#define RB_TREE_ITERATOR_TPP
#include "iterator_traits.tpp"

namespace ft
{
    enum Rb_tree_color
    {
        RED = false,
        BLACK = true
    };
    struct Rb_node
    {
        Rb_tree_color color;
        Rb_node *parent;
        Rb_node *left;
        Rb_node *right;
        // Val data;
    public:
        Rb_node(): color(RED), parent(), left(), right() {}
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
    template <typename Val>
    struct Node : public Rb_node
    {
        Val data;
        Node(Val val): Rb_node(), data(val)
        {
        }
    };


    template <typename T>
    class Rb_tree_iterator
    {
    private:
        template<typename X>
        struct Rb_tree_iterator_traits
        {

        };
        template<typename X>
        struct Rb_tree_iterator_traits<X *>
        {
            typedef Rb_node* node_type;
            typedef Node<X>* link_type;   
        };
        template<typename X>
        struct Rb_tree_iterator_traits<const X *>
        {
            typedef const Rb_node* node_type;
            typedef const Node<X>* link_type;
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

		Rb_tree_iterator(const Rb_tree_iterator<value_type*> &src)
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
        operator*() const _GLIBCXX_NOEXCEPT
        {
            return (static_cast<link_type>(_current)->data);
        }

        pointer
        operator->() const _GLIBCXX_NOEXCEPT
        {
            return (&static_cast<link_type>(_current)->data);
        }

        void    rb_increment()
        {
            if (_current->right)
            {
                _current = _current->right;
                while (_current->left)
                    _current = _current->left;
            }
            else
            {
                Rb_node *p (_current->parent);

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
            // if (_current->color == BLACK)
            //     std::cout << " BLACK " << std::endl;
            // else
            //     std::cout << " RED " << std::endl;
            rb_increment();
            return (*this);
        }
        Rb_tree_iterator operator++(int)
        {
            Rb_tree_iterator tmp (*this);
            // if (_current->color == BLACK)
            //     std::cout << " BLACK " << std::endl;
            // else
            //     std::cout << " RED " << std::endl;
            rb_increment();
            return (tmp);
        }
        void    rb_decrement()
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
                Rb_node *p (_current->parent);

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
            Rb_tree_iterator tmp (*this);
            rb_decrement();
            return (tmp);
        }

        // template<typename U>
        // friend bool operator!=(Rb_tree_iterator<U> rhs)
        // {
        //     return (lhs._current != rhs.base());
        // }
        

        // friend bool operator!=(Rb_tree_iterator<T> lhs, Rb_tree_iterator<const T> rhs)
        // {
        //     return (lhs._current != rhs.base());
        // }
        bool operator!=(const Rb_tree_iterator<T> &rhs) const
        {
            return (_current != rhs._current);
        }
        // bool operator!=(Rb_tree_iterator<const T> lhs, Rb_tree_iterator<T> rhs)
        // {
        //     return (lhs.base() != rhs.base());
        // }
        // bool operator!=(const Rb_tree_iterator<T> &rhs)
        // {
        //     return (_current != rhs._current);
        // }
        bool
            operator==(const Rb_tree_iterator<T> &rhs) const
        {
            return (_current == rhs._current);
        }
    };
    
    

   
}
#endif