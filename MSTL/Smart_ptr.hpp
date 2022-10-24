#pragma once
#ifndef __SMART_PTR_HPP__
#define __SMART_PTR_HPP__

#pragma message("TODO: Make this class much. much better.\n")

namespace mstl {

	template <class T>
	class Smart_ptr {
	private:
		T* ptr;
	public:

		Smart_ptr() // for mstl::make_ptr<T>();
			: ptr(nullptr) {}

		Smart_ptr(T* data) { // for Smart_ptr<int>(new int);
			ptr = data;
		}

		inline T& operator *() const {
			return *ptr;
		}

		inline T* operator ->() const {
			return ptr;
		}

		inline T& operator [](size_t i) {
			return ptr[i];
		}

		inline T* operator =(T* value) {
			ptr = value;
			return value;
		}

		void free() {
			assert(ptr == nullptr, "ptr is already null! Freeing again will cause a runtime error\n");
			delete ptr;
			ptr = nullptr;
		}

		~Smart_ptr() {
			assert(ptr == nullptr, "ptr is already null!!\n");
			delete ptr;
		}

	}; // Smart_ptr

	template <typename T>
	Smart_ptr<T> make_ptr() {
		return mstl::Smart_ptr<T>(new T);
	}
};

#endif /* __SMART_PTR_HPP__ */