#ifndef LymphV_H
#define LymphV_H

#include <bits/stdc++.h>
using namespace std;

namespace LymphV
{
	#define LymphVersion 20190328

	#define FOR(x,y) for (int x = 0; x < y; ++x)
	#define For(x,y,z) for (int x = y; x <= z; ++x)
	#define Ffor(x,y,z) for (int x = y; x <= z; ++x)
	#define Bfor(x,y,z) for (int x = y; x >= z; --x)

	#define ms(x,y) memset (x, y, sizeof(x))
	#define MS(x,y) memset (x, y, sizeof(x))
	#define zero(x) (((x) > 0 ? (x) : -(x)) < EPS)

	#define F first
	#define S second
	#define pb push_back

	#if defined(LocalLymphV) && defined(DebugLymphV)
	#define debug(x) cerr << __FILE__ " line" << __LINE__ << ": " << #x << " = " << repr(x) << endl
	#else
	#define debug(x) // /##/
	#endif

	///debug string
	template <typename T>
	inline string repr (const T & t)
	{
		stringstream ss;
		ss << t;
		return ss.str();
	}
	inline string repr (const string & s)
	{
		stringstream ss;
		ss << "\"";
		FOR(i,s.size())
		switch (s[i])
		{
		case '\n' : ss << "\\n"; break;
		case '\"' : ss << "\\\""; break;
		case '\t' : ss << "\\t"; break;
		case '\r' : ss << "\\r"; break;
		case '\\' : ss << "\\\\"; break;
		case '\0' : ss << "\\x00"; break;
		case '\f' : ss << "\\f"; break;
		default : ss << s[i];
		}
		ss << "\"";
		return ss.str();
	}
	inline string repr (const char * const s){return repr(string(s));}
	inline string repr (char * s) {return repr(string(s));}
	template <typename T, int N>
	inline string repr(const T (& ts) [N])
	{
		return repr(vector<T>(ts,ts+N));
	}
	inline string repr (const char & c)
	{
		return repr(string(1,c));
	}

	typedef long long ll;
	typedef unsigned long long ull;
	typedef pair<int,int> pii;
	typedef pair<ll,int> pli;
	typedef vector<int> vi;
	typedef map<string,int> msn;

	static const double PI = acos(-1.0);

	static const double EPS = 1e-8;
	static const int MAX_N = 1e5 + 5;
	static const ll MOD = 1e9 + 7;
	static const int INF = 0x3f3f3f3f;

	static char ans[2][5] = {"NO", "YES"};
	static int di[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};

	template <typename T>
	inline T sqr (T x) { return x * x;}

	/// create a random num [0,n)
	inline int ran (int n) {return rand() % n;}

	#if __cplusplus >= 201103L
	///python.print
	inline void print () {cout << endl;}
	template<typename Head, typename... Tail>
	void print(const Head & head, const Tail & ... tail)
	{
		cout<< head << " ";
		print(tail...);
	}
	#else
	inline void print () {cout << endl;}
	template <typename T>
	inline void print (const T & a) {cout << a << endl;}
	template <typename T1, typename T2>
	inline void print (const T1 & a, const T2 & b) {cout << a << " " << b << endl;}
	#endif

	///read file
	inline string readFile(const string& sFileName)
	{
		string rst = "";
		FILE* f = fopen(sFileName.c_str(), "rb");
		if (!f) return rst;

		fseek(f, 0, SEEK_END);
		int size = ftell(f);
		fseek(f, 0, SEEK_SET);

		char* buf = new char[size];
		fread(buf, 1, size,f);
		fclose(f);

		rst = string(buf, size);
		delete[] buf;

		return rst;
	}

}
#endif //LymphV_H
