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
		/**
		 * @brief Default constructor
		 * Hiçbir öğe içermeyen boş bir container oluşturur.
		 * @param alloc 
		 */
		explicit vector(const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _start(0), _end(0), _end_capacity(0) {}
		/**
		 * @brief Constructor'ı doldur.
		 * n öğeli bir kap oluşturur. Her öğe val'in bir kopyasıdır (örn: 3n 4 -> 3, 3, 3, 3).
		 * @param n 
		 * @param val 
		 * @param alloc 
		 */
		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
			: _alloc(alloc)
		{
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_end_capacity = this->_start + n;
			while (n--)
				this->_alloc.construct(this->_end++);
		}
		/**
		 * @brief Range constructor
		 * belirtilen [first, last) aralığındaki her elemanın, aynı sırada kendi karşılık gelen elemanından oluşan bir konteyner oluşturur.
		 * @tparam InputIterator 
		 * @param first 
		 * @param last 
		 * @param alloc 
		 */
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			: _alloc(alloc)
		{
			size_type n = ft::difference(first, last);
			this->_start = this->_alloc.allocate(n);
			this->_end_capacity = this->_start + n;
			this->_end = this->_start;
			while (n--)
				this->_alloc.construct(this->_end++, *first++);
		}
		/**
		 * @brief Copy constructor
		 * x'in her bir öğesinin kopyası ile aynı sırayla dolu bir konteynır oluşturur.
		 * @param x 
		 */
		vector(const vector& x) : _alloc(x._alloc)
		{
			size_type n = x.size();
			this->_start = this->_alloc.allocate(n);
			this->_end_capacity = this->_start + n;
			this->_end = this->_start;
			pointer x_start = x._start;
			while (n--)
				this->_alloc.construct(this->_end++, *x_start++);
		}
		/**
		 * @brief Destructor
		 *  Tüm konteyner elemanlarını yok eder ve vektör tarafından ayrılmış depolama kapasitesini kullanarak tüm depolama alanını geri alır.
		 */
		~vector()
		{
			this->clear(); // clear metodu aşağıda açıklamasına bakabiliriz
			this->_alloc.deallocate(this->_start, this->capacity());
		}
		/**
		 * @brief Assignment operator cons
		 * mevcut içeriğini değiştirerek konteynırın yeni içeriğini atayarak ve boyutunu buna göre değiştirerek kullanır.
		 * @param x Aynı tipte vektör
		 * @return vector& 
		 */
		vector& operator=(const vector& x)
		{
			if (*this == x)
				return *this;
			this->clear();
			this->_alloc.deallocate(this->_start, this->capacity());
			size_type n = x.size();
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_end_capacity = this->_start + n;
			pointer x_start = x._start;
			while (n--)
				this->_alloc.construct(this->_end++, *x_start++);
			return *this;
		}

		/*  -- Iterators Area -- */
		/* Const_iterator ve iterator arasındaki fark birinde geri dönüş değerini değiştirebilirken
		diğerinde vektörün elemanlarını değiştiremezsin.*/
		/**
		 * @brief Vektörün başlangıç iteratörünü döndürür
		 * Vektörün ilk elemanını gösteren bir iterator geri döndürür.
		 * 
		 * @return iterator & const_iterator
		 */
		iterator begin() { return iterator(this->_start); }
		const_iterator begin() const { return const_iterator(this->_start); }
		/**
		 * @brief Vektörün sonunu döndürür
		 * vektördeki son elemanın hemen sonrasına denk gelen, teorik bir elemanı işaret eden bir iterator döndürür.
		 * @return iterator & const_iterator
		 */
		iterator end() { return iterator(this->_end); }
		const_iterator end() const { return const_iterator(this->_end); }
		/**
		 * @brief Ters başlangıca yönelik bir ters iterator döndürür
		 * Bu, vektördeki son elemanı işaret eden bir ters iterator döndürür. (baştan ilk elemana doğru gider)
		 * @return reverse_iterator & const_reverse_iterator
		 */
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		/**
		 * @brief rbegin'in tam tersini döndürür
		 * Baştan başlayıp sonra doğru giden reverse iterator döndürür
		 * @return reverse_iterator & const_reverse_iterator
		 */
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
		

		/*  -- Capacity Area -- */
		/**
		 * @brief Boyut döndürme
		 * Vektördeki öğelerin sayısını döndürür.
		 * @return size_type 
		 */
		size_type size() const { return size_type(this->end() - this->begin()); }
		/**
		 * @brief Ayrılmış depolama kapasitesinin boyutunu döndürür
		 * mevcut vektör için ayrılan depolama alanının boyutunu, elemanlar olarak ifade edilen terimlerle döndürür.
		 * @return size_type 
		 */
		size_type capacity() const { return size_type(this->_end_capacity - this->_start); }
		/**
		 * @brief vector sınıfının kullanabileceği en fazla bellek boyutunu döndürür. 
		 * Ancak, bu değer bazen size_t türünün sınırlarını aşabilir. 
		 * Bu nedenle, max_size() fonksiyonu, PTRDIFF_MAX sabitinden daha büyükse, sadece PTRDIFF_MAX'e kadar olan bir değer döndürür.
		 * PTRDIFF_MAX, bir işaretli tam sayının alabileceği en büyük pozitif değerdir. 
		 * * -> Bu, vektörün kullanabileceği maksimum bellek boyutunu sınırlar ve taşma hatalarını önler.
		 * @return size_type 
		 */
		size_type max_size() const
		{ return (this->_alloc.max_size() > PTRDIFF_MAX ? PTRDIFF_MAX : this->_alloc.max_size()); }
		/**
		 * @brief Boyu değiştir
		 * Bu fonksiyon, belirtilen n sayısı kadar eleman içerecek şekilde, container'ın boyutunu yeniden ayarlar.
		 * @param n Yeni konteyner boyutu, öğe sayısı olarak ifade edilir.
		 * @param val Eğer n, mevcut konteyner boyutundan büyükse, eklenen elemanların içeriği kopyalanan nesnedir.
		 */
		void resize(size_type n, value_type val = value_type())
		{
			if (n > this->max_size())
				throw std::out_of_range("ft::vector")
			if (n < this->size())
				this->erase(this->begin() + n, this->end());
			else
				this->insert(this->end(), n - this->size(), val);
		}
		/**
		 * @brief Vektörün boş olup olmadığını test eder
		 * Vektörün boş olup olmadığını döndürür. (true false)
		 * @return true 
		 * @return false 
		 */
		bool empty() const { return this->begin() == this->end(); }
		/**
		 * @brief Kapasite değişikliği isteği
		 * Vektörün kapasitesinin en azından n elemanı içerecek kadar olmasını talep eder.
		 * @param n Vektör için minimum kapasite
		 */
		/* vektörün kapasitesini artırmak veya azaltmak için kullanılır. 
		   vektörün en azından n elemanı barındırabilecek kapasiteye sahip olmasını isteyerek çağrılır.
		   Eğer vektörün kapasitesi zaten n'den büyükse, hiçbir şey yapılmadan fonksiyon sonlandırılır.

		   Eğer vektörün kapasitesi n'den küçükse, mevcut elemanların bellekteki yeri tutulur ve daha büyük bir bellek alanı ayrılır.
		   Daha sonra, önceki bellek alanındaki elemanlar yeni bellek alanına kopyalanır
		   ve önceki bellek alanı boşaltılır. Son olarak, önceki bellek alanı serbest bırakılır.
		
		   Anlaması zor olduğunda notion'daki örnekten ilerlemek mantıklı olabilir
		*/
		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw std::out_of_range("ft::vector");
			if (this->capacity() >= n)
				return;
			
			// init area
			pointer prev_start = this->_start;
			pointer prev_end = this->_end;
			size_type prev_capacity = this->capacity();

			// allocate and other init
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_end_capacity = this->_start + n;

			// bakılacak
			for (pointer it = prev_start; it != prev_end; it++)
				this->_alloc.construct(this->_end++, *it);
			for (pointer it = prev_start; it != prev_end; it++)
				this->_alloc.destroy(it);
			this->_alloc.deallocate(prev_start, prev_capacity);
		}


		/* -- Element Access Area -- */
		/**
		 * @brief Elemana ulaşmak için
		 * Elemanın referansını geri döndürür
		 * @param n erişilecek index değeri
		 * @return reference & const_reference
		 */
		reference operator[](size_type n) { return *(this->begin() + n); }
		const_reference operator[](size_type n) const { return *(this->begin() + n); }
		/**
		 * @brief Elemana ulaşmak için
		 * Vektördeki n pozisyonundaki elemana referans döndürür. 
		 * Fonksiyon, n'in geçerli öğelerin sınırları içinde olup olmadığını otomatik olarak kontrol eder 
		 * ve geçerli değilse bir out_of_range istisnası fırlatır.
		 * @param n erişilecek index değeri
		 * @return reference & const_reference
		 */
		reference at(size_type n)
		{
			if (n >= size())
				throw std::out_of_range("ft::vector");
			return (*this)[n];
		}
		const_reference at(size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("ft::vector");
			return (*this)[n];
		}
		/**
		 * @brief İlk elemana ulaşmak için
		 * İlk elemanın referansını geri döndürür
		 * @return reference & const_reference
		 */
		reference front() { return *begin(); }
		const_reference front() const { return *begin(); }
		/**
		 * @brief Son elemana ulaşmak için
		 * Son elemanın referansını geri döndürür
		 * @return reference & const_reference
		 */
		reference back() { return *(end() - 1); } // - 1 deme sebebimiz end en sondaki elemanın bir sonrakini gösterir yani (başlangıcı)
		const_reference back() const { return *(end() - 1); }
		

		/* -- Modifiers -- */
		/* 
		Assign metodu, bir container'ın mevcut içeriğini tamamen siler ve yerine yeni bir içerik yerleştirir. 
		Aşağıda farklı kullanımlarına örnekler verilmiştir:
		range assign: Belirtilen başka bir range içeriğini mevcut container'a kopyalar.
		fill assign: Container'ın tüm elemanlarını aynı bir değere eşitler.
		initializer list assign: Değişken sayıda argüman alarak container'a değerler ata
		
		Daha detaylı incelemek için notion vector sayfası ziyaret edilmeli.
		*/
		
		/**
		 * @brief İçeriği temizle
		 * Bu fonksiyon, vektörden tüm elemanları (vektörün bellek alanındaki kapasitesini) kaldırır ve vektörü boşaltır. Vektörün boyutu 0 olur.
		 */
		void clear()
		{
			while (this->_start != this->_end)
				this->_alloc.destroy(--this->_end);
		}
	};
}

#endif