#include "DataBase.h"
#include <cmath>
#include<vector>
#include<QPoint>

class Intersection {
public:

	double px, py;

	double PI = 3.14159265359;

	std::vector<DataBase::Point> intersectionPointList;

	double slopeFinder(DataBase::Edge line);
	int sideIndicator(DataBase::Edge line1, DataBase::Edge line2);
	void intersectionFinder(DataBase::Edge line1, DataBase::Edge line2);
	int parallelCheck(DataBase::Edge line1, DataBase::Edge line2);
	int perpendicularCheck(DataBase::Edge line1, DataBase::Edge line2);
	double roundUP(double target);

};