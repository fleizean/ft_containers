#ifndef VECTOR_HPP
#define VECTOR_HPP
//design patern: https://cplusplus.com/reference/vector/vector/?kw=vector


#include <stddef.h>
#include <memory> // typename A = std::allocator<T>
#include <iostream>
#include <string>
#include "../iterators/reverse_iterator.hpp"
#include "../iterators/randomaccess_iterator.hpp"


#include "../utils/type_traits.hpp"
#include "../utils/algorithm.hpp"
#include "../utils/pair.hpp"
namespace ft
{

	/*
	üye tipleri 			|	definasyonları																			|

	value_type				|	İlk şablon parametresi  (T)																|
	allocator_type			|	İkinci şablon parametresi (Alloc)														|
	reference				|	allocator_type::reference																|
	const_reference			|	allocator_type::const_reference															|
	pointer					|	allocator_type::pointer																	|
	const_pointer			|	allocator_type::const_pointer															|
	iterator				|	random access iterator for value_type													|
	const_iterator			|	random access iterator for const value_type												|
	reverse_iterator		|	reverse_iterator<iterator>																|
	const_reverse_iterator	|	reverse_iterator<const_iterator>														|
	difference_type			|	iki pointer veya iterator için bellek bloğundaki iki adresin mesafe aralığı				|	ptrdiff_t kullanılma sebebi negatif değerleri de alabilmesidir
	size_type				|	genellikle bir container boyutunu depolamak için kullanılır.							|	size_t negatif değer alamaz üstteki ile farkı budur

	*/
    template <class T, class Alloc = std::allocator<T> >
    class vector
	{
        public:
            typedef T                                       value_type; // element tipi
            typedef Alloc                                   allocator_type; // allocator için nesne 
            typedef typename Alloc::reference               reference;
            typedef typename Alloc::const_reference         const_reference;
            typedef typename Alloc::pointer                 pointer;
            typedef typename Alloc::const_pointer           const_pointer;
            typedef ft::RandomAccessIterator<value_type>         iterator;
            typedef ft::RandomAccessIterator<const value_type>	const_iterator;
            typedef ft::ReverseIterator<iterator>       reverse_iterator;
            typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;
            typedef ptrdiff_t                               difference_type; //	iki pointer veya iterator için mesafe aralığı
            typedef std::size_t                             size_type;
			
        private:
            size_type                                       _size;
            size_type                                       _capacity;
            Alloc                                           _allocator;
            value_type                                      *_data;        

		/*
		member functions

		(constructor)		Vektör Construct (public member function)
		(destructor)		Vektör destructor (public member function)
		operator=			Vektör Assign operator (public member function)

		*/	

		/*
		explicit ifadesi'nin tanımı notion'da yazıyor, kısaca backgroundda yapılan otomatik veri convert
		işlemini bastırmak için kullanılır.
		*/
        public:
			//default vector
            explicit vector(const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _allocator(alloc), _data(NULL){}

			//fill vector
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(n), _capacity(n), _allocator(alloc), _data(NULL)
			{
			    _data = _allocator.allocate(_capacity);
			    for (size_type i = 0; i < this->_size; i++)
			        this->_allocator.construct(&this->_data[i], val);
			}

			//range vector
			template <class InputIterator>
			explicit vector(InputIterator first, InputIterator sec, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true): _size(0), _capacity(0), _data(NULL), _allocator(alloc)
			{
			    assign(first, sec);
			};

			public:
			//copy constructor
            vector(const vector& other):_size(other._size), _capacity(other._capacity), _allocator(other._allocator), _data(other._data){}
			
			vector &operator=(const vector &vector)
        	{
            	if (this == &vector)
            	    return (*this);
            	*this = vector;
            	return (*this);
        	}
            ~vector(){if (this->_data != NULL) clear();};

			/*
			member functions - iterators:
			begin		Başlangıç elementini point eden iterator döndürür
			end			Bitiş elementini point eden iterator döndürür
			rbegin		Bitiş elementinden başlayarak ters iterator döndürür
			rend		Başangıç elemntinden başlayarak ters iterator döndürür
			cbegin		const_iterator olarak başlangıcı işaret eden iterator döndürür.
			cend		cons_iterator olarak bitişi işaret eden iterator döndürür.
			crbegin		cons_iterator olarak bitiş elementinden başlayan ters iteratör döndürür.
			crend		const_iterator olarak başlangıç elementinden başlayan ters iteratör döndürür.
			*/
			
			/*
			rbegin example:
			-------------------------------------------------
			example arr: 3, 7, 10, 2, 1, 55, 44, 22, 90 , 31
			after rbegin: 31, 90, 22, 44, 55, 1, 2, 10, 7, 3
			-------------------------------------------------

			rend example:
			-------------------------------------------------
			example arr: 3, 7, 10, 2, 1, 55, 44, 22, 90 , 31
			after rend: 31, 90, 22, 44, 55, 1, 2, 10, 7, 3,
			-------------------------------------------------
			*/


			//------------Iterator Functions------------------------//
				//begin
				//end
				//rbegin
				//rend

            iterator begin(){return iterator(this->_data);}
			const_iterator begin() const { return const_iterator(this->_data); }

			iterator end(){return iterator(this->_data + this->_size);}
			const_iterator end() const {return const_iterator(this->_data + this->_size);}

            reverse_iterator rbegin(){ return (reverse_iterator(this->end())); }
            const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }
			
