#include<bits/stdc++.h>
using namespace std;
vector<string> acc;
map <string,int> money_trans;
map <string,vector<string>> fr_to;
int dem;

bool checkacc(string s) {
    if( s.length() >=6 && s.length() <= 20) return true;
    else return false;
}

void checkLane(string s , int k, int n,vector<string> pair ) {
    if(pair.empty()) pair.push_back(s);
    for(int i = 0; i < fr_to[pair.back()].size();i++) {
        if( !count(pair.begin(),pair.end(), fr_to[pair.back()][i]) ) {
        pair.push_back(fr_to[pair.back()][i]);    
        checkLane(s, k+1,n,pair);
        pair.pop_back();
        }
        else {
            if( k == n-1 && s == fr_to[pair.back()][i]) {
            dem ++;
            }
        }
    }
}


int main() {
    string fr_acc;
    int num = 0;
    int total_money = 0;
    do{
        cin >> fr_acc;
        if( fr_acc == "#") continue;
        string to_acc, money, time_pt,atm;
        cin >> to_acc >> money >> time_pt >> atm;
        if(checkacc(fr_acc) && checkacc(to_acc)) {
            num++;
            total_money += stoi(money);
            money_trans[fr_acc] += stoi(money); 
            if( !count(fr_to[fr_acc].begin(), fr_to[fr_acc].end(), to_acc) ) fr_to[fr_acc].push_back(to_acc);
            if( !count(acc.begin(), acc.end(), fr_acc) ) acc.push_back(fr_acc);
            if( !count(acc.begin(), acc.end(), to_acc) ) acc.push_back(to_acc);
        }
        
    } while ( fr_acc != "#");

    string type;
    do{
        cin >> type;
        if(type == "#") continue;
        if(type == "?number_transactions") cout<< num << endl;
        else if( type == "?total_money_transaction") cout << total_money << endl;
        else if( type == "?list_sorted_accounts") {
            sort(acc.begin(),acc.end());
            for(int i = 0; i < acc.size();i++) cout<< acc[i] <<" ";
        }
        else if( type == "?total_money_transaction_from") {
            string data;
            cin >> data;
            cout << money_trans[data] << endl;
        }
        else if( type == "?inspect_cycle") {
            dem = 0;
            string account;
            int k;
            vector<string> check;
            cin >> account>> k;   
            checkLane(account,0,k,check);    
            if(dem >0) cout << "1" << endl; else cout << "0" << endl;
        }
    } while( type != "#");
    return 0;
}