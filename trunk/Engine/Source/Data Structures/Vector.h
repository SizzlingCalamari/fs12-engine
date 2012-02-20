#pragma once

#include <malloc.h>
#include <iterator>

//#include <vector>

#ifndef NULL
	#define NULL = 0
#endif

namespace FS12
{
	typedef unsigned int size_type;

	template<class _Type>
	class vector_iterator_const
		: public std::iterator<std::random_access_iterator_tag, _Type>
	{
		typedef vector_iterator_const<_Type> vicType;
		typedef _Type* pointer;
		typedef _Type& reference;
		
	protected:
		pointer m_pData;	// pointer to element in vector

	public:
		// Default constructor
		vector_iterator_const() : m_pData(NULL) { }

		// Constructor that takes an location
		// used for begin and end, etc
		vector_iterator_const(pointer _ptr): m_pData(_ptr){ }

		// Derefernce operator
		reference operator * () const { return (*this->m_pData); }

		// Arrow Operator
		pointer operator -> () const { return (&**this); }

		// Prefix Operators
		vicType& operator ++ () { ++(this->m_pData); return (*this); }
		vicType& operator -- () { --(this->m_pData); return (*this); }

		// Postfix Operators
		vicType operator ++ (int)
		{
			vicType _Tmp = *this;
			++(*this);
			return (_Tmp);
		}
		vicType operator -- (int)
		{
			vicType _Tmp = *this;
			--(*this);
			return (_Tmp);
		}
		
		// Incement/Decrement Operators
		vicType& operator += (size_type _Off)
		{
			m_pData += _Off;
			return (*this);
		}
		vicType operator + (size_type _Off) const
		{
			vicType _Tmp = *this;
			return (_Tmp += _Off);
		}
		vicType& operator -= (int _Off)
		{	
			return (*this += -_Off);
		}
		vicType operator - (int _Off) const
		{
			vicType _Tmp = *this;
			return (_Tmp -= _Off);
		}

		// Comparison Operators
		// TODO: Add a function to check if iterators are comparable
		bool operator == (const vicType& _Right) const { return (this->m_pData == _Right.m_pData); }
		bool operator != (const vicType& _Right) const { return (!(*this == _Right)); }
		bool operator <  (const vicType& _Right) const { return (this->m_pData < _Right.m_pData); }
		bool operator >  (const vicType& _Right) const { return (_Right < *this); }
		bool operator <= (const vicType& _Right) const { return (!(_Right < *this)); }
		bool operator >= (const vicType& _Right) const { return (!(*this < _Right)); }

		// TODO: Figure out the point of these :)
		//size_type operator - (const vicType& _Right) const
		//{
		//	return (this->_Ptr - _Right._Ptr);
		//}
		//reference operator[](size_type _Off) const
		//{	// subscript
		//	return (*(*this + _Off));
		//}
	};

	template<class _Type>
	class vector_iterator
		: public vector_iterator_const<_Type>
	{
		typedef vector_iterator_const<_Type> _base;
		typedef vector_iterator<_Type> iterType;
		typedef _Type* pointer;
		typedef _Type& reference;

	public:
		// Default constructor
		vector_iterator() : _base() { }

		// Constructor that takes an location
		// used for begin and end, etc
		vector_iterator(pointer _ptr): _base(_ptr){ }

		// Derefernce operator
		reference operator * () const { return (*this->m_pData); }

		// Arrow Operator
		pointer operator -> () const { return (&**this); }

		// Prefix Operators
		iterType& operator ++ () { ++(this->m_pData); return (*this); }
		iterType& operator -- () { --(this->m_pData); return (*this); }

		// Postfix Operators
		iterType operator ++ (int)
		{
			iterType _Tmp = *this;
			++(*this);
			return (_Tmp);
		}
		iterType operator -- (int)
		{
			iterType _Tmp = *this;
			--(*this);
			return (_Tmp);
		}
		
		// Incement/Decrement Operators
		iterType& operator += (size_type _Off)
		{
			m_pData += _Off;
			return (*this);
		}
		iterType operator + (size_type _Off) const
		{
			iterType _Tmp = *this;
			return (_Tmp += _Off);
		}
		iterType& operator -= (int _Off)
		{	
			return (*this += -_Off);
		}
		iterType operator - (int _Off) const
		{
			iterType _Tmp = *this;
			return (_Tmp -= _Off);
		}

		// Comparison Operators
		// TODO: Add a function to check if iterators are comparable
		bool operator == (const iterType& _Right) const { return (this->m_pData == _Right.m_pData); }
		bool operator != (const iterType& _Right) const { return (!(*this == _Right)); }
		bool operator <  (const iterType& _Right) const { return (this->m_pData < _Right.m_pData); }
		bool operator >  (const iterType& _Right) const { return (_Right < *this); }
		bool operator <= (const iterType& _Right) const { return (!(_Right < *this)); }
		bool operator >= (const iterType& _Right) const { return (!(*this < _Right)); }
	};

