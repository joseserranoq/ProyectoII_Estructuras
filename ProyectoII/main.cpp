#include <iostream>
#include <fstream>
using namespace std;
struct Nodo {
	Nodo*sig;
	Nodo* nHijo;
	Nodo* nPadre;
	int cant; //cantidad
	string valor; //caracteristicas
	string nivel; //tipo de caracteristica
	//constructor
	struct Lista* sublista;
	Nodo(int c,string n, string v) {
		cant = c;
		valor = v;
		nivel = n;
		sig = NULL;
		nHijo = NULL;
		nPadre = NULL;
		sublista = NULL;
	}

} * raiz;

struct Lista {
	int posicion;
	Lista* sig;
	struct Nodo* nexoNodo;
	//constructor
	Lista(int pos) {
		posicion = pos;
		sig = NULL;
		nexoNodo = NULL;
	}
};

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
	int numMascotas;
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
			<< " Oficio: " << p.oficio << " Sueldo: " << p.sueldo << " A�os de trabajo: " << p.anosTrabajo << " Cantidad de hijos: " << p.cantHijos
			<< " Hobby: " << p.hobby << " Tipo de alimentacion: " << p.tipoAlimentacion << " Tipo de comida: " << p.tipoComida
			<< " Tipo de musica: " << p.tipoMusica << " Provincia: " << p.provincia << " Canton: " << p.canton << " Distrito: " << p.distrito << " Numeros de mascotas: " << p.numMascotas << endl;

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
		cout << "\nNo se pudo abrir el archivo"<<endl;
		exit(1);
	}
	//archivo.seekg(0);
	int index = 0;
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		if (p.nombre == nombre)
		{
			archivo.close();
			cout << "\nSe encuentra en la posicion: " << index << endl;
			return index;
		}

		index++;
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	cout << "No se encontr� el nombre" << endl;
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
	int i = 0;
	//archivo.seekg(0);
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		if (posicion == i) {
			cout << "\nNombre: " << p.nombre << " Edad: " << p.edad << " Genero: " << p.genero << " Estado Civil: " << p.estadoCivil
				<< " Oficio: " << p.oficio << " Sueldo: " << p.sueldo << " A�os de trabajo: " << p.anosTrabajo << " Cantidad de hijos: " << p.cantHijos
				<< " Hobby: " << p.hobby << " Tipo de alimentacion: " << p.tipoAlimentacion << " Tipo de comida: " << p.tipoComida
				<< " Tipo de musica: " << p.tipoMusica << " Provincia: " << p.provincia << " Canton: " << p.canton << " Distrito: " << p.distrito <<" Numero de mascotas: "<<p.numMascotas << endl;
			return;
		}
		i++;
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	cout << "No se encontro la persona";     //SE IMPRIME AUNQUE LA PERSONA YA ESTE AGREGADA �DEJAR MSJ O NO?
	archivo.close();
}

int totalpersonas() { //cuenta el total de personas que hay en el archivo
	ifstream archivo("lista.txt", ios::in | ios::binary);
	struct Persona p;
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	int i = 0;
	//archivo.seekg(0);
	archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	while (!archivo.eof()) {//end of file
		i++;
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
	}
	archivo.close();
	return i;
}

//Se modifica la persona, segun el id ingresa de la persona a modificar
void modificarPersona(Persona modificar, int posicion) {
	/*
	* FALTA AGREGAR LA VERIFICACION DE SI EXISTE LA POSCION EN EL ARCHIVO
	*/

	fstream archivo("lista.txt", ios::in | ios::out | ios::binary);

	if (archivo.fail()) {
		cout << "\nEl archivo no se puede abrir";
		exit(1);
	}
	archivo.seekp(posicion * sizeof(modificar), ios::beg);
	archivo.write(reinterpret_cast<char*>(&modificar), sizeof(modificar));
	archivo.close(); //se cierra el archivo
}

//Se utiliza para contar el total de personas que estan almacenadas en el archivo y generar la raiz del arbol de decision
Nodo * generaRaiz() {
	//cuenta las personas del archivo para crear la raiz
	int c = totalpersonas();

	//Se crea la raiz
	Nodo* nn = new Nodo(c, "Todos", "");
	nn->sig = NULL;
	return nn;
}

