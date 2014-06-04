/*
	**********************************************************************************************************
	**@autor: 			Khriz Enríquez @khrizenriquez
	**
	**@Descripción: 	Crear un menú dinámico con las siguientes opciones
	**						Alta/creación de opciones, Modificación de opciones, Eliminación de opciones
	**
	**					Ejecución del menú: Lectura del menú, Mostrar menú, Ejecutar opciones
	**
	**Segun los 7 ejercicios que se han hecho se complementarán con este programa, los cuales son:
	**	Pilas, Colas, Recursividad, Archivos secuenciales, Archivos binarios
	**********************************************************************************************************

	Para manejo de archivos en c++
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
/*********************************************************************************************
										variables globales
**********************************************************************************************/
char nombreUsuario[50];
int opcionMenuPrimario = 0;
/*cuando una pila esta vacia se coloca el valor -1 por estandar https://www.youtube.com/watch?v=yE0aMD5IueE*/
int top = -1;
/*el bottom tendrá el valor del primer arreglo*/
int bottom = 0;
/*	tendrá 10 posiciones la pila, no puedo generar un elemento como un JSon para que reciba varios valores
entonces lo mas cernano será una pila en forma de arreglo*/
struct pila{
	int id;//identificador del elemento de la pila
	char valor[50];
} pila1[ 10 ];
int topBinario = -1;
//para saber cual es el indice de mi estructura de datos
int bottomBinario = 0;
FILE *fArchivo;
struct datosArchivo{
	int id;
	char datos[50];
} dArchivo[10];
/**********************************************************************************************	
									funciones y procedimientos
**********************************************************************************************/
void menuDeOpciones();
void menuDinamico();
void menuPredeterminado();
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

