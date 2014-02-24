/*Khriz Enríquez @khrizenriquez

Programa que muestra 2 opciones, ingresar estudiantes y hacer búsqueda por estudiantes.

El usuario debera indicar cuantos estudiantes quiere ingresar y la aplicación deberá pedir 10 datos del usuario, guardar esa información en un archivo de texto,
con la información obtenida se puede buscar en base a 3 filtros de busqueda dentro del archivo y mostrarla en pantalla*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>//me permite usar el exit
#include <windows.h>//para poder usar el sleep
#include <iostream>
#include <fstream>

using namespace std;

/*declaracion de variables globales*/
int cantidadAlumnos, opcion;
char strNombre[50], strApellido[50], strDepartamento[50], strMunicipio[50], strUniversidad[50], strCarrera[50], strFacultad[50], strColor[30];
int edad, noCarne;
FILE *fArchivo;//coloco el * xq necesito el puntero

void ciclo();//funcion principal que donde se ejecutara el ingreso y la busqueda de valores
void menuPrincipal();//menu que le mostrara las opciones al usuario de ingresar datos o buscar por datos
void menuBusqueda();//menu para cuando se generen las búsquedas
void procesoBusqueda();//hara todo respecto a las búsquedas para el alumno

//area de estructuras
struct Alumno{
	int carne;
	char nombre[50], apellido[50], universidad[50], facultad[50], carrera[50], departamento[50], municipio[50];
	int edad;
	char colorFavorito[30];
} alumno;

int main(int argc, char const *argv[])
{
	ciclo();

	getch();
	return 0;
}

void ciclo()
{
	opcion = 0;//inicializo el valor de opcion cada vez que se ejecuta esta funcion

	menuPrincipal();//para mostrar el menu o encabezado donde indica que desea hacer el usuario
	cout << "Que opcion deseas usar: ";cin >> opcion;
	/*con 1 indico que seleccionara el ingreso de la información de los alumnos
	con 2 sera para hacer la busqueda de los alumnos
	si es un valor que no es 1 o 2 y es numerico la funcion sera recursiva
	si es un valor que es alfanumerico tronara la aplicacion*/
	if (opcion == 1)
	{
		cout << "\nIngresaras 10 datos por cada alumno, por esa razon no ingreses demasiados alumnos para que no exista problema.\n\n";
		cout << "Cuantos alumnos desea ingresar: "; cin >> cantidadAlumnos;
		
		if ((fArchivo = fopen("busquedaDatos1.dat", "w+")) == NULL)
		{
			printf("Lo sentimos, pero el sistema operativo te esta troleando y no deja crear el archivo :(\n");
		}else
		{
			//debo ingresar la cantidad de alumnos que el usuario indico
			for (int i = 0; i < cantidadAlumnos; i++)
			{
				cout << "Alumno " << (i + 1) << " de " << cantidadAlumnos << "\n\n";
				//el usuario llena los 10 valores para cada alumno
				/*los valores que se pediran para que el usuario ingrese son:

				número de carné, nombre del alumno, apellido del alumno, edad, Facultad donde estudia, carrera universitaria que estudia, universidad donde estudia, departamento, municipio, direccion, color favorito*/
				cout << "1. Numero de carne: ";cin >> noCarne;cout << "\n";

				cout << "2. Nombre: ";cin >> strNombre;cout << "\n";

				cout << "3. Apellidos: ";cin >> strApellido;cout << "\n";

				cout << "4. " << strNombre << " en que Universidad estudias: ";cin >> strUniversidad;cout << "\n";

				cout << "5. " << strNombre << " en que facultad de ";cout << strUniversidad << " estas: ";cin >> strFacultad;cout << "\n";

				cout << "6. " << strNombre << " que carrera estudias en la facultdad de ";cout << strFacultad << " : ";cin >> strCarrera;cout << "\n";
				
				cout << "7. " << strNombre << " en que departamento vives: ";cin >> strDepartamento;cout << "\n";
				
				cout << "8. " << strNombre << " en que municipio de " << strDepartamento << " estas: ";cin >> strMunicipio;cout << "\n";
				
				cout << "9. " << strNombre << " cual es tu edad: ";cin >> edad;cout << "\n";
				
				cout << "10. " << strNombre << " cual es tu color favorito: ";cin >> strColor;cout << "\n";

				cout << "x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-";

				fprintf(fArchivo, "%i %s %s %s %s %s %s %s %i %s\n", noCarne, strNombre, strApellido, strUniversidad, strFacultad, strCarrera, strDepartamento, strMunicipio, edad, strColor);
				//condiciono para crear el archivo si no existe y llenarlo con los valores que obtuve
			}			
			fclose(fArchivo);
		}
		ciclo();//lo hago recursivo para que pregunte de nuevo que desea hacer el usuario
	}else
		if (opcion == 2)
		{
			procesoBusqueda();			
		}else
			if (opcion == 3)
			{
				cout << "Gracias por usar mi aplicacion :D";
				Sleep(1000);//para que demore un segundo en cerrar
				exit(0);//cierra el proceso
			}else
			{
				ciclo();//llamo a la misma funcion para que sea recursiva y vuelva a pedir los valores
			}

}

