
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<utility>
#include<vector>
#include<set>
#include<string.h>

using namespace std;

int board[100][100];
int dir[4][2] = { { 0,1 }, { 1,0 } , { 0,-1 } , { -1,0 } };
int N,sr,sc;

map<pair<int,int>,int> row_map[100];
map<pair<int,int>,int> col_map[100];

vector<pair<int, int> > worm_hole[5];

set<int,greater<int> > res;

void dfs(int r,int c, int d,int tot);
int main(int argc, char** argv)
{
    int test_case;
    int T;
    
    
    cin>>T;
    for(test_case = 1; test_case <= T; ++test_case)
    {
        res.clear();
        memset(board, 0, sizeof(board));
        
        
        
        scanf("%d",&N);
        
        for(int i = 0 ; i < N ; i++) row_map[i].clear();
        for(int i = 0 ; i < N ; i++) col_map[i].clear();
        for(int i = 0 ; i < 5 ; i++) worm_hole[i].clear();
        
        
        for(int i = 0 ; i < N ; i++){
            for(int j = 0 ;  j < N ; j++){
                scanf("%d",&board[i][j]);
                if (board[i][j] != 0) {
                    row_map[i][pair<int,int>(i,j)] = board[i][j];
                    col_map[j][pair<int,int>(i,j)] = board[i][j];
                }
                if(board[i][j] >= 6 && board[i][j] <=10){
                    worm_hole[board[i][j]-6].push_back(pair<int, int>(i,j));
                }
            }
        }
        
        
        for(int i = 0 ; i < N ; i++){
            for(int j = 0 ;  j < N  ; j++){
                if(board[i][j] == 0){
                    for(int d = 0 ; d < 4; d++){
                        sr = i;
                        sc = j;
                        row_map[sr][pair<int, int>(sr,sc)] = 0;
                        col_map[sc][pair<int, int>(sr,sc)] = 0;
                        
                        dfs(i, j, d, 0);
                        
                        row_map[sr].erase(pair<int, int>(sr,sc));
                        col_map[sc].erase(pair<int, int>(sr,sc));
                        
                    }
                }
                
            }
        }
        
        if(res.empty()) printf("%d",0);
        else printf("#%d %d\n",test_case,*(res.begin()));
        
        
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
void dfs(int r,int c, int d,int tot){
    bool iswall;
    int temp_r,temp_c;
    while(true){
        if ((tot != 0 && r == sr && sc == c)) { //return to start point or black hole
            res.insert(tot-1);
            return;
        }else if (board[r][c] == -1){
            res.insert(tot-1);
            return;
        }
        
        
        if(board[r][c] >= 1 && board[r][c]<= 5){ //change direction
            if (board[r][c] == 1) {
                if (d == 0 || d == 3) d = (d+2)%4;
                else if(d == 1) d = 0;
                else if(d == 2) d = 3;
            } else if (board[r][c] == 2) {
                if (d == 0 || d == 1) d = (d+2)%4;
                else if(d == 2) d = 1;
                else if(d == 3) d = 0;
            } else if (board[r][c] == 3) {
                if (d == 1 || d == 2) d = (d+2)%4;
                else if(d == 3) d = 2;
                else if(d == 0) d = 1;
            } else if (board[r][c] == 4) {
                if (d == 2 || d == 3) d = (d+2)%4;
                else if(d == 0) d = 3;
                else if(d == 1) d = 2;
            } else if (board[r][c] == 5) {
                d = (d+2)%4;
            }
            
            
        }else if(board[r][c] >=6 && board[r][c] <= 10){ //worm hole
            if (worm_hole[board[r][c]-6][0].first != r || worm_hole[board[r][c]-6][0].second != c) {
                temp_r = worm_hole[board[r][c]-6][0].first;
                temp_c = worm_hole[board[r][c]-6][0].second;
            }else{
                temp_r = worm_hole[board[r][c]-6][1].first;
                temp_c = worm_hole[board[r][c]-6][1].second;
            }
            r = temp_r;
            c = temp_c;
        
        }
                        //find path refering to direction
        iswall = true;
        if (d == 0) { //right
            for(map<pair<int,int>,int>::iterator iter = row_map[r].begin(); iter != row_map[r].end(); ++iter){
                if((*iter).first.second > c){
                    if(board[(*iter).first.first][(*iter).first.second] <= 5) {
                        r = (*iter).first.first;
                        c = (*iter).first.second;
                        tot++;
                    } // face brick
                    else {
                        r = (*iter).first.first;
                        c = (*iter).first.second;
                    } //face worm hole or black hole
                    iswall = false;
                    break;
                }
            }
            if (iswall) {
                if(c == N-1 && board[r][c] >=1 && board[r][c] <=5) {
                    //dfs(r, N-1, (d+2)%4, tot+2)
                    d = (d+2)%4;
                    tot+=2;
                }
                else {
                    c = N-1;
                    d = (d+2)%4;
                    tot++;
                }//dfs(r, N-1, (d+2)%4, tot+1);
            }
            
            
        }else if(d == 1) { //down
            for(map<pair<int,int>,int>::iterator iter = col_map[c].begin(); iter != col_map[c].end(); ++iter){
                if((*iter).first.first > r){
                    if(board[(*iter).first.first][(*iter).first.second] <= 5) {
                        r = (*iter).first.first;
                        c = (*iter).first.second;
                        tot++;
                    }//dfs((*iter).first.first, (*iter).first.second, d,tot+1); // face brick
                    else {
                        r = (*iter).first.first;
                        c = (*iter).first.second;
                        
                    }//dfs((*iter).first.first, (*iter).first.second, d,tot); //face worm hole or black hole
                    iswall = false;
                    break;
                }
            }
            if (iswall) {
                if(r == N-1 && board[r][c] >=1 && board[r][c] <=5) {
                    d = (d+2)%4;
                    tot+=2;
                }//dfs(N-1, c, (d+2)%4, tot+2);
                else {
                    r = N-1;
                    d = (d+2)%4;
                    tot++;
                }//dfs(N-1, c, (d+2)%4, tot+1);
            }
        }else if(d == 2) { //left
            for(map<pair<int,int>,int>::iterator iter = (--row_map[r].end());;){
                if((*iter).first.second < c){
                    if(board[(*iter).first.first][(*iter).first.second] <= 5) {
                        r = (*iter).first.first;
                        c = (*iter).first.second;
                        tot++;
                    }//dfs((*iter).first.first, (*iter).first.second, d,tot+1); // face brick
                    else {
                        r = (*iter).first.first;
                        c = (*iter).first.second;
                        
                    }//dfs((*iter).first.first, (*iter).first.second, d,tot); //face worm hole or black hole
                    iswall = false;
                    break;
                }
                if (iter == row_map[r].begin()) break;
                else --iter;
                
            }
            if (iswall) {
                if(c == 0 && board[r][c] >=1 && board[r][c] <=5) {
                    d = (d+2)%4;
                    tot+=2;
                }//dfs(r, 0, (d+2)%4, tot+2);
                else {
                    c = 0;
                    d = (d+2)%4;
                    tot++;
                }//dfs(r, 0, (d+2)%4, tot+1);
            }
        }else if(d == 3) { //up
            for(map<pair<int,int>,int>::iterator iter = (--col_map[c].end());;){
                if((*iter).first.first < r){
                    if(board[(*iter).first.first][(*iter).first.second] <= 5) {
                        r = (*iter).first.first;
                        c = (*iter).first.second;
                        tot++;
                    }//dfs((*iter).first.first, (*iter).first.second, d,tot+1); // face brick
                    else {
                        r = (*iter).first.first;
                        c = (*iter).first.second;
                        
                    }//dfs((*iter).first.first, (*iter).first.second, d,tot); //face worm hole or black hole
                    iswall = false;
                    break;
                }
                if (iter == col_map[c].begin()) break;
                else --iter;
                
            }
            if (iswall) {
                if(r == 0 && board[r][c] >=1 && board[r][c] <=5) {
                    d = (d+2)%4;
                    tot+=2;
                }//dfs(0, c, (d+2)%4, tot+2);
                else {
                    r = 0;
                    d = (d+2)%4;
                    tot++;
                }//dfs(0, c, (d+2)%4, tot+1);
            }
        }
        
    }
    
    
}
