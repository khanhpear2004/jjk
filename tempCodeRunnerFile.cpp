#include <iostream>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

class Restaurant {

	public:
		Restaurant() {};
		~Restaurant() {};
		virtual void RED(string name, int energy) = 0;
		virtual void BLUE(int num) = 0;
		virtual void PURPLE() = 0;
		virtual void REVERSAL() = 0;
		virtual void UNLIMITED_VOID() = 0;
		virtual void DOMAIN_EXPANSION() = 0;	
		virtual void LIGHT(int num) = 0;
		public:
			class customer {
			public:	
				string name;
				int energy;
				customer* prev;
				customer* next;
			public:
				customer(){}
				customer(string na, int e, customer* p, customer *ne): name(na), energy(e), prev(p), next(ne){}
				~customer(){
					delete prev;
					delete next;
				}
				void print() {
					cout << name << "-" << energy << endl;
				}
			};
};

class tableAddress; //pre declaration

int MAXSIZE;

class imp_res : public Restaurant
{
	public:
		int guest , wait; customer *recent; customer *waited;
		tableAddress *first;
		imp_res() {
			 this->guest = 0;
			 this->wait = 0;
			 this->recent = nullptr;
			 this->waited = nullptr;
			 this->first = nullptr;
		};

		//In ra thứ tự khách trong nhà hàng bắt đầu từ bàn gần nhất
		void check(customer *recent){
			customer* tmp = recent;
			for(int i = 0; i < guest; i++){
				cout<<tmp->name<<" "<<tmp->energy<<endl;
				tmp = tmp->next;
			}
		}

		//In ra thứ tứ FIFO của hàng chờ khách đợi
		void waitList(customer *waited){
			customer* tmp = waited->next;
			for(int i = 0; i < wait; i++){
				cout<<tmp->name<<" "<<tmp->energy<<endl;
				tmp = tmp->next;
			}
		}

		//In ra thứ tứ khách đếm từ trước đến sau
		void arrive(customer *firstArrive){
			customer* tmp = firstArrive;
			for(int i = 0; i < guest; i++){
				cout<<tmp->name<<" "<<tmp->energy<<endl;
				tmp = tmp->next;
			}
		}

		//Kiểm tra xem trong nhà hàng đã có khách mang tên đó chưa
		bool onService(customer *c){
			customer* tmp = recent; customer* l = waited; bool q = 0;
			for(int i = 0; i < guest; i++){
				if(tmp->name == c->name) {return 1;}
				else tmp = tmp->next;
			}
			q = 1;
			if(q){
				for(int i = 0; i < wait; i++){
					if(l->name == c->name) {return 1;}
					else l = l->next;
				}
			}
			
			return 0; 
		}

	
		//Để khách ngồi về phía bên phải (next) ở vị trí recent
		void insertNext(customer *&r, customer *c){
			r->next->prev = c; c->next = r->next;
			r->next = c; c->prev = r;
			r = c;
		}

		//Để khách ngồi về phía bên trái (prev) ở vị trí recent
		void insertPrev(customer *&r, customer *c){
			r->prev->next = c; c->prev = r->prev;
			c->next = r; r->prev = c;
			r = c;
		}

		//Đá một khách ngồi lâu ra ngoài
		void remove(customer *&r){
			if(guest == 1) r = nullptr;
			else{
				customer *tmp = r;
				r->prev->next = r->next;
				r->next->prev = r->prev;
				r = r->prev;
				tmp->prev = nullptr; tmp->next = nullptr;
				delete tmp;
			}
		}

		//cho một khách đang chờ ra khỏi hàng chờ để đi vào hàm
		void removeWait(customer *&w){
			if(wait == 1) w = nullptr;
			else{
				customer *tmp = w;
				w->prev->next = w->next;
				w->next->prev = w->prev;
				w = w->prev;
				tmp->prev = nullptr; tmp->next = nullptr;
				delete tmp;
			}
		}

		//Lấy tứ tự của người đang ở hàng chờ
		customer *takeIndex(customer *w, int n){
			for(int i = 0; i < n; i++){
				w = w->next;
			}
			return w;
		}

		//Kiểm tra vị trí của bàn ăn có năng lượng lớn nhất
		int biggestEnegry(customer *w){
			int index = 0; int temp = 0, max = 0;
			for(int i = 0; i < wait; i++){
				if(abs(w->energy) >= max){
					index = temp; max = abs(w->energy);
				}
				w = w->next;
				temp++;
			}
			return index;
		}

