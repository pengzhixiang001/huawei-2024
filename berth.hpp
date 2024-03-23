#include"profile and blocks.hpp"
#ifndef BERTH
#define BERTH
class Berth
{
    public:
    int id=-1;
    int x;
    int y;
    int transport_time;
    int ismubiao=0;
    int loading_speed;
    int goodsnum=0;
    int money=0;
    int gocount=0;
    Berth(){}
    Berth(int x, int y, int transport_time, int loading_speed) {
        this -> x = x;
        this -> y = y;
        this -> transport_time = transport_time;
        this -> loading_speed = loading_speed;
    }
}berth[berth_num + 10];
#endif