#include"profile and blocks.hpp"
class Boat
{
    public:
    int num=0, pos, status;
    int reache_time=0;
    int mubiao=-1;
    int gotime=0;
int towards(int zhen){
    int maxgoods=-1;
    int towa=-1;
    for(int i=0;i<berth_num;i++){
        if(berth[i].ismubiao==1) continue;
        if(berth[i].goodsnum>maxgoods){
            maxgoods=berth[i].goodsnum;
            towa=i;
        }
    }
    mubiao=towa;
    berth[towa].ismubiao=1;
    reache_time=zhen+berth[towa].transport_time;
    return towa;
}
}boat[10];