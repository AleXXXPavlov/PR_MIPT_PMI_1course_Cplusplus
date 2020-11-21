#pragma once

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

	String(const String&); // конструктор копирования
	String& operator= (const String&); // оператор присваивания от обьекта класса
	String& operator= (const char*); // оператор присваивания от строки

	~String(); // деструктор

	/* Методы для получения информации об объекте класса */
	size_t length() const; // получение длины строки

	friend std::istream& operator>> (std::istream&, String&); // переопределение оператор потокового ввода
	friend std::ostream& operator<< (std::ostream&, const String&); // переопределение оператор потокового вывода

	bool empty(); // проверка на пустоту строки

	/* Методы для изменения объекта класса */
	char& operator[] (size_t); // получение элемента неконстантной строки по индексу
	const char& operator[] (size_t) const; // получение элемента константной строки по индексу

	void Incr_Memory(size_t); // достижение необходимого минимума capacity
	void Red_Memory(size_t); // достижение необходимого максимума capacity
	void resize(size_t, const char); // изменение длины строки

	void push_back(const char); // добавление элемента в конец строки
	String& append(size_t, const char); // добавление какого-то количества элементов
	String& append(const String&, size_t, size_t); // добавление какого-то количества элементов некоторой строки, начиная с некоторого индекса
	void pop_back(); // удаление последнего элемента строки

	char& front(); // возвращение указателя на первый элемент неконстантной строки
	char& back(); // возвращение указателя на последний элемент неконстантной строки
	const char& front() const; // возвращение указателя на первый элемент константной строки
	const char& back() const; // возвращение указателя на последний элемент константной строки

	size_t find(const String&) const; // нахождение самого левого вхождения подстроки
	size_t rfind(const String&) const; // нахождение самого правого вхождения подстроки

	String substr(size_t, size_t) const; // возвращение подстроки, начинающаяся с определенного индекса, какой-то длины
	void clear(); // освобождение памяти из-под строки

	// Арифметические операторы
	bool operator== (const String&) const;
	bool operator!= (const String&) const;
	bool operator< (const String&) const;
	bool operator> (const String&) const;
	bool operator<= (const String&) const;
	bool operator>= (const String&) const;

	String& operator+= (const String&); // конкатенация с изменением объекта
	String& operator+= (const char); // конкатенация с одним символом с изменением объекта

private:
	char* body_ = nullptr; // указатель на начало строки
	size_t size_ = 0; // реальный размер
	size_t capacity_ = 0; // максимальный размер
};
