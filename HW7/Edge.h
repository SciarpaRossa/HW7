#pragma once
#include <iostream>

class Edge
{
	private:
		int weight;
		char vertx;
		char verty;
	public:
		Edge();
		Edge(int new_weight, char new_vertx, char new_verty);
		~Edge();
		void display(void);
		int get_weight(void);
		int get_vertx(void);
		int get_verty(void);
		bool operator>(Edge& r_side);
		bool operator<(Edge& r_side);
		bool operator==(Edge& r_side);
};

