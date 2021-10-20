#include <iostream>
#include <fstream>
using namespace std;

struct Persona {
	char nombre[20];
	int edad;
	char genero[7];
	char estadoCivil[8];
	char oficio[20];
	int sueldo;
	int anosTrabajo;
	int cantHijos;
	char hobby[15];
	char tipoAlimentacion[20];
	char tipoComida[20];
	char tipoMusica[15];
	char provincia[15];
	char canton[15];
	char distrito[15];
};

void escribir(Persona x)
{
	fstream archivo("lista.txt", ios::in | ios::out | ios::binary);
	if (archivo.fail()) {
		cout << "\nNo se pudo abrir el archivo";
		exit(1);
	}
	archivo.seekp(0, ios::end);
	archivo.write(reinterpret_cast<char*>(&x), sizeof(x));
	archivo.close(); //se cierra el archivo
}

void leer()
{
	ifstream archivo("lista.txt", ios::in | ios::binary);
	struct Persona p;
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	//archivo.seekg(0);
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		cout << "\nNombre: " << p.nombre << " Edad: " << p.edad << " Genero: " << p.genero << " Estado Civil: " << p.estadoCivil
			<< " Oficio: " << p.oficio << " Sueldo: " << p.sueldo << " Años de trabajo: " << p.anosTrabajo << " Cantidad de hijos: " << p.cantHijos
			<< " Hobby: " << p.hobby << " Tipo de alimentación: " << p.tipoAlimentacion << " Tipo de comida: " << p.tipoComida
			<< " Tipo de música: " << p.tipoMusica << " Provincia: " << p.provincia <<" Cantón: " << p.canton <<" Distrito: " << p.distrito << endl;

		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	archivo.close();
}
int buscaPersona(string nombre)
{
	ifstream archivo("lista.txt", ios::in | ios::binary);
	struct Persona p;
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	//archivo.seekg(0);
	int index = 0;
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		if (p.nombre == nombre)
		{
			archivo.close();
			cout << "Se encuentra en la posicion: " << index << endl;
			return index;
		}

		index++;
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	cout << "No se encontró el nombre" << endl;
	archivo.close();
}

void leerPersona(int posicion)
{
	ifstream archivo("lista.txt", ios::in | ios::binary);
	struct Persona p;
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	int i=0;
	//archivo.seekg(0);
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		if (posicion == i) {
			cout << "\nNombre: " << p.nombre << " Edad: " << p.edad << " Genero: " << p.genero << " Estado Civil: " << p.estadoCivil
				<< " Oficio: " << p.oficio << " Sueldo: " << p.sueldo << " Años de trabajo: " << p.anosTrabajo << " Cantidad de hijos: " << p.cantHijos
				<< " Hobby: " << p.hobby << " Tipo de alimentación: " << p.tipoAlimentacion << " Tipo de comida: " << p.tipoComida
				<< " Tipo de música: " << p.tipoMusica << " Provincia: " << p.provincia << " Cantón: " << p.canton << " Distrito: " << p.distrito << endl;
		}
		i++;
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	cout << "No se encontró la persona";
	archivo.close();
}
int main()
{
	fstream archivo("lista.txt", ios::in | ios::out | ios::binary | ios::trunc);
	//in order
	//nombre, edad, genero, estadocivil, oficio, sueldo, años de trabajo, cant hijos, hobby, alimentación, comida, musica, provincia, canton , distrito

	Persona p1 = {"Ana", 20, "hombre", "soltero", "miscelaneo", 500000, 3, 1, "futbol", "pollotariano", "pollo", "Hardcore zumba","Alajuela","San Ramón","Palmares"} ;

	escribir(p1);
	Persona p2 = { "Rambo", 20, "hombre", "soltero", "miscelaneo", 500000, 3, 1, "futbol", "pollotariano", "pollo", "Hardcore zumba","Alajuela","San Ramón","Palmares" };
	escribir(p2);
	Persona p3 = { "Carlos", 20, "hombre", "soltero", "miscelaneo", 500000, 3, 1, "futbol", "pollotariano", "pollo", "Hardcore zumba","Alajuela","San Ramón","Palmares" };
	escribir(p3);
	Persona p4 = { "Alina", 20, "hombre", "soltero", "miscelaneo", 500000, 3, 1, "futbol", "pollotariano", "pollo", "Hardcore zumba","Alajuela","San Ramón","Palmares" };
	escribir(p4);
	Persona p5 = { "Jose", 20, "hombre", "soltero", "miscelaneo", 500000, 3, 1, "futbol", "pollotariano", "pollo", "Hardcore zumba","Alajuela","San Ramón","Palmares" };
	escribir(p5);
	//leer();
	buscaPersona("Jose");
	leerPersona(4);
	//cout << "El tamaño de la estructura:  " << sizeof(Persona);
	return 0;
}
