#ifndef RANDOMACCESSITERATOR_HPP
#define RANDOMACCESSITERATOR_HPP

#include "iterator_base.hpp"

namespace ft
{
	template <typename Iterator, typename Container>
	class random_access_iterator
		: public ft::iterator<  typename ft::iterator_traits<Iterator>::iterator_category,
								typename ft::iterator_traits<Iterator>::value_type,
								typename ft::iterator_traits<Iterator>::difference_type,
								typename ft::iterator_traits<Iterator>::pointer,
								typename ft::iterator_traits<Iterator>::reference >
	{
	public:
		typedef typename ft::iterator_traits<Iterator>::difference_Type			difference_type;
		typedef typename ft::iterator_traits<Iterator>::reference				reference;
		typedef typename ft::iterator_traits<Iterator>::pointer					pointer;
	
	/* Üye değişkenler */
	protected:
		Iterator	_current;
	
	public:
		random_access_iterator() : _current(Iterator()) {}

		explicit random_access_iterator(const Iterator& it) : _current(it) {}

		template<typename Iter>
		random_access_iterator(const random_access_iterator<Iter, Container>& it) : _current(it.base()) {}

		virtual ~random_access_iterator() {}

		const Iterator& base() const { return _current; }

		reference operator*() const { return _current; }
		pointer operator->() const { return _current; }
		/* random_access_iterator& operator++() ve random_access_iterator operator++(int) farkı şudur:
		
		random_access_iterator& operator++() önce _current üyesini bir arttırır ve ardından
		artırılmış iterator nesnesini döndürür. Yani, öncelikle mevcut konumu artırır ve sonrasında 
		işlem sonucu olan iterator'ü geri döndürür.
		random_access_iterator operator++(int) ise _current üyesini bir arttırır ancak önceki konumda kalmış olan 
		iterator'ün örneğini döndürür. Yani, öncelikle işlem öncesi iterator örneğini saklar, mevcut konumu
		artırır ve önceki konumda kalmış olan iterator örneğini döndürür.
		*/
		/* Diğer alttakilerde aynısı */
		random_access_iterator& operator++() { ++_current; return *this; }
		random_access_iterator operator++(int) { return random_access_iterator(_current++); }
		random_access_iterator& operator--() { --_current; return *this; }
		random_access_iterator operator--(int) { return random_access_iterator(_current--); }
		random_access_iterator operator+(const difference_type& n) const { return random_access_iterator(_current + n); }
		random_access_iterator& operator+=(const difference_type& n) { _current += n; return *this; }
		random_access_iterator operator-(const difference_type& n) const { return random_access_iterator(_current - n); }
		random_access_iterator& operator-=(const difference_type& n) { _current -= n; return *this; }
		difference_type operator-(const random_access_iterator& it) const { return _current - it._current; }
		reference operator[](const difference_type& n) const { return _current[n]; }

	};

	/*  Class'a bağımlı olmayan overloads tanımlamaları */
}

#endif