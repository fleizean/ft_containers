/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_map_iterator.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:06:15 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/15 10:49:09 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REV_MAP_ITERATOR_HPP
#define REV_MAP_ITERATOR_HPP

#include "../utils/type_traits.hpp"
#include "map_iterator.hpp"

namespace ft
{
        /**
        *  
        * ------------------------------------------------------------- *
        * -------------------- REV_MAP_ITERATOR ------------------- *
        * Coplien form:
        * (constructor): rev_map_iterator oluşturur
        * (destructor): Rev_map_iterator yıkıcı
        * operator=: İçeriği atama işlemi
        * Operators
        * operators: rev_map_iterator için operatörler
        * non-member operators: rev_map_iterator için operatörler
        * ------------------------------------------------------------- *
        */
        
    /**
    *   @param Key      Konteynerin anahtar öğelerinin türü.
    *   @param T        Konteynerin eşlenik öğelerinin türü.
    *   @param Compare  İkili ağacı sıralamak için kullanılan önerge.
    *   @param Node     İkili ağaçta düğümler olarak kullanılan yapı.
    *   @param B        Bir yineleyici / bir sabit yineleyici olup olmadığını belirten bir boolean değeri.
    */
    template<class Key, class T, class Compare, typename Node, bool B>
    class rev_map_iterator
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

            nodePtr         _node;      // Binary tree node'u
            nodePtr         _lastElem;  // Binary tree _last element'i
            key_compare     _comp;      // key_compare için compare tanımlaması
        
        
            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */

        public:
        
            /**
            *   Default constructor
            *
            *   @param node
            *   @param lastElem
            *   @param comp
            */
            rev_map_iterator(nodePtr node = 0, nodePtr lastElem = 0,
                            const key_compare& comp = key_compare()) :
                _node(node), _lastElem(lastElem), _comp(comp) {}
        
            /**
            *   Copy constructor
            *   @param copy
            */
            rev_map_iterator(const rev_map_iterator<Key, T, Compare, Node, false>& copy)
            {
                _node = copy.getNonConstNode();
                _lastElem = copy.getNonConstLastElem();
                _comp = copy.getCompare();
            }
            
            /**
            *   Convert constructor, bir const / const olmayan "map_iterator"dan önceki T elemanını işaret 
            *   eden bir "rev_map_iterator" oluşturan dönüştürücü bir constructor'ı açıklar.
            *   Bu işlem, begin() == rend() ve end() == rbegin() olduğundan gerekli hale gelir.
            *   
            *   @param copy
            */
            explicit rev_map_iterator(map_iterator<Key, T, Compare, Node, false> copy)
            {
                --copy;
                _node = copy.getNonConstNode();
                _lastElem = copy.getNonConstLastElem();
                _comp = copy.getCompare();
            }

            ~rev_map_iterator() {}

            /**
            *   Operator cons
            *   
            *   @param x
            */
            rev_map_iterator& operator=(const rev_map_iterator& assign)
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
            /* --------------------------- GETTERS ------------------------- */

            /**
            *   @return Bu kod bloğu, o anki node'un const olmayan node versiyonunu döndürür.
            */
            nodePtr getNonConstNode() const         { return _node; }

            /**
            *   @return Bu kod bloğu, last elementi işaret eden node döndürür.
            */
            nodePtr getNonConstLastElem() const     { return _lastElem; }

            /**
            *   @return İkili ağacı sıralamak için kullanılan karşılaştırma nesnesini döndürür.
            */
            key_compare getCompare() const          { return _comp; }


            /* ------------------------------------------------------------- */
            /* -------------------------- OPERATORS ------------------------ */

            reference operator*() const             { return (_node->content); }
            pointer operator->() const              { return (&_node->content); }
            rev_map_iterator& operator++()
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
            rev_map_iterator operator++(int)
            {
                rev_map_iterator res(*this);

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
            rev_map_iterator& operator--()
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

            /**
            *   ?
            */
            rev_map_iterator operator--(int)
            {
                rev_map_iterator res(*this);

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

            bool operator==(const rev_map_iterator& it) const   { return (it._node == _node); }
            bool operator!=(const rev_map_iterator& it) const   { return (it._node != _node); }


            /* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */
            /* ------------------------------------------------------------- */
            
        private:

            /**
            *   Ağaçtaki en yüksek anahtara sahip öğeyi arar.
            *
            *   @param root     Ağacın ilk düğümü.
            *   @param return   Ağacın en yüksek anahtarına sahip olan öğe.
            */
            Node* searchMaxNode(Node *root)
            {
                // Ağacın sağ uç noktasına ve döngüsel bağlantı olan _lastElem'e kadar ilerler
                if (root && root != _lastElem && root->right && root->right != _lastElem)
                    return searchMaxNode(root->right);
                return root;
            }

            /**
            *   Bu fonksiyon, ağaçtaki en düşük anahtara sahip öğeyi arar.
            *
            *   @param root     ağacın ilk düğümüdür.
            *   @param return   ağaçtaki en düşük anahtarı içeren öğedir.
            */
            Node* searchMinNode(Node *root)
            {
                // Ağacın sol uç noktasına ve dairesel bağlantı _lastElem'e kadar gider.
                if (root && root != _lastElem && root->left && root->left != _lastElem)
                    return searchMinNode(root->left);
                return root;
            }

    };

}

#endif