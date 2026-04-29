// struct Card{int card, suits;};

int senior_card(Card cards[], int numb_users){
    int max = 0;
    for(int i = 5; i < numb_users; i++){ // максимальная пара
        if(cards[i].card > max){
            max = cards[i].card;
        }
    }for(int i = 5; i < numb_users; i++){ // максимальная пара
        if(cards[i].card == max){
            return i;
        }
    }
    return 0;
}
int pair_k(Card cards[], int numb_users){
    struct Base_pairs{
        size_t user, pair_card;
        char L_R;
    }; // номер юзера, пара чего и какая из карт совпадает
    Base_pairs bp[5]{0,0};
    int k = 0;
    for(size_t j = 5; j < numb_users; j+=2){ // пара в руках
        if(cards[j].card == cards[j + 1].card){
            bp[k].user = j;
            bp[k].pair_card = cards[j].card;
            k++; 
        }
    }
    for(size_t i = 0; i < 5; i++){ // пара со столом
        for(size_t j = 5; j < numb_users; j++){
            if(cards[i].card == cards[j].card){
                bp[k].user = j;
                bp[k].pair_card = cards[j].card;
                if(j % 2 != 0){
                    bp[k].L_R = 'L';
                }else{
                    bp[k].L_R = 'R';
                }
                k++;
            }
        }
    }
    int max = 0;
    for(int i = 0; i < 5; i++){ // максимальная пара
        if(bp[i].pair_card > max){
            max = bp[i].pair_card;
        }
    }
    for(int i = 0; i < 5; i++){ // очищаем содержимое остальных совпадений, чтобы не было ошибок
        if(max != bp[i].pair_card){
            bp[i] = {0,0,char(NULL)};
        }
        for(int j = i + 1 % 5; j < 5; j++){
            if(bp[i].user == bp[j].user && bp[i].pair_card == bp[j].pair_card && bp[i].L_R == bp[j].L_R){
                bp[j] = {0,0,char(NULL)};
            }
        }
    }
    int pare_coincidence = 0;
    for(int i = 0, j = 0; i < 5; i++){
        if(bp[i].pair_card > 0){
            pare_coincidence++;
        }
    }
    // cout << "pare_coincidence: " << pare_coincidence << endl;
    // for(int i = 0; i < 5; i++){ // возврат юзера с максимальной парой
    //     cout << bp[i].user << " | " << bp[i].pair_card << " | " << bp[i].L_R << endl;
    // }
    if(pare_coincidence < 2){ // Выиграл по совпадению со столом или в руках
        for(int i = 0; i < 5; i++){
            if(bp[i].pair_card == max){
                return bp[i].user;
            }
        }
    }else{ // Выиграл из нескольких совпадений по старшей карте
        struct base_max_L_R{
        int user, L_R;
        }base_L_R[3]{0,0};
        k = 0;
        for(int i = 0; i < 5; i++){
            if(max == bp[i].pair_card && bp[i].pair_card != 0){ // если он нашел еще одну максимальную пару
                if(bp[i].L_R == 'L'){
                    base_L_R[k].user = bp[i].user + 1;
                    base_L_R[k].L_R = cards[bp[i].user + 1].card;
                    k++;
                }else{
                    base_L_R[k].user = bp[i].user - 1;
                    base_L_R[k].L_R = cards[bp[i].user - 1].card;
                    k++;
                }
            }
        }
        int max_L_R = 0;
        for(int i = 0; i < 3; i++){
            if(base_L_R[i].L_R > max_L_R){
                max_L_R = base_L_R[i].L_R;
            }
        }
        // cout << "Max_SOSED: " << max_L_R << endl;
        for(int i = 0; i < 3; i++){
            if(base_L_R[i].L_R == max_L_R){
                return base_L_R[i].user;
            }
        }
    }
    return 0;
}
int two_pair(Card cards[], int numb_users){
    struct Base_boub_pairs{
        size_t user, pair_card;
        char L_R;
    };
    Base_boub_pairs bdp[20]{0,0, char(NULL)};
    int k = 0;
    for(size_t i = 0; i < 5; i++){
        for(size_t j = i + 1; j < 5; j++){
            if(cards[i].card == cards[j].card){ // пара на столе
                bdp[k].user = j;
                bdp[k].pair_card = cards[j].card;
                // cout << "User: " << bdp[k].user << " Pair: " << bdp[k].pair_card << endl;
                k++;
            }
        }
    }
    for(size_t i = 5; i < numb_users; i+=2){
        if(cards[i].card == cards[i + 1].card){ // пара в руках
            bdp[k].user = i;
            bdp[k].pair_card = cards[i].card;
            // cout << "User: " << bdp[k].user << " Pair: " << bdp[k].pair_card << endl;
            k++;
        }
    }
    for(size_t i = 0; i < 5; i++){ // пара со столом
        for(size_t j = 5; j < numb_users; j++){
            if(cards[i].card == cards[j].card){
                bdp[k].user = j;
                bdp[k].pair_card = cards[j].card;
                if(j % 2 != 0){
                    bdp[k].L_R = 'L';
                }else{
                    bdp[k].L_R = 'R';
                }
                k++;
            }
        }
    }
    for(size_t i = 0; i < k; i++){
        for(size_t j = 0; j < k; j++){
            if(bdp[i].user < bdp[j].user){
                swap(bdp[i].user, bdp[j].user);
                swap(bdp[i].pair_card, bdp[j].pair_card);
                swap(bdp[i].L_R, bdp[j].L_R);
            }
        }
    }
    int max_pair_table = 0;
    int max_pair_user = 0;
    for(size_t i = 0; i < 5;i++){
        if(bdp[i].user < 5){
            if(bdp[i].pair_card > max_pair_table){
                max_pair_table = bdp[i].pair_card;
            }
        }
    }
    for(size_t i = 0; i < k; i++){
        cout << "User: " << bdp[i].user << " Pair: " << bdp[i].pair_card << " " << bdp[i].L_R << endl;
    }
    cout << "MAX pair table " << max_pair_table << endl;
    return 0;
}
int set(Card cards[], int numb_users){
    struct Base_boub_pairs{
        size_t user, pair_card;
        char L_R;
    };
    Base_boub_pairs bdp[20]{0,0, char(NULL)};
    int k = 0;
    for(size_t i = 0; i < 5; i++){
        for(size_t j = i + 1; j < 5; j++){
            if(cards[i].card == cards[j].card){ // пара на столе
                bdp[k].user = j;
                bdp[k].pair_card = cards[j].card;
                // cout << "User: " << bdp[k].user << " Pair: " << bdp[k].pair_card << endl;
                k++;
            }
        }
    }
    for(size_t i = 5; i < numb_users; i+=2){
        if(cards[i].card == cards[i + 1].card){ // пара в руках
            bdp[k].user = i;
            bdp[k].pair_card = cards[i].card;
            // cout << "User: " << bdp[k].user << " Pair: " << bdp[k].pair_card << endl;
            k++;
        }
    }
    for(size_t i = 0; i < 5; i++){ // пара со столом
        for(size_t j = 5; j < numb_users; j++){
            if(cards[i].card == cards[j].card){
                bdp[k].user = j;
                bdp[k].pair_card = cards[j].card;
                if(j % 2 != 0){
                    bdp[k].L_R = 'L';
                }else{
                    bdp[k].L_R = 'R';
                }
                k++;
            }
        }
    }
    for(size_t i = 0; i < k; i++){
        for(size_t j = 0; j < k; j++){
            if(bdp[i].user < bdp[j].user){
                swap(bdp[i].user, bdp[j].user);
                swap(bdp[i].pair_card, bdp[j].pair_card);
                swap(bdp[i].L_R, bdp[j].L_R);
            }
        }
    }
    int max_set = 0;
    for(size_t i = 0; i < k; i++){
        for(size_t j = i + 1; j < k; j++){
            if(bdp[i].user == bdp[j].user && bdp[i].pair_card == bdp[j].pair_card){
                max_set = bdp[i].pair_card;
                // cout << "User: " << bdp[i].user << " | " << bdp[i].pair_card << " | " << bdp[i].L_R << endl; 
            }
            // else{bdp[i].user = 0; bdp[i].pair_card = 0; bdp[i].L_R = char(NULL);}
        }
    }
    for(size_t i = 0; i < k; i++){
        if(max_set == bdp[i].pair_card){
            for(size_t j = i + 1; j < k; j++){
                if(bdp[i].pair_card == bdp[j].pair_card && bdp[i].user != bdp[j].user){
                    if(bdp[i].L_R == 'L'){
                        if(bdp[j].L_R == 'L'){
                            if(bdp[i + 1].pair_card > bdp[j + 1].pair_card){
                                return bdp[i].user;
                            }else{
                                return bdp[j].user;
                            }
                        }else{
                            if(bdp[i + 1].pair_card > bdp[j - 1].pair_card){
                                return bdp[i].user;
                            }else{
                                return bdp[j].user;
                            }
                        }
                    }else if(bdp[i].L_R = 'R'){
                        if(bdp[j].L_R == 'L'){
                            if(bdp[i - 1].pair_card > bdp[j + 1].pair_card){
                                return bdp[i].user;
                            }else{
                                return bdp[j].user;
                            }
                        }else{
                            if(bdp[i - 1].pair_card > bdp[j - 1].pair_card){
                                return bdp[i].user;
                            }else{
                                return bdp[j].user;
                            }
                        }
                    }else{

                    }
                }
            }
            // cout << "User: " << bdp[i].user << " | " << bdp[i].pair_card << " | " << bdp[i].L_R << endl; 
            return bdp[i].user;
        }
    }
    return 0;
}
int street(Card cards[], int numb_users){
    return 0;
}
int flash(Card cards[], int numb_users){
    return 0;
}
int full_house(Card cards[], int numb_users){
    // if(set(cards, numb_users) == pair_k(cards, numb_users)){return set(cards, numb_users);}
    return 0;
}
int kare(Card cards[], int numb_users){
    return 0;
}
int street_flash(Card cards[], int numb_users){
    return 0;
}
int flash_royal(Card cards[], int numb_users){
    return 0;
}
int logic(Card cards[], int numb_users){ // Возвращает номер игрока, который выиграл
    int user = 0;
    
    if(two_pair(cards, numb_users) != 0){
        cout <<"Two_pair: ";
        return two_pair(cards, numb_users);
    }

    // if(flash_royal(cards, numb_users) != 0){
    //     return flash_royal(cards, numb_users);
    // }else if(street_flash(cards, numb_users) != 0){
    //     return street_flash(cards, numb_users);
    // }else if(kare(cards, numb_users) != 0){
    //     return kare(cards, numb_users);
    // }else if(full_house(cards, numb_users) != 0){
    //     return full_house(cards, numb_users);
    // }else if(flash(cards, numb_users) != 0){
    //     return flash(cards, numb_users);
    // }else if(street(cards, numb_users) != 0){
    //     return street(cards, numb_users);
    // }else if(set(cards, numb_users) != 0){
    //     cout << "Set: ";
    //     return set(cards, numb_users);
    // }
    // else if(two_pair(cards, numb_users) != 0){
    //     cout <<"Two_pair: ";
    //     return two_pair(cards, numb_users);
    // }else if(pair_k(cards, numb_users) != 0){
    //     cout << "Pair: ";
    //     return pair_k(cards, numb_users);
    // }else{
    //     cout << "Senior_card: ";
    //     return senior_card(cards, numb_users);
    // }
    return 0;
}