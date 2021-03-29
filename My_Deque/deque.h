
#ifndef __DEQUE__
#define __DEQUE__

#include <vector>
#include <iterator>	
#include<algorithm>

template<typename T> class RA_Deque_Iterator;
template<typename T> using iterator = RA_Deque_Iterator<T>;

template <typename T>
class Deque {
	friend class iterator<T>;
public:
	// Constructors / Destructor
	Deque();
	explicit Deque(int);
	explicit Deque(int, const T& value);

	Deque(const Deque&);
	Deque& operator= (Deque&);

	~Deque();

	// other methods
	size_t size() const;

	T& operator[] (size_t);
	const T& operator[] (size_t) const;
	T& at(size_t);
	const T& at(size_t) const;

	// methods push, pop
	void push_back(const T&);
	void push_front(const T&);

	void pop_front();
	void pop_back();

private:
	static const size_t SIZE = 5;								// array's size	
	std::vector<T**> pointers;

	// Begins / Ends / Size / Capacity
	size_t begin1 = 0;										// pointers' begin
	size_t begin2 = 0;										// array's begin
	size_t end1 = 0;										// pointers' end
	size_t end2 = 0;										// array's end

	size_t m_size = 0;										// number of T elements
	size_t m_capacity = 0;									// pointers' capacity

	void reallocate();										// realloc pointers
	void deallocate();										// dealloc pointers
};

template<typename T>
class RA_Deque_Iterator {
	friend class Deque;

public:
	iterator() = default;

	iterator& operator++ ();
	iterator& operator-- ();

	const iterator& operator++ (int);
	const iterator& operator-- (int);

	void operator+= (size_t);
	void operator-= (size_t);

	bool operator< (const iterator&) const;
	bool operator> (const iterator&) const;
	bool operator<= (const iterator&) const;
	bool operator>= (const iterator&) const;
	bool operator== (const iterator&) const;
	bool operator!= (const iterator&) const;

	T& operator* ();
	T* operator-> ();

private:
	T* iter;
};


#endif