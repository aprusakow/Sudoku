// Komputer.h
#ifndef KOMPUTER_H
#define KOMPUTER_H

#include "Solver.h"
#include "Sudoku.h"

class Komputer : public Solver {
private:
    Sudoku& sudoku;
    int zycia;
    bool rozwiazSudoku(int** board, int N);
    bool znajdzPustaKomorke(int** board, int N, int& row, int& col);
    bool czyBezpieczne(int** board, int N, int row, int col, int num);
public:
    Komputer(Sudoku& sudoku);//konstruktor
    bool rozwiaz() override;//z Solver
    int getZycia() const;
};

#endif
