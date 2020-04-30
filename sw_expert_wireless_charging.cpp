
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string.h>
#include<utility>
#include<queue>
#include<map>
using namespace std;

int M,A;
vector< pair<int,int> > board[10][10];
int dir[5][2] = { {0,0} , {-1,0} , {0,1} , {1,0} , {0,-1} };
int pos[2][2] = { {0,0} , {9,9} };
int res[2] = {0,0};
vector<int> move_list[2];


typedef struct BC{
    int r,c,cn,p;
}bc;

vector<bc> bcs;


int main(int argc, char** argv)
{
    int test_case;
    int T,temp;
    bc temp_bc;
    int t_x,t_y,t_c,t_p;
    
    queue<pair<int,int> > q;
    map<pair<int,int> ,int> visit;
    cin>>T;
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for(test_case = 1; test_case <= T; ++test_case)
    {
        
        move_list[0].clear();
        move_list[0].push_back(0);
        move_list[1].clear();
        move_list[1].push_back(0);
        bcs.clear();
        pos[0][0] = 0;
        pos[0][1] = 0;
        pos[1][0] = 9;
        pos[1][1] = 9;
        res[0] = 0;
        res[1] = 0;
        
        scanf("%d %d",&M,&A);
        
        for (int i = 0 ; i < 10; i++) {
            for(int j = 0 ; j < 10 ;j++){
                board[i][j].clear();
            }
            
        }
        
        for(int i = 0 ; i < 2 ; i++){
            for(int j = 0 ; j < M ; j++)
            {
                scanf("%d",&temp);
                move_list[i].push_back(temp);
            }
        }
        for(int i = 0 ; i < A ; i++){
        
            scanf("%d %d %d %d",&t_x,&t_y,&t_c,&t_p);
            temp_bc.r = t_y-1;
            temp_bc.c = t_x-1;
            temp_bc.cn = t_c;
            temp_bc.p = t_p;
            bcs.push_back(temp_bc);
            
        }
        
        
        //bfs
        int tr,tc;
        for(int i = 0 ; i < A ; i++){
            visit.clear();
            
            tr = bcs[i].r;
            tc = bcs[i].c;
            
            if(visit[pair<int, int>(tr+1,tc)] == 0){
                q.push(pair<int,int>(tr+1,tc));
                visit[pair<int, int>(tr+1,tc)] = 1;
            }
            if(visit[pair<int, int>(tr,tc+1)] == 0){
                q.push(pair<int,int>(tr,tc+1));
                visit[pair<int, int>(tr,tc+1)] = 1;
            }
            if(visit[pair<int, int>(tr-1,tc)] == 0){
                q.push(pair<int,int>(tr-1,tc));
                visit[pair<int, int>(tr-1,tc)] = 1;
            }
            if(visit[pair<int, int>(tr,tc-1)] == 0){
                q.push(pair<int,int>(tr,tc-1));
                visit[pair<int, int>(tr,tc-1)] = 1;
            }
            board[tr][tc].push_back(pair<int,int>(bcs[i].p,i));
            visit[pair<int, int>(tr,tc)] = 1;
            for(int j = 0; j < ((bcs[i].cn)*((2*bcs[i].cn)+2)) ; j++){
                tr = q.front().first;
                tc = q.front().second;
                q.pop();
                if((tr < 10 && tr >= 0 && tc < 10 && tc >= 0))
                {
                    board[tr][tc].push_back(pair<int,int>(bcs[i].p,i));
                }
                if(visit[pair<int, int>(tr+1,tc)] == 0){
                    q.push(pair<int,int>(tr+1,tc));
                    visit[pair<int, int>(tr+1,tc)] = 1;
                }
                if(visit[pair<int, int>(tr,tc+1)] == 0){
                    q.push(pair<int,int>(tr,tc+1));
                    visit[pair<int, int>(tr,tc+1)] = 1;
                }
                if(visit[pair<int, int>(tr-1,tc)] == 0){
                    q.push(pair<int,int>(tr-1,tc));
                    visit[pair<int, int>(tr-1,tc)] = 1;
                }
                if(visit[pair<int, int>(tr,tc-1)] == 0){
                    q.push(pair<int,int>(tr,tc-1));
                    visit[pair<int, int>(tr,tc-1)] = 1;
                }
                
            }
            while (!q.empty()) {
                q.pop();
            }
        }
        
        int temp_p,t_res1,t_res2;
        for(int t = 0 ; t <= M ; t++){
            //move
            temp_p = 0;
            t_res1 =0;
            t_res2=0;
            for(int i = 0 ; i < 2;i++){
                pos[i][0] += dir[ move_list[i][t] ][0];
                pos[i][1] += dir[ move_list[i][t] ][1];
            }
            if (board[pos[0][0]][pos[0][1]].size() != 0 && board[pos[1][0]][pos[1][1]].size() != 0) {
                for(int i = 0 ; i < board[pos[0][0]][pos[0][1]].size(); i++){
                    for(int j = 0 ; j < board[pos[1][0]][pos[1][1]].size(); j++){
                        if (board[pos[0][0]][pos[0][1]][i].second == board[pos[1][0]][pos[1][1]][j].second) {
                            if ((t_res1+t_res2) >= board[pos[0][0]][pos[0][1]][i].first) {
                                continue;
                            }
                            t_res1 = board[pos[0][0]][pos[0][1]][i].first/2;
                            t_res2 = board[pos[0][0]][pos[0][1]][i].first/2;
                        }
                        else{
                            if((t_res2 + t_res1) >= (board[pos[0][0]][pos[0][1]][i].first + board[pos[1][0]][pos[1][1]][j].first)){
                                continue;
                            }
                            t_res1 = board[pos[0][0]][pos[0][1]][i].first;
                            t_res2 = board[pos[1][0]][pos[1][1]][j].first;
                        }
                    }
                }
                res[0] += t_res1;
                res[1] += t_res2;
                
                
            }else if(board[pos[0][0]][pos[0][1]].size() == 0 && board[pos[1][0]][pos[1][1]].size() != 0){
                for(int i = 0 ; i < board[pos[1][0]][pos[1][1]].size(); i++){
                    temp_p = max(temp_p,board[pos[1][0]][pos[1][1]][i].first);
                }
                res[1] += temp_p;
            }else if(board[pos[0][0]][pos[0][1]].size() != 0 && board[pos[1][0]][pos[1][1]].size() == 0){
                for(int i = 0 ; i < board[pos[0][0]][pos[0][1]].size(); i++){
                    temp_p = max(temp_p,board[pos[0][0]][pos[0][1]][i].first);
                }
                res[0] += temp_p;
            }
        }
        printf("#%d %d\n",test_case,res[0]+res[1]);
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
