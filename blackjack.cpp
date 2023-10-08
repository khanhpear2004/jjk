#include<iostream>
#include<string>
#include<math.h>
#include<cstdlib>
#include<ctime>
#include<unordered_set>

using namespace std;

//enum mark{SPADE=0, CLUB=1, DIAMOND=2, HEART=3};

//enum number{A=1, Two=2, Three=3, Four=4, Five=5, Six=6, Seven=7, Eight=8, Nine=9, Ten=10, J=11, Q=12, K=13};

unordered_set<int> usedCard;

class card{
    private:
        string mark;
        string num;
    public:
        string setMark(){
            return mark;
        }

        void getMark(string mark){
            this->mark = mark;
        }

        string setNum(){
            return num;
        }

        void getNum(string num){
            this->num = num;
        }

        void print(){
            cout<<this->num<<"-"<<this->mark<<" ";
        }
};

class deck{
    public:
        int cards = 52;
        card *draw(int num);
};

class player : public deck{
    private:
        int money;
    public:
        card *hand[5];
        int valOfCard[5];

        int setMoney(){
            return money;
        }

        void getMoney(int money){
            this->money = money;
        }

        void raise(int plus);

        void chooseAValue(int n, int &sum);

        void setValueOfCard(int n);

        int counting(int n);

        void printCard(int n);

        bool blackJack(card *a, card *b);

        void resetHand(){
            for(int i = 0; i < 5; i++){
                hand[i] = nullptr;
            }
        }
};

class dealer : public player{
    public:
        void hiddenCard();
};

class game{
    public:
        bool deal = 0, play = 1, end = 0; int bet;
        void simulated(player *p, dealer *d);

        void printBetting(int bet){
            cout<<"Your bet at the moment is: "<<bet<<endl;
        }
};

card *deck::draw(int num){
    bool hadDrawn = 0;
    card *c = new card();
    string mark;
    while(!hadDrawn){
        if(usedCard.find(num) == usedCard.end()){
            int m =num/13 , n = num%13;
            if(n == 0 && m > 0){
                c->getNum("K");
                switch(m){
                    case 1: mark = "SPADE"; break;
                    case 2: mark = "CLUB"; break;
                    case 3: mark = "DIAMOND"; break;
                    case 4: mark = "HEART"; break;
                }
                c->getMark(mark);
            }
            else{
                switch(n){
                    case 1: c->getNum("A"); break;
                    case 11: c->getNum("J"); break;
                    case 12: c->getNum("Q"); break;
                    case 13: c->getNum("K"); break;
                    default: c->getNum(to_string(n)); break;
                }
                switch(m){
                    case 0: mark = "SPADE"; break;
                    case 1: mark = "CLUB"; break;
                    case 2: mark = "DIAMOND"; break;
                    case 3: mark = "HEART"; break;
                }
                c->getMark(mark);
            }
            usedCard.insert(num);
            hadDrawn = 1;
        }
        else num = rand() % 52 + 1;
    }
    return c;
}

void player::raise(int plus){
    this->money = money - plus;
}

void player::printCard(int n){
    for(int i = 0; i < n; i++){
        hand[i]->print();
    }
}

bool player::blackJack(card *a, card *b){
    if(a->setNum() == "A" && (b->setNum() == "J" || b->setNum() == "Q" || b->setNum() == "K")){
        return true;
    }
    else if(b->setNum() == "A" && (a->setNum() == "J" || a->setNum() == "Q" || a->setNum() == "K")){
        return true;
    }
    else return false;
}

void player::chooseAValue(int n, int &sum){
    int choice; cout<<"choose your A's value: "<<endl;
    if(n == 2){
        cout<<"press 1 to make your A's value = 11"<<endl;
        cout<<"press 2 to make your A's value = 1"<<endl;
        cin>>choice;
        if(choice == 1) sum += 11;
        else if(choice == 2) sum += 1;
    }
    else if(n == 3){
        cout<<"press 1 to make your A's value = 10"<<endl;
        cout<<"press 2 to make your A's value = 1"<<endl;
        cin>>choice;
        if(choice == 1) sum += 10;
        else if(choice == 2) sum += 1;
    }
    
}