            reverse_iterator rend(){return (reverse_iterator(this->begin() - 1));}
            const_reverse_iterator rend() const {return (const_reverse_iterator(this->begin() - 1));}
		//------------Iterator Functions end------------------------//

			/*
			member functions - capacity:
			size			vektörün içindeki eleman sayısını döndürür.
			max_size		vektörün sahip olabileceği en büyük eleman sayısını döndürür.
			resize			vektörün boyutunu değiştirir.
			capacity		vektörün sahip olduğu bellek alanının büyüklüğünü döndürür.
			empty			vektörün boş olup olmadığını kontrol eder. (true false)
			reserve			vektörün kapasitesini arttırır.
			shrink_to_fit	vektörün kapasitesini vektörün boyutuna eşit hale getirir. (c++98 sürümünde yok)

			reserve ve resize farkı;
			reserve fonksiyonu, kapasiteyi arttırırken resize fonksiyonu ise vektörün boyutunu değiştirir.
			*/

 		//------------Capacity Functions------------------------//
			//size
			//max_size
			//resize
			//capacity
			//empty
			//reserve
			//shrink_to_fit c++11 (bu proje kapsamında sadece c++98 yapıldığı için yok sadece bilgilendirme için)

            size_t size() const {return this->_size;}

            size_t max_size() const {return this->_allocator.max_size();}

			
			void resize(size_type n, value_type val = value_type())
			{
				if (n == this->_size)
					return ;
				if (n < this->_size)
				{
					size_type i = n;
					while(i != this->_size)
						this->_allocator.destroy(&this->_data[i++]);
				}
				else
				{
					size_type i = n;
					size_type oldSize = this->_size;
					while (i > oldSize)
					{
						this->push_back(val);
						i--;
					}
				}
				this->_size = n;
			}

            size_t capacity() const {return this->_capacity;}

			bool empty()
			{
				if (this->_size)
					return (false);
				return (true);
			}
			


			void reserve(size_t size)
			{
				this->_reAlloc(size);
			}

		//------------Capacity Functions end------------------------//

		/*
		member functions - element access:
		operator[]	Elemana ulaşmak için kullanılır. (örn: a[5])
		at			Elemana ulaşmak için kullanılır. (örn: a.at(5) -> 5. index)
		front		İlk elemanın referansını döndürür.
		back		Son elemanın referansını döndürür.	
		*/

		//------------Element Access------------------------//
			//operator[]
			//at
			//front
			//back

			reference operator[](size_type n)
			{
				return (_data[n]);
			}
			const_reference operator[] (size_type n) const
			{
				return (_data[n]);
			}

			reference at(size_type n)
			{
				this->checkIndex(n);
				return (this->_data[n]);
			}
			const_reference at (size_type n) const
			{
				this->checkIndex(n);
				return (this->_data[n]);
			}

			reference front(void)
			{
				return (this->_data[0]);
			}
			const_reference front(void) const
			{
				return (this->_data[0]);
			}

