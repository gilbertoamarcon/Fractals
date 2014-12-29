#include "Branch.h"

Branch::Branch(){};

Branch::~Branch(){};

int Branch::init(double maxAngle, double depth, int maxChilds, double minSpot){
    this->order     = depth;
    this->maxAngle  = maxAngle;
    this->depth     = depth;
    spot            = 1;
    numChilds       = (int)(maxChilds*((double)rand()/RAND_MAX));
    if(numChilds < 2)
        numChilds   = 2;
    child           = NULL;
    angle1          = 0;
    angle2          = 0;
    length          = ((double)order/depth);
    jetColor();
    if(order < 1)
        return 0;
    child = (Branch*)malloc(numChilds*sizeof(Branch));
    for(int i = 0; i < numChilds; i++)
        (child+i)->init(order-1,maxAngle,depth,numChilds,minSpot);
    return 0;
}

int Branch::init(int order, double maxAngle, double depth, int maxChilds, double minSpot){
    this->order     = order;
    this->maxAngle  = maxAngle;
    this->depth     = depth;
    spot            = minSpot*((double)rand()/RAND_MAX)+minSpot;
    numChilds       = (int)(maxChilds*((double)rand()/RAND_MAX));
    if(numChilds < 2)
        numChilds   = 2;
    child           = NULL;
    angle1          = maxAngle*((double)rand()/RAND_MAX-0.5);
    angle2          = maxAngle*((double)rand()/RAND_MAX-0.5);
    length          = ((double)order/depth);
    jetColor();
    if(order < 1)
        return 0;
    child = (Branch*)malloc(numChilds*sizeof(Branch));
    for(int i = 0; i < numChilds; i++)
        (child+i)->init(order-1,maxAngle,depth,numChilds,minSpot);
    return 0;
}

int Branch::clean(){
    if(order < 1)
        return 0;
    for(int i = 0; i < numChilds; i++)
        (child+i)->clean();
    free(child);
    return 0;
}

int Branch::jetColor(){
    if(length < 0.2){
        r = 0.5+length*2.5;
        g = 0;
        b = 0;
        return 0;
    }
    if(length < 0.4){
        r = 1;
        g = (length-0.2)*5;
        b = 0;
        return 0;
    }
    if(length < 0.6){
        r = 1-(length-0.4)*5;
        g = 1;
        b = (length-0.4)*5;
        return 0;
    }
    if(length < 0.8){
        r = 0;
        g = 1-(length-0.6)*5;
        b = 1;
        return 0;
    }
    r = 0;
    g = 0;
    b = 1-(length-0.8)*2.5;
    return 0;
}
