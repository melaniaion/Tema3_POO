#include <iostream>
#include<string>
#include<vector>
using namespace std;

class Proprietar{
    const string numep = "X";
    int age;                                    //variabile statice si constante;
    const static int id_prop = 5231;
    static int salariu;

public:
    Proprietar(){age = 0;}
    Proprietar(string numep, int age): numep(numep),age(age){}              //constructori
    Proprietar(const Proprietar &ob)
    {
        this->age = ob.age;
    }

    virtual ~Proprietar(){};                //constructor virtual pentru a evita memory leak in cazul unui upcasting

    Proprietar& operator= (const Proprietar &obj)
    {
        this->age = obj.age;                                    //supraincarcare operator =
        return *this;
    }

    friend istream& operator>> (istream& is, Proprietar& p);          //supraincarcare << si >> ca functii prieten
    friend ostream& operator<< (ostream& os, const Proprietar& p);

    virtual void citire(){Proprietar p; cin>>p;}            //functii virtuale pentru citire si afisare rescrise in derivate
    virtual void afisare(){Proprietar p; cout<<p;}

    void modificare_salariu(int valoare)const           //metoda constanta pentru modificare salariu
    {
        salariu = valoare;
    }

    static int getSalariu()
    {
        return salariu;
    }
    static int getId()
    {
        return id_prop;
    }

};

int Proprietar :: salariu = 4000;               //variabila statica initializata in afara clasei

istream& operator>> (istream& is, Proprietar& p)
{
    cout<<"Dati varsta:"<<endl;
    is>>p.age;
    cout<<endl;
    return is;
}
ostream& operator<< (ostream& os, const Proprietar& p)
{
    os<<"Proprietarul este: ";
    os<<p.numep<<" are varsta de "<<p.age<<" ani"<<" cu id-ul: "<<p.id_prop<<" si salariul "<<p.salariu<<endl;
    return os;
}

class Farmacie : public Proprietar{                 //clasa Farmacie, mosteneste Proprietar
    string denumire;
    int angajati;
    int profit;

public:
    Farmacie(){denumire = "necunoscuta"; angajati = 1; profit = 0;}
    Farmacie(string denumire, int angajati, int profit)
    {
        this->denumire = denumire;
        this->angajati = angajati;
        this->profit = profit;
    }
    Farmacie(const Farmacie &ob)                                //constructorii si destructorul
    {
        this->denumire = ob.denumire;
        this->angajati = ob.angajati;
        this->profit = ob.profit;
    }
    ~Farmacie(){}

    Farmacie& operator= (const Farmacie &obj)
    {
        this->denumire = obj.denumire;
        this->angajati = obj.angajati;
        this->profit = obj.profit;
        return *this;
    }

    void citire()                           //functiile de citire si afisare rescrise in derivata
    {
        string d;
        int a;
        int p;
        cout<<"Dati denumirea, angajatii si profitul"<<endl;
        cin>>d>>a>>p;
        denumire = d;
        angajati = a;
        profit = p;
        cout<<endl;
    }

    void afisare()
    {
        cout<<"Farmacia se numeste: "<<denumire<<" cu "<<angajati<<" angajati si "<<profit<<" profit"<<endl;
    }
    void afisare_prop(Proprietar &p)                //operatorului << implementat in clasa de baza, referire in derivata
    {
        cout<<p;
    }


    void setFarmacieNume(string d)
    {
        denumire = d;
    }
    void setFarmacieAngajati(int a)
    {
        angajati = a;
    }
    void setFarmacieProfit(int p)
    {
        profit = p;
    }

    string getFarmacieNume() const
    {
        return denumire;
    }
    int getFarmacieAngajati() const
    {
        return angajati;
    }
    int getFarmacieProfit() const
    {
        return profit;
    }
};

class Farmacie_Online : public Proprietar{              //clasa pentru farmaciile online, mosteneste Proprietar
    string adresa_web;
    int nr_vizitatori;
    int discount;

public:
    Farmacie_Online(){adresa_web = "www.farmacii.ro"; nr_vizitatori = 0; discount = 0;}
    Farmacie_Online(string adresa_web, int nr_vizitatori, int discount)
    {
        this->adresa_web = adresa_web;
        this->nr_vizitatori = nr_vizitatori;
        this->discount = discount;
    }
    Farmacie_Online(const Farmacie_Online &ob)
    {
        this->adresa_web = ob.adresa_web;
        this->nr_vizitatori = ob.nr_vizitatori;
        this->discount = ob.discount;
    }
    ~Farmacie_Online(){}