void player::setValueOfCard(int n){
    for(int i = 0; i < n; i++){
        if(hand[i]->setNum() == "A"){
            if(n == 2){
                valOfCard[i] = 11;
            }
            else if(n == 3){
                valOfCard[i] = 10;
                if(counting(n) > 11) valOfCard[i] = 1;
            }
            else{
                valOfCard[i] = 1;
            }
        }
        else if(hand[i]->setNum() == "J" || hand[i]->setNum() == "Q" || hand[i]->setNum() == "K"){
            valOfCard[i] = 10;
        }
        else{
            valOfCard[i] = stoi(hand[i]->setNum());
        }
    }
}

int player::counting(int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += valOfCard[i];
    }
    return sum;
}

/*int player::counting(int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        if(hand[i]->setNum() == "A"){
            cout<<"choose the A's value: "<<endl;
        }
        else if(hand[i]->setNum() == "J" || hand[i]->setNum() == "Q" || hand[i]->setNum() == "K") sum += 10;
        else sum += stoi(hand[i]->setNum());
    }
    return sum;
}*/

void game::simulated(player *p, dealer *d){
    int choose; srand(time(0)); int money; p->getMoney(30000);
    cout<<"your current money is: "<<p->setMoney()<<endl;
    while(!end){
        cout<<"BEGIN THE NEW GAME"<<endl;
        cout<<"choose 1 to draw a card if you like"<<endl;
        cout<<"choose 2 to raise your bet before draw a card"<<endl;
        cout<<"choose 3 to stop draw a hold cards"<<endl;
        cout<<"-----------------------------------------------------------"<<endl;
        int num1, num2, phand = 0, dhand = 0;
        cout<<"Now bet your money: "; cin>>bet;
        cout<<"\n";
        p->raise(bet);

        for(int i = 0; i < 2; i++){
            num1 = rand() % 52 + 1; p->hand[i] = p->draw(num1); phand++; //p->cards--;
            num2 = rand() % 52 + 1; d->hand[i] =  d->draw(num2); dhand++; //p->cards--;
        }
        p->setValueOfCard(phand); d->setValueOfCard(dhand);

        cout<<"your cards are: "<<endl;
        p->printCard(phand); cout<<"\n";
        cout<<"The total value of cards is: "<<p->counting(phand)<<endl;
        cout<<"--------------------------------------------------------------"<<endl;
        cout<<"the dealer cards are: "<<endl;
        d->printCard(dhand); cout<<"\n";
        cout<<"The total value of cards is: "<<d->counting(dhand)<<endl;

        while(play){
            if(phand == 2 && p->blackJack(p->hand[0], p->hand[1]) && !d->blackJack(d->hand[0], d->hand[1])){
                cout<<"CONGRATULATION, BLACKJACK - you won double"<<endl;
                p->getMoney(bet*2); bet = 0; break;
            }

            if(phand == 2 && !p->blackJack(p->hand[0], p->hand[1]) && d->blackJack(d->hand[0], d->hand[1])){
                cout<<"UNFORTUNATELY, the dealer has a BLACKJACK - you lose"<<endl;
                bet = 0; break;
            }

            cout<<"\n";
            cout<<"choose your next move: "; cin>>choose;
            int newnum = rand() % 52 + 1;
            switch(choose){
                case 1:{
                    if(phand < 5){
                        p->hand[phand] = p->draw(newnum); phand++; //p->cards--;
                        p->setValueOfCard(phand);
                    }
                    break;
                }
                case 2:{
                    int choice;
                    cout<<"increase your bet: you have 2 options"<<endl;
                    cout<<"1/ DOUBLE YOUR CURRENT BET"<<endl;
                    cout<<"2/ ALL OUT"<<endl;
                    cout<<"your choice is: "; cin>>choice;
                    if(phand < 5){
                        switch(choice){
                            case 1:{
                                p->raise(bet); bet*2; p->hand[phand] = p->draw(newnum); phand++; break; //p->cards--; 
                            }
                            case 2:{
                                p->raise(bet*2); bet*3; p->hand[phand] = p->draw(newnum); phand++; break; //p->cards--; break;
                            }
                        }
                        p->setValueOfCard(phand);
                    }
                    break;
                }
                case 3:{
                    cout<<"you choose to hold, now is the dealer turn: "<<endl;
                    deal = 1; play = 0; break;
                }
                default: end = 1; break;
            }
            cout<<"\n";
            cout<<"-------------------------------------------------------------------"<<endl;
            p->printCard(phand); cout<<"\n"; cout<<"your total value of cards is: "<<p->counting(phand)<<endl;
            cout<<"-------------------------------------------------------------------"<<endl;
            d->printCard(dhand); cout<<"\n"; cout<<"the dealer's total value of cards is: "<<d->counting(dhand)<<endl;
            cout<<"-------------------------------------------------------------------"<<endl;
            if(p->counting(phand) > 21){
                deal = 1; play = 0;
            }
            cout<<"\n";

            if(phand == 5 && p->counting(phand) <= 21){
                cout<<"CONGRATULATION, you won double"<<endl;
                p->getMoney(p->setMoney() + bet*2); bet = 0; break;
            }
        }

        while(deal){
            int dnum = rand() % 52 + 1;
            if(d->counting(dhand) < 15 || (d->counting(dhand) < p->counting(phand)) && (p->counting(phand) < 21) || d->blackJack( d->hand[0], d->hand[1])){
                d->hand[dhand] = d->draw(dnum); dhand++; p->cards--;
                d->setValueOfCard(dhand);
                cout<<"\n";
                cout<<"-------------------------------------------------------------------"<<endl;
                p->printCard(phand); cout<<"\n"; cout<<"your total value of cards is: "<<p->counting(phand)<<endl;
                cout<<"-------------------------------------------------------------------"<<endl;
                d->printCard(dhand); cout<<"\n"; cout<<"the dealer's total value of cards is: "<<d->counting(dhand)<<endl;
                cout<<"-------------------------------------------------------------------"<<endl;
                cout<<"\n";
            }
            else{
                if(d->counting(dhand) > 21){
                    cout<<"You won due to the dealer cards are already over 21"<<endl;
                    cout<<"You recieve: "<<bet<<" chips"<<endl; p->getMoney(p->setMoney() + bet*2);
                }
                else{
                    if(dhand == 5){
                        cout<<"You lose due to the dealer cards are below or equal 21 while already draw 5 cards"<<endl;
                    }
                    else{
                        if(d->counting(dhand) > p->counting(phand) || p->counting(phand) > 21){
                            cout<<"YOU LOSE"<<endl;
                        }
                        else if(d->counting(dhand) == p->counting(phand)){
                            cout<<"IT'S A DRAW"<<endl; p->getMoney(p->setMoney() + bet);
                        }
                        else{
                            cout<<"YOU WIN"<<endl; cout<<"You recieve: "<<bet<<" chips"<<endl; p->getMoney(p->setMoney() + bet*2);                       
                        }
                    }
                }
                deal = 0;
            }
        }

        cout<<"you currently have "<<p->setMoney()<<" chips"<<endl;
        p->resetHand(); d->resetHand(); usedCard.clear(); play = 1; deal = 0;

        /*if(p->cards == 0){
            
        }*/
        if(p->setMoney() <= 0) {
            end = 1;
            cout<<"YOU LOSE ALL MONEY, BETTER LUCK NEXT TIME"<<endl;
        }
    }
}

int main(){
    player *p = new player();
    dealer *d = new dealer();
    game *g = new game();
    g->simulated(p, d);
}

/*int main(){
    srand(time(0));
    unordered_set<int> usedCard;
    int size = usedCard.size();

    while(size < 52){
        int num = rand() % 52 + 1;
        if(usedCard.find(num) == usedCard.end()){
            cout<<num<<" ";
            string card;
            int mark = num/13, val = num%13;
            if(val == 0 && mark > 0){
                card += "K ";
                switch(mark){
                    case 1: card += 6; break;
                    case 2: card += 5; break;
                    case 3: card += 4; break;
                    case 4: card += 3; break;
                }
            }
            else{
                switch(val){
                    case 1: card += "A "; break;
                    case 11: card += "J "; break;
                    case 12: card += "Q "; break;
                    case 13: card += "K "; break;
                    default: card += to_string(val) + " "; break;
                }
                switch(mark){
                    case 0: card += 6; break;
                    case 1: card += 5; break;
                    case 2: card += 4; break;
                    case 3: card += 3; break;
                }
            }
            cout<<card<<endl;
            usedCard.insert(num); size++;
        }
    }

}*/