#include <iostream>
#include "pr_cards.h"
#include "gen_cards.h"
#include "logic.h"


// 7 - 1 user
// 9 - 2 users
// 11 - 3 users 
// 13 - 4 users
// 15 - 5 users
#define users 15
using namespace std;
int main(){
    system("clear");
    cout << "-------------------ALL_IN-------------------\n";
    Card mass_cards[users];
    gen_cards_for_users(mass_cards, users);
    print_on_table(mass_cards, 3);
    print_of_users(mass_cards, users);
    int user = logic(mass_cards, users);

    if(user > 4 && user < 7){
        cout << "User 1 WIN";
    }else if(user > 6 && user < 9){
        cout << "User 2 WIN";
    }else if(user > 8 && user < 11){
        cout << "User 3 WIN";
    }else if(user > 10 && user < 13){
        cout << "User 4 WIN";
    }else if(user > 12 && user < 16){
        cout << "User 5 WIN";
    }else{
        cout << "FULL_loose ";
    }
    cout << endl;

    return 0;
}
