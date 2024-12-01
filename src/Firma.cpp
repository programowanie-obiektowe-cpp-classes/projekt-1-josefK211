#include "Firma.hpp"
#include "Config.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>

std::random_device              rd;
std::mt19937                    gen(rd());
std::uniform_int_distribution<> dist_numer(1, 99);


Firma::Firma() : m_stan_konta(5000.0)
{
    zatrudnij(std::make_unique< Inz >(losuj_imie_inzyniera(), "MEiL"));
    zatrudnij(std::make_unique< Mag >(losuj_imie_magazyniera(), true));
    zatrudnij(std::make_unique< Mkt >(losuj_imie_marketingowca(), 100));
    zatrudnij(std::make_unique< Rob >(losuj_imie_robotnika(), 44.0));
}

std::string Firma::losuj_imie_inzyniera()
{
    std::vector< std::string > imiona = {
        "Andrzej", "Nierinz", "Prawie Inzynier", "Inzynier1", "Reinyzni", "Zyninier"};
    std::uniform_int_distribution<> dist(0, imiona.size() - 1);
    return imiona[dist(gen)];
}

std::string Firma::losuj_imie_robotnika()
{
    std::vector< std::string >      imiona = {"Waldziu", "Mietek", "Janusz", "Mlody", "Krzychu", "Piotras", "Mirek"};
    std::uniform_int_distribution<> dist(0, imiona.size() - 1);
    return imiona[dist(gen)];
}

std::string Firma::losuj_imie_magazyniera()
{
    int numer = dist_numer(gen); 
    return "Michal" + std::to_string(numer);
}

std::string Firma::losuj_imie_marketingowca()
{
    int numer = dist_numer(gen); 
    return "Robot" + std::to_string(numer);
}

void Firma::zatrudnij(std::unique_ptr< Pracownik > pracownik)
{
    m_pracownicy.push_back(std::move(pracownik));
}


void Firma::wez_kredyt(double kwota, int czas_splaty)
{
    if (czas_splaty > MAX_RATY)
    {
        std::cout << "Przekroczono limit splaty " << MAX_RATY << " miesiecy!\n";
        return;
    }
    if (kwota > wartosc_firmy() * MAX_ZADLUZENIE_WSP)
    {
        std::cout << "Nie mozna wziac kredytu wiekszego niz " << MAX_ZADLUZENIE_WSP << "x wartosc firmy!\n";
        return;
    }
    m_kredyty.emplace_back(kwota, czas_splaty);
    m_stan_konta += kwota;
}


void Firma::zaplac_wynagrodzenie()
{
    for (const auto& pracownik : m_pracownicy)
    {
        m_stan_konta -= pracownik->koszt();
    }
}


void Firma::splac_raty()
{
    for (auto it = m_kredyty.begin(); it != m_kredyty.end();)
    {
        m_stan_konta -= it->splac_rate();
        if (it->czy_splacony())
        {
            it = m_kredyty.erase(it);
        }
        else
        {
            ++it;
        }
    }
}


void Firma::drukuj_pracownikow() const
{
    for (const auto& pracownik : m_pracownicy)
    {
        pracownik->print();
    }
}


void Firma::symuluj_miesiac()
{ 
    int pojemnosc_magazynu = liczba_magazynierow() * CMag;

    int teoretyczna_produkcja = liczba_robotnikow() * CR;

    int faktyczna_produkcja = std::min(teoretyczna_produkcja, pojemnosc_magazynu);

    int popyt = liczba_marketerow() * CMkt;

    int sprzedaz = std::min(faktyczna_produkcja, popyt);

    double cena_produktu = liczba_inzynierow() * CI;

    double przychod = sprzedaz * cena_produktu;

    m_przychody.push_back(przychod);
    if (m_przychody.size() > N)
    {
        m_przychody.erase(m_przychody.begin());
    }

    m_stan_konta += przychod;

    std::cout << "Sprzedano " << sprzedaz << " produkty za " << std::fixed << std::setprecision(2) << przychod
              << " zl.\n";

    if (m_stan_konta < 0)
    {
        std::cout << "Firma zbankrutowala! Stan konta: " << std::fixed << std::setprecision(2) << m_stan_konta
                  << " zl.\n";
        exit(0); 
    }
}

double Firma::wartosc_firmy() const
{
    if (m_przychody.empty())
        return 0.0;
    double suma = 0.0;
    for (double przychod : m_przychody)
        suma += przychod;
    return suma / m_przychody.size();
}


void Firma::podsumuj() const
{
    std::cout << "Stan konta: " << std::fixed << std::setprecision(2) << m_stan_konta
              << ", Wartosc firmy: " << wartosc_firmy() << "\n";
}

int Firma::liczba_inzynierow() const
{
    return licz_pracownikow< Inz >();
}
int Firma::liczba_magazynierow() const
{
    return licz_pracownikow< Mag >();
}
int Firma::liczba_marketerow() const
{
    return licz_pracownikow< Mkt >();
}
int Firma::liczba_robotnikow() const
{
    return licz_pracownikow< Rob >();
}

template < typename T >
int Firma::licz_pracownikow() const
{
    return std::count_if(m_pracownicy.begin(), m_pracownicy.end(), [](const auto& pracownik) {
        return dynamic_cast< T* >(pracownik.get()) != nullptr;
    });
}
