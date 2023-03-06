#ifndef ITERATOR_BASE_HPP
#define ITERATOR_BASE_HPP

#include <cstddef>


/*
	iterator_traits bir şablon sınıfıdır ve bir iterator tipinin özelliklerini tanımlamak için kullanılır. 

	value_type: iteratorun işaret ettiği veri türünü belirtir. 
	{
		Örneğin, bir vector<int> üzerinde dolaşan bir iteratorun value_type özelliği int olacaktır.
	}
	difference_type: iki iterator arasındaki mesafeyi belirten tamsayı türünü belirtir.
	{
		Örneğin, bir vector<int> üzerindeki iki iterator arasındaki mesafeyi belirlemek için kullanılır. 
		difference_type özelliği negatif olabilir, bu nedenle iki iterator arasındaki mesafe pozitif veya negatif olabilir.
	}
	pointer: iteratorun işaret ettiği veriye bir işaretçi türüdür.
	{
		Örneğin, bir vector<int> üzerinde dolaşan bir iteratorun pointer özelliği int* olacaktır.
	}
	reference: iteratorun işaret ettiği veriye bir referans türüdür.
	{
		Örneğin, bir vector<int> üzerinde dolaşan bir iteratorun reference özelliği int& olacaktır.
	}
	iterator_category: iteratorun hangi kategoriye ait olduğunu belirtir.
	{
		C++'da, iteratorlar beş kategoriye ayrılır: 
		input_iterator_tag, output_iterator_tag, forward_iterator_tag, bidirectional_iterator_tag ve random_access_iterator_tag. 
		
		Bu özellik, iteratorun özelliklerine göre hangi kategoriye ait olduğunu belirlemek için kullanılır. 
		Örneğin, bir vector<int> üzerinde dolaşan bir iteratorun iterator_category özelliği random_access_iterator_tag olacaktır, 
		çünkü vector'ün random access özelliği vardır ve dolayısıyla vector üzerindeki iteratorlar random access iteratorlardır.
	}
	
	Daha detaylı >> notion'da
*/

namespace ft
{
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template <  typename Category, typename T,
                typename Distance = std::ptrdiff_t,
                typename Pointer = T*,
                typename Reference = T& >

    struct iterator
	{
		typedef Category		iterator_category;
		typedef T				value_type;
		typedef Distance		difference_type;
		typedef Pointer			pointer;
		typedef Reference		reference;
	};

    template <typename Iterator>
    struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

    template <typename T>
    struct iterator_traits<T*>
    {
		typedef random_access_iterator_tag				iterator_category;
		typedef T										value_type;
		typedef std::ptrdiff_t							difference_type;
		typedef T*										pointer;
		typedef T&										reference;
	};

    template <typename T>
    struct iterator_traits<const T*>
    {
		typedef random_access_iterator_tag				iterator_category;
		typedef T										value_type;
		typedef std::ptrdiff_t							difference_type;
		typedef const T*								pointer;
		typedef const T&								reference;
	};
};

#endif