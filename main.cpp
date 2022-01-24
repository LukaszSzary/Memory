#include <iostream>
#include <random>
#include<windows.h>
#include"Naglowek.h"

bool wskaznik1 = false,wskaznik2=false,wskaznik3=false;//wskaznik2 i 3 dostosowuj¹ dzia³anie funkcji w zale¿noœci od trrybu 2(1vs1) 3(ai)  
int karty[20]{}, kartaPierwszyWybor{}, kartaDrugiWybor{}, 
zapelnieniePlanszy[20]{}/*rejest zapamiêtuj¹cy czy karta pod danym nr jest ju¿ odkryta*/,
turaGraczaNr{}, licznikTur{}, licznikPunktow[2];
const int wysokoscObrazka=6,szerokoscObrazka=11,wymiarPionowyPlanszy= wysokoscObrazka*4+3, wymiarPoziomyPlanszy= szerokoscObrazka*5+4;
char plansza[wymiarPionowyPlanszy][wymiarPoziomyPlanszy]{}, obrazki[11][wysokoscObrazka][szerokoscObrazka]= {
	{{201,205,205,205,205,205,205,205,205,205,187},{186,32,32,32,32,32,32,32,32,32,186},{186,32,32,32,32,32,32,32,32,32,186},{186,32,32,32,32,32,32,32,32,32,186},{186,32,32,32,32,32,32,32,32,32,186},{200,205,205,205,205,205,205,205,205,205,188}},
	{{218,196,196,196,196,196,196,196,196,196,191},{179,36,36,36,36,36,36,36,36,36,179},{179,36,36,36,36,36,36,36,36,36,179},{179,36,36,36,36,36,36,36,36,36,179},{179,36,36,36,36,36,36,36,36,36,179},{192,196,196,196,196,196,196,196,196,196,217}},
	{{218,196,196,196,196,196,196,196,196,196,191},{179,176,176,176,176,176,176,176,176,176,179},{179,176,176,176,176,176,176,176,176,176,179},{179,176,176,176,176,176,176,176,176,176,179},{179,176,176,176,176,176,176,176,176,176,179},{192,196,196,196,196,196,196,196,196,196,217}},
	{{218,196,196,196,196,196,196,196,196,196,191},{179,177,177,177,177,177,177,177,177,177,179},{179,177,177,177,177,177,177,177,177,177,179},{179,177,177,177,177,177,177,177,177,177,179},{179,177,177,177,177,177,177,177,177,177,179},{192,196,196,196,196,196,196,196,196,196,217}},
	{{218,196,196,196,196,196,196,196,196,196,191},{179,178,178,178,178,178,178,178,178,178,179},{179,178,178,178,178,178,178,178,178,178,179},{179,178,178,178,178,178,178,178,178,178,179},{179,178,178,178,178,178,178,178,178,178,179},{192,196,196,196,196,196,196,196,196,196,217}},
	{{218,196,196,196,196,196,196,196,196,196,191},{179,186,186,186,186,186,186,186,186,186,179},{179,186,186,186,186,186,186,186,186,186,179},{179,186,186,186,186,186,186,186,186,186,179},{179,186,186,186,186,186,186,186,186,186,179},{192,196,196,196,196,196,196,196,196,196,217}},
	{{218,196,196,196,196,196,196,196,196,196,191},{179,205,205,205,205,205,205,205,205,205,179},{179,205,205,205,205,205,205,205,205,205,179},{179,205,205,205,205,205,205,205,205,205,179},{179,205,205,205,205,205,205,205,205,205,179},{192,196,196,196,196,196,196,196,196,196,217}},
	{{218,196,196,196,196,196,196,196,196,196,191},{179,174,174,174,174,174,174,174,174,174,179},{179,174,174,174,174,174,174,174,174,174,179},{179,174,174,174,174,174,174,174,174,174,179},{179,174,174,174,174,174,174,174,174,174,179},{192,196,196,196,196,196,196,196,196,196,217}},
	{{218,196,196,196,196,196,196,196,196,196,191},{179,175,175,175,175,175,175,175,175,175,179},{179,175,175,175,175,175,175,175,175,175,179},{179,175,175,175,175,175,175,175,175,175,179},{179,175,175,175,175,175,175,175,175,175,179},{192,196,196,196,196,196,196,196,196,196,217}},
	{{218,196,196,196,196,196,196,196,196,196,191},{179,35,35,35,35,35,35,35,35,35,179},{179,35,35,35,35,35,35,35,35,35,179},{179,35,35,35,35,35,35,35,35,35,179},{179,35,35,35,35,35,35,35,35,35,179},{192,196,196,196,196,196,196,196,196,196,217}},
	{{218,196,196,196,196,196,196,196,196,196,191},{179,38,38,38,38,38,38,38,38,38,179},{179,38,38,38,38,38,38,38,38,38,179},{179,38,38,38,38,38,38,38,38,38,179},{179,38,38,38,38,38,38,38,38,38,179},{192,196,196,196,196,196,196,196,196,196,217}}
};
//obrazki w formie ASCII
using namespace std;

