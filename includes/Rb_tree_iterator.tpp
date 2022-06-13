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
        Rb_node(/* args */): color(RED), parent(), left(), right() {}
        ~Rb_node() {}
    };
    template <typename Val>
    struct Node : public Rb_node
    {
        Val data;
        Node(Val val): Rb_node(), data(val)
        {
        }
    };

    template <typename T, typename U>
    class Rb_tree_iterator
    {
    private:
        Rb_node *_current;
        typedef iterator_traits<T> _traits_type;

    public:
        typedef T iterator_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef typename _traits_type::value_type value_type;
        typedef typename _traits_type::difference_type difference_type;
        typedef typename _traits_type::reference reference;
        typedef typename _traits_type::pointer pointer;
		typedef Node<U>* link_type;


        Rb_tree_iterator()
            : _current()
        {
        }
        explicit Rb_tree_iterator(Rb_node *src)
            : _current(src)
        {
            //std::cout << "here " << (static_cast<link_type>(_current)->data);
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

        inline friend bool
            operator!=(const Rb_tree_iterator &lhs, const Rb_tree_iterator &rhs)
        {
            return (lhs._current != rhs._current);
        }
    };
}
#endif