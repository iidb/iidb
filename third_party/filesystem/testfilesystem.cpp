/*
 * testfilesystem.cpp
 *
 * 还有非常重要的一点，BufType b = bpm->allocPage(...)
 * 在利用上述allocPage函数或者getPage函数获得指向申请缓存的指针后，
 * 不要自行进行类似的delete[] b操作，内存的申请和释放都在BufPageManager中做好
 * 如果自行进行类似free(b)或者delete[] b的操作，可能会导致严重错误
 */
#include "bufmanager/bufmanager.h"
#include "fileio/FileManager.h"
#include "utils/pagedef.h"
#include <iostream>

using namespace std;
typedef unsigned int T;

int main() {
	MyBitMap::initConst();   //新加的初始化
	FileManager* fm = new FileManager();
	BufPageManager<T>* bpm = new BufPageManager<T>(fm);
	fm->createFile("testfile.txt"); //新建文件
	fm->createFile("testfile2.txt");
	int fileID, f2;
	fm->openFile("testfile.txt", fileID); //打开文件，fileID是返回的文件id
        fm->openFile("testfile2.txt", f2);
	for (int pageID = 0; pageID < 1000; ++ pageID) {
		int index;
		//为pageID获取一个缓存页
		BufType b = bpm->allocPage(fileID, pageID, index, false);
		//注意，在allocPage或者getPage后，千万不要进行delete[] b这样的操作
		//内存的分配和管理都在BufPageManager中做好，不需要关心，如果自行释放会导致问题
		b[0] = pageID; //对缓存页进行写操作
		b[1] = fileID;
		bpm->markDirty(index); //标记脏页
		//在重新调用allocPage获取另一个页的数据时并没有将原先b指向的内存释放掉
		//因为内存管理都在BufPageManager中做好了
		b = bpm->allocPage(f2, pageID, index, false);
		b[0] = pageID;
		b[1] = f2;
		bpm->markDirty(index);
	}
	for (int pageID = 0; pageID < 1000; ++ pageID) {
		int index;
		//为pageID获取一个缓存页
		BufType b = bpm->getPage(fileID, pageID, index);
		//注意，在allocPage或者getPage后，千万不要进行delete[] b这样的操作
		//内存的分配和管理都在BufPageManager中做好，不需要关心，如果自行释放会导致问题
		cout << b[0] << ":" << b[1] << endl; 		//读取缓存页中第一个整数
		bpm->access(index); //标记访问
		b = bpm->getPage(f2, pageID, index);
		cout << b[0] << ":" << b[1] << endl;
		bpm->access(index);
	}
	//程序结束前可以调用BufPageManager的某个函数将缓存中的内容写回
	//具体的函数大家可以看看ppt或者程序的注释
	return 0;
}
