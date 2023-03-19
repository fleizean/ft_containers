#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
namespace ft
{

    template<class Iterator>
    class ReverseIterator
    {
        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;

            ReverseIterator() : current() {}
            explicit ReverseIterator(iterator_type x) : current(x) {}

            template <class Iter>
            ReverseIterator(const ReverseIterator<Iter>& other) : current(other.base()) {}

            iterator_type base() const { return current; }
            reference operator*() const {
                iterator_type tmp = current;
                return *--tmp;
            }
            pointer operator->() const { return &(operator*()); }

            ReverseIterator& operator++() {
                --current;
                return *this;
            }

            ReverseIterator operator++(int) {
                ReverseIterator tmp = *this;
                --current;
                return tmp;
            }

            ReverseIterator& operator--() {
                ++current;
                return *this;
            }

            ReverseIterator operator--(int) {
                ReverseIterator tmp = *this;
                ++current;
                return tmp;
            }

            ReverseIterator operator+(difference_type n) const { return ReverseIterator(current - n); }
            ReverseIterator& operator+=(difference_type n) { current -= n; return *this; }
            ReverseIterator operator-(difference_type n) const { return ReverseIterator(current + n); }
            ReverseIterator& operator-=(difference_type n) { current += n; return *this; }

            reference operator[](difference_type n) const { return *(*this + n); }

        private:
            iterator_type current;
    };

        template <class Iterator>
        bool operator==(const ReverseIterator<Iterator>& x, const ReverseIterator<Iterator>& y)
        {
            return x.base() == y.base();
        }

        template <class Iterator>
        bool operator!=(const ReverseIterator<Iterator>& x, const ReverseIterator<Iterator>& y)
        {
            return x.base() != y.base();
        }

        template <class Iterator>
        bool operator<(const ReverseIterator<Iterator>& x, const ReverseIterator<Iterator>& y)
        {
            return y.base() < x.base();
        }

        template <class Iterator>
        bool operator>(const ReverseIterator<Iterator>& x, const ReverseIterator<Iterator>& y)
        {
            return y < x;
        }

        template <class Iterator>
        bool operator<=(const ReverseIterator<Iterator>& x, const ReverseIterator<Iterator>& y)
        {
            return !(y < x);
        }

        template <class Iterator>
        bool operator>=(const ReverseIterator<Iterator>& x, const ReverseIterator<Iterator>& y)
        {
            return !(x < y);
        }
}

#endif