#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

using namespace std;

class table
{
public:
    int ID;
    string name;
    int age;
    table* next;
    table(int ID, string name, int age, table* next)
    {
        this->ID = ID;
        this->name = name;
        this->age = age;
        this->next = next;
    }
};

class restaurant
{
public:
    table *recentTable;
    restaurant()
    {
        recentTable = nullptr;
    }
    ~restaurant()
    {
        delete recentTable;
    }
    table* finsert(table *last, int ID, string name, int age)
    {
        if (last != nullptr)
            return last;
        table *temp = new table(ID, "", age, last);

        last = temp;
        last->next = last;
        return last;
    }
    table *insert(table *last, int ID, string name, int age)
    {
        if (last == NULL)
            return finsert(last, ID, name, age);
        table *temp = new table (ID, name, age, last->next);
        last -> next = temp;
        last = temp;
        return last;
    }
};

class waitList : public restaurant{
    public:
        table *list;
        waitList() : restaurant(){
            list = nullptr;
        }
        ~waitList(){
            delete list;
        }
        table* firstWait(table *last, int ID, string name, int age){
            if (last != nullptr)
                return last;
            table *temp = new table(ID, name, age, last);
            last = temp;
            last->next = last;
            return last;
        }
        table* deleteNode(table *last, string name){
            if(last == nullptr)
                return last;
            table *t = last; table *sub = last;
            while(t->name != name){
                sub = t;
                t = t->next;
            }
            sub->next = t->next;
            return last;
        }
};

class guessCome : public waitList{
    public:
        table *arrive;
        guessCome() : waitList(){
            arrive = nullptr;
        }
        ~guessCome(){
            delete arrive;
        }
};

table* sub;

void makeTable(restaurant *&r){
    for(int i = 1; i <= 15; i++){
        r->recentTable = r->insert(r->recentTable,i,"",0);
    }
}

waitList *w = new waitList();

void changeData(table *&a, table *&b){
    table *tmp = new table(a->ID, a->name, a->age, nullptr);
    a->ID = b->ID; a->name = b->name; a->age = b->age;
    b->ID = tmp->ID; b->name = tmp->name; b->age = tmp->age;
    delete tmp;
}
    
int findmaxID(restaurant *&r){
    int max = 0;
    table *t = r->recentTable;
    for(int i = 0; i < 15; i++){
        if(t->ID >= max) max = t->ID;
        t = t->next;
    }
    return max;
}

string findName(restaurant *r, int ID){
    table *t = r->recentTable;
    while(t->ID != ID){
        t = t->next;
    }
    return t->name;
}

string elementOfCommand(string &line){
    string code = line.substr(0,line.find(" "));
    line.erase(line.begin(), line.begin() + line.find(" ") + 1);
    return code;
}

int countQueue(){
    int cnt = 1;
    if(w->list == nullptr) cnt = 0;
    else{
        table* head = w->list;
        for(table* t = head->next; t != head; t = t->next){
            cnt++;
        }
    }
    return cnt;
}

int countGuest(guessCome *g){
    int guest = 1;
    if(g->arrive == nullptr) guest = 0;
    else{
        table* head = g->arrive;
        for(table* t = head->next; t != head; t = t->next){
            guest++;
        }
    }
    return guest;
}

void insertFromList(table *list, restaurant *&r){
    if (list != nullptr){
        table* recent =r->recentTable;
            if(recent->name == ""){
                recent->name = list->next->name; recent->age = list->next->age;
            }
        }
    table *t = list; table *h = list->next;
    t->next = h->next;
    
}   

bool ResIsFull(restaurant *r){
    int cnt = 0; bool full = 1;
    table *t = r->recentTable; 
    for(int i = 0; i < 15; i++){
        if(t->name == "") {
            full = 0; break;
        }
        else{
            t = t->next;
        }
    }
    return full;
}

