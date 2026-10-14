#ifndef PRODUS_H
#define PRODUS_H
#include "Ingredient.h"
#include "StrategiePret.h"
#include <string>
#include <memory>
#include <iostream>
#include <vector>


class Produs
{
protected:
    ///atributele sunt protected pentru a fi accesibile direct in clasele derivate
    std::string nume;
    float pretPreparare;///pret de baza
    int timpPreparare;

    std::shared_ptr<StrategiePret> strategiePret;

    Produs(std::string nume="", float pretPrep=0.0f, int timpPrep=0);

    Produs(const Produs& other) = default;
    Produs& operator=(const Produs& other) = default;

    ///metode virtuale interne
    virtual float calculeazaPretFinal() const;
    virtual void afisareDetalii(std::ostream& os) const = 0;///virtuala pura

public:
    virtual ~Produs() = default;///destructor virtual

    void setStrategiePret(std::shared_ptr<StrategiePret> nouaStrategie)
    {
        if(nouaStrategie)
            strategiePret=nouaStrategie;
    }

    std::shared_ptr<StrategiePret> getStrategiePret() const
    {
        return strategiePret;
    }

    void afiseaza(std::ostream& os) const;
    float getPretFinal() const
    {
        return calculeazaPretFinal();
    }

    int getTimpPreparare() const
    {
        return timpPreparare;
    }

    ///permite copierea obiectelor fara a sti timpul exact la momentul copierii
    virtual std::shared_ptr<Produs> clone() const = 0;

    friend void swap(Produs& a, Produs& b);

    /// permite clasei Gestiune sa ceara lista de ingrediente
    /// indiferent de tipul de produs (Bautura, Patiserie, Sandwich)
    virtual const std::vector<Ingredient*>& getIngrediente() const = 0;

    ///metode virtuale pure
    virtual bool esteVegan() const = 0;
    virtual bool esteFaraZahar() const = 0;
    virtual bool esteFaraLactoza() const = 0;
    virtual float calculeazaKcalTotal() const = 0;
    virtual bool esteDisponibil() const = 0;

    const std::string& getNume() const
    {
        return nume;
    }
    float getPretPreparare() const
    {
        return pretPreparare;    // Am corectat getter-ul (nu e nevoie de referinta la float)
    }

    /// operatorul << de afisare
    friend std::ostream& operator<<(std::ostream& os, const Produs& p);
};

#endif
