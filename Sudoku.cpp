#include "Kolor.h"
#include "Sudoku.h"
#include "Log.h"
#include "Gracz.h"
#include <iostream>
#include <cmath>//pierwiastki
#include <iomanip>//setw
#include <limits>//czyszczenie bufora
#include <cstdlib>//rand()
#include <string>
#include <conio.h>//_getch()
#include <windows.h>//Kolor, system("cls")
#define NOMINMAX

using namespace std;


// Konstruktor
Sudoku::Sudoku(int N, int K)
{
    this->N = N; // Ustawienie wymiaru Sudoku
    this->K = K; // Ustawienie liczby pustych p�l
    double SRNd = sqrt(N); // Pierwiastek z N - rozmiar podkwadrat�w
    SRN = (int)SRNd; // Konwersja do typu int
    plansza = new int* [N];
    k_indeksy = new int* [N];
    this->zycia = 5;
    // Inicjalizacja planszy i k_indeksy
    for (int i = 0; i < N; i++)
    {
        plansza[i] = new int[N];
        k_indeksy[i] = new int[N];
        memset(plansza[i], -1, N * sizeof(int)); // Wype�nienie planszy -1
        memset(k_indeksy[i], 0, N * sizeof(int)); // Wype�nienie k_indeksy 0
    }
}

// Destruktor
Sudoku::~Sudoku() {
    // Zwolnienie pami�ci przy u�yciu delete[]
    for (int i = 0; i < N; i++) {
        delete[] plansza[i];
        delete[] k_indeksy[i];
    }
    delete[] plansza;
    delete[] k_indeksy;

}

// Getter
int Sudoku::getZycia() const {
    return zycia;
}
// Getter
int Sudoku::getRozmiar() const {
    return N;
}
// Getter
int** Sudoku::getPlansza() {
    return plansza;
}
// Metoda wype�niaj�ca Sudoku
void Sudoku::wypelnij()
{
    wypelnijDiagonale();
    wypelnijReszte(0, SRN);
    // Sprawdzenie, czy Sudoku jest wype�nione; je�li nie, pr�ba ponownego wype�nienia
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (plansza[i][j] == -1) {
                // Je�li plansza nie jest wype�niona, wyczyszczenie planszy i ponowne wype�nienie
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        plansza[i][j] = -1;
                    }
                }
                wypelnij();
            }
        }
    }
}

// Metoda wype�niaj�ca diagonale
void Sudoku::wypelnijDiagonale()
{
    for (int i = 0; i < N; i = i + SRN)
    {
        wypelnijKwadrat(i, i);
    }
}

// Metoda sprawdzaj�ca, czy dana liczba jest ju� w danym kwadracie
bool Sudoku::czyWKwadracie(int rowStart, int colStart, int num)
{
    for (int i = 0; i < SRN; i++) {
        for (int j = 0; j < SRN; j++) {
            if (plansza[rowStart + i][colStart + j] == num) {
                return false;
            }
        }
    }
    return true;
}

// Metoda wype�niaj�ca kwadrat
void Sudoku::wypelnijKwadrat(int row, int col)
{
    int num;
    for (int i = 0; i < SRN; i++) {
        for (int j = 0; j < SRN; j++) {
            do {
                num = randomGenerator(N);
            } while (!czyWKwadracie(row, col, num));
            plansza[row + i][col + j] = num;
        }
    }
}

// Generator losowych liczb
int Sudoku::randomGenerator(int num)
{
    return floor((rand() % num) + 1);
}

// Metoda sprawdzaj�ca, czy wprowadzenie danej liczby jest bezpieczne w danym miejscu
bool Sudoku::czyBezpieczne(int i, int j, int num) {
    return (czyWRzedzie(i, num) && czyWKol(j, num) && czyWKwadracie(i - i % SRN, j - j % SRN, num));
}

// Metoda sprawdzaj�ca, czy dana liczba wyst�puje w danym wierszu
bool Sudoku::czyWRzedzie(int i, int num)
{
    for (int j = 0; j < N; j++) {
        if (plansza[i][j] == num) {
            return false;
        }
    }
    return true;
}

// Metoda sprawdzaj�ca, czy dana liczba wyst�puje w danej kolumnie
bool Sudoku::czyWKol(int j, int num)
{
    for (int i = 0; i < N; i++) {
        if (plansza[i][j] == num) {
            return false;
        }
    }
    return true;
}

