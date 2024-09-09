#include "Gracz.h"
#include "Sudoku.h"

Gracz::Gracz(const std::string& nick) : nick(nick) {}
Gracz::Gracz() {}
const std::string& Gracz::pobierzNick() const { return nick; }
