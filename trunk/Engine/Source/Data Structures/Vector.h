#pragma once

#include <stdlib.h>
#include <malloc.h>
#include <iterator>

//#ifndef NULL
//	#define NULL = 0
//#endif

namespace FS12
{
	template<class _Type> class vector;

	template<class _Type>
		class Vector_iterator_const
	{
	};

	template<class _Type> 
		class Vector_iterator
	{
	};

	#pragma region Fancy Iterator
	/*
	template<class _Vector>
		class _Vector_iterator_const : public _Iterator012<
				random_access_iterator_tag, typename _Myvec::value_type,
				typename _Myvec::difference_type, typename _Myvec::const_pointer,
				typename _Myvec::const_reference, _Iterator_base>
	{
	protected:
		typedef _Vector_iterator_const<_Vector>		_Iter;
		typedef random_access_iterator_tag			iterator_category;

		typedef typename _Vector::pointer			_VecPtr;
		typedef typename _Vector::value_type		_VecValue_type;
		typedef typename _Vector::difference_type	_VecDifference_type;
		typedef typename _Vector::const_pointer		_VecPointer;
		typedef typename _Vector::const_reference	_VecReference;

		_VecPtr m_pElement; // Pointer to element in vector

	public:

		_VecReference operator * () 
		{
			//TODO: Range checking
			return ((*this)->m_pElement);
		}
	};
	*/
	#pragma endregion


	template<class _Type>
	class vector
	{
		friend class Vector_iterator_const<_Type>;
		friend class Vector_iterator<_Type>;

		typedef Vector_iterator_const<_Type>*	c_iterator; // Constant iterator pointer
		typedef Vector_iterator<_Type>*			iterator;	// Regular iterator pointer
	protected:
		_Type*		m_pArray;	// Data array

		iterator	m_pBegin;
		iterator	m_pEnd;

		UINT		m_Size;
		UINT		m_Capacity;

		// Hidden Destructor
		~vector();

		// Helper Resize function
		

	public:
		// Constructors:
		// Default Constructor
		vector() : m_pArray(NULL), m_Size(0), m_Capacity(0),
			m_iterpBegin(NULL), m_iterpEnd(NULL) {}

		// Constructor with a default capacity
		vector(UINT _capacity) : vector() { resize(_capacity); }


		// Standard Functions:
		// Push Back
		HRESULT push_back(_Type& _data);
		// Pop Back
		HRESULT pop_back();
		// Insert
		// Reserve

		// Append
		HRESULT append(UINT _capacity);
		// Resize
		HRESULT resize(UINT _capacity);
		// Empty
		bool isEmpty() const { return (this->m_pBegin == this->m_pEnd); }
		// Clear
		HRESULT clear();

		// Iterator Functions:
		// Iterator to vector element 0
		iterator	begin() { return m_pBegin; }
		c_iterator	begin() const { return (c_iterator)m_pBegin; }
		// Iterator to vector element n
		iterator	end() { return m_pEnd; }
		c_iterator	end() const { return (c_iterator)m_pEnd; }


	};
};