// Metoda rekurencyjnie wype�niaj�ca reszt� planszy
bool Sudoku::wypelnijReszte(int i, int j) {
    if (j >= N && i < N - 1) {
        i++;
        j = 0;
    }
    if (i >= N && j >= N) {
        return true;
    }
    if (i < SRN) {
        if (j < SRN) {
            j = SRN;
        }
    }
    else if (i < N - SRN) {
        if (j == (i / SRN) * SRN) {
            j += SRN;
        }
    }
    else {
        if (j == N - SRN) {
            i++;
            j = 0;
            if (i >= N) {
                return true;
            }
        }
    }
    for (int num = 1; num <= N; num++) {
        if (czyBezpieczne(i, j, num)) {
            plansza[i][j] = num;
            if (wypelnijReszte(i, j + 1)) {
                return true;
            }
            plansza[i][j] = -1;
        }
    }
    return false;
}

// Metoda usuwaj�ca losowo cyfry z planszy
void Sudoku::usunKCyfr()
{
    int count = K;
    while (count != 0) {
        int cellId = randomGenerator(N * N) - 1;
        int i = (cellId / N);
        int j = cellId % N;
        if (plansza[i][j] == 0) continue;
        else {
            count--;
            plansza[i][j] = 0;
            k_indeksy[i][j] = 1;
        }
    }
}

