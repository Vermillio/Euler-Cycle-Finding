#include "EulerCycle.h"
#include <iostream>
#include <fstream>

using namespace std;

void grph::EulerFinder::findProc(int index)
{
	pth.push_back(index);
	for (int i = 0; i < (*curGr)[index].size(); ++i)
		if (!visited[index][i])
		{
			visited[index][i] = true;
			findProc((*curGr)[index][i].to);
			return;
		}
}

void grph::EulerFinder::demo()
{
	Graph gr;
	string filename;
	cout << "Enter filename ( must be stored in " << getcd() << " ) " << endl;
	cin >> filename;
	if (!gr.readFile(filename))
		return;
	cout << gr;
	path eul = findEuler(&gr);
	cout << eul;
}

vector<grph::edge> grph::Graph::operator[](int index)
{
	return gr[index];
}

bool grph::Graph::readFile(string filename)
{
	ifstream fin(filename, ios::in);

	if (!fin.is_open())
	{
		cout << "Error: couldn't open file." << endl;
		return false;
	}


	char buff[20];
	int i = 0, to;
	while (!fin.eof())
	{
		fin >> buff;
		if (isdigit(buff[0]))
		{
			to = atoi(buff);
			if (gr.size() <= to)
				gr.resize(to + 1);
			gr[i].push_back({ to});
			//gr[to].push_back({ i, atof(weight) });
		}
		else {
			++i;
			if (gr.size() < i)
				gr.resize(i);
		}
	}
	fin.close();
	return true;
}

int grph::Graph::size()
{
	return gr.size();
}


ostream & grph::operator<<(ostream & c, path &_p)
{
	cout << "{ ";
	for (auto it : _p.p)
		cout << it << " ";
	cout << "}" << endl;
	return c;
}

string grph::getcd()
{
	wchar_t *w = nullptr;
	wstring ws = _wgetcwd(w, _MAX_PATH);
	return string(ws.begin(), ws.end());
}

ostream & grph::operator<<(ostream & c, Graph gr)
{
	for (int i = 0; i < gr.size(); ++i)
	{
		cout << "Vertex " << i << ": ";
		for (auto j : gr[i])
			cout << "{ " << i << " -> " << j.to << " } ";
		cout << endl;
	}
	cout << endl;
	return c;
}

grph::path grph::EulerFinder::findEuler(Graph *gr)
{
	curGr = gr;
	visited = vector<vector<bool>>(gr->size());
	for (int i = 0; i < visited.size(); ++i)
		visited[i] = vector<bool>((*gr)[i].size(), 0);
	pth.clear();
	findProc(0);
	if (pth[0] != pth[pth.size() - 1])
		return path();
	for (int i = 0; i < visited.size(); ++i)
		for (int j = 0; j < visited[i].size(); ++j)
		{
			if (!visited[i][j])
				return path();
		}
	return path(pth);
}
