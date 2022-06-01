#include <iostream>
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

        Point(float valX, float valY) {
            x = valX;
            y = valY;
        }

        void set(float newX, float newY) {
            x = newX;
            y = newY;
        }

        float getX(void) {
            return x;
        }

        float getY(void) {
            return y;
        }
};


class Manipulator 
{
    private:
        Point pos;
        float range;

    public:
        Manipulator() {
            range = 1;
        }

        float getPosX(void) {
            return pos.getX();
        }

        float getPosY(void) {
            return pos.getY();
        }

        float getRange(void) {
            return range;
        }

        void setPos(float posX, float posY) {
            pos.set(posX, posY);
        }

        void setRange(float newRange) {
            range = newRange;
        }

        float distToPoint(Point p) {
            float res;
            float pX = p.getX();
            float pY = p.getY();
            float mX = pos.getX();
            float mY = pos.getY();

            res = sqrt(pow((mX - pX), 2) + pow((mY - pY), 2));
            if(res > range) {
                res = -1;
            }
            return res;
        }
};


/**
 * @brief           Функция определения оптимального манипулятора
 * 
 * @param[in]       Man1: Объект первого манипулятора
 * @param[in]       Man2: Объект второго манипулятора
 * @param[in]       Target: Целевая точка, к которуй будут тянуться манипуляторы
 * @return          optimCode
 */
optimCode choose_manip(Manipulator Man1, Manipulator Man2, Point Target) {
    float dist1 = Man1.distToPoint(Target);
    float dist2 = Man2.distToPoint(Target);

    if((dist1 < 0) && (dist2 < 0)) {
        return OUT_OF_RANGE;
    }

    if((dist1 < 0) && (dist2 >= 0)) {
        return MAN2_OPTIM;
    }

    if((dist2 < 0) && (dist1 >= 0)) {
        return MAN1_OPTIM;
    }

    return (dist1 < dist2) ? MAN1_OPTIM : MAN2_OPTIM;
}


int main(void)
{
    Point Target;
    Manipulator Man1, Man2;

    float target_x, target_y, man1_x, man1_y, man1_r, man2_x, man2_y, man2_r;
    std::cout << "Please enter parameters in the next order:" << std::endl <<
            "target_x target_y man1_x man1_y man1_r man2_x man2_y man2_r" << std::endl;

    std::cin >> target_x >> target_y >> man1_x >> man1_y >> man1_r >> man2_x >> man2_y >> man2_r;
     
    Target.set(target_x, target_y);
    Man1.setPos(man1_x, man1_y);
    Man1.setRange(man1_r);
    Man2.setPos(man2_x, man2_y);
    Man2.setRange(man2_r);

    switch (choose_manip(Man1, Man2, Target))
    {
    case MAN1_OPTIM:
        std::cout << "Need to use Manipulator 1" << std::endl;
        break;
    case MAN2_OPTIM:
        std::cout << "Need to use Manipulator 2" << std::endl;
        break;

    default:
        std::cout << "OUT_OF_RANGE";
        break;
    }

    return 0;
}
