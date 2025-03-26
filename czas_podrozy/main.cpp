#include <iostream>
#include <fstream>
#include <random>

using namespace std;

int main() { // Droga z Łodzi nad morze
    random_device rd;
    mt19937 gen(rd());

    ofstream plik("dane.txt");
    double tab[10000] = {};
    double max_wartosc = 0;
    double min_wartosc = INFINITY;

    discrete_distribution<> transport({6, 3, 1}); // 60% podroz autem, 30% pociagiem, 10% autobusem
    discrete_distribution<> miasto({3, 5, 2}); // 30% kolobrzeg, 50% gdansk, 20% swinoujscie
    normal_distribution<> czas_przerwy_samochod(0.33, 0.1); // srednia przerwa 20min

    normal_distribution<> czas_dojazdu_na_dworzec(0.5, 0.2); // Średni czas 30 minut
    normal_distribution<> czas_dojazdu_z_dworca(0.75, 0.2); // Średni czas 45 minut

    normal_distribution<> czas_dojazdu_na_zbiorke(0.5, 0.2);
    normal_distribution<> czas_dojazdu_ze_zbiorki(0.5, 0.2);

    for (int n = 0; n < 10000; n++) {
        double czas = 0; // w godzinach
        int liczba_przerw = 0;

        switch (transport(gen)) {
            //-------------------------------------------------
            case 0: { // samochod
                switch (miasto(gen)) {
                    case 0: { // kolobrzeg
                        normal_distribution<> kolobrzeg(5.75, 0.3); // sredni czas drogi samochodem do kolobrzegu
                        czas += kolobrzeg(gen);
                        poisson_distribution<> liczba_przerw_kolobrzeg(4); // srednio 4 przerwy w trakcie podrozy do kolobrzegu
                        liczba_przerw = liczba_przerw_kolobrzeg(gen);
                        for (int i = 0; i < liczba_przerw; ++i) {
                            czas += czas_przerwy_samochod(gen); // przy kazdej przerwie liczymy czas przerwy na nowo
                        }

                        break;
                    }
                    case 1: { // gdansk
                        normal_distribution<> gdansk(4.5, 0.5); // sredni czas drogi samochodem do gdanska
                        czas += gdansk(gen);
                        poisson_distribution<> liczba_przerw_gdansk(3); // srednio 3 przerwy w trakcie podrozy do gdanska
                        liczba_przerw = liczba_przerw_gdansk(gen);
                        for (int i = 0; i < liczba_przerw; ++i) {
                            czas += czas_przerwy_samochod(gen); // przy kazdej przerwie liczymy czas przerwy na nowo
                        }

                        break;
                    }
                    case 2: { // swinoujscie
                        normal_distribution<> swinoujscie(6.5, 0.5); // sredni czas drogi samochodem do swinoujscia
                        czas += swinoujscie(gen);
                        poisson_distribution<> liczba_przerw_swinoujscie(5); // srednio 5 przerw w trakcie podrozy do swinoujscia
                        liczba_przerw = liczba_przerw_swinoujscie(gen);
                        for (int i = 0; i < liczba_przerw; ++i) {
                            czas += czas_przerwy_samochod(gen); // przy kazdej przerwie liczymy czas przerwy na nowo
                        }

                        break;
                    }
                    default:
                        cout << "Blad!" << endl;
                        return 1;
                }

                break;
            }
                //-------------------------------------------------
            case 1: { // pociąg (train)
                switch (miasto(gen)) {
                    case 0: { // Kołobrzeg
                        normal_distribution<> pociag_kolobrzeg(8.6, 1); // czas przejazdu pociągiem
                        czas += czas_dojazdu_na_dworzec(gen); // Dodajemy czas dojazdu na dworzec
                        czas += pociag_kolobrzeg(gen);
                        czas += czas_dojazdu_z_dworca(gen); // Dodajemy czas z dworca do miejsca docelowego

                        break;
                    }
                    case 1: { // Gdańsk
                        normal_distribution<> pociag_gdansk(5.5, 0.75); // czas przejazdu pociągiem
                        czas += czas_dojazdu_na_dworzec(gen); // Dodajemy czas dojazdu na dworzec
                        czas += pociag_gdansk(gen);
                        czas += czas_dojazdu_z_dworca(gen); // Dodajemy czas z dworca do miejsca docelowego


                        break;
                    }
                    case 2: { // Świnoujście
                        normal_distribution<> pociag_swinoujscie(8.5, 1); // czas przejazdu pociągiem
                        czas += czas_dojazdu_na_dworzec(gen); // Dodajemy czas dojazdu na dworzec
                        czas += pociag_swinoujscie(gen);
                        czas += czas_dojazdu_z_dworca(gen); // Dodajemy czas z dworca do miejsca docelowego

                        break;
                    }
                    default:
                        cout << "Blad!" << endl;
                        return 1;
                }
                break;
            }
                //-------------------------------------------------
            case 2: { // autokar (bus)
                switch (miasto(gen)) {
                    case 0: { // Kołobrzeg
                        normal_distribution<> autokar_kolobrzeg(5.5, 0.2); // czas przejazdu autokarem
                        czas += czas_dojazdu_na_zbiorke(gen);
                        czas += autokar_kolobrzeg(gen);
                        czas += czas_dojazdu_ze_zbiorki(gen);

                        break;
                    }
                    case 1: { // Gdańsk
                        normal_distribution<> autokar_gdansk(4.25, 0.15); // czas przejazdu autokarem
                        czas += czas_dojazdu_na_zbiorke(gen);
                        czas += autokar_gdansk(gen);
                        czas += czas_dojazdu_ze_zbiorki(gen);

                        break;
                    }
                    case 2: { // Świnoujście
                        normal_distribution<> autokar_swinoujscie(6.75, 0.25); // czas przejazdu autokarem
                        czas += czas_dojazdu_na_zbiorke(gen);
                        czas += autokar_swinoujscie(gen);
                        czas += czas_dojazdu_ze_zbiorki(gen);

                        break;
                    }
                    default:
                        cout << "Blad!" << endl;
                        return 1;
                }
                break;
            }
                //-------------------------------------------------
            default:
                cout << "Blad!" << endl;
                return 1;
        }

        tab[n] = czas;
        cout << "Czas podrozy: " << tab[n] << " godzin" << endl;
        plik << tab[n] << endl;
        if(tab[n] < min_wartosc)
            min_wartosc = tab[n];
        if(tab[n] > max_wartosc)
            max_wartosc = tab[n];
    }
    cout << endl << "Minimalna wartosc: " << min_wartosc << " godzin" << endl;
    cout << "Maksymanlna wartosc: " << max_wartosc << " godzin" << endl;


    plik.close();

    return 0;
}
