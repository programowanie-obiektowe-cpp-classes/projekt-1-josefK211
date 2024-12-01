#ifndef KREDYT_HPP
#define KREDYT_HPP

class Kredyt
{
public:
    Kredyt(double kwota, int raty);
    double splac_rate();
    bool   czy_splacony() const;

private:
    double m_dlug;
    int    m_pozostale_raty;
    double m_miesieczna_rata;
};

#endif // KREDYT_HPP
