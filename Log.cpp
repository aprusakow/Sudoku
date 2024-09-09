#include "Log.h"
#include <iostream>
#include <sstream>//data i godzina
#include <chrono>//data i godzina
#include <iomanip>//data i godzina
#define _CRT_SECURE_NO_WARNINGS

Log::Log(Gracz& gracz) {
    this->nick = gracz.pobierzNick();
    std::string nazwaPliku = nick + ".txt";
    plik.open(nazwaPliku, std::ios::app);
    if (!plik.is_open()) {
        std::cerr << "Nie mo�na otworzy� pliku logu!" << std::endl;
    }
}

Log::~Log() {
    if (plik.is_open()) {
        plik.close();
    }
}

std::string Log::pobierzCzas() {
    auto teraz = std::chrono::system_clock::now();
    std::time_t czas = std::chrono::system_clock::to_time_t(teraz);
    std::tm tm;
    localtime_s(&tm, &czas);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y, %H:%M:%S");
    return oss.str();
}


void Log::rozpocznijGre(const std::string& wymiar, const std::string& poziomTrudnosci, const std::string& tryb) {
    plik << pobierzCzas() << ", gracz (" << nick << ") rozpocz�� gr� - wybrany wymiar: " << wymiar << ", poziom trudno�ci: " << poziomTrudnosci << ", tryb: " << tryb << std::endl;
}

void Log::zapiszOdpowiedz(const std::string& odpowiedz, char wsp1, int wsp2, bool poprawna, int zycia) {
    plik << pobierzCzas() << ", gracz (" << nick << ") wprowadzi� " << (poprawna ? "poprawn�" : "niepoprawn�") << " odpowied� (" << odpowiedz << ") w pole (" << wsp1 << wsp2 << ")" << ((zycia == 1 || zycia == 5 || zycia == 0) ? ". Zosta�o mu " : ". Zosta�y mu ") << zycia << ((zycia == 5 || zycia == 0) ? " �y�." : (zycia == 1 ? " �ycie." : " �ycia.")) << std::endl;
}

void Log::poddajSie(int zycia) {
    plik << pobierzCzas() << ", gracz (" << nick << ") podda� si�." << ((zycia == 1 || zycia == 5 || zycia == 0) ? " Zosta�o mu " : " Zosta�y mu ") << zycia << ((zycia == 5 || zycia == 0) ? " �y�." : (zycia == 1 ? " �ycie." : " �ycia.")) << std::endl;
}


void Log::komputer(bool czySkonczyl, int zycia) {
    plik << pobierzCzas() << ", komputer skonczyl rozwiazywac sudoku. " << (czySkonczyl ? "Wygra�." : "Przegra�.") << ((zycia == 1 || zycia == 5 || zycia == 0) ? " Zosta�o mu " : " Zosta�y mu ") << zycia << ((zycia == 5 || zycia == 0) ? " �y�." : (zycia == 1 ? " �ycie." : " �ycia.")) << std::endl;
}


void Log::zakonczGre(bool czySkonczyl, int zycia) {
    plik << pobierzCzas() << ", gracz (" << nick << ") zako�czy� gr�, " << (czySkonczyl ? "wygra�." : "przegra�.") << ((zycia == 1 || zycia == 5 || zycia == 0) ? " Zosta�o mu " : " Zosta�y mu ") << zycia << ((zycia == 5 || zycia == 0) ? " �y�." : (zycia == 1 ? " �ycie." : " �ycia.")) << std::endl;
}

void Log::zakonczProgram() {
    plik << pobierzCzas() << ", gracz (" << nick << ") zako�czy� program." << std::endl;
}