		void swap(customer *&a, customer *&b){
			if(a->next == b){
				a->next = b->next; b->next->prev = a;
				b->prev = a->prev; a->prev->next = b;
				b->next = a; a->prev = b;
			}
			else if(b->next == a){
				b->next = a->next; a->next->prev = b;
				a->prev = b->prev; b->prev->next = a;
				a->next = b; b->prev = a;
			}
			else{
				customer *aNext = a->next; customer *aPrev = a->prev;
				customer *bNext = b->next; customer *bPrev = b->prev;
				a->next = bNext; a->prev = bPrev;
				bPrev->next = a; bNext->prev = a;
				b->next = aNext; b->prev = aPrev;
				aPrev->next = b; aNext->prev = b;
			}
		}

		int calculateSum(customer *r, int n){
			int sum = 0;
			for(int i = 0; i < n; i++){
				sum += r->energy;
				r = r->next;
			}
			return sum;
		}
		
		//Tính tổng enegry của các chú thuật sư
		int SumOfSorcerer(customer *r, customer *w){
			int s = 0;
			for(int i = 0; i < guest; i++){
				if(r->energy > 0) s += r->energy;
				r = r->next;
			}
			if(guest == 10 && wait > 0){
				for(int i = 0; i < wait; i++){
					if(w->energy > 0) s += w->energy;
					w = w->next;
				}
			}
			return s;
		}

		//Tính tổng enegry của lời nguyền
		int SumOfCurse(customer *r, customer *w){
			int c = 0;
			for(int i = 0; i < guest; i++){
				if(r->energy < 0) c += r->energy;
				r = r->next;
			}
			if(guest == 10 && wait > 0){
				for(int i = 0; i < wait; i++){
					if(w->energy < 0) c += w->energy;
					w = w->next;
				}
			}
			return c;
		}

		void domain(customer *&r);

		void printSubSmallest(customer *r);

		void shellsort(customer *&r);

		void goInside(customer *&r, customer *c);

		void goHome(customer *&r, int n);

		void reverse(customer *&r);

		void printLight(customer *r, int n);

		void RED(string name, int energy)
		{
			//cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
			goInside(recent, cus);
		}
		void BLUE(int num)
		{
			goHome(recent, num);
		}
		void PURPLE()
		{
			shellsort(waited);
		}
		void REVERSAL()
		{
			reverse(recent);
		}
		void UNLIMITED_VOID()
		{
			printSubSmallest(recent);
		}
		void DOMAIN_EXPANSION()
		{
			domain(recent);
		}
		void LIGHT(int num)
		{
			printLight(recent, num);
		}
};

class tableAddress : public imp_res{
	public:
		customer *data;
		tableAddress *tail;
		tableAddress *next;
		tableAddress *prev;
		tableAddress(customer *data, tableAddress *next, tableAddress *prev){
			this->data = data; this->next = next; this->prev = prev;
		}

		void addAddress(tableAddress *&t, customer *x){
			tableAddress *tmp = new tableAddress(x, nullptr, nullptr);
			if(t == nullptr){
				t = tmp; t->tail = tmp;
			}
			else{
				/*tableAddress *p = t;
				while(p->next != nullptr){
					p = p->next;
				}
				p->next = tmp;
				tmp->prev = p;*/
				 t->tail->next = tmp;
				 t->tail = tmp;
			}
		}

		void addAddressForList(tableAddress *&t, customer *x){
			tableAddress *tmp = new tableAddress(x, nullptr, nullptr);
			if(t == nullptr){
				t = tmp;
			}
			else{
				tmp->next = t;
				t->prev = tmp;
				t = tmp;
			}
		}

		tableAddress *tailing(tableAddress *t){
			while(t->next != nullptr){
				t = t->next;
			}
			return t;
		}

		void deleteFirst(tableAddress *&t){
			if(t->next == nullptr) {t = nullptr;}
			else{
				tableAddress *p = t;
				t = t->next;
				t->prev = nullptr;
				delete p;
			}
		}

		void deleteLast(tableAddress *&t){
			tableAddress *p = t;
			while(p->next != nullptr){p = p->next;}
			p->prev->next = nullptr;
			p->prev = nullptr;
			delete p;
		}

		void deleted(tableAddress *&t){
			if(t == nullptr) return;
			else if(t->next != nullptr && t->prev == nullptr) deleteFirst(t);
			else if(t->next == nullptr && t->prev != nullptr) deleteLast(t);
			else{
				tableAddress *p = t;
				p->prev->next = p->next;
				p->next->prev = p->prev;
				t = t->prev;
				delete p;
			}
		}

		void swapCustomer(tableAddress *&a, tableAddress *&b){
			tableAddress *tmp = new tableAddress(a->data, nullptr, nullptr);
			a->data = b->data; b->data = tmp->data;
			delete tmp;
		}
};

