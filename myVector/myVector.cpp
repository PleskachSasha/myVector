#include <iostream>
#include <Vector>
#include <initializer_list>
#include <stdexcept>
template<class T>
class Vector
{
public:
	class Iterator;

	Vector() : size_(0), capacity_(1) {
		arr_ = new T[capacity_];
	}
	Vector(size_t size) : size_(size), capacity_(size_)
	{
		arr_ = new T[capacity_]{};
	}
	template<class T1>
	Vector(std::initializer_list<T1> v):Vector(v.size()) {
		int count = 0;
		for (const auto& element : v)
		{
			arr_[count] = element;
			++count;
		}
	}
	Vector(T count, T value) : size_(count), capacity_(count) {
		arr_ = new T[count];
		for (size_t i = 0; i < size_; ++i)
		{
			arr_[i] = value;
		}
	}
	Vector(const Vector& other) {
		if (this != &other) {
			delete[] arr_;

			arr_ = new T[other.capacity()];

			for (size_t i = 0; i < other.size(); ++i)
			{
				arr_[i] = other.arr_[i];
			}

			size_ = other.size();
			capacity_ = other.capacity();
		}
	}
	Vector& operator=(const Vector& other) {
		if (this != &other) {
			delete[] arr_;

			arr_ = new T[other.capacity()];

			for (size_t i = 0; i < other.size(); ++i)
			{
				arr_[i] = other.arr_[i];
			}

			size_ = other.size();
			capacity_ = other.capacity();
		}
		return *this;
	}
	Vector(Vector&& other) noexcept {
		delete[] arr_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		arr_ = other.arr_;

		other.size_ = 0;
		other.capacity_= 0;
		other.arr_ = nullptr;
		
	}
	Vector& operator=(const Vector&& other) noexcept {
		delete[] arr_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		arr_ = other.arr_;

		other.size_ = 0;
		other.capacity_ = 0;
		other.arr_ = nullptr;
		
		return *this;
	}
	~Vector() {
		delete[] arr_;
	}

	T& at(const size_t pos) {
		if (pos >= size_) 
			throw std::out_of_range("Invalid index");

		return arr_[pos];
	}
	const T& at(const size_t pos) const {
		if (pos >= size_) {
			throw std::out_of_range("Invalid index");
		}
		return arr_[pos];
	}

	T& operator[](const size_t index) {
		return arr_[index];
	}
	const T& operator[](const size_t index) const{
		return arr_[index];
	}
	T& front() {
		return arr_[0];
	}
	T& back() {
		return arr_[size_ - 1];
	}

	Iterator begin() {
		return arr_;
	}
	Iterator end() {
		return (arr_ + size_);
	}

	bool empty() {
		return begin() == end();
	}
	size_t size() const {
		return size_;
	}
	void reserve(size_t new_cap) {
		if (new_cap >= capacity_) {
			T* temp = arr_;
			capacity_ = new_cap;
			arr_ = new T[new_cap];
			for (size_t i = 0; i < size_; ++i)
				arr_[i] = temp[i];
			delete[] temp;
		}
	}
	size_t capacity() const {
		return capacity_;
	}
	void shrink_to_fit() {
		T* temp = arr_;
		capacity_ = size_;
		arr_ = new T[size_];

		for (size_t i = 0; i < size_; ++i)
			arr_[i] = temp[i];

		delete[] temp;
	}

	void clear() {
		for (size_t i = 0; i < size_; ++i)
			arr_[i].~T();
		
		size_ = 0;
	}
	void insert(size_t pos, T value) {
		if (size_ >= capacity_)
			reserve(capacity_ * 2);
		for (size_t i = size_; i > pos; --i) {
			arr_[i] = arr_[i - 1];
		}
		arr_[pos] = T(value);
		++size_;
	}
	Iterator insert(Iterator pos, T value) {
		int index = (reinterpret_cast<size_t>(&(*pos)) - reinterpret_cast<size_t>(&(*begin()))) / sizeof(T);
		insert(index, value);
		
		return arr_ + index;
	}
	Iterator insert(Iterator pos, int count, T value) {
		int index = (reinterpret_cast<size_t>(&(*pos)) - reinterpret_cast<size_t>(&(*begin()))) / sizeof(T);
		while (count)
		{
			insert(index, value);
			--count;
		}
		
		return arr_ + index;
	}
	
