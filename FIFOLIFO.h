#ifndef FIFOLIFO_H
#define FIFOLIFO_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct Tarea { 
    string id; 
    int ti, t, rem, tf, T; 
    long long E; 
    double I; 
};

inline void imprimir(ofstream &archivo, string texto) {
    archivo << texto;
}

inline void dibujarFila(ofstream &archivo, Tarea &a) {
    stringstream ss;
    ss << left << setw(6) << a.id << "| " << setw(3) << a.ti << "| " << setw(3) << a.t 
       << "| " << setw(4) << a.tf << "| " << setw(4) << a.T << "| " << setw(12) << a.E 
       << "| " << fixed << setprecision(4) << a.I << "\n";
    imprimir(archivo, ss.str());
}

inline double simularFIFO(vector<Tarea> lista, string nombre, ofstream &reporte) {
    int n = lista.size(), reloj = 0, finalizados = 0;
    vector<bool> listo(n, false);
    long long sumaE = 0; double sumaT = 0, sumaI = 0;

    imprimir(reporte, "\n" + nombre + "\nID    | ti | t  | tf | T   | E           | I\n");

    while (finalizados < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (!listo[i] && lista[i].ti <= reloj) {
                if (idx == -1 || lista[i].ti < lista[idx].ti) {
                    idx = i;
                }
            }
        }
        
        if (idx == -1) { reloj++; continue; }

        reloj += lista[idx].t; 
        lista[idx].tf = reloj;
        lista[idx].T = lista[idx].tf - lista[idx].ti;
        lista[idx].E = (long long)lista[idx].T * lista[idx].t;
        lista[idx].I = (double)lista[idx].t / lista[idx].T;

        sumaT += lista[idx].T; sumaE += lista[idx].E; sumaI += lista[idx].I;
        dibujarFila(reporte, lista[idx]);
        listo[idx] = true; finalizados++;
    }
    double pE = (double)sumaE / n;
    imprimir(reporte, "PROMEDIOS -> T: " + to_string(sumaT/n) + " | pE: " + to_string(pE) + "\n");
    return pE;
}

inline double simularLIFO(vector<Tarea> lista, string nombre, ofstream &reporte) {
    int n = lista.size(), reloj = 0, finalizados = 0;
    vector<bool> listo(n, false);
    long long sumaE = 0; double sumaT = 0, sumaI = 0;

    imprimir(reporte, "\n" + nombre + "\nID    | ti | t  | tf | T   | E           | I\n");

    while (finalizados < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (!listo[i] && lista[i].ti <= reloj) {
                if (idx == -1 || lista[i].ti > lista[idx].ti) {
                    idx = i;
                }
            }
        }
        
        if (idx == -1) { reloj++; continue; }

        reloj += lista[idx].t; 
        lista[idx].tf = reloj;
        lista[idx].T = lista[idx].tf - lista[idx].ti;
        lista[idx].E = (long long)lista[idx].T * lista[idx].t;
        lista[idx].I = (double)lista[idx].t / lista[idx].T;

        sumaT += lista[idx].T; sumaE += lista[idx].E; sumaI += lista[idx].I;
        dibujarFila(reporte, lista[idx]);
        listo[idx] = true; finalizados++;
    }
    double pE = (double)sumaE / n;
    imprimir(reporte, "PROMEDIOS -> T: " + to_string(sumaT/n) + " | pE: " + to_string(pE) + "\n");
    return pE;
}

#endif
