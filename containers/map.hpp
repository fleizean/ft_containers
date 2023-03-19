/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:38:30 by llefranc          #+#    #+#             */
/*   Updated: 2023/03/17 01:26:18 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

#include "../utils/algorithm.hpp"
#include "../utils/pair.hpp"

#include "../iterators/map_iterator.hpp"
#include "../iterators/rev_map_iterator.hpp"

namespace ft
{
	/**
	* ------------------------------------------------------------- *
	* ------------------------- MAP --------------------------- *
	*
	* - Cannonical Form:           
	* (constructor):    Construct map
	* (destructor):     Map destructor
	* operator=:        Assign map
	*
	* - Iterators:
	* begin:            iteratörün başlangıç noktasını işaret eden işaretçi döndürür.
	* end:              iteratörün bitiş noktasını işaret eden işaretçi döndürür.
	* rbegin:           container'ın son elemanından başlayarak ilk elemanına doğru bir iteratör döndürür
	* rend:             container'ın ilk elemanından başlayarak son elemanına doğru bir iteratör döndürür.
	*
	* - Capacity:
	* empty:            Map'in boş olup olmadığını kontrol etmeye yarar, değer olarak true false döndürür.
	* size:             Map'in güncel size'ını döndürür
	* max_size:         Map'in tutabileceği maksimum size değerini döndürür.
	*
	* - Element access:
	* operator[]:       Bir elemena ulaşmak için kullanılır. örn: a[1]
	*
	* - Modifiers:
	* insert:           Eleman eklemek için kullanılır 3 farklı versiyonu var (function overloading)
	* erase:            Eleman silmek için kullanılır 3 farklı versiyonu var (function overloading)
	* swap:             Dışarıdan gelen eleman ile o anki mapin elemanlarını swap etmeye yarayan fonksiyon.
	* clear:            Map'teki tüm elemanları siler
	*
	* - Observers:
	* key_comp:         key_comp geri döndüren getter
	* value_comp:       value_comp geri döndüren getter
	*
	* - Operations:
	* find:             map konteynerinde bir anahtarın var olup olmadığını kontrol etmek için kullanılır.
	* count:            map konteynerinde belirtilen bir anahtara sahip kaç adet öğe olduğunu sayar. eğer hiç bulamazsa 0 döndürür.
	* lower_bound:      Return iterator to lower bound
	* upper_bound:      Return iterator to upper bound
	* equal_range       Get range of equal elements
	* ------------------------------------------------------------- *
	*/

	/**
	*   @param key     	Map'in key valuesi
	*   @param T        Map tipini belirlemek için kullanılır
	*   @param Compare  Map'teki düğümleri sıralamak için kullanılacak olan bir karşılaştırma işlevi.
	*	Varsayılan olarak, std::less<Key> kullanılır, yani key değerlerinin küçükten büyüğe doğru sıralanması sağlanır. 
	*	Ancak, kullanıcı özel bir sıralama düzeni belirlemek istiyorsa, 
	*	Compare parametresine kendine özgü bir karşılaştırma işlevi nesnesi sağlayabilir. 
	*   @param Alloc    Allocator sınıfı için isim tanımlaması, Alloc nesnesi oluşturduk diyebiliriz.
	*/
	template < class Key, class T, class Compare = std::less<Key>, 
			class Alloc = std::allocator<ft::pair<const Key, T> >
	> class map
	{
		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

		private:        

			struct Node
			{
				ft::pair<const Key, T>  content;
				Node*                   parent; // childin babası
				Node*                   left; // o anki node'un solu
				Node*                   right; // o anki node'un sağı
			};


		/* ------------------------------------------------------------- */
		/* -------------------------- ALIASES -------------------------- */
			
		public:

			typedef Key                                             			key_type;
			typedef Compare                                         			key_compare;
			typedef Alloc                                           			allocator_type;
			typedef T                                               			mapped_type;
						
			typedef ft::pair<const key_type, mapped_type>           			value_type;
			typedef long int                                        			difference_type; // aralık mesafesi
			typedef size_t                                          			size_type; // map size dönerken bununla dönüyoruz
			
			typedef T&                                              			reference;
			typedef const T&                                        			const_reference;
			typedef T*                                              			pointer;
			typedef const T*                                        			const_pointer;
			
			typedef typename ft::map_iterator<Key, T, Compare, Node, false>     iterator;
			typedef typename ft::map_iterator<Key, T, Compare, Node, true>      const_iterator;

			typedef typename ft::rev_map_iterator<Key, T, Compare, Node, false> reverse_iterator;
			typedef typename ft::rev_map_iterator<Key, T, Compare, Node, true>  const_reverse_iterator;


		/* ------------------------------------------------------------- */
		/* ---------------------- NESTED CLASSES ----------------------- */

		/**
		*   map sınıfında saklanan öğelerin sıralanması için kullanılan karşılaştırma işlevini tutar. 
		*	
		*/
			class value_compare
			{
				friend class map;
				
				protected:
				
					key_compare comp;
					
					value_compare(Compare c) : comp(c) {}

				public:
				
					typedef bool        result_type;
					typedef value_type  first_argument_type;
					typedef value_type  second_argument_type;

					bool operator()(const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first); // küçük mü diye kontrol eder x < y ona göre true false döner
					}
			};
			

		/* ------------------------------------------------------------- */
		/* ------------------------ ATTRIBUTES ------------------------- */
			
		private:

			Node*                   _root;          // Ağaçtaki ilk elemanı işaret eden bir işaretçi.
			Node*                   _lastElem;      // Ağaçtaki son elemanı işaret eden bir işaretçi.
			size_type               _size;          // Number of T values inside the map
			allocator_type          _allocPair;     // MAX_SIZE hesaplama için Allocator nesnesi kullanmamız lazım
			key_compare             _comp;          // Key value'yu karşılaştırmak için nesne
			std::allocator<Node>    _allocNode;    	// Node için allocator nesnesi
			
			
		/* ---------------------------------------------------------------- */
		/* ------------------------ CANNONICAL FORM ----------------------- */
			
		public:
			
			
			/**
			*   Default constructor, size'ı 0 olan yeni bir map oluşturur.
			*
			*   @param comp
			*   @param alloc
			*/
			explicit map(const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type()) :
				_size(0), _allocPair(alloc), _comp(comp)
			{
				_lastElem = createNode(ft::pair<const key_type, mapped_type>());
				_root = _lastElem;
				_lastElem->left = _lastElem;
				_lastElem->right = _lastElem;
			}


			/**
			*   Bir başlangıç ve bir bitiş iterator'ı arasındaki eleman sayısı kadar eleman içeren bir map oluşturur
			*	ve bu elemanların değerlerini oluşturulan yeni elemanlara kopyalar.
			*	Yani başka bir deyişle, bir aralıktan (range) başlayarak bir map oluşturur.
			*	
			*   @param first    Aralık için başlangıç konumu alan iterator
			*   @param last     Aralık için son konumu alan iterator (yani first'den başlayıp last'a kadar )
			*   @param comp     Sıralama için kullanılan şablon parametresidir.
			*   @param alloc    Allocate için kullanılan şablon parametresidir.
			*/
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(), 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
				_size(0), _allocPair(alloc), _comp(comp)
			{
				_lastElem = createNode(ft::pair<const key_type, mapped_type>());
				_root = _lastElem;
				_lastElem->left = _lastElem;
				_lastElem->right = _lastElem;
				
				for (; first != last; ++first)
					insert(*first);
			}

			/**
			*   Copy constructor, dışarıdan alınan mapin değerlerleri ile yeni bir map oluşturur
			*   
			*   @param x        Dışarıdan alınan map
			*/
			map(const map& x) :
				_size(0), _allocPair(x._allocPair), _comp(x._comp), _allocNode(x._allocNode)
			{
				_lastElem = createNode(ft::pair<const key_type, mapped_type>());
				_root = _lastElem;
				_lastElem->left = _lastElem;
				_lastElem->right = _lastElem;

				for (const_iterator it = x.begin(); it != x.end(); ++it)
					insert(*it);
			}

			/**
			*   Yıkıcı fonksiyon, map'in tüm elemanlarını ve düğümlerini
			*   (son eleman düğümü dahil) yok eder ve bellekten geri verir.
			*/
			~map()
			{
				clear();
				deallocateNode(_lastElem); // son elemanın temizleneceği yer
			}

			/**
			*  Assignment constructor
			*   @param x
			*/
			map& operator=(const map& x)
			{
				map tmp(x);
				this->swap(tmp);
				
				return *this;
			}

			/* ------------------------------------------------------------- */
			/* ------------------------- ITERATORS ------------------------- */

			/**
			*   @return     Map'teki ilk düğümü yani başlangıçı gösteren iterator döndürür
			*/
			iterator begin()                        { return iterator(_lastElem->right, _lastElem, _comp); }
			const_iterator begin() const            { return const_iterator(_lastElem->right, _lastElem, _comp); }

			/**
			*   @return     Son map öğesinin sonrasını işaret eden, sahte bir düğüm üzerinde duran bir iterator döndürür. 
			*/
			iterator end()                          { return iterator(_lastElem, _lastElem, _comp); }
			const_iterator end() const              { return const_iterator(_lastElem, _lastElem, _comp); }

			/**
			*   @return     Bir map'in son elemanına (maksimum değer) işaret eden reverse_iterator.
			*/
			reverse_iterator rbegin()               { return reverse_iterator(_lastElem->left, _lastElem, _comp); }
			const_reverse_iterator rbegin() const   { return const_reverse_iterator(_lastElem->left, _lastElem, _comp); }

			/**
			*   @return     Bir map'in ilk elemanının öncesine, yani bir sahte düğümde işaret eden reverse_iterator.
			*/
			reverse_iterator rend()                 { return reverse_iterator(_lastElem, _lastElem, _comp); }
			const_reverse_iterator rend() const     { return const_reverse_iterator(_lastElem, _lastElem, _comp); }


			/* ------------------------------------------------------------- */
			/* -------------------------- CAPACITY ------------------------- */

			/**
			*   @return     Map'in boş olup olmadığını döndürür, döndürdüğü değer true false'dur.
			*/
			bool empty() const              { return _size == 0; }

			/**
			*   @return     Map'in size'ını döndürür
			*/
			size_type size() const          { return _size; }
			
			/**
			*   @return     Map'in alabileceği max size'ı döndürür
			*/
			size_type       max_size() const
			{
				return _allocPair.max_size();
			}


			/* ------------------------------------------------------------- */
			/* ---------------------- ELEMENTS ACCESS ---------------------- */ 
			
			/**
			*   Belirtilen anahtarın ağaçta olup olmadığını arar ve yoksa onu oluşturur.
			*   Sonra değişiklik yapmaya izin veren bir referans döndürür.
			*
			*   @param k   
			*   @return  
			*/
			mapped_type& operator[](const key_type& k)
			{
				Node* tmp = searchNode(_root, k);

				if (tmp)
					return tmp->content.second;
				
				value_type val = make_pair<key_type, mapped_type>(k, mapped_type());
				_size++;
				return insertNode(_root, val)->content.second;
			}
			

			/* ------------------------------------------------------------- */
			/* ------------------------- MODIFIERS ------------------------- */

			/**
			*   Öğeyi harita içinde bulunmadığı durumda ekler.
			*   Öğe eklendiğinde, boyut bir artırılır.
			*
			*   @param val  Eklenecek value
			*   @return     Eğer belirtilen anahtar map'ta bulunmuyorsa,
			*               yeni eklenen elemana işaret eden bir iterator ile birlikte bir çift döndürür.
			*               Aksi takdirde, zaten mevcut olan anahtara işaret eden bir iterator ile birlikte bir çift döndürür 
			*               ve boolean bir değer döndürür: eleman eklendiyse true, aksi halde false döner.
			*/
			ft::pair<iterator,bool> insert (const value_type& val)
			{
				// ağaçta belirtilen bir anahtarın zaten mevcut olup olmadığını kontrol eder
				// anahtar zaten mevcutsa, anahtarı içeren bir iterator döndürür.
				Node* elemIsPresent = searchNode(_root, val.first);
				if (elemIsPresent)
					return ft::pair<iterator, bool>(iterator(elemIsPresent, _lastElem, _comp), false);

				++_size;
				return ft::pair<iterator, bool>(iterator(insertNode(_root, val), _lastElem, _comp), true);
			}
			
			/**
			*  	Belli bir pozisyon veriyorsun o alana o elemanı eklemeye yarıyor.
			*   @param position             
			*   @param val     
			*   @return        
			*                   
			*/
			iterator insert (iterator position, const value_type& val)
			{   
				// eğer position anahtarı val anahtarından büyükse, position'ı azaltmamız 
				// ve val'den ağaçta en yakın daha büyük bir anahtarı bulana kadar devam etmemiz gerektiğini ifade eder.
				if (position->first > val.first)
				{
					iterator prev(position);
					--prev;
					while (prev != end() && prev->first >= val.first)
					{
						--position;
						--prev;
					}
				}

				else if (position->first < val.first)
				{
					iterator next(position);
					++next;
					while (next != end() && next->first <= val.first)
					{
						++position;
						++next;
					}
				}

				// Eğer value varsa ve o alan boş değilse
				if (position != end() && val.first == position->first)
					return position;

				++_size;
				return iterator(insertNode(position.getNode(), val), _lastElem, _comp);
			}
			
			/**
			*   Integer olmayan ve aynı anda 2 iterator (first ve last olmak üzere) geldiği durumlarda 
			*	first ve last aralığında eleman eklemeye yarar.
			*   @param first
			*   @param last
			*/  
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				while (first != last)
					insert(*first++);
			}

			/**
			*   Verilen pozisyona göre gidip o pozisyondaki elemanı silmeye yarar
			*
			*/
			void erase (iterator position)
			{
				deleteNode(position.getNode(), position->first);
				--_size;
			}

			/**
			*   Verilen key değerine göreo pozisyonu bulup siler ve ret'e ne kadar sildiyse o kadar değer döndürür
			*
			*   @param k    The key to find in map and to remove.
			*   @return     Number of elements erased. Since you can't have twice the same key in 
			*               map, this is either 0 or 1.
			*/
			size_type erase (const key_type& k)
			{
				size_type ret = deleteNode(_root, k);
				_size -= ret;
				return ret;
			}

			/**
			*   Verilen iterator first ve iterator last aralığındaki bütün elemanları siler
			*
			*   @param first
			*   @param last
			*/
			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					iterator tmp(first);
					++first;
					erase(tmp);
				}
			}

			/**
			*   Bu fonksiyon, şu anki harita nesnesinin içeriğiyle bir haritayı takas eder.
			*
			*   @param x Swap edilecek nesne (dışarıdan gelir)
			*/
			void swap (map& x)
			{
				swap(_root, x._root);
				swap(_lastElem, x._lastElem);
				swap(_size, x._size);
				swap(_comp, x._comp);
				swap(_allocPair, x._allocPair);
				swap(_allocNode, x._allocNode);
			}

			/**
			*   Bütün map konteynırını temizler ve size'ı 0'a eşitler
			*/
			void clear()        { erase(begin(), end()); _size = 0; }


			/* ------------------------------------------------------------- */
			/* ------------------------- OBSERVERS ------------------------- */
			
			/**
			*   @return ilk verilen argüman ikinci argümandan küçükse true döner büyük veya eşitse false döner
			*/
			key_compare key_comp() const        { return _comp; }

			/**
			*   @return ilk verilen argüman ikinci argümandan küçükse true döner büyük veya eşitse false döner
			*/
			value_compare value_comp() const    { return value_compare(_comp); }
			
			
			/* ------------------------------------------------------------- */
			/* ------------------------ OPERATIONS ------------------------- */

			/**
			*   konteynerinde bir anahtarın var olup olmadığını kontrol etmek için kullanılır.
			*
			*   @param k   Aranacak eleman
			*   @return    Verilen anahtar k'yı içeren bir öğe varsa, bu öğenin konumunu temsil eden bir iterator nesnesi döndürülür.
			*	@return    Aksi takdirde, konteynerin sonunu temsil eden bir iterator nesnesi döndürülür.
			*/
			iterator find(const key_type& k)
			{
				Node* tmp = searchNode(_root, k);

				if (tmp)
					return iterator(tmp, _lastElem, _comp);
				
				// Case no match
				return end();
			}
			const_iterator find(const key_type& k) const
			{
				Node* tmp = searchNode(_root, k);

				if (tmp)
					return const_iterator(tmp, _lastElem, _comp);
				
				// Case no match
				return end();
			}

			/**
			*   
			*
			*   @param k   	Verilen key değerine göre o node'u bulur ve orada value değeri varsa true yoksa false döner
			*   @return
			*/
			size_type count (const key_type& k) const
			{
				Node* tmp = searchNode(_root, k);
				
				if (tmp)
					return true;
				return false;
			}

			/**
			*   Verilen key valuesunun varsa kendisini geri döndürür
			*
			*   @param k
			*   @return
			*               
			*/
			iterator lower_bound(const key_type& k)
			{
				iterator it = begin();

				for (; it != end(); ++it)
					if (!_comp(it->first, k))
						break;
				
				return it;  
			}
			const_iterator lower_bound(const key_type& k) const
			{
				const_iterator it = begin();

				for (; it != end(); ++it)
					if (!_comp(it->first, k))
						break;
				
				return it;  
			}

			/**
			*   k'den sonra gelen ilk değeri geri döndürür
			*
			*   @param k
			*   @return
			*               
			*/
			iterator upper_bound(const key_type& k)
			{
				iterator it = begin();

				for (; it != end(); ++it)
					if (_comp(k, it->first))
						break;
				
				return it;  
			}
			const_iterator upper_bound(const key_type& k) const
			{
				const_iterator it = begin();

				for (; it != end(); ++it)
					if (_comp(k, it->first))
						break;
				
				return it;  
			}

			/**
			*   Verilen k değerinin kendisini ve bir sonraki (next) key değerini iterator olarak geri döndürür
			*
			*   @param k
			*   @return
			*/
			pair<iterator,iterator> equal_range(const key_type& k)
			{
				iterator it = upper_bound(k);

				if (it != begin())
				{
					--it;

					if (_comp(it->first, k) || _comp(k, it->first))
						++it;
				}

				iterator next(it);
				if (it != end())
					++next;
				
				return make_pair<iterator, iterator>(it, next);
			}
			pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{
				const_iterator it = upper_bound(k);

				if (it != begin())
				{
					--it;

					if (_comp(it->first, k) || _comp(k, it->first))
						++it;
				}

				const_iterator next(it);
				if (it != end())
					++next;
				
				return make_pair<const_iterator, const_iterator>(it, next);
			}


			/* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */
			/* ------------------------------------------------------------- */
			
		private:

			/**
			*  	a ve b'yi swaplar
			*   @param a
			*   @param b
			*/
			template <typename U>
			void swap(U& a, U& b)
			{
				U tmp = a;
				a = b;
				b = tmp;
			}

			/**
			*   pair oluşturmak için kullanılır
			*   @param x
			*   @param y
			*/
			template <class T1,class T2>
			pair<T1,T2> make_pair(T1 x, T2 y) const
			{
				return pair<T1,T2>(x,y);
			}


			/* ----- PRIVATE MEMBER FUNCTIONS : AVL BINARY SEARCH TREE ----- */
			/* ----------- inserting / deleting inside the tree ------------ */

			/**
			*   Yeni bir düğüm oluşturur ve gelen pairi atar. Sol ve sağ düğüm işaretçileri NULL'dir.
			*
			*   @param pair
			*   @return
			*/
			Node* createNode(const value_type& pair)
			{
				Node* newNode = _allocNode.allocate(1);

				_allocPair.construct(&newNode->content, pair);
				newNode->parent = 0;
				newNode->left = 0;
				newNode->right = 0;

				return newNode;
			}

			/**
			*  	Düğümün içeriğinin yıkıcı metodunu çağırır ve daha sonra düğümün bellek alanını serbest bırakır.
			*
			*   @param del
			*/
			void deallocateNode(Node* del)
			{
				_allocPair.destroy(&del->content);
				_allocNode.deallocate(del, 1);
			}

			/**
			*   Ağacın yüksekliğini bulmaya yarar her bir parent bir height++ diyebiliriz
			*
			*   @param root
			*   @param height
			*   @param return
			*/
			int heightTree(Node *root, int height)
			{
				if (!root || root == _lastElem)
					return height - 1;

				int leftHeight = heightTree(root->left, height + 1);
				int rightHeight = heightTree(root->right, height + 1);

				return leftHeight > rightHeight ? leftHeight : rightHeight;
			}

			/**
			*   Tree'de keyi arar ve keyi bulursa elementi döndürür.
			*	
			*   @param root
			*   @param key
			*   @param return
			*/
			Node* searchNode(Node* root, key_type key) const
			{
				if (!root || root == _lastElem)
					return 0;
				
				if (!_comp(root->content.first, key) && !_comp(key, root->content.first))
					return root;
				
				if (root->content.first > key && root->left && root->left != _lastElem)
					return searchNode(root->left, key);
				else if (root->content.first < key && root->right && root->right != _lastElem)
					return searchNode(root->right, key);

				return 0;
			}

			/**
			*   Ağaçtaki en yüksek key değerine sahip öğeyi arar.
			*
			*   @param root
			*   @param return
			*/
			Node* searchMaxNode(Node *root) const
			{
				if (root->right && root->right != _lastElem)
					return searchMaxNode(root->right);
				return root;
			}

			/**
			*   Ağaçtaki en küçük key değerine sahip öğeyi arar.
			*
			*   @param root
			*   @param return
			*/
			Node* searchMinNode(Node *root) const
			{
				if (root->left && root->left != _lastElem)
					return searchMinNode(root->left);
				return root;
			}

			/**
			*   Ağaca veya belirli bir alt ağaca yeni bir öğe ekleyerek çifti 
			*   ekler ve ardından gerekirse AVL ağacını dengeleyerek.
			*   Öğe zaten mevcutsa, hiçbir şey yapmaz ve NULL değeri döndürür.
			*
			*   @param insertPos    
			*   @param data         
			*   @param return
			*/
			Node* insertNode(Node* insertPos, const value_type& pair)
			{
				if (_root == _lastElem)
				{
					_root = createNode(pair);
					
					_root->left = _lastElem;
					_root->right = _lastElem;
					_lastElem->left = _root;
					_lastElem->right = _root;

					return _root;
				}

				if (insertPos->content.first == pair.first)
					return 0;

				//  fake son düğüm (_lastElem) ulaşana kadar yapılacak tekrarlayan döngü (recursive loop)
				if (insertPos->content.first > pair.first && 
						insertPos->left && insertPos->left != _lastElem)
					return insertNode(insertPos->left, pair);
				else if (insertPos->content.first < pair.first && 
						insertPos->right && insertPos->right != _lastElem)
					return insertNode(insertPos->right, pair);

				// Eğer bu adıma ulaştıysak, yaprak düğüme veya ağacın maksimum / minimum düğümüne ulaştık
				// (her ikisi de _lastElem ile bağlantılıdır): yeni düğümü doğru konumuna yerleştiriyoruz.
				Node *newNode = createNode(pair);

				// Case we reached a left or right leaf
				if (insertPos->content.first > newNode->content.first && !insertPos->left)
					insertPos->left = newNode;
				else if (insertPos->content.first < newNode->content.first && !insertPos->right)
					insertPos->right = newNode;

				// Min veya max düğümüne ulaşıldığında, düğümü min / max ve lastElem arasına ekleyerek işlem yapılır.
				else if (insertPos->left && insertPos->content.first > newNode->content.first)
				{
					newNode->left = _lastElem;
					_lastElem->right = newNode;
					insertPos->left = newNode;
				}
				else if (insertPos->right && insertPos->content.first < newNode->content.first)
				{
					newNode->right = _lastElem;
					_lastElem->left = newNode;
					insertPos->right = newNode;
				}
					
				newNode->parent = insertPos;

				// Yeni düğümden kök düğüme kadar olan ağacı dengelemek (equilibrating) sol height (veya sağ) sağ'dan(veya sol) 2 fazla yüksek olma durumunda
				// dengelemek için bir sağa veya sola kaydırma işlevi
				balanceTheTree(&_root, newNode);

				return newNode;
			}

			/**
			*   Ağaçtan veya belirli bir alt ağaçtan anahtara uyan düğümü siler ve ardından gerektiğinde 
			*   AVL ağacını dengeleyerek (equilibrating). Öğe yoksa, bu fonksiyon hiçbir şey yapmaz.
			*
			*   @param deletePos    
			*   @param key
			*   @param return
			*/
			bool deleteNode(Node* deletePos, key_type key)
			{
				// Balance node ilk elemanı gösterecek
				Node* balanceNode = 0;
				
				// Silinecek düğüm, deletePos düğümünden anahtarı eşleşene kadar aranır
				Node* del = searchNode(deletePos, key);

				// Öğe yoksa, silinecek bir şey yok
				if (!del)
					return false;
				
				/* --------------- KÖK DÜĞÜMÜ SİLME DURUMU --------------- */
				// Silinecek düğüm kök düğüm ise
				if (!del->parent)
				{
					// Kök, ağaçta tek düğümdür ve boş olur
					if (del->left == _lastElem && del->right == _lastElem)
					{
						_root = _lastElem;
						_lastElem->left = _lastElem;
						_lastElem->right = _lastElem;
					}

					// Yalnızca bir childı	 varsa (sol veya sağ), yalnızca kök için ağacı dengelememiz gerekir
					else if (del->left && del->right == _lastElem)
					{
						balanceNode = del->parent;
						_root = del->left;
						del->left->parent = 0;
						
						// Ağaç AVL olduğundan, _root'un yalnızca bir childı varsa, bu childı
						// bir yaprak ve sol ve sağ childı yoktur. Bu nedenle, yeni kökün sol ve sağ tarafından
						// lastElem olması gerekiyor, ancak zaten _it'e bir taraftan bağlı
						// (bu durumda, sol)
						_lastElem->left = del->left;
						del->left->right = _lastElem;
					}
					else if (del->left == _lastElem && del->right)
					{
						balanceNode = del->parent;
						_root = del->right;
						del->right->parent = 0;

						// Üstteki açıklama ile aynı ancak zıt taraftan
						_lastElem->right = del->right;
						del->right->left = _lastElem;
					}
					
					// İki oğlu varsa, anahtarını silinecek düğümün anahtarıyla sol alt ağaçtaki en yüksek anahtarın anahtarını değiştirmemiz gerekir. 
					// Daha sonra, sol alt ağaçtaki bu en yüksek anahtar ile düğümü silmemiz gerekiyor.
					else
					{
						Node* maxNode = searchMaxNode(del->left);
						
						// Kopyalamak için yok etmek ve oluşturmak gerekiyor (sabit değişkenleri kopyalamak için)
						_allocPair.destroy(&del->content);
						_allocPair.construct(&del->content, maxNode->content);
						
						return deleteNode(del->left, maxNode->content.first);
					}
				}


				/* --------------- NODE SİLME DURUMLARI --------------- */
				// Silinecek değer yaprak düğüm ise
				else if ((!del->left || del->left == _lastElem) && (!del->right || del->right == _lastElem))
				{
					balanceNode = del->parent;

					// Min düğümü / max düğümü durumunda, _lastElem'e bağlama farklıdır
					Node* linkToParent = 0;
					if (del->left == _lastElem || del->right == _lastElem)
					{
						linkToParent = _lastElem;
						del->content.first <= del->parent->content.first ?
							_lastElem->right = del->parent : _lastElem->left = del->parent;
					}
						
					del->content.first <= del->parent->content.first ?
						del->parent->left = linkToParent : del->parent->right = linkToParent;
				}
				
				// Sadece bir child'ı varsa (sadece sol child veya sadece sağ child)
				else if ((del->left && del->left != _lastElem) && (!del->right || del->right == _lastElem))
				{
					balanceNode = del->parent;

					del->content.first <= del->parent->content.first ?
							del->parent->left = del->left : del->parent->right = del->left;
					del->left->parent = del->parent;

					// Silinecek düğüm max düğümü ise, _lastElem'i yeniden bağlamak gerekiyor
					if (del->right == _lastElem)
					{
						_lastElem->left = del->left;
						del->left->right = _lastElem;
					}
				}
				else if ((!del->left || del->left == _lastElem) && del->right && del->right != _lastElem)
				{
					balanceNode = del->parent;

					del->content.first <= del->parent->content.first ?
							del->parent->left = del->right : del->parent->right = del->right;
					del->right->parent = del->parent;
					
					// Silinecek düğüm max düğümü ise, _lastElem'i yeniden bağlamak gerekiyor
					if (del->left == _lastElem)
					{
						_lastElem->right = del->right;
						del->right->left = _lastElem;
					}
				}

				// İki childı varsa, silinecek düğümün anahtarını sol alt ağaçtaki en yüksek anahtarla değiştirmek ve
				// sol alt ağaçtaki bu en yüksek anahtarın düğümünü silmek gerekiyor
				else
				{
					Node* maxNode = searchMaxNode(del->left);

					// Kopyalamak için yok etmek ve yeniden oluşturmak gerekiyor (sabit değişkenler kopyalanacağından)
					_allocPair.destroy(&del->content);
					_allocPair.construct(&del->content, maxNode->content);
					
					return deleteNode(del->left, maxNode->content.first);
				}

				// Ağacı balanceNode'dan kök düğümüne dengeleyecek
				balanceTheTree(&_root, balanceNode);

				deallocateNode(del);
				return true;
			}


			/* ----- PRIVATE MEMBER FUNCTIONS : AVL BINARY SEARCH TREE ----- */
			/* -------------------- balancing the tree --------------------- */

			/**
			*   Sol ve sağ alt ağaçların yüksekliklerini karşılaştırır.
			*
			*   @param node 
			*   @return     sol ve sağ ağacın farkını geri döndürür
			*/
			int balanceOfSubtrees(Node* node)
			{
				if (!node)
					return 0;
				return heightTree(node->left, 1) - heightTree(node->right, 1);
			}

			/**
			*   Bir düğümle sol child arasında sağ döndürme yapar.
			*   Sol child yukarı çıkacak ve bu düğümün yerini alacak; ve bu düğüm yukarı 
			*   çıkan düğümün sağ child olacaktır.
			*
			*   @param root
			*   @param nodeGoingDown
			*/
			void rotateRight(Node** root, Node* nodeGoingDown)
			{
				//  				ÖRNEK RIGHT KAYDIRMASI
				//
				//
				//               Q                                 P              |
				//              / \     RIGHT ROTATION            / \             |
				//             P   C  ------------------->>>     A   Q            |
				//            / \                                   / \           |
				//           A   B                                 B   C          |

				Node* nodeGoingUp = nodeGoingDown->left;
				
				nodeGoingDown->left = nodeGoingUp->right;
				
				if (nodeGoingUp->right)
					nodeGoingUp->right->parent = nodeGoingDown;
				
				nodeGoingUp->right = nodeGoingDown;
				
				nodeGoingUp->parent = nodeGoingDown->parent;
				
				if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
					nodeGoingDown->parent->left = nodeGoingUp;
				else if (nodeGoingDown->parent)
					nodeGoingDown->parent->right = nodeGoingUp;
				
				nodeGoingDown->parent = nodeGoingUp;

				if (!nodeGoingUp->parent)
					*root = nodeGoingUp;
			}

			/**
			*   Bir düğüm ve onun sağ child arasında bir sol döndürme yapar.
			*   Sağ child yukarı çıkacak ve bu düğümün yerini alacak; 
			*   ve bu düğüm yukarı çıkan düğümün sol child olacaktır.
			*
			*   @param root
			*   @param nodeGoingDown
			*/
			void rotateLeft(Node** root, Node* nodeGoingDown)
			{
				//   				ÖRNEK LEFT KAYDIRMASI
				//
				//
				//               Q                                 P              |
				//              / \          LEFT ROTATION        / \             |
				//             P   C    <<<-------------------   A   Q            |
				//            / \                                   / \           |
				//           A   B                                 B   C          |

				Node* nodeGoingUp = nodeGoingDown->right;
				
				nodeGoingDown->right = nodeGoingUp->left;

				if (nodeGoingUp->left)
					nodeGoingUp->left->parent = nodeGoingDown;

				nodeGoingUp->left = nodeGoingDown;

				nodeGoingUp->parent = nodeGoingDown->parent;
				
				if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
					nodeGoingDown->parent->left = nodeGoingUp;
				else if (nodeGoingDown->parent)
					nodeGoingDown->parent->right = nodeGoingUp;

				nodeGoingDown->parent = nodeGoingUp;

				if (!nodeGoingUp->parent)
					*root = nodeGoingUp;
			}

			/**
			*   AVL ağacındaki bir düğümden başlar ve bu düğümün yanı sıra tüm üst düğümleri 
			*   köke kadar dengesizliklerini (sol ve sağ alt ağaçların yükseklikleri) kontrol eder.
			*   Dengesizlik varsa, dengeyi geri yüklemek için (sol veya sağ) bir döndürme işlemi gerçekleştirilir.
			*
			*	Kısacası, sol ve sağ parentlarını sayar ve aralarında 1 farktan fazla yükseklik farkı varsa 
			*	dengelemek için ona göre rotateright veya rotateleft yapar.
			*   @param root
			*   @param node
			*/
			void balanceTheTree(Node** root, Node* node)
			{
				while (node)
				{
					int balance;
					
					if ((balance = balanceOfSubtrees(node)) < -1 && balanceOfSubtrees(node->right) < 0)
						rotateLeft(root, node);

					else if (balance < -1 && balanceOfSubtrees(node->right) >= 0)
					{
						rotateRight(root, node->right);
						rotateLeft(root, node);
					}
					
					else if (balance > 1 && balanceOfSubtrees(node->left) > 0)
						rotateRight(root, node);

					else if (balance > 1 && balanceOfSubtrees(node->left) <= 0)
					{
						rotateLeft(root, node->left);
						rotateRight(root, node);
					}
					node = node->parent;
				}
			}
			
	};
		
}

//Iterators

void mapBegin();
void mapEnd();
void mapRBegin();
void mapREnd();

//Capacity
void mapEmpty();
void mapSize();
void mapMaxSize();

//Element access:
void mapBoxBrackets();

//Modifiers:
void mapInsert();
void mapErase();
void mapSwap();
void mapClear();

void mapKeyComp();
void mapValueComp();

void mapLowerBound();
void mapUpperBound();
void mapFind();
void mapCount();
void mapEqualRange();
#endif