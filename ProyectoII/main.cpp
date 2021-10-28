#include <iostream>
#include <fstream>
using namespace std;

struct Persona {
	char nombre[30];
	int edad;
	char genero[7];
	char estadoCivil[15];
	char oficio[30];
	int sueldo;
	int anosTrabajo;
	int cantHijos;
	char hobby[30];
	char tipoAlimentacion[20];
	char tipoComida[20];
	char tipoMusica[15];
	char provincia[15];
	char canton[15];
	char distrito[15];
};

//El metodo escribir, requiere de un parametro persona y guarda en un archivo txt, los datos ingresados de la persona.
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

//El metodo leer, imprime toda la informacion del txt.
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

//Se busca la persona del archivo y retorna su posicion que posee en el archivo
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

//Se imprime la persona en base a su posicion en el archivo
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

	Persona p1 = {"Ana Alves", 20, "Mujer", "Soltera", "Miscelanea", 500000, 3, 1, "Futbol", "Pollotariano", "Salado", "Hardcore zumba","Alajuela","San Ramón","Palmares"} ;
	escribir(p1);
	Persona p2 = { "Rambo Alvarez", 20, "Hombre", "Viudo", "Militar", 100000, 15, 8, "Basquetbol", "Carnivoro", "Picante", "Metal","San Jose","Curridabat","La Palma" };
	escribir(p2);
	Persona p3 = { "Carlos Rojas", 37, "Hombre", "Soltero", "Chef", 500000, 3, 0, "Ver series", "Omnivoro", "Dulce", "Salsa","Alajuela","San Carlos","La Palmera" };
	escribir(p3);
	Persona p4 = { "Alina Acuña", 25, "mujer", "Soltera", "Enfermera", 700000, 5, 2, "Tenis", "Lactovegetariano", "Agridulce", "Merengue","Alajuela","Grecia","Bolivar" };
	escribir(p4);
	Persona p5 = { "Jose Quesada", 21, "Hombre", "Casado", "Programador", 1000000, 3, 0, "Jugar play", "Vegetariano", "Picante", "Merengue","Alajuela","San Ramon","Palmares" };
  escribir(p5);
  Persona p6 = {"Maria Carranza", 40, "Mujer", "Soltera", "QA", 1200000, 16, 0, "Caminar", "Omnivoro", "Condimentada", "Jazz","San Jose","Escazu","Escazu"} ;
	escribir(p6);
	Persona p7 = { "Fernanda Huertas", 27, "Mujer", "Soltera", "Ingeniera Industrial", 800000, 10, 0, "Leer libros", "Vegano", "Picante", "Jazz","Guanacaste","Liberia","Mayorga" };
	escribir(p7);
	Persona p8 = { "Carlos Vaca", 37, "Hombre", "Divorciado", "Ebanista", 2000000, 20, 10, "Pintar", "Omnivoro", "Salado", "Rock","Heredia","San Rafael","La Plaza" };
	escribir(p8);
	Persona p9 = { "Alba Cascarron", 50, "Mujer", "Viuda", "Costurera", 300000, 25, 2, "Ver television", "Crudismo", "Dulce", "Techno","Puntarenas","Buenos Aires","La Penca" };
	escribir(p9);
	Persona p10 = { "Marlen Montero", 48, "Mujer", "Casada", "Ama de casa", 150000, 0, 5, "Ver novelas", "Lactovegetariano", "Agridulce", "Rock","Alajuela","San Carlos","La Tigra" };
  escribir(p10);
  Persona p11 = {"Pancracio Sancho", 80, "Hombre", "Viudo", "Pensionado", 150000, 55, 7, "Ver noticias", "Omnivoro", "Condimentada", "Clasica","Alajuela","Los Chiles","San Jorge"} ;
	escribir(p11);
	Persona p12 = { "Fleyber Saborio", 22, "Hombre", "Divorciado", "Soldador", 1000000, 3, 1, "Poker", "Omnivoro", "Condimentada", "Metal","San Jose","Guachipelin","Villareal" };
	escribir(p12);
	Persona p13 = { "Marina Rojas", 37, "Mujer", "Divorciada", "Doctora", 1500000, 10, 2, "Ver series", "Vegano", "Dulce", "Rock","Cartago","Cartago","Carmen" };
	escribir(p13);
	Persona p14 = { "Maria Urbina", 17, "Mujer", "Soltera", "Estudiante", 0, 0, 0, "Tenis", "Vegana", "Picante", "Electronica","Guanacaste","Liberia","La Leyla" };
	escribir(p14);
	Persona p15 = { "Alma Costa", 70, "Mujer", "Vuida", "Pensionada", 1000000, 3, 10, "Ver novelas", "Vegetariano", "Dulce", "Jazz","Alajuela","San Ramon","Palmares" };
  escribir(p15);
  Persona p16 = {"Ana Carranza", 41, "Mujer", "Soltera", "Programadora", 1500000, 16, 0, "Correr", "Pollotariano", "Agridulce", "Hardcore","San Jose","Curridabat","Curridabat"} ;
	escribir(p16);
	Persona p17 = { "Alvaro Jimenez", 27, "Hombre", "Soltero", "Policia", 500000, 3, 1, "Futbol", "Omnivoro", "Salado", "Gospel","Puntarenas","Esparza","San Rafael" };
	escribir(p17);
	Persona p18 = { "Sofia Salas", 19, "Mujer", "Soltera", "Recepcionista", 500000, 1, 0, "Ver series", "Omnivoro", "Picante", "Caribeño","Alajuela","San Carlos","Agua Azul" };
	escribir(p18);
	Persona p19 = { "Linaza Harvey", 29, "Mujer", "Casada", "Boxeadora", 100000, 10, 1, "Tenis", "Ovovegetariana", "Condimentada", "Bachata","Alajuela","Los Chiles","Medio Queso" };
	escribir(p19);
	Persona p20 = { "Gerardo Guzman", 35, "Hombre", "Viudo", "Carpintero", 450000, 10, 0, "Leer el periodico", "Carnivoro", "Salado", "Rock and Roll","Limon","Guacimo","Cantarrana" };
  escribir(p20);
  Persona p21 = { "Sofia Sanchez", 37, "Mujer", "Casada", "Administracion", 400000, 5, 2, "Comprar Zapatos", "Vegetariana", "Dulce", "Country","Cartago","Carmen","Merced" };
  escribir(p21);
  Persona p22 = {"Pancho Maradiaga", 90, "Hombre", "Viudo", "Pensionado", 100000, 55, 7, "Ver noticias", "Omnivoro", "Dulce", "Jazz","Alajuela","La Leyla","San Jorge"} ;
	escribir(p22);
	Persona p23 = { "David Gonzalez", 24, "Hombre", "Soltero", "Jornalero", 200000, 9, 1, "Ver videos", "Omnivoro", "Salado", "Instrumental","Alajuela","San Carlos","Cutris" };
	escribir(p23);
	Persona p24 = { "Tatiana Rojas", 27, "Mujer", "Casada", "Ingeniera", 1500000, 5, 0, "Ver series", "Omnivoro", "Dulce", "Rock","Cartago","Cartago","Ochomogo" };
	escribir(p24);
	Persona p25 = { "Juan Vainas", 40, "Hombre", "Casado", "Doctor", 0, 0, 0, "Tenis", "Vegano", "Berenjena", "Electronica","Guanacaste","Liberia","La Cruz" };
	escribir(p25);
	Persona p26 = { "Evelyn Gutierrez", 24, "Mujer", "Casada", "Ama de Casa", 0, 0, 6, "Ver novelas", "Omnivoro", "Dulce", "Hip Hop","Guanacaste","Bagaces","Mogote" };
  escribir(p26);
  Persona p27 = {"Bellota Azul", 18, "Mujer", "Soltera", "Estudiante", 15000, 0, 0, "Correr", "Pollotariano", "Uvas", "Hardcore","San Jose","Desamparados","Desamparados"} ;
	escribir(p27);
	Persona p28 = { "Blanca Nieves", 35, "Mujer", "Soltera", "Princesa", 200000, 15, 0, "Ver animales", "Vegana", "Manzana", "Hip Hop","Puntarenas","Esparza","Caldera" };
	escribir(p28);
	Persona p29 = { "Stephanie Quesada", 22, "Mujer", "Casada", "Emprendedora", 350000, 2, 1, "Jugar Futbol", "Omnivoro", "Agridulce", "Reggaeton","Guanacaste","Hojancha","Matambu" };
	escribir(p29);
	Persona p30 = { "Tulio Ramirez", 50, "Hombre", "Soltero", "Reportero", 450000, 7, 2, "Poker", "Omnivoro", "Agridulce", "Techno","Alajuela","Los Chiles","Pangola" };
	escribir(p30);
	Persona p31 = { "Gerardo Mazorca", 61, "Hombre", "Viudo", "Maestro", 2000000, 10, 0, "Correr", "Omnivoro", "Salado", "Jazz","Limon","Guacimo","Cantarrana" };
  escribir(p31);
	Persona p32 = { "Tinkerbell Dalpra", 25, "Mujer", "Casada", "Cajera", 1000000, 3, 10, "Poker", "Omnivoro", "Dulce", "Reggae","Guanacaste","Abangares","La Delta" };
  escribir(p32);
  Persona p33 = { "Gerard Moreno", 20, "Hombre", "Casado", "Empresario", 3000000, 4, 0, "Poker", "Omnivoro", "Picante", "Techno","Heredia","San Rafael","Los Angeles" };
  escribir(p33);
  Persona p34 = { "Xiomara Campos", 56, "Mujer", "Casada", "Estilista", 300000, 4, 1, "Maquillaje", "Omnivoro", "Salado", "Flamenco","Limon","Rio Blanco","Brisas" };
  escribir(p34);
  Persona p35 = {"Juana La Cubana", 50, "Mujer", "Soltera", "Escritora", 600000, 25, 0, "Ver novelas", "Pollotariano", "Pollo", "Reggae","Alajuela","San Ramón","Bajo Rodriguez"} ;
	escribir(p35);
	Persona p36 = { "Watermelon Rodriguez", 27, "Mujer", "Casada", "Maestra", 4000000, 8, 3, "Basquetbol", "Omnivoro", "Picante", "Metal","San Jose","Desamparados","La Carpio" };
	escribir(p36);
	Persona p37 = { "Kimberly Rojas", 23, "Mujer", "Soltera", "Estudiante", 100000, 2, 0, "Tomar Cafe", "Omnivoro", "Salado", "Drum and Bass","Guanacaste","Carrillo","Palmira" };
	escribir(p37);
	Persona p38 = { "Rita Peluche", 80, "Mujer", "Soltera", "Enfermera", 700000, 50, 2, "Tenis", "Lactovegetariano", "Berenjena", "Salsa","Alajuela","Los Angeles","Bolivar" };
	escribir(p38);
	Persona p39 = { "Jose Suarez", 21, "Hombre", "Casado", "Futbolista", 1000000, 0, 0, "Jugar play", "Vegetariano", "Picante", "Bachata","Alajuela","San Ramon","Palmares" };
  escribir(p39);
  Persona p40 = { "Gledys Huertas", 55, "Mujer", "Viuda", "Diseñadora", 500000, 10, 0, "Ver revistas de moda", "Omnivoro", "Dulce", "Jazz","San Jose","Desamparados","San Miguel" };
	escribir(p40);
	Persona p41 = { "Dickembell Arroyo", 25, "Hombre", "Soltero", "Cajero", 450000, 7, 2, "Poker", "Omnivoro", "Picante", "Techno","Alajuela","Los Chiles","Pangola" };
	escribir(p41);
	Persona p42 = { "Ronald Montero", 47, "Hombre", "Divorciado", "Maestro", 2000000, 10, 2, "Ver series", "Omnivoro", "Cafe", "Rock","Limon","Guacimo","Sarapiqui" };
  escribir(p42);
	Persona p43 = { "Walt Disney", 19, "Hombre", "Casada", "Herrero", 500000, 1, 1, "Futbol", "Omnivoro", "Dulce", "Reggae","Guanacaste","Abangares","La Delta" };
  escribir(p43);
  Persona p44 = { "Chayanne Rojas", 50, "Hombre", "Casado", "Empresario", 3000000, 4, 0, "Poker", "Omnivoro", "Manzana", "Salsa","Heredia","Desamparados","Los Angeles" };
  escribir(p44);
  Persona p45 = { "Miguel Contreras", 75, "Hombre", "Viudo", "Pensionado", 2500000, 40, 2, "Ganaderia", "Omnivoro", "Salado", "Clasica","Guanacaste","Nandayure","San Rafael" };
  escribir(p45);
  Persona p46 = {"Pepe Jose", 20, "Hombre", "Soltero", "Mesero", 600000, 1, 0, "Ver novelas", "Vegetariano", "Pescado", "Reggae","Cartago","San Ramón","Bajo Rodriguez"} ;
	escribir(p46);
	Persona p47 = { "Natasha Vanessa", 60, "Mujer", "Soltera", "Comerciante", 9000000, 50, 9, "Coser", "Omnivoro", "Picante", "Metal","San Jose","Desamparados","La Carpio" };
	escribir(p47);
	Persona p48 = { "Juan Castro", 40, "Hombre", "Casado", "Abogado", 2000000, 20, 2, "Tomar cafe", "Omnivoro", "Salado", "Blues","Guanacaste","Carrillo","Palmira" };
	escribir(p48);
	Persona p49 = { "Katherine Amador", 20, "Mujer", "Soltera", "Estudiante", 1150000, 0, 0, "Reposteria", "Omnivoro", "Dulce", "Country","Alajuela","San Carlos","Pocosol" };
	escribir(p49);
	Persona p50 = { "Samantha Montero", 19, "Mujer", "Soltera", "Estudiante", 175000, 0, 0, "Ver series", "Omnivoros", "Jalapeno", "Metal","Alajuela","San Carlos","Fortuna" };
  escribir(p50);


  //Busca la persona por el nombre.
	buscaPersona("Jose");
  //El metodo leerPersona, imprime toda la imformacion de la persona.
	leerPersona(4);
	//cout << "El tamaño de la estructura:  " << sizeof(Persona);
	return 0;
}
