#ifndef __HASHMAP_HPP__
#define __HASHMAP_HPP__

namespace mstl {

	/* START PAIR STRUCT */

	template <class FirstType, class SecondType>
	struct pair {
		FirstType first;
		SecondType second;
	};

	template <class T, class T1>
	void AddFirst(pair<T, T1>* obj, T value) {
		obj->first = value;
	}

	template <class T, class T1>
	void AddSecond(pair<T, T1>* obj, T1 value) {
		obj->second = value;
	}

	template <class T, class T1>
	pair<T, T1> Add(T value_first, T1 value_second) {
		pair<T, T1> obj;

		/*TODO: Clean this up.*/

		obj.first = value_first;
		obj.second = value_second;
		return obj;
	}

	/*	 END PAIR STRUCT	*/
	/*	 START HASHMAP CLASS*/

	template <class Type1, class Type2>
	class HashMap {
	private:
		pair<Type1, Type2> Pair;
		pair<Type1, Type2>* arr; // array to store the values in.

		pair<Type1, Type2>* buffer; // fixed by putting pair ptr instead of void*

		std::size_t capacity;
		std::size_t space;
	private:
		using type = pair<Type1, Type2>;
		using ptr = pair<Type1, Type2>*;
	private:
		void resize(size_t size) {
			buffer = new type[capacity];

			for (unsigned int i = 0; i < capacity; i++) {
				buffer[i] = arr[i];
			}
			delete[] arr;

			arr = new type[size];

			for (unsigned int i = 0; i < capacity; i++) {
				arr[i] = buffer[i];
			}
			delete[] buffer;
			buffer = nullptr;

			capacity = size;
		}
		void Push(const type& value) {
			if (space == capacity) {
				resize(space + capacity / 2);
			}
			arr[space] = value;
			space++;
		}

	public:
		HashMap()
			: arr(nullptr), buffer(nullptr), capacity(2), space(0) {
			arr = new pair<Type1, Type2>[capacity];
		}
		~HashMap() {
			assert(arr == nullptr, "Array is already deleted!\n");
			delete[] arr;
		}
	public:

		void add(const Type1& first, const Type2& second) {
			Pair = Add<Type1, Type2>(first, second);
			Push(Pair);
		}

		HashMap& operator [](Type1 value) {
			mstl::AddFirst(&Pair, value);
			return *this;
		}

		HashMap& operator =(Type2 value) {
			mstl::AddSecond(&Pair, value);
			Push(Pair);
			return *this;
		}

	public:
		class iterator {
		private:
			using ref_iter = iterator&;
			using type = pair<Type1, Type2>;
			using ptr = pair<Type1, Type2>*;
			using ref = pair<Type1, Type2>&;
		public:
			ptr array;
			size_t ssize;
		public:
			iterator(ptr obj, size_t size) : array(obj), ssize(size) {}
			iterator() = default;
		public:
			inline bool operator !=(const iterator& obj) {
				return this->array != obj.array;
			}
			inline bool operator ==(const iterator& obj) {
				return this->array == obj.array;
			}

			inline ref_iter operator ++(int) {
				++(*this);
				return *this;
			}

			inline ref_iter operator ++() {
				this->array++;
				return *this;
			}

			inline ref operator *() { // TODO: edit this <<<<<<<<<< operator for alphabetic printing
				return *array;
			}

			inline ptr operator ->() const {
				return array;
			}

		}; // iterator

	public:
		inline iterator begin() const {
			return iterator({ arr, 0 });
		}

		inline iterator end() const {
			return iterator({ &arr[space], space });
		}

	}; // HashMap

};

#endif /* __HASHMAP_HPP__ */