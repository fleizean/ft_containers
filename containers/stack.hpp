/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleizean <fleizean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:30 by llefranc          #+#    #+#             */
/*   Updated: 2023/03/18 14:23:46 by fleizean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    /*
    * ------------------------------------------------------------- *
    * -------------------------- STACK ---------------------------- *
    *
    * Coplien form:
    * (constructor):        Stack yapısını oluşturur
    * (destructor):         Stack yapısını yıkıcı
    * operator=:            İçeriği atama
    *
    * Üye fonksiyonlar:
    * empty:                Container'ın boş olup olmadığını test eder
    * size:                 Boyutu döndürür
    * top:                  Bir sonraki elemana erişir
    * push:                 Eleman ekler
    * pop:                  En üstteki elemanı kaldırır
    *
    * Üye olmayan fonksiyon yüklemeleri:
    * relational operators: Stack için karşılaştırma operatörleri
    * ------------------------------------------------------------- *
    */

    /**
    *   @param T            Container tipi
    *   @param Container    T elemanlarını depolamak için dahili olarak kullanılan bir Container nesnesi.
    */
    template <class T, class Container = ft::vector<T> >
    class stack
    {
            /* ------------------------------------------------------------- */
            /* -------------------------- ALIASES -------------------------- */

        public:

            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;
            
            
            /* ------------------------------------------------------------- */
            /* ------------------------- ATTRIBUTES ------------------------ */

        private:

            container_type  _ctnr;
            
            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */
            
        public:
            
            /**
            * Yığın (stack) veri yapısını oluşturan bir adaptör nesnesi oluşturur.
            * Bu nesne, yapıcıya verilen ctnr argümanının bir kopyasını veri olarak içeren bir konteyner nesnesi kullanır.
            *   @param ctnr
            */
            explicit stack (const container_type& ctnr = container_type()) :
                    _ctnr(ctnr) {}
            
            /**
            *   Copy constructor
            *   @param x
            */
            stack(const stack& x) :
                    _ctnr(x._ctnr) {}
                
            /*
            *   Destructor
            */
            ~stack() {}
        
            /**
             * @brief assignment
             * 
             * @param x 
             * @return stack& 
             */
            stack& operator=(const stack& x)
            {
                stack tmp(x);
                swap(_ctnr, tmp._ctnr);
                return *this;
            }
            

            /* ------------------------------------------------------------- */
            /* ----------------- MEMBER FUNCTION OVERLOADS ----------------- */

            /**
            *   
            *   Konteynırın boş olup olmadığını döndürür. (true false)
            */
            bool empty() const                  { return _ctnr.empty(); }
            
            /**
            *   
            *   Konteynırın mevcut size'ını döndürür
            */
            size_type size() const              { return _ctnr.size(); }
            
            /**
            *   İçindeki verileri tutmak için kullandığı temel konteynır nesnesinin back üye fonksiyonunu çağırır, 
            *   bu fonksiyon, yığının en üstündeki öğeye bir referans döndürür. 
            *   Yığınlar son eklenen öğe ile çıkarma işlemi yapan veri yapıları olduğu için en üstteki öğe son eklenendir.
            * 
            *   Kısacası stack'deki LIFO yapısı (Last in First Out) yüzünden en son ekleneni geri döndürür.
            */
            value_type& top()                   { return _ctnr.back(); }
            const value_type& top() const       { return _ctnr.back(); }
            
            /**
            *   Stack'e yeni bir eleman eklemeye yarar. Bu eleman stack'in üstüne eklenir
            *   ve artık stack'in en üstündeki eleman haline gelir.
            *
            *   @param val eklenecek element
            */
            void push (const value_type& val)   { _ctnr.push_back(val); }
            
            /**
            *   Yığının en üstündeki elemanı yığından çıkarır.
            *   Yani yığındaki en son eklenen elemanı yığından çıkarır.
            */
            void pop()                          { _ctnr.pop_back(); }


            /* ------------------------------------------------------------- */
            /* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */
            
            /**
            *   Friend teriminin burada kullanılmasının sebebi lhs ve rhs terimlerinin private
            *   değişken olan _ctnr(containera) erişim yapması için. Eğer kaldırırsanız hatayı
            *   görntüleyebilirsiniz.
            */

            friend bool operator==(const stack& lhs, const stack& rhs)  { return lhs._ctnr == rhs._ctnr; }
            friend bool operator!=(const stack& lhs, const stack& rhs)  { return lhs._ctnr != rhs._ctnr; }
            friend bool operator<(const stack& lhs, const stack& rhs)   { return lhs._ctnr < rhs._ctnr; }
            friend bool operator<=(const stack& lhs, const stack& rhs)  { return lhs._ctnr <= rhs._ctnr; }
            friend bool operator>(const stack& lhs, const stack& rhs)   { return lhs._ctnr > rhs._ctnr; }
            friend bool operator>=(const stack& lhs, const stack& rhs)  { return lhs._ctnr >= rhs._ctnr; }


            /* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */
            /* ------------------------------------------------------------- */

        private:
            template <typename U>
            void swap(U& a, U& b)
            {
                U tmp(a);
                a = b;
                b = tmp;
            }

    };
        
}

#endif