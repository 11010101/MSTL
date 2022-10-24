#ifndef __LIST_HPP__
#define __LIST_HPP__

#define null nullptr

namespace mstl {

	template <typename T>
	class list {
	private:
		T *TheList;
		T *buff;
		size_t len;
		size_t space_left;
	public:
		list(std::initializer_list<T> list) 
			: TheList(new T[4]), len(4), space_left(0) {

			for (auto& i : list) {
				TheList[space_left] = i;
				space_left++;
				if (space_left == len) {
					alloc(space_left + len);
				}
			}
		}
		list() 
			: TheList(new T[4]), len(4), space_left(0) {}

		void alloc(size_t size_to_alloc) {
				
				buff = new T[len];

				for (int i = 0; i < len; i++) {
					buff[i] = TheList[i];
				}

				delete[] TheList; 
				TheList = null;
				TheList = new T[size_to_alloc];
				len = size_to_alloc;

				for (int i = 0; i < space_left; i++) {
					TheList[i] = buff[i];
				}

				delete[] buff;
				buff = null;
		}

		inline void push_back(const T& data) {
			if (space_left == len) {
				alloc(space_left + len);
			}

			TheList[space_left] = data;
			space_left++;
		}

		inline void push_front(const T& data) {
			buff = new T[len++];
			buff[0] = data; // create a new index 0
			for (int i = 0; i < space_left; i++) { // buff[0] is already reserved for the data we just pushed so we'll start at index 1
				buff[i + 1] = TheList[i];
			}
			delete[] TheList;
			TheList = null;
			TheList = new T[len];
			for (int i = 0; i < space_left + 1; i++) {
				TheList[i] = buff[i];
			}
			delete[] buff;
			buff = null;
			if (space_left == len) {
				alloc(len * 3 / 2);
			}
			space_left++;
		}

		/* erases the index given and replaces that with the index after it. */
		void erase(uint32_t index) {

			assert(index >= len, "Accessing index: %d while the arraylen is: %d is illegal!\n", index, len);
			assert(TheList == null, "Cannot clear index if list is null!!\n");

			TheList[index] = NULL;

			int buf = 0;

			buff = new T[len - 1];
			for (int i = 0; i <= index - 1; i++) {
				buff[i] = TheList[i];
				buf++;
			}

			for (int i = index + 1; i < space_left; i++) {
				buff[buf] = TheList[i];
				buf++;
			}

			space_left--;
			delete[] TheList;
			TheList = null;

			TheList = new T[len - 1];
			for (int i = 0; i < space_left; i++) {
				TheList[i] = buff[i];
			}

			delete[] buff;
			buff = null;
		}

		/* Just does the destructor's job */
		void clear() {
			assert(TheList == null, "Cannot call Clear twice!!\n");
			delete[] TheList;
			TheList = null;
		}

		/* Returns the sizeof function for this list */
		inline size_t size() const {
			return sizeof(TheList);
		}

		/* Returns the amount of space taken in the list rn */
		inline size_t space() const {
			return space_left;
		}

		/* Returns the amount of elements in the array rn */
		inline size_t length() const {
			return len;
		}

		inline list& operator +=(const list& data) {
			buff = new T[len];
			for (int i = 0; i < space_left; i++) {
				buff[i] = TheList[i];
			}
			delete[] TheList;
			TheList = null;

			TheList = new T[len += data.length()];
			for (int i = 0; i < space_left; i++) {
				TheList[i] = buff[i];
			}

			delete[] buff;
			buff = null;

			int z = space_left;

			for (int i = 0; i < data.space(); i++) {
				TheList[z++] = data.TheList[i];
				if (space_left == len) {
					alloc(space_left + len);
				}
			}

			space_left += data.space();

			return *this;
		}

		/* Is just the same as push_back */
		inline list& operator =(const T& data) {
			push_back(data);
			return *this;
		}

		class iterator {
		private:
			T* arr;
			size_t size;
		public:
			iterator(T* thearr, size_t size)
				: arr(thearr), size(size) {}
			inline bool operator != (const iterator& obj) {
				return this->arr != obj.arr;
			}

			inline bool operator ==(const iterator& obj) {
				return this->arr == obj.arr;
			}

			inline T& operator *() {
				return *arr;
			}

			inline iterator& operator ++() {
				this->arr++;
				return *this;
			}

			inline iterator& operator ++(int) {
				++(*this);
				return *this;
			}

			inline T* operator ->() {
				return arr;
			}
		};
		inline iterator begin() const {
			return iterator({ &TheList[0], 0 });
		}
		inline iterator end() const {
			return iterator({ &TheList[space_left], space_left });
		}
		
		~list() {
			assert(TheList == null, "List is already null!\n");
			delete[] TheList;
		}

	};
};

#endif /* __LIST_HPP__ */