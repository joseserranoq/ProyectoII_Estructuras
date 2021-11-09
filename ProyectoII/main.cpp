#include <iostream>
#include <fstream>
using namespace std;
struct Nodo {
	Nodo* sig;
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
	char oficio[30];S
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
	Lista * nnL = new Lista(posicion);
	nnL->nexoNodo = temp;

	if (lista == NULL) {
		lista = nnL;
	}
	else {
		Lista* tempL = lista;
		while (tempL->sig != NULL)
			tempL = tempL->sig;
		tempL->sig = nnL;
	}

	return lista;
}

Nodo* creaNodoString(string valor,int posicion ,Nodo * r,string tipoN) {
	//se recorre el nivel
	Nodo* temp = r->nHijo;	//Nodo del nivel Genero
	Nodo* tempAnt = r; //Nodo padre
	while (temp != NULL) {
		if (temp->nivel == tipoN) //si se encuentra el nivel, para el bucle
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

			Nodo* nn = new Nodo(1, tipoN, valor);
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
		Nodo* nn = new Nodo(1, tipoN, valor); // en el valor iria el valor conseguido por el archivo falta generar el codigo para conseguir ese valor
		nn->cant = 1; //la persona que crea el nodo
		nn->sig = NULL;
		nn->nPadre = tempAnt;
		tempAnt->nHijo = nn;

		//crea sublista primer dato
		nn->sublista = agregaPosicion(nn,posicion);
	}
	return r;
}

//Las funciones determina... funcionan para retornar un valor que va a servir para insertarlo en un nodo como corresponda
string determinaValorEdad(int valor) { //se utiliza para determinar en que nodo del nivel edad ira el valor que se presente en el archivo
	if (valor < 18)
		return "<18";
	else if (valor <= 50)
		return "18<=50";
	else	//valor > 50
		return ">50";
}

string determinaValorSueldo(int valor) {
	if (valor < 100000)
		return "<100'000";
	else if (valor < 500000)
		return "100'000 < 500'000 ";
	else if (valor < 1000000)
		return "500'000 <= 1'000'000";
	else
		return ">1'000'000";
}

string determinaValorCantH(int valor) {
	if (valor <= 2)
		return "<=2";
	else if (valor <= 5)
		return "2 <= 5";
	else
		return ">5";
}

string determinaValorAnosT(int valor) { //años trabajados
	if (valor < 3)
		return "<3";
	else if (valor < 5)
		return "3 <= 5";
	else if (valor <= 10)
		return "5 <= 10";
	else
		return "> 10";
}

string determinaValorCantM(int valor) { //cantidad de mascotas
	if (valor <= 2)
		return "<=2";
	else if (valor <= 10)
		return "2 <= 10";
	else
		return ">10";
}

