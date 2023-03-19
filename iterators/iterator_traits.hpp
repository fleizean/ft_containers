#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

# include <string>
# include <iterator>
# include <iostream>

/**
 * iterator_traits isimli bir template yapısıdır.
 * Bu yapının tek bir parametresi vardır: Iterator.
 * iterator_traits yapısı, Iterator türüne ait özelliklerin belirlenmesinde kullanılır.
 * iterator_traits yapısı, Iterator türünün altı adet özelliğini belirler:
 * - difference_type: iki iterator arasındaki mesafeyi ifade eden tamsayı türü.
 * - value_type: iterator'un gösterdiği elemanın türü.
 * - pointer: iterator'un gösterdiği elemanın adresini tutan bir işaretçi türü.
 * - reference: iterator'un gösterdiği elemanın referansını tutan bir tür.
 * - iterator_category: iterator'un kategorisini belirten bir tür.
 * Bu özelliklere erişmek için typename anahtar kelimesi kullanılır.
 */

namespace ft
{								
   template<class T> struct remove_const { typedef T type; };

	template<class T> struct remove_const <const T> { typedef T type; };
	
	
	template <class Iterator> class iterator_traits
	{
		public:
			typedef typename Iterator::difference_type	difference_type;
			typedef typename Iterator::value_type				value_type;
			typedef typename Iterator::pointer			pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template <class T> class iterator_traits<T*>
	{
		public:
			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*			pointer;
			typedef T&			reference;
			typedef	std::random_access_iterator_tag	iterator_category;
	};
	
	template <class T> class iterator_traits<const T*>
	{
		public:
			typedef std::ptrdiff_t	difference_type;
			typedef const T				value_type;
			typedef const T*			pointer;
			typedef const T&			reference;
			typedef	std::random_access_iterator_tag	iterator_category;
	};
};

#endif
