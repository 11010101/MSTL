#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

namespace mstl {

	template <typename T>
	class vector {
	private:
		size_t vec_space;
		size_t vec_capacity;

		T* arr;
		T* tempbuff;
	public:

		vector()
			: vec_space(0), vec_capacity(2), arr(nullptr), tempbuff(nullptr) {
			arr = new T[vec_capacity];
		}

		vector(const std::initializer_list<T>& init)
			: vec_space(0), vec_capacity(2), arr(nullptr), tempbuff(nullptr) {
			arr = new T[vec_capacity]; // just start with 2 bytes;
			for (const auto& val : init) {
				push(val);
			}
		}

		void alloc(size_t size_to_alloc) {
			tempbuff = new T[vec_space];

			for (unsigned int i = 0; i < vec_space; i++) {
				tempbuff[i] = arr[i];
			}
			delete[] arr;

			arr = new T[size_to_alloc];

			vec_capacity = size_to_alloc;

			for (unsigned int i = 0; i < vec_space; i++) {
				arr[i] = tempbuff[i];
			}
			delete[] tempbuff;
		}

		void push(const T& value_to_add) {
			if (vec_space == vec_capacity) {
				alloc(vec_space + vec_capacity / 2);
			}

			arr[vec_space] = value_to_add;
			vec_space++;
		}

		void clear() {
			assert(arr == nullptr, "Array is already cleared. Clearing again will cause an abort.\n");
			delete[] arr;
			arr = nullptr;
			tempbuff = nullptr;
			vec_space = 0;
			vec_capacity = 2;
			arr = new T[vec_capacity]; // alloc 2 bytes again. dont want the destructor to be called and get a debug assertion
		}

		size_t space() const { /* returns the amount of space taken in vector. */
			return vec_space;
		}

		size_t capacity() const {
			return vec_capacity;
		}

		T* ReturnArray() const {
			return arr;
		}

		~vector() {
			assert(arr == nullptr, "Array is already cleared by clear().\n");
			delete[] arr;
		}

		/* START ITERATOR CLASS */

		class iterator {
		public:
			iterator(T* arr, size_t ssize)
				: m_data(arr), m_size(ssize) {}

		private:
			using ClassType = vector;
			using ref = T&;
			using ptr = T*;
			using type = T;
			using refIter = iterator&;

		public:
			inline iterator& operator ++() {
				this->m_data++;
				return *this;
			}

			inline ref operator *() {
				return *m_data;
			}

			inline iterator& operator++ (int) {
				++(*this);
				return *this;
			}

			inline bool operator !=(const iterator& obj) {
				return this->m_data != obj.m_data;
			}
			inline bool operator ==(const iterator& obj) {
				return this->m_data == obj.m_data;
			}
		private:
			T* m_data = NULL;
			size_t m_size;
		}; // iterator

	public:
		iterator begin() const {
			return { &arr[0], 0 };
		}
		iterator end() const {
			return iterator({ &arr[vec_space], vec_space });
		}

	}; // vector
};

#endif /* __VECTOR_HPP__ */