#include "Kredyt.hpp"

Kredyt::Kredyt(double kwota, int raty) : m_dlug(kwota), m_pozostale_raty(raty), m_miesieczna_rata(kwota / raty)
{}

double Kredyt::splac_rate()
{
    if (m_pozostale_raty > 0)
    {
        --m_pozostale_raty;
        return m_miesieczna_rata;
    }
    return 0.0;
}

bool Kredyt::czy_splacony() const
{
    return m_pozostale_raty <= 0;
}
