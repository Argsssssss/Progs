#include <iostream>
using namespace std;
string base_cards[4] = {"♠", "♥", "♦", "♣"};
struct Card{int card, suits;};
string card_collection(int card){
    string over_char[] = {"10", "J", "Q", "K", "A"};
    if(card > 9){
        return over_char[card - 10];
    }else{
        return to_string(card);
    }
    return "ERROR";
}

void print_C(Card card_1, Card card_2){
    cout << "╔═════╗" << "  " << "╔═════╗\n";
    cout << "║" << card_collection(card_1.card);
    if(card_1.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_1.suits % 4] <<"║  ║" << card_collection(card_2.card);
    if(card_2.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_2.suits % 4] << "║" << endl;
    cout << "║     ║  ║     ║\n";

    cout << "║" << base_cards[card_1.suits % 4];
    if(card_1.card == 10){cout <<"  ";} else{cout <<"   ";} cout << card_collection(card_1.card) <<"║  ║" << base_cards[card_2.suits % 4];
    if(card_2.card == 10){cout <<"  ";} else{cout <<"   ";} cout << card_collection(card_2.card) << "║";

    cout << "\n╚═════╝" << "  " << "╚═════╝\n";
}
void print_C(Card card_1, Card card_2, Card card_3, Card card_4, Card card_5, int numb_round){

    cout << "╔═════╗" << "  " << "╔═════╗" << "  " << "╔═════╗" << "  " << "╔═════╗" << "  " << "╔═════╗\n";
    switch(numb_round){
        case 0:
            cout << "║" << "*   " << '*' <<"║  ║" << "*   " << '*' << "║  ║" << "*   " << '*' <<"║  ║" << "*   " << '*' << "║  ║" << "*   " << '*' << "║" << endl; 
            cout << "║     ║  ║     ║  ║     ║  ║     ║  ║     ║\n";
            cout << "║" << "*   " << '*' <<"║  ║" << "*   " << '*' << "║  ║" << "*   " << '*' <<"║  ║" << "*   " << '*' << "║  ║" << "*   " << '*' << "║";
            break;
        case 1:
            cout << "║" << card_collection(card_1.card);
            if(card_1.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_1.suits % 4] <<"║  ║" << card_collection(card_2.card);
            if(card_2.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_2.suits % 4] << "║  ║" << card_collection(card_3.card);
            if(card_3.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_3.suits % 4] <<"║  ║";
            cout << "*   " << '*' << "║  ║" << "*   " << '*' << "║" << endl;
            cout << "║     ║  ║     ║  ║     ║  ║     ║  ║     ║\n";
            cout << "║" << base_cards[card_1.suits % 4];
            if(card_1.card == 10){cout <<"  ";} else{cout <<"   ";} cout << card_collection(card_1.card)  <<"║  ║" << base_cards[card_2.suits % 4];
            if(card_2.card == 10){cout <<"  ";} else{cout <<"   ";} cout <<  card_collection(card_2.card) << "║  ║" << base_cards[card_3.suits % 4];
            if(card_3.card == 10){cout <<"  ";} else{cout <<"   ";} cout << card_collection(card_3.card) <<"║  ║";
            cout << "*   " << '*' << "║  ║" << "*   " << '*' << "║";
            break;
        case 2:
            cout << "║" << card_collection(card_1.card);
            if(card_1.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_1.suits % 4] <<"║  ║" << card_collection(card_2.card);
            if(card_2.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_2.suits % 4] << "║  ║" << card_collection(card_3.card);
            if(card_3.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_3.suits % 4] <<"║  ║" << card_collection(card_4.card);
            if(card_4.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_4.suits % 4] << "║  ║" << "*   ";
            cout << '*' << "║" << endl;
            cout << "║     ║  ║     ║  ║     ║  ║     ║  ║     ║\n";
            cout << "║" << base_cards[card_1.suits % 4];
            if(card_1.card == 10){cout <<"  ";} else{cout <<"   ";} cout << card_collection(card_1.card)  <<"║  ║" << base_cards[card_2.suits % 4];
            if(card_2.card == 10){cout <<"  ";} else{cout <<"   ";} cout <<  card_collection(card_2.card) << "║  ║" << base_cards[card_3.suits % 4];
            if(card_3.card == 10){cout <<"  ";} else{cout <<"   ";} cout << card_collection(card_3.card) <<"║  ║" << base_cards[card_4.suits % 4];
            if(card_4.card == 10){cout <<"  ";} else{cout <<"   ";} cout << card_collection(card_4.card) << "║  ║" << "*   ";
            cout << '*' << "║";
            break;
        case 3:
            cout << "║" << card_collection(card_1.card);
            if(card_1.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_1.suits % 4] <<"║  ║" << card_collection(card_2.card);
            if(card_2.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_2.suits % 4] << "║  ║" << card_collection(card_3.card);
            if(card_3.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_3.suits % 4] <<"║  ║" << card_collection(card_4.card);
            if(card_4.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_4.suits % 4] << "║  ║" << card_collection(card_5.card);
            if(card_5.card == 10){cout <<"  ";} else{cout <<"   ";} cout << base_cards[card_5.suits % 4] << "║" << endl; 
            cout << "║     ║  ║     ║  ║     ║  ║     ║  ║     ║\n";
            cout << "║" << base_cards[card_1.suits % 4];
            if(card_1.card == 10){cout <<"  ";} else{cout <<"   ";} cout << card_collection(card_1.card)  <<"║  ║" << base_cards[card_2.suits % 4];
            if(card_2.card == 10){cout <<"  ";} else{cout <<"   ";} cout <<  card_collection(card_2.card) << "║  ║" << base_cards[card_3.suits % 4];
            if(card_3.card == 10){cout <<"  ";} else{cout <<"   ";} cout << card_collection(card_3.card) <<"║  ║" << base_cards[card_4.suits % 4];
            if(card_4.card == 10){cout <<"  ";} else{cout <<"   ";} cout << card_collection(card_4.card) << "║  ║" << base_cards[card_5.suits % 4];
            if(card_5.card == 10){cout <<"  ";} else{cout <<"   ";} cout << card_collection(card_5.card) << "║";
            break;
    }
    cout << "\n╚═════╝" << "  " << "╚═════╝" << "  " << "╚═════╝" << "  " << "╚═════╝" << "  " << "╚═════╝\n";
}
void print_on_table(Card mass_cards[], int numb_round){
    Card card_on_tab_1, card_on_tab_2, card_on_tab_3, card_on_tab_4, card_on_tab_5;
    card_on_tab_1.card = mass_cards[0].card;
    card_on_tab_1.suits = mass_cards[0].suits;
    card_on_tab_2.card = mass_cards[1].card;
    card_on_tab_2.suits = mass_cards[1].suits;
    card_on_tab_3.card = mass_cards[2].card;
    card_on_tab_3.suits = mass_cards[2].suits;
    card_on_tab_4.card = mass_cards[3].card;
    card_on_tab_4.suits = mass_cards[3].suits;
    card_on_tab_5.card = mass_cards[4].card;
    card_on_tab_5.suits = mass_cards[4].suits;
    print_C(card_on_tab_1, card_on_tab_2, card_on_tab_3, card_on_tab_4, card_on_tab_5, numb_round);
}
void print_of_users(Card mass_cards[],int numb_users){
    if(numb_users > 6){
        Card card_1_user_1;
        Card card_2_user_1;
        card_1_user_1.card = mass_cards[5].card;
        card_1_user_1.suits = mass_cards[5].suits;
        card_2_user_1.card = mass_cards[6].card;
        card_2_user_1.suits = mass_cards[6].suits;
        print_C(card_1_user_1, card_2_user_1);
        if(numb_users > 8){
            Card card_1_user_2;
            Card card_2_user_2;
            card_1_user_2.card = mass_cards[7].card;
            card_1_user_2.suits = mass_cards[7].suits;
            card_2_user_2.card = mass_cards[8].card;
            card_2_user_2.suits = mass_cards[8].suits;
            print_C(card_1_user_2, card_2_user_2);
            if(numb_users > 10){
                Card card_1_user_3;
                Card card_2_user_3;
                card_1_user_3.card = mass_cards[9].card;
                card_1_user_3.suits = mass_cards[9].suits;
                card_2_user_3.card = mass_cards[10].card;
                card_2_user_3.suits = mass_cards[10].suits;
                print_C(card_1_user_3, card_2_user_3);
                if(numb_users > 12){
                    Card card_1_user_4;
                    Card card_2_user_4;
                    card_1_user_4.card = mass_cards[11].card;
                    card_1_user_4.suits = mass_cards[11].suits;
                    card_2_user_4.card = mass_cards[12].card;
                    card_2_user_4.suits = mass_cards[12].suits;
                    print_C(card_1_user_4, card_2_user_4);
                    if(numb_users > 14){
                        Card card_1_user_5;
                        Card card_2_user_5;
                        card_1_user_5.card = mass_cards[13].card;
                        card_1_user_5.suits = mass_cards[13].suits;
                        card_2_user_5.card = mass_cards[14].card;
                        card_2_user_5.suits = mass_cards[14].suits;
                        print_C(card_1_user_5, card_2_user_5);
                    }
                }
            }
        }
    }
}
// ╔═════╗
// ║A   ♠║ print_C(14,0)
// ║     ║
// ║♠   A║
// ╚═════╝ 
