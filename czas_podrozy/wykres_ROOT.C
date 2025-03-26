#include <iostream>
#include <fstream>
#include <cmath>
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"

using namespace std;

void rysowanie_zaliczenie()
{
    const int n = 10000;
    float x1[n];
    ifstream d("sciezka\\dane.txt");

    for (int i = 0; i < n; ++i) {
        d >> x1[i];
    }
    d.close();

    TCanvas *c1 = new TCanvas("c1", "Jakub Ludwiczak - Zaliczenie", 1200, 800);

    int bins = static_cast<int>((14.0 - 2.0) / 0.25); // podzial na 4 slupki na kazda godzine

    TH1F *hi1 = new TH1F("hi1", "Czas podrozy z Lodzi nad morze;Czas w godzinach;Liczba wystapien", bins, 2.0, 14.0);
    for (int i = 0; i < n; ++i) {
        hi1->Fill(x1[i]);
    }
	
    hi1->SetFillColor(7);
    hi1->SetFillStyle(3003);
    hi1->SetLineColor(kBlack);
    hi1->SetLineWidth(2);
    hi1->GetXaxis()->SetNdivisions(20); // pokazuje wszystkie godziny 

    hi1->Draw();
    TF1 *fitFunc = new TF1("fitFunc", "gaus", 2.0, 14.0);
    hi1->Fit(fitFunc, "R");
}
