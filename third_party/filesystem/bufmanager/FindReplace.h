#ifndef BUF_SEARCH
#define BUF_SEARCH
#include "../utils/pagedef.h"
#include <list>
#include <algorithm>

//template <int CAP_>
/*
 * FindReplace
 * simple LRU
 */

class FindReplace
{
private:
	std::list<int> q;
	int capacity;

public:
	FindReplace()
	{
		this->capacity = CAP;
		for (int i = 0; i < CAP;++i)
			q.push_front(i);
	}

	void access(int index)
	{
		auto pos = std::find(q.begin(), q.end(), index);
		if (pos != q.end())
			q.remove(index);
		q.push_front(index);
		if (q.size() > capacity)
			q.pop_back();
	}
	int find()
	{
		return q.back();
	}
	void free(int index)
	{
		q.remove(index);
	}
};
#endif
