// Solver.h
#ifndef SOLVER_H
#define SOLVER_H

class Solver {
public:
    virtual bool rozwiaz() = 0;// W przypadku rozwi�zywania Sudoku, Solver mo�e zawiera� interfejs (cz�sto w postaci wirtualnej metody), 
    ~Solver() = default;//kt�ry wymusza implementacj� metody solve() przez klasy dziedzicz�ce, takie jak Komputer.
};

#endif
