#include<iostream>
#include<fstream>
using namespace std;


class Login
{
    string username;
    string password;
public:
   void userLogin();
};

//LOGIN PAGE
void Login::userLogin()
{
    int flag=0,counts=0,opt;
    string uname,pwd,Name,password;

    while (flag!=1)
    {
        cout<<"\nEnter the desired choice:\n";
        cout<<"[1] Login \n";
        cout<<"[2] Register(available only once per user)\n";
        cin>>opt;

        if (opt==2)
        {

            if(counts!=0)
            {
                cout<<"\nRegistered once.login to continue\n";
            }
            else
            {
                counts++;
                ofstream fp("loginPage.txt");
                if (!fp.is_open())
                {
                    cout<<"Error opening file\n";
                    exit(1);

                }
                cout<<"New Username: ";
                fflush(stdin);
                getline(cin, uname);
                cout<<"New Password: ";
                getline(cin, pwd);
                fp<<uname;
                fp<<'\n';
                fp<<pwd;
                fp.close();
            }
        }
        if (opt==1)
        {
            ifstream fp1("loginPage.txt");
            if (!fp1.is_open())
            {
                cout<<"Error opening file\n";
                exit(1);

            }
            getline(fp1, Name, '\n');
            getline(fp1, password, '\n');
            fp1.close();

            while (1)
            {

                cout<<"\n\n"<<"Enter Username: ";
                fflush(stdin);
                getline(cin, uname);
                cout<<"Enter Password: ";
                getline(cin, pwd);
                if (Name==uname && password==pwd)
                {
                    cout<<"\nLogin Successful\n";
                    cout<<"Welcome, ";
                    cout<<uname<<endl;
                    flag=1;
                    break;
                }
                else
                {
                    cout<<"\nIncorrect name or password\n";
                }
            }

        }
    }
}





class Flavor
{
    string taste;
    string toppings;
public:
    Flavor();
    void setFlavor(string,string);
    string getTaste(){return taste;}
    string getToppings(){return toppings;}
};

void Flavor::setFlavor(string taste,string toppings)
{
    this->taste=taste;
    this->toppings=toppings;
}

Flavor::Flavor()
{
    taste="";
    toppings="";
}






class Cake
{
    string type;
    float price;
    
public:
    Flavor *flavor;
    Cake();
    void setCake(string,float,Flavor*);
    string getType(){return type;}
    float getPrice(){return price;}
};

void Cake::setCake(string t,float p,Flavor *f)
{
    type=t;
    price=p;
    flavor=f;
}

Cake::Cake()
{
    type="";
    price=0;
}






class Order
{
    int orderNo;
public:
    Cake cake;
    Order();
    int getOrderNo(){return orderNo;};
    void setOrder(int,Cake);
};

Order::Order()
{
    orderNo=0;
}
void Order::setOrder(int no,Cake c)
{
    cake=c;
    orderNo=no;
}






class Person
{
    string name;
    long long int phone;
public:
    Person();
    string getName(){return name;}
    int getPhone(){return phone;}
    void setPerson(string,long long int);
};

void Person::setPerson(string name,long long int phone)
{
    this->name=name;
    this->phone=phone;
}

Person::Person()
{
    name="xx";
    phone=0;
}






class Customer:public Person
{
    Order order;
public:
    void setCustomer(Order);
    void deliver();
};

void Customer::deliver()
{
    system("clear");
    cout<<"+-------------------------------------------------------+"<<endl;
    cout<<"|                Order no:"<<this->order.getOrderNo()<<"                             |"<<endl;
    cout<<"|    Customer name:"<<this->getName()<<"                                  |"<<endl;
    cout<<"|    Cake description:"<<this->order.cake.getType()<<" "<<this->order.cake.flavor->getTaste()<<" "<<this->order.cake.flavor->getToppings()<<"                     |"<<endl;
    cout<<"|    Total cost: Rs."<<this->order.cake.getPrice()<<"                                 |"<<endl;
    cout<<"|                Thank you                              |"<<endl;
    cout<<"+-------------------------------------------------------+"<<endl;

    cout<<"Press any key to continue"<<endl;
    cin.get();
}

void Customer::setCustomer(Order O)
{
    order=O;
}





int getCakePrice(string type)
{
    if(type=="One-tier")
        return 200;
    else if (type=="Two-tier")
        return 350;
    else if(type=="Cupcake")
        return 50;
    else
        return 50;
}

int getFlavorPrice(string flavr)
{
    if(flavr=="Vanilla")
        return 150;
    else if (flavr=="Chocolate")
        return 150;
    else if(flavr=="Blueberry")
        return 190;
    else
        return 190;
}

int getToppingsPrice(string top)
{
    if(top=="Frosting")
        return 70;
    else if (top=="Nuts")
        return 60;
    else if(top=="Chocochips")
        return 40;
    else
        return 30;
}





int main()
{
    Login login;
    int opt,orderNo=0;;
    string type,flavr,toppings,name;
    long long int phone; 
    login.userLogin();
    Flavor flavor;
    Cake cake;
    Order order;
    Customer c;

    while(1)
    {
        cout<<"\nTAKE ORDER"<<endl;
        float total=0;
        cout<<"Customer name: ";
        cin>>name;
        cout<<"Contact number: ";
        cin>>phone;
        cout<<"\n   Cake type ";
        cout<<"\nOne-tier\nTwo-tier\nCupcake\nBrownie\n";
        cin>>type;
        total+=getCakePrice(type);
        cout<<"\n   Flavor ";
        cout<<"\nVanilla\nChocolate\nBlueberry\nStrawberry\n";
        cin>>flavr;
        total+=getFlavorPrice(flavr);
        cout<<"\n   Toppings ";
        cout<<"\nFrosting\nNuts\nLettering\nChocochips\n";
        cin>>flavr;
        total+=getToppingsPrice(flavr);
        flavor.setFlavor(flavr,toppings);
        cake.setCake(type,total,&flavor);
        order.setOrder(++orderNo,cake);
        c.setCustomer(order);
        c.setPerson(name,phone);
        system("clear");
        cout<<"\nOrder is being processed\n";
        cin.get();
        c.deliver();
        system("clear");
        cout<<"\n[1] Take next order\n[2] Exit\n";
        cin>>opt;
        if(opt==1)
            continue;
        else
            break;
    }
    return 0;
}