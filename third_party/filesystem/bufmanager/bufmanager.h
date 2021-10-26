#define CAP 60000
#define MOD CAP
#include "../fileio/FileManager.h"
#include <unordered_map>
#include "FindReplace.h"
#include <algorithm>
#include <utility>

namespace std
{
	template <>
	struct hash<std::pair<int, int> >
	{
		std::size_t operator()(std::pair<int, int> const &s) const noexcept
		{
			std::size_t h1 = std::hash<int>{}(s.first);
			std::size_t h2 = std::hash<int>{}(s.second);
			return h1 ^ (h2 << 1); // or use boost::hash_combine
		}
	};
}

template <typename T>
class BufPageManager
{
	T* addr[CAP];
	bool dirty [CAP];
	int last;
	FileManager *fileManager;
	std::unordered_map<std::pair<int, int>, T> hash;
	FindReplace find_replace;
	size_t hash_f(std::pair<int,int> p)
	{
		return (std::hash<int>{}(p.first)) ^ (std::hash<int>{}(p.second));
	}

public:
	BufPageManager(FileManager *fm)
	{
		last = -1;
		fileManager = fm;
		for (int i = 0; i < CAP; ++i)
		{
			dirty[i] = false;
			addr[i] = NULL;
		}
	}
	/*
	 * @函数名allocPage
	 * @param fileID:文件id，数据库程序在运行时，用文件id来区分正在打开的不同的文件
	 * @param pageID:文件页号，表示在fileID指定的文件中，第几个文件页
	 * @param index:函数返回时，用来记录缓存页面数组中的下标
	 * @param read:是否要将文件页中的内容读到缓存中
	 * 返回:缓存页面的首地址
	 * 功能:为文件中的某一个页面获取一个缓存中的页面
	 *           缓存中的页面在缓存页面数组中的下标记录在index中
	 *           并根据read是否为true决定是否将文件中的内容写到获取的缓存页面中
	 * 注意:在调用函数allocPage之前，调用者必须确信(fileID,pageID)指定的文件页面不存在缓存中
	 *           如果确信指定的文件页面不在缓存中，那么就不用在hash表中进行查找，直接调用替换算法，节省时间
	 */
	T* allocPage(int fileID, int pageID, int &index, bool read = false)
	{
		auto b = fetchPage( fileID,  pageID, index);
		if (read)
			fileManager->readPage(fileID, pageID, b, 0);
		return b;
	}
	/*
	 * @函数名getPage
	 * @param fileID:文件id
	 * @param pageID:文件页号
	 * @param index:函数返回时，用来记录缓存页面数组中的下标
	 * 返回:缓存页面的首地址
	 * 功能:为文件中的某一个页面在缓存中找到对应的缓存页面
	 *           文件页面由(fileID,pageID)指定
	 *           缓存中的页面在缓存页面数组中的下标记录在index中
	 *           首先，在hash表中查找(fileID,pageID)对应的缓存页面，
	 *           如果能找到，那么表示文件页面在缓存中
	 *           如果没有找到，那么就利用替换算法获取一个页面
	 */
	T* getPage(int fileID, int pageID, int &index)
	{
		//TODO
		//return address
	}

	// fetch the start address of page index
	T* fetchPage(int fileID, int pageID, int &index)
	{
		index = find_replace.find();
		if (addr[index] == NULL)
		{
			addr[index] = allocMem();
		}
		else
		{
			if (dirty[index])
			{
				auto it = hash.begin();
				for (; it != hash.end(); ++it)
					if (it->second == index)
						break;
				fileManager->writePage(it->first.first, it->first.second, addr[index], 0);
				dirty[index] = false;
			}
		}
		hash[std::make_pair(fileID, pageID)] = index;
		return addr[index];
	}
	/*
	 * @函数名access
	 * @param index:缓存页面数组中的下标，用来表示一个缓存页面
	 * 功能:标记index代表的缓存页面被访问过，为替换算法提供信息
	 */
	void access(const int index)
	{
		if (index == this->last)
			return;
		find_replace.access(index);
		this->last = index;
	}
	/*
	 * @函数名markDirty
	 * @param idex:缓存页面数组中的下标，用来表示一个缓存页面
	 * 功能:标记index代表的缓存页面被写过，保证替换算法在执行时能进行必要的写回操作，
	 *           保证数据的正确性
	 */
	void markDirty(int index)
	{
		dirty[index] = true;
		access(index);
	}
	/*
	 * @函数名release
	 * @param index:缓存页面数组中的下标，用来表示一个缓存页面
	 * 功能:将index代表的缓存页面归还给缓存管理器，在归还前，缓存页面中的数据不标记写回
	 */
	void release(int index)
	{
		dirty[index] = false;
		find_replace.free(index);
		auto it = hash.begin();
		for (; it != hash.end(); ++it)
			if (it->second == index)
				break;
		hash.erase(it);
	}
	/*
	 * writeBack
	 * @param index:缓存页面数组中的下标，用来表示一个缓存页面
	 * 功能:将index代表的缓存页面归还给缓存管理器，在归还前，缓存页面中的数据需要根据脏页标记决定是否写到对应的文件页面中
	 */
	void writeBack(int index)
	{
		//TODO
		//HINT: using fileManager->writePage
	}
	/*
	 * close
	 * 功能:将所有缓存页面归还给缓存管理器，归还前需要根据脏页标记决定是否写到对应的文件页面中
	 */
	void close()
	{
		for (int i = 0; i < CAP; ++i)
		{
			writeBack(i);
		}
	}

	T* allocMem()
	{
		return new T[(PAGE_SIZE / sizeof(T))];
	}
};