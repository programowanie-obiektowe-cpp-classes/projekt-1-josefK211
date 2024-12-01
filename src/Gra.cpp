#include "Gra.hpp"
#include "Firma.hpp"
#include <iostream>
#include <string>


void Gra::start()
{
    while (true)
    {
        std::cout << "\nWybierz akcje:\n";
        std::cout << "lp - wylistuj pracownikow\n";
        std::cout << "zinz - zatrudnij inzyniera\n";
        std::cout << "zmag - zatrudnij magazyniera\n";
        std::cout << "zmkt - zatrudnij marketera\n";
        std::cout << "zrob - zatrudnij robotnika\n";
        std::cout << "kred - wez kredyt\n";
        std::cout << "kt - zakoncz ture\n";
        std::cout << "zatrudniaj inzynierow zeby latwo wygrac\n";
        std::cout << "nie zmienienie nic skonczy sie porazka\n";

        std::string komenda;
        std::cin >> komenda;

         if (komenda == "lp")
        {
            m_firma.drukuj_pracownikow();
        }
        else if (komenda == "zinz")
        {
            m_firma.zatrudnij(std::make_unique< Inz >(m_firma.losuj_imie_inzyniera(), "MEiL"));
        }
        else if (komenda == "zmag")
        {
            m_firma.zatrudnij(std::make_unique< Mag >(m_firma.losuj_imie_magazyniera(), true));
        }
        else if (komenda == "zmkt")
        {
            m_firma.zatrudnij(std::make_unique< Mkt >(m_firma.losuj_imie_marketingowca(), 100));
        }
        else if (komenda == "zrob")
        {
            m_firma.zatrudnij(std::make_unique< Rob >(m_firma.losuj_imie_robotnika(), 42.5));
        }

        else if (komenda == "kred")
        {
            int kwota;
            int    raty;
            std::cout << "Podaj kwote kredytu: ";
            std::cin >> kwota;
            std::cout << "Podaj liczbe rat: ";
            std::cin >> raty;
            m_firma.wez_kredyt(kwota, raty);
        }
        else if (komenda == "kt")
        {
            m_firma.splac_raty();
            m_firma.zaplac_wynagrodzenie();
            m_firma.symuluj_miesiac();
            m_firma.podsumuj();

            if (m_firma.wartosc_firmy() >= 10000.0)
            {
                std::cout << "Gratulacje! Osiagnales cel gry!\n";
                break;
            }
        }
        else
        {
            std::cout << "Nieznana komenda!\n";
        }
    }
}
