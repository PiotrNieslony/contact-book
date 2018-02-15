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
    fstream plik;
    plik.open("kontakty.txt", ios::out | ios::app);
    if(plik.good() == false) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); //czerwony
        cout << "Wystapil problem przy probie zapisu danych do pliku." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
        return 0;
    }
    for(int i=0; i<iloscKontaktow; i++) {
        plik << kontakty[i].id << "|";
        plik << kontakty[i].imie << "|";
        plik << kontakty[i].nazwisko << "|";
        plik << kontakty[i].telefon << "|";
        plik << kontakty[i].email << "|";
        plik << kontakty[i].adres << "|" << endl;
    }
    plik.close();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);// zielony
    cout << "Kontakty zostaly zapisane do pliku kontakty.txt";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);// bia³y
    Sleep(1900);
    return iloscKontaktow;
}

int wczytajKontaktyZPliku(vector<Kontakt> &kontakty, string nazwaPliku) {
    string linia;
    int nr_lini = 1;
    int i = 0;

    fstream plik;
    plik.open(nazwaPliku.c_str(), ios::in);
    if(plik.good() == false) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); //czerwony
        cout << "Wystapil problem z odczytem kontaktow z pliku." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
        return 0;
    }

    while(getline(plik, linia)) {
        switch(nr_lini) {
        case 1:
            kontakty[i].id = atoi(linia.c_str());
            break;
        case 2:
            kontakty[i].imie = linia;
            break;
        case 3:
            kontakty[i].nazwisko = linia;
            break;
        case 4:
            kontakty[i].telefon = linia;
            break;
        case 5:
            kontakty[i].email = linia;
            break;
        case 6:
            kontakty[i].adres = linia;
            break;
        }
        nr_lini++;
        if(nr_lini == 7) {
            nr_lini = 1;
            i++;
        }
    }
    plik.close();
    return i; //ilosc kontaktow
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

int main() {
    vector<Kontakt> kontakty(10);

    int iloscKontaktow;

    string nazwaPliku;

    string szukanaWartosc;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout << "KONWERTER PLIKU KONTAKTY.TXT Z WERSJI v0.1 DO NOWSZEJ" << endl;
    cout << "---------------------------" << endl;
    cout << "Podaj nazwe pliku: " ;
    cin >> nazwaPliku;
    iloscKontaktow = wczytajKontaktyZPliku(kontakty, nazwaPliku);
    wyswietlanieWszystkichKontaktow(kontakty, iloscKontaktow);
    zapisywanieKontaktu(kontakty, iloscKontaktow);
}