Nodo * creaNodoInt(int valor,int posicion,Nodo * r,string tipoN) { //funcion que se utiliza para generar un nivel si el valor dado es un entero
	/*
	Se deben de realizar agrupaciones pre establecidas mediante las condiciones
	para convertir int a string se usa:
	int a = 10;
	stringstream ss;
	ss << a;
	string str = ss.str();
	Esto se utilizara para poder insertar el dato del valor a nodo que debe de ser un string
	Previamente debe de pasar el int por algunas condiciones pare determinar en qué nodo debe de ir
	*/
	//Se recorre el nivel
	Nodo* temp = r->nHijo;	//Nodo del nivel Edad
	Nodo* tempAnt = r; //Nodo padre
	while (temp != NULL) {
		if (temp->nivel == tipoN) //si se encuentra el nivel, para el bucle
			break;
		tempAnt = temp;
		temp = temp->nHijo;
	}
	//Determina el cuál es el tipo, para agrupar el valor correctamente
	string v;
	if (tipoN == "Edad")
		v = determinaValorEdad(valor);
	else if (tipoN == "Sueldo")
		v = determinaValorSueldo(valor);
	else if (tipoN == "Anos Trabajo")
		v = determinaValorAnosT(valor);
	else if (tipoN == "Cantidad Hijos")
		v = determinaValorCantH(valor);
	else if (tipoN == "Cantidad de Mascotas")
		v = determinaValorCantM(valor);
	//este condicional determina si existe  o no el nivel
	if (temp != NULL) {	//ya existe el nivel
		//busca si hay del mismo valor
		Nodo* t = recorreNodoH(temp,v); //desde el nodo de inicio busca el valor de la lista
		if (t != NULL) { //si existe el valor
			t->cant += 1;
			t->sublista = agregaPosicion(t, posicion);
		}
		else { //Si no existe el valor
			//se recorre al ultimo valor de la lista
			while (temp->sig != NULL)
				temp = temp->sig;
			string v = determinaValorEdad(valor);
			Nodo* nn = new Nodo(1, tipoN, v);
			nn->nPadre = tempAnt;
			nn->sig = NULL;
			temp->sig = nn; //se asigna al arbol
			//generando la sublista
			temp->sublista=agregaPosicion(temp, posicion);
		}
	}
	else { //no existe el nivel, entonces lo crea con sus respectivos valores
		Nodo* nn = new Nodo(1, tipoN, v); // en el valor iria el valor conseguido por el archivo falta generar el codigo para conseguir ese valor
		nn->cant = 1; //la persona que crea el nodo
		nn->sig = NULL;
		nn->nPadre = tempAnt;
		tempAnt->nHijo = nn;

		//
		//crea sublista primer dato
		nn->sublista = agregaPosicion(nn, posicion);

	}
	return r;
}
bool validaInt(string var) {	//Funciona decodifica el string para saber si son numeros digitados
	int largo = var.size();
	int i=0;
	while (i < largo) {
		if (!isdigit(var[i])) //si el char no es un entero
			return false;
		i++;
	}
	return true;	//si todos los chars son numeros positivos, no se permiten signos
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
	cout << "Se selecciona la opcion que desea \n1-edad  2-genero  3-estadoCivil  4-Oficio  5-Sueldo  6-Años de Trabajo  7-Cantidad de Hijos  8-Hobby  9-Tipo de Alimentacion\n  "
		<< "10-Tipo de Comida  11-Tipo de Musica  12-Provincia  13-Canton  14-Distrito  15-Cantidad de Mascotas \nIntroduzca una opcion : ";
	string num;
	cin >> num;
	if (validaInt(num)) {
		//convierte el string en un int
		int opcion = stoi(num, NULL, 16);	//int stoi (const string&  str, size_t* idx = 0, int base = 10);

		ifstream archivo("lista.txt", ios::in | ios::binary);
		struct Persona p;
		if (archivo.fail()) {
			cout << "No se pudo abrir el archivo";
			exit(1);
		}
		int posicion = 0;	//tiene la funcion de saber la posicion de los elementos en el archivo
		archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
		while (!archivo.eof()) {//end of file
			//falta funcion que determine que no se repitan
			//contador para un maximo y minimo de niveles

			if (opcion == 1) {
				r = creaNodoInt(p.edad, posicion, r, "Edad");
				cout << "Dato Edad insertado con exito" << endl;
			}
			else if (opcion == 2) {
				r = creaNodoString(p.genero, posicion, r, "Genero");
				cout << "Dato Genero insertado con exito" << endl;
			}
			else if (opcion == 3) {
				r = creaNodoString(p.estadoCivil, posicion, r, "Estado Civil");
				cout << "Dato Estado Civil insertado con exito" << endl;
			}
			else if (opcion == 4) {
				r = creaNodoString(p.oficio, posicion, r, "Oficio");
				cout << "Dato Oficio insertado con exito" << endl;
			}
			else if (opcion == 5) {
				r = creaNodoInt(p.sueldo, posicion, r, "Sueldo");
				cout << "Dato Sueldo insertado con exito" << endl;
			}
			else if (opcion == 6) {
				r = creaNodoInt(p.anosTrabajo, posicion, r, "Años de Trabajo");
				cout << "Nivel Años de Trabajo insertado con exito" << endl;
			}
			else if (opcion == 7) {
				r = creaNodoInt(p.cantHijos, posicion, r, "Cantidad de Hijos");
				cout << "Nivel Cantidad de Hijos insertado con exito" << endl;
			}
			else if (opcion == 8) {
				r = creaNodoString(p.hobby, posicion, r, "Hobby");
				cout << "Nivel Hobby insertado con exito" << endl;
			}
			else if (opcion == 9) {
				r = creaNodoString(p.tipoAlimentacion, posicion, r, "Tipo de Alimentacion");
				cout << "Nivel Tipo de Alimentacion insertado con exito" << endl;
			}
			else if (opcion == 10) {
				r = creaNodoString(p.tipoComida, posicion, r, "Tipo Comida");
				cout << "Nivel Tipo Comida insertado con exito" << endl;
			}
			else if (opcion == 11) {
				r = creaNodoString(p.tipoMusica, posicion, r, "Tipo Musica");
				cout << "Nivel Tipo Musica insertado con exito" << endl;
			}
			else if (opcion == 12) {
				r = creaNodoString(p.provincia, posicion, r, "Provincia");
				cout << "Nivel Provincia insertado con exito" << endl;
			}
			else if (opcion == 13) {
				r = creaNodoString(p.canton, posicion, r, "Canton");
				cout << "Nivel Canton insertado con exito" << endl;
			}
			else if (opcion == 14) {
				r = creaNodoString(p.distrito, posicion, r, "Distrito");
				cout << "Nivel Distrito insertado con exito" << endl;
			}
			else if (opcion == 15) {
				r = creaNodoInt(p.numMascotas, posicion, r, "Cantidad Mascotas");
				cout << "Nivel Cantidad Mascotas insertado con exito" << endl;
			}
			archivo.read(reinterpret_cast<char*>(&p), sizeof(p));
			posicion += 1;

		}
		archivo.close();
	}
	else
		cout << "Dato incorrecto" << endl;
	//Sale del condicional anterior
	cout << endl << "Desea continuar?" << endl << "digite cualquier tecla para continuar o digite 0 para terminar" << endl;
	int op;
	cin >> op;
	if (op != 0) {
		system("CLS");
		r = arbolDecision(r);
	}
	system("CLS");
	cout << "Arbol generado con exito" << endl;
	return r;

}
// Metodo para contar nodos hojas del arbol de decision.
int hoja = 0;
void contarHojas(Nodo * raiz){
    if(raiz == NULL){
        return;
    }
    //Si es null es porque es hija, lo cual se aumenta en la variable 'hoja'.
    if(raiz->sublista==NULL){
        hoja++;
        return;
    }
    Nodo * tempSubLista = raiz->sublista;

    while(tempSubLista != NULL){
        contarHojas(tempSubLista);}

        tempSubLista = tempSubLista->sig; // Pasa al siguiente hijo
    }
}

