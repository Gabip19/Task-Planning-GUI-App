//#pragma once
//
//
//template<typename TElem>
//class IteratorVector;
//
//
//template<typename TElem>
//class my_vector
//{
//	friend class IteratorVector<TElem>;
//
//private:
//
//	TElem* elems;
//	int len;
//	int capacity;
//	
//	void resize(); 
//
//public:
//
//	// Rule of 5
//	
//	my_vector() noexcept;										// Constructor
//	my_vector(const my_vector<TElem>& ot);						// Copy Constructor
//	my_vector<TElem>& operator=(const my_vector<TElem>& ot);	// Assignment Operator
//	my_vector(my_vector<TElem>&& ot) noexcept;					// Move Constructor
//	my_vector<TElem>& operator=(my_vector<TElem>&& ot);			// Move Assignment Operator
//	~my_vector();												// Destructor
//	
//	// Functii basic
//
//	void push_back(TElem new_el);
//	void erase(int index);
//	void clear();
//	const int size() const noexcept;
//
//	// Acces elemente
//
//	TElem& at(const int poz) noexcept;
//	TElem at(const int poz) const;
//	TElem& operator[](const int poz) noexcept;
//	TElem operator[](const int poz) const noexcept;
//	
//	// Iterator
//
//	IteratorVector<TElem> begin() noexcept;
//	IteratorVector<TElem> begin() const noexcept;
//	IteratorVector<TElem> end() noexcept;
//	IteratorVector<TElem> end() const noexcept;
//
//};
//
//
//template<typename TElem>
//inline my_vector<TElem>::my_vector() noexcept
//{
//	this->capacity = 2;
//	this->len = 0;
//	this->elems = new TElem[capacity];
//}
//
//
//template<typename TElem>
//inline my_vector<TElem>::my_vector(const my_vector<TElem>& ot)
//{
//	this->capacity = ot.capacity;
//	this->len = ot.len;
//	this->elems = new TElem[ot.capacity];
//
//	for (int i = 0; i < ot.len; i++)
//	{
//		this->elems[i] = ot.elems[i];
//	}
//}
//
//
//template<typename TElem>
//inline my_vector<TElem>& my_vector<TElem>::operator=(const my_vector<TElem>& ot)
//{
//	if (this == &ot)
//	{
//		return *this;
//	}
//
//	delete[] elems;
//	elems = new TElem[ot.capacity];
//	
//	for (int i = 0; i < ot.len; i++)
//	{
//		elems[i] = ot.elems[i];
//	}
//
//	this->len = ot.len;
//	this->capacity = ot.capacity;
//	return *this;
//}
//
//
//template<typename TElem>
//inline my_vector<TElem>::my_vector(my_vector<TElem>&& ot) noexcept
//{
//	elems = ot.elems;
//	len = ot.len;
//	capacity = ot.capacity;
//
//	ot.elems = nullptr;
//	ot.len = 0;
//	ot.capacity = 0;
//}
//
//
//template<typename TElem>
//inline my_vector<TElem>& my_vector<TElem>::operator=(my_vector<TElem>&& ot)
//{
//	if (this == &ot)
//	{
//		return *this;
//	}
//	
//	delete[] elems;
//
//	elems = ot.elems;
//	len = ot.len;
//	capacity = ot.capacity;
//
//	ot.elems = nullptr;
//	ot.len = 0;
//	ot.capacity = 0;
//	
//	return *this;
//}
//
//
//template<typename TElem>
//inline my_vector<TElem>::~my_vector()
//{
//	delete[] this->elems;
//}
//
//
//
//// Mareste capacitatea de stocare a vectorului
//template<typename TElem>
//inline void my_vector<TElem>::resize()
//{
//	const int new_capacity = capacity * 2;
//	TElem* new_elems = new TElem[new_capacity];
//	
//	if (new_elems != nullptr)
//		for (int i = 0; i < len; i++)
//			new_elems[i] = elems[i];
//
//	if (elems != nullptr)
//		delete[] elems;
//	elems = new_elems;
//	capacity = new_capacity;
//}
//
//
//// Adauga un element in vector
//template<typename TElem>
//inline void my_vector<TElem>::push_back(TElem new_el)
//{
//	if (len == capacity)
//		resize();
//
//	elems[len] = new_el;
//	len++;
//}
//
//
//// Sterge un element din vector
//template<typename TElem>
//inline void my_vector<TElem>::erase(const int index)
//{
//	for (int i = index; i < this->len - 1; i++)
//	{
//		elems[i] = elems[i + 1];
//	}
//	this->len--;
//}
//
//
//// Sterge toate elementele din lista
//template<typename TElem>
//inline void my_vector<TElem>::clear()
//{
//	this->capacity = 2;
//	this->len = 0;
//	delete[] this->elems;
//	this->elems = new TElem[this->capacity];
//}
//
//
//// Returneaza numarul de elemente din vector
//template<typename TElem>
//inline const int my_vector<TElem>::size() const noexcept
//{
//	return this->len;
//}
//
//
//// Returneaza o referinta a elementului de pe pozitia poz
//template<typename TElem>
//inline TElem& my_vector<TElem>::at(const int poz) noexcept
//{
//	return elems[poz];
//}
//
//
//// Returneaza valoarea elementului de pe pozitia poz
//template<typename TElem>
//inline TElem my_vector<TElem>::at(const int poz) const
//{
//	return elems[poz];
//}
//
//
//// Returneaza o referinta a elementului de pe pozitia poz
//template<typename TElem>
//inline TElem& my_vector<TElem>::operator[](const int poz) noexcept
//{
//	return elems[poz];
//}
//
//
//// Returneaza valoarea elementului de pe pozitia poz
//template<typename TElem>
//inline TElem my_vector<TElem>::operator[](const int poz) const noexcept
//{
//	return elems[poz];
//}
//
//
//// Returneaza un iterator la inceputul vectorului
//template<typename TElem>
//inline IteratorVector<TElem> my_vector<TElem>::begin() noexcept
//{
//	return IteratorVector<TElem>(*this, 0);
//}
//
//
//// Returneaza un iterator la inceputul vectorului varianta const
//template<typename TElem>
//inline IteratorVector<TElem> my_vector<TElem>::begin() const noexcept
//{
//	return IteratorVector<TElem>(*this, 0);
//}
//
//
//// Returneaza un iterator la finalul vectorului
//template<typename TElem>
//inline IteratorVector<TElem> my_vector<TElem>::end() noexcept
//{
//	return IteratorVector<TElem>(*this, len);
//}
//
//
//// Returneaza un iterator la finalul vectorului varianta const
//template<typename TElem>
//inline IteratorVector<TElem> my_vector<TElem>::end() const noexcept
//{
//	return IteratorVector<TElem>(*this, len);
//}
//
//
//
//template<typename TElem>
//class IteratorVector
//{
//
//private:
//
//	const my_vector<TElem>& vec;
//	int poz;
//
//public:
//
//	IteratorVector(const my_vector<TElem>& vec_) noexcept;
//	IteratorVector(const my_vector<TElem>& vec_, int poz) noexcept;
//	bool valid() const noexcept;
//	TElem& element() const noexcept;
//	void next() noexcept;
//	TElem& operator*() noexcept;
//	IteratorVector& operator++() noexcept;
//	IteratorVector& operator--() noexcept;
//	IteratorVector& operator+(const int value) noexcept;
//	IteratorVector& operator-(const int value) noexcept;
//	bool operator==(const IteratorVector& ot) noexcept;
//	bool operator!=(const IteratorVector& ot) noexcept;
//
//};
//
//
//template<typename TElem>
//inline IteratorVector<TElem>::IteratorVector(const my_vector<TElem>& vec_) noexcept : vec{ vec_ } {};
//
//
//template<typename TElem>
//inline IteratorVector<TElem>::IteratorVector(const my_vector<TElem>& vec_, int poz_) noexcept : vec{ vec_ }, poz{ poz_ } {};
//
//
//// Verifica daca un iterator pe vector este valid
//template<typename TElem>
//inline bool IteratorVector<TElem>::valid() const noexcept
//{
//	return poz < vec.len;
//}
//
//
//// Returneaza elementul de pe pozitia indicata de iterator
//template<typename TElem>
//inline TElem& IteratorVector<TElem>::element() const noexcept
//{
//	return vec.elems[poz];
//}
//
//
//// Plaseaza iteratorul pe vector la urmatorul element
//template<typename TElem>
//inline void IteratorVector<TElem>::next() noexcept
//{
//	poz++;
//}
//
//
//// Returneaza elementul de pe pozitia indicata de iterator
//template<typename TElem>
//inline TElem& IteratorVector<TElem>::operator*() noexcept
//{
//	return element();
//}
//
//
//// Plaseaza iteratorul pe vector la urmatorul element
//template<typename TElem>
//inline IteratorVector<TElem>& IteratorVector<TElem>::operator++() noexcept
//{
//	next();
//	return *this;
//}
//
//
//// Plaseaza iteratorul pe vector la elementul anterior
//template<typename TElem>
//inline IteratorVector<TElem>& IteratorVector<TElem>::operator--() noexcept
//{
//	this->poz--;
//	return *this;
//}
//
//
//// Random acces iterator + operation
//template<typename TElem>
//inline IteratorVector<TElem>& IteratorVector<TElem>::operator+(const int value) noexcept
//{
//	this->poz += value;
//	return *this;
//}
//
//
//// Random acces iterator - operation
//template<typename TElem>
//inline IteratorVector<TElem>& IteratorVector<TElem>::operator-(const int value) noexcept
//{
//	this->poz -= value;
//	return *this;
//}
//
//
//// Verifica daca doi iteratori pe vector sunt identici
//template<typename TElem>
//inline bool IteratorVector<TElem>::operator==(const IteratorVector& ot) noexcept
//{
//	return this->poz == ot.poz;
//}
//
//
//// Verifica daca doi iteratori pe vectori sunt diferiti
//template<typename TElem>
//inline bool IteratorVector<TElem>::operator!=(const IteratorVector& ot) noexcept
//{
//	return !(*this == ot);
//}