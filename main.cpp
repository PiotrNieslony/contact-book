#include <iostream>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>

using namespace std;

struct Kontakt {
    int id;
    string imie, nazwisko, telefon, email, adres;
};

string plikZKontaktami = "Adresaci.txt";
string plikZDanymiUzytkownikow = "Uzytkownicy.txt";

void wyswietlKomunikatNeutralny(string tekstDoWyswietlenia) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);// zielony
    cout << tekstDoWyswietlenia << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);// bia³y
    Sleep(1900);
}

void wyswietlKomunikatKrytyczny(string tekstDoWyswietlenia) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);// zielony
    cout << tekstDoWyswietlenia << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    system("pause");
}

void wyswietlKomunikatOstrzegawczy(string tekstDoWyswietlenia) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << tekstDoWyswietlenia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    Sleep(1500);
}

int zapisywanieKontaktu(vector<Kontakt> &kontakty, int iloscKontaktow, int idZalogowanegoUzytkownika, int idOstatniegoZapisanegoKontaktu) {
    system("cls");
    Kontakt pojedynczyKontakt;
    pojedynczyKontakt.id = idOstatniegoZapisanegoKontaktu + 1;
    cout << "Podaj imie: ";
    cin >> pojedynczyKontakt.imie;
    cout << "Podaj nazwisko: ";
    cin >> pojedynczyKontakt.nazwisko;
    cout << "Podaj nr. telefonu: ";
    cin.sync();
    getline(cin,pojedynczyKontakt.telefon);
    cout << "Podaj adres email: ";
    cin >> pojedynczyKontakt.email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin,pojedynczyKontakt.adres);

    kontakty.push_back(pojedynczyKontakt);

    fstream plik;
    plik.open(plikZKontaktami.c_str(), ios::out | ios::app);
    if(plik.good() == false) {
        wyswietlKomunikatKrytyczny("Wystapil problem przy probie zapisu danych do pliku." );
        return 0;
    }

    plik << pojedynczyKontakt.id << "|";
    plik << idZalogowanegoUzytkownika << "|";
    plik << pojedynczyKontakt.imie << "|";
    plik << pojedynczyKontakt.nazwisko << "|";
    plik << pojedynczyKontakt.telefon << "|";
    plik << pojedynczyKontakt.email << "|";
    plik << pojedynczyKontakt.adres << "|" << endl;
    plik.close();

    system("cls");
    wyswietlKomunikatNeutralny("Super, dodales nowe dane kontaktowe.");
    return pojedynczyKontakt.id;
}

void wyswieltLinieOdzielajaca() {
    const int ILOSC_WYSIETLONYCH_ZNAKOW = 120;
    for(int i = 0; i < ILOSC_WYSIETLONYCH_ZNAKOW ; i++) cout << "_";
    cout << endl;
}

void wyswietlNaglowekTabeli() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    printf ("|%-3s|%-12s|%-12s|%-11s|%-30s|%-45s|\n",
            "id", "nr", "nazwisko", "tel", "email", "adres");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    wyswieltLinieOdzielajaca();
}

void wyswietlWierszTabeli(vector<Kontakt> &kontakty, int i) {
    printf ("|%-3i|%-12s|%-12s|%-11s|%-30s|%-45s|\n",
            kontakty[i].id,
            kontakty[i].imie.c_str(),
            kontakty[i].nazwisko.c_str(),
            kontakty[i].telefon.c_str(),
            kontakty[i].email.c_str(),
            kontakty[i].adres.c_str());
}

void wyswietlanieWszystkichKontaktow(vector<Kontakt> &kontakty, int iloscKontaktow) {
    wyswietlNaglowekTabeli();
    for(int i=0; i < iloscKontaktow; i++) {
        wyswietlWierszTabeli(kontakty, i);
    }
    wyswieltLinieOdzielajaca();
}

