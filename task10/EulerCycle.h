#pragma once
#include <vector>
#include <string>
using namespace std;

namespace grph
{


	struct edge
	{
		int to;
		edge(int _to) : to(_to) {};
	};

	struct path
	{
		vector<int> p;
		path() {};
		path(vector<int> _p) : p(_p) {};
		friend ostream& operator<< (ostream &c, path &_p);

	};

	string getcd();

	class Graph
	{
		vector<vector<edge>> gr;
	public:

		vector<edge> operator[] (int index);
		bool readFile(string filename);
		int size();
		friend ostream& operator<< (ostream &c, Graph gr);
	};

	class EulerFinder
	{
		Graph *curGr;
		vector<vector<bool>> visited;
		vector<int> pth;
		void findProc(int index);
	public:
		void demo();
		grph::path findEuler(Graph *gr);
	};
}