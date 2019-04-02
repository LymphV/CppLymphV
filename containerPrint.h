#ifndef VContainerPrint_H
#define VContainerPrint_H

#include "LymphV.h"

namespace LymphV
{
	///python.print(tuple)
	template<typename L, typename R>
	ostream & operator<< (ostream & out, const pair<L,R> & p)
	{
		return out << "(" << repr(p.first) << ", " << repr(p.second) << ")";
	}

	///python.print(list)
	template<typename T>
	ostream & operator<< (ostream & out, const vector<T> & v)
	{
		out << "[";
		FOR(i, v.size()) out << (i ? ", " : "") << repr(v[i]);
		return out << "]";
	}
	
	///python.print(list)
	template<typename T>
	ostream & operator<< (ostream & out, const list<T> & l)
	{
		out << "[";
		for (typename list<T>::const_iterator it = l.begin(); it != l.end(); ++it)
			out << (it == l.begin() ? "" : ", ") << repr(*it);
		return out << "]";
	}

	///python.print(dict)
	template<typename K, typename V>
	ostream & operator<< (ostream & out, const map<K,V> & mp)
	{
		out << "{";
		for (typename map<K,V>::const_iterator it = mp.begin(); it != mp.end(); ++it)
			out << (it == mp.begin() ? "" : ", ") << repr(it->first) << " : " << repr(it->second);
		return out << "}";
	}
	
	#if __cplusplus >= 201103L
	///python.print(dict)
	template<typename K, typename V>
	ostream & operator<< (ostream & out, const unordered_map<K,V> & mp)
	{
		out << "{";
		for (typename unordered_map<K,V>::const_iterator it = mp.begin(); it != mp.end(); ++it)
			out << (it == mp.begin() ? "" : ", ") << repr(it->first) << " : " << repr(it->second);
		return out << "}";
	}
	#endif // __cplusplus

	///python.print(set)
	template<typename T>
	ostream & operator<< (ostream & out, const set<T> & s)
	{
		if (s.empty()) return out << "set()";
		for (typename set<T>::const_iterator it = s.begin(); it != s.end(); ++it)
			out << (it == s.begin() ? "{" : ", ") << repr(*it);
		return out << "}";
	}
	
	#if __cplusplus >= 201103L
	///python.print(set)
	template<typename T>
	ostream & operator<< (ostream & out, const unordered_set<T> & s)
	{
		if (s.empty()) return out << "set()";
		for (typename unordered_set<T>::const_iterator it = s.begin(); it != s.end(); ++it)
			out << (it == s.begin() ? "{" : ", ") << repr(*it);
		return out << "}";
	}
	#endif // __cplusplus
}


#endif //VContainerPrint_H