			reference back(void)
			{
				return (this->_data[this->_size - 1]);
			}
			const_reference back(void) const
			{
				return (this->_data[this->_size - 1]);
			}


        //------------Element Access end------------------------//

			/*
			member functions - modifiers:
			assign			Assign vector content (public member function)
			push_back		Add element at the end (public member function)
			pop_back		Delete last element (public member function)
			insert			Insert elements (public member function)
			erase			Erase elements (public member function)
			swap			Swap content (public member function)
			clear			Clear content (public member function)
			emplace			Construct and insert element (public member function)
			emplace_back	Construct and insert element at the end (public member function)
			*/
			//------------Modifiers Functions------------------------//
			//assign
			//push_back
			//pop_back
			//insert
			//erase
			//swap
			//clear
			//emplace c++11
			//emplace_back c++11
			/*
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true
			Bu kısım, bir SFINAE (Substitution Failure Is Not An Error) tekniği kullanılarak fonksiyonun template argümanlarının 
			türlerine göre derlenebilirlik durumunu kontrol ediyor.

			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true ifadesi, InputIt türünün int veya long gibi tamsayı türleri olmadığı durumlarda
			(yani !ft::is_integral<InputIt>::value durumunda) bu template fonksiyonunun tanımlanması için bir koşul olarak kullanılıyor. 
			Eğer bu koşul sağlanırsa, bool türünden bir değer döndürülüyor ve bu değer varsayılan olarak true olarak atanıyor.

			Bu teknik, bir fonksiyonun şablon parametreleri tarafından belirlenen türlerin belirli özellikleri taşıması gerektiği durumlarda kullanılabilir. 
			Burada InputIt türünün tamsayı olmaması gerektiği durumlarda, enable_if ile birlikte yazılan koşulun sağlanmaması durumunda derleme hatası alınmaz, 
			ancak bu fonksiyonun şablonu, diğer uygun koşullar sağlandığında hala derlenebilir olur.
			*/


			/**
			 * @brief Verilen first ve last aralığı kadar yeni bir konteynır oluşturur elemanları da o aralık boyunca bütün sayılar olur.
			 * 
			 * @tparam InputIt 
			 * @param first 
			 * @param last 
			 */
			template< class InputIt >
			void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
			{
				if (this->_data)// Vektör bellekte bir yer kaplıyorsa, onu serbest bırak
					this->_allocator.deallocate(this->_data, this->_capacity);
				this->_size = last - first;// Vektörün yeni boyutunu hesapla ve _size'a ata
				if (this->_capacity < this->_size)// Eğer vektör kapasitesi, boyuttan küçükse, kapasiteyi boyuta eşitle
					this->_capacity = this->_size;
				this->_data = this->_allocator.allocate(this->_capacity);// Yeni kapasite kadar bellekte yer ayır
				for (size_type i = 0; i < this->_size; i++)// Vektöre elemanları ekle
					this->_allocator.construct(&this->_data[i], *(first + i));
			}

			/**
			 * @brief Verilen n sayısı kadar value değerini ekler örn: 5, 6 (5'tane 6 ekleyecek)
			 * 
			 * @param n 
			 * @param val 
			 */
			void assign (size_type n, const value_type& val)
			{
				clear();
				if (n > this->_capacity)
				{
					this->_allocator.deallocate(this->_data, this->_capacity);
					this->_data = this->_allocator.allocate(n);
					this->_capacity = n;
				}

				for (size_type i = 0; i < n; i++)
					this->_allocator.construct(&this->_data[i],val);
				this->_size = n;
			}
			
			void push_back(value_type value)
			{
			    if (this->_size == this->_capacity)
					reserve(this->_capacity == 0 ? 1 : this->_capacity + 1);
            	this->_allocator.construct(&this->_data[this->_size], value);
            	this->_size++;
			}

            void pop_back(void)
            {
                if (this->_size == 0)
                    return ;
                this->_allocator.destroy(this->_data + this->_size - 1);
                this->_size--;
                this->_capacity--;
            }
			
