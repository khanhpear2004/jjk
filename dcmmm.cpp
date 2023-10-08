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

int MAXSIZE;


class Red:public Restaurant::customer
{
public:
    Red(){};

    static void addtoWait(customer* cus, customer*& head_waiting, int GuestWaiting_size)
    {
        if (GuestWaiting_size == MAXSIZE)
        {
            return;
        }
        else if (head_waiting == nullptr)
        {
            head_waiting = cus;
            head_waiting->next = head_waiting->prev = cus;
        }
        else
        {
            head_waiting->prev->next = cus;
            cus->prev = head_waiting->prev;
            cus->next = head_waiting;
            head_waiting->prev = cus;
        }
    }


    static void addLeft(customer* cus, customer *cusX, customer* tail_order)
    {
        customer* preX = cusX->prev;
        cus->next=cusX;
        cusX->prev=cus;
        preX->next=cus;
        cus->prev=preX;
        tail_order->next= new Restaurant::customer(cus->name,cus->energy, nullptr, nullptr);
        tail_order=tail_order->next;
    }

    static void addRight(customer* cus,customer* cusX, customer* tail_order)
    {
        customer* nextX = cusX->next;
        cus->next=nextX;
        nextX->prev=cus;
        cusX->next=cus;
        cus->prev=cusX;
        tail_order->next= new Restaurant::customer(cus->name,cus->energy, nullptr, nullptr);
        tail_order=tail_order->next;
    }

    static bool findName(customer* cus, customer* head_table, customer* head_waiting, int GuestTable_size, int GuestWaiting_size)
    {
        if (head_table == nullptr||head_waiting==nullptr)
        {
            return false;
        }
        customer* curr_table = head_table;
        customer* curr_wating = head_waiting;
        int i = 0;
        while (i<GuestTable_size)
        {
            if (curr_table->name==cus->name)
            {
                return true;
                break;
            }
            curr_table=curr_table->next;
            i++;
        }
        i=0;
        while (i<GuestWaiting_size)
        {
            if (curr_wating->name==cus->name)
            {
                return true;
                break;
            }
            curr_wating=curr_wating->next;
            i++;
        }
        return false;
    }

    static void findHighRes(customer* cus, customer* head_table, int GuestTable_size, customer* tail_order)
    {
        int max_res=-1;
        customer* best_pos = nullptr;
        int subs = 0;
        int max_subs = 0;
        customer* current = head_table;
        for (int i = 0; i<GuestTable_size; i++)
        {
            subs = cus->energy-current->energy;
            int res = abs(subs);
            if (res>max_res)
            {
                max_subs = subs;
                max_res=res;
                best_pos=current;
            }
            current = current->next;
        }
        if(best_pos!= nullptr)
        {
            if(max_subs<0)
            {
                Red::addLeft(cus,best_pos,tail_order);
            }
            else
            {
                Red::addRight(cus,best_pos,tail_order);
            }
        }
    }
};

class Blue : public Restaurant::customer
{
public:
    static customer* SearchInfo(customer* head_table, customer* head_order)
    {
        if (head_table == nullptr || head_order == nullptr)
        {
            return nullptr;
        }

        customer* temp_order = head_order;
        customer* temp_table = head_table;

        while (temp_order != nullptr)
        {
            if (temp_table->name == temp_order->name && temp_table->energy == temp_order->energy)
            {
                return temp_table;
            }
            else
            {
                temp_order = temp_order->next;
                temp_table = temp_table->next;
            }
        }
        return nullptr;
    }

    static void KickGuest(customer*& head_table, customer*& head_order, customer*& tail_order, int GuestTable_size)
    {
        int i = 0;
        while (i<GuestTable_size)
        {
            customer* delete_guest = SearchInfo(head_table,head_order);
            customer* pre_temp = delete_guest -> prev;
            customer* next_temp = delete_guest -> next;
            pre_temp->next=next_temp;
            next_temp->prev=pre_temp;
            if (head_table == delete_guest) head_table = head_table -> next;
            delete delete_guest;
            customer* temp_order = head_order;
            head_order = head_order->next;
            delete temp_order;
            i += 1;
        }
    }

    static void AddtoTablefromWait(customer*& head_table, customer*& head_order, customer*& tail_order, customer*& head_waiting, customer* cusX, int GuestTable_size)
    {
        customer* temp = head_waiting;
        head_waiting = head_waiting -> next;
        head_waiting -> prev = temp -> prev;
        temp -> prev -> next = head_waiting;
        temp -> next = temp -> prev = nullptr;
        if(head_table==nullptr)
        {
            head_table=temp;
            head_table->next=head_table->prev=temp;
            head_order = tail_order = new Restaurant::customer(temp -> name, temp -> energy, nullptr, nullptr);
        }
        else if (GuestTable_size>=MAXSIZE/2)
        {
            Red::findHighRes(temp,head_table,GuestTable_size, tail_order);
            tail_order -> next = new Restaurant::customer(temp -> name, temp -> energy, nullptr, nullptr);
            tail_order = tail_order -> next;
        }
        else
        {
            if(temp->energy>=cusX->energy)
            {
                Red::addRight(temp,cusX,tail_order);
                tail_order -> next = new Restaurant::customer(temp -> name, temp -> energy, nullptr, nullptr);
                tail_order = tail_order -> next;
            }
            else
            {
                Red::addLeft(temp,cusX,tail_order);
                tail_order -> next = new Restaurant::customer(temp -> name, temp -> energy, nullptr, nullptr);
                tail_order = tail_order -> next;
            }
        }
    }
};

