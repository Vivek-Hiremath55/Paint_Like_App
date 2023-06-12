#pragma once
#include <vector>
#include <string>
#include <qstring.h>
class DataBase
{

public:

	struct Point
	{
		double x;
		double y;
	};

	struct Edge
	{
		float startX;
		float startY;
		float endX;
		float endY;
	};

	struct Item : Edge
	{
		QString entityName;
		int itemNumber;
		std::vector<Edge> itemEdgeList;
	};

	std::vector<Edge> edgeList;
	std::vector<Edge> highlightList;
};

