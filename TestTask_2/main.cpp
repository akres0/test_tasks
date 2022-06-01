#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <cmath>

enum optimCode {
    OUT_OF_RANGE = 0,
    MAN1_OPTIM,
    MAN2_OPTIM
};

class Point 
{
    private:
        float x;
        float y;

    public:
        Point() {
            x = 0;
            y = 0;
        }

        Point(float x, float y) {
            this->x = x;
            this->y = y;
        }

        float getX(void) {
            return x;
        }

        float getY(void) {
            return y;
        }

        void set(float x, float y) {
            this->x = x;
            this->y = y;
        }
};


class Manipulator 
{
    private:
        Point base;
        Point head;
        float range;

    public:
        Manipulator() {
            range = 1;
        }

        Manipulator(float x, float y, float range) {
            setBase(x, y);
            setHead(x, y);
            this->range = range;
        }

        float getBaseX(void) {
            return base.getX();
        }

        float getBaseY(void) {
            return base.getY();
        }

        float getHeadX(void) {
            return head.getX();
        }

        float getHeadY(void) {
            return head.getY();
        }

        float getRange(void) {
            return range;
        }

        void setHead(float headX, float headY) {
            head.set(headX, headY);
        }

        void setBase(float baseX, float baseY) {
            base.set(baseX, baseY);
        }

        void setRange(float newRange) {
            range = newRange;
        }

        float headToPoint(Point p) {
            float res;
            float pX = p.getX();
            float pY = p.getY();
            float mX = head.getX();
            float mY = head.getY();

            res = sqrt(pow((mX - pX), 2) + pow((mY - pY), 2));
            return res;
        }

        bool inRange(Point p) {
            float res;
            float pX = p.getX();
            float pY = p.getY();
            float mX = base.getX();
            float mY = base.getY();

            res = sqrt(pow((mX - pX), 2) + pow((mY - pY), 2));

            return (res > range) ? false : true;
        }
};


optimCode choose_manip(Manipulator Man1, Manipulator Man2, Point Target) {
    float dist1 = Man1.headToPoint(Target);
    float dist2 = Man2.headToPoint(Target);
    bool in_range1 = Man1.inRange(Target);
    bool in_range2 = Man2.inRange(Target);

    // if((in_range1 == false) && (in_range2 == false)) {
    //     return OUT_OF_RANGE;
    // }

    // if((in_range1 == false) && (in_range2 == true)) {
    //     return MAN2_OPTIM;
    // }

    // if((in_range1 == true) && (in_range2 == false)) {
    //     return MAN1_OPTIM;
    // }

    return (dist1 < dist2) ? MAN1_OPTIM : MAN2_OPTIM;
}

/* Условия решения */
std::vector<Point> Details {{1, 3}, {2, 1.41}, {0.2, -7} ,{-5, -1} , {0, 9}};

Manipulator Man1(0, 0, 4);
Manipulator Man2(2, 1, 3);

int main(void)
{
    std::string man1_way;
    std::string man2_way;
    std::string tmpM;
    float tmpX;
    float tmpY;

    for(auto it = Details.begin(); it != Details.end(); ++it) {

        switch (choose_manip(Man1, Man2, *it))
        {
        case MAN1_OPTIM:
            tmpX = it->getX();
            tmpY = it->getY();
            Man1.setHead(tmpX, tmpY);
            tmpM = "{" + std::to_string(tmpX) + ", " + std::to_string(tmpY) + "}";
            man1_way.append(tmpM);
            tmpM.clear();
            break;

        case MAN2_OPTIM:
            tmpX = it->getX();
            tmpY = it->getY();
            Man2.setHead(tmpX, tmpY);
            tmpM = "{" + std::to_string(tmpX) + ", " + std::to_string(tmpY) + "}";
            man2_way.append(tmpM);
            tmpM.clear();
            break;

        default:
            std::cout << "Point out of range!" << std::endl;
            break;
        }
    }

    std::cout << "Manipulator 1 way: " << man1_way << std::endl;
    std::cout << "Manipulator 2 way: " << man2_way << std::endl;

    return 0;
}
