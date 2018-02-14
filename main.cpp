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

int zapisywanieKontaktu(vector<Kontakt> &kontakty, int iloscKontaktow) {
    system("cls");
    kontakty[iloscKontaktow].id = iloscKontaktow+1;
    cout << "Podaj imie: ";
    cin >> kontakty[iloscKontaktow].imie;
    cout << "Podaj nazwisko: ";
    cin >> kontakty[iloscKontaktow].nazwisko;
    cout << "Podaj nr. telefonu: ";
    cin.sync();
    getline(cin,kontakty[iloscKontaktow].telefon);
    cout << "Podaj adres email: ";
    cin >> kontakty[iloscKontaktow].email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin,kontakty[iloscKontaktow].adres);

    fstream plik;
    plik.open("kontakty.txt", ios::out | ios::app);
    if(plik.good() == false) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); //czerwony
        cout << "Wystapil problem przy probie zapisu danych do pliku." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
        return 0;
    }
    plik << kontakty[iloscKontaktow].id << "|";
    plik << kontakty[iloscKontaktow].imie << "|";
    plik << kontakty[iloscKontaktow].nazwisko << "|";
    plik << kontakty[iloscKontaktow].telefon << "|";
    plik << kontakty[iloscKontaktow].email << "|";
    plik << kontakty[iloscKontaktow].adres << "|" << endl;
    plik.close();

    iloscKontaktow++;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);// zielony
    cout << "Super, dodales nowe dane kontaktowe.";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);// bia³y
    Sleep(1900);
    return iloscKontaktow;
}

void wyswieltLinieOdzielajaca() {
    const int ILOSC_WYSIETLONYCH_ZNAKOW = 120;
    for(int i = 0; i < ILOSC_WYSIETLONYCH_ZNAKOW ; i++) cout << "_";
    cout << endl;
}

void wyswietlNaglowekTabeli() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    printf ("|%-3s|%-12s|%-12s|%-11s|%-30s|%-45s|\n",
            "lp.", "nr", "nazwisko", "tel", "email", "adres");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    wyswieltLinieOdzielajaca();
}

void wyswietlWierszTabeli(vector<Kontakt> &kontakty, int i) {
    printf ("|%-3i|%-12s|%-12s|%-11s|%-30s|%-45s|\n",
            i+1,
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

int wczytajKontaktyZPliku(vector<Kontakt> &kontakty) {
    string linia;

    int i = 0;
    size_t pozycjaZnakuOd =0;
    size_t pozycjaSeparatora;
    int iloscZnakow;


    fstream plik;
    plik.open("kontakty.txt",ios::in);
    if(plik.good() == false) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); //czerwony
        cout << "Wystapil problem z odczytem kontaktow z pliku." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
        return 0;
    }

    while(getline(plik, linia)) {
        pozycjaSeparatora = linia.find("|");
        kontakty[i].id = atoi(linia.substr(pozycjaZnakuOd, pozycjaSeparatora).c_str());

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        kontakty[i].imie = linia.substr(pozycjaZnakuOd, iloscZnakow);

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        kontakty[i].nazwisko = linia.substr(pozycjaZnakuOd, iloscZnakow);

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        kontakty[i].telefon = linia.substr(pozycjaZnakuOd, iloscZnakow);

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        kontakty[i].email = linia.substr(pozycjaZnakuOd, iloscZnakow);

        pozycjaZnakuOd = pozycjaSeparatora+1;
        pozycjaSeparatora = linia.find("|",pozycjaZnakuOd);
        iloscZnakow = pozycjaSeparatora - pozycjaZnakuOd;
        kontakty[i].adres = linia.substr(pozycjaZnakuOd, iloscZnakow);

        i++;
    }
    plik.close();
    return i; //ilosc kontaktow
}

int main() {
    vector<Kontakt> kontakty(10);

    int iloscKontaktow = wczytajKontaktyZPliku(kontakty);

    char wybor;

    string szukanaWartosc;

    while(true) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
        cout << "KSIAZKA ADRESOWA v0.1" << endl;
        cout << "---------------------------" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        cout << "Ilosc zapisanych kontaktow: "<< iloscKontaktow << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cout << "MENU GLOWNE: "<< endl;
        cout << "1. Dodaj dane przyjaciela" << endl;
        cout << "3. Znajdz kontakt" << endl;
        cout << "5. Wyswietl dane wszystkich zapisanych przyjaciol" << endl;
        cout << "9. Zakoncz program" << endl << endl;
        cout << "wybor: ";
        cin >> wybor;
        cin.sync();

        switch(wybor) {
        case '1':
            iloscKontaktow = zapisywanieKontaktu(kontakty, iloscKontaktow);
            break;
        case '3':
            system("cls");
            cout << "WYSZUKIWANIE:" << endl;
            cout << "1. Wyszukaj imie" << endl;
            cout << "2. Wyszukaj nazwisko" << endl;
            cout << "9. Menu glowne" << endl << endl;
            cout << "wybor: ";
            cin >> wybor;
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
        case  '9':
            exit(0);
            break;
        default:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout << "Nie ma takiej opcji w menu";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            Sleep(1500);
            break;
        }
    }
}