/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:20:22 by llefranc          #+#    #+#             */
/*   Updated: 2023/03/17 02:06:26 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR
#define MAP_ITERATOR

#include "../utils/type_traits.hpp"

namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * ---------------------- MAP_ITERATOR --------------------- *
    *
    * - Coplien form:
    * (constructor):        Map_iterator oluştur
    * (destructor):         Map_iterator yıkıcı
    * operator=:            İçeriği atama
    *
    * - Operators
    * operators:            Map_iterator için operatörler
    * non-member operators: Map_iterator için global operatörler
    * ------------------------------------------------------------- *
    */
        
    /**
    *   @param Key      Konteynerin anahtar öğelerinin türü.
    *   @param T        Konteynerin eşlenmiş öğelerinin türü.
    *   @param Compare  İkili ağacı sıralamak için kullanılan önişlemci.
    *   @param Node     İkili ağaçtaki düğümler olarak kullanılan yapı.
    *   @param B        Bir yinelenen / sabit yinelenen mi olduğunu belirtmek için kullanılan bir boolean değeri.
    */
    template <class Key, class T, class Compare, typename Node, bool B>
    class map_iterator
    {
            /* ------------------------------------------------------------- */
            /* -------------------------- ALIASES -------------------------- */

        public:
        
            typedef Key                                             key_type;
            typedef Compare                                         key_compare;
            typedef T                                               mapped_type;
            
            typedef ft::pair<const key_type, mapped_type>           value_type;
            typedef long int                                        difference_type;
            typedef size_t                                          size_type;
            
            typedef std::bidirectional_iterator_tag                                     iterator_category;
            typedef typename chooseConst<B, value_type&, const value_type&>::type       reference;
            typedef typename chooseConst<B, value_type*, const value_type*>::type       pointer;
            typedef Node*                                                               nodePtr;
            

            /* ------------------------------------------------------------- */
            /* ------------------------- ATTRIBUTES ------------------------ */
            
        private:

            nodePtr         _node;      // Pointer to a binary tree's node
            nodePtr         _lastElem;  // Pointer to the dummy node of binary tree
            key_compare     _comp;      // Comparison object used to sort the binary tree
            

            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */

        public:

            /**
            *   Default constructor
            *   @param nod
            *   @param last
            *   @param comp
            */
            map_iterator(nodePtr node = 0, nodePtr lastElem = 0, 
                        const key_compare& comp = key_compare()) :
                _node(node), _lastElem(lastElem), _comp(comp) {}
        
            /**
            *   Copy constructor
            *   @param copy
            */
            map_iterator(const map_iterator<Key, T, Compare, Node, false>& copy)
            {
                _node = copy.getNode();
                _lastElem = copy.getLastElem();
                _comp = copy.getCompare();
            }
            
            ~map_iterator() {}

            /**
            *   operator cons 
            *   @param x
            */
            map_iterator& operator=(const map_iterator& assign)
            {
                if (this != &assign)
                {
                    _node = assign._node;
                    _lastElem = assign._lastElem;
                    _comp = assign._comp;
                }
                return (*this);
            }


            /* ------------------------------------------------------------- */
            /* -------------------------- GETTERS -------------------------- */

            /**
            *   @return O anki node'u döndürür
            */
            nodePtr getNode() const             { return _node; }
            
            /**
            *   @return O anki son elemanı döndürür
            */
            nodePtr getLastElem() const         { return _lastElem; }
            
            /**
            *   @return key_compare compare'i döndürür
            */
            key_compare getCompare() const      { return _comp; }


            /* ------------------------------------------------------------- */
            /* -------------------------- OPERATORS ------------------------ */
            
            reference operator*() const         { return (_node->content); }
            pointer operator->() const          { return (&_node->content); }

            map_iterator& operator++()
            {
                nodePtr previousNode = _node;

                if (_node == _lastElem)
                {
                    _node = _lastElem->right;
                    return (*this);
                }
                while (_node != _lastElem && !_comp(previousNode->content.first, _node->content.first))
                {
                    if (_node->right && (_node->right == _lastElem || 
                            _comp(previousNode->content.first, _node->right->content.first)))
                    {
                        _node = _node->right;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMinNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }
                return (*this);
            }

            map_iterator operator++(int)
            {
                map_iterator res(*this);

                if (_node == _lastElem)
                {
                    _node = _lastElem->right;
                    return (res);
                }
                
                while (_node != _lastElem && !_comp(res->first, _node->content.first))
                {
                    if (_node->right && (_node->right == _lastElem || 
                            _comp(res->first, _node->right->content.first)))
                    {
                        _node = _node->right;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMinNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }
                
                return (res);
            }

            map_iterator& operator--()
            {
                nodePtr previousNode = _node;

                if (_node == _lastElem)
                {
                    _node = _lastElem->left;
                    return (*this);
                }

                while (_node != _lastElem && !_comp(_node->content.first, previousNode->content.first))
                {
                    if (_node->left && (_node->left == _lastElem || 
                            _comp(_node->left->content.first, previousNode->content.first)))
                    {
                        _node = _node->left;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }

                return (*this);
            }
            map_iterator operator--(int)
            {
                map_iterator res(*this);

                if (_node == _lastElem)
                {
                    _node = _lastElem->left;
                    return (res);
                }
                
                while (_node != _lastElem && !_comp(_node->content.first, res->first))
                {
                    if (_node->left && (_node->left == _lastElem || 
                            _comp(_node->left->content.first, res->first)))
                    {
                        _node = _node->left;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }
                
                return (res);
            }

            bool operator==(const map_iterator& it) const   { return (it._node == _node); }
            bool operator!=(const map_iterator& it) const   { return (it._node != _node); }


            /* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */
            /* ------------------------------------------------------------- */

        private:

            /**
            *   Ağaçtaki en yüksek anahtara sahip öğeyi arar.
            *
            *   @param root
            *   @param return
            */
            Node* searchMaxNode(Node *root)
            {
                if (root && root != _lastElem && root->right && root->right != _lastElem)
                    return searchMaxNode(root->right);
                return root;
            }

            /**
            *   Ağaçtaki en düşük anahtara sahip öğeyi arar.
            *
            *   @param root
            *   @param return
            */
            Node* searchMinNode(Node *root)
            {
                if (root && root != _lastElem && root->left && root->left != _lastElem)
                    return searchMinNode(root->left);
                return root;
            }
    };
}


#endif