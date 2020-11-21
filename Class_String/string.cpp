
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>

// -------------------------------------------------- Класс String и его методы --------------------------------------------------

class String {
public:
	/* Методы для создания и удаления объектов */
	String() = default; // конструктор по-умолчанию

	explicit String(const char*); // конструктор от C-style строки
	explicit String(size_t); // конструктор с 1 параметром
	explicit String(char, size_t); // конструктор с 2 параметрами

	String(const String &); // конструктор копирования
	String& operator= (const String&); // оператор присваивания от обьекта класса
	String& operator= (const char*); // оператор присваивания от строки

	~String(); // деструктор

	/* Методы для получения информации об объекте класса */
	char& operator[] (size_t) const; // получение элемента строки по индексу
	size_t length() const; // получение длины строки

	void push_back(const char); // добавление элемента в конец строки

	friend std::istream& operator>> (std::istream&, String&); // переопределение оператор потокового ввода
	friend std::ostream& operator<< (std::ostream&, const String&); // переопределение оператор потокового вывода

	bool empty(); // проверка на пустоту строки

	/* Методы для изменения объекта класса */
	void Incr_Memory(size_t); // достижение необходимого минимума capacity
	void Red_Memory(size_t); // достижение необходимого максимума capacity

	void pop_back(); // удаление последнего элемента строки

	char* front() const; // возвращение указателя на первый элемент строки
	char* back() const; // возвращение указателя на последний элемент строки

	bool operator== (const String&) const; // проверка равенства строк
	String& operator+= (const String&); // конкатенация с изменением объекта
	String& operator+= (const char); // конкатенация с одним символом с изменением объекта
	String& operator+ (const String&) const; // конкатенация с получением нового объекта

	size_t find(const String&) const; // нахождение самого левого вхождения подстроки
	size_t rfind(const String&) const; // нахождение самого правого вхождения подстроки

	String& substr(size_t, size_t); // возвращение подстроки, начинающаяся с определенного индекса, какой-то длины
	void clear(); // освобождение памяти из-под строки

private:
	char* body_ = nullptr; // указатель на начало строки
	size_t size_ = 0; // реальный размер
	size_t capacity_ = 0; // максимальный размер
};

// ---------------------------------------- Конструкторы / Оператор присваивания  ----------------------------------------

String::String(size_t size) :
	capacity_(size)
{
	body_ = new char[capacity_];
}

String::String(char c, size_t size = 1) :
	String::String(size)
{
	memset(body_, c, size);
	size_ = capacity_;
}

String::String(const char* str) :
	String::String(strlen(str))
{
	memcpy(body_, str, size_);
	size_ = capacity_;
}

String::String(const String& Obj) :
	String::String(Obj.body_) 
{}

String& String::operator= (const String& Obj) {
	if (this == &Obj) {
		return *this;
	}

	delete[] body_;
	
	body_ = new char[Obj.size_];
	memcpy(body_, Obj.body_, Obj.size_);
	size_ = Obj.size_;
	capacity_ = Obj.capacity_;

	return *this;
}

String& String::operator= (const char* str) {
	assert(str != nullptr);

	delete[] body_;
	body_ = new char[strlen(str)];
	memcpy(body_, str, strlen(str));

	size_ = strlen(str);
	capacity_ = strlen(str);

	return *this;
}

String::~String() {
	size_ = 0;
	capacity_ = 0;
	delete[] body_;
	body_ = nullptr;
}

// ---------------------------------------- Реализация методов для получения информации о классе --------------------------------------
char& String::operator[] (size_t ix) const {
	return body_[ix];
}

size_t String::length() const {
	return size_;
}

void String::push_back(const char c) {
	*this += c;
}

bool String::operator== (const String& Obj) const {
	if (size_ != Obj.size_) {
		return false;
	}

	for (size_t i = 0; i < size_; ++i) {
		if (body_[i] != Obj.body_[i]) {
			return false;
		}
	}

	return true;
}

String& String::operator+= (const String& Obj) {
	if (capacity_ < size_ + Obj.size_) {
		Incr_Memory(Obj.size_);
	}

	memcpy(body_ + size_, Obj.body_, Obj.size_);
	size_ += Obj.size_;

	return *this;
}

String& String::operator+= (const char c) {
	if (capacity_ < size_ + 1) {
		Incr_Memory(1);
	}

	body_[size_] = c;
	++size_;

	return *this;
}

String& String::operator+ (const String& Obj) const {
	String Obj_res = *this;
	return Obj_res += Obj;
}

std::istream& operator>> (std::istream& in, String &Obj) {
	delete[] Obj.body_;

	char c;
	while (in.read(&c, 1)) {
		if (c == ' ' || c == '\0' || c == '\n') {
			break;
		}

		Obj.push_back(c);
	}
	
	return in;
}

std::ostream& operator<< (std::ostream& out, const String &Obj) {
	for (size_t i = 0; i < Obj.size_; ++i) {
		std::cout << Obj.body_[i];
	}
	std::cout << '\n';

	return out;
}

bool String::empty() {
	return size_ == 0 ? true : false;
}

// --------------------------------------------- Реализация методов для работы с классом ------------------------------------------------
void String::Incr_Memory(size_t add_num) {
	if (size_ + add_num <= capacity_) {
		return;
	}

	body_ = (char*)realloc(body_, 2 * (size_ + add_num) * sizeof(char));
	assert(body_ != nullptr);

	capacity_ = 2 * (size_ + add_num);
}

void String::Red_Memory(size_t sub_num) {
	if (capacity_ - sub_num < size_) {
		Incr_Memory(sub_num);
	}

	if (size_ + sub_num <= capacity_ / 4) {
		capacity_ /= 2;

		body_ = (char*)realloc(body_, capacity_ * sizeof(char));
		assert(body_ != nullptr);
	}
}

void String::pop_back() {
	assert(size_ != 0);

	Red_Memory(1);

	body_[size_ - 1] = '\0';
	--size_;
}

char* String::front() const {
	return body_;
}

char* String::back() const {
	return body_ + size_ - 1;
}

size_t String::find(const String &Obj) const {
	if (Obj.size_ > size_) {
		return size_;
	}

	size_t i = 0;
	for (; i < size_ - Obj.size_ + 1; ++i) {
		if (!strncmp(body_ + i, Obj.body_, Obj.size_)) {
			return i;
		}
	}

	return i;
}

size_t String::rfind(const String &Obj) const {
	if (Obj.size_ > size_) {
		return size_;
	}
	
	for (size_t i = size_ - Obj.size_; i > -1; --i) {
		if (!strncmp(body_ + i, Obj.body_, Obj.size_)) {
			return i;
		}
	}
	
	return size_;
}

String& String::substr(size_t ix, size_t count) {
	assert(ix + count - 1 < size_);

	String substr(count);
	memcpy(substr.body_, body_ + ix, count);
	substr.size_ = count;

	return substr;
}
void String::clear() {
	size_ = 0;
	capacity_ = 0;

	delete[] body_;
	body_ = nullptr;
}

// --------------------------------------------------------------------------------------------------------------------------------

int main() {
	
	
	return 0;
}
