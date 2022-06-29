#include <iostream>
#include <Vector>
#include <initializer_list>


template<class T>
class Vector
{
public:
	Vector() {
		capacity_ = 1;
		arr_ = new T[1];
	}
	Vector(int size) : size_(size)
	{
		capacity_ = size_;
		arr_ = new T[size_]{};
	}
	template<class T1>
	Vector(std::initializer_list<T1> v):Vector(v.size()) {
		int count = 0;
		for (auto& element : v)
		{
			arr_[count] = element;
			++count;
		}
	}
	Vector(T count, T value) {
		arr_ = new T[count];
		size_ = count;
		capacity_ = count;

		for (size_t i = 0; i < count; ++i)
		{
			arr_[i] = value;
		}
	}

	//template<class T1>
	//Vector(T1* begin, T1* end);

	// Почему нельзя Vector(const Vector& other)
	Vector(Vector& other) {
		delete[] arr_;
		arr_ = new T[other.capacity()];
		for (size_t i = 0; i < other.size(); ++i)
		{
			arr_[i] = other.arr_[i];
		}
		size_ = other.size();
		capacity_ = other.capacity();
	}
	Vector& operator=(const Vector& other) {
		delete[] arr_;
		arr_ = new T[other.capacity()];
		for (size_t i = 0; i < other.size(); ++i)
		{
			arr_[i] = other.arr_[i];
		}
		size_ = other.size();
		capacity_ = other.capacity();
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
	Vector& operator=(const Vector&& other) {
		delete[] arr_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		arr_ = other.arr_;

		other.size_ = 0;
		other.capacity_ = 0;
		other.arr_ = nullptr;
		
	}
	~Vector() {
		delete[] arr_;
	}
	

	T* begin() {
		return &arr_[0];
	}
	T* end() {
		return &arr_[size_];
	}
	void push_back(int value) {
		newCapacity(size_);
		arr_[size_] = value;
		++size_;
	}
	void push_front(T value) {
		newCapacity(size_);
		for (size_t i = size_ ; i > 0; --i)
		{
			arr_[i] = arr_[i - 1];
		}
		++size_;
		arr_[0] = value;
	}

	//template<typename T1>
	//void emplace_back(T1 value); // подумайте как реализовать этот метод(place in)

	//T* insert(T*pos, T value) 
	void insert(T pos, T value)	{
		newCapacity(size_);
		for (size_t i = size_; i > pos; --i) {
			arr_[i] = arr_[i - 1];
		}
		arr_[pos] = value;
		++size_;
	}
	void erase(T pos) {
		for (size_t i = pos; i < size_; ++i) {
			arr_[i] = arr_[i + 1];
		}
		--size_;
	}
	//T* erase(size_t pos);
	//T* erase(T* pos);
	//T* erase(T* begin, T* end);


	T back() {
		return arr_[size_ - 1];
	}
	T front() {
		return arr_[0];
	}
	T& operator[](size_t index) {
		return arr_[index];
	}
	const T& operator[](size_t index) const {
		return arr_[index];
	}
	void resize(size_t newSize) {
		newCapacity(newSize);
		T* temp = arr_;
		arr_ = new T[capacity_];

		for (size_t i = 0; i < newSize; ++i)
		{
			if (i < size_)
			{
				arr_[i] = temp[i];
			}
			else {
				arr_[i] = 0;
			}
		}
		size_ = newSize;

		delete[] temp;
	}
	void reserve(size_t new_cap) {
		T* temp = arr_;
		capacity_ = new_cap;
		arr_ = new T[capacity_];
		for (size_t i = 0; i < size_; ++i)
			arr_[i] = temp[i];

		delete[] temp;
	}
	size_t capacity() {
		return capacity_;
	}
	size_t size() {
		return size_;
	}
	bool empty() {
		return size_ ? true : false;
	}



protected:
	void newCapacity(size_t size) {
		if (size >= capacity_)	{
			T* temp = arr_;
			capacity_ *= 2;
			arr_ = new T[capacity_];
			for (size_t i = 0; i < size_; ++i)
				arr_[i] = temp[i];

			delete[] temp;
		}
	}

	

private:
	T* arr_;
	size_t size_{};
	size_t capacity_{};
};


int main()
{

	//std::vector<int> v(2,3);
	Vector<int> v{1,2,3,4,5};
	Vector<int> v1 = std::move(v);
	for (size_t i = 0; i < v1.size(); ++i)
	{
		std::cout << v1[i];
	}
}

