#pragma once
#include "Array.h"

namespace spaceGraph
{
	template<class T>
	class Graph
	{
		struct Vertex
		{
			T data;
			Vertex() = default;
			Vertex(T _data) : data(_data) {}
		};
		size_t cnt;
		vector<Vertex> vertices;
		vector<vector<size_t>> relations;

	public:
		Graph() = default;
		void ReadFromFile(string path)
		{
			fstream fin(path, ios_base::in);
			fin >> this->cnt;
			this->vertices.resize(this->cnt);
			this->relations.resize(this->cnt);
			for (size_t i = 0; i < this->cnt; i++)
			{
				size_t k;
				fin >> k;
				relations[i].resize(k);
			}
			for (size_t i = 0; i < this->cnt; i++)
			{
				for (size_t j = 0; j < this->relations[i].size(); j++)
					fin >> relations[i][j];
			}
			fin.close();
		}


	};
}