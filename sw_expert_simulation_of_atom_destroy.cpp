
#include<iostream>
#include<string.h>
#include <set>
using namespace std;

int N,tot_ele;
int board[4001][4001];
int dir[4][2] = { {1,0} , {-1,0} ,{0,-1} , {0,1} };

typedef struct Element{
    int r,c,d,e;
    bool isDead;
}element;

element ele_list[1001];
set<int> die;

int main(int argc, char** argv)
{
    int test_case;
    int T;
    int t_r,t_c,t_e,t_d;
    

    int res;
    int target_r,target_c,target_num;
    cin>>T;
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for(test_case = 1; test_case <= T; ++test_case)
    {
        res = 0;
        memset(board,0,sizeof(board));
        scanf("%d",&N);
        tot_ele = N;
        for(int i = 1 ; i <= N ; i++){
            scanf("%d %d %d %d",&t_c,&t_r,&t_d,&t_e);
            t_r =  (t_r+1000) *2 ;
            t_c = (t_c+1000) *2;
            ele_list[i].c = t_c;
            ele_list[i].r = t_r;
            ele_list[i].e = t_e;
            ele_list[i].d = t_d;
            ele_list[i].isDead = false;
            board[t_r][t_c] = i;
            
        }
        while (tot_ele > 0) {
            die.clear();
            for(int i = 1 ; i  <= N ; i++){
                if(ele_list[i].isDead) continue;
                if (ele_list[i].r+dir[ele_list[i].d][0] > 4000 || ele_list[i].r+dir[ele_list[i].d][0] < 0 || ele_list[i].c+dir[ele_list[i].d][1] > 4000 || ele_list[i].c+dir[ele_list[i].d][1] < 0) { //out of bound
                    ele_list[i].isDead = true;
                    //res+=ele_list[i].e;
                    tot_ele--;
                    if(board[ele_list[i].r][ele_list[i].c] == i) board[ele_list[i].r][ele_list[i].c] = 0;
                    continue;
                }/*else if (board[ ele_list[i].r+dir[ele_list[i].d][0] ][ ele_list[i].r+dir[ele_list[i].d][0] ] != 0) { //cross check
                    target_r =ele_list[i].r+dir[ele_list[i].d][0];
                    target_c =ele_list[i].c+dir[ele_list[i].d][1];
                    target_num = board[target_r][target_c];
                    if((((ele_list[target_num].d + ele_list[i].d) == 1) || ((ele_list[target_num].d + ele_list[i].d) == 5)) && board[ele_list[target_num].r][ele_list[target_num].c] > i){ //up and down ######
                        ele_list[i].isDead = true;
                        ele_list[target_num].isDead = true;
                        res += (ele_list[i].e + ele_list[target_num].e);
                        tot_ele-=2;
                        if(board[ele_list[i].r][ele_list[i].c] == i) board[ele_list[i].r][ele_list[i].c] = 0;
                        board[ele_list[target_num].r][ele_list[target_num].c] = 0;
                        continue;
                    }
                }*/
                if(board[ele_list[i].r][ele_list[i].c] == i) board[ele_list[i].r][ele_list[i].c] = 0; // 내 고향이 내가아니라면 누가 덮어씌운거 걍놔둬
                ele_list[i].r += dir[ele_list[i].d][0];
                ele_list[i].c += dir[ele_list[i].d][1];
                
                if (board[ele_list[i].r][ele_list[i].c] != 0) { //overlap check
                    if(board[ele_list[i].r][ele_list[i].c] < i){ // isOverlapped
                        die.insert(board[ele_list[i].r][ele_list[i].c]);
                        die.insert(i);
                        
                    }
                }
                board[ele_list[i].r][ele_list[i].c] = i;
                
                
            }
            for(set<int>::iterator iter = die.begin(); iter != die.end(); ++iter){ //die
                ele_list[(*iter)].isDead = true;
                res += ele_list[(*iter)].e;
                board[ele_list[(*iter)].r][ele_list[(*iter)].c] = 0;
                tot_ele--;
            }
            
        }
    
    printf("#%d %d\n",test_case,res);
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
