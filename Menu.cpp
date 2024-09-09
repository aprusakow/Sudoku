#include "Sudoku.h"
#include "Menu.h"
#include "Log.h"
#include "Gracz.h"
#include <iostream>
#include <iomanip> //setw
#include <cstdlib> //system("cls")
#include <cmath> //pierwiastki
#include <conio.h> //_getch()

using namespace std;



void Menu::printinfo() {
    system("cls");
    cout << "========================================\n";
    cout << setw(30) << "Z A S A D Y  G R Y: \n";
    cout << "========================================\n";

    cout << "Sudoku sklada sie z siatki NxN pol (do wyboru przez gracza - 4x4, 9x9, 16x16).\n";
    cout << "Uzyj tylko cyfr od 1 do N.\n";
    cout << "Kazdy blok NxN moze zawierac tylko cyfry od 1 do N.\n";
    cout << "Kazda pionowa kolumna moze zawierac tylko cyfry od 1 do N.\n";
    cout << "Kazdy poziomy wiersz moze zawierac tylko cyfry od 1 do N.\n";
    cout << "Kazda cyfra w bloku sqrt(N)xsqrt(N), pionowej kolumnie lub poziomym wierszu moze byc uzyta tylko raz.\n";
    cout << "Gra konczy sie, gdy caly diagram Sudoku jest poprawnie wypelniony cyframi.\n";
    cout << "Masz 5 zyc. Jesli stracisz je wszystkie gra sie konczy. Zycie mozna stracic przez wpisanie zlej cyfry,\n";
    cout << "lub przez probe wpisania cyfry w pole, ktore zostalo juz wygenerowane przez komputer.\n";
    cout << "Sa trzy poziomy trudnosci:\n";
    cout << "1. latwy(30 % planszy zakryte),\n2. sredni(40 % planszy zakryte),\n3. trudny(50 % planszy zakryte).\nMozesz rowniez wybrac opcje gry komputera.\n";
    cout << "========================================\n";
    cout << setw(30) << "M I L E J  G R Y! \n";
    cout << "========================================\n";
    cout << "\n\n\nKliknij dowolny przycisk aby wrocic do menu.\n";
    char znak = _getch();
    if (znak) {
        system("CLS");
        return;
    }
}

void Menu::printmenu() {
    cout << "========================================\n";
    cout << setw(24) << "Witaj!";
    cout << "\n========================================\n\n";
    cout << setw(27) << "M  E  N  U\n";
    cout << "\n========================================\n\n";
    cout << "1. i n s t r u k c j a\n";
    cout << "2. z a g r a j\n";
    cout << "3. w y j d z\n";
    cout << "\n\nT W O J  W Y B O R : ";
}

