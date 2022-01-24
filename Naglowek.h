#pragma once
void lobby();
void oneVsOne();
void trening();
bool czyWszystkieKartyOdkryte();
void poczatek();
void czyKartaMozliwaDoWybrania(int* i);
int wprowadzanieNrKarty();
void pokazPlansze();
void uzupelnianiePlanszy(int nrKarty, int nrObrazka);
int drugaWspolrzednaKarty(int nrKarty);
int pierwszaWspolrzednaKarty(int nrKarty);
void losoweUstawienieKart();
void tyVsAI();
void czyKartaMozliwaDoWybraniaAI(int* i);
int wprowadzanieNrKartyAI();