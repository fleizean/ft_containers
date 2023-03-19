#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
	/**
	 * @brief lexicographical_compare
	 * İki farklı sıralanabilir dizinin (belirtilen aralıklarda) karşılaştırılmasını sağlar.
	 * İlk dizi, ikinci diziye göre alfabetik (ya da sayısal) olarak küçükse, true değerini döndürür.
	 * Eğer iki dizi eşit değilse, false döndürülür.
	 * @tparam InputIt1 
	 * @tparam InputIt2 
	 * @param first1 
	 * @param last1 
	 * @param first2 
	 * @param last2 
	 * @return true 
	 * @return false 
	 */
	template <class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
	                             InputIt2 first2, InputIt2 last2)
	{
	   while (first1 != last1)
	   {
	      if (first1 == first2 || *first2 < *first1)
	         return false;
	      else if (*first1 < *first2)
	         return true;
	      ++first1;
	      ++first2;
	   }
	   return (first2 != last2);
	}
	
	/**
	 * @brief equal
	 * başlangıç ve bitiş değeri verilen iteratorleri karşılaştırır. 
	 * Elemanlar eşitse true, değilse false döndürülür.
	 * @tparam InputIterator1 
	 * @tparam InputIterator2 
	 * @param first1 
	 * @param last1 
	 * @param first2 
	 * @return true 
	 * @return false 
	 */
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
	   while (first1 != last1)
	   {
	      if (!(*first1 == *first2)) // or: if (!pred(*first1,*first2)), for version 2
	         return false;
	      ++first1;
	      ++first2;
	   }
	   return true;
	}
}

#endif