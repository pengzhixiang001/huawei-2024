#include"profile and blocks.hpp"
#include"berth.hpp"
#include"random"
#include<thread>
#ifndef ROBOT
#define ROBOT
/*碰撞*/
class Robot
{
    public:
    int x, y, goods;
    int searchx=-1;
    int searchy=-1;
    double maxgoods=0;
    int directions=-1;
    int money=0;
    int status;
    int mbx, mby;
    Robot() {}
    Robot(int startX, int startY) {
        x = startX;
        y = startY;
    }
    void init(){
        for(int i=x-max_go-2;i<=max_go+x+2;i++){
            for(int j=y-max_go-2;j<=max_go+y+2;j++){
                if(i>=0&&i<200&&j>=0&&j<200){
                    maps[i][j].distance_=9999;
                }
            }
        }
        directions=-1;
        maxgoods=0;
    }
    bool get(){
    if(maps[x][y].value>0&&goods==0){
        money=maps[x][y].value;
        maps[x][y].value=0;
        goods=1;
        return true;
    }
    else return false;
    }
    bool pull(){
        if(goods==1&&maps[x][y].distance==0){
            maps[x][y].value+=money;
            berth[maps[x][y].berthid].money+=money;
            berth[maps[x][y].berthid].goodsnum++;
            totalgoodcounts[maps[x][y].berthid]++;
            money=0;
            goods=0;
            return true;
        }
        else return false;
    }
    void search(int x,int y,int n,int direction){
        if(x<0||x>199||y<0||y>199){return;}
        if(maps[x][y].distance==9999){return;}
        if(n>max_go){return;}
        if(maps[x][y].distance_<=n){return;}
        maps[x][y].distance_=n;
        if(maps[x][y].judgevalue()>maxgoods&&searched[x][y]==0){
            maxgoods=maps[x][y].judgevalue();
            searchx=x;
            searchy=y;
            directions=direction;
        }
        if(x>0)search(x-1,y,n+1,direction);
        if(x<199)search(x+1,y,n+1,direction);
        if(y>0)search(x,y-1,n+1,direction);
        if(y<199)search(x,y+1,n+1,direction);
    }
    int birang(int mbx,int mby,int x,int y){
    if(mbx==x-1&&mby==y){
        if(maps[mbx][mby-1].distance!=9999&&nextloc[mbx][mby-1]==0){return 1;}
        if(maps[mbx][mby+1].distance!=9999&&nextloc[mbx][mby+1]==0){return 0;}
        return 2;
    }
    if(mbx==x+1&&mby==y){
        if(maps[mbx][mby-1].distance!=9999&&nextloc[mbx][mby-1]==0){return 1;}
        if(maps[mbx][mby+1].distance!=9999&&nextloc[mbx][mby+1]==0){return 0;}
        return 3;
    }
    if(mbx==x&&mby==y-1){
        if(maps[mbx-1][mby].distance!=9999&&nextloc[mbx-1][mby]==0){return 2;}
        if(maps[mbx+1][mby].distance!=9999&&nextloc[mbx+1][mby]==0){return 3;}
        return 1;
    }
    if(mbx==x&&mby==y+1){
        if(maps[mbx-1][mby].distance!=9999&&nextloc[mbx-1][mby]==0){return 2;}
        if(maps[mbx+1][mby].distance!=9999&&nextloc[mbx+1][mby]==0){return 3;}
        return 0;
    }
    return -1;
    }
    int move(){
        if(status==0){
        nextloc[x][y]=1;
        mbx=x;mby=y;     
        return -1;}
        if(goods==1){
            mbx=x;mby=y;
            int left=9999, right=9999, up=9999, down=9999,result=-1;
            if(y!=0)left=maps[x][y-1].distance;
            if(y!=199)right=maps[x][y+1].distance;
            if(x!=0)up=maps[x-1][y].distance;
            if(x!=199)down=maps[x+1][y].distance;
            if(right<maps[x][y].distance){
                if(nextloc[x][y+1]==0){
                mbx=x;mby=y+1;
                nextloc[mbx][mby]=1;
                return 0;}
            }
            if(left<maps[x][y].distance){
                if(nextloc[x][y-1]==0){
                mbx=x;mby=y-1;
                nextloc[mbx][mby]=1;
                return 1;}
            }
            if(up<maps[x][y].distance){
                if(nextloc[x-1][y]==0){
                mbx=x-1;mby=y;
                nextloc[mbx][mby]=1;
                return 2;}
            }
            if(down<maps[x][y].distance){
                if(nextloc[x+1][y]==0){
                mbx=x+1;mby=y;
                nextloc[mbx][mby]=1;
                return 3;}
            }
            if(left<maps[x][y].distance){
                if(down!=9999&&nextloc[x+1][y]==0){
                    nextloc[x+1][y]=1;
                    mbx=x+1;mby=y;
                    return 3;
                }
                if(up!=9999&&nextloc[x-1][y]==0){
                    nextloc[x-1][y]=1;
                    mbx=x-1;mby=y;
                    return 2;
                }
                return 0;
            }
            if(right<maps[x][y].distance){
                if(down!=9999&&nextloc[x+1][y]==0){
                    nextloc[x+1][y]=1;
                    mbx=x+1;mby=y;
                    return 3;
                }
                if(up!=9999&&nextloc[x-1][y]==0){
                    nextloc[x-1][y]=1;
                    mbx=x-1;mby=y;
                    return 2;
                }
                return 1;
            }
            if(up<maps[x][y].distance){
                if(left!=9999&&nextloc[x][y-1]==0){
                    nextloc[x][y-1]=1;
                    mbx=x;mby=y-1;
                    return 1;
                }
                if(right!=9999&&nextloc[x][y+1]==0){
                    nextloc[x][y+1]=1;
                    mbx=x;mby=y+1;
                    return 0;
                }
                return 3;
            }
            if(down<maps[x][y].distance){
                if(left!=9999&&nextloc[x][y-1]==0){
                    nextloc[x][y-1]=1;
                    mbx=x;mby=y-1;
                    return 1;
                }
                if(right!=9999&&nextloc[x][y+1]==0){
                    nextloc[x][y+1]=1;
                    mbx=x;mby=y+1;
                    return 0;
                }
                return 2;
            }
            mbx=x;mby=y;
            return -1;
        }
        else {
            mbx=x;mby=y;
            searchx=x;
            searchy=y;
        init();
        maps[x][y].distance_=0;
        std::thread t1(&Robot::search,this,x-1,y,1,2);
        std::thread t2(&Robot::search,this,x+1,y,1,3);
        std::thread t3(&Robot::search,this,x,y-1,1,1);
        std::thread t4(&Robot::search,this,x,y+1,1,0);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        // search(x-1,y,1,2);
        // search(x+1,y,1,3);
        // search(x,y-1,1,1);
        // search(x,y+1,1,0);
        searched[searchx][searchy]=1;
        if(directions==0){mbx=x;mby=y+1;}
        else if(directions==1){mbx=x;mby=y-1;}
        else if(directions==2){mbx=x-1;mby=y;}
        else if(directions==3){mbx=x+1;mby=y;}
        if(nextloc[mbx][mby]==1){
                mbx=x;mby=y;
                nextloc[mbx][mby]=1;
                return -1;
        }
        else if(nextloc[mbx][mby]==0){
                nextloc[mbx][mby]=1;
                return directions;
            }
            return directions;
        }
        return -1;
    }
}robot[robot_num + 10];
#endif