void menuPrincipal()
{
	for (int i = 0; i < 40; i++)
	{
		cout << "x-";
	}
	cout << "\nBienvenido\nSelecciona una opcion,\nPresiona  1  para ingresar un nuevo estudiante, \nPresiona  2  para realizar una busqueda del usuario, \nPresiona  3  para cerrar la aplicacion. \n\nCUANDO SELECCIONE UNA OPCION PRESIONE ENTER\n\n";
	for (int i = 0; i < 40; i++)
	{
		cout << "x-";
	}
}

void menuBusqueda()
{
	for (int i = 0; i < 40; i++)
	{
		cout << "|.";
	}
	cout << "\nPuedes generar busquedas en base a 3 filtros diferentes:";
	cout << "\nPresiona  1  por el numero de carne del alumno (Ejemplo: 1)";
	cout << "\nPresiona  2  por el nombre del alumno (Ejemplo: Khriz)";
	cout << "\nPresiona  3  por la universidad del alumno (Ejemplo: Umg)";
	cout << "\nPresiona  4  para salir al menu principal\n\n";
	for (int i = 0; i < 40; i++)
	{
		cout << "|.";
	}
}

//el proceso de busqueda aún no sirve
void procesoBusqueda()
{
	/*Cuando el usuario ingrese a esta opción sera para generar la busqueda en base a:
	opcion 1: noCarne
	opcion 2: nombre
	opcion 3: universidad
	opcion 4: salir*/
	menuBusqueda();
	cout << "Que opcion deseas usar: ";cin >> opcion;//uso la misma variable de opcion para escuchar que oprime el usuario
	if (opcion == 1)
	{
		//la búsqueda se realizara por el numero de carne que tenga el alumno
		cout << "Ingrese el numero de carne que desea buscar: ";cin >> opcion;
		if ((fArchivo = fopen("busquedaDatos1.dat", "a+")) == NULL)
		{
			cerr << "No esta el archivo que buscas";
		}else
		{
			//el 1 donde se compara hace referencia a true
			while(fread(&alumno, sizeof(unsigned int), 1, fArchivo) == 1)
			{
				// mostrando estructura buscada
				cout << alumno.carne << "\n";
				cout << opcion << "\n";
				/*cout << alumno.nombre;
				cout << alumno.apellido;
				cout << alumno.universidad;
				cout << alumno.facultad;
				cout << alumno.carrera;
				cout << alumno.departamento;
				cout << alumno.municipio;
				cout << alumno.edad;
				cout << alumno.colorFavorito;*/
				if ( opcion == alumno.carne )
				{
					printf("MATRICULA = %d ", alumno.carne);
					printf(" NOMBRE = %s ", alumno.nombre);
					printf(" universidad = %s ", alumno.universidad);
					printf("\n");
				}
				fclose(fArchivo);
				getchar();
			}
		}
	}else
		if (opcion == 2)
		{
			int edad;
			char nombre[50], universidad[30];
			ifstream salida;
			salida.open("busquedaDatos1.dat", ios::in);

			if (salida.fail())
			{
				cerr << "Hubo un error, pisaste";
				getch();
			}else
			{
				int aux;
				cout << "carne: ";cin >> aux;

				salida >> edad;

				while(!salida.eof())
				{
					salida >> nombre >> universidad;

					//cout << aux;

					if (aux == edad)
					{
						cout << "Juelaverga";
					}/*else
					{
					}*/
				}
			}
		}else
			if (opcion == 3)
			{
				cout << "Opcion 3";
			}else
				if (opcion == 4)
				{
					ciclo();
				}
		
}