#ifndef VRange_H
#define VRange_H

#include "LymphV.h"

namespace LymphV
{
	///python.range
	class range
	{
	protected:
		int start, stop, step;;

	public:
		class const_iterator : public std::iterator<input_iterator_tag, int>
		{
			int now;
			const range & rng;
			void stdNow ()
			{
				if (rng.step > 0 && now > rng.stop || rng.step < 0 && now < rng.stop)
					now = rng.stop;
			}
		public:
			const_iterator (const range & rng) : rng(rng), now(rng.start) {stdNow();}
			const_iterator (const range & rng, int now) : rng(rng), now(now) {stdNow();}

			const int & operator* () const {return now;}

			const_iterator & operator++ ()
			{
				assert (rng.step);
				now += rng.step;
				stdNow();
				return *this;
			}
			const_iterator operator++ (int)
			{
				const_iterator res = *this;
				++*this;
				return res;
			}

			bool operator == (const const_iterator & value) {return now == value.now;}
			bool operator != (const const_iterator & value) {return now != value.now;}
		} ;
		typedef int value_type;
		typedef const_iterator iterator;

		range(int start, int stop, int step = 1) : start(start), stop(stop), step(step) {assert(step);}
		range(int stop) : start(0), stop(stop), step(1) {}
		virtual ~range() {step = 0;}

		const_iterator begin() const {return const_iterator(*this);}
		const_iterator end() const {return const_iterator(*this, stop);}

		operator string() const
		{
			stringstream res;
			res << "range(" << start << "," << stop;
			if (step != 1) res << ", " << step;
			res << ")";
			return res.str();
		}
	};

	inline ostream & operator<< (ostream & out, const range & r)
	{
		return out << string(r);
	}
}

#endif //VRange_H