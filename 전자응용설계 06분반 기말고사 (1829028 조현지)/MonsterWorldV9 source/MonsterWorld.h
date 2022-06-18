#pragma once
#include "Canvas.h"
#include "VariousMonsters.h"
#include "Human.h"
#include <windows.h>

class MonsterWorld {
	//Vector < Vector<int> > world;
	vector < vector<int> > world;
	int xMax, yMax, nMove;
	//Vector <Monster*> pMon;
	vector <Monster*> pMon;
	Canvas	canvas;

	int& Map(int x, int y) { return world[y][x]; }
	bool isDone() { return countItems() == 0; }
	int countItems() {
		int nItems = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) nItems++;
		return nItems;
	}
	void print() {
		canvas.clear();
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) canvas.draw(x, y, "■");
		for (int i = 0; i < pMon.size(); i++)
			pMon[i]->draw(canvas);
		canvas.print("[ Monster World (멋진 STL 세상) ]");

		cerr << " 전체 이동 횟수 = " << nMove << endl;
		cerr << " 남은 아이템 수 = " << countItems() << endl;
		for (int i = 0; i < pMon.size(); i++)
			pMon[i]->print();
	}
public:
	//MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h) {
	MonsterWorld(int w, int h) : world(h), canvas(w, h), xMax(w), yMax(h) {
		nMove = 0;
		for (int y = 0; y < yMax; y++) {
			//world[y] = Vector<int>(w);
			//for (int x = 0; x < xMax; x++) Map(x, y) = 1;
			world[y] = vector<int>(w,1);
		}
	}
	~MonsterWorld() {
		for (int i = 0; i < pMon.size(); i++)
			delete pMon[i];
	}
	void add(Monster* m) {
		pMon.push_back(m);
	}
	void play(int maxwalk, int wait) {
		print();
		cerr << " 엔터를 누르세요...";
		getchar();
		for (int i = 0; i < maxwalk; i++) {
			for (int k = 0; k < pMon.size(); k++)
				pMon[k]->move(world, xMax, yMax);

			nMove++;
			print();
			if (isDone()) break;
			Sleep(wait);
		}
	}
};