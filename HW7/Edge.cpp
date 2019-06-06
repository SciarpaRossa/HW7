#include "Edge.h"


Edge::Edge() : weight(0), vertx(0), verty(0) 
{}



Edge::Edge(int new_weight, char new_vertx, char new_verty) : weight(new_weight), vertx(new_vertx), verty(new_verty)
{}



Edge::~Edge()
{}



bool
Edge::operator>(Edge& r)
{
	if (weight > r.weight)
		return true;

	return false;
}



bool
Edge::operator<(Edge& r)
{
	if (weight < r.weight)
		return true;

	return false;
}



bool
Edge::operator==(Edge& r)
{
	if (weight == r.weight)
		return true;

	return false;
}



void
Edge::display(void)
{
	std::cout << "<" << weight << ", "
		<< vertx << ", "
		<< verty << ">";

	return;
}



int
Edge::get_weight(void)
{
	return weight;
}



int
Edge::get_vertx(void)
{
	return vertx - 'A';
}



int
Edge::get_verty(void)
{
	return verty - 'A';
}