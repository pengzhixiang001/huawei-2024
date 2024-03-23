#include"profile and blocks.hpp"
#include"robot.hpp"
#include"berth.hpp"
#include"boat.hpp"
#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int money, boat_capacity, id;
char ch;
void Init()
{
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            scanf("%c", &ch);maps[i][j].classes=ch;
            }scanf("%c",&ch);
            }
    for(int i = 0; i < berth_num; i ++)
    {
        int id;
        scanf("%d", &id);
        scanf("%d%d%d%d", &berth[id].x, &berth[id].y, &berth[id].transport_time, &berth[id].loading_speed);
        berth[id].id = id;
        for(int j = berth[id].x; j < berth[id].x + 4; j ++){
            for(int k = berth[id].y; k < berth[id].y + 4; k ++){
                maps[j][k].berthid = id;
                maps[j][k].setDistance(0,j,k,id);
                }}
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(maps[i][j].berthid==-1){continue;}
            berthzero[maps[i][j].berthid]++;
            // if(maps[i][j].classes=='A'){
            //     robotcount[maps[i][j].berthid]++;
            // }
        }
    }
    for(int i=0;i<berth_num;i++){
        berthzero[i]=((double)berthzero[i])/(berth[i].transport_time*2+boat_capacity/berth[i].loading_speed);
    }
    int numcount_=0;
    while(numcount_<5){
        int maxzero=0;
        int maxid=-1;
        for(int i=0;i<berth_num;i++){
            if(berthzero[i]>maxzero&&berthisclose[i]==0){
                maxzero=berthzero[i];
                maxid=i;
            }
        }
        if(maxid==-1){
            break;
        }
        for(int i=0;i<numcount_;i++){
            if(berth[paixv[i]].x<=berth[maxid].x+defineclose
            &&berth[paixv[i]].x>=berth[maxid].x-defineclose
            &&berth[paixv[i]].y<=berth[maxid].y+defineclose
            &&berth[paixv[i]].y>=berth[maxid].y-defineclose){
                berthisclose[maxid]=1;
                break;
            }
        }
        if(berthisclose[maxid]==1){
            continue;
        }
        paixv[numcount_]=maxid;
        berthzero[maxid]=0;
        numcount_++;
    }
    while(numcount_<5){
        int maxzero=0;
        int maxid=-1;
        for(int i=0;i<berth_num;i++){
            if(berthzero[i]>maxzero){
                maxzero=berthzero[i];
                maxid=i;
            }
        }
        paixv[numcount_]=maxid;
        berthzero[maxid]=0;
        numcount_++;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            maps[i][j].distance=9999;
        }
    }
    for(int i=0;i<5;i++){
        for(int j=berth[paixv[i]].x;j<berth[paixv[i]].x+4;j++){
            for(int k=berth[paixv[i]].y;k<berth[paixv[i]].y+4;k++){
                maps[j][k].setDistance(0,j,k,paixv[i]);
            }
        }
    }
    scanf("%d", &boat_capacity);
    char okk[100];
    scanf("%s", okk);
    printf("OK\n");
    fflush(stdout);
}

int Input()
{
    scanf("%d%d", &id, &money);
    int num;
    scanf("%d", &num);
    for(int i = 1; i <= num; i ++)
    {
        int x, y, val;
        scanf("%d%d%d", &x, &y, &val);
        maps[x][y].value = val;
        q.push({x,y,id+1000});
    }
    for(int i = 0; i < robot_num; i ++)
    {
        scanf("%d%d%d%d", &robot[i].goods, &robot[i].x, &robot[i].y, &robot[i].status);
        robot[i].mbx=robot[i].x;
        robot[i].mby=robot[i].y;
        if(robot[i].status==0){
            nextloc[robot[i].x][robot[i].y]=1;
        }
    }
    for(int i = 0; i < 5; i ++)
        scanf("%d%d\n", &boat[i].status, &boat[i].pos);
    char okk[100];
    scanf("%s", okk);
    return id;
}