// Metoda sprawdzaj�ca, czy Sudoku zosta�o uko�czone
bool Sudoku::czyUkonczone() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (plansza[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

// Metoda sprawdzaj�ca, czy kom�rka zosta�a wygenerowana przez komputer
bool Sudoku::czyKomorkaWygenerowanaPrzezKomputer(int wiersz, int kolumna) {
    if (k_indeksy[wiersz][kolumna] == 1) {
        return false;
    }
    else {
        return true;
    }
}

// Metoda rozpoczynaj�ca gr�
void Sudoku::graj(Gracz gracz, int poziomTrudnosci, int tryb) {
    Log log(gracz);
    log.rozpocznijGre(std::to_string(N) + "x" + std::to_string(N), std::to_string(poziomTrudnosci), (tryb == 1 ? "gracz" : "komputer"));

    bool grajPonownie = true;
    while (grajPonownie) {
        while (!czyUkonczone()) {
            if (zycia == 0) {
                system("cls");
                cout << "S K O N C Z Y L Y  C I E  Z Y C I A, K O N I E C  G R Y. :(\n";
                cout << "\nKliknij dowolny przycisk aby wrocic do menu.\n";
                log.zakonczGre(false, zycia);
                char znak = _getch();
                if (znak) {
                    system("CLS");
                    return;
                }
            }
            char wiersz;
            int kolumna, liczba;
            int indeksWiersza;
            char pom = 'A' + N - 1;
            string x;
            string input;
            cout << "T W O J E  Z Y C I A: " << zycia << endl << endl;
            std::cout << std::endl << "P O D A J  W S P O L R Z E D N E\n(j e s l i  c h c e s z  s i e  p o d d a c - k l i k n i j  X)\n\nl i t e r a (A-" << pom << "):\n";
            std::cin >> input;
            bool validInput = false;
            if (input[0] == 'X') {
                system("cls");
                drukujSudoku();
                while (!validInput) {
                    cout << "C Z Y  N A  P E W N O  C H C E S Z  S I E  P O D D A C? (t - t a k, n - n i e):\n";
                    cin >> x;
                    if (x.length() == 1 && (x[0] == 't' || x[0] == 'n')) {
                        validInput = true;
                        log.poddajSie(zycia);
                        if (x[0] == 't') {
                            system("cls");
                            drukujSudoku();
                            cout << "\n\nKliknij dowolny przycisk aby wrocic do menu...";
                            char znak = _getch();
                            if (znak) {
                                system("CLS");
                                return;
                            }
                        }
                        else {
                            system("cls");
                            drukujSudoku();
                            continue;
                        }
                    }
                    else {
                        system("cls");
                        drukujSudoku();
                        std::cout << "Nieprawidlowa litera. Podaj pojedyncza litere t lub n.\n" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                continue;
            }
            else if (cin.fail() || input.length() != 1 || input[0] < 'A' || input[0] > pom) {
                system("cls");
                std::cout << "Nieprawidlowa litera. Podaj pojedyncza litere A-" << pom << ".\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                drukujSudoku();
                continue;
            }

            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuni�cie ewentualnych pozosta�o�ci z bufora
            }

            wiersz = input[0];
            std::cout << "c y f r a (1-" << N << "): ";
            std::cin >> kolumna;

            if (cin.fail() || kolumna < 1 || kolumna > N) {
                system("cls");
                std::cout << "Nieprawidlowa cyfra. Podaj cyfre od 1 do " << N << ".\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                drukujSudoku();
                continue;
            }

            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuni�cie ewentualnych pozosta�o�ci z bufora
            }

            std::cout << "t w o j a  o d p o w i e d z: ";
            std::cin >> liczba;

            if (cin.fail() || liczba < 1 || liczba > N) {
                system("cls");
                std::cout << "Nieprawidlowa liczba. Podaj liczbe od 1 do " << N << ".\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                drukujSudoku();
                continue;
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuni�cie ewentualnych pozosta�o�ci z bufora
            }

            indeksWiersza = wiersz - 'A';
            kolumna--;

            if (!czyBezpieczne(indeksWiersza, kolumna, liczba)) {
                zycia--;
                system("cls");
                std::cout << "Ta cyfra juz istnieje w rzedzie, kolumnie lub bloku. Sprobuj ponownie.\n" << std::endl;
                log.zapiszOdpowiedz(std::to_string(liczba), wiersz, kolumna + 1, false, zycia);
                drukujSudoku();
            }
            else if (czyKomorkaWygenerowanaPrzezKomputer(indeksWiersza, kolumna)) {
                zycia--;
                system("cls");
                cout << "Ta cyfra zostala wygenerowana przez komputer. Nie mozna zmieniac tych wartosci. Sprobuj ponownie.\n" << endl;
                log.zapiszOdpowiedz(std::to_string(liczba), wiersz, kolumna + 1, false, zycia);
                drukujSudoku();
            }
            else if (czyBezpieczne(indeksWiersza, kolumna, liczba)) {
                plansza[indeksWiersza][kolumna] = liczba;
                log.zapiszOdpowiedz(std::to_string(liczba), wiersz, kolumna + 1, true, zycia);
                system("cls");
                drukujSudoku();
            }
        }
        if (czyUkonczone()) {
            system("cls");
            drukujSudoku();
            std::cout << "Gratulacje! Udalo Ci sie ukonczyc Sudoku!\n" << std::endl;
            log.zakonczGre(true, zycia);

            cout << "\nKliknij dowolny przycisk aby wrocic do menu.\n";
            char znak = _getch();
            if (znak) {
                system("CLS");
                return;
            }
        }
    }
}

// Metoda drukuj�ca Sudoku
void Sudoku::drukujSudoku()
{
    int dl = 3 * N; // Ilo�� kresek -
    char lit = 'A';
    int num = 1;
    cout << "    ";
    for (num; num <= N; num++) {
        cout << setw(3) << num;
        if (num % (int)sqrt(N) == 0) {
            cout << setw(3) << " ";
            dl += 3;
        }
    }
    cout << endl;
    cout << setw(4) << " " << setfill('-') << setw(dl) << " ";
    cout << setfill(' ');
    cout << endl;

    // Drukowanie planszy
    for (int i = 0; i < N; i++) {
        cout << lit << setw(3) << "|";
        for (int j = 0; j < N; j++) {
            if (plansza[i][j] == 0) {
                cout << setw(3) << " ";
            }
            else {
                // Sprawd�, czy warto�� jest wygenerowana przez komputer
                if (czyKomorkaWygenerowanaPrzezKomputer(i, j)) {
                    // Ustaw kolor dla warto�ci wygenerowanych przez komputer
                    cout << setw(3) << Kolor(13) << plansza[i][j] << Kolor(7); // np. czerwony kolor
                }
                else {
                    // Ustaw domy�lny kolor dla pozosta�ych warto�ci
                    cout << setw(3) << Kolor(10) << plansza[i][j] << Kolor(7);
                }
            }
            if ((j + 1) % (int)sqrt(N) == 0 || j == N + 1) {
                cout << setw(3) << "|";
            }
        }
        ++lit;
        if ((i + 1) % (int)sqrt(N) == 0 || i == N - 1) {
            cout << endl;
            cout << setw(4) << " " << setfill('-') << setw(dl) << " ";
            cout << setfill(' ');
            cout << endl;
        }
        else
            cout << endl << endl;
    }
    cout << endl;

}
