#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"
#include <memory>
#include <stdexcept>

namespace ft
{
	/**
	 * @brief Vector
	 * Vektörler, boyutları girdi girildikçe büyüyen dizileri temsil eden sıralı konteynerlerdir.
	 * @tparam T 
	 * @tparam Alloc 
	 */
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{  
		/* Üye Değişkenler */
		private:
			typedef vector<T, Alloc> vector_type;

		public:
			/* İlk Şablon parametresi (T) */
			typedef T															value_type;
			/* İkinci Şablon parametresi (Alloc) */
			typedef Alloc														allocator_type;
			/* reference türü, allocator_type türünün reference öğesine eşitleniyor. Bu, bu container'daki elemanların referansını belirtmek için kullanılır. */
			typedef typename allocator_type::reference							reference;
			/* const_reference türü, allocator_type türünün const_reference öğesine eşitleniyor. Bu, bu container'daki sabit elemanların referansını belirtmek için kullanılır. */
			typedef typename allocator_type::const_reference					const_reference;
			/* pointer türü, allocator_type türünün pointer öğesine eşitleniyor. Bu, bu container'daki elemanların işaretçisini belirtmek için kullanılır. */
			typedef typename allocator_type::pointer							pointer;
			/* const_pointer türü, allocator_type türünün const_pointer öğesine eşitleniyor. Bu, bu container'daki sabit elemanların işaretçisini belirtmek için kullanılır. */
			typedef typename allocator_type::const_pointer						const_pointer;
			/* iterator türü, ft::random_access_iterator sınıfının pointer ve vector_type öğeleriyle özelleştirilmiş bir sürümüdür. Bu, bu container'ın elemanları üzerinde dolaşmak için kullanılır. */
			typedef ft::random_access_iterator<pointer, vector_type>			iterator;
			/* const_iterator türü, ft::random_access_iterator sınıfının const_pointer ve vector_type öğeleriyle özelleştirilmiş bir sürümüdür. Bu, bu container'ın sabit elemanları üzerinde dolaşmak için kullanılır. */
			typedef ft::random_access_iterator<const_pointer, vector_type>		const_iterator;
			/* reverse_iterator türü, ft::reverse_iterator sınıfının iterator öğesi ile özelleştirilmiş bir sürümüdür. Bu, container'daki elemanları tersten dolaşmak için kullanılır. */
			typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
			/* const_reverse_iterator türü, ft::reverse_iterator sınıfının const_iterator öğesi ile özelleştirilmiş bir sürümüdür. Bu, container'daki sabit elemanları tersten dolaşmak için kullanılır. */
			typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			/* difference_type türü, std::ptrdiff_t ile eşleştirilmiştir. Bu, iterator türündeki iki öğe arasındaki mesafeyi hesaplamak için kullanılır. */
			typedef std::ptrdiff_t												difference_type;
			/* size_t türü, std::size_t ile eşleştirilmiştir. Bu, difference_type ile aynı boyuta sahip olacak şekilde tasarlanmış bir işaretlenmemiş tamsayı türüdür ve sıfırdan büyük tüm değerleri temsil eder. Bu, container'ın boyutunu belirtmek için kullanılır. */
			typedef std::size_t													size_type;

	/* Üye işlevler */
	protected:
		allocator_type		_alloc;
		pointer				_start;
		pointer				_end;
		pointer				_end_capacity;

	/* Üye fonksiyonlar */
	public:
		
	};
}

#endif