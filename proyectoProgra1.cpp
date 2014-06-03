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
	int contador = 0, top = 20, opcionEditar;
	char valorMenu[100];
   /*	lo ideal es tener una estructura de tamaño indefinido*/
	struct datosEditar {
		char datosMenu[100];
	} dEditar[ top ];

	if ( ( fMenuD = fopen( "menuDinamico.dat", "rb+" ) ) == NULL ) {
		printf("Algo extraño esta pasando, puede que te esten troleando :S\nO la radiacion no permite que uses esta aplicacion :(");
		printf("\nPor esa razon no podras guardar opciones al menu dinamico\n\n");
		Sleep( 5000 );
		menuDinamico();
	}else {
		printf("Estos son los valores que tienes en el menu\n");
		while( !feof( fMenuD ) ) {
			contador++;
			if ( contador < top ) {
				fscanf( fMenuD, "%s \n", dEditar[ contador ].datosMenu );
				printf( "%i %s \n",  contador , dEditar[ contador ].datosMenu );
			}
		}
	}
	//para cerrar el archivo
	fclose( fMenuD );

   /*	en esta parte pregunto que opcion desea eliminar el usaurio*/
	printf("\n\nQue numero de opcion deseas editar? ");
	cin >> opcionEditar;
	printf("Cual sera el nuevo valor de esta opcion del menu? ");
	cin >> valorMenu;

	if ( opcionEditar >= top || opcionEditar <= 0 ) {
		printf("Lo siento pero el valor que ingresaste en el menu no es valido.\n");
		editarOpcionMenuD();
	}else
	if ( opcionEditar > contador ) {
		printf("El valor que ingresaste no aparece en el menu de opciones que se te muestran :(\n");
		editarOpcionMenuD();
	}else {
		if ( ( fMenuD = fopen( "menuDinamico.dat", "wb+" ) ) == NULL ) {
			printf("Algo extraño esta pasando, puede que te esten troleando :S\nO la radiacion no permite que uses esta aplicacion :(");
			printf("\nPor esa razon no podras guardar opciones al menu dinamico\n\n");
			Sleep( 5000 );
			menuDinamico();
		}else {
			for ( int i = 1; i <= contador; i++ ) {
			   /* 		si el valor que estoy leyendo en la iteración es diferente al que escribio el usuario proceso a eliminarlo*/
				if ( i == opcionEditar ) {
					fprintf( fMenuD, "%s \n", valorMenu );
				}else{
					fprintf( fMenuD, "%s \n", dEditar[ i ].datosMenu );
				}
			}
			printf("\n\nSe ha cambiado con exito el nombre :)\n\n");
		}
	}
	//para cerrar el archivo
	fclose( fMenuD );
	printf("\n\n");
	menuDinamico();
}
void eliminandoOpcionMenuD(){
	FILE *fMenuD;
	int contador = 0, top = 20;
	int opcionEliminar;
   /*	lo ideal es tener una estructura de tamaño indefinido*/
	struct datosEditar {
		char datosMenu[100];
	} dEditar[ top ];

	if ( ( fMenuD = fopen( "menuDinamico.dat", "rb+" ) ) == NULL ) {
		printf("Algo extraño esta pasando, puede que te esten troleando :S\nO la radiacion no permite que uses esta aplicacion :(");
		printf("\nPor esa razon no podras guardar opciones al menu dinamico\n\n");
		Sleep( 5000 );
		menuDinamico();
	}else {
		printf("Estos son los valores que tienes en el menu\n");
		while( !feof( fMenuD ) ) {
			contador++;
			if ( contador < top ) {
				fscanf( fMenuD, "%s \n", dEditar[ contador ].datosMenu );
				printf( "%i %s \n",  contador , dEditar[ contador ].datosMenu );
			}
		}
	}
	//para cerrar el archivo
	fclose( fMenuD );

   /*	en esta parte pregunto que opcion desea eliminar el usaurio*/
	printf("\n\nQue numero de opcion deseas eliminar? ");
	cin >> opcionEliminar;

	if ( opcionEliminar >= top || opcionEliminar <= 0 ) {
		printf("Lo siento pero el valor que ingresaste en el menu no es valido.\n");
		editarOpcionMenuD();
	}else
	if ( opcionEliminar > contador ) {
		printf("El valor que ingresaste no aparece en el menu de opciones que se te muestran :(\n");
		editarOpcionMenuD();
	}else {
		if ( ( fMenuD = fopen( "menuDinamico.dat", "wb+" ) ) == NULL ) {
			printf("Algo extraño esta pasando, puede que te esten troleando :S\nO la radiacion no permite que uses esta aplicacion :(");
			printf("\nPor esa razon no podras guardar opciones al menu dinamico\n\n");
			Sleep( 5000 );
			menuDinamico();
		}else {
			for ( int i = 1; i <= contador; i++ ) {
				/* 	si el valor que estoy leyendo en la iteración es diferente al que escribio el usuario proceso a eliminarlo*/
				if ( i != opcionEliminar ) {
					fprintf( fMenuD, "%s \n", dEditar[ i ].datosMenu );
				}
			}
			printf("\n\nSe ha eliminado con exito :)\n\n");
		}
	}
	//para cerrar el archivo
	fclose( fMenuD );
	printf("\n\n");
	menuDinamico();
}
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
			fscanf( fMenuD, "%s ", nombreOpcion );
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

