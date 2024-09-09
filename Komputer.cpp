#include "Komputer.h"
#include <cmath>
#include <Windows.h>
#include <iostream>
Komputer::Komputer(Sudoku& sudoku) : sudoku(sudoku), zycia(5) {} // konstruktor kopiujacy

bool Komputer::rozwiaz() {
	int N = sudoku.getRozmiar();
	int** plansza = sudoku.getPlansza();
	return rozwiazSudoku(plansza, N);
}

int Komputer::getZycia() const { return zycia; } // getter dla zycia

bool Komputer::rozwiazSudoku(int** plansza, int N) {
	int wiersz, kolumna;
	static bool czyWyswietlonoKomunikat = false;
	if (zycia <= 0) {
		this->zycia = 0;
		if (!czyWyswietlonoKomunikat) {
			std::cout << "Komputer stracil wszystkie zycia.\n";
			czyWyswietlonoKomunikat = true;
		}
		return false; // Komputer stracil wszystkie zycia
	}

	if (!znajdzPustaKomorke(plansza, N, wiersz, kolumna)) {
		return true; // 0 pustych komorek oznacza ze sudoku jest rozwiazane
	}

	for (int num = 1; num <= N; num++) {
		if (czyBezpieczne(plansza, N, wiersz, kolumna, num)) {
			plansza[wiersz][kolumna] = num;
			sudoku.drukujSudoku(); // wyswietlanie
			std::cout << "Z Y C I A  K O M P U T E R A: " << zycia << ".\n";
			Sleep(100);
			system("cls");

			if (rozwiazSudoku(plansza, N)) {
				return true;
			}
			plansza[wiersz][kolumna] = 0; // Backtracking
			zycia--; // zmniejszenie liczby zyc
			if (zycia <= 0) {
				this->zycia = 0;
				if (!czyWyswietlonoKomunikat) {
					std::cout << "Komputer stracil wszystkie zycia.\n";
					czyWyswietlonoKomunikat = true;
				}
				return false; // Komputer stracil wszystkie zycia
			}

			sudoku.drukujSudoku(); // wyswietlanie
			std::cout << "Z Y C I A  K O M P U T E R A: " << zycia << ".\n";
			Sleep(100);
			system("cls");
		}
	}

	return false; // Triggeruje backtracking
}

bool Komputer::znajdzPustaKomorke(int** plansza, int N, int& wiersz, int& kolumna) {
	for (wiersz = 0; wiersz < N; wiersz++) {
		for (kolumna = 0; kolumna < N; kolumna++) {
			if (plansza[wiersz][kolumna] == 0) {
				return true;
			}
		}
	}
	return false;
}

bool Komputer::czyBezpieczne(int** plansza, int N, int wiersz, int kolumna, int num) {
	// sprawdz wiersz
	for (int x = 0; x < N; x++) {
		if (plansza[wiersz][x] == num) {
			return false;
		}
	}

	// sprawdz kolumna
	for (int x = 0; x < N; x++) {
		if (plansza[x][kolumna] == num) {
			return false;
		}
	}

	// sprawdz kwadrat
	int sqrtN = (int)sqrt(N);
	int startWierszWKwadracie = wiersz - wiersz % sqrtN;
	int startKolWKwadracie = kolumna - kolumna % sqrtN;

	for (int r = 0; r < sqrtN; r++) {
		for (int d = 0; d < sqrtN; d++) {
			if (plansza[r + startWierszWKwadracie][d + startKolWKwadracie] == num) {
				return false;
			}
		}
	}

	return true;
}