	template<class _Type>
	class vector
	{
		// Type defines for easy types
		typedef vector<_Type> vectorType;
		typedef vector_iterator_const<_Type>	c_iterator; // Constant iterator
		typedef vector_iterator<_Type>			iterator;	// Regular iterator

	private:
		_Type*		m_pBegin;
		_Type*		m_pEnd;
		_Type*		m_pCapacity;

		size_type	m_Size;
		size_type	m_Capacity;


		void TidyUp()
		{
			free(m_pBegin);

			m_pBegin = m_pEnd = NULL;
			m_Size = m_Capacity = 0;
		}

		size_type MaxSize()
		{
			_SIZT _Count = (_SIZT)(-1) / sizeof (_Type);
			return (_Count > 0) ? (size_type)_Count : 1;
		}
	public:
		// Constructors:
		// Default Constructor
		vector() : m_pBegin(NULL), m_pEnd(NULL), m_pCapacity(NULL), m_Size(0), m_Capacity(0) {}

		// Constructor with a default capacity
		vector(size_type _capacity) : vector() { /*resize(_capacity);*/ }

		~vector() { clear(); }

		// Standard Functions:
		// Clear the array
		void clear()
		{
			free(m_pBegin);

			m_pBegin = m_pEnd = NULL;
			m_Size = m_Capacity = 0;
		}

		// Push Back
		void push_back(_Type&& _data)
		{
			if (m_pEnd == m_pCapacity)
				resize();
			
			memcpy((void*)(m_pEnd), (void*)&(_data), sizeof(_Type));

			++m_Size;
			++m_pEnd;
		}

		size_type size() const { return m_Size; }
		size_type capacity() const { return m_Capacity; }

		// Pop Back
		//HRESULT pop_back();
		// Insert
		//HRESULT insert(_Type& _data, iterator location);
		//HRESULT insert(_Type& _data, c_iterator location);
		//HRESULT insert(_Type& _data, int location);
		// Reserve

		// Append
		//HRESULT append(UINT _capacity);
		// Empty
		//bool isEmpty() const { return (this->m_pBegin == this->m_pEnd); }
		// Clear
		//HRESULT clear();

		// Iterator Functions:
		// Iterator to vector element 0
		//iterator begin()
		//{	// return iterator for beginning of mutable sequence
		//	return (iterator(this->_Myfirst, this));
		//}
		//const_iterator begin() const
		//{	// return iterator for beginning of nonmutable sequence
		//	return (const_iterator(this->_Myfirst, this));
		//}

		iterator	begin() { return iterator(m_pBegin); }
		c_iterator	begin() const { return c_iterator(m_pBegin); }

		iterator	end() { return iterator(m_pEnd); }
		c_iterator	end() const { return c_iterator(m_pEnd); }

		// Resize
		void resize(size_type _capacity = 0)
		{
			if (_capacity && _capacity < m_Capacity)
				return; // TODO: Add code to downsize here
			if (_capacity > m_Capacity)
				m_Capacity = _capacity;
			else if (!m_pBegin)
				m_Capacity = 1;
			else if ((m_Capacity * 2) >= MaxSize())
				m_Capacity = MaxSize();
			else
				m_Capacity *= 2;

			void* temp = NULL;
			if (!m_pBegin)
				m_pBegin = (_Type*)malloc(sizeof(_Type) * m_Capacity);
			else
			{
				temp = realloc(m_pBegin, sizeof(_Type) * m_Capacity);
				if (!temp)
					return;
				else
					m_pBegin = (_Type*)temp;
			}

			m_pEnd = (m_pBegin + m_Size);
			m_pCapacity = (m_pBegin + m_Capacity);
		}

		_Type& operator [] (const size_type _index) 
		{ 
			return *(m_pBegin + _index);
		}

	};
};