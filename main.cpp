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
    Kontakt pojedynczyKontakt;
    if(iloscKontaktow == 0) pojedynczyKontakt.id = 0;
    else pojedynczyKontakt.id = kontakty[iloscKontaktow-1].id+1;
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
    plik.open("kontakty.txt", ios::out | ios::app);
    if(plik.good() == false) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); //czerwony
        cout << "Wystapil problem przy probie zapisu danych do pliku." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
        return 0;
    }
    plik << pojedynczyKontakt.id << "|";
    plik << pojedynczyKontakt.imie << "|";
    plik << pojedynczyKontakt.nazwisko << "|";
    plik << pojedynczyKontakt.telefon << "|";
    plik << pojedynczyKontakt.email << "|";
    plik << pojedynczyKontakt.adres << "|" << endl;
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

void wyszukiwanieID(vector<Kontakt> &kontakty, int szukanaWartosc, int iloscKontaktow ) {

    wyswietlNaglowekTabeli();
    for(int i=0; i < iloscKontaktow; i++) {
        if (kontakty[i].id == szukanaWartosc) {
            wyswietlWierszTabeli(kontakty, i);
            return;
        }
    }
    wyswieltLinieOdzielajaca();
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

void zapiszWszystkieKontaktyDoPliku(vector<Kontakt> &kontakty, int iloscKontaktow) {
    remove("kontakty-kopia.txt");
    if((rename("kontakty.txt", "kontakty-kopia.txt")) != 0) {
        cout << ( "Blad przy tworzeniu kopii pliku" ) << endl;
        return;
    }
    fstream plik;
    plik.open("kontakty.txt", ios::out | ios::app);
    if(plik.good() == false) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); //czerwony
        cout << "Wystapil problem przy probie zapisu danych do pliku." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
        return;
    }
    for(int i = 0; i < iloscKontaktow; i++) {
        plik << kontakty[i].id << "|";
        plik << kontakty[i].imie << "|";
        plik << kontakty[i].nazwisko << "|";
        plik << kontakty[i].telefon << "|";
        plik << kontakty[i].email << "|";
        plik << kontakty[i].adres << "|" << endl;
    }
    plik.close();
}

int wczytajKontaktyZPliku(vector<Kontakt> &kontakty) {
    string linia;
    Kontakt pojedynczyKontakt;
    int i = 0;
    size_t pozycjaZnakuOd;
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
        pojedynczyKontakt.id = atoi(linia.substr(0, pozycjaSeparatora).c_str());

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

        i++;
    }
    plik.close();
    return i; //ilosc kontaktow
}

void komunikatInformacyjny(string tekstDoWyswietlenia) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);// zielony
    cout << tekstDoWyswietlenia << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);// bia³y
    Sleep(1900);
}

void edytujDaneKontaktowe(vector<Kontakt> &kontakty, int iloscKontaktow, int id, int poleDoEdycji) {
    string nowaWartosc;
    for(int i = 0; i < iloscKontaktow; i++) {
        if(kontakty[i].id == id) {
            switch(poleDoEdycji) {
            case 1:
                cout << "Wprowadz imie: ";
                cin >> nowaWartosc;
                kontakty[i].imie = nowaWartosc;
                zapiszWszystkieKontaktyDoPliku(kontakty,iloscKontaktow);
                komunikatInformacyjny("Dane zostaly zmienione.");
                return;
            case 2:
                cout << "Wprowadz nazwisko: ";
                cin >> nowaWartosc;
                kontakty[i].nazwisko = nowaWartosc;
                zapiszWszystkieKontaktyDoPliku(kontakty,iloscKontaktow);
                komunikatInformacyjny("Dane zostaly zmienione.");
                return;
            case 3:
                cout << "Wprowadz telefon: ";
                cin >> nowaWartosc;
                kontakty[i].telefon = nowaWartosc;
                zapiszWszystkieKontaktyDoPliku(kontakty,iloscKontaktow);
                komunikatInformacyjny("Dane zostaly zmienione.");
                return;
            case 4:
                cout << "Wprowadz emial: ";
                cin >> nowaWartosc;
                kontakty[i].email = nowaWartosc;
                zapiszWszystkieKontaktyDoPliku(kontakty,iloscKontaktow);
                komunikatInformacyjny("Dane zostaly zmienione.");
                return;
            case 5:
                cout << "Wprowadz adres: ";
                cin.sync();
                getline(cin,kontakty[i].adres);
                zapiszWszystkieKontaktyDoPliku(kontakty,iloscKontaktow);
                komunikatInformacyjny("Dane zostaly zmienione.");
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
                zapiszWszystkieKontaktyDoPliku(kontakty,iloscKontaktow);
                komunikatInformacyjny("Dane zostaly zmienione.");
                return;
            }
        }
    }
    komunikatInformacyjny("Kontakt o takim ID nie istnieje. W celu sprawdzenia ID wyszukaj lub wyswietl wszystkie kontakty");
}

