
#ifndef LOG_H
#define LOG_H
#include "Gracz.h"
#include <string>
#include <fstream>

class Log : Gracz {
public:
    Log(Gracz& gracz);
    ~Log();
    void komputer(bool czySkonczyl, int zycia);
    void rozpocznijGre(const std::string& wymiar, const std::string& poziomTrudnosci, const std::string& tryb);
    void zapiszOdpowiedz(const std::string& odpowiedz, char wsp1, int wsp2, bool poprawna, int zycia);
    void poddajSie(int zycia);
    void zakonczGre(bool czySkonczyl, int zycia);
    void zakonczProgram();
private:
    std::string nick;
    std::ofstream plik;
    std::string pobierzCzas();
};

#endif // LOG_H
