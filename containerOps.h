#ifndef VContainerOps_H
#define VContainerOps_H

#include "LymphV.h"
#include "traits.h"
#include "containerPrint.h"

namespace LymphV
{
	#define MapCtr(T) template <typename T1, typename T2>\
		T<T2> mapCtr (const T<T1> &, const T2 &);

	#define MapMap(T) template <typename K, typename V, typename T2>\
		vector<T2> mapCtr (const T<K,V> &, const T2 &); 

	MapCtr(vector);
	MapCtr(set);
	MapCtr(list);
	MapMap(map);

	#if __cplusplus >= 201103L
	MapCtr(unordered_set);
	MapMap(unordered_map);
	#endif // __cplusplus

	template <typename T1, size_t N, typename T2>
	vector<T1> mapCtr(const T1 (&) [N], const T2 &);

	template <typename T> T unref (T &);
	
	#define vtOf(x) typename iterable_traits<x>::value_type
	#define itrOf(x) typename iterable_traits<x>::iterator
	#define citrOf(x) typename iterable_traits<x>::const_iterator
	
	///python.len
	template <typename CTR>
	inline size_t len(const CTR & container)
	{
		return container.size();
	}
	template <typename T, size_t N>
	inline size_t len (const T (& ts) [N])
	{
		return N;
	}

	///c++11.begin, c++11.end
	#if __cplusplus < 201103L
		template<typename Iterable>
		itrOf(Iterable) begin (Iterable & iterable)
		{
			return iterable.begin();
		}
		template<typename Iterable>
		citrOf(Iterable) begin (const Iterable & iterable)
		{
			return iterable.begin();
		}
		template<typename T, size_t N>
		T * begin (T (&ts) [N])
		{
			return ts;
		}

		template<typename Iterable>
		itrOf(Iterable) end (Iterable & iterable)
		{
			return iterable.end();
		}
		template<typename Iterable>
		citrOf(Iterable) end (const Iterable & iterable)
		{
			return iterable.end();
		}
		template<typename T, size_t N>
		T * end (T (&ts) [N])
		{
			return ts + N;
	}
	#endif // __cplusplus

	///python.dict.keys(dict)
	template <typename K, typename V>
	set<K> getKeySet (const map<K,V> & mp)
	{
		set<K> res;
		for (typename map<K,V>::const_iterator it = mp.begin(); it != mp.end(); ++it)
			res.insert(it->first);
		return res;
	}
	
	template <typename Iterable>
	vector<vtOf(Iterable)> toVector (const Iterable & iterable)
	{
		return vector<vtOf(Iterable)> (begin(iterable), end(iterable));
	}

	///python.set.__and__
	template <typename T>
	set<T> operator & (const set<T> & self, const set<T> & value)
	{
		set<T> res;
		for (typename set<T>::const_iterator it = self.begin(); it != self.end(); ++it)
			if (value.find(*it) != value.end())
				res.insert(*it);
		return res;
	}

	///python.set.__or__
	template <typename T>
	set<T> operator | (const set<T> & self, const set<T> & value)
	{
		set<T> res;
		for (typename set<T>::const_iterator it = self.begin(); it != self.end(); ++it)
			res.insert(*it);
		for (typename set<T>::const_iterator it = value.begin(); it != value.end(); ++it)
			res.insert(*it);
		return res;
	}

	///python.set.__iand__
	template <typename T>
	set<T> & operator &= (set<T> & self, const set<T> & value)
	{
		for (typename set<T>::const_iterator it = self.begin(); it != self.end(); ++it)
			if (value.find(*it) == value.end())
				self.erase(it);
		return self;
	}

	///python.set.__ior__
	template <typename T>
	set<T> & operator |= (set<T> & self, const set<T> & value)
	{
		for (typename set<T>::const_iterator it = value.begin(); it != value.end(); ++it)
			self.insert(*it);
		return self;
	}

	///python.sum
	template <typename K, typename V>
	K sum (const map<K,V> & container, K start = K())
	{
		for (typename map<K,V>::const_iterator it = container.begin(); it != container.end(); ++it)
			start += it->first;
		return start;
	}
	template <typename Iterable>
	vtOf(Iterable) sum (const Iterable & iterable)
	{
		return accumulate(begin(iterable), end(iterable), vtOf(Iterable) ());
	}
	template <typename Iterable, typename T>
	T sum (const Iterable & iterable, T start)
	{
		return accumulate(begin(iterable), end(iterable), start);
	}
	template <typename Iterable>
	string sum (const Iterable & iterable, char * start)
	{
		return accumulate(begin(iterable), end(iterable), string(start));
	}
	template <typename Iterable>
	string sum (const Iterable & iterable, const char * start)
	{
		return accumulate(begin(iterable), end(iterable), string(start));
	}
	#if __cplusplus >= 201103L
		class Sum
		{
		public:
			template <typename... T>
			auto operator() (const T & ... t) -> decltype(sum(t...)) {return sum(t...);}
		};
		inline Sum sum () {return Sum();}
	#endif //__cplusplus
	///end sum
	
	
	///
	#if __cplusplus >= 201103L
	template <typename FUN, typename CTR>
	auto pymap (FUN f, const CTR & container) -> decltype (mapCtr(container, f(declval<decltype(unref(*begin(container)))>())))
	{
		typedef decltype(unref(*begin(container))) value_type;
		typedef typename result_of<FUN(value_type)>::type ResValueType;
		//typedef decltype (f(declval<CTR::value_type>())) ResValueType;
		vector<ResValueType> res(len(container));
		transform(begin(container), end(container), begin(res), f);
		
		//for (auto it = begin(container); it != end(container); ++it) res.push_back(f(*it));

		return decltype(mapCtr(container, declval<ResValueType>())) (res.begin(), res.end());
	}
	#endif // __cplusplus
}

#endif //VContainerOps_H