/*	procedimientos y funciones para el menu de opciones predeterminadas*/
int fibonacci( int n ) {
	/*	fuente: http://programavideojuegos.blogspot.com/2013/05/sucesion-de-fibonacci-en-c.html*/
	if ( n > 2 )
		return fibonacci( n - 1 ) + fibonacci( n - 2 );
	else if ( n == 2 )
		return 1;
	else if ( n == 1 )
		return 1;
	else if ( n == 0 )
		return 0;
}

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
		system( "cls" );

		/*	fuente: http://programavideojuegos.blogspot.com/2013/05/sucesion-de-fibonacci-en-c.html*/
		printf("%s para este ejemplo de recursividad se trabajara con la serie fibonacci\n\n");
		printf("La sucesion de Fibonacci es una sucesion infinita de numeros en los que cada uno de ellos es el resultado de la suma de sus dos inmediatamente anteriores. La sucesion comienza tal que asi: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987..., estos son los numeros iterando hasta 20 veces:\n\n\n", nombreUsuario);
		Sleep( 2000 );
		int num;
		for ( num=0; num<=20; num++ ) {
			printf("%d   ", fibonacci(num) );
		}
		printf("\n\n");
		menuPredeterminado();
	}else
	if ( opcionMenuP == 4 ){
		system( "cls" );

		printf("Hey %s, te cuento que para el ejemplo de archivos secuenciales se creara o sobre escribira un archivo con los datos de un texto Lorem para efecto de este ejemplo, luego de crearce el archivo se guardaran de un texto Lorem en el y de manera imediata se leeran y mostraran en pantalla.\n", nombreUsuario );
		FILE *fArchivoSecuencial;
		if ( ( fArchivoSecuencial =  fopen( "fArchivoSecuencial.dat", "wb+" ) ) == NULL ) {
			printf("Algo extraño esta pasando, puede que te esten troleando :S\nO la radiacion no permite que uses esta aplicacion :(");
			printf("\nPor esa razon no podras guardar opciones al menu dinamico\n\n");
			Sleep( 5000 );
			menuPredeterminado();
		}else{
			/*for ( int i = 0; i <= 50; i++ ) {
				fprintf( fArchivoSecuencial, "%i \n", i );
			}*/
			fprintf( fArchivoSecuencial, "%s \n", "Lorem ipsum dolor sit amet, consectetur adipisicing elit. Excepturi, recusandae nam magnam quam nihil eius soluta quae expedita illo accusamus commodi explicabo sapiente sit deleniti labore fugiat natus inventore laboriosam." );
			printf("\n\n");
			fclose( fArchivoSecuencial );
			printf("\n\n\nDatos guardados correctamente :).\n\n\n");
		}
		printf("Los datos guardados son: \n");

		if ( ( fArchivoSecuencial = fopen( "fArchivoSecuencial.dat", "rb+" ) ) == NULL ) {
			printf("Algo extraño esta pasando, puede que te esten troleando :S\nO la radiacion no permite que uses esta aplicacion :(");
			printf("\nPor esa razon no podras guardar opciones al menu dinamico\n\n");
			Sleep( 5000 );
			menuPredeterminado();
		}else{
			char datosArchivoSec[50];
			printf("Chuta\n");
			while( !feof( fArchivoSecuencial ) ) {
				fscanf( fArchivoSecuencial, "%s \n", datosArchivoSec );
				printf("%s ", datosArchivoSec );
			}
		}
		printf("\n\n");
		fclose( fArchivoSecuencial );
		printf("\n\n\nDatos mostrados correctamente :).\n\n\n");
		menuPredeterminado();
	}else
	if ( opcionMenuP == 5 ){
	}else
	if ( opcionMenuP == 6 ){
		menuPredeterminado();
	}else{
		menuPredeterminado();
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
		printf("hasta luego %s\n", nombreUsuario);
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