void losoweUstawienieKart() {
	int x{};
	mt19937 generator(time(nullptr));
	uniform_int_distribution<int> nrKarty(0, 19);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			while (true) {
				x = nrKarty(generator);
				if (karty[x] == 0) {
					karty[x] = i + 1;
					break;
				}
			}
		}
	}
}//
//losowo ustawia karty w tablicy ktora przechowyje ich kolejnosc
int pierwszaWspolrzednaKarty(int nrKarty) {
	if (nrKarty < 6) { return 0; }
	else if(nrKarty >= 6 && nrKarty <11) { return (wysokoscObrazka + 1); }
	else if(nrKarty >= 11 && nrKarty < 16) { return 2*(wysokoscObrazka + 1); }
	else if(nrKarty >= 16 ) { return 3*(wysokoscObrazka + 1); }
}
//zwraca pierwsza wspolrzedna karty na planszy
int drugaWspolrzednaKarty(int nrKarty) {
	if (nrKarty%5 ==1) { return 0; }
	else if (nrKarty % 5 == 2) { return (szerokoscObrazka+1); }
	else if (nrKarty % 5 == 3) { return 2*(szerokoscObrazka + 1); }
	else if (nrKarty % 5 == 4) { return 3*(szerokoscObrazka + 1); }
	else if (nrKarty % 5 == 0) { return 4*(szerokoscObrazka + 1); }
	
}
//zwraca druga wspolrzedna karty na planszy
void uzupelnianiePlanszy(int nrKarty, int nrObrazka ) {
	if (nrObrazka == 0) {
		for (int i = 0; i < wysokoscObrazka; i++) {
			for (int j = 0; j < szerokoscObrazka; j++) {
				plansza[pierwszaWspolrzednaKarty(nrKarty) + i][drugaWspolrzednaKarty(nrKarty) + j] = obrazki[nrObrazka][i][j];
				if (nrKarty <= 9 && i==1 && j==1) {
					plansza[pierwszaWspolrzednaKarty(nrKarty) + i][drugaWspolrzednaKarty(nrKarty) + j] =nrKarty+'0';
				}
				else if (nrKarty > 9) {
					if(i==1&&j==1){ plansza[pierwszaWspolrzednaKarty(nrKarty) + i][drugaWspolrzednaKarty(nrKarty) + j] = (nrKarty/10)+'0'; }
					if (i == 1 && j == 2) { plansza[pierwszaWspolrzednaKarty(nrKarty) + i][drugaWspolrzednaKarty(nrKarty) + j] = (nrKarty%10)+'0'; }
				}
			}
		}
	}
	else {
		for (int i = 0; i < wysokoscObrazka; i++) {
			for (int j = 0; j < szerokoscObrazka; j++) {
				plansza[pierwszaWspolrzednaKarty(nrKarty) + i][drugaWspolrzednaKarty(nrKarty) + j] = obrazki[nrObrazka][i][j];
			}
		}
	}
}
//wpisuje pojedynczy obrazek do planszy
void pokazPlansze() {
	system("cls");
	for (int i = 0; i < wymiarPionowyPlanszy; i++) {
		for (int j = 0; j < wymiarPoziomyPlanszy; j++) {
				cout << plansza[i][j];
		}
		cout << endl;
	}
	if (wskaznik2) {
		cout << "Ilo" << static_cast<char>(152) << static_cast<char>(134) << " punkt" << static_cast<char>(162) << "w : gracz 1 " << licznikPunktow[0] << ", gracz 2 " << licznikPunktow[1] << ". ";
	}
	if (wskaznik3) {
		cout << "Ilo" << static_cast<char>(152) << static_cast<char>(134) << " punkt" << static_cast<char>(162) << "w : gracz " << licznikPunktow[0] << ", AI " << licznikPunktow[1] << ". ";
	}
}
//wypisuje plansze
int wprowadzanieNrKarty() {

	int i{};
	pokazPlansze();
	if (wskaznik3) {//dodatkowe informacje jesli tryb to 1vsAI
		if (licznikTur % 2 == 0) {
			cout << "Tura gracza " <<endl;
		}
		else {
			cout << "Tura AI " << endl;
		}
	}
	if (wskaznik2) {//dodatkowe informacje w przypadku trybu 1vs1
		cout << "Tura gracza numer " << turaGraczaNr<<endl;
	}
	if (wskaznik1) {//informacje odnoszace sie do proby wyboru juz wybranej karty
		cout << "Ta karta by" << static_cast<char>(136) << "a ju"<< static_cast<char>(190)<<" wybrana! ";
		wskaznik1 = false;
	}
	cout << "Podaj numer karty, kt"<< static_cast<char>(162)<<static_cast<char>(165)<<" wybierasz : ";
	cin >> i;
	while (i<1||i>20||cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		pokazPlansze();
		cout << "Nieprawid"<<static_cast<char>(136)<<"owa warto"<< static_cast<char>(152)<< static_cast<char>(134)<<"!" << endl;
		cout << "Podaj numer karty, kt" << static_cast<char>(162) << static_cast<char>(165) << " wybierasz : ";
		cin >> i;
	}
	return i;
}
//pyta i waliduje o nr karty pod katem zakresu i poprawnosci strumienia wejscia
void czyKartaMozliwaDoWybrania(int *i) {
	while (zapelnieniePlanszy[*i - 1] != 0) {
		wskaznik1 = true;
		*i = wprowadzanieNrKarty();
	}
	zapelnieniePlanszy[*i - 1] = 1;
}
//sprawdza czy gracz mo¿e wybraæ tak¹ kartê, czy nie zosta³a ju¿ wczeœniej odkryta i pobiera nr. kart do momentu podania nr. mo¿liwego do wybrania
void poczatek() {
	for (int j = 1; j < 21; j++) {//wype³nienie palnszy kartami "0" czyli "ty³ami" kart
		uzupelnianiePlanszy(j, 0);
		zapelnieniePlanszy[j - 1] = 0;
		karty[j - 1] = 0;
	}
	licznikPunktow[0] = 0;
	licznikPunktow[1] = 0;
	licznikTur = 0;
	losoweUstawienieKart();
}
//wazne akcje do wykonania na pocz¹tku
bool czyWszystkieKartyOdkryte() {
	int c{};
	for (int i = 0; i < 20; i++) {
		c += zapelnieniePlanszy[i];
	}
	if (c == 20) {
		return false;
	}
	else {
		return true;
	}
}
//sprawdza czy wszystkie karty zosta³y odkryte 
int wprowadzanieNrKartyAI() {
	int i{};
	pokazPlansze();
	cout << "Tura AI " << endl;
	mt19937 generator(time(nullptr));
	uniform_int_distribution<int> nrKartyAI(1, 20);
	i = nrKartyAI(generator);
	return i;
}
// AI "wybiera" karte
void czyKartaMozliwaDoWybraniaAI(int* i) {
	while (zapelnieniePlanszy[*i - 1] != 0) {
		*i = wprowadzanieNrKartyAI();
	}
	zapelnieniePlanszy[*i - 1] = 1;
}
//sprawdza czy AI mo¿e wybraæ t¹ kartê
void trening() {
	poczatek();
	while (czyWszystkieKartyOdkryte()) {
		kartaPierwszyWybor = wprowadzanieNrKarty();
		czyKartaMozliwaDoWybrania(&kartaPierwszyWybor);
		uzupelnianiePlanszy(kartaPierwszyWybor, karty[kartaPierwszyWybor - 1]);
		pokazPlansze();
		kartaDrugiWybor = wprowadzanieNrKarty();
		czyKartaMozliwaDoWybrania(&kartaDrugiWybor);
		uzupelnianiePlanszy(kartaDrugiWybor, karty[kartaDrugiWybor - 1]);
		pokazPlansze();
		if (karty[kartaPierwszyWybor - 1] != karty[kartaDrugiWybor - 1]) {
			//jeœli odkryte karty nie s¹ takie same ten if cofa zmiany na planszy i w rejestrze odkrytych kart
			Sleep(2000);
			uzupelnianiePlanszy(kartaPierwszyWybor, 0);
			zapelnieniePlanszy[kartaPierwszyWybor - 1] -= 1;
			uzupelnianiePlanszy(kartaDrugiWybor, 0);
			zapelnieniePlanszy[kartaDrugiWybor - 1] -= 1;
			pokazPlansze();
		}
	}
	cout << "Koniec treningu!"<<endl;
	cout << "Je" << static_cast<char>(152) << "li chcesz powt" << static_cast<char>(162) << "rzy" << static_cast<char>(134) << " trening, nacisnij TAB, by powr" << static_cast<char>(162) << "ci" << static_cast<char>(134) << " do menu naci" << static_cast<char>(152) << "nij ESC.";
	while (true) {
		if (GetKeyState(VK_TAB) & 0x8000)
		{
			trening();
		}
		if (GetKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
	}
	lobby();
}
//trening memory
void oneVsOne(){
	poczatek();
	wskaznik2 = true;
	while (czyWszystkieKartyOdkryte()) {
		turaGraczaNr = (licznikTur % 2) + 1;
		kartaPierwszyWybor = wprowadzanieNrKarty();
		czyKartaMozliwaDoWybrania(&kartaPierwszyWybor);
		uzupelnianiePlanszy(kartaPierwszyWybor, karty[kartaPierwszyWybor - 1]);
		pokazPlansze();
		kartaDrugiWybor = wprowadzanieNrKarty();
		czyKartaMozliwaDoWybrania(&kartaDrugiWybor);
		uzupelnianiePlanszy(kartaDrugiWybor, karty[kartaDrugiWybor - 1]);
		pokazPlansze();
		if (karty[kartaPierwszyWybor - 1] != karty[kartaDrugiWybor - 1]) {
			//jeœli odkryte karty nie s¹ takie same ten if cofa zmiany na planszy i w rejestrze odkrytych kart
			Sleep(2000);
			uzupelnianiePlanszy(kartaPierwszyWybor, 0);
			zapelnieniePlanszy[kartaPierwszyWybor - 1] -= 1;
			uzupelnianiePlanszy(kartaDrugiWybor, 0);
			zapelnieniePlanszy[kartaDrugiWybor - 1] -= 1;
			pokazPlansze();
		}
		else {
			licznikPunktow[licznikTur % 2] += 1; // przyznaje punkt graczowi którego obecnie jest tura
		}
		licznikTur += 1;
	}
	if (licznikPunktow[0] > licznikPunktow[1]) {
		cout << "Wygra" << static_cast<char>(136) << " gracz 1!\n";
	}
	else if (licznikPunktow[0] < licznikPunktow[1]) {
		cout << "Wygra" << static_cast<char>(136) << " gracz 2!\n";
	}
	else if (licznikPunktow[0] == licznikPunktow[1]) {
		cout << "Remis\n";
	}
	cout << "Je" << static_cast<char>(152) << "li chcesz zagra" << static_cast<char>(134) << " jeszcze raz, nacisnij SPACE, by powr" << static_cast<char>(162) << "ci" << static_cast<char>(134) << " do menu naci" << static_cast<char>(152) << "nij TAB.";
	wskaznik2 = false;
	while (true) {
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			oneVsOne();
		}
		if (GetKeyState(VK_TAB) & 0x8000)
		{
			break;
		}
	}
	lobby();
}
//tryb 1 na 1
void tyVsAI() {
	poczatek();
	wskaznik3 = true;
	while (czyWszystkieKartyOdkryte()) {
		
		turaGraczaNr = (licznikTur % 2) + 1;
		if (turaGraczaNr == 1) {
			kartaPierwszyWybor = wprowadzanieNrKarty();
			czyKartaMozliwaDoWybrania(&kartaPierwszyWybor);
			uzupelnianiePlanszy(kartaPierwszyWybor, karty[kartaPierwszyWybor - 1]);
			pokazPlansze();
			kartaDrugiWybor = wprowadzanieNrKarty();
			czyKartaMozliwaDoWybrania(&kartaDrugiWybor);
			uzupelnianiePlanszy(kartaDrugiWybor, karty[kartaDrugiWybor - 1]);
			pokazPlansze();
		}
		else {
			kartaPierwszyWybor = wprowadzanieNrKartyAI();
			czyKartaMozliwaDoWybraniaAI(&kartaPierwszyWybor);
			uzupelnianiePlanszy(kartaPierwszyWybor, karty[kartaPierwszyWybor - 1]);
			pokazPlansze();
			Sleep(1000);
			kartaDrugiWybor = wprowadzanieNrKartyAI();
			czyKartaMozliwaDoWybraniaAI(&kartaDrugiWybor);
			uzupelnianiePlanszy(kartaDrugiWybor, karty[kartaDrugiWybor - 1]);
			pokazPlansze();

		}
		if (karty[kartaPierwszyWybor - 1] != karty[kartaDrugiWybor - 1]) {
			//jeœli mie zozsa³y wybrane takie same karty to ten if cofa zaznaczenie ¿e te karty s¹ wybrane i zakrywa karty(zastêpuje je kartami "0")  
			Sleep(2000);
			uzupelnianiePlanszy(kartaPierwszyWybor, 0);
			zapelnieniePlanszy[kartaPierwszyWybor - 1] -= 1;
			uzupelnianiePlanszy(kartaDrugiWybor, 0);
			zapelnieniePlanszy[kartaDrugiWybor - 1] -= 1;
			pokazPlansze();
		}
		else {
			licznikPunktow[licznikTur % 2] += 1;
		}
		licznikTur += 1;
	}
	if (licznikPunktow[0] > licznikPunktow[1]) {
		cout << "Wygra" << static_cast<char>(136) << " gracz!\n";
	}
	else if (licznikPunktow[0] < licznikPunktow[1]) {
		cout << "Wygra" << static_cast<char>(136) << "o AI!\n";
	}
	else if (licznikPunktow[0] == licznikPunktow[1]) {
		cout << "Remis\n";
	}
	cout << "Je" << static_cast<char>(152) << "li chcesz zagra" << static_cast<char>(134) << " jeszcze raz, nacisnij SPACE, by powr" << static_cast<char>(162) << "ci" << static_cast<char>(134) << " do menu naci" << static_cast<char>(152) << "nij TAB.";
	wskaznik3 = false;
	while (true) {
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			tyVsAI();
		}
		if (GetKeyState(VK_TAB) & 0x8000)
		{
			break;
		}
	}
	lobby();
}
//gracz vs AI
void lobby() {
	system("cls");
	char baner[3][36] = { {' ',' ',220,' ',' ',' ',220,' ',' ',220,220,220,' ',' ',220,' ',' ',' ',220,' ',' ',' ',220,220,220,' ',' ',220,220,220,' ',220,' ',' ',' ',220},{' ',219,' ',223,220,223,' ',219,' ',219,220,' ',' ',219,' ',223,220,223,' ',219,' ',219,' ',' ',' ',219,' ',219,220,219,' ',' ',223,220,223,' '},{' ',219,' ',' ',' ',' ',' ',219,' ',219,220,220,' ',219,' ',' ',' ',' ',' ',219,' ',223,220,220,220,223,' ',219,223,220,' ',' ',' ',219,' ',' '} };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 36; j++) {
			cout << baner[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Wybierz numer trybu gry!" << endl;
	cout << "1. 1 vs 1" << endl;
	cout << "2. Ty vs AI" << endl;
	cout << "3. Trening" << endl;
	cout << "Je" << static_cast<char>(152) << "li chcesz zamkn" << static_cast<char>(165) << static_cast<char>(134) << " program naci" << static_cast<char>(152) << "nij ESC." ;
	while (true) {
		if (GetKeyState(0x31))
		{
			oneVsOne();
		}
		if (GetKeyState(0x32) & 0x8000)
		{
			tyVsAI();
		}
		if (GetKeyState(0x33) & 0x8000)
		{
			trening();
		}
		if (GetKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
	}
}
//menu

int main() {
	lobby();
}