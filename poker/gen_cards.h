#include <random>
// Дебаг должен обращаться к базе данных карт и к уже сгенерированным картам, если уже такие имеются на столе и флаг стола true,
// если на столе такая имеется, если флаг стола true, то требуется перегенерация карты, пока не исчезнет флаг стола
#define STS 4
#define CRD 15
const Card base_card[] = {
        2,0, 2,1, 2,2, 2,3, // 0 1 2 3
        3,0, 3,1, 3,2, 3,3, // 4 5 6 7
        4,0, 4,1, 4,2, 4,3,
        5,0, 5,1, 5,2, 5,3,
        6,0, 6,1, 6,2, 6,3,
        7,0, 7,1, 7,2, 7,3,
        8,0, 8,1, 8,2, 8,3,
        9,0, 9,1, 9,2, 9,3,
        10,0, 10,1, 10,2, 10,3,
        11,0, 11,1, 11,2, 11,3,
        12,0, 12,1, 12,3, 12,3,
        13,0, 13,1, 13,3, 13,3,
        14,0, 14,1, 14,2, 14,3
};
int rc4(int MIN, int MAX){
    random_device RNDOM;
    size_t S[255], result = 0, j = 0;
    for(size_t i = 0; i < 255;i++){
        S[i] = i;
    }
    for(size_t i = 0; i < 255;i++){
        j = (j + S[i] + RNDOM()) % 255;
        swap(S[i], S[j]);
    }
    size_t seed = RNDOM() % 255;
    for(size_t i = 0, t, buff_i, buff_j; i < seed; i++){
        buff_i = (buff_i + 1) % 255;
        buff_j = (buff_j + S[buff_i]) % 255;
        swap(S[buff_i], S[buff_j]);
        t = (S[buff_i] + S[buff_j]) % 255;
        result += S[t] % 255;
    }
    if(result % MAX < MIN){
            result += result + MIN;
            result %= MAX;
    }else{
        result %= MAX;
    }
    if(result < MIN){
        result += MIN;
    }
    return result;
}
void sotr_cards(Card cards[], int numb_users){
    int flags[52]{0};
    //mass_cards[] {card, suits...}
    for(int i = 0; i < numb_users; i++){
        for(int j = 0; j < 52; j++){
            if(cards[i].card == base_card[j].card && cards[i].suits == base_card[j].suits){
                flags[j]++;
                if(flags[j] > 1){
                    // cout << "! ";
                    while(true){
                        size_t rand_flag = rc4(0,52);
                        // cout << rand_flag << " rand_flag | " << base_card[rand_flag].card << ": " << base_card[rand_flag].suits << endl;
                        if(flags[rand_flag] == 0){
                            cards[i].card = base_card[rand_flag].card;
                            cards[i].suits = base_card[rand_flag].suits;
                            flags[j]--;
                            break;
                        }
                    }
                }
            }
        }
    }
    // for(int i = 0; i < 52; i++){
    //     cout << flags[i] << " --- " << base_card[i].card << " : " << base_card[i].suits << endl;
    // }
}
void gen_cards_for_users(Card mass_cards[], int numb_users){ // 4 только стол, выше 4 уже игроки
// struct Card{int card, suits;}; карта, масть
    mass_cards[0] = {rc4(2,CRD), rc4(0,STS)};
    mass_cards[1] = {rc4(2,CRD), rc4(0,STS)};
    mass_cards[2] = {rc4(2,CRD), rc4(0,STS)};
    mass_cards[3] = {rc4(2,CRD), rc4(0,STS)};
    mass_cards[4] = {rc4(2,CRD), rc4(0,STS)};
    if(numb_users > 6){
        mass_cards[5] = {rc4(2,CRD), rc4(0,STS)};
        mass_cards[6] = {rc4(2,CRD), rc4(0,STS)};
        if(numb_users > 8){
            mass_cards[7] = {rc4(2,CRD), rc4(0,STS)};
            mass_cards[8] = {rc4(2,CRD), rc4(0,STS)};
            if(numb_users > 10){
                mass_cards[9] = {rc4(2,CRD), rc4(0,STS)};
                mass_cards[10] = {rc4(2,CRD), rc4(0,STS)};
                if(numb_users > 12){
                    mass_cards[11] = {rc4(2,CRD), rc4(0,STS)};
                    mass_cards[12] = {rc4(2,CRD), rc4(0,STS)};
                    if(numb_users > 14){
                        mass_cards[13] = {rc4(2,CRD), rc4(0,STS)};
                        mass_cards[14] = {rc4(2,CRD), rc4(0,STS)};
                    }
                }
            }
        }
    }
    sotr_cards(mass_cards, numb_users);
}

// Дебаг должен обращаться к базе данных карт и к уже сгенерированным картам, если уже такие имеются на столе и флаг стола true,
// если на столе такая имеется, если флаг стола true, то требуется перегенерация карты, пока не исчезнет флаг стола