void komunikatOilosciZnalezionychKontaktow(int iloscZnalezionychKontaktow, string szukanaWartosc) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11); //cyjan
    switch(iloscZnalezionychKontaktow) {
    case 0:
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14); //zolty
        cout << endl <<"Nie znaleziono zadnego kontaktu dla nazwy: \"" << szukanaWartosc <<"\"" << endl << endl;
        break;
    case 1:
        cout << endl <<"Znaleziono 1 kontakt" << endl  << endl;
        break;
    case 2:
    case 3:
    case 4:
        cout << endl <<"Znaleziono " << iloscZnalezionychKontaktow << " kontakty" << endl << endl;
        break;
    default:
        cout << endl <<"Znaleziono " << iloscZnalezionychKontaktow << " kontaktow" << endl << endl;
        break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15); // bialy
}

bool wyszukiwanieID(vector<Kontakt> &kontakty, int szukanaWartosc, int iloscKontaktow ) {

    wyswietlNaglowekTabeli();
    for(int i=0; i < iloscKontaktow; i++) {
        if (kontakty[i].id == szukanaWartosc) {
            wyswietlWierszTabeli(kontakty, i);
            return true;
        }
    }
    wyswieltLinieOdzielajaca();
    return false;
}

void wyszukiwanieImienia(vector<Kontakt> &kontakty, string szukanaWartosc, int iloscKontaktow ) {
    int iloscZnalezionychKontaktow = 0;
    wyswietlNaglowekTabeli();
    for(int i=0; i < iloscKontaktow; i++) {
        if (kontakty[i].imie == szukanaWartosc) {
            wyswietlWierszTabeli(kontakty, i);
            iloscZnalezionychKontaktow++;
        }
    }
    wyswieltLinieOdzielajaca();
    komunikatOilosciZnalezionychKontaktow(iloscZnalezionychKontaktow, szukanaWartosc);
}

void wyszukiwanieNazwiska(vector<Kontakt> &kontakty, string szukanaWartosc, int iloscKontaktow ) {
    int iloscZnalezionychKontaktow = 0;
    wyswietlNaglowekTabeli();
    for(int i=0; i < iloscKontaktow; i++) {
        if (kontakty[i].nazwisko == szukanaWartosc) {
            wyswietlWierszTabeli(kontakty, i);
            iloscZnalezionychKontaktow++;
        }
    }
    wyswieltLinieOdzielajaca();
    komunikatOilosciZnalezionychKontaktow(iloscZnalezionychKontaktow, szukanaWartosc);
}


int wczytajKontaktyZPliku(vector<Kontakt> &kontakty, int idZalogowanegoUzytkownika) {
    string linia;
    Kontakt pojedynczyKontakt;
    int idOstatniegoZapisanegoKontaktu = 0;
    size_t pozycjaZnakuOd;
    size_t pozycjaSeparatora;
    int iloscZnakow;
    int idWlascicielaKontaktu;

    fstream plik;
    plik.open(plikZKontaktami.c_str(),ios::in);
    if(plik.good() == false) {
        wyswietlKomunikatKrytyczny("Wystapil problem z odczytem kontaktow z pliku.");
        return 0;
    }

    while(getline(plik, linia)) {
        pozycjaSeparatora = linia.find("|");
        pojedynczyKontakt.id = atoi(linia.substr(0, pozycjaSeparatora).c_str());
        idOstatniegoZapisanegoKontaktu = pojedynczyKontakt.id;

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        idWlascicielaKontaktu = atoi(linia.substr(pozycjaZnakuOd, iloscZnakow).c_str());
        if(idWlascicielaKontaktu != idZalogowanegoUzytkownika) continue;

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        pojedynczyKontakt.imie = linia.substr(pozycjaZnakuOd, iloscZnakow);

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        pojedynczyKontakt.nazwisko = linia.substr(pozycjaZnakuOd, iloscZnakow);

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        pojedynczyKontakt.telefon = linia.substr(pozycjaZnakuOd, iloscZnakow);

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        pojedynczyKontakt.email = linia.substr(pozycjaZnakuOd, iloscZnakow);

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        pojedynczyKontakt.adres = linia.substr(pozycjaZnakuOd, iloscZnakow);

        kontakty.push_back(pojedynczyKontakt);
    }
    plik.close();
    return idOstatniegoZapisanegoKontaktu;
}

