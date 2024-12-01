#ifndef PRACOWNICY_HPP
#define PRACOWNICY_HPP

#include <iostream>
#include <string>

class Pracownik
{
public:
    virtual ~Pracownik()         = default;
    virtual void   print() const = 0;
    virtual double koszt() const = 0;

protected:
    explicit Pracownik(std::string imie);
    std::string m_imie;
};

class Inz : public Pracownik
{
public:
    Inz(std::string imie, std::string wydzial);
    void   print() const override;
    double koszt() const override;

private:
    std::string m_wydzial;
};

class Mag : public Pracownik
{
public:
    Mag(std::string imie, bool obsl_widl);
    void   print() const override;
    double koszt() const override;

private:
    bool m_obsl_widl;
};

class Mkt : public Pracownik
{
public:
    Mkt(std::string imie, int follows);
    void   print() const override;
    double koszt() const override;

private:
    int m_follows;
};

class Rob : public Pracownik
{
public:
    Rob(std::string imie, double but);
    void   print() const override;
    double koszt() const override;

private:
    double m_but;
};

#endif // PRACOWNICY_HPP
