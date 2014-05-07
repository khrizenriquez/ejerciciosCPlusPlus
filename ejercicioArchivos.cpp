/*	
	@autor: 		Khriz Enríquez
	@nombreApp:		colaArchivoBinario
	@descripción:	Ya existe un archivo binario que tiene 10 registros con una estructura de la 
					siguiente manera: 
					struct p {
						int valor1;
						int valor2;
					};.

	1.	Crear un procedimiento que lea el archivo y lo cargue a un arreglo de la siguiente manera:
		1.1 	Toma los 2 valores y los múltiplica entre ellos
		1.2		eL resultado de la multiplicación debe asignarlo en la posición del vector que 
				corresponde
	2.	Cree un procedimiento que muestre los valores del vector en pantalla
*/

#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//variables globales
FILE *fArchivo;
//estructuras
struct p {
	int valor1;
	int valor2;
} estructuraX;

/*procedimiento para cargar los datos del archivo a la estructura de datos*/
void cargandoDatos(){
	//lo primero que debo hacer es leer el archivo y cargar los datos
	if ( ( fArchivo = fopen( "ejercicioArchivos.dat", "rb" ) ) == NULL ) {
		printf("Te estan troleando y no quieren que trabajes en el archivo.\n");
	}else{

		while ( !feof( fArchivo ) ){

			fscanf( fArchivo, "%s %s", &estructuraX.valor1, &estructuraX.valor2 );
			
			printf( "valor 1: %s 	 valor 2: %s\n", &estructuraX.valor1, &estructuraX.valor2 );
		}
		fclose( fArchivo );
	}
}

//procedimiento para mostrar los valores en pantalla del vector acutal
void mostrandoDatos (){
	//se hara un ciclo para mostrar unicamente los valores
	for ( int i = 0; i < 10; i++ ) {
		
	}
}

int main( int argc, char const *argv[] ) {
	cargandoDatos();

	getch();
	return 0;
}