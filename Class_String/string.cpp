
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>

// -------------------------------------------------- Класс String и его методы --------------------------------------------------

class String {
public:
	/* Методы для создания и удаления объектов */
	String(); // конструктор по-умолчанию

	explicit String(const char*); // конструктор от C-style строки
	explicit String(size_t); // конструктор с 1 параметром
	explicit String(size_t, char); // конструктор с 2 параметрами

	String(const String &); // конструктор копирования
	String& operator= (const String&); // оператор присваивания 
	
	/* Методы для получения информации об объекте класса */
	char operator[] (size_t) const; // получение элемента строки по индексу
	size_t length() const; // получение длины строки

	void push_back(char); // добавление элемента в конец строки

	std::istream& operator>> (std::istream&); // переопределение оператор потокового ввода
	std::ostream& operator<< (std::ostream&) const; // переопределение оператор потокового вывода

	bool empty(); // проверка на пустоту строки

	/* Методы для изменения объекта класса */
	void pop_back(); // удаление последнего элемента строки

	char* front() const; // возвращение указателя на первый элемент строки
	char* back() const; // возвращение указателя на последний элемент строки

	String& operator+= (const String&); // конкатенация с изменением объекта
	String& operator+ (const String&) const; // конкатенация с получением нового объекта

	size_t find(const char*); // нахождение самого левого вхождения подстроки
	size_t rfind(const char*); // нахождение самого правого вхождения подстроки

	char* substr(size_t, size_t); // возвращение подстроки, начинающаяся с определенного индекса, какой-то длины
	void clear(); // освобождение памяти из-под строки

private:
	char* body_; // указатель на начало строки
	size_t size_; // реальный размер
};

// ---------------------------------------- Конструкторы / Оператор присваивания  ----------------------------------------
String::String() {
	size_ = 1;

	body_ = new char[size_];
	body_[0] = '\0';
}

String::String(size_t size) :
	size_(size)
{
	body_ = new char[size_];
}

String::String(size_t size, char c) :
	String::String(size)
{
	for (size_t i = 0; i < size_; ++i) {
		body_[i] = c;
	}
}

String::String(const char* str) :
	size_(strlen(str))
{
	body_ = new char[size_];
	for (size_t i = 0; i < size_; ++i) {
		body_[i] = str[i];
	}
}

String::String(const String &Obj):
	size_(Obj.size_)
{
	body_ = new char[size_];
	for (size_t i = 0; i < size_; ++i) {
		body_[i] = Obj.body_[i];
	}
}

String& String::operator= (const String& Obj) {
	if (this == &Obj) {
		return *this;
	}

	delete[] body_;
	
	body_ = new char[Obj.size_];
	size_ = Obj.size_;
	for (size_t i = 0; i < size_; ++i) {
		body_[i] = Obj.body_[i];
	}

	return *this;
}

// ---------------------------------------- Реализация методов для получения информации о классе --------------------------------------
char String::operator[] (size_t ix) const {
	return body_[ix];
}

size_t String::length() const {
	return size_;
}

void String::push_back(char c) {
	body_ = (char*)realloc(body_, (size_ + 1) * sizeof(char));

	assert(body_ != NULL);
	body_[size_] = c;

	++size_;
}

String& String::operator+= (const String& Obj) {
	body_ = (char*)realloc(body_, (size_ + Obj.size_) * sizeof(char));
	assert(body_ != NULL);

	for (size_t i = size_; i < size_ + Obj.size_; ++i) {
		body_[i] = Obj.body_[i - size_];
	}
	size_ += Obj.size_;

	return *this;
}

String& String::operator+ (const String& Obj) const {
	String Obj_res = *this;
	return Obj_res += Obj;
}

std::istream& String::operator>> (std::istream& in) {
	size_t size;
	std::cin >> size;

	delete[] body_;
	body_ = new char[size];
	for (size_t i = 0; i < size; ++i) {
		std::cin >> body_[i];
	}

	size_ = size;
	return in;
}

std::ostream& String::operator<< (std::ostream& os) const {
	std::cout << size_ << '\n';

	for (size_t i = 0; i < size_; ++i) {
		std::cout << body_[i];
	}

	return os << '\n';
}

bool String::empty() {
	return size_ == 0 ? true : false;
}

// --------------------------------------------- Реализация методов для работы с классом ------------------------------------------------

void String::pop_back() {
	body_ = (char*)realloc(body_, (size_ - 1) * sizeof(char));
	assert(body_ != NULL);

	--size_;
}

char* String::front() const {
	return body_;
}

char* String::back() const {
	return body_ + size_ - 1;
}

size_t String::find(const char* substr) {
	bool indicator = false;
	size_t ix = 0;

	for (; ix < size_ - strlen(substr) + 1 && !indicator; ++ix) {
		for (size_t jx = 0; jx < strlen(substr); ++jx) {
			if (body_[ix + jx] != substr[jx]) {
				break;
			}

			if (jx == strlen(substr) - 1) {
				indicator = true;
			}
		}
	}

	return ix;
}

size_t String::rfind(const char* substr) {
	bool indicator = false;
	size_t ir = size_;

	for (size_t ix = 0; ix < size_ - strlen(substr) + 1; ++ix) {
		indicator = false;
		for (size_t jx = 0; jx < strlen(substr); ++jx) {
			if (body_[ix + jx] != substr[jx]) {
				break;
			}

			if (jx == strlen(substr) - 1) {
				indicator = true;
			}
		}

		if (indicator) {
			ir = ix;
		}
	}

	return ir;
}

char* String::substr(size_t ix, size_t count) {
	assert(ix + count - 1 < size_);

	char* substr = new char[count + 1];
	for (size_t i = ix; i < ix + count; ++i) {
		substr[i] = body_[i - ix];
	}
	substr[count - 1] = '\0';

	return substr;
}

void String::clear() {
	delete[] body_;
}

// --------------------------------------------------------------------------------------------------------------------------------

int main() {
	

	return 0;
}
