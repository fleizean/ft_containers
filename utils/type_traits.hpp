#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * ---------------------- ft::ENABLE_IF ------------------------ *
    * Bu özellik, bir şartın doğru olması durumunda bir türün 
    * kullanılabilir hale gelmesini sağlar.
    */
   
    /**
    *   Typedef an int into type only if B is true.
    */
    template <bool Cond, class T = void>
    struct enable_if
    {
    };
    
    // Partial specialization for true
    template <class T>
    struct enable_if<true, T>
    {
       typedef T type;
    };
    /**
    * ------------------------------------------------------------- *
    * --------------------- ft::IS_INTEGRAL ----------------------- *
    * Bu özellik, bir türün tam sayı türü olup olmadığını belirler. 
    * Eğer belirtilen tür bir tam sayı türü ise is_integral özelliği 
    * doğru (true) değerini döndürür; ksi takdirde yanlış (false) 
    * değerini döndürür.
    */

    template <typename T>
    struct is_integral { static const bool value = false; };

    template <>
    struct is_integral<bool> { static const bool value = true; };

    template <>
    struct is_integral<char> { static const bool value = true; };
   
    template <>
    struct is_integral<short> { static const bool value = true; };
   
    template <>
    struct is_integral<int> { static const bool value = true; };
   
    template <>
    struct is_integral<long> { static const bool value = true; };
   
    template <>
    struct is_integral<long long> { static const bool value = true; };
   
    template <>
    struct is_integral<unsigned char> { static const bool value = true; };
   
    template <>
    struct is_integral<unsigned short> { static const bool value = true; };
   
    template <>
    struct is_integral<unsigned int> { static const bool value = true; };
   
    template <>
    struct is_integral<unsigned long> { static const bool value = true; };
   
    template <>
    struct is_integral<unsigned long long> { static const bool value = true; };

    /* * ------------------------------------------------------------- * */


    /**
    *   Use a boolean to typedef either type 1 or type 2.
    */
    template <bool isConst, typename isFalse, typename isTrue>
    struct chooseConst {};

    /**
    *   Typedef: pointer, ref...
    */
    template <typename isFalse, typename isTrue>
    struct chooseConst<false, isFalse, isTrue>
    {
        typedef isFalse type;
    };

    /**
    *   Typedef: const pointer, const ref...
    */
    template <typename isFalse, typename isTrue>
    struct chooseConst<true, isFalse, isTrue>
    {
        typedef isTrue type;
    };
}

#endif