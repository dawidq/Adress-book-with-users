#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Adresat
{
    int id=0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};
string wczytajLinie()
{
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}
char wczytajZnak()
{
    string wejscie = "";
    char znak  = {0};

    while (true)
    {
        getline(cin, wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}
int dodajOsobe(vector<Adresat>&adresaci, int idZalogowanegoUzytkownika)
{
    Adresat obiekt;
    string imie, nazwisko, numerTelefonu, email, adres;
    string linia;
    int idOstatniegoAdresata=0;
    size_t pozycja = 0;
    string szukaj="|";
    cout << "Podaj imie: ";
    cin.ignore();
    imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu: ";
    numerTelefonu = wczytajLinie();
    cout << "Podaj email: ";
    email = wczytajLinie();
    cout << "Podaj adres: ";
    adres = wczytajLinie();

        fstream plik2;
        plik2.open("KsiazkaAdresowa.txt", ios::in | ios::out | ios::app);
        while (getline(plik2,linia))
        {
            pozycja=linia.find(szukaj);
            idOstatniegoAdresata=atoi((linia.substr(0,pozycja)).c_str());
        }
        plik2.close();

    if(idOstatniegoAdresata==0)
            {
            idOstatniegoAdresata=1;
            }
            else
            idOstatniegoAdresata=idOstatniegoAdresata+1;

    obiekt.id = idOstatniegoAdresata;
    obiekt.imie = imie;
    obiekt.nazwisko = nazwisko;
    obiekt.numerTelefonu = numerTelefonu;
    obiekt.email = email;
    obiekt.adres = adres;
    adresaci.push_back(obiekt);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out | ios::app);

    if (plik.good() == true)
    {
        plik << obiekt.id << "|";
        plik << idZalogowanegoUzytkownika << "|";
        plik << obiekt.imie << "|";
        plik << obiekt.nazwisko << "|";
        plik << obiekt.numerTelefonu << "|";
        plik << obiekt.email << "|";
        plik << obiekt.adres << "|";
        plik <<endl;
        plik.close();
        cout << endl << "Adresat zostal dodany" << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}
int wczytajadresataZPliku(vector<Adresat>&adresaci, int idZalogowanegoUzytkownika)
{
    int id=0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
    string linia;
    size_t pozycja = 0;
    string szukaj="|";
    int idUzytkownika=0;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in | ios::out | ios::app);
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            pozycja=linia.find(szukaj);
            id=atoi((linia.substr(0,pozycja)).c_str());
            linia.erase(0,pozycja+1);

            pozycja=linia.find(szukaj);
            idUzytkownika=atoi((linia.substr(0,pozycja)).c_str());
            linia.erase(0,pozycja+1);

            pozycja=linia.find(szukaj);
            imie=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            pozycja=linia.find(szukaj);
            nazwisko=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            pozycja=linia.find(szukaj);
            numerTelefonu=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            pozycja=linia.find(szukaj);
            email=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            pozycja=linia.find(szukaj);
            adres=linia.substr(0,pozycja);
            if(idZalogowanegoUzytkownika==idUzytkownika)
            {
                adresaci.push_back(Adresat{id, imie, nazwisko, numerTelefonu, email, adres});
            }
            pozycja=0;
        }
        return id;


        plik.close();
    }
    else
        cout<<"Plik nie istnieje"<<endl;
}
void wyswietlWszystkieadresaci(vector<Adresat>&adresaci)
{
    for (vector<Adresat>::iterator itr = adresaci.begin(),
            koniec=adresaci.end();
            itr !=koniec; ++itr )
    {

        cout<<itr->imie<<endl;
        cout<<itr->nazwisko<<endl;
        cout<<itr->numerTelefonu<<endl;
        cout<<itr->email<<endl;
        cout<<itr->adres<<endl;
        cout << endl;
    }
    system("pause");
}
void wyszukajPoImieniu(vector<Adresat>&adresaci)
{
    string imie;
    cout << "Poda imie adresata jakiego mamy wyszukac: ";
    imie = wczytajLinie();
    for (vector<Adresat>::iterator itr = adresaci.begin(),
            koniec=adresaci.end();
            itr !=koniec; ++itr )
    {
        if (itr->imie==imie)
        {

            cout<<itr->imie<<endl;
            cout<<itr->nazwisko<<endl;
            cout<<itr->numerTelefonu<<endl;
            cout<<itr->email<<endl;
            cout<<itr->adres<<endl;
            cout << endl;
        }

    }
    system("pause");
}
void wyszukajPoNazwisku(vector<Adresat>&adresaci)
{
    string nazwisko;
    cout << "Podaj nazwisko adresata jakiego mamy wyszukac: ";
    nazwisko = wczytajLinie();
    for (vector<Adresat>::iterator itr = adresaci.begin(),
            koniec=adresaci.end();
            itr !=koniec; ++itr )
    {
        if (itr->nazwisko==nazwisko)
        {

            cout<<itr->imie<<endl;
            cout<<itr->nazwisko<<endl;
            cout<<itr->numerTelefonu<<endl;
            cout<<itr->email<<endl;
            cout<<itr->adres<<endl;
            cout << endl;
        }
    }
    system("pause");
}
bool sprawdzanieIstnieniaIdAdresata(vector<Adresat>&adresaci,int idAdresata)
{
    for (vector<Adresat>::iterator itr = adresaci.begin(),
            koniec=adresaci.end();
            itr !=koniec; ++itr )
    {
        if (itr->id==idAdresata)
        {
            return true;
        }
        else
            false;
    }
}
void dodanieDanychDoPlikuPoEdycji(vector<Adresat>&adresaci, int idAdresata, int idZalogowanegoUzytkownika)
{
    int id=0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
    string linia;
    size_t pozycja = 0;
    string szukaj="|";
    int idUzytkownika=0;

    fstream plik1;
    plik1.open("KsiazkaAdresowa.txt", ios::in | ios::out | ios::app);
    fstream plik2;
    plik2.open("TempKsiazkaAdresowa.txt", ios::out);
    while (getline(plik1,linia))
    {
        pozycja=linia.find(szukaj);
        id=atoi((linia.substr(0,pozycja)).c_str());

        if(idAdresata==id)
        {
            for (vector<Adresat>::iterator itr = adresaci.begin(),
                    koniec=adresaci.end();
                    itr !=koniec; ++itr )
            {
                if(itr->id==id)
                {
                    plik2 << itr->id << "|";
                    plik2 << idZalogowanegoUzytkownika << "|";
                    plik2 << itr->imie << "|";
                    plik2 << itr->nazwisko << "|";
                    plik2 << itr->numerTelefonu << "|";
                    plik2 << itr->email << "|";
                    plik2 << itr->adres << "|";
                    plik2 <<endl;
                }

            }
        }
        else
            plik2 <<linia<<endl;
        pozycja=0;
    }
    plik1.close();
    plik2.close();
    remove("KsiazkaAdresowa.txt");
    rename("TempKsiazkaAdresowa.txt","KsiazkaAdresowa.txt");
}
void edytujImie(vector<Adresat>&adresaci, int idAdresata, int idZalogowanegoUzytkownika)
{
    for (vector<Adresat>::iterator itr = adresaci.begin(),
            koniec=adresaci.end();
            itr !=koniec; ++itr )
    {
        if (itr->id==idAdresata)
        {
            cout << endl;
            cout<<"Zapisane imie: "<<itr->imie<<endl;
            cout << endl;
            cout<<"Podaj nowe imie: ";
            cin.ignore();
            itr->imie=wczytajLinie();
            dodanieDanychDoPlikuPoEdycji(adresaci,idAdresata, idZalogowanegoUzytkownika);
            cout<<"Cos niesamowitego! Twoje imie zostalo zmienione!"<<endl;
        }
    }

    Sleep( 1000 );
}
void edytujNazwisko(vector<Adresat>&adresaci, int idAdresata, int idZalogowanegoUzytkownika)
{
    for (vector<Adresat>::iterator itr = adresaci.begin(),
            koniec=adresaci.end();
            itr !=koniec; ++itr )
    {
        if (itr->id==idAdresata)
        {
            cout << endl;
            cout<<"Zapisane nazwisko: "<<itr->nazwisko<<endl;
            cout << endl;
            cout<<"Podaj nowe nazwisko: ";
            cin.ignore();
            itr->nazwisko=wczytajLinie();
            dodanieDanychDoPlikuPoEdycji(adresaci,idAdresata,idZalogowanegoUzytkownika);
            cout<<"Cos niesamowitego! Twoje nazwisko zostalo zmienione!"<<endl;
        }
    }

    Sleep( 1000 );
}
void edytujNumerTelefonu(vector<Adresat>&adresaci, int idAdresata, int idZalogowanegoUzytkownika)
{
    for (vector<Adresat>::iterator itr = adresaci.begin(),
            koniec=adresaci.end();
            itr !=koniec; ++itr )
    {
        if (itr->id==idAdresata)
        {
            cout << endl;
            cout<<"Zapisany numer telefonu: "<<itr->numerTelefonu<<endl;
            cout << endl;
            cout<<"Podaj nowy numer telefonu: ";
            cin.ignore();
            itr->numerTelefonu=wczytajLinie();
            dodanieDanychDoPlikuPoEdycji(adresaci,idAdresata,idZalogowanegoUzytkownika);
            cout<<"Cos niesamowitego! Twoj numer telefonu zostal zmieniony!"<<endl;
        }
    }

    Sleep( 1000 );
}
void edytujEmail(vector<Adresat>&adresaci, int idAdresata, int idZalogowanegoUzytkownika)
{
    for (vector<Adresat>::iterator itr = adresaci.begin(),
            koniec=adresaci.end();
            itr !=koniec; ++itr )
    {
        if (itr->id==idAdresata)
        {
            cout << endl;
            cout<<"Zapisany email: "<<itr->email<<endl;
            cout << endl;
            cout<<"Podaj nowy email: ";
            cin.ignore();
            itr->email=wczytajLinie();
            dodanieDanychDoPlikuPoEdycji(adresaci,idAdresata,idZalogowanegoUzytkownika);
            cout<<"Cos niesamowitego! Twoj email zostal zmieniony!"<<endl;
        }
    }

    Sleep( 1000 );
}
void edytujAdres(vector<Adresat>&adresaci, int idAdresata, int idZalogowanegoUzytkownika)
{
    for (vector<Adresat>::iterator itr = adresaci.begin(),
            koniec=adresaci.end();
            itr !=koniec; ++itr )
    {
        if (itr->id==idAdresata)
        {
            cout << endl;
            cout<<"Zapisany adres: "<<itr->adres<<endl;
            cout << endl;
            cout<<"Podaj nowy adres: ";
            cin.ignore();
            itr->adres=wczytajLinie();
            dodanieDanychDoPlikuPoEdycji(adresaci,idAdresata,idZalogowanegoUzytkownika);
            cout<<"Cos niesamowitego! Twoj adres zostal zmieniony!"<<endl;
        }
    }

    Sleep( 1000 );
}
int edytujAdresata(vector<Adresat>&adresaci, int idZalogowanegoUzytkownika)
{
    int idAdresata=0;
    char wybor2;
    cout<<"Witaj w menu edycji adresatow!"<<endl;
    cout<<endl;
    cout<<"Wprowadz ID adresata: ";
    cin>>idAdresata;
    cout<<endl;

    if(sprawdzanieIstnieniaIdAdresata(adresaci,idAdresata)==true)
    {
        cout << "Wybierz odpowiednie pole do edycji" << endl;
        cout<<endl;
        cout << "1. Imie" << endl;
        cout << "2. Nazwisko" << endl;
        cout << "3. Numer telefonu" << endl;
        cout << "4. Email" << endl;
        cout << "5. Adres" << endl;
        cout << "6. Powrot do menu glownego" << endl;
        cout<<endl;
        cout << "Wybierz opcje: ";

        cin>>wybor2;

        if (wybor2 == '1')
        {
            edytujImie(adresaci, idAdresata,idZalogowanegoUzytkownika);
        }
        else if (wybor2 == '2')
        {
            edytujNazwisko(adresaci, idAdresata,idZalogowanegoUzytkownika);
        }
        else if (wybor2 == '3')
        {
            edytujNumerTelefonu(adresaci, idAdresata,idZalogowanegoUzytkownika);
        }
        else if (wybor2 == '4')
        {
            edytujEmail(adresaci, idAdresata,idZalogowanegoUzytkownika);
        }
        else if (wybor2 == '5')
        {
            edytujAdres(adresaci, idAdresata,idZalogowanegoUzytkownika);
        }
        else if (wybor2 == '6')
        {
            system("pause");
        }
    }
    else
        cout<<"Nie istnieje adresat z takim numerem ID! Wpisz poprawny numer!"<<endl;
    system("pause");
}
void usunAdresata(vector<Adresat>&adresaci)
{
    int idAdresata=0;
    int id=0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
    string linia;
    size_t pozycja = 0;
    string szukaj="|";
    int idUzytkownika=0;
    int i=0;
    string CzyChceszUsunac;
    cout<<"Witaj tutaj mozesz usunac adresata!"<<endl;
    cout<<endl;
    cout<<"Wprowadz ID adresata: ";
    cin.sync();
    cin>>idAdresata;
    if(sprawdzanieIstnieniaIdAdresata(adresaci,idAdresata)==true)
    {
        cout<<endl;
        cout<<"Czy napewno chcesz usunac adresata o numerze ID: "<<idAdresata<<endl;
        cin>>CzyChceszUsunac;

        if(CzyChceszUsunac=="t")
        {

            fstream plik1;
            plik1.open("KsiazkaAdresowa.txt", ios::in | ios::out | ios::app);
            fstream plik2;
            plik2.open("TempKsiazkaAdresowa.txt", ios::out);
            while (getline(plik1,linia))
            {
                pozycja=linia.find(szukaj);
                id=atoi((linia.substr(0,pozycja)).c_str());

                if(idAdresata==id)
                {
                    for (vector<Adresat>::iterator itr = adresaci.begin(),
                            koniec=adresaci.end();
                            itr !=koniec; ++itr )
                    {
                        if(itr->id==idAdresata)
                        {
                            adresaci.erase(itr);
                            plik2 <<"";
                        }

                    }

                }
                else
                    plik2 <<linia<<endl;
                pozycja=0;
            }
            plik1.close();
            plik2.close();
            remove("KsiazkaAdresowa.txt");
            rename("TempKsiazkaAdresowa.txt","KsiazkaAdresowa.txt");
            cout<<"Cos niesamowitego! Twoj adreat zostal usuniety!"<<endl;
            Sleep( 1000 );
        }
    }
    else
        cout<<"Nie istnieje adresat z takim numerem ID! Wpisz poprawny numer!"<<endl;

    Sleep( 1000 );

}
struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};
int rejestracja(vector<Uzytkownik>&uzytkownicy)
{
    Uzytkownik obiekt;
    string nazwa, haslo;
    cout<<"Podaj nazwe uzytkownika: ";
    cin.ignore();
    cin>>nazwa;
    int i=0;

    while(i<uzytkownicy.size())
    {
        if(uzytkownicy[i].nazwa == nazwa)
        {
            cout<<"taki uzytkownik istnieje. Podaj inna nazwe uzytkownika: "<<endl;
            cin>>nazwa;
            i=0;
        }
        else
            i++;
    }
    cout<<"Podaj haslo: ";
    cin>> haslo;
    if(uzytkownicy.empty() == true)
    {
        obiekt.id =1;
    }
    else

        obiekt.id=uzytkownicy.back().id + 1;

    obiekt.nazwa=nazwa;
    obiekt.haslo=haslo;

    uzytkownicy.push_back(obiekt);
    fstream plik;
    plik.open("Uzytkownicy.txt",ios::out | ios::app);

    if (plik.good() == true)
    {
        plik << obiekt.id << "|";
        plik << obiekt.nazwa << "|";
        plik << obiekt.haslo << endl;

        plik.close();
        cout << endl << "Rejestracja przebiegla pomyslnie! Gratulacje!" << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }

}
void wczytajUzytkownikowZPliku(vector<Uzytkownik>&uzytkownicy)
{
    int id=0;
    string nazwa="", haslo="";
    string linia;
    size_t pozycja = 0;
    string szukaj="|";

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in | ios::out | ios::app);
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            pozycja=linia.find(szukaj);
            id=atoi((linia.substr(0,pozycja)).c_str());
            linia.erase(0,pozycja+1);

            pozycja=linia.find(szukaj);
            nazwa=linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            haslo=linia;


            uzytkownicy.push_back(Uzytkownik{id, nazwa, haslo});
            pozycja=0;
        }

        plik.close();
    }
    else
        cout<<"Plik nie istnieje"<<endl;
}
int logowanie (vector<Uzytkownik>&uzytkownicy)
{
    string nazwa, haslo;
    cout<<"Podaj login: ";
    cin>>nazwa;

    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(),
            koniec=uzytkownicy.end();
            itr !=koniec; ++itr )
    {
        if(itr->nazwa == nazwa)
        {
            for (int proby =0; proby<3; proby++)

            {
                cout<<"Podaj haslo: pozostalo "<<3-proby<<" prob"<<endl;
                cin>>haslo;
                if (itr->haslo==haslo)
                {
                    cout<<"Zalogowales sie"<<endl;
                    Sleep(1000);
                    return itr->id;
                }
            }
            cout<<"Podales 3 razy niepoprawne haslo zaczekaj 3 sekundy przed kolejna proba"<<endl;
            Sleep(3000);
            return 0;
        }

    }
    cout<<"Nie ma uzytkownika z takim loginem"<<endl;
    Sleep(1500);
    return 0;
}
void zmianaHasla(vector<Uzytkownik>&uzytkownicy, int idZalogowanegoUzytkownika)
{
    int id=0;
    string nazwa="", haslo="";
    string newHaslo="";
    string linia;
    size_t pozycja = 0;
    string szukaj="|";
    int idUzytkownika=0;
    cout<<"Podaj nowe haslo: "<<endl;
    cin>>newHaslo;


    fstream plik1;
    plik1.open("Uzytkownicy.txt", ios::in | ios::out | ios::app);
    fstream plik2;
    plik2.open("TempUzytkownicy.txt", ios::out);
    while (getline(plik1,linia))
    {
        pozycja=linia.find(szukaj);
        id=atoi((linia.substr(0,pozycja)).c_str());

        if(idZalogowanegoUzytkownika==id)
        {
            for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(),
                    koniec=uzytkownicy.end();
                    itr !=koniec; ++itr )
            {
                if(itr->id==idZalogowanegoUzytkownika)
                {
                    itr->haslo=newHaslo;
                    plik2 << itr->id << "|";
                    plik2 << itr->nazwa << "|";
                    plik2 << itr->haslo << endl;
                }
            }

        }
        else
            plik2 <<linia<<endl;
        pozycja=0;
    }
    plik1.close();
    plik2.close();
    remove("Uzytkownicy.txt");
    rename("TempUzytkownicy.txt","Uzytkownicy.txt");


    cout<<endl;
    cout<<"Haslo zostalo zmienione!"<<endl;
    Sleep(1500);
}

