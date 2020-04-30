
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<utility>
#include <set>
#include <string.h>
#define START 151

using namespace std;



int N,M,K;

int board[400][400];

int dir[4][2] = { {1,0} , {-1,0} , {0,1} , {0,-1}};
bool f_time[400][400];
map< pair<int,int> ,int > activated; //map[r,c] = left hour
map< pair<int,int> ,int > unactivated;


int main(int argc, char** argv)
{
    int test_case;
    int T;
    int r,c;
    cin>>T;
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */

    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        memset(board, 0, sizeof(board));
        memset(f_time, false, sizeof(f_time));
        activated.clear();
        unactivated.clear();
        scanf("%d %d %d",&N,&M,&K);
        
        for(int i = START; i < START+N; i++){
            for(int j= START; j < START+M; j++){
                scanf("%d",&board[i][j]);
                if(board[i][j] >= 1){
                    unactivated[pair<int, int>(i,j)] = board[i][j];
                    
                }
            }
        }
        
        
        for(int t = 1 ; t <= K ; t++){ //whole hour
            
            for(map<pair<int, int>,int>::iterator iter = unactivated.begin(); iter != unactivated.end();){
                r =(*iter).first.first;
                c =(*iter).first.second;
                f_time[r][c] = false;
                if((--((*iter).second)) <= 0 ){
                    activated[(*iter).first] = board[(*iter).first.first][(*iter).first.second]+1;
                    unactivated.erase(iter++);
                }else{
                    iter++;
                }
            }
            
            
            for(map<pair<int, int>,int>::iterator iter = activated.begin(); iter != activated.end();){
                r =(*iter).first.first;
                c =(*iter).first.second;
                if((*iter).second ==  board[r][c]){ // spreading mother
                    
                    for(int i = 0 ; i < 4; i++){
                        if(board[r+dir[i][0]][c+dir[i][1]] == 0){ //not exist cell
                            board[r+dir[i][0]][c+dir[i][1]] = board[r][c];
                            f_time[r+dir[i][0]][c+dir[i][1]] = true;
                            unactivated[pair<int,int>(r+dir[i][0],c+dir[i][1])] = board[r][c];
                            
                        }
                        else{ //exist cell
                            if(f_time[r+dir[i][0]][c+dir[i][1]]){ //simultaenously spreading
                                board[r+dir[i][0]][c+dir[i][1]] = max(board[r+dir[i][0]][c+dir[i][1]],board[r][c] );
                                unactivated[pair<int,int>(r+dir[i][0],c+dir[i][1])] = board[r+dir[i][0]][c+dir[i][1]];
                            }
                        }
                    }
                }
                
                if((--((*iter).second)) <= 0){
                    activated.erase(iter++);
                }
                else{
                    iter++;
                }
                
                
            }
            
            
        }


        printf("#%d %d\n",test_case,int(activated.size()+unactivated.size()));
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