//sirve para recorrer los nodos y encontrar donde asignar el nuevo tipo
Nodo* recorreNivel(string tipo) {
	Nodo* temp = raiz->nHijo;
	Nodo* tempAnt = raiz;
	//recorre el arbol
	while (temp != NULL) {
		tempAnt = temp;
		temp = temp->nHijo;
		if (temp->nivel == tipo) {
			return temp;	//si encuentra el nivel
		}
	}
	//si no se encuentra el nivel
	return temp;
}

//recorre el nodo de manera horizontal para saber que valores tiene el nivel
Nodo* recorreNodoH(Nodo * temp,string valor) {
	while (temp != NULL) {
		if (temp->valor == valor) { //si existe el valor
			return temp;
		}
		temp = temp->sig;
	}
	return NULL; //si no existe va a ser NULL
}

//agrega la poscion en las sublistas
Lista* agregaPosicion(Nodo * temp, int posicion) {
	//recorrer la sublista para colocar la posicion al final de la lista
	Lista* tempL = temp->sublista;
	while (tempL->sig != NULL)	//
		tempL = tempL->sig;
	Lista* npos = new Lista(posicion);
	npos->posicion = posicion;
	npos->nexoNodo = temp;
	tempL->sig = npos;
	return tempL;
}

Nodo* creaNodoGenero(string valor,int posicion ,Nodo * r) { //falta el nexo a padre
	//Se recorre el nivel
	Nodo* temp = r->nHijo;	//Nodo del nivel Genero
	Nodo* tempAnt = r; //Nodo padre
	while (temp != NULL) {
		if (temp->nivel == "Genero") //si se encuentra el nivel, para el bucle
			break;
		tempAnt = temp;
		temp = temp->nHijo;
	}
	if (temp != NULL) {	//ya existe el nivel
		//busca si hay del mismo valor
		Nodo * t = recorreNodoH(temp,valor); //desde el nodo de inicio busca el valor de la lista
		if (t != NULL) { //si existe el valor
			t->cant += 1;
			t->sublista = agregaPosicion(t, posicion);
		}
		else { //Si no existe el valor
			//se recorre al ultimo valor de la lista
			while (temp->sig != NULL)
				temp = temp->sig;

			Nodo* nn = new Nodo(1, "Genero", valor);
			nn->nPadre = tempAnt;

			nn->sig = NULL;
			temp->sig = nn; //se asigna al arbol
			//generando la sublista
			Lista* nnL = new Lista(posicion);
			nnL->sig = NULL;
			nnL->nexoNodo = temp; //enlace al nodo seleccionado segun el valor
			nn->sublista = nnL; //se agrega la lista al nuevo nodo
		}
	}
	else { //no existe el nivel, entonces lo crea con sus respectivos valores
		Nodo* nn = new Nodo(1, "Genero", valor); // en el valor iria el valor conseguido por el archivo falta generar el codigo para conseguir ese valor
		nn->cant = 1; //la persona que crea el nodo
		nn->sig = NULL;
		nn->nPadre = tempAnt;
		tempAnt->nHijo = nn;

		//crea sublista primer dato
		Lista* nnL = new Lista(posicion); //crea la sublista con la posicion de la persona en el archivo
		nnL->nexoNodo = nn;
		nnL->sig = NULL;
		nn->sublista = nnL;

	}
	return r;
}

