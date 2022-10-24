#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

namespace mstl {

	template <typename T, unsigned int size>
	class Array {
	private:
		T s_array[size];
		size_t space;
		/* a size_t size is not needed. the template already has that argument */
	public:

		void Push(const T& value_to_push) {
			s_array[space] = value_to_push;
			space++;

			assert(space == size, "Exceeding limit of array!\n");

		}

		Array(const std::initializer_list<T>& list) : space(0) {
			size_t idx = 0;
			for (auto& i : list) {
				s_array[idx] = i;
				if (idx == size) {
					error("Cannot put more than %I32u elements in array.\n", size);
				}
				idx++;
				space++;
				std::cout << idx << " " << space << '\n';
			}
		}

		Array()
			: space(0) {}

		inline T& operator [](size_t i) {
			return s_array[i];
		}

		size_t Space() const {
			return space;
		}

		class iterator {
		private:
			using ref_iter = iterator&;
			using ref = Array&;
			using ptr = T*;
		private:
			T* arr;
			size_t space;
		public:
			iterator(T* thearr, size_t space) : arr(thearr), space(space) {}
		public:
			inline bool operator ==(const ref obj) {
				return this->arr == obj.arr;
			}

			inline bool operator !=(const iterator obj) {
				return this->arr != obj.arr;
			}

			inline ref_iter operator ++() {
				this->arr++;
				return *this;
			}

			inline ref_iter operator ++(int) {
				++(*this); // "++(*this)" is normally not possible. but there is one overload for this. ^^^

				return *this;
			}

			inline T& operator *() {
				return *arr;
			}

		}; // iterator

	public:
		inline iterator begin() const {
			return iterator({ (T*)&s_array[0], 0 });
		}

		inline iterator end() const {
			return iterator({ (T*)&s_array[space], (size_t)space });
		}


	}; // Array

};
#endif /* __ARRAY_HPP__ */