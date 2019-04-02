#ifndef VTraits_H
#define VTraits_H

#include "LymphV.h"

namespace LymphV
{
	///traits of iterable class
	template <typename Iterable>
	struct iterable_traits
	{
		typedef typename Iterable::value_type value_type;
		typedef typename Iterable::iterator iterator;
		typedef typename Iterable::const_iterator const_iterator;
		///more
	};

	///traits of array
	template <typename T, size_t N>
	struct iterable_traits<T[N]>
	{
		typedef T value_type;
		typedef T * iterator;
		typedef const T * const_iterator;
		///more
	};

}

#endif //VTraits_H