	void erase(size_t pos) {
		arr_[pos].~T();
		for (size_t i = pos; i < size_; ++i) {
			arr_[i] = arr_[i + 1];
		}
		--size_;
	}
	Iterator erase(Iterator pos) {
		int index = (reinterpret_cast<size_t>(&(*pos)) - reinterpret_cast<size_t>(&(*begin()))) / sizeof(T);
		//??
		//arr_[index].~T();
		for (size_t i = index; i < size_; ++i) {
			arr_[i] = arr_[i + 1];
		}
		//??
		arr_[size_-1].~T();
		--size_;

		return pos;
	}
	Iterator erase(Iterator begin_it, Iterator end_it){

		int first_index = (reinterpret_cast<size_t>(&(*begin_it)) - reinterpret_cast<size_t>(&(*begin()))) / sizeof(T);
		int second_index = (reinterpret_cast<size_t>(&(*end_it)) - reinterpret_cast<size_t>(&(*begin()))) / sizeof(T);

		for (size_t i = first_index, j = second_index; j <= size_; ++j, ++i ) {
			arr_[i] = arr_[j];
			for (int k = 0; k < size(); k++)
			{
				std::cout << arr_[k] << " ";
			}
			std::cout << std::endl;
		}

		for (size_t i = second_index; i < size_; i++)
		{
			arr_[i].~T();
		}

		size_ = size_ - (second_index - first_index);
		return begin_it;
	}

	void push_back(T value) {
		if (size_ >= capacity_)
			reserve(capacity_ * 2);
		arr_[size_] = T(value);
		++size_;
	}
	void push_front(T value) {
		if (size_ >= capacity_)
			reserve(capacity_ * 2);
		for (size_t i = size_ ; i > 0; --i)
		{
			arr_[i] = arr_[i - 1];
		}
		arr_[0] = T(value);
		++size_;
	}
	
	template< class... Args >
	void emplace_back(Args&&... args) {
		if (size_ == capacity_) {
			T* temp = arr_;
			capacity_ *= 2;
			arr_ = new T[capacity_];

			for (size_t i = 0; i < size_; ++i)
				arr_[i] = temp[i];

			delete[] temp;
		}

		new (arr_ + size_) T(std::forward<Args>(args)...);
		++size_;
	}

	void pop_back() {
		arr_[size_].~T();
		--size_;
	}
	void pop_front() {
		arr_[0].~T();
		for (size_t i = 0; i < size_; ++i) {
			arr_[i] = arr_[i + 1];
		}
		
		--size_;
	}
	void resize(size_t newSize) {
		if (newSize != size_)
		{
			if (newSize < size_) {
				for (size_t i = newSize; i < size_; ++i)
				{
					arr_[i].~T();
				}
				size_ = newSize;
			}
			else {
				if (size_ == capacity_)
					reserve(capacity_ * 2);
				T* temp = arr_;
				arr_ = new T[capacity_];

				for (size_t i = 0; i < newSize; ++i)
				{
					if (i < size_)
					{
						arr_[i] = temp[i];
					}
					else {
						arr_[i] = T();
					}
				}
				size_ = newSize;

				delete[] temp;
			}
		}
		
	}

	friend std::ostream& operator<< (std::ostream s, const Vector<T>& n);

	class Iterator
	{
	public:
		Iterator(T* cur) : cur_(cur) {}
		~Iterator() = default;
		Iterator operator+ (int i) { return cur_ + i; }
		Iterator operator- (int i) { return cur_ - i; }

		Iterator operator++ (int) { return cur_++; }
		Iterator operator-- (int) { return cur_--; }
		Iterator operator++ ()	{ return ++cur_; }
		Iterator operator-- ()	{ return --cur_; }

		bool operator!= (const Iterator& other) { return cur_ != other.cur_; }
		bool operator== (const Iterator& other) { return cur_ == other.cur_; }
		bool operator>= (const Iterator& other) { return cur_ >= other.cur_; }
		bool operator> (const Iterator& other) { return cur_ > other.cur_; }
		bool operator< (const Iterator& other) { return cur_ < other.cur_; }

		T& operator* () { return *cur_; }

		
	private:
		T* cur_;
	};

private:
	T* arr_;
	size_t size_{};
	size_t capacity_{};
};

template<typename T>
std::ostream& operator<< (std::ostream s, const Vector<T>& n)
{
	s << Vector<T>::cur_[n];
}

int main()
{
	
}