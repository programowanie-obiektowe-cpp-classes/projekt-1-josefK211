#ifndef FIRMA_HPP
#define FIRMA_HPP

#include "Kredyt.hpp"
#include "Pracownicy.hpp"
#include <memory>
#include <vector>

class Firma
{
public:
    Firma();
    void   zatrudnij(std::unique_ptr< Pracownik > pracownik);
    void   wez_kredyt(double kwota, int czas_splaty);
    void   zaplac_wynagrodzenie();
    void   splac_raty();
    void   drukuj_pracownikow() const;
    void   symuluj_miesiac();
    double wartosc_firmy() const;
    void   podsumuj() const;

    std::string losuj_imie_inzyniera();
    std::string losuj_imie_robotnika();
    std::string losuj_imie_magazyniera();
    std::string losuj_imie_marketingowca();

private:
    double                                      m_stan_konta;
    std::vector< std::unique_ptr< Pracownik > > m_pracownicy;
    std::vector< Kredyt >                       m_kredyty;
    std::vector< double >                       m_przychody;

    int liczba_inzynierow() const;
    int liczba_magazynierow() const;
    int liczba_marketerow() const;
    int liczba_robotnikow() const;

    template < typename T >
    int licz_pracownikow() const;

   

};

#endif // FIRMA_HPP
