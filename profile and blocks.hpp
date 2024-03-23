#ifndef PROFILE_HPP
#define PROFILE_HPP
#include<queue>
/*排除没有机器人的港口*/
const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int max_go=85;
const int N = 210;
int distancejianshao=0;
int valuebeishu=1;
int maxgocounts=0;
int defineclose=20;
class Block {
public:
    char classes='0';
    int distance=9999;
    int distance_=9999;
    int value=0;
    int goodsnum=0;
    int berthid=-1;
    Block(){};
    Block(char classes){
        this->classes=classes;
    }
    void setDistance(int distance,int x,int y,int id);
    double judgevalue();
}maps[200][200];
void Block::setDistance(int distance,int x,int y,int id){
    if(maps[x][y].classes=='*'||maps[x][y].classes=='#')return;
    if(maps[x][y].distance<=distance) return;
    this->distance=distance;
    this->berthid=id;
    if(x>0) maps[x-1][y].setDistance(distance+1,x-1,y,id);
    if(x<199) maps[x+1][y].setDistance(distance+1,x+1,y,id);
    if(y>0) maps[x][y-1].setDistance(distance+1,x,y-1,id);
    if(y<199) maps[x][y+1].setDistance(distance+1,x,y+1,id);
}
double Block::judgevalue(){
    if(distance==0||distance==9999) return -1;
    return (double)value*valuebeishu/(distance+distance_+distancejianshao);
}
class item{
public:
int x=-1;int y=-1;int xiaoshi=-1;
};
std::queue<item> q;
int nextloc[N][N]={0};
int searched[N][N]={0};
double berthzero[berth_num]={0};
int paixv[berth_num]={0};
int robotcount[berth_num]={0};
int berthgocount[berth_num]={0};
int totalgoodcounts[berth_num]={0};
int berthisclose[berth_num]={0};
#endif