#include <bits/stdc++.h>
#define chmpn(i,l,r) for(int i=l; i<r; ++i)
#define prime(i,r,l) for(int i=r; i>=l; --i)
#define rgx(a,b) for(auto &a:b)

using namespace std;

// https://medium.com/@sandeep4.verma/system-design-scalable-url-shortener-service-like-tinyurl-106f30f23a82

string aFile="Trip.txt", uFile="Reservation.txt";
struct tour{
    string aPlace, aCode, aCountry, aDays, aPrices;
    string uPhone, uName, uPeople, uDate, uStatus, uDcode;
};
class Tourist{
public:
// admin
    void aPack(tour r){ // packs details in string and writes to trip.txt
        ofstream fp(aFile,ios::out|ios::app); // manipulate files. if file exists, app (append the text) else make and add text
        if(!fp){cout<< "can't open file."; exit(0);}
        string buff=r.aCode+"|"+r.aPlace+"|"+r.aCountry+"|"+r.aDays+"|"+r.aPrices;
        while (buff.length()<45) buff+="|";
        fp<< buff << endl; // writes buff to file
        fp.close();
    }
    tour aUnpack(string buff){ // extracting tour struct details
        tour r; size_t n=0;
        n=buff.find("|"); r.aCode=   buff.substr(0,n); buff.erase(0,n+1);
        n=buff.find("|"); r.aPlace=  buff.substr(0,n); buff.erase(0,n+1);
        n=buff.find("|"); r.aCountry=buff.substr(0,n); buff.erase(0,n+1);
        n=buff.find("|"); r.aDays=   buff.substr(0,n); buff.erase(0,n+1);
        n=buff.find("|"); r.aPrices= buff.substr(0,n); buff.erase(0,n+1);
        return r;
    }
    void aWrite(){ // input of trip
        tour s;
        cout << "destination code: "; cin >> s.aCode;
        cout << "place you want to visit: "; cin >> s.aPlace;
        cout << "destination country: "; cin >> s.aCountry;
        cout << "no. of days of trip: "; cin >> s.aDays;
        cout << "cost of trip: "; cin >> s.aPrices;
        aPack(s);
    }
    void aDis(){
        ifstream fp(aFile,ios::in);
        if(!fp){cout << "can't open file."; exit(0);}
        cout << "Sr no.\tDest. code\tPlace\t\tCountry\t\tDuration\tPrices\n\n";
        int c=1; string buff;
        while (getline(fp,buff)){
            tour r=aUnpack(buff);
            cout << c++ << '\t' << r.aCode << '\t' << r.aPlace << "\t\t" << r.aCountry << "\t\t" << r.aCountry << "\t\t" << r.aDays << '\t' << r.aPrices <<'\n'<< endl;
        }
        fp.close();        
    }
    void aModify(){
        fstream fp; string aCode, buff; int i=0,j,c; tour s[100];
        fp.open(aFile,ios::in); if(!fp){cout << "can't open file."; exit(0);}
        cout << "destination code to be modified: "; cin >> aCode; 
        while (true){
            getline(fp,buff); if(fp.eof()) break; // till array of trips finishes
            s[i++]=aUnpack(buff);
        }
        for(j=0; j<i; ++j){ // tours in array
            if(s[j].aCode==aCode){
                cout << "trip details:\ndestination code: " << s[j].aCode << "\ndestination place: " << s[j].aPlace << "\ndestination country: " << s[j].aCountry << "\nno. of days: " << s[j].aDays << "\ncost of trip: " << s[j].aPrices << "\n";
                cout << "to update, enter:\n1 for place\n2 for days\n3 for cost\n"; cin >> c;
                switch (c){
                case 1:
                    cout << "destination place: "; cin >> s[j].aPlace;
                    cout << "destination country: "; cin >> s[j].aCountry;
                    break;
                case 2:
                    cout << "no. of days: "; cin >> s[j].aDays;
                    break;
                case 3:
                    cout << "cost of trip: "; cin >> s[j].aPrices;
                    break;
                default:
                    break;
                }
                break;
            }
        }
        if(i==j){cout << "no trip found."; return;}
        fp.close();
        fstream fd(aFile,ios::out|ios::trunc);
        if(!fd){cout << "file not found."; exit(0);}
        for(j=0; j<i; ++j) aPack(s[j]);
        fd.close();
    }
// user
    void uPack(tour r){
        fstream fp(uFile,ios::out|ios::app);
        if(!fp){cout << "file not found."; exit(0);}
        string buff=r.uName+"|"+r.uPhone+"|"+r.uPeople+"|"+r.uDcode+"|"+r.uDate+"|"+r.uStatus;
        while (buff.length()<45) buff+="|";
        fp<<buff<<endl; fp.close();
    }
    tour uUnpack(string buff){
        tour r; stringstream ss(buff);
        getline(ss,r.uName,'|'); getline(ss,r.uPhone,'|'); getline(ss,r.uPeople,'|'); getline(ss,r.uDcode,'|'); getline(ss,r.uDate,'|'); getline(ss,r.uStatus,'|');
        return r; 
    }
    void uWrite(){
        tour r;
        cout << "name: "; cin >> r.uName;
        cout << "contact no.: "; cin >> r.uPhone;
        cout << "no. of tourists: "; cin >> r.uPeople;
        cout << "destination code: D-"; cin >> r.uDcode;
        cout << "date of journey(dd/mm/yy): "; cin >> r.uDate;
        cout << "enter 'confirm' to confirm the registration: "; cin >> r.uStatus;
        uPack(r);
    }
    void uDis(){
        fstream fp(uFile,ios::in); string buff; tour r;
        if(!fp){cout << "file not found."; exit(0);}
        cout << "Sr no.\tName\t\tContact no.\t\tPeople\tDate\t\tDestination code\tStatus\n\n";
        int c=1;
        while (1){
            getline(fp,buff);
            if(fp.eof()) break;
            r=uUnpack(buff);
            cout <<c++<<'\t'<<r.uName<<"\t\t"<<r.uPhone<<"\t\t"<<r.uPeople<<'\t'<<r.uDate<<"\t\t"<<r.uDcode<<'\t'<<r.uStatus<<endl;
        }
        fp.close();
    }
    void uModify(){
        fstream fp(uFile,ios::in); string uName,buff; int i=0,j; tour s[100];
        if(!fp){cout<<"file not found."; exit(0);}
        cout<<"enter name to cancel registration: "; cin >> uName;
        while (1){
            getline(fp,buff);
            if(fp.eof()) break;
            s[i++]=uUnpack(buff);
        }
        for(j=0; j<i; ++j){
            if(s[j].uName==uName){
                cout << "reservation details:\nname: "<<s[j].uName<<"\ncontact no.: "<<s[j].uPhone<<"\nno. of people: "<<s[j].uPeople<<"\ndestination: "<<s[j].uDcode<<"\ndate of journey: "<<s[j].uDate<<"\nstatus: "<<s[j].uStatus<<"\n";
                cout << "enter 'cancel' to cancel ticket: "; cin >> s[j].uStatus;
                cout << "reservation cancelled.\n";
                cout << "name: "<<s[j].uName<<"\ncontact no.: "<<s[j].uPhone<<"\nno. of people: "<<s[j].uPeople<<"\ndestination: "<<s[j].uDcode<<"\ndate of journey: "<<s[j].uDate<<"\nstatus: "<<s[j].uStatus<<"\n";
                break;
            }
        }
        if(i==j){cout << "record not found."; exit(0);}
        fp.close();
        fstream fd(uFile,ios::out|ios::trunc);
        if(!fd){cout << "can't open file."; exit(0);}
        for(j=0; j<i; ++j) uPack(s[j]);
        fd.close();
    }
    void uSearch(){
        fstream fp(uFile,ios::in); string uName,buff; int i=0,j; tour s;
        if(!fp){cout << "can't open file.";exit(0);}
        cout << "name to search: "; cin >> uName;
        while (1){
            getline(fp,buff);
            if(fp.eof())break;
            s=uUnpack(buff);
            if(s.uName==uName){
                cout << "reservation found.\nname: "<<s.uName<<"\ncontact no.: "<<s.uPhone<<"\nno. of people: "<<s.uPeople<<"\ndestination: "<<s.uDcode<<"\ndate of journey: "<<s.uDate<<"\nstatus: "<<s.uStatus<<"\n";
                return;
            }
        }
        cout<<"reservation not found.";
    }
};