int main()
{   
    // ofstream fout("C:\\Users\\pengz\\Desktop\\huawei2024\\sdk\\C++\\shuru.txt");
    Init();
    for(int zhen = 1; zhen <= 15000; zhen ++)
    {   
        // if(zhen==15000){
        //     for(int i=0;i<berth_num;i++){
        //         if(berth[i].goodsnum>0){
        //             fout<<i<<' '<<berth[i].goodsnum<<endl;
        //         }
        //     }
        // }
        /*条件*/
        int totalgoods=0;
        for(int i=0;i<5;i++){
            totalgoods+=berth[paixv[i]].goodsnum;
        }
        if(totalgoods>2*boat_capacity){
            valuebeishu=2;
        }
        if(totalgoods>3*boat_capacity){
            valuebeishu=3;
            distancejianshao==5;
        }
        if(totalgoods>4*boat_capacity){
            valuebeishu=4;
            distancejianshao==10;
        }
        if(totalgoods>5*boat_capacity){
            valuebeishu=5;
            distancejianshao==15;
        }
        int id = Input();
        item temp=q.front();
        while(temp.xiaoshi<=zhen){
            q.pop();
            maps[temp.x][temp.y].value=0;
            temp=q.front();
        }
        // for(int i=0;i<5;i++){
        //     if(zhen==boat[i].reache_time){
        //         berth[boat[i].mubiao].ismubiao=0;
        //     }
        // }
        for(int i = 0; i < robot_num; i ++){
            if(robot[i].get()){
                printf("get %d\n", i);
            }
            if(robot[i].pull()){
                printf("pull %d\n", i);
            }
            if(robot[i].status==0){
                continue;
            }
            int ismove = robot[i].move();
            //  fout<<ismove<<' ';
            if(ismove==-1){
                for(int j=0;j<i;j++){
                if(robot[j].mbx==robot[i].x&&robot[j].mby==robot[i].y){
                    nextloc[robot[i].mbx][robot[i].mby]=0;
                    ismove=robot[i].birang(robot[j].mbx,robot[j].mby,robot[j].x,robot[j].y);
                    if(ismove==0){robot[i].mby=robot[i].y+1;robot[i].mbx=robot[i].x;nextloc[robot[i].x][robot[i].y+1]=1;}
                    if(ismove==1){robot[i].mby=robot[i].y-1;robot[i].mbx=robot[i].x;nextloc[robot[i].x][robot[i].y-1]=1;}
                    if(ismove==2){robot[i].mbx=robot[i].x-1;robot[i].mby=robot[i].y;nextloc[robot[i].x-1][robot[i].y]=1;}
                    if(ismove==3){robot[i].mbx=robot[i].x+1;robot[i].mby=robot[i].y;nextloc[robot[i].x+1][robot[i].y]=1;}
                    break;
                }
            }
            if(ismove==-1){continue;}
            printf("move %d %d\n", i, ismove);
            continue;
            }
            else{
                for(int j=0;j<i;j++){
                if(robot[j].mbx==robot[i].x&&robot[j].mby==robot[i].y&&robot[i].mbx==robot[j].x&&robot[i].mby==robot[j].y){
                    nextloc[robot[i].mbx][robot[i].mby]=0;
                    ismove=robot[i].birang(robot[j].mbx,robot[j].mby,robot[j].x,robot[j].y);
                    if(ismove==0){robot[i].mby=robot[i].y+1;robot[i].mbx=robot[i].x;nextloc[robot[i].x][robot[i].y+1]=1;}
                    if(ismove==1){robot[i].mby=robot[i].y-1;robot[i].mbx=robot[i].x;nextloc[robot[i].x][robot[i].y-1]=1;}
                    if(ismove==2){robot[i].mbx=robot[i].x-1;robot[i].mby=robot[i].y;nextloc[robot[i].x-1][robot[i].y]=1;}
                    if(ismove==3){robot[i].mbx=robot[i].x+1;robot[i].mby=robot[i].y;nextloc[robot[i].x+1][robot[i].y]=1;}
                    break;
                }
            }
            }
            printf("move %d %d\n", i, ismove);
            }
            for(int i=0;i<robot_num;i++){
                nextloc[robot[i].mbx][robot[i].mby]=0;
                searched[robot[i].searchx][robot[i].searchy]=0;
            }
            for(int i=0;i<5;i++){
                if(boat[i].status==0){continue;}
                if(boat[i].status==1){
                    int mubiaoberthid=paixv[i];
                    //  mubiaoberthid=boat[i].towards(zhen);
                    /*计算目标泊位*/
                    if(boat[i].pos==-1){
                     printf("ship %d %d\n",i,mubiaoberthid);
                     boat[i].reache_time=zhen+berth[mubiaoberthid].transport_time;
                    }
                    else{
                        /*金钱和货物对应关系，考虑用一个类 加上 队列*/
                        // int maxgoods_num=0;
                        // int maxgoods_id=-1;
                        // if(zhen-boat[i].reache_time>=500&&boat[i].num+berth[boat[i].pos].goodsnum<boat_capacity/2){
                        //     for(int j=0;j<5;j++){
                        //         if(berth[paixv[j]].goodsnum>maxgoods_num){
                        //             maxgoods_num=berth[paixv[j]].goodsnum;
                        //             maxgoods_id=j;
                        //         }
                        //     }
                        //     if(maxgoods_id!=-1){
                        //         printf("ship %d %d\n",i,maxgoods_id);
                        //         boat[i].reache_time=zhen+500;
                        //     }
                        //     continue;
                        // }
                        if(zhen>=15000-berth[boat[i].pos].transport_time-1){
                            printf("go %d\n",i);
                            continue;
                        }
                        if(boat[i].num==boat_capacity){
                            boat[i].status=0;boat[i].num=0;
                            printf("go %d\n",i);
                            berth[boat[i].pos].gocount++;
                            if(berth[boat[i].pos].gocount>maxgocounts){
                                maxgocounts=berth[boat[i].pos].gocount;
                            }
                            boat[i].gotime=zhen;
                            continue;
                        }
                        int load=min(berth[boat[i].pos].loading_speed,boat_capacity-boat[i].num);
                        if(berth[boat[i].pos].goodsnum>=load){
                            boat[i].num+=load;
                            berth[boat[i].pos].goodsnum-=load;
                        }
                        else{
                            boat[i].num+=berth[boat[i].pos].goodsnum;
                            berth[boat[i].pos].goodsnum=0;
                        }
                    }
                }
                if(boat[i].status==2){
                   continue; 
                }
            }
        puts("OK");
        fflush(stdout);
    }
    return 0;
}