//RED
void imp_res :: goInside(customer *&recent, customer* c)
{
	if(c->energy != 0 && !onService(c)){
		if(guest < MAXSIZE / 2.0){
			customer *t = new customer(c->name, c->energy, nullptr, nullptr);
			if(recent == nullptr){
				recent = c; recent->prev = c; recent->next = c;
				first->addAddress(first, recent);
			}
			else{
				if(c->energy >= recent->energy){
					insertNext(recent, c);
				}
				else {insertPrev(recent, c);}
				first->addAddress(first, recent);
			}
		}
		else{
			customer *tmp = recent; int amax = 0, max = 0;
			if(guest >= MAXSIZE && wait != MAXSIZE){
				if(waited == nullptr){
					waited = c; waited->prev = waited->next = c;
				}
				else{
					insertNext(waited, c);
				}
				wait++; guest--;
			}
			else if(guest >= MAXSIZE && wait == MAXSIZE) return;
			else{
				customer *t = new customer(c->name, c->energy, nullptr, nullptr);
				for(int i = 0; i < guest; i++){
					if(abs(c->energy - tmp->energy) > amax){
						amax = abs(c->energy - tmp->energy); max = c->energy - tmp->energy;
						recent = tmp;
					}
					tmp = tmp->next;
				}
				if(max > 0) insertNext(recent, c);
				else insertPrev(recent, c);
				first->addAddress(first, recent);
			}
		}
		guest++;
	}
}

//BLUE
void imp_res :: goHome(customer *&recent, int n){
	customer *tmp = recent;
	if(n >= guest){
		recent = nullptr;
		if(tmp != nullptr){tmp->next = nullptr; tmp->prev = nullptr;}
		for(int i = 0; i < guest; i++) {first->deleteFirst(first);}
		guest = 0;
		delete tmp;
	}
	else{
		for(int i = 0; i < n; i++){
			if(first->data->energy > 0){recent = first->data->next;}
			else{recent = first->data->prev;}
			remove(first->data);
			first->deleteFirst(first); 
			guest--;
		}
	}

	while(waited != nullptr && guest != MAXSIZE){
		customer *w = waited->next;
		customer *n = new customer(w->name, w->energy, nullptr, nullptr);
		removeWait(w); wait--;
		goInside(recent, n);
	}
}


//PURPLE
void imp_res :: shellsort(customer *&w){
	int divided, i, j, num = biggestEnegry(waited->next); 
	customer *tmp = nullptr; customer* itable = nullptr; customer *jtable = nullptr;
	for(divided = wait/2; divided > 0; divided /= 2){
		for(i = divided; i <= num; i++){
			itable = takeIndex(w->next, i);
			tmp = new customer(itable->name, itable->energy, nullptr, nullptr);
			for(j = i; j >= divided && abs(takeIndex(w->next, j - divided)->energy) < abs(tmp->energy) ; j -= divided){
				jtable = takeIndex(w->next, j); customer *change = takeIndex(w->next, j - divided);
				swap(jtable, change);
				if(jtable == waited){waited = change;}
			}
			delete tmp;
		}
	}
}


//REVERSAL
void imp_res :: reverse(customer *&r){
	int plus = 0, minus = 0; customer *tmp = r;
	for(int i = 0; i < guest; i++){
		tmp->energy > 0 ? plus++ : minus++;
		tmp = tmp->next;
	}
	
	tableAddress *sorcerer = nullptr; tableAddress *curse = nullptr;
	customer *x = r; customer *y = x;
	if(x->energy > 0){
		while(y->energy > 0){y = y->prev;}
		for(int i = 0; i < guest; i++){
			if(x->energy > 0){sorcerer->addAddress(sorcerer, x);}
			x = x->prev;
			if(y->energy < 0){curse->addAddress(curse, y);}
			y = y->prev;
		}
	}
	else{
		while(y->energy < 0){y = y->prev;}
		for(int i = 0; i < guest; i++){
			if(y->energy > 0){sorcerer->addAddress(sorcerer, y);}
			y = y->prev;
			if(x->energy < 0){curse->addAddress(curse, x);}
			x = x->prev;
		}
	}

	tableAddress *plast = sorcerer->tailing(sorcerer); tableAddress *mlast = curse->tailing(curse);
	while(plus > 0){
		swap(sorcerer->data, plast->data); sorcerer = sorcerer->next; plast = plast->prev; plus-=2;
	}
	while(minus > 0){
		swap(curse->data, mlast->data); curse = curse->next; mlast = mlast->prev; minus-=2;
	}
	delete sorcerer; delete curse;
}