void REG(restaurant *&r, int ID, string name, int age){
    bool check = 0;
    table* last = r->recentTable;
    table* t = r->recentTable->next;
    if(ResIsFull(r)){
        if(w->list != nullptr){
            w->list = w->insert(w->list, ID, name, age);
        }
        else{
            w->list = w->firstWait(w->list, ID, name, age);
        }
    }
    else{
        for(table* t = r->recentTable->next; t != last; t = t->next){
            if(ID == t->ID){
                if(t->name == ""){
                    t->name = name; t->age = age; check = 1;
                    r->recentTable = t;
                    break;
                }
                else{
                    if(ID < 15) ID++;
                    else ID = 1;
                }
            }
        }
        if(check == 0){
            while(t != last){
                if(t->name == ""){
                    t->name = name; t->age = age;
                    r->recentTable = t; break;
                }
                t = t->next;
            }
        }
    }
}

void merge(table *&sub, table* insert){
    table *tmp = new table(insert->ID, insert->name, insert->age, nullptr);
    if(sub == nullptr){
        sub = tmp;
        sub->next = sub;
    }
    else{
        table* head = sub;
        while(head->next != sub){
            head = head->next;
        }
        head->next = tmp;
        tmp->next = sub;
    }
}

int mergeTable;

void REGM(restaurant *&r, string name, int age, int num){
    int max = 15, cnt = 0;
    table *find = r->recentTable;
    table *head = nullptr;
    for(int i = 0; i < 15; i++){
        if(find->ID == max){
            for(int j = 1; j <= num; j++){
                if(j == 1) head = find; mergeTable = head->ID;

                if(find->name == ""){
                    cnt++; merge(sub, find);
                    if(cnt == num){
                        head->next = find->next;
                        find = head;
                    } 
                }
                else{
                    max--; cnt = 0; i = 0; sub = nullptr; break;
                }
                find = find->next;
            }
        }
        find = find->next; 
    }
    r->recentTable = head;
    head->name = name; head->age = age;
}

void REGMMM(restaurant *&r, string name, int age, int num){
    int cnt = 0;
    table *head = nullptr;
    table *find = r->recentTable;
    for(int i = 1; i <= 15; i++){
        if(find->name == ""){
            cnt++; merge(sub, find);
            if(cnt == num){
                head->next = find->next;
                find = head;
                break;
            } 
        }
        else{
            cnt = 0; sub = nullptr;
        }

        if(cnt == 1){
            head = find;
        }
        find = find->next;
    }
    head->name = name; head->age = age;
}

void CLE(restaurant *&r, int ID, bool &set){
    if(ID == mergeTable){
        table *subhead = sub->next;
        table *subtail = subhead;
        while(subtail->next->ID != sub->ID){
            subtail = subtail->next;
        }
        table *rtail = r->recentTable;
        while(rtail->ID != sub->ID){
            rtail = rtail->next;
        }
        table *rhead = rtail->next;
        rtail->next = subhead;
        subtail->next = rhead;
        set = 0; sub = nullptr;
    }
    
    table* t = r->recentTable;
    for(int i = 0; i < 15; i++){
        if(t->ID == ID){
            t->name = ""; t->age = 0; 
            r->recentTable = t; break;
        }
        t = t->next;
    }
    insertFromList(w->list, r);
}

void PS(guessCome *g, int num){
    cout<<"Guests who came into restaurant list (from the last)"<<endl;
    cout<<"---------------------------------------------------------------------------------"<<endl;
    for(int i = 0; i < num; i++){
        if(g == nullptr) cout<<"Empty\n";
        else{
           table* tail = g->arrive;
           while(tail->next != g->arrive){
                tail = tail->next;
           }
           cout<<g->arrive->name<<endl;
           g->arrive = tail;
        }
    }
    cout<<"---------------------------------------------------------------------------------"<<endl;
}

void PQ(guessCome *g, int num){
    cout<<"Guests who came into restaurant list (from the first)"<<endl;
    cout<<"---------------------------------------------------------------------------------"<<endl;
    table* t = g->arrive->next;
    for(int i = 0; i < num; i++){
        if(g == nullptr) cout<<"Empty\n";
        else{
            cout<<t->name<<endl;
            t = t->next;
        }
    }
    cout<<"---------------------------------------------------------------------------------"<<endl;
}

void PT(restaurant *r){
    cout<<"Guests who already have table in the restaurant"<<endl;
    cout<<"---------------------------------------------------------------------------------"<<endl;
    table *t = r->recentTable;
    for(int i = 0; i < 15; i++){
        if(t->name != "") cout<<t->name<<endl;
        t = t->next;
    }
    cout<<"---------------------------------------------------------------------------------"<<endl;
}