void zapiszZmienionyKontaktDoPliku(Kontakt pojedynczyKontakt, int idZalogowanegoUzytkownika) {
    string linia;
    size_t pozycjaSeparatora;
    int idKontaktu;
    int i = 0;
    string kopiaPlikuZKontaktami = "." + plikZKontaktami;
    remove(kopiaPlikuZKontaktami.c_str());
    if((rename(plikZKontaktami.c_str(), kopiaPlikuZKontaktami.c_str())) != 0) {
        cout << ( "Blad przy tworzeniu kopii pliku" ) << endl;
        return;
    }
    fstream plik;
    fstream plikKopia;
    plik.open(plikZKontaktami.c_str(), ios::out | ios::app);
    plikKopia.open(kopiaPlikuZKontaktami.c_str(),ios::in);
    if(plik.good() == false || plikKopia.good() == false) {
        wyswietlKomunikatKrytyczny("Wystapil problem przy probie zapisu danych do pliku.");
        return;
    }
    while(getline(plikKopia, linia)) {
        pozycjaSeparatora = linia.find("|");
        idKontaktu = atoi(linia.substr(0, pozycjaSeparatora).c_str());
        if (idKontaktu == pojedynczyKontakt.id) {
            plik << pojedynczyKontakt.id << "|";
            plik << idZalogowanegoUzytkownika << "|";
            plik << pojedynczyKontakt.imie << "|";
            plik << pojedynczyKontakt.nazwisko << "|";
            plik << pojedynczyKontakt.telefon << "|";
            plik << pojedynczyKontakt.email << "|";
            plik << pojedynczyKontakt.adres << "|" << endl;
            i++;
        } else {
            plik << linia << endl;
        }
    }
    plik.close();
    plikKopia.close();
}

void edytujDaneKontaktowe(vector<Kontakt> &kontakty, int iloscKontaktow, int id, int poleDoEdycji, int idZalogowanegoUzytkownika) {
    string nowaWartosc;
    for(int i = 0; i < iloscKontaktow; i++) {
        if(kontakty[i].id == id) {
            switch(poleDoEdycji) {
            case 1:
                cout << "Wprowadz imie: ";
                cin >> nowaWartosc;
                kontakty[i].imie = nowaWartosc;
                zapiszZmienionyKontaktDoPliku(kontakty[i],  idZalogowanegoUzytkownika);
                wyswietlKomunikatNeutralny("Dane zostaly zmienione.");
                return;
            case 2:
                cout << "Wprowadz nazwisko: ";
                cin >> nowaWartosc;
                kontakty[i].nazwisko = nowaWartosc;
                zapiszZmienionyKontaktDoPliku(kontakty[i],  idZalogowanegoUzytkownika);
                wyswietlKomunikatNeutralny("Dane zostaly zmienione.");
                return;
            case 3:
                cout << "Wprowadz telefon: ";
                cin.sync();
                getline(cin,kontakty[i].telefon);
                zapiszZmienionyKontaktDoPliku(kontakty[i],  idZalogowanegoUzytkownika);
                wyswietlKomunikatNeutralny("Dane zostaly zmienione.");
                return;
            case 4:
                cout << "Wprowadz emial: ";
                cin >> nowaWartosc;
                kontakty[i].email = nowaWartosc;
                zapiszZmienionyKontaktDoPliku(kontakty[i],  idZalogowanegoUzytkownika);
                wyswietlKomunikatNeutralny("Dane zostaly zmienione.");
                return;
            case 5:
                cout << "Wprowadz adres: ";
                cin.sync();
                getline(cin,kontakty[i].adres);
                zapiszZmienionyKontaktDoPliku(kontakty[i],  idZalogowanegoUzytkownika);
                wyswietlKomunikatNeutralny("Dane zostaly zmienione.");
                return;
            case 6:
                cout << "Wprowadz imie: ";
                cin >> nowaWartosc;
                kontakty[i].imie = nowaWartosc;
                cout << "Wprowadz nazwisko: ";
                cin >> nowaWartosc;
                kontakty[i].nazwisko = nowaWartosc;
                cout << "Wprowadz telefon: ";
                cin >> nowaWartosc;
                kontakty[i].telefon = nowaWartosc;
                cout << "Wprowadz emial: ";
                cin >> nowaWartosc;
                kontakty[i].email = nowaWartosc;
                cout << "Wprowadz adres: ";
                cin.sync();
                getline(cin,kontakty[i].adres);
                zapiszZmienionyKontaktDoPliku(kontakty[i],  idZalogowanegoUzytkownika);
                wyswietlKomunikatNeutralny("Dane zostaly zmienione.");
                return;
            }
        }
    }
    wyswietlKomunikatNeutralny("Kontakt o takim ID nie istnieje. W celu sprawdzenia ID wyszukaj lub wyswietl wszystkie kontakty");
}

