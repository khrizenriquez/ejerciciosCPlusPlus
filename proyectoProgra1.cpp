/*
	@autor: Khriz Enríquez khrizenriquez

	Crear un menú dinámico
		-Alta/creación de opciones
		-Modificación de opciones
		-Eliminación de opciones

	Ejecución del menú
		-Lectura del menú
		-Mostrar menú
		Ejecutar opciones

	Segun los 7 ejercicios que se han hecho se complementarán con este programa, los cuales son:
		Pilas
		Colas
		Recursividad
		Archivos secuenciales
		Archivos binarios
*/

/*
	para manejo de archivos en c++
	r: sólo lectura. El fichero debe existir.
	w: se abre para escritura, se crea un fichero nuevo o se sobrescribe si ya existe.
	a: añadir, se abre para escritura, el cursor se situa al final del fichero. Si el fichero no existe, se crea.
	r+: lectura y escritura. El fichero debe existir.
	w+: lectura y escritura, se crea un fichero nuevo o se sobrescribe si ya existe.
	a+: añadir, lectura y escritura, el cursor se situa al final del fichero. Si el fichero no existe, se crea.

	En cuanto a los valores permitidos para los bytes, se puede añadir otro carácter a la cadena de modo:
	t: modo texto. Normalmente es el modo por defecto. Se suele omitir.
	b: modo binario.

	http://c.conclase.net/ficheros/index.php
*/

/*
	La libreria conio.h es propia de borland y no es un estandar ( borland ya no tiene soporte y ya no es genial "Borland C++ 
	(abandonado, sustituido por C++Builder -> http://en.wikipedia.org/wiki/Borland" ) ) por eso hay que evitar usarla
*/
//#include "<conio.h>"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>//para usar el exit
#include <windows.h>//para usar el sleep

using namespace std;

/*	variables globales*/
char nombreUsuario[50];
int opcionMenuPrimario = 0;

/*	funciones y procedimientos*/
void menuDeOpciones();
void menuDinamico();
void menuPrincipal() {
	system("cls");
	printf("************************************************************\n");
	cout << "Guatemala " << endl;
	system("date /t");
	system("time /t");
	printf("\nPara poder tratarde de una mejor manera, indicame cual es tu nombre:\n\n\n");
	cout << "Tu nombre es ( no ingreses espacios ): ";cin >> nombreUsuario;

	for ( int i = 0; i <= 10; i++ ) {
		Sleep(500);
		printf(".");
	}

	printf("\nGenail %s entonces empecemos, solo espera un momento\n", nombreUsuario);
	printf("************************************************************\n");

	Sleep(5000);
	menuDeOpciones();
}

/*	función que nos servirá para poder cambiar el nombre al usuario, el parametro que recibe es el nombre*/
char* cambiandoNombre( char *nUsuario ){
	printf("Tu nombre actual es %s\n", nUsuario);
	cout << "Ingresa tu nuevo nombre: ";cin >> nUsuario;

	return nUsuario;
}

/*
	opciones del menu dinamico
*/
void agregandoOpcionMenuD() {
	FILE *fMenuD;
	if ( ( fMenuD = fopen( "menuDinamico.dat", "ab+" ) ) == NULL ) {
		printf("Algo extraño esta pasando, puede que te esten troleando :S\nO la radiacion no permite que uses esta aplicacion :(");
		printf("\nPor esa razon no podras guardar opciones al menu dinamico\n\n");
		Sleep( 5000 );
		menuDinamico();
	}else{
		char nombreOpcion[100];

		printf("\nIngresa el valor que colocaras en el menu dinamico: ");
		cin >> nombreOpcion;
		printf("\n\n");
		fprintf( fMenuD, "%s \n", nombreOpcion );
		fclose( fMenuD );
		printf("\n\n\nDatos guardados correctamente :).\n\n\n");
	}
	menuDinamico();
}
void editarOpcionMenuD(){
	FILE *fMenuD;
	if ( ( fMenuD = fopen( "menuDinamico.dat", "rb" ) ) == NULL ) {
		printf("Algo extraño esta pasando, puede que te esten troleando :S\nO la radiacion no permite que uses esta aplicacion :(");
		printf("\nPor esa razon no podras guardar opciones al menu dinamico\n\n");
		Sleep( 5000 );
		menuDinamico();
	}else {
		int contador = 0;
		char nombreOpcion[100];
		struct stMenuDinamico {
			char nombreOpcion[100];
		};
		//stMenuDinamico stMenuD[];
		printf("Las opciones que tienes son: \n\n");
		while( !feof( fMenuD ) ) {
			contador++;
			stMenuDinamico stMenuD[ contador ];
			fscanf( fMenuD, "%s", stMenuD[contador].nombreOpcion );
		}

		printf("%i en total\n", contador);
		//printf("%s valor del arreglo\n", stMenuD[ 2 ].nombreOpcion);
		/*struct stMenuDinamico {
			char nombreOpcion[100];
		}stMenuD[ contador ];
		for ( int i = 0; i < contador; ++i ) {
			fscanf( fMenuD, "%s", stMenuD[ i ].nombreOpcion );
			printf("%i. %s \n", i, stMenuD[ i ].nombreOpcion);
		}*/
	}
	//para cerrar el archivo
	fclose( fMenuD );
	printf("\n\n");
	menuDinamico();
}
void eliminandoOpcionMenuD(){}
void viendoOpcionMenuD(){
	FILE *fMenuD;

	if ( ( fMenuD = fopen( "menuDinamico.dat", "rb" ) ) == NULL ) {
		printf("Algo extraño esta pasando, puede que te esten troleando :S\nO la radiacion no permite que uses esta aplicacion :(");
		printf("\nPor esa razon no podras guardar opciones al menu dinamico\n\n");
		Sleep( 5000 );
		menuDinamico();
	}else {
		char nombreOpcion[100];
		int contador = 0;

		printf("Las opciones que tienes son: \n\n");
		while( !feof( fMenuD ) ) {
			contador++;
			fscanf( fMenuD, "%s", nombreOpcion );
			printf("%i. %s \n", contador, nombreOpcion);
		}
	}
	//para cerrar el archivo
	fclose( fMenuD );
	printf("\n\n");
	menuDinamico();
}

