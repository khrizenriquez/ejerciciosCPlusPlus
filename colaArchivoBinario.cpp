/*
	@autor: 		Khriz Enríquez
	@nombreApp:		colaArchivoBinario
	@descripción:	Manejar una cola que tenga la opción de almancenar los datos en un archivo
					binario.

	El menú tendrá las opciones:
		-1. Agregar datos: agregará los datos a la cola creada
		-2. Eliminar datos de cola: eliminará el primer dato de la cola
		-3. Mostrar los datos que se encuentran actualmente en la cola
		-4. Guardar: guardará los datos de la estructura de datos en el archivo binario
		-5. Salir
*/

//	área de importación
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>//me sirve para el exit
#include <windows.h>//me sirve para el sleep

using namespace std;

//	área de definiciones

//	variables globales
//para saber cual es el valor maximo que tengo en mi estructura de datos
int top = -1;
//para saber cual es el indice de mi estructura de datos
int bottom = 0;
FILE *fArchivo;
struct datosArchivo{
	int id;
	char datos[50];
} dArchivo[10];
//	procedimiento para cargar los datos de un archivo binario a una estructura de datos y manipularlo como cola
void cargandoDatos (){
	/* 
		Se cargarán todos los datos de un archivo binario hacia una estructura 
		para poder manipularla, la opción q debe ir implicita para que cuando se abra la aplicación se
		obtengan los valores del archivo de una vez en la estructura de datos para manipularlo 
		
		para los modos de apertura de achvios http://www.chuidiang.com/clinux/ficheros/fichero-binario.php
		r o rb: Abre el fichero para lectura. El fichero debe existir o tendremos un error.
		w o wb. Abre el fichero para escribir en él. Puede o no existir. Si existe se machaca el contenido que hubiera. 
				Si no existe se crea.
		a o ab. Abre el fichero para añadirle datos al final. Respeta el contenido que tuviera.
		r+, rb+ o r+b. Abre el fichero para lectura y escritura (el + es el que indica que es para lectura 
				y escritura a la vez). El fichero debe existir y respeta el contenido, aunque si escribimos algo iremos 
				machacando datos.
		w+, wb+ o w+b. Abre el fichero para lectura y escritura. Crea el fichero si no existe y machaca el contenido si existe.
		a+, ab+ o a+b. Abre el fichero para lecturay y escritura. La escritura comenzará al final del fichero, respetando el contenido.

	*/
	if ( ( fArchivo = fopen( "colasArchivoBinario.dat", "ab+" ) ) == NULL ) {
		/* Si entra acá es xq ocurrio un error inesperado */
		printf("Te estan troleando y no quieren que abras la aplicacion.\n");
	}else{
		/*primero obtengo la información del archivo, luego eso se lo cargo a mi estructura de datos.
		La limitante que tengo es que mi estructura tiene una una capacidad maxima de 10 (es un arreglo de 10 posiciones)*/
		while ( !feof( fArchivo ) ) {
			if ( top < 8 ) {
				//printf( "%-15i%-15s\n", dArchivo[ bottom ].id, dArchivo[ bottom ].datos );
				cout << dArchivo[ bottom ].id; cout << endl;
				cout << dArchivo[ bottom ].datos;
				printf("%i%s", dArchivo[ bottom ].id, dArchivo[ bottom ].datos);
				fscanf( fArchivo, "%i%s", dArchivo[ bottom ].id, dArchivo[ bottom ].datos );
				top++;
				bottom++;
			}else{
				printf("Ya existen demasiados datos para ingresarlos a la estructura\n");
			}
		}
		fclose( fArchivo );//como buen desarrollador cierro el archivo luego de usarlo
		getch();
	}
}
//	procedimiento para el menú y sus opciones
void menu (){
	int opciones = 0;//será la variable que llevará el control de la opción que se presiona
	
	printf("***********************************************************************\n");
	printf("Bienvenido mega usuario, puedes escoger lo que desees de estas opciones\n");
	printf("1.	Agregar datos\n");
	printf("2.	Eliminar datos\n");
	printf("3.	Mostrar los datos actuales\n");
	printf("4.	Guardar\n");
	printf("5.	Salir\n");
	printf("***********************************************************************\n");

	cin >> opciones;

	if ( opciones == 1 ) {
		/* La opción 1 se encargará de agregar los datos a la cola */
		if ( top == -1 ){
			printf("No existen datos en este momento.\n\n");

			/*comienzo a llenar los datos de la estructura, lleno los datos de uno en uno y luego
			de haber llenado un dato le pregunto al usuario que desea hacer, 

			Si esta entrando a esta parte es porque no hay valores entonces puedo ingresar valores en 
			la posición 0 del arreglo */
			cout << "Ingresa el identificador	: "; cin >> dArchivo[0].id;
			cout << "Ingresa el nombre 		: "; cin >> dArchivo[0].datos;
			/*en cada pasada de ciclo aumento en 1 el valor de top, esto hace que pueda tener el control de 
			cuantos valores se han ingresado y llenado*/
			top++;
			menu();
		}else{
			if ( top > 8 ) {
				printf("Ya llegaste al limite de los valores que puedes ingresar.\n");
				Sleep(2000);
				menu();
			}else {
				/*en el momento que ingrese acá, es porque el arreglo ya no esta vacío*/
				cout << "Ingresa el identificador no. "; cout << ( top + 2 );//
				cout << "	: "; cin >> dArchivo[ ( top + 1 ) ].id;//1 mas top para hacer el valor correcto del arreglo
				cout << "Ingresa el nombre no. "; cout << ( top + 2 ); 
				cout << "		: "; cin >> dArchivo[ ( top + 1 ) ].datos;
				/*en cada pasada de ciclo aumento en 1 el valor de top, esto hace que pueda tener el control de 
				cuantos valores se han ingresado y llenado*/
				top++;
				menu();
			}
		}
	}else
	if ( opciones == 2 ) {
		/*la opción 2 se encargará de eliminar los datos de la cola actual siguiendo el principio fifo( first in first out )*/
		if ( top == -1 ){
			printf("La cola en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menu();
		}else{
			/*si la cola no se encuentra vacía*/
			printf("\n\n");
			bottom++;//para aumentar el valor del indice al cual esta apuntando la variable bottom
			for (int i = bottom; i <= top; i++ ) {
				dArchivo[ i ].id;
				dArchivo[ i ].datos;
			}
			printf("Se extrajo el dato de la cola.\n\n");
			menu ();
		}
	}else
	if ( opciones == 3 ) {
		/* La opción 3 mostrará los datos actuales que se encuentren dentro de la cola */
		if ( top == -1 ){
			printf("La cola en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menu();
		}else{
			/*si la cola no se encuentra vacía*/
			printf("\n\n");
			for (int i = bottom; i <= top; i++ ) {
				cout << (i + 1); cout << ". "; cout << dArchivo[ i ].id; cout << " | "; cout << dArchivo[ i ].datos; cout << endl;
			}
			printf("\n\n");
			menu ();
		}
	}else
	if ( opciones == 4 ) {
		/* La opción 4 guardará los datos que se encuentren en la estructura de datos a el archivo binario */
		if ( top == -1 ){
			printf("La cola en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menu();
		}else{
			/*si la cola no se encuentra vacía*/
			if ( ( fArchivo = fopen( "colasArchivoBinario.dat", "ab+" ) ) == NULL ) {
				/* Si entra acá es xq ocurrio un error inesperado */
				printf("Te estan troleando y no quieren que abras la aplicacion.\n");
			}else{
				/*primero obtengo la información del archivo, luego eso se lo cargo a mi estructura de datos.
				La limitante que tengo es que mi estructura tiene una una capacidad maxima de 10 (es un arreglo de 10 posiciones)*/
				printf("\n\n");
				for (int i = bottom; i <= top; i++ ) {
					cout << (i + 1); cout << ". "; cout << dArchivo[ i ].id; cout << " | "; cout << dArchivo[ i ].datos; cout << endl;
					fprintf( fArchivo, "%i %s\n", dArchivo[i].id, dArchivo[i].datos );
				}
				fclose( fArchivo );
				printf("\n\n");
			}
		}
		menu ();
	}else
	if ( opciones == 5 ) {
		/* Saldrá de la aplicación */
		system("cls");
		printf("Matando todos los procesos actuales... espera un momento\n");
		Sleep(5000);//espero 5 segundos
		exit(0);
	}else{
		/*Si la opción que presiona no esta dentro del menu lo mando al mismo menú de nuevo*/
		menu ();
	}
}

int main(int argc, char const *argv[])
{
	cargandoDatos ();//primero cargo los datos del archivo binario a la estructura de datos
	menu ();//escucho las opciones que presione el usuario

	getch();
	return 0;
}