int main()
{
    vector<Uzytkownik> uzytkownicy;
    vector<Adresat> adresaci;
    int idZalogowanegoUzytkownika=0;
    char wybor;
    wczytajUzytkownikowZPliku(uzytkownicy);
    while(true)
    {
        if(idZalogowanegoUzytkownika==0)
        {
            system("cls");
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zakoncz program"<<endl;
            cin>>wybor;
            if(wybor=='1')
            {
                rejestracja(uzytkownicy);
            }
            else if(wybor=='2')
            {
                idZalogowanegoUzytkownika=logowanie(uzytkownicy);
                wczytajadresataZPliku(adresaci, idZalogowanegoUzytkownika);
            }
            else if(wybor=='9')
            {
                exit(0);
            }
        }
        else
        {

            system("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl;
            cout<<endl;
            cout << "Wybierz opcje: ";

            cin>>wybor;

            if (wybor == '1')
            {
                dodajOsobe(adresaci,idZalogowanegoUzytkownika);
            }
            else if (wybor == '2')
            {

                wyszukajPoImieniu(adresaci);
            }
            else if (wybor == '3')
            {

                wyszukajPoNazwisku(adresaci);
            }
            else if (wybor == '4')
            {
                wyswietlWszystkieadresaci(adresaci);
            }
            else if (wybor == '5')
            {
                usunAdresata(adresaci);
            }
            else if (wybor == '6')
            {
                edytujAdresata(adresaci,idZalogowanegoUzytkownika);
            }
            else if(wybor=='7')
            {
                zmianaHasla(uzytkownicy,idZalogowanegoUzytkownika);
            }
            else if(wybor=='9')
            {
                adresaci.clear();
                idZalogowanegoUzytkownika=0;
                system("pause");
            }
        }
    }
    return 0;
}
