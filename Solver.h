// Solver.h
#ifndef SOLVER_H
#define SOLVER_H

class Solver {
public:
    virtual bool rozwiaz() = 0;// W przypadku rozwi¹zywania Sudoku, Solver mo¿e zawieraæ interfejs (czêsto w postaci wirtualnej metody), 
    ~Solver() = default;//który wymusza implementacjê metody solve() przez klasy dziedzicz¹ce, takie jak Komputer.
};

#endif
