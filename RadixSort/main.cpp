// Programa de consola - Radix Sort
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <list>
#include <Windows.h>
#include "windows.h"
#include "ParNroBarras.h"

using namespace std;

/* Variables Globales */
// Datos genéricos
int Lim_Inf = 0, Lim_Sup = 100000;
int intervalos = 50;

// Contenedores
queue<ParNroBarras> DIG[10];
vector<int> numeros;
vector<ParNroBarras> listaPares;

// Función que posiciona el cursor
// "X" se mueve horizontalmente e "Y" indica el número de línea
void gotoXY(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

int potencia10(int exp) {
	int pot = 1;

	for (int i = 0; i < exp; i++) {
		pot *= 10;
	}

	return pot;
}

int obtenerCifraxPos(int num, int pos) {
	int c;
	c = num / (potencia10(pos));
	c = c % 10; // Para quedarme con la ultima cifra
	return c;
}

int obtenerNroMayor(int n) {
	int max = 0;

	for (int i = 0; i < n; i++) {
		if (numeros[i] > max) {
			max = numeros[i];
		}

	}
	return max;
}

int obtenerCifrasMayor(int n) {
	int cifras = 0;
	int max = obtenerNroMayor(n);

	while (max >= 10) {
		cifras++;
		max /= 10;
	}

	cifras++;
	return cifras;
}

void encola(int c, ParNroBarras n) {

	switch (c) {
	case 0:	DIG[0].push(n);
		break;
	case 1:	DIG[1].push(n);
		break;
	case 2:	DIG[2].push(n);
		break;
	case 3:	DIG[3].push(n);
		break;
	case 4:	DIG[4].push(n);
		break;
	case 5:	DIG[5].push(n);
		break;
	case 6:	DIG[6].push(n);
		break;
	case 7:	DIG[7].push(n);
		break;
	case 8:	DIG[8].push(n);
		break;
	case 9:	DIG[9].push(n);
		break;
	}
}

// Función que determina el numero de barras de acuerdo al numero
int obtenerBarrasxNumero(int num) {
	int n_barras, flag = 0, i = 0;
	int h = (Lim_Sup - Lim_Inf + 1) / intervalos;

	while ((i < intervalos) && (flag == 0)) {

		if ((Lim_Inf + i * h <= num) && (num < (Lim_Inf + (i + 1)*h))) {
			n_barras = i + 1;
			flag = 1;
		}

		i++;
	}

	// Esta despues del valor truncado
	// E incluso puede ser Lim_Sup si division no es entera
	if (flag == 0) {
		n_barras = intervalos;
	}

	return n_barras;

	// Modifica vector de barras
	/*barrasNumero.clear();

	for (int i = 0; i < intervalos; i++) {
		if (i < n_barras) {
			barrasNumero.push_back('|');
		}
		else {
			barrasNumero.push_back(' ');
		}
	}*/
}

int obtenerNroBarrasMax(int n) {
	int max = 0, barras;

	for (int i = 0; i < n; i++) {
		barras = listaPares[i].nroBarras;
		if (barras > max) {
			max = barras;
		}
	}

	return max;
}

void graficarBarras(int n, int barras_max, int retraso_ms, int esPrimeraVez) {

	int n_barras;

	for (int i = 0; i < n; i++) {
		
		n_barras = listaPares[i].nroBarras;

		if (esPrimeraVez == 0) {
			if (i != 0) {
				// Borrar el indicador anterior
				gotoXY((i - 1), barras_max);
				cout << " ";
			}

			if (i != (n - 1)) {
				// Borrar el último indicador
				gotoXY(n - 1, barras_max);
				cout << " ";
			}

			// Cursos actual
			gotoXY(i, barras_max);
			cout << "^";
		}

		// para borrar
		for (int j = 0; j < barras_max; j++) {
			gotoXY(i, barras_max - j - 1); // Ir a la posición para escribir (de abajo para arriba)

			cout << ' ';
		}
		Sleep(retraso_ms);

		for (int j = 0; j < barras_max; j++) {
			gotoXY(i, barras_max - j - 1); // Ir a la posición para escribir (de abajo para arriba)

			if (j < n_barras) {
				cout << '|';
			}
			else {
				cout << ' ';
			}
		}

		Sleep(retraso_ms);
	}
}

void modificarOrdenLista() {
	int i = 0, j = 0;
	listaPares.clear();

	while (i < 10) {

		while (!DIG[i].empty()) {
			listaPares.push_back(DIG[i].front());
			DIG[i].pop();
			j++;
		}

		i++;
	}
}

int main() {
	int no_cierre;
	int n, n_barras, num;
	int aux, c, c_max, barras_max;
	ParNroBarras par = ParNroBarras(0,0);

	//n = 10;
	cout << "Ingrese la cantidad de numeros aleatorios a generar en el intervalo [0;100000]: ";
	cin >> n;

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); // Maximizar consola
	numeros.clear();

	// Generar numeros aleatorios
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		num = Lim_Inf + rand() % (Lim_Sup + 1 - Lim_Inf);
		numeros.push_back(num);
	}

	// Cifras del numero mayor
	c_max = obtenerCifrasMayor(n);

	system("cls"); // Limpiar consola

	// Llenar la relación
	for (int i = 0; i < n; i++) {
		n_barras = obtenerBarrasxNumero(numeros[i]);
		ParNroBarras par = ParNroBarras(numeros[i], n_barras);
		listaPares.push_back(par);
	}

	// Obtener mayor numero de barras a dibujar
	barras_max = obtenerNroBarrasMax(n) + 2; // dar espacio

	// Ver números a ordenar
	/*gotoXY(0, barras_max + 4);
	cout << "Numeros a ordenar: ";
	gotoXY(0, barras_max + 5);
	for (int i = 0; i < n; i++) {
		cout << numeros[i] << " ";
	}*/

	// Barras desordenadas
	graficarBarras(n, barras_max, 0, 1);

	Sleep(50); // Retraso

	for (int pos = 0; pos < c_max; pos++) {
		Sleep(50);

		for (int i = 0; i < n; i++) {
			par = listaPares[i];
			c = obtenerCifraxPos(par.numero, pos);

			encola(c, par);
		}

		modificarOrdenLista();

		// Consola
		graficarBarras(n, barras_max, 20, 0);
	}

	// Ver números ordenados
	/*gotoXY(0, barras_max + 7);
	cout << "Numeros ordenados: ";
	gotoXY(0, barras_max + 8);
	for (int i = 0; i < n; i++) {

		cout << listaPares[i].numero << " ";
	}*/

	gotoXY(0, barras_max + 2);
	cout << "Radix Sort";
	cin >> no_cierre;

	return 0;
}