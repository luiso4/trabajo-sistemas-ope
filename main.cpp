#include "FifoLifo.h"
#include "Rr.h"
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

int main() {
    int quantum; 
    cout << "Ingresa el valor del Quantum: "; 
    if (!(cin >> quantum)) return 1;

    ifstream archivo("Datos.csv"); 

    vector<Tarea> base; string linea; bool titulo = true;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea); string c1, c2, c3;
        if (getline(ss, c1, ',') && getline(ss, c2, ',') && getline(ss, c3)) {
            if (titulo && c2.find_first_not_of("0123456789") != string::npos) { titulo = false; continue; }
            base.push_back({c1, stoi(c2), stoi(c3), stoi(c3), 0, 0, 0, 0});
        }
        titulo = false;
    }
    archivo.close();

    ofstream log("resultados.txt");

    auto t1 = high_resolution_clock::now(); 
    double r_fifo = simularFIFO(base, "ALGORITMO FIFO", log);
    double ms_fifo = duration_cast<microseconds>(high_resolution_clock::now() - t1).count() / 1000.0;

    auto t2 = high_resolution_clock::now(); 
    double r_lifo = simularLIFO(base, "ALGORITMO LIFO", log);
    double ms_lifo = duration_cast<microseconds>(high_resolution_clock::now() - t2).count() / 1000.0;

    auto t3 = high_resolution_clock::now(); 
    double r_rr = simularRR(base, quantum, log);
    double ms_rr = duration_cast<microseconds>(high_resolution_clock::now() - t3).count() / 1000.0;

    imprimir(log, "\nTIEMPOS\nFIFO: " + to_string(ms_fifo) + " ms\nLIFO: " + to_string(ms_lifo) + " ms\nRR:   " + to_string(ms_rr) + " ms\n");
    
    double el_menor = min({r_fifo, r_lifo, r_rr});
    string ganador = (el_menor == r_fifo) ? "FIFO" : (el_menor == r_lifo) ? "LIFO" : "ROUND ROBIN";
    
    imprimir(log, "\nEl mejor algoritmo es " + ganador + " (Menor pE)\n");

    log.close(); 
    cout << "\nRevisa el txt\n"; 
    
    return 0;
}