Nodo *  arbolDecision(Nodo * r) {
	/*
		Se genera la raiz
		cantidad = contPersonas() //se encarga de contar el total de personas que se encuentran en el archivo
		Nodo * nn = new Nodo(valor, nivel, cantidad) //valor y nivel ya son predeterminados en el doc
		raiz->sig = NULL
		raiz = nn;

		Se realiza un while para recorrer los niveles
		Nodo * temp = raiz->sig;
		Nodo * tempAnt = raiz; //Esta variable es util para encontrar el nodo padre del nodo que se va a crear;
		while(temp != NULL){
			tempAnt = temp;
			temp = temp-> nHijo;
		}
		Se crea el primer nodo del nivel y se le asigna sus enlaces
		Nodo * nn = new Nodo(cantidad 1, nivel = segun la opcion que se elija, valor = segun la persona elegida)
		nn->nPadre = tempAnt;

		Se genera la sublista de el nodo
		pos = buscaPersona(p.nombre) //devuelve la posicion en el archivo
		Si el valor y el nivel coinciden con el nodo entonces
		temp -> cantidad +=1
		if(nn->nexoNodo == NULL)
			nn->nexoNodo = new Lista(pos);
		else{
			Lista * t = temp->sublista;
			while(t->sig != NULL)
				temp = temp->sig;

	*/
	cout << "Se selecciona la opcion que desea 1 - edad 2 - genero 3 - estadoCivil";
	int opcion;
	cin >> opcion;

	while (opcion != 0) {
		ifstream archivo("lista.txt", ios::in | ios::binary);
		struct Persona p;
		if (archivo.fail()) {
			cout << "No se pudo abrir el archivo";
			exit(1);
		}
		int posicion  = 0;
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
		while (!archivo.eof()) {//end of file
			if (opcion == 1) {
				r = creaNodoGenero(p.genero,posicion,r);
			}
			archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
			posicion += 1;
		}
		archivo.close();
		opcion = 0;
	}
	cout << endl<<"Desea continuar?"<<endl <<"Cualquier tecla para continuar o presione 0 para terminar"<<endl;
	int op;
	cin >> op;
	if (opcion == 0)	//se utliza para salir de la funcion
		return r;
	arbolDecision(raiz);

}