int main(int argc, char const *argv[]){
    cout<<"tourist reservation system in cpp:\n\npress ENTER to continue.\n";
    if(cin.get()=='\n'){
        system("cls");
        int ch,c1,c2; Tourist obj;
        cout << "who are you?\n1. Admin\n2. User\nEnter 1/2 or Ctrl+C to exit: "; cin >> ch;
        switch (ch){
        case 1: // admin
            system("cls");
            cout << "welcome admin\nchoose:\n1. New trips\n2. Display a trip\n3. Display a reservation\n4. Update trip\nYou know how to exit anytime. Your choice please: ";
            while (1){
                cin >> c1;
                switch (c1){
                case 1: obj.aWrite(); break;
                case 2: obj.aDis(); break;
                case 3: obj.uDis(); break;
                case 4: obj.aModify(); break;
                default: exit(0);
                }
            }
            break;
        case 2: // user
            system("cls");
            cout << "welcome user\nchoose:\n1. New reservation\n2. Search reservation\n3. Cancel reservation\nYou know how to exit anytime. Your choice please: ";
            while (1){
                cin >> c2;
                switch (c2){
                case 1: cout << "\tChoose your destination.\n"; obj.aDis(); obj.uWrite(); break;
                case 2: obj.uSearch(); break;
                case 3: obj.uModify(); break;
                default: exit(0);
                }
            }
        default: exit(0);
        }
    }
    return 0;
}