			/**
			 * @brief Belirtilen pozisyona tek bir eleman eklemek için kullanılır
			 * 
			 * @param position 
			 * @param val 
			 * @return iterator 
			 */
			iterator insert(iterator position, const value_type& val)
            {
				size_type index = position - begin();
            	if (this->_size >= this->_capacity)
            	{
            	    _smart_reAlloc(this->_size + 1);
            	    position = begin() + index;
            	}
            	iterator last = end() - 1;
            	while (last >= position)
            	{
            	    *(last + 1) = *last;
            	    --last;
            	}
            	this->_allocator.construct(&(*(position)), val);
            	++this->_size;
            	return (begin() + index);
            }

			/**
			 * @brief Belirtilen pozisyona n tane value değerini ekler.
			 * 
			 * @param position 
			 * @param n 
			 * @param val 
			 */
            void insert(iterator position, size_type n,const value_type& val)
            {
                size_type index = position - begin();
            	if (this->_size + n > this->_capacity)
            	{
            	    _smart_reAlloc(this->_size + n);
            	    position = begin() + index;
            	}
            	iterator last = end() - 1;
            	while (last >= position)
            	{
            	    *(last + n) = *last;
            	    --last;
            	}
            	for (iterator it = position; it != position + n; ++it)
            	    this->_allocator.construct(&(*it), val);
            	this->_size += n;
            }

			/**
			 * @brief Belirtilen pozisyona verilen aralıktaki sayıları ekler. (first - last aralığı kadar sayılar)
			 * 
			 * @tparam InputIterator 
			 * @param position 
			 * @param first 
			 * @param last 
			 */
			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
			{
				difference_type const	idx = position - this->begin();
				difference_type const	old_end_idx = this->end() - this->begin();
				iterator				old_end, end;
				size_type dist = last - first;
				this->resize(this->_size + dist);

				end = this->end();
				position = this->begin() + idx;
				old_end = this->begin() + old_end_idx;
				while (old_end != position)
					*--end = *--old_end;
				while (first != last)
					*position++ = *first++;
			}

			/**
			 * @brief verilen pozisyondaki elemanı silmek için kullanılır
			 * 
			 * @param pos 
			 * @return iterator 
			 */
			iterator erase(iterator pos)
            {
  				iterator iter = pos;
				
				this->_allocator.destroy(&(*pos)); // o pozisyondaki elemanı siler
				while (iter != (this->end() - 1))
					this->_allocator.construct(&(*iter), *(++iter)); // o pozisyona elemanı ekler kaydırma işlemi de uygulanır.
				this->_size--;
				return (pos);
            }

			/**
			 * @brief verilen aralıktaki elemanları siler
			 * 
			 * @param first 
			 * @param last 
			 * @return iterator 
			 */
            iterator erase(iterator first, iterator last)
            {
                size_type dist = last - first;

  				iterator iter = first;
 			 	for (size_type i = 0; i < dist; ++i, ++iter) 
        			this->_allocator.destroy(&(*iter));
				if (last != this->end()) // silinecek elemanlar son elemanlar değilse, kaydırmamız gerekiyor
				{
						std::copy(last, this->end(), first);
    			}			
                this->_size -= dist;
                return first;
            }

			void swap(vector& other)
			{
				size_type tempSize = other._size;
				size_type tempCapacity = other._capacity;
				Alloc	  tempAlloc = other._allocator;
				pointer   tempArray = other._data;

				other._size = this->_size;
				other._capacity = this->_capacity;
				other._allocator = this->_allocator;
				other._data = this->_data;

				this->_size = tempSize;
				this->_capacity = tempCapacity;
				this->_allocator = tempAlloc;
				this->_data = tempArray; 
			}

			void clear()
            {
				for (size_t i = 0; i < this->_size; i++)
					this->_allocator.destroy(&_data[i]);
				if (this->_data != NULL)
					this->_allocator.deallocate(this->_data, this->_capacity);
				this->_data = NULL;
				this->_size = 0;
				this->_capacity = 0;
            }

		//------------Modifiers Functions end------------------------//


		/*
		allocator:
			get_allocator
		*/	

		//------------Allocator Functions------------------------//


			allocator_type get_allocator() const
        	{
            return (this->_allocator);
        	}

		//------------Allocator Functions end------------------------//

			
			//helping funcs
			
			// İki iterator arasındaki mesafeyi ileri yönde hesaplar
			size_type distance_forward(iterator first, iterator end)
			{
				size_type dis = 0;
				while(1)
				{
					dis++;
					first++;
					if (first == end)
						break;

				}
				return dis;
			}