//Metodo para agregar una persosna al archivo
void agregarPersona(){
    Persona personaNueva;

    string datoString;

    cout<<"Nombre: "<<endl;
    getline(cin, datoString);
    strncpy(personaNueva.nombre, datoString.c_str(),sizeof(personaNueva.nombre));

    cout<<"Edad: "<<endl;
    cin >> personaNueva.edad;
    cin.ignore();

    cout<<"Genero: "<<endl;
    getline(cin, datoString);
    strncpy(personaNueva.genero, datoString.c_str(),sizeof(personaNueva.genero));

    cout<<"Estado civil: "<<endl;
    getline(cin, datoString);
    strncpy(personaNueva.estadoCivil, datoString.c_str(),sizeof(personaNueva.estadoCivil));

    cout<<"Oficio: "<<endl;
    getline(cin, datoString);
    strncpy(personaNueva.oficio, datoString.c_str(),sizeof(personaNueva.oficio));

    cout<<"Sueldo: "<<endl;
    cin >> personaNueva.sueldo;
    cin.ignore();

    cout<<"Años de trabajo: "<<endl;
    cin >> personaNueva.anosTrabajo;
    cin.ignore();

    cout<<"Cantidad de hijos: "<<endl;
    cin >> personaNueva.cantHijos;
    cin.ignore();

    cout<<"Hobby: "<<endl;
    getline(cin, datoString);
    strncpy(personaNueva.hobby, datoString.c_str(),sizeof(personaNueva.hobby));

    cout<<"Tipo de alimentacion: "<<endl;
    getline(cin, datoString);
    strncpy(personaNueva.tipoAlimentacion, datoString.c_str(),sizeof(personaNueva.tipoAlimentacion));

    cout<<"Tipo de comida: "<<endl;
    getline(cin, datoString);
    strncpy(personaNueva.tipoComida, datoString.c_str(),sizeof(personaNueva.tipoComida));

    cout<<"Tipo de musica: "<<endl;
    getline(cin, datoString);
    strncpy(personaNueva.tipoMusica, datoString.c_str(),sizeof(personaNueva.tipoMusica));

    cout<<"Provincia: "<<endl;
    getline(cin, datoString);
    strncpy(personaNueva.provincia, datoString.c_str(),sizeof(personaNueva.provincia));

    cout<<"Canton: "<<endl;}
    getline(cin, datoString);
    strncpy(personaNueva.canton, datoString.c_str(),sizeof(personaNueva.canton));

    cout<<"Distrito: "<<endl;
    getline(cin, datoString);
    strncpy(personaNueva.distrito, datoString.c_str(),sizeof(personaNueva.distrito));

    cout<<"Cantidad de mascotas: "<<endl;
    cin >> personaNueva.numMascotas;
    cin.ignore();
}


