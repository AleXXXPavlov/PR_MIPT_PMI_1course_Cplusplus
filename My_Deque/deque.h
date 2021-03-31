
#ifndef __DEQUE__
#define __DEQUE__
// Deque header file 

#include <vector>
#include <iterator>	
#include<algorithm>
#include <cmath>

template <typename T>
class Deque {
	friend class iterator;
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
	static const size_t SIZE = 5;						    // array's size	
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

public:
	template<bool is_const = false>
	class iterator {
		friend class Deque;
		
		using category = std::random_access_iterator_tag;
		using value_type = T;
		using pointer = std::conditional_t<iscnst, const T*, T*>;
		using reference = std::conditional_t<iscnst, const T&, T&>;
		using difference_type = std::ptrdiff_t;

		using const_iterator = iterator<true>;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<iterator<true>>;

	public:

		// --------------- Constructos / Assignment / Destructor ---------------

		iterator(int p1, int p2, std::vector<T*>& v_ptrs) :
			p1(p1), p2(p2), ptr(v_ptrs[p1] + p2), ptr0(&(v_ptrs[p1])) {}
		iterator(const iterator& c_it) :
			p1(c_it.p1), p2(c_it.p2), ptr(c_it.ptr), ptr0(c_it.ptr) {}
		iterator<is_const>& operator= (iterator<is_const>& it) {
			std::swap(p1, it.p1);
			std::swap(p2, it.p2);
			std::swap(ptr, it.ptr);
			std::swap(ptr0, it.ptr0);
		}

		~iterator() = default; 



		inline iterator& operator++ () {
			return *this += 1;
		}
		inline iterator& operator-- () {
			return *this -= 1;
		}

		const iterator operator++ (int) {
			Deque<T>::iterator r_it = *this;
			*this += 1;
			return r_it;
		}
		const iterator operator-- (int) {
			Deque<T>::iterator r_it = *this;
			*this -= 1;
			return r_it;
		}

		 iterator& operator+= (int num) {
			if (num < 0) return *this -= (-num);

			new_p1 = (num + p2) / SIZE + p1;
			new_p2 = (num + p2) % SIZE;
			
			ptr0 += new_p1 - p1;
			ptr = pointers[new_p1] + new_p2;
			p1 = new_p1;
			p2 = new_p2;

			return *this;
		}
		iterator& operator-= (int num) {
			if (num < 0) return *this += (-num);

			diff = num - p2;
			if (diff <= 0) new_p2 -= num;
			else {
				new_p2 = SIZE - diff % SIZE;
				new_p1 -= ceil(diff / SIZE);
			}

			ptr0 -= p1 - new_p1;
			p1 = new_p1;
			p2 = new_p2;
			ptr = pointers[p1] + p2;

			return *this;
		}

		// -------------------- Bool methods ---------------------

		inline bool operator< (const iterator& it) const {
			if (p1 != it.p1) return p1 < it.p1;
			return p2 < it.p2;
		}
		inline bool operator> (const iterator& it) const {
			if (p1 != it.p1) return p1 > it.p1;
			return p2 > it.p2;
		}
		inline bool operator<= (const iterator& it) const {
			return p1 <= it.p1;		
		}
		inline bool operator>= (const iterator& it) const {
			return p1 >= i.p1;
		}
		inline bool operator== (const iterator& it) const {
			return p1 == it.p1 && p2 == it.p2;
		}
		inline bool operator!= (const iterator& it) const {
			return p1 != it.p1 || p2 != it.p2;
		}

		// Other methods

		std::conditional_t<is_const, const T&, T&> operator* () const {
			return *ptr;
		}
		std::conditional_t<is_const, const T*, T*> operator-> () const {
			return ptr;
		}

		inline iterator begin() const {
			return iterator(begin1, begin2, pointers);
		}
		inline iterator end() const {
			if (end2 == SIZE - 1) return iterator(end1 + 1, 0, pointers);
			return iterator(end1, end2 + 1, pointers);
		}

		inline const_iterator cbegin() const {
			return iterator(begin1, begin2, pointers);
		}
		inline const_iterator cend() const {
			if (end2 == SIZE - 1) return iterator(end1 + 1, 0, pointers);
			return iterator(end1, end2 + 1, pointers);
		}

		inline reverse_iterator rbegin() {
			iterator it = end();
			return std::make_reverse_iterator(it);
		}
		inline reverse_iterator rend() {
			iterator it = begin();
			return std::make_reverse_iterator(it);
		}
		inline const_reverse_iterator crbegin() const {
			const_iterator it = cend();
			return std::make_reverse_iterator(it);
		}
		inline const_reverse_iterator crend() const {
			const_iterator it = cbegin();
			return std::make_reverse_iterator(it);
		}

		// -------------------- Insert, Erase methods ------------------

		void insert(iterator it, const T& el) {
			
		}
		void insert(const_iterator it, const T& el) {

		}

		void erase(iterator it) {

		}
		void erase(const_iterator it) {

		}

	private:
		int p1;													// pointers' position
		int p2;													// array's position

		std::conditional_t<is_const, const T*, T*> ptr;			// current pointer of element
		T** ptr0;												// pointer of current array
	};
};




#endif