#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int N,K;
deque<char> box;
set<int,greater<int> > res;

int hex_to_dec(int idx);

int main(int argc, char** argv)
{
    int test_case;
    int T;
    char temp;
    bool isfail = false;
    set<int>::iterator iter;
    scanf("%d",&T);
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for(test_case = 1; test_case <= T; ++test_case)
    {
        res.clear();
        box.clear();
        isfail = false;
        
        scanf("%d %d",&N,&K);
        scanf("%c",&temp);
        for(int i = 0 ; i < N; i++){
            scanf("%c",&temp);
            box.push_back(temp);
        }
        
        
        
        while(!isfail){
            isfail = true;
            
            for(int i = 0 ; i < N; i+=(N/4)){
                if(res.insert(hex_to_dec(i)).second){
                    isfail = false;
                }
                
            }
            
            box.push_front(box.back());
            box.pop_back();
        }
        iter = res.begin();
        
        for(int i = 0 ; i < K-1 ; i++){
            iter++;
        }

        
        printf("#%d ",test_case);
        printf("%d\n",*(iter));
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

int hex_to_dec(int idx){
    
    int result = 0,e = 1;
    
    for (int i = 0 ; i < (N/4)-1; i++) {
        e = e*16;
    }
    
    for(int i  = 0 ; i < (N/4) ; i++){
        if (box[idx] >= 48 && box[idx]<=57) {
            result = result + (int(box[idx])-48)*e;
        }else{
            result = result + (int(box[idx])-55)*e;
        }
        
        e = e/16;
        idx++;
        
    }
    
    
    return result;
}