//UNLIMITED_VOID
void imp_res :: printSubSmallest(customer *r){
	customer *tmp = r; customer *smallest = r; int length = 0;
	int max = calculateSum(tmp, 4);
	for(int i = 4; i < guest; i++){
		if(max <= calculateSum(tmp, i)){
			max = calculateSum(tmp, i); smallest = tmp; length = i; 
		}
		customer *check = tmp->next;
		while(check != tmp){
			int s = calculateSum(check, i);
			if(s <= max){
				max = s; length = i;
				smallest = check;
			}
			check = check->next;
		}
	}

	for(int i = 0; i < length; i++){
		cout<<smallest->name<<"-"<<smallest->energy<<endl;
		smallest = smallest->next;
	}
}

//DOMAIN_EXPANSION
void imp_res :: domain(customer *&r){
	tableAddress *list = nullptr;
	tableAddress *del = first;
	int s = SumOfSorcerer(r, waited);
	int c = SumOfCurse(r, waited);
	if(s > abs(c)){
		for(int i = 0; i < guest; i++){
			if(del->data->energy < 0){
				customer *tmp = new customer(del->data->name, del->data->energy, nullptr, nullptr);
				list->addAddressForList(list, tmp);
				remove(del->data); guest--;
				del->deleted(del);
				del = del->next;
			}
			else{del = del->next;}
		}
	}
	else{
		for(int i = 0; i < guest; i++){
			if(del->data->energy > 0){
				customer *tmp = new customer(del->data->name, del->data->energy, nullptr, nullptr);
				list->addAddressForList(list, tmp);
				remove(del->data); guest--;
				del->deleted(del);
				del = del->next;
			}
			else{del = del->next;}
		}
	}

	while(waited != nullptr && guest != MAXSIZE){
		customer *w = waited->next;
		customer *n = new customer(w->name, w->energy, nullptr, nullptr);
		remove(w); wait--;
		goInside(recent, n);
	}

	cout<<"List of guests who just have gotten kicked out"<<endl;
	for(list; list != nullptr; list){
		cout<<list->data->name<<" - "<<list->data->energy<<endl;
		list->deleteFirst(list);
	}
	delete list;
}

//LIGHT
void imp_res :: printLight(customer *r, int n){
	if(n == 0){
		if(waited != nullptr){
			customer* tmp = waited->next;
			for(int i = 0; i < wait; i++){
				cout<<tmp->name<<" - "<<tmp->energy<<endl;
				tmp = tmp->next; 
			}
		}
	}
	else if(n > 0){
		if(r != nullptr){
			customer* tmp = r;
			for(int i = 0; i < guest; i++){
				cout<<tmp->name<<" - "<<tmp->energy<<endl;
				tmp = tmp->next;
			}
		}
	}
	else{
		if(r != nullptr){
			customer* tmp = r;
			for(int i = 0; i < guest; i++){
				cout<<tmp->name<<"-"<<tmp->energy<<endl;
				tmp = tmp->prev;
			}
		}
	}
}


void simulate(string filename, imp_res* r)
{
	ifstream ss(filename);
	string str, maxsize, name, energy, num;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
    	}
        else if(str == "RED") // RED <NAME> <ENERGY>
        {
            ss >> name;
            ss >> energy;
            r->RED(name, stoi(energy));
    	}
    	else if(str == "BLUE") // BLUE <NUM>
    	{
                ss >> num;
    			r->BLUE(stoi(num));
		}
    	else if(str == "PURPLE") // PURPLE
    	{
    			r->PURPLE();
		}
		else if(str == "REVERSAL") // REVERSAL
		{
    			r->REVERSAL();	
		}
    	else if(str == "UNLIMITED_VOID") // UNLIMITED_VOID
     	{   	
    			r->UNLIMITED_VOID();
    	}
    	else if(str == "DOMAIN_EXPANSION") // DOMAIN_EXPANSION
    	{
    			r->DOMAIN_EXPANSION();
    	}
    	else // LIGHT <NUM>
    	{
                ss >> num;
    			r->LIGHT(stoi(num));
    	}
    }
}

int main(int argc, char* argv[]){
	//if (argc < 2)
    //	return 1;
	//  string fileName = argv[1];
	imp_res* r = new imp_res();
	string fileName = "jjk.txt";
    simulate(fileName, r);
	//cout<<"IN RESTAURANT WE HAVE: "<<endl;
	//r->check(r->recent);
	//cout<<"THE WAITLIST CONTAINS: "<<endl;
	//r->waitList(r->waited);
	//r->arrive(r->firstArrive);
  	delete r;
	return 0;
}