/*	Menú de las pilas*/
void menuPilas () {
	//	limpio la pantalla de cualquier cosa que tenga escrita en ella
	int opcion = 0;
	printf("*******************************************\n");
	printf("El programa de pilas esta relacionado con el de colas\n\n");
	printf("Programa de pilas\nBienvenido super usuario %s que opcion deseas usar:\n\n", nombreUsuario);
	printf("1.	Push\n");
	printf("2.	Pop\n");
	printf("3.	Mostrar la pila actual\n");
	printf("4.	Regresar al menu anterior\n");
	printf("*******************************************\n\n");

	cin >> opcion;

	if ( opcion == 1 ) {
		/* En la opción 1 sera push que se encargará de ingresar los valores a el arreglo */
		if ( top == -1 ){
			printf("La pila esta vacia por el momento\n\n");
			bottom = 0;

			/*comienzo a llenar los datos de la estructura, lleno los datos de uno en uno y luego
			de haber llenado un dato le pregunto al usuario que desea hacer, 

			Si esta entrando a esta parte es porque no hay valores entonces puedo ingresar valores en 
			la posición 0 del arreglo */
			cout << "Ingresa el identificador	: "; cin >> pila1[0].id;
			cout << "Ingresa el nombre 		: "; cin >> pila1[0].valor;
			/*en cada pasada de ciclo aumento en 1 el valor de top, esto hace que pueda tener el control de 
			cuantos valores se han ingresado y llenado*/
			top++;
			menuPilas();
		}else{
			if ( top > 7 ) {
				printf("Ya llegaste al limite de los valores que puedes ingresar.\n");
				Sleep(2000);
				menuPilas();
			}else {
				/*en el momento que ingrese acá, es porque el arreglo ya no esta vacío*/
				cout << "Ingresa el identificador no. "; cout << ( top + 2 );//
				cout << "	: "; cin >> pila1[ ( top + 1 ) ].id;//1 mas top para hacer el valor correcto del arreglo
				cout << "Ingresa el nombre no. "; cout << ( top + 2 );
				cout << "		: "; cin >> pila1[ ( top + 1 ) ].valor;
				/*en cada pasada de ciclo aumento en 1 el valor de top, esto hace que pueda tener el control de 
				cuantos valores se han ingresado y llenado*/
				top++;
				menuPilas();
			}
		}
	}else
	if ( opcion == 2 ) {
		/* la opcion 2 contrendrá el pop que se encargará de sacar al elemento del arreglo, se esta trabajando
		como filo ( first in last out ), esto quiere decir que el primero en entrar será el último en salir y el ultimo en entrar deberá
		ser el que se elimina del arreglo */
		if ( top == -1 ){
			printf("La pila en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menuPilas();
		}else{
			/*si la pila no se encuentra vacía*/
			printf("\n\n");
			top--;//para reducir el tamaño de mi limite
			for (int i = bottom; i <= top; i++ ) {
				pila1[ i ].id;
				pila1[ i ].valor;
			}
			printf("Se ha hecho pop en la pila actual.\n\n");
			menuPilas ();
		}
	}else
	if ( opcion == 3 ) {
		/* En la opción 3 hago que se muestren los valores actuales de la pila
		en la variable top obtengo el valor de cuantos elementos tengo por ahora en mi arreglo */
		//lo primero que debo hacer es condicionar y si el top es igual a -1 quiere decir que la pila esta vacía
		if ( top == -1 ){
			printf("La pila en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menuPilas();
		}else{
			system("cls");
			/*si la pila no se encuentra vacía*/
			printf("\n\nLos valores actuales de la pila son:\n\n");
			for (int i = bottom; i <= top; i++ ) {
				cout << (i + 1); cout << ". "; cout << pila1[ i ].id; cout << " | "; cout << pila1[ i ].valor; cout << endl;
			}
			printf("\n\n");
			menuPilas ();
		}
	}else
	if ( opcion == 4 ) {
		/* en la opcion 3 saldrá del proceso actual y se cerrará la aplicación */
		system("cls");//limpio la pantalla
		menuPredeterminado ();
	}else {
		system("cls");
		menuPilas();
	}
}

/*	Menú de colas*/
void menuColas () {
	//	limpio la pantalla de cualquier cosa que tenga escrita en ella
	int opcion = 0;
	printf("*******************************************\n");
	printf("El programa de Colas esta relacionado con el de pilas\n\n");
	printf("Programa de colas\nBienvenido super usuario %s que opcion deseas usar:\n\n", nombreUsuario);
	printf("1.	Agregar datos a la cola\n");
	printf("2.	Eliminar dato de la cola\n");
	printf("3.	Mostrar la cola actual\n");
	printf("4.	Regresar al menu anterior\n");
	printf("*******************************************\n\n");

	cin >> opcion;

	if ( opcion == 1 ) {
		/* En la opción 1 sera push que se encargará de ingresar los valores a el arreglo */
		if ( top == -1 ){
			printf("La cola esta vacia por el momento\n\n");

			bottom = 0;

			/*comienzo a llenar los datos de la estructura, lleno los datos de uno en uno y luego
			de haber llenado un dato le pregunto al usuario que desea hacer, 

			Si esta entrando a esta parte es porque no hay valores entonces puedo ingresar valores en 
			la posición 0 del arreglo */
			cout << "Ingresa el identificador	: "; cin >> pila1[0].id;
			cout << "Ingresa el nombre 		: "; cin >> pila1[0].valor;
			/*en cada pasada de ciclo aumento en 1 el valor de top, esto hace que pueda tener el control de 
			cuantos valores se han ingresado y llenado*/
			top++;
			menuColas();
		}else{
			if ( top > 7 ) {
				printf("Vacia la cola para poder ingresar valores.\n");
				Sleep(2000);
				menuColas();
			}else {
				/*en el momento que ingrese acá, es porque el arreglo ya no esta vacío*/
				cout << "Ingresa el identificador no. "; cout << ( top + 2 );//
				cout << "	: "; cin >> pila1[ ( top + 1 ) ].id;//1 mas top para hacer el valor correcto del arreglo
				cout << "Ingresa el nombre no. "; cout << ( top + 2 ); 
				cout << "		: "; cin >> pila1[ ( top + 1 ) ].valor;
				/*en cada pasada de ciclo aumento en 1 el valor de top, esto hace que pueda tener el control de 
				cuantos valores se han ingresado y llenado*/
				top++;
				menuColas();
			}
		}
	}else
	if ( opcion == 2 ) {
		/*la opcion 2 hará el pop trabajando como fifo ( first in first out )*/
		if ( top == -1 ){
			printf("La cola en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menuColas();
		}else{
			/*si la cola no se encuentra vacía*/
			printf("\n\n");
			bottom++;//para aumentar el valor del indice al cual esta apuntando la variable bottom
			for ( int i = bottom; i <= top; i++ ) {
				pila1[ i ].id;
				pila1[ i ].valor;
			}
			printf("Se extrajo el dato de la cola.\n\n");
			menuColas ();
		}
	}else
	if ( opcion == 3 ) {
		/* En la opción 3 hago que se muestren los valores actuales de la pila
		en la variable top obtengo el valor de cuantos elementos tengo por ahora en mi arreglo */
		//lo primero que debo hacer es condicionar y si el top es igual a -1 quiere decir que la pila esta vacía
		if ( top == -1 ){
			printf("La cola en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menuColas();
		}else{
			system("cls");
			/*si la cola no se encuentra vacía*/
			printf("\n\nLos valores actuales de la cola son:\n\n");
			for (int i = bottom; i <= top; i++ ) {
				cout << (i + 1); cout << ". "; cout << pila1[ i ].id; cout << " | "; cout << pila1[ i ].valor; cout << endl;
			}
			printf("\n\n");
			menuColas ();
		}
	}else
	if ( opcion == 4 ) {
		/* en la opcion 3 saldrá del proceso actual y se cerrará la aplicación */
		system("cls");//limpio la pantalla
		menuPredeterminado();
	}else {
		system("cls");
		menuColas();
	}
}

/*	Menú de archivos binarios*/
void menuArchivosB (){
	int opciones = 0;//será la variable que llevará el control de la opción que se presiona
	
	printf("***********************************************************************\n");
	printf("Bienvenido mega usuario %s, puedes escoger lo que desees de estas opciones\n", nombreUsuario);
	printf("1.	Agregar datos\n");
	printf("2.	Eliminar datos\n");
	printf("3.	Mostrar los datos actuales\n");
	printf("4.	Guardar\n");
	printf("5.	Salir\n");
	printf("***********************************************************************\n");

	cin >> opciones;

	if ( opciones == 1 ) {
		/* La opción 1 se encargará de agregar los datos a la cola */
		if ( topBinario == -1 ){
			printf("No existen datos en este momento.\n\n");

			/*comienzo a llenar los datos de la estructura, lleno los datos de uno en uno y luego
			de haber llenado un dato le pregunto al usuario que desea hacer, 

			Si esta entrando a esta parte es porque no hay valores entonces puedo ingresar valores en 
			la posición 0 del arreglo */
			cout << "Ingresa el identificador	: "; cin >> dArchivo[0].id;
			cout << "Ingresa el nombre 		: "; cin >> dArchivo[0].datos;
			/*en cada pasada de ciclo aumento en 1 el valor de top, esto hace que pueda tener el control de 
			cuantos valores se han ingresado y llenado*/
			topBinario++;
			menuArchivosB();
		}else{
			if ( topBinario > 8 ) {
				printf("Ya llegaste al limite de los valores que puedes ingresar.\n");
				Sleep(2000);
				menuArchivosB();
			}else {
				/*en el momento que ingrese acá, es porque el arreglo ya no esta vacío*/
				cout << "Ingresa el identificador no. "; cout << ( topBinario + 2 );//
				cout << "	: "; cin >> dArchivo[ ( topBinario + 1 ) ].id;//1 mas top para hacer el valor correcto del arreglo
				cout << "Ingresa el nombre no. "; cout << ( topBinario + 2 ); 
				cout << "		: "; cin >> dArchivo[ ( topBinario + 1 ) ].datos;
				/*en cada pasada de ciclo aumento en 1 el valor de top, esto hace que pueda tener el control de 
				cuantos valores se han ingresado y llenado*/
				topBinario++;
				menuArchivosB();
			}
		}
	}else
	if ( opciones == 2 ) {
		/*la opción 2 se encargará de eliminar los datos de la cola actual siguiendo el principio fifo( first in first out )*/
		if ( topBinario == -1 ){
			printf("La cola en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menuArchivosB();
		}else{
			/*si la cola no se encuentra vacía*/
			printf("\n\n");
			bottom++;//para aumentar el valor del indice al cual esta apuntando la variable bottom
			for (int i = bottom; i <= topBinario; i++ ) {
				dArchivo[ i ].id;
				dArchivo[ i ].datos;
			}
			printf("Se extrajo el dato de la cola.\n\n");
			menuArchivosB ();
		}
	}else
	if ( opciones == 3 ) {
		/* La opción 3 mostrará los datos actuales que se encuentren dentro de la cola */
		if ( topBinario == -1 ){
			printf("La cola en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menuArchivosB();
		}else{
			/*si la cola no se encuentra vacía*/
			printf("\n\n");
			for (int i = bottom; i <= topBinario; i++ ) {
				cout << (i + 1); cout << ". "; cout << dArchivo[ i ].id; cout << " | "; cout << dArchivo[ i ].datos; cout << endl;
			}
			printf("\n\n");
			menuArchivosB ();
		}
	}else
	if ( opciones == 4 ) {
		/* La opción 4 guardará los datos que se encuentren en la estructura de datos a el archivo binario */
		if ( topBinario == -1 ){
			printf("La cola en este momento se encuentra vacia, en 5 segundos \nregresaras al menu principal\n\n");
			Sleep(5000);
			menuArchivosB();
		}else{
			/*si la cola no se encuentra vacía*/
			if ( ( fArchivo = fopen( "colasArchivoBinario.dat", "ab+" ) ) == NULL ) {
				/* Si entra acá es xq ocurrio un error inesperado */
				printf("Te estan troleando y no quieren que abras la aplicacion.\n");
			}else{
				/*primero obtengo la información del archivo, luego eso se lo cargo a mi estructura de datos.
				La limitante que tengo es que mi estructura tiene una una capacidad maxima de 10 (es un arreglo de 10 posiciones)*/
				printf("\n\n");
				for (int i = bottom; i <= topBinario; i++ ) {
					fprintf( fArchivo, "%i %s\n", dArchivo[i].id, dArchivo[i].datos );
				}
				fclose( fArchivo );
				printf("Datos guardados en el archivo.\n\n");
			}
		}
		menuArchivosB ();
	}else
	if ( opciones == 5 ) {
		/* Saldrá de la aplicación */
		system("cls");
		menuPredeterminado();
	}else{
		/*Si la opción que presiona no esta dentro del menu lo mando al mismo menú de nuevo*/
		menuArchivosB ();
	}
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
		menuPilas ();
	}else
	if ( opcionMenuP == 2 ){
		menuColas ();
	}else
	if ( opcionMenuP == 3 ){
		system( "cls" );

		/*	fuente: http://programavideojuegos.blogspot.com/2013/05/sucesion-de-fibonacci-en-c.html*/
		printf("Hey %s para este ejemplo de recursividad se trabajara con la serie fibonacci\n\n");
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
		if ( ( fArchivoSecuencial =  fopen( "fArchivoSecuencial.txt", "wt+" ) ) == NULL ) {
			printf("Algo extraño esta pasando, puede que te esten troleando :S\nO la radiacion no permite que uses esta aplicacion :(");
			printf("\nPor esa razon no podras guardar opciones al menu dinamico\n\n");
			Sleep( 5000 );
			menuPredeterminado();
		}else{
			fprintf( fArchivoSecuencial, "%s \n", "Lorem ipsum dolor sit amet, consectetur adipisicing elit. Excepturi, recusandae nam magnam quam nihil eius soluta quae expedita illo accusamus commodi explicabo sapiente sit deleniti labore fugiat natus inventore laboriosam." );
			printf("\n\n");
			fclose( fArchivoSecuencial );
			printf("\n\n\nDatos guardados correctamente :).\n\n\n");
		}
		printf("Los datos guardados son: \n");

		if ( ( fArchivoSecuencial = fopen( "fArchivoSecuencial.txt", "rt+" ) ) == NULL ) {
			printf("Algo extraño esta pasando, puede que te esten troleando :S\nO la radiacion no permite que uses esta aplicacion :(");
			printf("\nPor esa razon no podras guardar opciones al menu dinamico\n\n");
			Sleep( 5000 );
			menuPredeterminado();
		}else{
			char datosArchivoSec[50];
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
		menuArchivosB();
	}else
	if ( opcionMenuP == 6 ){
		menuDeOpciones();
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