/*

        CONSULTAS

*/

void numeroPersonaNivel() {
    //Contadores
    int conNivel = 0;
    //Punteros
    Nodo* tempV = raiz;
    //Para recorrer hacia abajo.
	while (tempV!= NULL) {
	    int conPersona = 0;
	    Nodo * tempH = tempV;

        while(tempH != NULL){
            conPersona += tempH->cant;
            cout <<"Nivel"<<conNivel<<": "<<canPersona<<endl;
            tempH = tempH->sig;
        }
        tempV = tempV->sig;
        conNivel++;
	}
	//si no se encuentra el nivel
	return temp;
}





/*

    Funciones que van el menu.

*/


void personasMenu(){
    int opcion;
    cout << "1. Agregar persona" << endl;
    cout << "2. Modificar a una persona" << endl;
    cout << "3. Borrar a una persona" << endl;
    cout << "4. Leer a una persona" << endl;

    cout <<"Ingrese una opcion: "<<endl;
    cin >> opcion;

    if (opcion == 1){
        agregarPersona();
    }
    if (opcion == 2){


    }
    if (opcion == 3){

    }
    if (opcion == 4){

        leerPersona()
    }
}




/*

    Menu

*/

void menu(){
    int opcionPrincipal;
    bool repetir = true;

    do{
        cout <<"1. Creacion del arbol binario" << endl;
        cout <<"2. Opciones del arbol binario" <<endl,

        cout <<"Ingrese una opcion: "<<endl;
        cin >> opcionPrincipal;

        if(opcionPrincipal == 1){
            //Metodo de la creacion del arbol binario creado a la manera del usuario.

        }
        if(opcionPrincipal == 2){
            int opcionSegundaria;
            cout << "1. Personas" << endl;
            cout << "2. Consultas" << endl;
            cout << "3. Reportes" << endl;

            cout <<"Ingrese una opcion: "<<endl;
            cin >> opcionSegundaria;
            if(opcionSegundaria == 1){

            }
            if(opcionSegundaria == 2){

            }
            if(opcionSegundaria == 3){

            }
        }

    }while(repetir);

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
