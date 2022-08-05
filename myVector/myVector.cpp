#include <iostream>
#include <Vector>
#include <initializer_list>
#include <stdexcept>
template<class T>
class Vector
{
public:
	class Iterator;

	Vector() {
		capacity_ = 1;
		arr_ = new T[1];
	}
	Vector(size_t size) : size_(size), capacity_(size_ * 2)
	{
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
		if (pos >= size_) {
			//???????????
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
		return arr_ + size_;
	}

	bool empty() {
		return size_ ? true : false;
	}
	size_t size() const {
		return size_;
	}
	void reserve(size_t new_cap) {
		T* temp = arr_;
		capacity_ = new_cap;
		arr_ = new T[capacity_];

		if(new_cap >= size_){
			for (size_t i = 0; i < size_; ++i)
				arr_[i] = temp[i];
		}
		else {
			size_ = new_cap;
			for (size_t i = 0; i < capacity_; ++i)
				arr_[i] = temp[i];
		}
		
		delete[] temp;
	}
	size_t capacity() const {
		return capacity_;
	}

	void clear() {
		size_ = 0;
	}
	void insert(T pos, T value) {
		newCapacity(size_);
		for (size_t i = size_; i > pos; --i) {
			arr_[i] = arr_[i - 1];
		}
		arr_[pos] = value;
		++size_;
	}
	Iterator insert(Iterator pos, T value) {
		newCapacity(size_);
		for (size_t i = size_; i > *pos; --i) {
			arr_[i] = arr_[i - 1];
		}
		arr_[*pos] = value;
		++size_;
		return pos;
	}
	void erase(size_t pos) {
		for (size_t i = pos; i < size_; ++i) {
			arr_[i] = arr_[i + 1];
		}
		--size_;
	}
	
	Iterator* erase(T* pos) {

	}
	//T* erase(T* begin, T* end);
	void push_back(T value) {
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

	void pop_back() {
		--size_;
	}
	void pop_front() {
		for (size_t i = 0; i < size_; ++i) {
			arr_[i] = arr_[i + 1];
		}
		--size_;
	}
	void resize(size_t newSize) {
		newCapacity(newSize);

		if (newSize < size_){
			size_ = newSize;
		}
		else {
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
		
	}
	friend std::ostream& operator<< (std::ostream s, const Vector<T>& n);
	class Iterator
	{
	public:
		Iterator(T* cur) : cur_(cur) {}
		~Iterator() {
			delete cur_;
		}
		T& operator+ (int i) { return *(cur_ + i); }
		T& operator- (int i) { return *(cur_ - i); }

		T& operator++ (int) { return *(cur_++); }
		T& operator-- (int) { return *(cur_--); }
		T& operator++ () { return *(++cur_); }
		T& operator-- ()	{ return *(--cur_); }

		bool operator!= (const Iterator& other) { return cur_ != other.cur_; }
		bool operator== (const Iterator& other) { return cur_ == other.cur_; }

		T& operator* () { return *cur_; }

		
	private:
		T* cur_;
	};

	
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

template<typename T>
std::ostream& operator<< (std::ostream s, const Vector<T>& n)
{
	s << Vector<T>::cur_[n];
}

int main()
{

	std::vector<int> a{ 1,2,3,4,5 };

	Vector<int> v{ 1,2,3,4,5 };
	auto it = Vector<int>::Iterator(v.begin());
	//v.insert(it, 2);
	
}