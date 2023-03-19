#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
    /*
    -------------------------------------------------------------------------------
    -    Bu dosya pair isimli bir template yapısıdır.
    -    Bu yapının iki adet parametresi vardır: birinci ve ikinci elemanların türü.
    -    pair yapısı, iki elemanın bir arada tutulmasında kullanılır.
    -    pair yapısı, elemanların türlerine göre iki adet özelliği belirler:
    -    first: pair yapısının birinci elemanı.
    -    second: pair yapısının ikinci elemanı.
    -    Bu özelliklere erişmek için . (nokta) operatörü kullanılır. Örneğin, pair yapısının first elemanına erişmek için "pair.first" kullanılır.
    -    Ayrıca, pair yapısına ait bazı özel fonksiyonlar da bulunmaktadır. Bunlar arasında örneğin, pair yapısının iki elemanını da eşleştiren make_pair() fonksiyonu yer alır.
    -------------------------------------------------------------------------------
    */
    template <typename T1, typename T2>
    class pair
    {
        public:
            T1 first;
            T2 second;

            pair() : first(), second() {}; //default constructor
			pair(const T1& a, const T2& b) : first(a), second(b) {}; // define constructor
			pair(const pair<T1, T2>& copy) : first(copy.first), second(copy.second) {}; // copy constructor
		
			template <typename U, typename V>
			pair(const pair<U, V>& copy) : first(copy.first), second(copy.second) {};

			~pair() {}; // destructor
			pair& operator=(const pair& assign)
			{
				if (this != &assign)
				{
					first = assign.first;
					second = assign.second;
				}
				return (*this);
			} 
    };

    /**
     * @brief Bu fonksiyon, verilen iki argümanı bir çift (pair) nesnesi olarak birleştirir ve oluşturulan çifti geri döndürür.
     * 
     * @tparam T1 
     * @tparam T2 
     * @param x 
     * @param y 
     * @return pair<T1,T2> 
     */
    template <class T1, class T2>
    pair<T1,T2> make_pair(T1 x, T2 y)
    {
    	return pair<T1,T2>(x,y);
    }
}

#endif