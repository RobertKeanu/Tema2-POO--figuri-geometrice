#include <bits/stdc++.h>
using namespace std;
class Punct{
private:
    float x,y;
public:
    //constructor fara parametrii
    Punct()
    {
        x=0;
        y=0;
    }
    //constructor cu parametrii
    Punct(float x_, float y_)
    {
        this->x=x_;
        this->y=y_;
    }
    //deconstructorul
    virtual ~Punct()
    {
        this->x=0;
        this->y=0;
    }
    //getter x
    float get_x() const
    {
        return x;
    }
    //getter y
    float get_y() const
    {
        return y;
    }
    //constructor de copiere
    Punct(const Punct& punct)
    {
        this->x = punct.x;
        this->y = punct.y;
    }
    //rescriere =
    Punct& operator=(const Punct &punct)
    {
        this->x = x;
        this->y = y;
        return *this; //daca this e diferit de pointer?
    }
    friend istream& operator>>(istream &in,Punct &punct)
    {
        cout<<"X :";
        in>>punct.x;
        cout<<"Y :";
        in>>punct.y;
        return in;
    }
    friend ostream& operator<<(ostream &out,Punct &punct)
    {
        out<<"Valoarea lui X este:"<<punct.x<<endl;
        out<<"Valoarea lui Y este:"<<punct.y<<endl;
        return out;
    }
};
class Gresit : public std::exception {
public:
    Gresit() = default;
    const char *what() const noexcept override{
        return "Figura nu este valida";
    }
};
class Patrat{
protected:
    static Punct stanga_jos;
    static int nr_fig;
    static float latura;
    bool valid;
public:      //constructori
    Patrat()
    {
        Punct punct;
        nr_fig++;
        Patrat::stanga_jos = punct; //mostenit din clasa punct
        Patrat::latura = 0;
        this->valid = false;
    }
    Patrat(const Punct& stanga_jos /* idk daca e ok .. asa zice clion*/,float latura)
    {
        this->stanga_jos = stanga_jos;
        this->latura = latura;
        if(latura > 0)
            this->valid = true;
        else
            this->valid = false;
    }
    ~Patrat()
    {
        Punct punct;
        this->stanga_jos = punct;
        this->latura = false;
        this->valid = false;
    }
//    float get_latura() const
//    {
//        return this->latura;  // se pot modifica valorile mai jos????
//    }
//    Punct get_stanga_jos() //??
//    {
//        Punct stanga_jos;
//        return this->stanga_jos;
//    }
    //constr de copiere
    Patrat(const Patrat& patrat)
    {
        stanga_jos = patrat.stanga_jos;
        latura = patrat.latura;   //e nevoie de this ?
    }
    Patrat& operator=(const Patrat& patrat)
    {
        if(this!=&patrat)
        {
            this->stanga_jos = patrat.stanga_jos;
            this->latura = patrat.latura;
            this->valid = patrat.valid;
        }
        return *this;
    }
    virtual bool get_valid()
    {
        return this->valid;
    }
    friend istream& operator>>(istream& in, Patrat& patrat); //intrebare.. cand facem citirea pentru clasa patrat
    friend ostream& operator<<(ostream& out, Patrat& patrat);
    float calcArie() const
    {
        if(valid == 1)
        return this->latura*this->latura;
        else
            return -1;
    }
    static int nr_ob()
    {
        return nr_fig;
    }
    virtual istream& Citire(istream& in)
    {
        cout<<"Valoarea punctului din stanga jos este: ";
        in>>this->stanga_jos;
        cout<<"Latura are valoarea : "<<endl;
        in>>this->latura;
        if(this-> latura > 0)
            this->valid = 1;
        else
            this->valid = 0;
        //valid = 0 sau valid = 1
        return in;
    }
    virtual ostream& Afisare(ostream& out) const
    {
        cout<<"Coordonatele punctului din stanga sunt: "<<this->stanga_jos<<endl;  // 2 erori non static data type stanga_jos??
        cout<<"Latura are lungimea: "<<this->latura<<endl;
        return out;
    }
};
istream& operator>>(istream& in, Patrat& patrat)
{
    return patrat.Citire(in);
}
ostream& operator<<(ostream& out, Patrat& patrat)
{
    return patrat.Afisare(out);
}
int Patrat::nr_fig;
class Dreptunghi:virtual public Patrat{
protected:
    float latura2;
    //fara parametrii
public:
    Dreptunghi():Patrat()
    {
//        static int nr_fig;
//        nr_fig++;
        this->latura2 = 0;
    }
    Dreptunghi(Punct punct,float latura,float latura2):Patrat(punct,latura)
    {
        this->latura2 = latura2;
        if(valid==1)
        {
            if(latura2 < 0)
                valid=0;
        }
    }
    Dreptunghi(float latura2) //cu parametrii
    {
        nr_fig++;
        this->latura2 = latura2;
    }
    ~Dreptunghi()
    {
        this->latura2 = 0;
    }
    float get_latura_drept() const
    {
        return this->latura2;
    }
    Dreptunghi(const Dreptunghi& drept):Patrat(drept)
    {
        this->latura2 = drept.latura2;
    }
    Dreptunghi& operator=(const Dreptunghi& drept)
    {
        if(this!=&drept)
        {
            Patrat::operator=(drept);
            this->latura2 = drept.latura2;
        }
        return *this;
    }
    virtual bool get_valid()
    {
        return this->valid;
    }
    virtual istream& Citire(istream& in)
    {
        Patrat::Citire(in);
        cout<<"Latura mare a dreptunghiului este : "<<endl;
        in>>latura2;
        if(valid == 1)
        {
            if(latura2<0)
                valid = 0;
        }
        return in;
    }
   virtual ostream& Afisare(ostream& out) const
    {
        Patrat::Afisare(out);
        cout<<"Latura mare a dreptunghiului are valoarea : "<<endl;
        out<<this->latura2<<endl;
        return out;
    }
    //pentru operatorii >> si << avem nevoie de mostenire / e nevoie de functii virtuale??
//    virtual void afisarea_Drept(const &Dreptunghi drept)      momentat trebuie facuta functia pentru << >> derivata din patrat
//    {
//
//    }
    virtual float calcArie()
    {
        if(valid == 1)
        return latura*latura2;
        else
            return -1;
    }
};
//Dreptunghi::Dreptunghi() : Patrat(){};
class Romb:virtual public Patrat{
protected:
    Punct colt_opus;
public:
    Romb();
    Romb(const Punct& punct, float latura, Punct colt):Patrat(punct, latura)
    {
        //implementare pentru valid = 0 sau valid = 1
        this->colt_opus=colt;
        float x1,x2,y1,y2;
        x1=stanga_jos.get_x();
        y1=stanga_jos.get_y();
        x2=colt_opus.get_x();
        y2=colt_opus.get_y();
        if(4*latura*latura>(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) && latura>0)
        {
            this->valid=1;
        }
        else
            this->valid=0;
    }
    Romb(const Romb& romb):Patrat(romb)
    {
        this->colt_opus = romb.colt_opus;
    }
    ~Romb()
    {
        Punct punct;
        colt_opus = punct;
    }
    Punct get_colt_opus()
    {
//        Punct colt_opus;
        return this->colt_opus;
    }
    virtual bool get_valid()
    {
        return this->valid;
    }
    Romb& operator=(const Romb& romb)
    {
        if(this!=&romb)
        {
            Patrat::operator=(romb);
            this->colt_opus = romb.colt_opus;
        }
        return *this;
    }

