#include "Intersection.h"
#include<QMessageBox>

double Intersection::slopeFinder(DataBase::Edge line) {

	double slope;

	if (line.endX != line.startX) {
		slope = ((line.endY - line.startY) / (line.endX - line.startX));
	}
	else {
		slope = 1;
	}

	return slope;
}

int Intersection::sideIndicator(DataBase::Edge line1, DataBase::Edge line2) {

	// ** Line 1 is meant to be compared to other lines ** //

	if (line1.startX > line2.endX && line1.startX > line2.startX && line1.endX > line2.endX && line1.endX > line2.endX) {

		// ** Line 1 to the right side of Line 2 (NO INTERSECTION) ** //

		return 0;
	}
	else if (line1.startX < line2.endX && line1.startX < line2.startX && line1.endX < line2.endX && line1.endX < line2.endX) {

		// ** Line 1 to the left of Line 2 (NO INTERSECTION)

		return 0;
	}
	else if (line1.startY > line2.endY && line1.startY > line2.startY && line1.endY > line2.endY && line1.endY > line2.endY) {

		// ** Line 1 above Line 2 (NO INTERSECTION)

		return 0;
	}
	else if (line1.startY < line2.endY && line1.startY < line2.startY && line1.endY < line2.endY && line1.endY < line2.endY) {

		// ** Line 1 below Line 2 (NO INTERSECTION)

		return 0;
	}
	else {

		// ** POSSIBLE INTERSETION 
		return 1;
	}
}

void Intersection::intersectionFinder(DataBase::Edge line1, DataBase::Edge line2) {

	double m1 = slopeFinder(line1);
	double m2 = slopeFinder(line2);

	double b1 = line1.startY - (m1 * line1.startX);
	double b2 = line2.startY - (m2 * line2.startX);

	double x, y;
	x = (b2 - b1) / (m1 - m2);
	y = (m1 * x) + b1;

	if (m1 == 1) {
		x = (b1 - b2) / (m2 - m1);
		y = (m2 * x) + b2;
	}

	DataBase::Point intersectionPoint{};
	intersectionPoint.x = x;
	intersectionPoint.y = y;
	
	// Check Valididty 
	// P = (1 - t) * P0 + (t * P1)                 -> P = P0 + t*(P1 - P0)
	// t = (P - P0) / (P1 - P0)                    0 <= t <= 1

	double u, v;
	u = (x - line1.startX) / (line1.endX - line1.startX);
	//if ((line1.endX - line1.startX) == 0) {
	//	u = (y - line1.startY) / (line1.endY - line1.startY);
	//}

	v = (x - line2.startX) / (line2.endX - line2.startX);
	//if ((line2.endX - line2.startX) == 0) {
	//	v = (y - line2.startY) / (line2.endY - line2.startY);
	//}


	if (0 <= u && u <= 1 && 0 <= v && v <= 1) {
		if (intersectionPointList.size() == 0) {

			intersectionPointList.push_back(intersectionPoint);
		}
		else {

			for (const auto& point : intersectionPointList)
			{

				if (point.x == intersectionPoint.x && point.y == intersectionPoint.y) {

					// ** Repeated Point (SKIP)
				}
				else {

					intersectionPointList.push_back(intersectionPoint);
				}
			}
		}
	}

	
}

int Intersection::parallelCheck(DataBase::Edge line1, DataBase::Edge line2) {

	int parallel;

	parallel = slopeFinder(line1) == slopeFinder(line2) ? 1 : 0;
	parallel = slopeFinder(line1) == (slopeFinder(line2) + PI) ? 1 : 0;
	parallel = slopeFinder(line1) == (slopeFinder(line2) - PI) ? 1 : 0;

	return parallel;
}

int Intersection::perpendicularCheck(DataBase::Edge line1, DataBase::Edge line2) {

	int perpendicular;

	perpendicular = slopeFinder(line1) == (slopeFinder(line2) + (PI / 2)) ? 1 : 0;
	perpendicular = slopeFinder(line1) == (slopeFinder(line2) - (PI / 2)) ? 1 : 0;

	return perpendicular;
}

double Intersection::roundUP(double target) {
	double dummy = target * 100000;
	dummy = dummy + 0.5;
	target = round(dummy) / 100000;
	return target;
}

void Intersection::findIntersectionBetItems(DataBase::Item item1, DataBase::Item item2) {

	for (const auto& line : item1.itemEdgeList) {
		for (const auto& line2 : item2.itemEdgeList) {
			
			intersectionFinder(line, line2);
		}
	}
}