void usunKontaktZPliku(int idKontaktuDoUsuniececia) {
    string linia;
    size_t pozycjaSeparatora;
    int idKontaktu;
    string kopiaPlikuZKontaktami = "." + plikZKontaktami;

    remove(kopiaPlikuZKontaktami.c_str());
    if((rename(plikZKontaktami.c_str(), kopiaPlikuZKontaktami.c_str())) != 0) {
        cout << ( "Blad przy tworzeniu kopii pliku" ) << endl;
        return;
    }

    fstream plik;
    fstream plikKopia;
    plik.open(plikZKontaktami.c_str(), ios::out | ios::app);
    plikKopia.open(kopiaPlikuZKontaktami.c_str(),ios::in);
    if(plik.good() == false || plikKopia.good() == false) {
        wyswietlKomunikatKrytyczny("Wystapil problem przy probie zapisu danych do pliku.");
        return;
    }

    while(getline(plikKopia, linia)) {
        pozycjaSeparatora = linia.find("|");
        idKontaktu = atoi(linia.substr(0, pozycjaSeparatora).c_str());
        if (idKontaktu != idKontaktuDoUsuniececia) plik << linia << endl;
    }

    plik.close();
    plikKopia.close();
}

int kasowanieKontaktu(vector<Kontakt> &kontakty, int iloscKontaktow, int idKontaktuDoUsuniececia, int idZalogowanegoUzytkownika) {
    bool czyPodanoPoprawneID = false;
    char wybor;
    vector<Kontakt>::iterator koniec = kontakty.end();
    for(vector<Kontakt>::iterator itr = kontakty.begin();
            itr != koniec; ++itr) {
        if((*itr).id == idKontaktuDoUsuniececia) {
            wyszukiwanieID(kontakty, (*itr).id, iloscKontaktow );
            cout << endl << "Czy napewno chcesz usunc wybrany kontakt?(T - tak, N - nie): ";
            cin >> wybor;
            if(wybor  == 't' || wybor  == 'T') {
                kontakty.erase(itr);
                usunKontaktZPliku(idKontaktuDoUsuniececia);
                wyswietlKomunikatNeutralny("Kontakt zostal usuniety.");
                return iloscKontaktow - 1;
            }
            czyPodanoPoprawneID = true;
            break;
        }
    }
    if(!czyPodanoPoprawneID) wyswietlKomunikatNeutralny("Kontakt o takim ID nie istnieje");
    return iloscKontaktow;
}

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