void datosQuemados() {
	fstream archivo("lista.txt", ios::in | ios::out | ios::binary | ios::trunc);
	//in order
	//nombre, edad, genero, estadocivil, oficio, sueldo, a�os de trabajo, cant hijos, hobby, alimentaci�n, comida, musica, provincia, canton , distrito

	Persona p1 = { "Ana Alves", 20, "Mujer", "Soltera", "Miscelanea", 500000, 3, 1, "Futbol", "Pollotariano", "Salado", "Hardcore zumba","Alajuela","San Ram�n","Palmares", 1 };
	escribir(p1);
	Persona p2 = { "Rambo Alvarez", 20, "Hombre", "Viudo", "Militar", 100000, 15, 8, "Basquetbol", "Carnivoro", "Picante", "Metal","San Jose","Curridabat","La Palma", 0 };
	escribir(p2);
	Persona p3 = { "Carlos Rojas", 37, "Hombre", "Soltero", "Chef", 500000, 3, 0, "Ver series", "Omnivoro", "Dulce", "Salsa","Alajuela","San Carlos","La Palmera", 5 };
	escribir(p3);
	Persona p4 = {"Alina Acu�a", 25, "mujer", "Soltera", "Enfermera", 700000, 5, 2, "Tenis", "Lactovegetariano", "Agridulce", "Merengue","Alajuela","Grecia","Bolivar", 1};
	escribir(p4);
	Persona p5 = { "Jose Quesada", 21, "Hombre", "Casado", "Programador", 1000000, 3, 0, "Jugar play", "Vegetariano", "Picante", "Merengue","Alajuela","San Ramon","Palmares", 2 };
	escribir(p5);
	Persona p6 = { "Maria Carranza", 40, "Mujer", "Soltera", "QA", 1200000, 16, 0, "Caminar", "Omnivoro", "Condimentada", "Jazz","San Jose","Escazu","Escazu", 2 };
	escribir(p6);
	Persona p7 = { "Fernanda Huertas", 27, "Mujer", "Soltera", "Ingeniera Industrial", 800000, 10, 0, "Leer libros", "Vegano", "Picante", "Jazz","Guanacaste","Liberia","Mayorga", 0 };
	escribir(p7);
	Persona p8 = { "Carlos Vaca", 37, "Hombre", "Divorciado", "Ebanista", 2000000, 20, 10, "Pintar", "Omnivoro", "Salado", "Rock","Heredia","San Rafael","La Plaza", 2 };
	escribir(p8);
	Persona p9 = { "Alba Cascarron", 50, "Mujer", "Viuda", "Costurera", 300000, 25, 2, "Ver television", "Crudismo", "Dulce", "Techno","Puntarenas","Buenos Aires","La Penca", 1 };
	escribir(p9);
	Persona p10 = { "Marlen Montero", 48, "Mujer", "Casada", "Ama de casa", 150000, 0, 5, "Ver novelas", "Lactovegetariano", "Agridulce", "Rock","Alajuela","San Carlos","La Tigra", 3 };
	escribir(p10);
	Persona p11 = { "Pancracio Sancho", 80, "Hombre", "Viudo", "Pensionado", 150000, 55, 7, "Ver noticias", "Omnivoro", "Condimentada", "Clasica","Alajuela","Los Chiles","San Jorge", 0 };
	escribir(p11);
	Persona p12 = { "Fleyber Saborio", 22, "Hombre", "Divorciado", "Soldador", 1000000, 3, 1, "Poker", "Omnivoro", "Condimentada", "Metal","San Jose","Guachipelin","Villareal", 2 };
	escribir(p12);
	Persona p13 = { "Marina Rojas", 37, "Mujer", "Divorciada", "Doctora", 1500000, 10, 2, "Ver series", "Vegano", "Dulce", "Rock","Cartago","Cartago","Carmen", 4 };
	escribir(p13);
	Persona p14 = { "Maria Urbina", 17, "Mujer", "Soltera", "Estudiante", 0, 0, 0, "Tenis", "Vegana", "Picante", "Electronica","Guanacaste","Liberia","La Leyla", 4 };
	escribir(p14);
	Persona p15 = { "Alma Costa", 70, "Mujer", "Vuida", "Pensionada", 1000000, 3, 10, "Ver novelas", "Vegetariano", "Dulce", "Jazz","Alajuela","San Ramon","Palmares", 0 };
	escribir(p15);
	Persona p16 = { "Ana Carranza", 41, "Mujer", "Soltera", "Programadora", 1500000, 16, 0, "Correr", "Pollotariano", "Agridulce", "Hardcore","San Jose","Curridabat","Curridabat", 0 };
	escribir(p16);
	Persona p17 = { "Alvaro Jimenez", 27, "Hombre", "Soltero", "Policia", 500000, 3, 1, "Futbol", "Omnivoro", "Salado", "Gospel","Puntarenas","Esparza","San Rafael", 5 };
	escribir(p17);
	Persona p18 = { "Sofia Salas", 19, "Mujer", "Soltera", "Recepcionista", 500000, 1, 0, "Ver series", "Omnivoro", "Picante", "Caribe�o","Alajuela","San Carlos","Agua Azul", 1 };
	escribir(p18);
	Persona p19 = { "Linaza Harvey", 29, "Mujer", "Casada", "Boxeadora", 100000, 10, 1, "Tenis", "Ovovegetariana", "Condimentada", "Bachata","Alajuela","Los Chiles","Medio Queso", 2 };
	escribir(p19);
	Persona p20 = { "Gerardo Guzman", 35, "Hombre", "Viudo", "Carpintero", 450000, 10, 0, "Leer el periodico", "Carnivoro", "Salado", "Rock and Roll","Limon","Guacimo","Cantarrana", 3 };
	escribir(p20);
	Persona p21 = { "Sofia Sanchez", 37, "Mujer", "Casada", "Administracion", 400000, 5, 2, "Comprar Zapatos", "Vegetariana", "Dulce", "Country","Cartago","Carmen","Merced", 0 };
	escribir(p21);
	Persona p22 = { "Pancho Maradiaga", 90, "Hombre", "Viudo", "Pensionado", 100000, 55, 7, "Ver noticias", "Omnivoro", "Dulce", "Jazz","Alajuela","La Leyla","San Jorge", 4 };
	escribir(p22);
	Persona p23 = { "David Gonzalez", 24, "Hombre", "Soltero", "Jornalero", 200000, 9, 1, "Ver videos", "Omnivoro", "Salado", "Instrumental","Alajuela","San Carlos","Cutris", 2 };
	escribir(p23);
	Persona p24 = { "Tatiana Rojas", 27, "Mujer", "Casada", "Ingeniera", 1500000, 5, 0, "Ver series", "Omnivoro", "Dulce", "Rock","Cartago","Cartago","Ochomogo", 5 };
	escribir(p24);
	Persona p25 = { "Juan Vainas", 40, "Hombre", "Casado", "Doctor", 0, 0, 0, "Tenis", "Vegano", "Berenjena", "Electronica","Guanacaste","Liberia","La Cruz", 5 };
	escribir(p25);
	Persona p26 = { "Evelyn Gutierrez", 24, "Mujer", "Casada", "Ama de Casa", 0, 0, 6, "Ver novelas", "Omnivoro", "Dulce", "Hip Hop","Guanacaste","Bagaces","Mogote", 0 };
	escribir(p26);
	Persona p27 = { "Bellota Azul", 18, "Mujer", "Soltera", "Estudiante", 15000, 0, 0, "Correr", "Pollotariano", "Uvas", "Hardcore","San Jose","Desamparados","Desamparados", 4 };
	escribir(p27);
	Persona p28 = { "Blanca Nieves", 35, "Mujer", "Soltera", "Princesa", 200000, 15, 0, "Ver animales", "Vegana", "Manzana", "Hip Hop","Puntarenas","Esparza","Caldera", 3 };
	escribir(p28);
	Persona p29 = { "Stephanie Quesada", 22, "Mujer", "Casada", "Emprendedora", 350000, 2, 1, "Jugar Futbol", "Omnivoro", "Agridulce", "Reggaeton","Guanacaste","Hojancha","Matambu", 1 };
	escribir(p29);
	Persona p30 = { "Tulio Ramirez", 50, "Hombre", "Soltero", "Reportero", 450000, 7, 2, "Poker", "Omnivoro", "Agridulce", "Techno","Alajuela","Los Chiles","Pangola", 1 };
	escribir(p30);
	Persona p31 = { "Gerardo Mazorca", 61, "Hombre", "Viudo", "Maestro", 2000000, 10, 0, "Correr", "Omnivoro", "Salado", "Jazz","Limon","Guacimo","Cantarrana", 3 };
	escribir(p31);
	Persona p32 = { "Tinkerbell Dalpra", 25, "Mujer", "Casada", "Cajera", 1000000, 3, 10, "Poker", "Omnivoro", "Dulce", "Reggae","Guanacaste","Abangares","La Delta", 5 };
	escribir(p32);
	Persona p33 = { "Gerard Moreno", 20, "Hombre", "Casado", "Empresario", 3000000, 4, 0, "Poker", "Omnivoro", "Picante", "Techno","Heredia","San Rafael","Los Angeles", 3 };
	escribir(p33);
	Persona p34 = { "Xiomara Campos", 56, "Mujer", "Casada", "Estilista", 300000, 4, 1, "Maquillaje", "Omnivoro", "Salado", "Flamenco","Limon","Rio Blanco","Brisas", 1 };
	escribir(p34);
	Persona p35 = { "Juana La Cubana", 50, "Mujer", "Soltera", "Escritora", 600000, 25, 0, "Ver novelas", "Pollotariano", "Pollo", "Reggae","Alajuela","San Ram�n","Bajo Rodriguez", 3 };
	escribir(p35);
	Persona p36 = { "Watermelon Rodriguez", 27, "Mujer", "Casada", "Maestra", 4000000, 8, 3, "Basquetbol", "Omnivoro", "Picante", "Metal","San Jose","Desamparados","La Carpio", 3 };
	escribir(p36);
	Persona p37 = { "Kimberly Rojas", 23, "Mujer", "Soltera", "Estudiante", 100000, 2, 0, "Tomar Cafe", "Omnivoro", "Salado", "Drum and Bass","Guanacaste","Carrillo","Palmira", 0 };
	escribir(p37);
	Persona p38 = { "Rita Peluche", 80, "Mujer", "Soltera", "Enfermera", 700000, 50, 2, "Tenis", "Lactovegetariano", "Berenjena", "Salsa","Alajuela","Los Angeles","Bolivar", 3 };
	escribir(p38);
	Persona p39 = { "Jose Suarez", 21, "Hombre", "Casado", "Futbolista", 1000000, 0, 0, "Jugar play", "Vegetariano", "Picante", "Bachata","Alajuela","San Ramon","Palmares", 2 };
	escribir(p39);
	Persona p40 = { "Gledys Huertas", 55, "Mujer", "Viuda", "Dise�adora", 500000, 10, 0, "Ver revistas de moda", "Omnivoro", "Dulce", "Jazz","San Jose","Desamparados","San Miguel", 1 };
	escribir(p40);
	Persona p41 = { "Dickembell Arroyo", 25, "Hombre", "Soltero", "Cajero", 450000, 7, 2, "Poker", "Omnivoro", "Picante", "Techno","Alajuela","Los Chiles","Pangola", 1 };
	escribir(p41);
	Persona p42 = { "Ronald Montero", 47, "Hombre", "Divorciado", "Maestro", 2000000, 10, 2, "Ver series", "Omnivoro", "Cafe", "Rock","Limon","Guacimo","Sarapiqui", 4 };
	escribir(p42);
	Persona p43 = { "Walt Disney", 19, "Hombre", "Casada", "Herrero", 500000, 1, 1, "Futbol", "Omnivoro", "Dulce", "Reggae","Guanacaste","Abangares","La Delta", 0 };
	escribir(p43);
	Persona p44 = { "Chayanne Rojas", 50, "Hombre", "Casado", "Empresario", 3000000, 4, 0, "Poker", "Omnivoro", "Manzana", "Salsa","Heredia","Desamparados","Los Angeles" , 0 };
	escribir(p44);
	Persona p45 = { "Miguel Contreras", 75, "Hombre", "Viudo", "Pensionado", 2500000, 40, 2, "Ganaderia", "Omnivoro", "Salado", "Clasica","Guanacaste","Nandayure","San Rafael", 4 };
	escribir(p45);
	Persona p46 = { "Pepe Jose", 20, "Hombre", "Soltero", "Mesero", 600000, 1, 0, "Ver novelas", "Vegetariano", "Pescado", "Reggae","Cartago","San Ram�n","Bajo Rodriguez", 3 };
	escribir(p46);
	Persona p47 = { "Natasha Vanessa", 60, "Mujer", "Soltera", "Comerciante", 9000000, 50, 9, "Coser", "Omnivoro", "Picante", "Metal","San Jose","Desamparados","La Carpio", 5 };
	escribir(p47);
	Persona p48 = { "Juan Castro", 40, "Hombre", "Casado", "Abogado", 2000000, 20, 2, "Tomar cafe", "Omnivoro", "Salado", "Blues","Guanacaste","Carrillo","Palmira", 0 };
	escribir(p48);
	Persona p49 = { "Katherine Amador", 20, "Mujer", "Soltera", "Estudiante", 1150000, 0, 0, "Reposteria", "Omnivoro", "Dulce", "Country","Alajuela","San Carlos","Pocosol", 2 };
	escribir(p49);
	Persona p50 = { "Samantha Montero", 19, "Mujer", "Soltera", "Estudiante", 175000, 0, 0, "Ver series", "Omnivoros", "Jalapeno", "Metal","Alajuela","San Carlos","Fortuna", 2 };
	escribir(p50);
	archivo.close();
}

int main()
{
	datosQuemados();
	//Busca la persona por el nombre.
	raiz = generaRaiz();
	raiz = arbolDecision(raiz);
	cout << endl << raiz->cant << endl << raiz->nHijo->valor << endl << raiz->nHijo->sig->valor<<endl;
	buscaPersona("Jose Quesada");
	//El metodo leerPersona, imprime toda la imformacion de la persona.
	leerPersona(4);

	//buscaPersona("Jose Quesada");
	//El metodo leerPersona, imprime toda la imformacion de la persona.
	cout << "\n\n-----Persona que se quiere modificar-----" << endl;
	leerPersona(6);
	Persona modificar = { "Juliana Ramirez", 32, "Mujer", "Casada", "Profesora", 450000, 15, 1, "Jugar Futbol", "Omnivoro", "Dulce", "Valadas","Ciudad Quesasa","San Carlos","Pocosol" };
	modificarPersona(modificar, 6);
	cout << "\n\n-----Persona ya modificada-----" << endl;
	leerPersona(6);

	//cout << "El tama�o de la estructura:  " << sizeof(Persona);
	return 0;
}
