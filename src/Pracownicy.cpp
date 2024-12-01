#include "Pracownicy.hpp"
#include <iostream>
#include <iomanip>

Pracownik::Pracownik(std::string imie) : m_imie(std::move(imie))
{}

Inz::Inz(std::string imie, std::string wydzial) : Pracownik(std::move(imie)), m_wydzial(std::move(wydzial))
{}

void Inz::print() const
{
    std::cout << "Inzynier: " << m_imie << ", Wydzial: " << m_wydzial << "\n";
}

double Inz::koszt() const
{
    return 1500.0;
}

Mag::Mag(std::string imie, bool obsl_widl) : Pracownik(std::move(imie)), m_obsl_widl(obsl_widl)
{}

void Mag::print() const
{
    std::cout << "Magazynier: " << m_imie << ", Obs. Widlaka: " << (m_obsl_widl ? "Tak" : "Nie") << "\n";
}

double Mag::koszt() const
{
    return 1000.0;
}

Mkt::Mkt(std::string imie, int follows) : Pracownik(std::move(imie)), m_follows(follows)
{}

void Mkt::print() const
{
    std::cout << "Marketer: " << m_imie << ", Follows: " << m_follows << "\n";
}

double Mkt::koszt() const
{
    return 1000.0;
}

Rob::Rob(std::string imie, double but) : Pracownik(std::move(imie)), m_but(but)
{}

void Rob::print() const
{
    std::cout << "Robotnik: " << m_imie << ", Rozmiar buta: " << std::fixed << std::setprecision(1) << m_but << "\n";
}

double Rob::koszt() const
{
    return 1100.0;
}