int rejestracja(vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    string nazwa, haslo;
    Uzytkownik pojedynczyUzytkownik;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    for (int i=0; i<iloscUzytkownikow; i++) {
        if (uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki uzytkownik nie istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    pojedynczyUzytkownik.nazwa = nazwa;
    pojedynczyUzytkownik.haslo = haslo;
    pojedynczyUzytkownik.id = iloscUzytkownikow+1;
    uzytkownicy.push_back(pojedynczyUzytkownik);

    fstream plikUzytkownicy;
    plikUzytkownicy.open(plikZDanymiUzytkownikow.c_str(), ios::out | ios::app);
    if(plikUzytkownicy.good() == false) {
        wyswietlKomunikatKrytyczny("Wystapil problem przy probie zapisu danych do pliku.");
        return 0;
    }

    plikUzytkownicy << pojedynczyUzytkownik.id << "|";
    plikUzytkownicy << pojedynczyUzytkownik.nazwa << "|";
    plikUzytkownicy << pojedynczyUzytkownik.haslo << "|" << endl;
    plikUzytkownicy.close();

    cout << "Konto zalozone" << endl;
    Sleep(1000);
    return iloscUzytkownikow + 1;
}

void zapiszWszystkichUzytkownikowDoPliku (vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    remove(plikZDanymiUzytkownikow.c_str());
    fstream plikUzytkownicy;
    plikUzytkownicy.open(plikZDanymiUzytkownikow.c_str(), ios::out | ios::app);
    if(plikUzytkownicy.good() == false) {
        wyswietlKomunikatKrytyczny("Wystapil problem przy probie zapisu danych do pliku.");
        system("pause");
        return;
    }
    for (int i = 0; i < iloscUzytkownikow; i++) {
        plikUzytkownicy << uzytkownicy[i].id << "|";
        plikUzytkownicy << uzytkownicy[i].nazwa << "|";
        plikUzytkownicy << uzytkownicy[i].haslo << "|" << endl;
    }
    plikUzytkownicy.close();
}

int logowanie(vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    string nazwa, haslo;
    cout << "Podaj nazwe:  ";
    cin >> nazwa;
    for (int i=0; i<iloscUzytkownikow; i++) {
        if (uzytkownicy[i].nazwa == nazwa) {
            for(int j=3; j>0; j--) {
                cout << "Podaj haslo. pozostalo prob " << j << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo) {
                    cout << "Zalogowales sie" << endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout << "podales 3 razy bledne haslo, odczeka 3s" << endl;
            Sleep(3000);
            return 0;
        }

    }
    cout << "Nie ma uzytkownika: " << nazwa << " ";
    Sleep(1500);
    return 0;
    Sleep(1500);
}

void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int iloscUzytkownikow, int idZalogowanegoUzytkownika) {
    string haslo;
    cout << "podaj nowe haslo: ";
    cin >> haslo;
    for(int i=0; i<iloscUzytkownikow; i++) {
        if(uzytkownicy[i].id == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }
    zapiszWszystkichUzytkownikowDoPliku (uzytkownicy, iloscUzytkownikow);
}

int wczytywanieUzytkownikow(vector<Uzytkownik> &uzytkownicy) {
    int iloscUzytkownikow = 0;
    string linia;
    Uzytkownik pojedynczyUzytkownik;
    fstream plikUzytkownicy;
    size_t pozycjaZnakuOd;
    size_t pozycjaSeparatora;
    int iloscZnakow;

    plikUzytkownicy.open(plikZDanymiUzytkownikow.c_str(),ios::in);
    if(plikUzytkownicy.good() == false) {
        wyswietlKomunikatKrytyczny("Wystapil problem z odczytem kontaktow z pliku: " + plikZDanymiUzytkownikow );
        return 0;
    }

    while(getline(plikUzytkownicy, linia)) {

        pozycjaSeparatora = linia.find("|");
        pojedynczyUzytkownik.id = atoi(linia.substr(0, pozycjaSeparatora).c_str());

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        pojedynczyUzytkownik.nazwa = linia.substr(pozycjaZnakuOd, iloscZnakow);

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        pojedynczyUzytkownik.haslo = linia.substr(pozycjaZnakuOd, iloscZnakow);

        uzytkownicy.push_back(pojedynczyUzytkownik);

        iloscUzytkownikow++;
    }
    plikUzytkownicy.close();
    return iloscUzytkownikow;
}

void naglowekAplikacji () {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout << "KSIAZKA ADRESOWA v0.3" << endl;
    cout << "---------------------------" << endl;
}

int main() {
    vector<Kontakt> kontakty;
    int iloscKontaktow;
    int idOstatniegoZapisanegoKontaktu = 0;
    int id;

    vector<Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = wczytywanieUzytkownikow(uzytkownicy);

    char wybor;

    string szukanaWartosc;

    while(true) {
        if(idZalogowanegoUzytkownika == 0) {
            system("cls");
            naglowekAplikacji();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
            cout << "Ilosc zarejestrowanych uzytkownikow: "<< iloscUzytkownikow << endl << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout << "1. Rejestracja" << endl;
            cout << "2. Logownaie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> wybor;

            if(wybor == '1') {
                iloscUzytkownikow = rejestracja(uzytkownicy, iloscUzytkownikow);
            } else if(wybor == '2') {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
                cout << "idZalogowanegoUzytkownika: " << idZalogowanegoUzytkownika << endl;
                idOstatniegoZapisanegoKontaktu = wczytajKontaktyZPliku(kontakty, idZalogowanegoUzytkownika);
            } else if(wybor == '9') {
                exit(0);
            }
        } else {
            system("cls");
            naglowekAplikacji();
            iloscKontaktow = kontakty.size();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
            cout << "Ilosc zapisanych kontaktow: "<< iloscKontaktow  << endl << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout << "MENU GLOWNE: "<< endl;
            cout << "1. Dodaj nowy kontakt" << endl;
            cout << "2. Edytuj kontakt" << endl;
            cout << "3. Usun kontakt" << endl;
            cout << "4. Znajdz kontakt" << endl;
            cout << "5. Wyswietl wszystkie zapisane kontaky" << endl;
            cout << "8. Uzytkownik" << endl;
            cout << "9. Zakoncz program" << endl << endl;
            cout << "wybor: ";
            cin.sync();
            cin >> wybor;
            cin.sync();

            switch(wybor) {
            case '1':
                idOstatniegoZapisanegoKontaktu = zapisywanieKontaktu(kontakty, iloscKontaktow, idZalogowanegoUzytkownika, idOstatniegoZapisanegoKontaktu);
                break;
            case '2':
                system("cls");
                cout << "EDYCJA:" << endl;
                cout << "Podaj ID kontaktu ktory chcesz edytowac: ";
                cin >> id;
                system("cls");
                if (wyszukiwanieID(kontakty, id, iloscKontaktow)) {
                    cout << "EDYCJA: " << endl << endl;
                    cout << "Co chcesz edytowac?: " << endl;
                    cout << "1. Imie" << endl;
                    cout << "2. Nazwisko" << endl;
                    cout << "3. Telefon" << endl;
                    cout << "4. Email" << endl;
                    cout << "5. Adres" << endl;
                    cout << "6. Wszystko" << endl;
                    cout << "9. Nic" << endl << endl;
                    cout << "wybor: ";
                    cin >> wybor;
                    cin.sync();
                    if (wybor == '9') break;
                    edytujDaneKontaktowe(kontakty, iloscKontaktow,id, wybor - 48, idZalogowanegoUzytkownika);
                } else {
                    system("cls");
                    wyswietlKomunikatNeutralny("Kontakt o takim ID nie istnieje. W celu sprawdzenia ID wyszukaj lub wyswietl wszystkie kontakty");
                }
                break;
            case '3':
                system("cls");
                cout << "Usuwanie:" << endl;
                cout << "Podaj ID kontaktu ktory chcesz usunac: " << endl;
                cin >> id;
                system("cls");
                iloscKontaktow = kasowanieKontaktu(kontakty, iloscKontaktow, id, idZalogowanegoUzytkownika);
                break;
            case '4':
                system("cls");
                cout << "WYSZUKIWANIE:" << endl;
                cout << "1. Wyszukaj imie" << endl;
                cout << "2. Wyszukaj nazwisko" << endl;
                cout << "9. Menu glowne" << endl << endl;
                cout << "wybor: ";
                cin >> wybor;
                cin.sync();
                if (wybor == '1') {
                    system("cls");
                    cout << "Podaj szukane Imie: ";
                    cin >> szukanaWartosc;
                    wyszukiwanieImienia(kontakty, szukanaWartosc, iloscKontaktow );
                    system("pause");
                } else if(wybor == '2') {
                    system("cls");
                    cout << "Podaj szukane nazwisko: ";
                    cin >> szukanaWartosc;
                    wyszukiwanieNazwiska(kontakty, szukanaWartosc, iloscKontaktow );
                    system("pause");
                } else if(wybor == '9') {
                    break;
                }

                break;
            case '5':
                system("cls");
                wyswietlanieWszystkichKontaktow(kontakty, iloscKontaktow);
                system("pause");
                break;
            case  '8':
                system("cls");
                cout << "1. Zmiana hasla" << endl;
                cout << "2. Wylogowywanie" << endl;
                cout << "9. Menu glowne" << endl;
                cin >> wybor;
                if(wybor == '1') {
                    zmianaHasla(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
                } else if(wybor == '2') {
                    idZalogowanegoUzytkownika = 0;
                    kontakty.clear();
                } else if(wybor == '9') {
                    break;
                }
                break;
            case  '9':
                exit(0);
                break;
            default:
                wyswietlKomunikatOstrzegawczy("Nie ma takiej opcji w menu");
                break;
            }
        }
    }
}