			// İki iterator arasındaki mesafeyi geri yönde hesaplar
			size_type distance_back(iterator first, iterator end)
			{
				size_type dis = 0;
				while(1)
				{
					dis++;
					first--;
					if (first == end)
						break;
				}
				return dis;
			}

			// Yeni bir kapasite hesaplamak için kullanılır
			size_type find_new_capacity(size_type n)
            {
                if (this->_capacity == 0)
                    return (n);
                if (this->_capacity < n + this->_size)
                    return (this->_capacity*2);
                return this->_capacity;
            }
			
			//  İki iterator arasındaki eleman sayısını hesaplar
            size_type find_size_by_two_position(iterator pos_start, iterator pos_end)
            {
                size_type newSize = 0;
                while(pos_start != pos_end)
                {
                    newSize++;
                    pos_start++;
                }
                return this->_size - newSize;
            }

			//memory functions
          
		  	// kapasite attırmak için kullanılır verilen yeni kapasite değeri ile
			void	_reAlloc(size_type newCapacity)
			{
				value_type	*newBlock;
				if (newCapacity < this->_capacity)
					return ;
				newBlock = this->_allocator.allocate(newCapacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.construct(&newBlock[i], this->_data[i]);
				this->_allocator.deallocate(this->_data, this->_capacity);
				this->_data = newBlock;
				this->_capacity = newCapacity;
			}

			// smart_reallocu anlatırken notion'u açman iyi olabilir
			void	_smart_reAlloc(size_type newCapacity)
			{
				if (newCapacity <= this->_capacity)
					return ;
				if (this->_size == 0)
                {
					this->_reAlloc(1);
                }
				else if(newCapacity > (this->_size * 2))
					this->_reAlloc(newCapacity);
				else
					this->_reAlloc(this->_size * 2);
			}

			// : Belirtilen indekse belirtilen sayıda boş alan açar
			void _open_space(size_type n, size_type index_to_insert)
			{
			    this->_smart_reAlloc(this->_size + n);

			    for (size_type i = this->_size + n - 1; i >= index_to_insert; i--)
				{
			        this->_allocator.construct(&this->_data[i], this->_data[i - n]);
					if (i == 0)
						break;
				}

			    this->_size += n;
			}

			// Vectorün kapasitesini yeniden ayarlamak için kullanılır
			void reallocateMemory(size_type newCapacity)
			{
			    pointer newData = this->_allocator.allocate(newCapacity);

			    for (size_type i = 0; i < _size; i++)
			    {
			        this->_allocator.construct(&newData[i], std::move(this->_data[i]));
			        this->_allocator.destroy(&this->_data[i]);
			    }

			    this->_allocator.deallocate(this->_data, this->_capacity);
			    this->_data = newData;
			    this->_capacity = newCapacity;
			}

			// Belirtilen indeksin vector sınırları içinde olup olmadığını kontrol eder
			void checkIndex(size_type pos)
			{
				if (pos >= this->_size)
					throw OutOfBoundsException(pos);
			}

			// exceptionlar için 
			class OutOfBoundsException : public std::exception
			{
				size_t _pos;

				public:
					OutOfBoundsException(int pos): _pos(pos){}
					virtual const char* what() const throw()
					{
						return ("out of index\n");
					}
 			};

    };
	/*
	Non-member fonskiyonlar overloads tanımlamaları:
	*/

	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}

	template <class T, class Alloc>
	bool operator == (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator != (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator < (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator <= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ((lhs < rhs) || (lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator > (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs == rhs)
			return (false);
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	bool operator >= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ((lhs > rhs) || (lhs == rhs));
	}
}

// for test
void print_my_vector(ft::vector<int> v);
void print_orj_vector(std::vector<int> v);

void testBegin();
void testEnd();
void testRbegin();
void testRend();
void testSize();
void testMaxSize();
void testResize();
void testCapacity();
void testEmpty();
void testReserve();
void testBoxBrackets();
void testAt();
void testFront();
void testBack();
void testAssign();
void testPushBack();
void testPopBack();
void testInsert();
void testErase();
void testSwap();
void testClear();
void testGetAllocator();

#endif