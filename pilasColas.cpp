/*
	@autor: 		Khriz Enríquez
	@nombreApp:		pilasColas
	@descripción:	Se ingresarán datos para las pilas y colas, en base a eso se hace el push (en las pilas) 
					y el pop (en las colas), aparte de mostrar los datos actuales dentro de la estructura.

	El menú tendrá las opciones:
		-1. Push: ingresar valores o elementos a la pila
		-2. Pop: eliminar el elemento de la pila (lifo ( last in first out ))
		-3. Eliminar dato de cola: eliminará el primer dato de la cola
		-4. Mostrar los elementos que contenga la pila
		-5. Salir
*/

//	declarando las librerias necesarias a utilizar
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>//me permite usar el exit
#include <windows.h>//para poder usar el sleep
#include <iostream>

//	definiciones
#define cantidad 10//cantidad de valores que podre ingresar a mi pila

using namespace std;

//	variables globales
/*cuando una pila esta vacia se coloca el valor -1 por estandar https://www.youtube.com/watch?v=yE0aMD5IueE*/
int top = -1;
/*el bottom tendrá el valor del primer arreglo*/
int bottom = 0;
/*tendrá 10 posiciones la pila, no puedo generar un elemento como un JSon para que reciba varios valores
entonces lo mas cernano será una pila en forma de arreglo*/
struct pila{
	int id;//identificador del elemento de la pila
	char valor[30];
} pila1[ cantidad ];
//	construyendo el menú
void menu (){
	//	limpio la pantalla de cualquier cosa que tenga escrita en ella
	int opcion = 0;
	printf("*******************************************\n");
	printf("Programa de pilas\nBienvenido super usuario que opcion deseas usar:\n\n");
	printf("	1.	Push\n");
	printf("	2.	Pop\n");
	printf("	3.	Eliminar dato de la cola\n");
	printf("	4.	Mostrar la pila actual\n");
	printf("	5.	Salir\n");
	printf("*******************************************\n\n");

	cin >> opcion;

	if ( opcion == 1 ) {
		/* En la opción 1 sera push que se encargará de ingresar los valores a el arreglo */
		if ( top == -1 ){
			printf("La pila esta vacia por el momento\n\n");

			/*comienzo a llenar los datos de la estructura, lleno los datos de uno en uno y luego
			de haber llenado un dato le pregunto al usuario que desea hacer, 

			Si esta entrando a esta parte es porque no hay valores entonces puedo ingresar valores en 
			la posición 0 del arreglo */
			cout << "Ingresa el identificador	: "; cin >> pila1[0].id;
			cout << "Ingresa el nombre 		: "; cin >> pila1[0].valor;
			/*en cada pasada de ciclo aumento en 1 el valor de top, esto hace que pueda tener el control de 
			cuantos valores se han ingresado y llenado*/
			top++;
			menu();
		}else{
			if ( top > 2 ) {
				printf("Ya llegaste al limite de los valores que puedes ingresar.\n");
				Sleep(2000);
				menu();
			}else {
				/*en el momento que ingrese acá, es porque el arreglo ya no esta vacío*/
				cout << "Ingresa el identificador no. "; cout << ( top + 2 );//
				cout << "	: "; cin >> pila1[ ( top + 1 ) ].id;//1 mas top para hacer el valor correcto del arreglo
				cout << "Ingresa el nombre no. "; cout << ( top + 2 ); 
				cout << "		: "; cin >> pila1[ ( top + 1 ) ].valor;
				/*en cada pasada de ciclo aumento en 1 el valor de top, esto hace que pueda tener el control de 
				cuantos valores se han ingresado y llenado*/
				top++;
				menu();
			}
		}
	}else
	if ( opcion == 2 ) {
		/* la opcion 2 contrendrá el pop que se encargará de sacar al elemento del arreglo, se esta trabajando
		como filo, esto quiere decir que el primero en entrar será el último en salir y el ultimo en entrar deberá
		ser el que se elimina del arreglo */
		if ( top == -1 ){
			printf("La pila en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menu();
		}else{
			/*si la pila no se encuentra vacía*/
			printf("\n\n");
			top--;//para reducir el tamaño de mi limite
			for (int i = 0; i <= top; i++ ) {
				pila1[ i ].id;
				pila1[ i ].valor;
			}
			printf("Se ha hecho pop en la pila actual.\n\n");
			menu ();
		}
	}else
	if ( opcion == 3 ) {
		/*la opcion 3 hará el pop trabajando como fifo ( first in first out )*/
		if ( top == -1 ){
			printf("La cola en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menu();
		}else{
			/*si la cola no se encuentra vacía*/
			printf("\n\n");
			bottom++;//para aumentar el valor del indice al cual esta apuntando la variable bottom
			for (int i = bottom; i <= top; i++ ) {
				pila1[ i ].id;
				pila1[ i ].valor;
			}
			printf("Se extrajo el dato de la cola.\n\n");
			menu ();
		}
	}else
	if ( opcion == 4 ) {
		/* En la opción 3 hago que se muestren los valores actuales de la pila
		en la variable top obtengo el valor de cuantos elementos tengo por ahora en mi arreglo */
		//lo primero que debo hacer es condicionar y si el top es igual a -1 quiere decir que la pila esta vacía
		if ( top == -1 ){
			printf("La pila en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menu();
		}else{
			/*si la pila no se encuentra vacía*/
			printf("\n\n");
			for (int i = bottom; i <= top; i++ ) {
				cout << (i + 1); cout << ". "; cout << pila1[ i ].id; cout << " | "; cout << pila1[ i ].valor; cout << endl;
			}
			printf("\n\n");
			menu ();
		}
	}else
	if ( opcion == 5 ) {
		/* en la opcion 3 saldrá del proceso actual y se cerrará la aplicación */
		system("cls");//limpio la pantalla
		printf("Asesiando todo proceso, espera un momento ;)........");
		Sleep(2000);//para que demore dos segundos en cerrar
		exit(0);//cierra el proceso
	}else {
		system("cls");
		menu ();
	}
}

int main(int argc, char const *argv[]) {
	menu ();

	getch();
	return 0;
}