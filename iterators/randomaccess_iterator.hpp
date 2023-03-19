#ifndef RANDOMACCESS_ITERATOR_HPP
#define RANDOMACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template <typename T>
    class RandomAccessIterator
    {

    public:
        typedef	typename iterator_traits<T*>::value_type 	value_type;
		typedef	typename iterator_traits<T*>::pointer	pointer;
		typedef	typename iterator_traits<T*>::reference	reference;
		typedef	typename iterator_traits<T*>::difference_type	difference_type;
		typedef	std::random_access_iterator_tag iterator_category;

        private:
            pointer _ptr;
	public:

		// CONSTRUCTORS
		RandomAccessIterator() : _ptr() {}

		RandomAccessIterator(pointer a) : _ptr(a) {}

		virtual ~RandomAccessIterator() {}

		RandomAccessIterator(const RandomAccessIterator<typename remove_const<value_type>::type > & src) : _ptr(&(*src)) {}

		RandomAccessIterator<value_type> & operator=(RandomAccessIterator<typename remove_const<value_type>::type > const & src) {
			_ptr = &(*src);
			return *this;
		}

        bool operator==(const RandomAccessIterator &rhs) const { return _ptr == rhs._ptr; }
        bool operator!=(const RandomAccessIterator &rhs) const { return _ptr != rhs._ptr; }
        bool operator<(const RandomAccessIterator &rhs) const { return _ptr < rhs._ptr; }
        bool operator<=(const RandomAccessIterator &rhs) const { return _ptr <= rhs._ptr; }
        bool operator>(const RandomAccessIterator &rhs) const { return _ptr > rhs._ptr; }
        bool operator>=(const RandomAccessIterator &rhs) const { return _ptr >= rhs._ptr; }

		int operator+(const RandomAccessIterator &right_hand_side)
        {
            return (this->_ptr + right_hand_side._ptr);
        }
        int operator-(const RandomAccessIterator &right_hand_side)
        {
            return (this->_ptr - right_hand_side._ptr);
        }

        pointer base() const { return _ptr; }
		

		//OPERATORS
		RandomAccessIterator & operator++() {
			++_ptr;
			return *this;
		}

		RandomAccessIterator operator++(int) {
			RandomAccessIterator tmp(*this);
			++_ptr;
			return tmp;
		}

		RandomAccessIterator & operator--() {
			--_ptr;
			return *this;
		}

		RandomAccessIterator  operator--(int) {
			RandomAccessIterator tmp = *this;
			--_ptr;
			return tmp;
		}
		RandomAccessIterator operator+(const difference_type & a) const {
			return _ptr + a;
		}

		RandomAccessIterator operator-(const difference_type & a) const {
			return _ptr - a;
		}

		RandomAccessIterator & operator+=(const difference_type & a) {
			_ptr += a;
			return (*this);
		}

		RandomAccessIterator & operator-=(const difference_type & a) {
			_ptr -= a;
			return (*this);
		}

		pointer operator->() const {
			return _ptr;
		}

		reference operator*() const {
			return *_ptr;
		}

		reference operator[](difference_type n) const {
			return *(_ptr + n);
		}
    };
    template <typename T>
    RandomAccessIterator<T> operator+(typename RandomAccessIterator<T>::difference_type n, const RandomAccessIterator<T> &x) { return x + n; }

 	template <typename T>
    RandomAccessIterator<T> operator-(typename RandomAccessIterator<T>::difference_type n, const RandomAccessIterator<T> &x) { return x - n; }
} // namespace ft
#endif
/*
base() işlemi, bir iterator'un temel halini (base) döndürür.
Bu temel hal, bir arka uç (past-the-end) işaretçisiyle birleştirilebilir ve
çoğu durumda bir aralığın başlangıcını belirlemek için kullanılabilir.
Örneğin, bir reverse_iterator tipindeki bir iterator,
standart bir iteratorun tam tersine işaret eder.
base() işlemi, reverse_iterator'ın işaret ettiği standart iteratorunun
temel halini döndürür.
Böylece, base() işlemi, reverse_iterator'ı bir aralığın sonundan başlayarak
öğeleri gezinmek için kullanırken başlangıç noktasını belirlemek için
kullanılabilir.
*/