int kasowanieKontaktu(vector<Kontakt> &kontakty, int iloscKontaktow, int id) {
    bool czyPodanoPoprawneID = false;
    char wybor;
    vector<Kontakt>::iterator koniec = kontakty.end();
    for(vector<Kontakt>::iterator itr = kontakty.begin();
            itr != koniec; ++itr) {
        if((*itr).id == id) {
            wyszukiwanieID(kontakty, (*itr).id, iloscKontaktow );
            cout << endl << "Czy napewno chcesz usunc wybrany kontakt?(T - tak, N - nie): ";
            cin >> wybor;
            if(wybor  == 't' || wybor  == 'T') {
                kontakty.erase(itr);
                iloscKontaktow--;
                komunikatInformacyjny("Kontakt zostal usuniety.");
            }
            czyPodanoPoprawneID = true;
            break;
        }
    }
    if(!czyPodanoPoprawneID) komunikatInformacyjny("Kontakt o takim ID nie istnieje");
    zapiszWszystkieKontaktyDoPliku(kontakty, iloscKontaktow);
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
            cout << "Taki uzytkownik istnieje. Wpis inna nazwe uzytkownika: ";
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
    plikUzytkownicy.open("Uzytkownicy.txt", ios::out | ios::app);
    if(plikUzytkownicy.good() == false) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); //czerwony
        cout << "Wystapil problem przy probie zapisu danych do pliku." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
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
    remove("Uzytkownicy.txt");
    fstream plikUzytkownicy;
    plikUzytkownicy.open("Uzytkownicy.txt", ios::out | ios::app);
    if(plikUzytkownicy.good() == false) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); //czerwony
        cout << "Wystapil problem przy probie zapisu danych do pliku." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
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

    plikUzytkownicy.open("Uzytkownicy.txt",ios::in);
    if(plikUzytkownicy.good() == false) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); //czerwony
        cout << "Wystapil problem z odczytem kontaktow z plikUzytkownicyu." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
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

int main() {
    vector<Kontakt> kontakty;

    int iloscKontaktow = wczytajKontaktyZPliku(kontakty);

    char wybor;
    int id;

    vector<Uzytkownik> uzytkownicy;
    int idzalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = wczytywanieUzytkownikow(uzytkownicy);

    string szukanaWartosc;

    while(true) {
        if(idzalogowanegoUzytkownika == 0) {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
            cout << "KSIAZKA ADRESOWA v0.3" << endl;
            cout << "---------------------------" << endl;
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
                idzalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
            } else if(wybor == '9') {
                exit(0);
            }
        } else {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
            cout << "KSIAZKA ADRESOWA v0.3" << endl;
            cout << "---------------------------" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
            cout << "Ilosc zapisanych kontaktow: "<< iloscKontaktow << endl << endl;
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
                iloscKontaktow = zapisywanieKontaktu(kontakty, iloscKontaktow);
                break;
            case '2':
                system("cls");
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
                system("cls");
                if (wybor == '9') break;
                cout << "EDYCJA:" << endl;
                cout << "Podaj ID kontaktu ktory chcesz edytowac: ";
                cin >> id;
                edytujDaneKontaktowe(kontakty, iloscKontaktow,id, wybor - 48);
                break;
            case '3':
                system("cls");
                cout << "Usuwanie:" << endl;
                cout << "Podaj ID kontaktu ktory chcesz usunac: " << endl;
                cin >> id;
                system("cls");
                iloscKontaktow = kasowanieKontaktu(kontakty, iloscKontaktow, id);
                break;
            case '4':
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
            case '8': {
                system("cls");
                cout << "1. Zmiana hasla" << endl;
                cout << "2. Wylogowywanie" << endl;
                cout << "9. Menu glowne" << endl;
                cin >> wybor;
                if(wybor == '1') {
                    zmianaHasla(uzytkownicy, iloscUzytkownikow, idzalogowanegoUzytkownika);
                } else if(wybor == '2') {
                    idzalogowanegoUzytkownika = 0;
                } else if(wybor == '9') {
                    break;
                }
            }
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
}
