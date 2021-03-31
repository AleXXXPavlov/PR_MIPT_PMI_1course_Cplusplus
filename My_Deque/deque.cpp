// My realization of deque

#include "deque.h"


// ---------------------------- Constructors / Assignment / Destructor --------------------------
template<typename T>
Deque<T>::Deque() {
	Deque(1, T());
}

template<typename T>
Deque<T>::Deque(int sz) {
	Deque(sz, T());
}

template<typename T>
Deque<T>::Deque(int sz, const T& value)
{
	begin1 = ceil(sz / m_size);
	begin2 = 0;
	end1 = 2 * begin1 - 1;
	end2 = (sz % SIZE == 0 ? SIZE - 1 : sz % SIZE - 1);

	size = sz;
	m_capacity = 3 * begin1;

	// Memory allocation
	pointers.resize(m_capacity);
	for (size_t i = 0; i < m_capacity; ++i) {
		pointers[i] = reinterpret_cast<T*>(new int8_t[sizeof(T) * SIZE]);
	}

	// Memory full
	size_t i = 0;
	try {
		size_t i1 = begin1;
		size_t i2 = begin2;

		for (; i < m_size; ++i) {
			new(pointers[i1] + i2) T(value);			// placement_new

			++i2;
			if (i2 == SIZE) {
				i2 = 0;
				++i1;
			}
		}
	} catch (...) {
		this->~Deque();
		throw;
	}
}

template<typename T>
Deque<T>::Deque(const Deque& obj) :
	begin1(obj.begin1), begin2(obj.begin2), end1(obj.end1),
	end2(obj.end2), m_size(obj.m_size), m_capacity(obj.m_capacity)
{
	// Memory allocation
	pointers.resize(m_capacity);
	for (size_t i = 0; i < m_capacity; ++i) {
		pointers[i] = reinterpret_cast<T*>(new int8_t[sizeof(T) * SIZE]);
	}

	// Memory full
	size_t i = 0;
	try {
		size_t i1 = begin1;
		size_t i2 = begin2;

		for (; i < m_size; ++i) {
			new(pointers[i1] + i2) T(obj[i]);			// placement_new

			++i2;
			if (i2 == SIZE) {
				i2 = 0;
				++i1;
			}
		}
	} catch(...) {
		this->~Deque;
		throw;
	}
}

template<typename T>
Deque<T>& Deque<T>::operator= (Deque& obj) {
	std::swap(pointers, obj.pointers);

	std::swap(begin1, obj.begin1);
	std::swap(begin2, obj.begin2);
	std::swap(end1, obj.end1);
	std::swap(end2, obj.end2);

	std::swap(m_size, obj.m_size);
	std::swap(m_capacity, obj.m_capacity);

	return *this;
}

template<typename T>
Deque<T>::~Deque() {
	size_t i1 = begin1, 
		i2 = begin2;

	for (size_t i = 0; i < m_size; ++i) {
		(pointers[i1] + i2)->~T();

		++i2;
		if (i2 == SIZE) {
			i2 = 0;
			++i1;
		}
	}

	for (int j = m_capacity - 1; j >= 0; --j) {
		delete[] reinterpret_cast<int8_t*>(pointers[j]);
	}

	pointers.clear();
	pointers.shrink_to_fit();

	begin1 = 0;
	begin2 = 0;
	end1 = 0;
	end2 = 0;

	m_size = 0;
	m_capacity = 0;
}

// ----------------------------- Methods for working with memory ----------------------------

template<typename T>
void Deque<T>::reallocate() {
	try {
		if ((begin1 == 0 && begin2 == 0) || (end1 == m_capacity - 1 && end2 == SIZE - 1)) {
			sz = end1 - begin1 + 1;

			// Memory reallocation
			pointers.resize(3*sz- m_capacity);
			m_capacity = 3 * sz - m_capacity;
			for (size_t i = end1 + 1; i < m_capacity; ++i) {
				pointers[i] = reinterpret_cast<T*>(new int8_t[sizeof(T) * SIZE]);
			}

			// Swaping pointers
			for (size_t i = end1, j = 2*sz-1; i >= begin1; --i, --j) {
				std::swap(pointers[i], pointers[j]);
			}

			begin1 = sz;
			end1 = 2*sz - 1;
		}
	} catch (...) {
		throw;
	}
}

template<typename T>
void Deque<T>::deallocate() {
	try {
		sz = end1 - begin1 + 1;
		if (sz <= m_capacity / 9) {
			// Swaping pointers
			for (size_t i = begin1, j = sz; i <= end1; ++i, ++j) {
				std::swap(pointers[i], pointers[j]);
			}

			begin1 = sz;
			end1 = 2 * sz - 1;

			// Memory reallocation
			for (size_t i = 3 * sz; i < m_capacity; ++i) {
				delete[] reinterpret_cast<int8_t*>(pointers[i]);
			}

			m_capacity = 3 * sz;				
		}
	} catch (...) {
		throw;
	}
}

// ------------------------------- Methods push, pop --------------------------------

template<typename T>
void Deque<T>::push_back(const T& value) {
	reallocate();

	try {
		if (end2 == SIZE - 1) {
			new[pointers[end1 + 1]] T(value);
			end2 = 0;
			++end1;
		}
		else {
			new[pointers[end1] + end2 + 1] T(value);
			++end2;
		}

		++m_size;
	} catch(...) {
		throw;
	}
}

template<typename T>
void Deque<T>::push_front(const T&) {
	try {
		if (begin2 == 0) {
			new[pointers[begin1 - 1] + SIZE - 1] T(value);
			begin2 = SIZE - 1;
			--begin1;
		}
		else {
			new[pointers[end1] + begin2 - 1] T(value);
			--begin2;
		}

		++m_size;
	}
	catch (...) {
		throw;
	}
}

template<typename T>
void Deque<T>::pop_back() {
	(pointers[end1] + end2)->~T();
	if (end2 == 0) {
		end2 = SIZE - 1;
		--end1;
	}
	else {
		--end2;
	}
	--m_size;

	deallocate();
}

template<typename T>
void Deque<T>::pop_front() {
	(pointers[begin1] + begin2)->~T();
	if (begin2 == SIZE - 1) {
		begin2 = 0;
		++begin1;
	}
	else {
		++end2;
	}
	--m_size;

	deallocate();
}


// ----------------------------------- Other methods --------------------------------

template<typename T>
size_t Deque<T>::size() const {
	return m_size;
}

template<typename T>
T& Deque<T>::operator[] (size_t pos) {
	if (pos + begin2 < SIZE) return pointers[begin1][pos + begin2];
	
	i -= (SIZE - begin2);
	return pointers[begin1 + i / SIZE + 1][i % SIZE];
}

template<typename T>
const T& Deque<T>::operator[] (size_t pos) const {
	if (pos + begin2 < SIZE) return pointers[begin1][pos + begin2];

	i -= (SIZE - begin2);
	return pointers[begin1 + i / SIZE + 1][i % SIZE];
}

template<typename T>
T& Deque<T>::at(size_t pos) {
	if (pos >= m_size || pos < 0) return std::out_of_range("std::out_of_range");
	return (*this)[pos];
}

template<typename T>
const T& Deque<T>::at(size_t pos) const {
	if (pos >= m_size || pos < 0) return std::out_of_range("std::out_of_range");
	return (*this)[pos];
}
