#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<char> names{'X', 'Y', 'Z'};
static bool err = false;

class Point
{
    private:
        float x;
        float y;
        float z;
    
    public:
        Point(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        float getX(void) {
            return x;
        }

        float getY(void) {
            return y;
        }

        float getZ(void) {
            return z;
        }

        void set(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
};


void get_start_point(vector<float> *p, string s) {
    size_t pos = 0;
    string token;

    while ((pos = s.find(" ")) != string::npos) {
        token = s.substr(0, pos);
        p->push_back(stof(token));
        s.erase(0, pos + 1);
    }
    p->push_back(stof(s));
}


void get_expected_delimiter(string s, string *delimiter) {
    for(auto it = s.begin(); it != s.end(); ++it) {
        if(!(isalpha(*it) || isdigit(*it))) {
            while (!(isalpha(*it) || isdigit(*it))) {
                delimiter->push_back(*it);
                ++it;
            }
            break;
        }
    }
}


bool extract_fields(string s, string *delimiter, vector<string> *res) {
        size_t pos = 0;

        while ((pos = s.find(*delimiter)) != string::npos) {
            res->push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter->length());
        }

        if(res->size() != 3) {
            return false;
        } else {
            return true;
        }
}


bool process_command(vector<string> *fields, vector<float> *coord) {
    string tmp;
    int i = 0;
    for(auto it = fields->begin(); it != fields->end(); ++it) {
        if(it->at(0) == names.at(i)) {
            it->erase(it->begin());
            coord->push_back(stof(*it));
        } else {
            return false;
        }
        i++;
    }
    return true;
}


int main(void)
{
    vector<string> gcode;
    vector<float> p_coord;
    string line;
    string delimiter;

    /* Считали весь входящий поток */
    while(getline(cin, line)) {
        if(line.empty()) {
            break;
        }
        gcode.push_back(line);
    }

    /* Вычисляем положение точки по первой строке */
    get_start_point(&p_coord, gcode.at(0));
    gcode.erase(gcode.begin());
    Point p(p_coord.at(0), p_coord.at(1), p_coord.at(2));
    p_coord.clear();

    /* Вычленение разделителя */
    get_expected_delimiter(gcode.at(0), &delimiter);

    /* Парсим оставшиеся строки и изменяем положение точки в соответствии с командами */
    vector<string> fields;
    for(auto it = gcode.begin(); it != gcode.end(); ++it) {
        if(extract_fields(*it, &delimiter, &fields)) {
            if(process_command(&fields, &p_coord)) {
                p.set(p.getX() + p_coord.at(0), p.getY() + p_coord.at(1), p.getZ() + p_coord.at(2));
            } else {
                err = true;
                break;
            }
        } else {
            err = true;
            break;
        }
        fields.clear();
        p_coord.clear();
    }

    cout << p.getX() << " " << p.getY() << " " << p.getZ() << endl;
    if(err) {
        cout << "ERROR_SCRIPT" << endl;
    }
    
    return 0;
}
