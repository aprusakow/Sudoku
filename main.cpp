#include "Menu.h"
#include "Gracz.h"
#include "Log.h"
#include "Sudoku.h"
#include "Komputer.h"
#include "Solver.h"
#include <ctime> //srand
#include <iomanip> //setw
#include <iostream>
#include <conio.h> //_getch

using namespace std;

int main() {
    // Inicjalizacja menu oraz gracza
    Menu menu;
    bool i = true;
    int N, K;
    // Solver* solver = nullptr;
    srand((unsigned)time(NULL)); // Inicjalizacja generatora liczb pseudolosowych
    cout << "========================================\n";
    cout << setw(28) << "A. Prusakow, Sudoku";
    cout << "\n========================================\n\n";
    cout << setw(28) << "P O D A J  S W O J  N I C K: ";
    string nick;
    cin >> nick;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuniêcie ewentualnych pozosta³oœci z bufora
    Gracz gracz(nick);
    Log log(gracz);
    system("cls");

    // Pêtla g³ówna programu
    while (i) {
        menu.printmenu(); // Wyœwietlenie menu
        int wyborMenu;
        while (true) {
            cin >> wyborMenu;
            if (cin.fail() || (wyborMenu < 1 || wyborMenu > 3)) {
                cout << "Niepoprawny wybor. Wprowadz liczbe od 1 do 3: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuniêcie ewentualnych pozosta³oœci z bufora
                break;
            }
        }

        switch (wyborMenu) {
        case 1: // Wyœwietlenie zasad
            menu.printinfo();
            break;
        case 2: // Rozpoczêcie gry
        {
            system("cls");
            cout << "=================================================================\n";
            cout << nick << ", W Y B I E R Z  P O Z I O M  T R U D N O S C I:\n";
            cout << "1. l a t w y\n";
            cout << "2. s r e d n i\n";
            cout << "3. t r u d n y\n";
            cout << "=================================================================\n";
            cout << "\n\nT W O J  W Y B O R : ";
            int poziomTrudnosci;
            while (true) {
                cin >> poziomTrudnosci;
                if (cin.fail() || (poziomTrudnosci < 1 || poziomTrudnosci > 3)) {
                    cout << "Niepoprawny wybor. Wprowadz liczbe od 1 do 3: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuniêcie ewentualnych pozosta³oœci z bufora
                    break;
                }
            }

            system("CLS");
            cout << "=================================================================\n";
            cout << nick << ", W Y B I E R Z  W Y M I A R  P L A N S Z Y: \n";
            cout << "=================================================================\n";
            cout << "\n\n1. 4 x 4\n";
            cout << "\n2. 9 x 9\n";
            cout << "\n3. 16 x 16\n";
            cout << "\n\nT W O J  W Y B O R : ";
            int wym;
            while (true) {
                cin >> wym;
                if (cin.fail() || (wym < 1 || wym > 3)) {
                    cout << "Niepoprawny wybor. Wprowadz liczbe od 1 do 3: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuniêcie ewentualnych pozosta³oœci z bufora
                    break;
                }
            }

            switch (wym) {
            case 1:
                N = 4;
                break;
            case 2:
                N = 9;
                break;
            case 3:
                N = 16;
                break;
            }

            switch (poziomTrudnosci) {
            case 1: // £atwy
                K = floor(0.3 * N * N);
                break;
            case 2:  // Œredni
                K = floor(0.4 * N * N);
                break;
            case 3:  // Trudny
                K = floor(0.5 * N * N);
                break;
            }
            system("cls");
            cout << "=================================================================\n";
            cout << nick << ", W Y B I E R Z  R O D Z A J  G R Y: \n";
            cout << "=================================================================\n";
            cout << "\n\n1. g r a  s a m o d z i e l n a\n";
            cout << "\n2. k o m p u t e r\n";
            cout << "\n\nT W O J  W Y B O R : ";
            int rodzaj;
            while (true) {
                cin >> rodzaj;
                if (cin.fail() || (rodzaj < 1 || rodzaj > 2)) {
                    cout << "Niepoprawny wybor. Wprowadz liczbe od 1 do 2: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuniêcie ewentualnych pozosta³oœci z bufora
                    break;
                }
            }
            Sudoku* sudoku = new Sudoku(N, K);
            system("CLS");
            sudoku->wypelnij();
            sudoku->usunKCyfr();
            switch (rodzaj) {
            case 1:
                sudoku->drukujSudoku();
                sudoku->graj(gracz, poziomTrudnosci, rodzaj);
                break;
            case 2:
                log.rozpocznijGre(std::to_string(N) + "x" + std::to_string(N), std::to_string(poziomTrudnosci), (rodzaj == 1 ? "gracz" : "komputer"));
                Komputer* solver = new Komputer(*sudoku);
                if (solver->rozwiaz()) {
                    sudoku->drukujSudoku();
                    cout << "\nUdalo sie rozwiazac sudoku!";
                    log.komputer(true, solver->getZycia());
                    cout << "\n\nKliknij dowolny przycisk aby wrocic do menu...";
                    char znak = _getch();
                    if (znak) {
                        system("CLS");
                        break;
                    }
                }
                else {
                    log.komputer(false, solver->getZycia());
                    cout << "Nie udalo sie rozwiazac sudoku :(\n";
                    cout << "\n\nKliknij dowolny przycisk aby wrocic do menu...";
                    char znak = _getch();
                    if (znak) {
                        system("CLS");
                        break;
                    }
                }
                delete solver;
                break;
            }
            break;
        }
        case 3:
            cout << "Zegnaj " << nick << "... Opuszczanie gry..." << endl;
            log.zakonczProgram();
            i = false;
            break;
        default:
            cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
            break;
        }
    }
    return 0;
}
