#ifndef __MSTL_HPP__
#define __MSTL_HPP__

#include <iostream>
#include <initializer_list>
#include <cstdio>
#include <cstdlib>

#ifdef assert(cond, msg)
#undef assert(cond, msg)
#endif

#define assert(x, ...)									\
	do {												\
		if(!(x)) { break;								\
		}else {											\
			fprintf(stderr, __VA_ARGS__); exit(1);	\
		}												\
	}while(0)

#include <MSTL/list.hpp>
#include <MSTL/Array.hpp>
#include <MSTL/HashMap.hpp>
#include <MSTL/Vector.hpp>
#include <MSTL/Smart_ptr.hpp>

#endif /* __MSTL_HPP__ */
