
#include "String.h"

// ---------------------------------------- Конструкторы / Оператор присваивания / Деструктор ----------------------------------------

String::String(char c) :
	size_(1), capacity_(1)
{
	body_ = new char[1];
	body_[0] = c;
}

String::String(char c, size_t size = 1) :
	capacity_(size)
{
	body_ = new char[capacity_];
	memset(body_, c, size);
	size_ = capacity_;
}

String::String(const char* str) :
	capacity_(strlen(str))
{
	body_ = new char[capacity_];
	memcpy(body_, str, capacity_);
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
	
	body_ = new char[Obj.capacity_];
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
size_t String::length() const {
	return size_;
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
char& String::operator[] (size_t ix) {
	return body_[ix];
}
const char& String::operator[] (size_t ix) const {
	return body_[ix];
}

void String::Incr_Memory(size_t add_num) {
	if (size_ + add_num <= capacity_ || add_num == 0) {
		return;
	}

	char* body_c = new char[size_];
	
	delete[] body_;
	body_ = new char[2 * (size_ + add_num)];
	memcpy(body_, body_c, size_);
	
	delete[] body_c;
	
	capacity_ = 2 * (size_ + add_num);
}

void String::Red_Memory(size_t sub_num) {
	if (size_ + sub_num <= capacity_ / 4) {
		capacity_ /= 2;

		char* body_c = new char[size_];

		delete[] body_;
		body_ = new char[capacity_];
		memcpy(body_, body_c, size_);

		delete[] body_c;
	}
}

void String::resize(size_t new_size, const char c = '\0') {
	if (new_size == size_) {
		return;
	}
	if (new_size > size_) {
		Incr_Memory(new_size - size_);

		memset(body_ + size_, '\0', new_size - size_);
		size_ = new_size;
		return;
	}
	if (new_size < size_) {
		memset(body_ + new_size, '\0', size_ - new_size);
		size_ = new_size;

		Red_Memory(0);
		return;
	}
}

void String::push_back(const char c) {
	*this += c;
}

String& String::append(size_t count = 1, const char c = '\0') {
	Incr_Memory(count);

	memset(body_, c, count);
	size_ += count;

	return *this;
}

String& String::append(const String& Obj, size_t count, size_t ix = 0) {
	Incr_Memory(count);

	memcpy(body_, Obj.body_ + ix, count);
	size_ += count;

	return *this;
}

void String::pop_back() {
	assert(size_ != 0);

	Red_Memory(1);

	body_[size_ - 1] = '\0';
	--size_;
}

char& String::front() {
	return body_[0];
}
const char& String::front() const {
	return body_[0];
}

char& String::back() {
	return body_[size_ - 1];
}
const char& String::back() const {
	return body_[size_ - 1];
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
	
	for (size_t i = size_ - Obj.size_; i > 0; --i) {
		if (!strncmp(body_ + i, Obj.body_, Obj.size_)) {
			return i;
		}
		if (!strncmp(body_, Obj.body_, Obj.size_)) {
			return 0;
		}
	}
	
	return size_;
}

String String::substr(size_t ix, size_t count) const {
	assert(ix + count - 1 <= size_);

	String str_r('0', count);
	memcpy(str_r.body_, body_ + ix, count);
	str_r[count] = '\0';
	str_r.size_ = count;
	
	return str_r;
}
void String::clear() {
	size_ = 0;
	capacity_ = 0;

	delete[] body_;
	body_ = nullptr;
}

// --------------------------------------------- Реализация арифметических операторов ------------------------------------------------

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

bool String::operator!= (const String& Obj) const {
	return !(*this == Obj);
}

bool String::operator< (const String& Obj) const {
	if (size_ > Obj.size_) {
		return false;
	}
	else if (size_ < Obj.size_) {
		return true;
	}
	else {
		for (size_t i = 0; i < size_; ++i) {
			if (body_[i] > Obj.body_[i]) {
				return false;
			}
			else if (body_[i] < Obj.body_[i]) {
				return true;
			}
		}

		return false;
	}
}

bool String::operator> (const String& Obj) const {
	return !(*this < Obj) && !(*this == Obj);
}

bool String::operator<= (const String& Obj) const {
	return (*this < Obj) || (*this == Obj);
}

bool String::operator>= (const String& Obj) const {
	return !(*this < Obj) || (*this == Obj);
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

const String& operator+ (const String& Obj1, const String& Obj2) {
	String Obj_res;
	Obj_res = Obj1;
	return Obj_res += Obj2;
}
const String& operator+ (const String& Obj, const char c) {
	String Obj_res;
	Obj_res = Obj;
	return Obj_res += c;
}
const String& operator+ (const char c, const String& Obj) {
	String Obj_res;
	Obj_res = Obj;
	return Obj_res += c;
}

// --------------------------------------------------------------------------------------------------------------------------------