void SQ(int num){
    table *t = w->list->next;
    for(int i = 0; i < num; i++){
        int max = t->age; table *s = t->next;
        int cnt = countQueue();
        for(int j = i + 1; j < countQueue(); j++){
            if(max <= s->age){
                max = s->age;  
            }
            s = s->next;
        }
        table *news = t->next;
        for(int j = i + 1; j < countQueue(); j++){
            if(news->age == max){
                changeData(t, news); break;
            }
            news = news->next;
        }
        t = t->next;
    }
}

void readfile(string filename, restaurant *&r){
    ifstream file;
    int ID, age, num, guest = 1; string name; bool set = 0;
    makeTable(r);
    guessCome *g = new guessCome();
    file.open(filename, ios::in);
    if(file.is_open()){
        string line, test; 
        while(getline(file,line)){
            string code = elementOfCommand(line);
            if(code == "REG"){
                string test = elementOfCommand(line);
                if(test[0] >= 48 && test[0] <= 57){
                    ID = stoi(test); name = elementOfCommand(line);
                    age = stoi(elementOfCommand(line));
                }
                else {
                    ID = 0; name = test; age = stoi(elementOfCommand(line));
                }
                if(age >= 16) {
                    REG(r, ID, name, age); 
                    if(countGuest(g) < 30){
                        g->arrive = g->insert(g->arrive, 0, r->recentTable->name, r->recentTable->age);
                        if(countGuest(g) <= 15) g->arrive->name = r->recentTable->name;
                        else{g->arrive->name = w->list->name;}
                    }
                }
            }
            else if(code == "REGM"){
                name = elementOfCommand(line); age = stoi(elementOfCommand(line)); num = stoi(elementOfCommand(line));
                if(set == 0 && age >= 16){
                    REGM(r, name, age, num); 
                    if(countGuest(g) < 15 - num) g->arrive = g->insert(g->arrive, 0, name, age);
                }
                set = 1;
            }
            else if(code == "CLE"){
                ID = stoi(elementOfCommand(line));
                CLE(r, ID, set);
                string nameFound = findName(r, ID);
                g->arrive = g->deleteNode(g->arrive, nameFound);
            }
            else if(code == "PS"){
                if(line[0] >= 48 && line[0] <= 57){
                    num = stoi(elementOfCommand(line));
                }
                else num = countGuest(g);
                PS(g, num);
            }
            else if(code == "PQ"){
                if(line[0] >= 48 && line[0] <= 57){
                    num = stoi(elementOfCommand(line));
                }
                else num = countGuest(g);
                PQ(g, num);
            }
            else if(code == "PT"){
                PT(r);
            }
            else if(code == "SQ"){
                num = stoi(elementOfCommand(line));
                SQ(num);
            }
        }
    }    
}

int main(){
    string filename = "dm.txt";
    restaurant *r = new restaurant();
    readfile(filename,r);
    /*for(int i = 1; i <= 15; i++){
        cout<<info[i]->ID<<" "<<info[i]->name<<" "<<info[i]->age<<endl;
    }*/
    int max = findmaxID(r);
    table* last = r->recentTable;
    while(last->ID != max){
        last = last->next;
    }

    for(table *t = last->next; t != last; t = t->next){
        cout<<"Table Num: "<<t->ID<<"          "<<"Guest's Name: "<<t->name<<"          "<<"Age: "<<t->age<<endl;
    }
    cout<<"Table Num: "<<last->ID<<"          "<<"Guest's Name: "<<last->name<<"          "<<"Age: "<<last->age<<endl;
    table* lastList = w->list;
    cout<<"-------------------------------------------------------------------------------------------------"<<endl;
    cout<<"WAIT LIST: "<<endl;
    cout<<"-------------------------------------------------------------------------------------------------"<<endl;
    for(table *s = lastList->next; s != lastList; s = s->next){
        cout<<"Table Order: "<<s->ID<<"          "<<"Guest's Name: "<<s->name<<"          "<<"Age: "<<s->age<<endl;
    }
    cout<<"Table Order: "<<lastList->ID<<"          "<<"Guest's Name: "<<lastList->name<<"          "<<"Age: "<<lastList->age<<endl;
}