class imp_res : public Restaurant
{
public:
    customer* head_table;
    customer* cusX;
    customer* head_waiting;
    customer* head_order;
    customer* tail_order;
    int GuestTable_size;
    int GuestWaiting_size;
    imp_res() {
        head_table = nullptr;
        head_waiting = nullptr;
        head_order = nullptr;
        tail_order = nullptr;
        cusX = nullptr;
        GuestTable_size = 0;
        GuestWaiting_size = 0;
    };

    void RED(string name, int energy)
    {
        cout << name << " " << energy << endl;
        customer *cus = new customer (name, energy, nullptr, nullptr);
        if(Red::findName(cus,head_table,head_waiting,GuestTable_size,GuestWaiting_size))
        {
            return;
        }
        if (energy != 0)
        {
            if (GuestTable_size == 0)
            {
                head_table=cus;
                head_table->prev=head_table->next=cus;
                head_order = tail_order = new customer(cus->name,cus->energy, nullptr, nullptr);
                cusX=cus;
                GuestTable_size++;
            }
            else if(GuestTable_size==MAXSIZE)
            {
                Red::addtoWait(cus,head_waiting,GuestWaiting_size);
                GuestWaiting_size++;
            }
            else if(GuestTable_size>=MAXSIZE/2)
            {
                Red::findHighRes(cus,head_table,GuestTable_size,tail_order);
                cusX=cus;
                GuestTable_size++;
                tail_order -> next = new customer(cus -> name, cus -> energy, nullptr, nullptr);
                tail_order -> next -> prev = tail_order;
                tail_order = tail_order -> next;
            }
            else
            {
                if(cus->energy<cusX->energy)
                {
                    Red::addLeft(cus,cusX,tail_order);
                    cusX=cus;
                    GuestTable_size++;
                }
                else
                {
                    Red::addRight(cus,cusX,tail_order);
                    cusX=cus;
                    GuestTable_size++;
                }
                tail_order -> next = new customer(cus -> name, cus -> energy, nullptr, nullptr);
                tail_order -> next -> prev = tail_order;
                tail_order = tail_order -> next;
            }
        }
    }
    void BLUE(int num)
    {
        cout << "blue "<< num << endl;
        if(GuestTable_size==0)
        {
            return;
        }
        else if (num>=GuestTable_size||num>=MAXSIZE)
        {
            customer* curr_table = head_table;
            while(GuestTable_size>0)
            {
                customer* temp = curr_table;
                curr_table = curr_table->next;
                delete temp;
                GuestTable_size--;
            }

            customer* curr_order = head_order;
            while(GuestTable_size>0)
            {
                customer* temp = curr_order;
                curr_order = curr_order->next;
                delete temp;
                GuestTable_size--;
            }

            head_table = head_order = nullptr;
            GuestTable_size=0;
        }
        else
        {
            Blue::KickGuest(head_table,head_order,tail_order,num);
            GuestTable_size-=num;
        }
        while(GuestWaiting_size>0)
        {
            Blue::AddtoTablefromWait(head_table,head_order, tail_order,head_waiting,cusX,GuestTable_size);
            GuestWaiting_size--;
            GuestTable_size++;
            if(GuestTable_size==MAXSIZE) break;
        }
    }
    void PURPLE()
    {
        cout << "purple"<< endl;
    }
    void REVERSAL()
    {
        cout << "reversal" << endl;
    }
    void UNLIMITED_VOID()
    {
        cout << "unlimited_void" << endl;
    }
    void DOMAIN_EXPANSION()
    {
        cout << "domain_expansion" << endl;
    }
    void LIGHT(int num)
    {
        cout << "light " << num << endl;
        if(num==0)
        {
            customer* temp = head_waiting;
            for (int i = 0; i<GuestWaiting_size; i++)
            {
                temp->print();
                temp=temp->next;
            }
        }
        else if(num>0)
        {
            customer *temp = cusX;
            for (int i = 0; i < GuestTable_size; i++)
            {
                temp->print();
                temp=temp->next;
            }
        }
        else if (num<0)
        {
            customer *temp = cusX;
            for (int i = 0; i < GuestTable_size; i++)
            {
                temp->print();
                temp=temp->prev;
            }
        }
    }
};

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
	// cout<<"IN RESTAURANT WE HAVE: "<<endl;
	// r->check(r->recent);
	// cout<<"THE WAITLIST CONTAINS: "<<endl;
	// r->waitList(r->waited);
	//r->arrive(r->firstArrive);
  	delete r;
	return 0;
}