void menuDinamico(){
	int opcionMenuD;

	printf("*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-\n\n");
	printf("Esta es la opcion para el menu dinamico\n\n");
	printf("Puedes escoger cualquiera de las siguientes opciones:\n");
	printf("\n1. Crear una opcion en el menu dinamico\n");
	printf("\n2. Editar una opcion del menu dinamico\n");
	printf("\n3. Eliminar una opcion del menu dinamico\n");
	printf("\n4. Ver las opciones del menu\n");
	printf("\n5. Regresar al menu principal\n");
	printf("*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-\n\n");
	cin >> opcionMenuD;

	if ( opcionMenuD == 1 ){
		agregandoOpcionMenuD();
	}else
	if ( opcionMenuD == 2 ){
		editarOpcionMenuD();
	}else
	if ( opcionMenuD == 3 ){
		eliminandoOpcionMenuD();
	}else
	if ( opcionMenuD == 4 ){
		viendoOpcionMenuD();
	}else
	if ( opcionMenuD == 5 ){
		menuDeOpciones();
	}else{
		menuDeOpciones();
	}
}


/*	Menú de opciones predeterminadas*/
void menuPredeterminado(){
	int opcionMenuP;

	printf("*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-\n\n");
	printf("Esta es la opcion para el menu predeteminado\n\n");
	printf("Puedes escoger cualquiera de las siguientes opciones:\n");
	printf("\n1. Opciones de pilas\n");
	printf("\n2. Opciones de cola\n");
	printf("\n3. Recursividad\n");
	printf("\n4. Archivos secuenciales\n");
	printf("\n5. Archivos binarios\n");
	printf("\n6. Regresar al menu principal\n");
	printf("*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-\n\n");
	cin >> opcionMenuP;

	if ( opcionMenuP == 1 ){
	}else
	if ( opcionMenuP == 2 ){
	}else
	if ( opcionMenuP == 3 ){
	}else
	if ( opcionMenuP == 4 ){
	}else
	if ( opcionMenuP == 5 ){
	}else
	if ( opcionMenuP == 6 ){
		menuDeOpciones();
	}else{
		menuDeOpciones();
	}
}

void menuDeOpciones() {
	system( "cls" );
	printf("*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-\n\n");
	printf("Ahora si te damos la bienvenida de manera formal %s\n\n", nombreUsuario);
	printf("Puedes escoger cualquiera de las siguientes opciones:\n");
	printf("\n1. Menu dinamico\n");
	printf("\n2. Menu de opciones predeterminadas\n");
	printf("\n3. Cambiar mi nombre\n");
	printf("\n4. Salir\n");
	printf("*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-*+-\n\n");
	cin >> opcionMenuPrimario;
   /*
		validamos todas las opcioens ingresadas por el usuario
   */
	system( "cls" );
	if ( opcionMenuPrimario == 1 ) {
		menuDinamico();
	}else
	if ( opcionMenuPrimario == 2 ) {
		menuPredeterminado();
	}else
	if ( opcionMenuPrimario == 3 ) {
		printf("Genial! has cambiando tu nombre de usuario\ny ahora es %s\n", cambiandoNombre( nombreUsuario ));
		Sleep( 2000 );
		menuDeOpciones();
	}else
	if ( opcionMenuPrimario == 4 ) {
		printf("Espara un momento, estamos asesinando todo\n");
		for ( int i = 0; i <= 20; i++ ) {
			Sleep(200);
			printf(".");
		}
	exit( 0 );
	}else{
		menuDeOpciones();
	}
}

int main( int argc, char const *argv[] ) {
	menuPrincipal();

   /*
		para usar el cin.get de manera correcta debo colocar el cin.ignore

		http://stackoverflow.com/questions/8499816/cin-get-not-working
		http://www.cplusplus.com/reference/istream/istream/ignore/
   */
	cin.ignore(256,'\n');
	cin.get();
	return 0;
}