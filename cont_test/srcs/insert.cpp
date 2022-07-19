#include <map>

template <typename _Arg>
iterator
_M_insert_unique_(const_iterator __pos, _Arg &&__x)
{
  _Alloc_node __an(*this);
  return _M_insert_unique_(__pos, std::forward<_Arg>(__x), __an);
}

template <typename _Key, typename _Val, typename _KeyOfValue,
          typename _Compare, typename _Alloc>
template <typename _NodeGen>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_unique_(const_iterator __position,
                      const _Val &__v,
                      _NodeGen &__node_gen)
{
  pair<_Base_ptr, _Base_ptr> __res = _M_get_insert_hint_unique_pos(__position, _KeyOfValue()(__v));

  if (__res.second)
    return _M_insert_(__res.first, __res.second,
                      _GLIBCXX_FORWARD(_Arg, __v),
                      __node_gen);
  return iterator(__res.first);
}
template <typename _Key, typename _Val, typename _KeyOfValue,
          typename _Compare, typename _Alloc>
pair<typename _Rb_tree<_Key, _Val, _KeyOfValue,
                       _Compare, _Alloc>::_Base_ptr,
     typename _Rb_tree<_Key, _Val, _KeyOfValue,
                       _Compare, _Alloc>::_Base_ptr>
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_get_insert_hint_unique_pos(const_iterator __position,
                                  const key_type &__k)
{
  iterator __pos = __position._M_const_cast();
  typedef pair<_Base_ptr, _Base_ptr> _Res;

  // end()
  if (__pos._M_node == _M_end())
  {
    if (size() > 0 && _M_impl._M_key_compare(_S_key(_M_rightmost()), __k))
      return _Res(0, _M_rightmost());
    else
      return _M_get_insert_unique_pos(__k);
  }
  else if (_M_impl._M_key_compare(__k, _S_key(__pos._M_node)))
  {
    // First, try before...
    iterator __before = __pos;
    if (__pos._M_node == _M_leftmost()) // begin()
      return _Res(_M_leftmost(), _M_leftmost());
    else if (_M_impl._M_key_compare(_S_key((--__before)._M_node), __k))
    {
      if (_S_right(__before._M_node) == 0)
        return _Res(0, __before._M_node);
      else
        return _Res(__pos._M_node, __pos._M_node);
    }
    else
      return _M_get_insert_unique_pos(__k);
  }
  else if (_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
  {
    // ... then try after.
    iterator __after = __pos;
    if (__pos._M_node == _M_rightmost())
      return _Res(0, _M_rightmost());
    else if (_M_impl._M_key_compare(__k, _S_key((++__after)._M_node)))
    {
      if (_S_right(__pos._M_node) == 0)
        return _Res(0, __pos._M_node);
      else
        return _Res(__after._M_node, __after._M_node);
    }
    else
      return _M_get_insert_unique_pos(__k);
  }
  else
    // Equivalent keys.
    return _Res(__pos._M_node, 0);
}

std::pair<iterator, bool>
insert(const value_type &__x)
{
  return _M_t._M_insert_unique(__x);
}

template <typename _Key, typename _Val, typename _KeyOfValue,
          typename _Compare, typename _Alloc>
pair<typename _Rb_tree<_Key, _Val, _KeyOfValue,
                       _Compare, _Alloc>::iterator,
     bool>
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_unique(const _Val &__v)
{
  typedef pair<iterator, bool> _Res;
  pair<_Base_ptr, _Base_ptr> __res = _M_get_insert_unique_pos(_KeyOfValue()(__v));

  if (__res.second)
  {
    _Alloc_node __an(*this);
    return _Res(_M_insert_(__res.first, __res.second,
                           _GLIBCXX_FORWARD(_Arg, __v), __an),
                true);
  }

  return _Res(iterator(__res.first), false);
}

template <typename _Key, typename _Val, typename _KeyOfValue,
          typename _Compare, typename _Alloc>
pair<typename _Rb_tree<_Key, _Val, _KeyOfValue,
                       _Compare, _Alloc>::_Base_ptr,
     typename _Rb_tree<_Key, _Val, _KeyOfValue,
                       _Compare, _Alloc>::_Base_ptr>
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_get_insert_unique_pos(const key_type &__k)
{
  typedef pair<_Base_ptr, _Base_ptr> _Res;
  _Link_type __x = _M_begin();
  _Base_ptr __y = _M_end();
  bool __comp = true;
  while (__x != 0)
  {
    __y = __x;
    __comp = _M_impl._M_key_compare(__k, _S_key(__x));
    __x = __comp ? _S_left(__x) : _S_right(__x);
  }
  iterator __j = iterator(__y);
  if (__comp)
  {
    if (__j == begin())
      return _Res(__x, __y);
    else
      --__j;
  }
  if (_M_impl._M_key_compare(_S_key(__j._M_node), __k))
    return _Res(__x, __y);
  return _Res(__j._M_node, 0);
}

template <typename _Key, typename _Val, typename _KeyOfValue,
          typename _Compare, typename _Alloc>
template <typename _NodeGen>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_insert_(_Base_ptr __x, _Base_ptr __p,
               const _Val &__v,
               _NodeGen &__node_gen)
{

  bool __insert_left = (__x != 0 || __p == _M_end() || _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__p)));

  _Link_type __z = __node_gen(_GLIBCXX_FORWARD(_Arg, __v));

  _Rb_tree_insert_and_rebalance(__insert_left, __z, __p,
                                this->_M_impl._M_header);
  ++_M_impl._M_node_count;
  return iterator(__z);
}