    virtual istream& Citire(istream& in)
    {
        Patrat::Citire(in);
        cout<<"Dati coordonatele coltului opus : "<<endl;
        in>>this->colt_opus;
        return in;
    }
    virtual ostream& Afisare(ostream &out)
    {
        Patrat::Afisare(out);
        cout<<"Coordonatele coltului opus sunt : "<<endl;
        out<< this -> colt_opus;
        return out;
    }
    virtual float calcArie()
    {
        float x1,x2,y1,y2,diag1,diag2,arie;
        x1 = stanga_jos.get_x();
        x2 = colt_opus.get_x();
        y1 = stanga_jos.get_y();
        y2 = stanga_jos.get_y();
        diag1 = (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
        diag2 = 2*sqrt(latura*latura - (diag1 * diag1)/4);
        arie = (diag1*diag2)/2;
        return arie;
    }
};
Romb::Romb():Patrat()
{
    Punct colt;
    this->colt_opus = colt;
}
class Paralelogram:public Dreptunghi, public Romb{
public:
    Paralelogram();
    Paralelogram(Punct punct, Punct punct2, float latura,float latura2):Dreptunghi(punct,latura,latura2), Romb(punct,latura2,punct2){};

    ~Paralelogram(){}; //se apeleaza automat de la celelalte clase
    Paralelogram(const Paralelogram& para):Dreptunghi(para),Romb(para){};
    virtual bool get_valid()
    {
        return this->valid;
    }
    Paralelogram& operator=(const Paralelogram& para)
    {
//            Patrat::operator=(para);
            if(this!=&para)
            {
                Dreptunghi::operator=(para);
                Romb::operator=(para);
            }
            return *this;
    }
    virtual istream& Citire(istream& in)
    {
        Patrat::Citire(in);
        cout<<"Dati coordonatele coltului opus : "<<endl;
        in>>this->colt_opus;
        cout<<"Latura 2 are lungimea : "<<endl;
        in>>this->latura2;
        float x1,x2,y1,y2;
        x1=stanga_jos.get_x();
        y1=stanga_jos.get_y();
        x2=colt_opus.get_x();
        y2=colt_opus.get_y();
        if(latura>0 && latura2>0 && latura*latura+latura2*latura2>=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
        {
            this->valid=true;
        }
        else
            this->valid=false;
        return in;
    }
    virtual ostream& Afisare(ostream& out)
    {
        Patrat::Afisare(out);
        cout<<"Coordonatele coltului opus sunt : "<<endl;
        out<<this->colt_opus;
        cout<<"Lungimea pentru latura 2 este : "<<endl;
        out<<this->latura2;
        return out;
    }
   virtual float calcArie()
    {
        if(valid==1) {
            float y1, y2;
            y1 = stanga_jos.get_y();
            y2 = colt_opus.get_y();
            return abs(y2 - y1) * latura;
        }
    }
};
Paralelogram::Paralelogram():Dreptunghi(), Romb(){};
class Trapez:public Paralelogram{
protected:
    float baza2;
    int caz;
public:
    Trapez():Paralelogram()
    {
        this->baza2 = 0;
        this->caz = 0;
    }
    Trapez(const Punct& punct, Punct punct2, float latura, float latura2, float baza2): Paralelogram(punct, punct2, latura, latura2)
    {
        this->baza2=baza2;
        caz = validare();
        if(caz)
            valid = true;
        else
            valid = false;
    }
    ~Trapez()
    {
        this->baza2=0;
    }
    Trapez(const Trapez& trap) : Paralelogram(trap)
    {
        this->baza2 = trap.baza2;
        this->caz = trap.caz;
    }
    bool get_valid()
    {
        return this->valid;
    }
//    float get_baza2() const
//    {
//        return this->baza2;
//    }
    Trapez& operator=(const Trapez& trap)
    {
        if(this!=&trap)
        {
            Paralelogram::operator=(trap);
            this->baza2 = trap.baza2;
            this->caz = trap.caz;
        }
        return *this;
    }
    virtual istream& Citire(istream& in)
    {
        Paralelogram::Citire(in);
        cout<<"Dati baza2 : "<<endl;
        in>>this->baza2;
        caz = validare();
        if(caz > 0)
            valid = true;
        else
            valid = false;
        return in;
    }
    int validare(){
        float x1,x2,x3,y1,y2,y3;
        x1=stanga_jos.get_x();
        y1=stanga_jos.get_y();
        x2=colt_opus.get_x();
        y2=colt_opus.get_y();
        x3=x1+baza2;
        y3=y1;
        if((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)==latura*latura){
            return 1;
        }
        if((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)==latura2*latura2){
            return 2;
        }
        x3=x2-latura;
        y3=y2;
        if((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)==latura2*latura2){
            return 3;
        }
        x3=x2-latura2;
        y3=y2;
        if((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)==latura*latura){
            return 4;
        }
        return 0;
    }
    float calcul_baza()
    {
        if(caz == 1 || caz == 4)
            return latura2;
        if (caz == 2 || caz == 3)
            return latura;
    }
    virtual ostream& Afisare(ostream& out)
    {
        Paralelogram::Afisare(out);
        cout<<"Baza2 are marimea : "<<endl;
        out<<this->baza2;
        return out;
    }
    virtual float calcArie()
    {
        if(valid==1)
        {
            float inaltime;
            inaltime = abs(stanga_jos.get_y() - colt_opus.get_y());
            float baza1;
            baza1 = calcul_baza();
            return (baza2 + baza1) * inaltime / 2;
        }//lat 1 sau lat 2 ramane de implementat
       else
           return -1;
    }
};
int main() {
    int OK=1;
    while(OK)
    {
        cout<<endl;
        cout<<"Oprirea programului se face prin apasarea tastei 0"<<endl;
        cout<<"Pentru a memora si afisa n elemente apasa 1"<<endl;
        cout<<"Pentru a citi si afisa o fig. geometrica apasa 2"<<endl;
        cout<<"Pentru a verifica daca o figura este valida apasa 3"<<endl;
        cout<<"Pentru a calcula aria unei figuri apasa 4"<<endl;
        cout<<"Pentru a afisa nr. de figuri geometrice apasa 5"<<endl;
        cout<<"Pentru upcasting(transformare din dreptunghi in patrat) apasa 6"<<endl;
        cout<<"Pentru downcasting(transformare din patrat in dreptunghi) apasa 7"<<endl;
        cout<<"Pentru evidentierea exceptiei (figura valida sau nu pentru patrat) apasa 8"<<endl;
        int cases;
        cin>>cases;
        switch(cases)
        {
            case 0:
            {
                OK = 0;
                break;
            }
            case 1:
            {
                int n;
                cin>>n;
                Patrat* fig[n];
                for(int i=0; i<n; i++)
                {
                    int opt;
                    cout<<endl;
                    cout<<"Pentru a introduce un patrat apasa 1"<<endl;
                    cout<<"Pentru a introduce un dreptunghi apasa 2"<<endl;
                    cout<<"Pentru a introduce un romb apasa 3"<<endl;
                    cout<<"Pentru a introduce un paralelogram apasa 4"<<endl;
                    cout<<"Pentru a introduce un trapez apasa 5"<<endl;
                    cin>>opt;
                    if(opt == 1)
                        fig[i] = new Patrat;
                    if(opt == 2)
                        fig[i] = new Dreptunghi;
                    if(opt == 3)
                        fig[i] = new Romb;
                    if(opt == 4)
                        fig[i] = new Paralelogram;
                    if(opt == 5)
                        fig[i] =  new Trapez;
                    cin>>*fig[i];
                }
                for(int i=0;i<n;i++)
                {
                    if(typeid(*fig[i]) == typeid(Patrat))
                        cout<<"figura"<<i+1<<"este patrat"<<endl;
                    if(typeid(*fig[i]) == typeid(Dreptunghi))
                        cout<<"figura"<<i+1<<"este dreptunghi"<<endl;
                    if(typeid(*fig[i]) == typeid(Romb))
                        cout<<"figura"<<i+1<<"este romb"<<endl;
                    if(typeid(*fig[i]) == typeid(Paralelogram))
                        cout<<"figura"<<i+1<<"este paralelogram"<<endl;
                    if(typeid(*fig[i]) == typeid(Trapez))
                        cout<<"figura"<<i+1<<"este trapez"<<endl;
                }


            }
            case 2:
            {
                cout<<"pentru introducere patrat apasa 1 : "<<endl;
                cout<<"pentru introducere dreptunghi apasa 2 : "<<endl;
                cout<<"pentru introducere romb apasa 3 : "<<endl;
                cout<<"pentru introducere paralelogram apasa 4 : "<<endl;
                cout<<"pentru introducere trapez apasa 5 : "<<endl;
                int opt;
                cout<<endl;
                cin>>opt;
                if(opt == 1)
                {
                    Patrat figura;
                    cin>>figura;
                    cout<<endl;
                    cout<<figura<<endl;
                }
                if(opt == 2)
                {
                   Dreptunghi figura;
                   cin>>figura;
                   cout<<endl;
                   cout<<figura<<endl;
                }
                if(opt == 3)
                {
                   Romb figura;
                   cin>>figura;
                   cout<<endl;
                   cout<<figura<<endl;
                }
                if(opt == 4)
                {
                   Paralelogram figura;
                   cin>>figura;
                   cout<<endl;
                   cout<<figura<<endl;
                }
                if(opt == 5)
                {
                   Trapez figura;
                   cin>>figura;
                   cout<<endl;
                   cout<<figura<<endl;
                }

            }
            case 3:
            {
                cout<<"pentru introducere patrat apasa 1 : "<<endl;
                cout<<"pentru introducere dreptunghi apasa 2 : "<<endl;
                cout<<"pentru introducere romb apasa 3 : "<<endl;
                cout<<"pentru introducere paralelogram apasa 4 : "<<endl;
                cout<<"pentru introducere trapez apasa 5 : "<<endl;
                int opt;
                cin>>opt;
                if(opt == 1)
                {
                    Patrat figura;
                    cin>>figura;
                    cout<<endl;
                    bool oki = figura.get_valid();
                    if(oki)
                        cout<<"valida"<<endl;
                    else
                        cout<<"nu e valida"<<endl;
                }
                if(opt == 2)
                {
                    Dreptunghi figura;
                    cin>>figura;
                    cout<<endl;
                    bool oki = figura.get_valid();
                    if(oki)
                        cout<<"valida"<<endl;
                    else
                        cout<<"nu e valida"<<endl;
                }
                if(opt == 3)
                {
                    Romb figura;
                    cin>>figura;
                    cout<<endl;
                    bool oki = figura.get_valid();
                    if(oki)
                        cout<<"valida"<<endl;
                    else
                        cout<<"nu e valida"<<endl;
                }
                if(opt == 4)
                {
                    Paralelogram figura;
                    cin>>figura;
                    cout<<endl;
                    bool oki = figura.get_valid();
                    if(oki)
                        cout<<"valida"<<endl;
                    else
                        cout<<"nu e valida"<<endl;
                }
                if(opt == 5)
                {
                    Trapez figura;
                    cin>>figura;
                    cout<<endl;
                    bool oki = figura.get_valid();
                    if(oki)
                        cout<<"valida"<<endl;
                    else
                        cout<<"nu e valida"<<endl;
                }
            }
            case 4:
            {
                cout<<"pentru introducere patrat apasa 1 : "<<endl;
                cout<<"pentru introducere dreptunghi apasa 2 : "<<endl;
                cout<<"pentru introducere romb apasa 3 : "<<endl;
                cout<<"pentru introducere paralelogram apasa 4 : "<<endl;
                cout<<"pentru introducere trapez apasa 5 : "<<endl;
                int opt;
                cin>>opt;
                if(opt == 1)
                {
                    Patrat figura;
                    cin>>figura;
                    cout<<endl;
                    cout<<"Aria figurii este : "<<figura.calcArie()<<endl;
                }
                else if(opt == 2)
                {
                    Dreptunghi figura;
                    cin>>figura;
                    cout<<endl;
                    cout<<"Aria figurii este : "<<figura.calcArie()<<endl;
                }
                else if(opt == 3)
                {
                    Romb figura;
                    cin>>figura;
                    cout<<endl;
                    cout<<"Aria figurii este : "<<figura.calcArie()<<endl;
                }
                else if(opt == 4)
                {
                    Paralelogram figura;
                    cin>>figura;
                    cout<<endl;
                    cout<<"Aria figurii este : "<<figura.calcArie()<<endl;
                }
                else if(opt == 5)
                {
                    Trapez figura;
                    cin>>figura;
                    cout<<endl;
                    cout<<"Aria figurii este : "<<figura.calcArie()<<endl;
                }
            }
            case 5:
            {
                cout<<Patrat::nr_ob()<<endl;
                break;
            }
            case 6:
            {
                cout<<"transformare din dreptunghi in patrat : "<<endl;
                Dreptunghi figura1;
                cin>>figura1;
                cout<<"figura2 este un patrat de forma : "<<endl;
                Patrat figura2 = static_cast<Dreptunghi>(figura1);
                cout<<figura2<<endl;
            }
            case 7:
            {
                cout<<"transformare din patrat in dreptunghi : "<<endl;
                Patrat* figura1 = new Dreptunghi;
                Dreptunghi* figura2;
                cin>>*figura1;
                figura2 = dynamic_cast<Dreptunghi*>(figura1);
                cout<<*figura2<<endl;
                break;
            }
            case 8:
            {
                cout<<"figura este valida sau nu? :"<<endl;
                Patrat figura;
                cin>>figura;
                cout<<endl;
                try{
                    bool oki = figura.get_valid();
                    if(oki)
                        cout<<"patrat valid"<<endl;
                }
                catch(const std::exception &e) //again nu e nev de std
                {
                    cout<<e.what()<<endl;
                } //nu stiu sigur daca e ok sau nu (verificarea se poate face pentru toate figurile destul de usor)
            }
        }
    }
    return 0;
}
