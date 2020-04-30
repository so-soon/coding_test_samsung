#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int N,W,H;



int combi[4];

int board[15][12];
int temp_board[15][12];
int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
int left_temp;
int co_brick;

set<int> res;

void dfs(int depth);
void boom(int r,int c);


int main(int argc, char** argv)
{
    int test_case;
    int T;
    scanf("%d",&T);
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for(test_case = 1; test_case <= T; ++test_case)
    {
        scanf("%d %d %d",&N,&W,&H);
        co_brick = 0;
        res.clear();
        
        for(int i = 0 ; i < H ; i++){
            for(int j = 0 ; j < W; j++){
                scanf("%d",&board[i][j]);
                if(board[i][j] >= 1) co_brick++;
            }
        }
        dfs(0);
        
        printf("#%d %d\n",test_case,*(res.begin()));
    }
    
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
void dfs(int depth){
    int r,c,space_num;
    if (depth == N) {
        left_temp = co_brick;
        //printf("\n\n size : %d\n",res.size());
        for(int i = 0 ; i < H ; i++){
            for(int j = 0 ; j < W; j++){
                temp_board[i][j] = board[i][j];
            }
        }
        //boom
        for(int i = 0 ; i < N; i++){
            r = 0;
            c =combi[i];
            while (temp_board[r][c] == 0 && r < H) {
                r++;
            }
            if(r >= H){
                continue;
            }else boom(r, c);
            
            //fill empty space
            
            for(int nc = 0; nc < W; nc++){
                space_num = 0;
                for(int nr = H-1; nr >=0; nr--){
                    if(temp_board[nr][nc] == 0) space_num++;
                    else if(space_num != 0){
                        temp_board[nr+space_num][nc] = temp_board[nr][nc];
                        temp_board[nr][nc] = 0;
                    }
                    
                }
                
            }/*
            printf("boom : %d \n",combi[i]);
            printf("\n");
            printf("\n");
            for(int wk = 0 ; wk < H ; wk++){
                for(int j = 0 ; j < W; j++){
                    printf("%d ",temp_board[wk][j]);
                }
                printf("\n");
            }*/
        }
        //for(auto ab = res.begin() ; ab != res.end(); ab++) printf("%d ",*(ab));
        
        //printf("\n\n");
        
        if(res.find(left_temp) == res.end()) res.insert(left_temp);
        
        
    }else{ // permutation
        for(int i = 0 ; i < W; i++){
    
        
            combi[depth] = i;
            dfs(depth+1);
        }
        
    }
    
}
void boom(int r,int c){
    int num;
    if (temp_board[r][c] == 0) {
        return;
    }else if(temp_board[r][c] == 1){
        left_temp--;
        temp_board[r][c] = 0;
        return;
    }else{
        //int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
        
        num = temp_board[r][c];
        temp_board[r][c] = 0;
        left_temp--;
        //down
        for(int d = 0 ; d < 4 ; d++){
            for(int i = 1; i <= num-1;i++){
                if (r+(dir[d][0]*i) >= 0 && r+(dir[d][0]*i) < H  && c+(dir[d][1]*i) >= 0 && c+(dir[d][1]*i) < W) {
                    boom(r+(dir[d][0]*i), c+(dir[d][1]*i));
                }
                else break;
            }
        }
        return;
    }
    
}