void _Rb_tree_insert_and_rebalance(const bool __insert_left,
                                   _Rb_tree_node_base *__x,
                                   _Rb_tree_node_base *__p,
                                   _Rb_tree_node_base &__header) throw()
{
  _Rb_tree_node_base *&__root = __header._M_parent;

  // Initialize fields in new node to insert.
  __x->_M_parent = __p;
  __x->_M_left = 0;
  __x->_M_right = 0;
  __x->_M_color = _S_red;

  // Insert.
  // Make new node child of parent and maintain root, leftmost and
  // rightmost nodes.
  // N.B. First node is always inserted left.
  if (__insert_left)
  {
    __p->_M_left = __x; // also makes leftmost = __x when __p == &__header

    if (__p == &__header)
    {
      __header._M_parent = __x;
      __header._M_right = __x;
    }
    else if (__p == __header._M_left)
      __header._M_left = __x; // maintain leftmost pointing to min node
  }
  else
  {
    __p->_M_right = __x;

    if (__p == __header._M_right)
      __header._M_right = __x; // maintain rightmost pointing to max node
  }
  // Rebalance.
  while (__x != __root && __x->_M_parent->_M_color == _S_red)
  {
    _Rb_tree_node_base *const __xpp = __x->_M_parent->_M_parent;

    if (__x->_M_parent == __xpp->_M_left)
    {
      _Rb_tree_node_base *const __y = __xpp->_M_right;
      if (__y && __y->_M_color == _S_red)
      {
        __x->_M_parent->_M_color = _S_black;
        __y->_M_color = _S_black;
        __xpp->_M_color = _S_red;
        __x = __xpp;
      }
      else
      {
        if (__x == __x->_M_parent->_M_right)
        {
          __x = __x->_M_parent;
          local_Rb_tree_rotate_left(__x, __root);
        }
        __x->_M_parent->_M_color = _S_black;
        __xpp->_M_color = _S_red;
        local_Rb_tree_rotate_right(__xpp, __root);
      }
    }
    else
    {
      _Rb_tree_node_base *const __y = __xpp->_M_left;
      if (__y && __y->_M_color == _S_red)
      {
        __x->_M_parent->_M_color = _S_black;
        __y->_M_color = _S_black;
        __xpp->_M_color = _S_red;
        __x = __xpp;
      }
      else
      {
        if (__x == __x->_M_parent->_M_left)
        {
          __x = __x->_M_parent;
          local_Rb_tree_rotate_right(__x, __root);
        }
        __x->_M_parent->_M_color = _S_black;
        __xpp->_M_color = _S_red;
        local_Rb_tree_rotate_left(__xpp, __root);
      }
    }
  }
  __root->_M_color = _S_black;
}