/* 
 * File:   main.cpp
 * Author: fabricio
 *
 * Created on 9 de noviembre de 2014, 0:12
 */

#include <iostream>
#include<stdio.h>
#include<math.h>
using namespace std;

class srtn {
public:
    int n, bt[10], at[10], tat[10], wt[10], rt[10], finish[10], twt, ttat, total;
    void IngresarDatos();
    void ejecutarSRT();
    void iniciar();
    void verTiempos();
    int siguienteProceso(int);
};

void srtn::IngresarDatos() {
    cout << "Ingrese numero de procesos: ";
    cin>>n;
    for (int i = 0; i < n; i++) {
        cout << "Ingrese tiempo rafaga del proceso" << i + 1 << ": ";
        cin >> bt[i];
        cout << "Ingrese tiempo de llegada del proceso" << i + 1 << ": ";
        cin >> at[i];
    }
}

void srtn::iniciar() {
    total = 0;
    twt = 0;
    ttat = 0;
    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
        finish[i] = 0;
        wt[i] = 0;
        tat[i] = 0;
        total += bt[i];
    }
}

void srtn::ejecutarSRT() {
    IngresarDatos();
    iniciar();
    int time, next = 0, old, i;
    cout << "Diagrama Gantt \n ";
    for (time = 0; time < total; time++) {
        old = next;
        next = siguienteProceso(time);
        if (old != next || time == 0) cout << "(" << time << ")|==P" << next + 1 << "==|";
        rt[next] = rt[next] - 1;
        if (rt[next] == 0) finish[next] = 1;
        for (i = 0; i < n; i++)
            if (i != next && finish[i] == 0 && at[i] <= time)
                wt[i]++;
    }
    cout << "(" << total << ")" << endl;

    for (i = 0; i < n; i++)
        if (!finish[i]) {
            cout << "No se puede continuar\n";
            return;
        }
    verTiempos();
}

void srtn::verTiempos() {
    for (int i = 0; i < n; i++) {
        twt += wt[i];
        tat[i] = wt[i] + bt[i];
        ttat += tat[i];
        cout << "Tiempo de espera para P" << (i + 1) << " = " << wt[i] << ", tiempo de respuesta= " << tat[i] << endl;
    }
    cout << "Tiempo medio de espera = " << (double) twt / n << "Tiempo medio de respuesta = " << (double) ttat / n << endl;
}

int srtn::siguienteProceso(int time) {
    int i, low;
    for (i = 0; i < n; i++)
        if (finish[i] == 0) {
            low = i;
            break;
        }
    for (i = 0; i < n; i++)
        if (finish[i] != 1)
            if (rt[i] < rt[low] && at[i] <= time)
                low = i;
    return low;
}

int main() {
    srtn algoritmo;
    algoritmo.ejecutarSRT();
    return 0;
}
