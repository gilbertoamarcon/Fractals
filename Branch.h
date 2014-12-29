#ifndef BRANCH_H
#define BRANCH_H
#include <stdlib.h>

using namespace std;

class Branch{
    public:
        double r;
        double g;
        double b;
        double maxAngle;
        double length;
        double angle1;
        double angle2;
        double depth;
        double order;
        double spot;
        int numChilds;
        Branch* child;
        Branch();
        virtual ~Branch();
        int init(double maxAngle, double depth, int maxChilds, double minSpot);
        int init(int order, double maxAngle, double depth, int maxChilds, double minSpot);
        int clean();
        int jetColor();
};

#endif // BRANCH_H