    Farmacie_Online& operator= (const Farmacie_Online &obj)
    {
        this->adresa_web = obj.adresa_web;
        this->nr_vizitatori = obj.nr_vizitatori;
        this->discount = obj.discount;
        return *this;
    }

     void citire()
    {
        string a;
        int v;
        int dis;
        cout<<"Dati adresa web, vizitatorii si discount"<<endl;
        cin>>a>>v>>dis;
        adresa_web = a;
        nr_vizitatori = v;
        discount = dis;
        cout<<endl;
    }

    void afisare()
    {
        cout<<"Adresa web este: "<<adresa_web<<" cu nr de vizitaori "<<nr_vizitatori<<" si discount "<<discount<<endl;
    }

    void afisare_prop_o(Proprietar &p)
    {
        cout<<p;
    }

    void setOFarmacieAdresa(string a)
    {
        adresa_web = a;
    }
    void setOFarmacieVizitatori(int v)
    {
        nr_vizitatori = v;
    }
    void setOFarmacieDiscount(int d)
    {
        discount = d;
    }

    string getOFarmacieAdresa() const
    {
        return adresa_web;
    }
    int getOFarmacieVizitatori() const
    {
        return nr_vizitatori;
    }
    int getOFarmacieDiscount() const
    {
        return discount;
    }

};
void addFarmacie(vector<Farmacie>& pharmacy)
{
    Farmacie f;                                     //functie pentru a adauga o farmacie noua
    f.citire();
    pharmacy.push_back(f);
}
void addFarmacie_online(vector<Farmacie_Online>& pharmacy_online)
{
    Farmacie_Online fo;                             //functie pentru a adauga o farmacie online noua
    fo.citire();
    pharmacy_online.push_back(fo);
}

template<class T>                               //Template
void Total(vector<T>& pharmacy)
{
    int s = 0;
    for(long long unsigned int i = 0; i < pharmacy.size(); i++)
            s += pharmacy[i].getFarmacieAngajati();
    cout<<"Numarul total de angajati ai farmaciilor: "<<s<<endl;
}
template<>                                                  //Specializare pentru totalul vizitatorilor farmaciilor online
void Total(vector<Farmacie_Online>& pharmacy_online)
{
    int s = 0;
    for(long long unsigned int i = 0; i < pharmacy_online.size(); i++)
            s += pharmacy_online[i].getOFarmacieVizitatori();
    cout<<"Numarul total de vizitatori ai farmaciilor online: "<<s<<endl;

}

void meniu(vector<Farmacie_Online>& pharmacy_online,vector<Farmacie>& pharmacy, Proprietar &p)      //meniul interactiv
{
    cout<<"1.Adaugati farmacie"<<endl<<"2.Adaugati farmacie online"<<endl<<"3.Afisati farmaciile"<<endl;
    cout<<"4.Afisati farmaciile online"<<endl<<"5.Afisati proprietar"<<endl<<"6.Schimbati varsta proprietar"<<endl<<"7.Exit"<<endl;
    int f;
    cin>>f;
    cout<<endl;
    if(f==1)
        addFarmacie(pharmacy);

    if(f==2)
        addFarmacie_online(pharmacy_online);

    if(f==3)
    {
        Farmacie f;
        f.afisare_prop(p);
        for(long long unsigned int i = 0; i < pharmacy.size(); i++)
                pharmacy[i].afisare();

    }

    if(f==4)
    {
        Farmacie_Online fo;
        fo.afisare_prop_o(p);
        for(long long unsigned int i = 0; i < pharmacy_online.size(); i++)
            pharmacy_online[i].afisare();
    }

    if(f==5)
    {
        cout<<p;
    }

    if(f==6)
    {
        Farmacie fp;
        cin>>fp;
        cout<<fp;
    }

    if(f==7)
        {
            Total<Farmacie_Online>(pharmacy_online);
            cout<<"La revedere!"<<endl;
        }
    else
    {
        cout<<endl;
        meniu(pharmacy_online,pharmacy,p);
    }
}



int main()
{   vector<Farmacie_Online> pharmacy_online;        //uitlizare STL
    vector<Farmacie> pharmacy;
    cout<<"FARMACII"<<endl<<endl;
    cout<<"Dati numele si varsta proprietarului:"<<endl;
    string nume;
    int varsta;
    cin>>nume>>varsta;
    cout<<endl;
    Proprietar p(nume,varsta);      //crearea obligatorie a unui proprietar
    p.modificare_salariu(4500);
    meniu(pharmacy_online,pharmacy,p);
    return 0;
}
