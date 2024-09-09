#ifndef SUDOKU_H
#define SUDOKU_H
#include "Gracz.h"
class Sudoku {
private:
	int** plansza;
	int N;
	int SRN;
	int K;
	int** k_indeksy;
	int zycia;
public:
	int getZycia() const;
	Sudoku(int N, int K);
	~Sudoku();
	int getRozmiar() const;
	int** getPlansza();
	bool czyUkonczone();
	void graj(Gracz gracz, int poziomTrudnosci, int tryb);
	void wypelnij();
	void wypelnijDiagonale();
	bool czyWRzedzie(int rowStart, int num);
	bool czyWKwadracie(int rowStart, int colStart, int num);
	bool czyWKol(int colStart, int num);
	int randomGenerator(int n);
	void wypelnijKwadrat(int row, int col);
	bool wypelnijReszte(int i, int j);
	bool czyBezpieczne(int i, int j, int liczba);
	void usunKCyfr();
	bool czyKomorkaWygenerowanaPrzezKomputer(int i, int j);
	void drukujSudoku();
};

#endif

