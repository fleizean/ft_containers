#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_base.hpp"

namespace ft
{
    template <typename Iterator>
    class reverse_iterator
        : public ft::iterator<  typename ft::iterator_traits<Iterator>::iterator_category,
                                typename ft::iterator_traits<Iterator>::value_type,
                                typename ft::iterator_traits<Iterator>::difference_type,
                                typename ft::iterator_traits<Iterator>::pointer,
                                typename ft::iterator_traits<Iterator>::reference >

    {
    public:
        typedef Iterator                                                    iterator_type;
        typedef typename ft::iterator_traits<Iterator>::differenc_type      difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
        typedef typename ft::iterator_traits<Iterator>::reference           reference;
    
    // Üye değişkenler
    protected:
        iterator_type       _current;
    
    public:
        reverse_iterator() : _current() {}

    // explicit tür dönüşümüne izin vermez
    explicit reverse_iterator(iterator_type it) : _current(it) {}

    // copy constructor
    template<typename Iter>
    reverse_iterator(const reverse_iterator<Iter>& rev_it) : _current(rev_it.base()) {}

    // destructor
    virtual ~reverse_iterator() {}

    iterator_type base() const { return _current; } // o anki elemanları (_current) karşılaştırmada kullanırız örn: vectorde bu olay var

    reference operator*() const { Iterator tmp = _current; return *--tmp; }

    pointer operator->() const { return &(operator*()); }

    reverse_iterator& operator++() { --_current; return *this; }
    reverse_iterator operator++(int) {reverse_iterator tmp(*this); --_current; return tmp; }

    reverse_iterator& operator--() { ++_current; return *this; }
    reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++_current; return tmp; }

    reverse_iterator operator+(difference_type n) const { return reverse_iterator(_current - n); }
    reverse_iterator& operator+=(difference_type n) { _current -= n; return *this; }

    reverse_iterator operator-(difference_type n) const { return reverse_iterator(_current + n); }
    reverse_iterator& operator-=(difference_type n) {_current += n; return *this; }
    
    reference operator[](difference_type n) const { return *(*this + n); }
    };

    // Üye olmayan işlevler
    	template <typename Iterator1, typename Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return lhs.base() != rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return lhs.base() > rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return lhs.base() >= rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return lhs.base() < rhs.base(); }

	template <typename Iterator1, typename Iterator2>
	bool operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return lhs.base() <= rhs.base(); }

    template <typename Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                            const reverse_iterator<Iterator> &rev_it)
    { return reverse_iterator<Iterator>(rev_it.base() - n); }

    template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(
		const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{ return rhs.base() - lhs.base(); }
}

#endif