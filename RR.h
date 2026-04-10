#ifndef RR_H
#define RR_H
#include <queue>
#include "FifoLifo.h"

using namespace std;

inline double simularRR(vector<Tarea> lista, int q, ofstream &reporte) {
    int n = lista.size(), reloj = 0, finalizados = 0;
    queue<int> cola; vector<bool> enCola(n, false), listo(n, false);
    long long sumaE = 0; double sumaT = 0, sumaI = 0;

    imprimir(reporte, "\nROUND ROBIN (Q=" + to_string(q) + ")\nID    | ti | t  | tf | T   | E           | I\n");

    auto revisarLlegadas = [&]() {
        for (int i = 0; i < n; i++) 
            if (!listo[i] && !enCola[i] && lista[i].ti <= reloj) { cola.push(i); enCola[i] = true; }
    };
    
    revisarLlegadas();

    while (finalizados < n) {
        if (cola.empty()) { reloj++; revisarLlegadas(); continue; }
        
        int actual = cola.front(); cola.pop();
        int consumo = min(q, lista[actual].rem);
        
        for (int i = 0; i < consumo; i++) { reloj++; revisarLlegadas(); }
        lista[actual].rem -= consumo;

        if (lista[actual].rem == 0) {
            lista[actual].tf = reloj;
            lista[actual].T = lista[actual].tf - lista[actual].ti;
            lista[actual].E = (long long)lista[actual].T * lista[actual].t;
            lista[actual].I = (double)lista[actual].t / lista[actual].T;

            sumaT += lista[actual].T; sumaE += lista[actual].E; sumaI += lista[actual].I;
            dibujarFila(reporte, lista[actual]);
            listo[actual] = true; finalizados++;
        } else {
            revisarLlegadas(); cola.push(actual);
        }
    }
    double pE = (double)sumaE / n;
    imprimir(reporte, "PROMEDIOS -> T: " + to_string(sumaT/n) + " | pE: " + to_string(pE) + "\n");
    return pE;
}

#endif
