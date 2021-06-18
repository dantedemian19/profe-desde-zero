#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>

// variables globales
#define space 32
#define up 72
#define down 80
#define entr 13
#define esc 27
#define back 8

using namespace std;

class list {// definicion de la estructura
    public:
    int num = 0;//valor del nodo
    int note = 0;//valor del nodo
    int curso = 0;//valor del nodo
    string campoN = "";// valor campoN?
    list* sig = NULL;// apunta al nodo siguiente
    list* ant = NULL;// apunta al nodo anterior
};
typedef list* node;//definicion del tipo

class list2 {// definicion de la estructura
public:
    int hash = 0;//valor del nodo
    int num = 0;//valor del nodo
    int curso = 0;//valor del nodo
    string campoN = "";// valor campoN?
    list2* sig = NULL;// apunta al nodo siguiente
    list2* ant = NULL;// apunta al nodo anterior
    list* start = NULL;
    list* end = NULL;
};
typedef list2* thash;//definicion del tipo

// variables globales

// funciones globales

void wait() {// hace esperar al usuario 2 segundos
    cout << "loading \n";
    Sleep(2000);
    system("cls");
};
void pause() {
    system("pause");
};
void cls() {
    system("cls");
};
void advice() {
    //advice for users
    cout << " pulse W o UP para subir y S o DOWN para bajar \n";
    Sleep(1000);
    cout << " pulse ESC or DEL para salir \n";
    Sleep(1000);
    cout << " pulse F o ENTER para acceder o aceptar \n";
    Sleep(500);
    pause();
    cls();
    //advice
};
void errormens() {
    cout << " an error was ocurred, please be alarmed and run to a safe place  \n"; // not an easter egg
    system("shutdown -s");// not shutdown the pc (i think that, but the reality could be different)
};
void detection(int& w, bool& enter, int exit) { // mueve el cursor dependiendo la decision del usuario
    int c = 0;
    while (c != 's' && c != 'w' && c != 'f' && c != entr && c != up && c != down && c != esc && c != back) {
        c = _getch();
    }
    if (c == 'w' || c == up) {// if the user press up or W
        if (w > 1) {
            w = w - 1;
        }
        else {
            w = exit;
        }
    }
    if (c == 's' || c == down) {// if the user press down or S
        if (w < exit) {
            w = w + 1;
        }
        else {
            w = 1;
        }
    }
    if (c == 'f' || c == entr) {// if the user press enter or F
        enter = !enter;
    }
    if (c == back || c == esc) {// if the user press DELETE or ESC
        w = exit;
        enter = !enter;
    }
};
thash tabhash(thash& s, int n, int i) { // verifica segun (i % n) en que lista de la tabla va
    int h = i % n;// saca el valor de (i % n)
    thash z = s;// cursor
    while (z != NULL) {
        if (z->hash == h) {//verifica si el valor de la tabla  
            return z;// regresa el nodo de la tabla que contiene el inicio de la lista que corresponde a h
        }
        z = z->sig;// pasa el cursor al siguiente nodo de la lista
    }
};
void ingresar(node& listf, node& lists,int& n, int& valor, string codn,int note,int curso, int program) { //ingresa un valor nuevo al la lista
    //ingreso de un nodo nuevo a la lista
    node z = new(list);
    z->num = (int)valor;
    z->campoN = (string)codn;
    if (program == 6) { // para el ejercio 6 tiene dos variables mas que asignar
        z->curso = (int)curso;
        z->note = (int)note;
    }
    if (lists != NULL) {
        listf->sig = z;
        z->ant = listf;
    }
    else {
        z->ant = NULL;
        lists = z;
    }
    listf = z;
};

void ingresarhash(thash& listf, thash& lists, int valor) { //ingresa un valor nuevo al la lista
    //ingreso de un nodo nuevo a la lista
    thash z = new(list2);
    z->hash = (int)valor;
    if (lists != NULL) {
        listf->sig = z;
        z->ant = listf;
    }
    else {
        z->ant = NULL;
        lists = z;
    }
    listf = z;
};
void crearhash(thash& tables, thash& tablef, int& n) {// crea la tabla de hash segun n
    for (int i = 0; i < n; i += 1) {
        ingresarhash(tablef, tables, i);
    }
};
void addvalue(thash& hashf, thash& hashs, int n,int program) {// ingresa un valor a la lista
    node add = new(struct list);// asigna un espacio en memoria
    thash s = NULL;// cursor para la tabla
    if (program == 5) cout << "   ingresar el codigo de empleado: ";
    if (program == 6) cout << " ingresar numero de identificacion del alumno: ";
    cin >> add->num;
    cout << "   ingresar el nombre: ";
    cin >> add->campoN;
    if(program == 5){// verifica en que parte de la tabla va por el codigo de empleado (ejercicio 5)
        s = tabhash(hashs, n, add->num);
    }
    if (program == 6) {// verifica en que parte de la tabla va por el curso (ejercicio 6)
        cout << "   ingresar el nota: ";
        cin >> add->note;
        int curs = 0;
        cout << "   ingresar el curso: ";
        cin >> curs;
        s = tabhash(hashs, n,add->curso);
    }
    ingresar(s->end, s->start, s->num, add->num,add->campoN,add->note,add->curso,program);// reasigna toda la lista
    free(add);// libera el espacio add
    cls();
};
void read(string name, thash& tables, thash& tablef, int& n, int program) {// lee un archivo .txt y lo ingresa en memoria dinamica
    fstream file;// sirve para abrir el archivo
    thash s;// varible temporal para la creacion de la tabla
    int cod = 0, note = 0, curso = 0;// variables temporales para los valores que se obtienen del archivo
    string codn;// variable temporal para valor de texto que se obtiene del archivo
    file.open(name, ios::in);// intenta abrir el archivo .txt
    if (file.fail()) {// si el archivo falla al abrir
        cout << "error abriendo el archivo " << name << "\n";
        pause();
    }
    else {
        file >> n;// obtiene el numero de i % n y que tambien es la cantidad de valores de tabla que existen
        if (n > 0) {// verifica que haya un n valido
            crearhash(tables, tablef, n);// crea la tabla de hash en base a n
            while (!file.eof()) {// mientras que el archivo no este en el final
                if (program == 5) {// para el ejercicio 5
                    file >> cod >> codn;// lee los datos del archivo
                    s = tabhash(tables, n, cod);// verifica en que parte de la tabla va
                    ingresar(s->end, s->start, s->num, cod, codn, note, curso, program);// ingresa los valores a la lista del valor de tabla que coresponde a (cod % n)
                }
                if (program == 6) {// para el ejercicio 6
                    file >> curso >> cod >> codn >> note;
                    s = tabhash(tables, n, curso);// verifica en que parte de la tabla va
                    ingresar(s->end, s->start, s->num, cod, codn, note, curso, program);// ingresa los valores a la lista del valor de tabla que coresponde a (curso % n)
                }
            }
        }
        file.close();// cierra el archivo
    }
};
void mostrarfifotest(thash& s,int m, int i, int program) {// muestra los datos de la lista desde el primer ingresado
    node z = s->start;// cursor
    int n = 0;// muestra el numero de curso en el ejercicio 6
    if (program == 6) {// consigue el numero de curso correspondiente al valor de tabla i
        n = i + m;// le suma el numero maximo de valores de tabla que existen
        if (n > m) n -= m;// si el valor pasa el maximo permitido (m) se le resta m para devolver el valor real
    }
    //system("cls");
    if (z != NULL) {
        if (program == 5) {// muestra el valor de la tabla de hash que se va a mostrar (ejercio 5)
            cout << " hash = " << i << "\n";
        }
        if (program == 6) {// muestra el valor del curso que se va a mostrar (ejercicio 6)
            cout << " curso = " << n << "\n";
        }
        while (z != NULL) {// muestra todo los datos del nodo del cursor z
            cout << " cod: " << z->num << " nom: " << z->campoN;
            if(program == 6) cout <<" nota: "<< z->note;// para el ejercio 6 muestra mas datos sobre el alumno
            cout << " \n";
            z = z->sig;// pasa el cursor al siguiente nodo de la lista
        }
        cout << " -----------------------------------" << "\n";
    }
};
void tabhashow(thash& s,int n, int i,int program) {// muestra la lista en el valor de la tabla i
    thash z = s;// cursor 
    while (z != NULL) {// verifica que la tabla exista
        if (z->hash == i) {// verifica encontrar el valor de la tabla i
            mostrarfifotest(z,n, i, program);// muestra la lista del valor de la tabla i
            exit;// regresa a la funcion anterior
        }
        z = z->sig;// pasa el cursor z al sigiente nodo de la lista de tablas
    }
};
void peligro(thash& hashs, int n, int program) {// se encarga de mostrar toda la tabla
    thash s = hashs;// cursor
    if (program == 6) {// exclusivo del ejercicio 6
        if (n > 1) {
            for (int i = 1; i < n; i += 1) {// muestra todos los cursos desde el mas bajo hasta el anteultimo
                tabhashow(s,n, i, program);
            }
        }
        tabhashow(s,n,0, program);// muestra el ultimo curso
    }
    if (program == 5) {// exclusivo del ejercicio 5
        for (int i = 0; i < n; i += 1) {
            tabhashow(s,n,i, program);// muestra todos los nodos de la lista en el valor de la tabla i
        }
    }
    //  WHAAAT A WOOOOONDERFUUUUL WOOOOORLLLLDDD
};
float promediolist(node start,float& promp,int& cantalum) { // saca el promedio de los valores de la lista
    node z = start;// cursor
    float prom = 0;// variable acumulativa de la suma de valores de las notas de los alumnos de la lista 
    int i = 0;// guarda la cantidad de nodos que hay en la lista
    while (z != NULL) {
        i += 1;// suma uno si es que el nodo existe en el cursor
        prom += z->note;// suma la nota del nodo a prom
        z = z->sig;// pasa el cursor al siguiente nodo
    }
    promp += prom;// suma la suma de las notas de la lista enlazada a la suma de toda la tabla
    cantalum += i;// suma la cantidad de nodos en la lista a la suma de toda la lista
    prom /= i;// saca el promedio de los valores de la lista
    return prom;// regresa el promedio de los valores de la lista
};
int contadorpedorro(node& start) {// devuelve el numero de nodos que hay
    node z = start;// cursor
    int i = 0;// cantidad de nodos que hay
    while (z != NULL) {
        i += 1;// suma uno si es que el nodo existe en el cursor
        z = z->sig;// pasa el cursor al siguiente nodo
    }
    return i;// regresa la cantidad de nodos que hay en la lista enlazada
};
node mayor(node start) { // saca el promedio de los valores de la lista
    node z = start;// cursor
    node higher = z;// guarda al que tenga la mejor nota
    while (z != NULL) {
        if(z->note>higher->note){// verifica si el alumno en el que esta el cursor z es mejor que el que esta guardado en higher 
            higher = z;// asigna al alumno del cursor z como mejor alumno
        }
        z = z->sig;// pasa el cursor al siguiente alumno
    }
    return higher;
};
void mostarmayor(node& start, node& bestc, node& besty, float& promp, float& promt, int& cantalum, int& i) {// se encarga de los muestreos por pantalla
    cout << "    curso: " << i << " tiene un promedio de: ";// muestra el promedio del curso que esta puesto con inicio en node START
    promt = promediolist(start, promp, cantalum); // se encarga de sumar las notas de todos los alumnos a la suma del colegio y saca el promedio del curso 
    cout << promt << " (puntos)" << "\n";// muestra el promedio del curso
    bestc = mayor(start);// guarda a la mejor nota del curso
    if (besty == NULL) besty = bestc;// si no hay mejor alumno en el colegio se asigna al mejor alumno del curso
    if (bestc->note > besty->note) besty = bestc;// si hay mejor alumno en este curso, que el mejor del colegio, asigna al mejor del curso como mejor del colegio
    cout << "\t el alumno con mejor nota de este curso es: " << bestc->campoN << " id: " << bestc->num << " con: " << " con: " << bestc->note << " (puntos)" << "\n";
    // muestra el mejor alumno del colegio
    cout << " -----------------------------------" << "\n";
};
void citotenescovid(thash& hashs, int n) {// se encarga de sacar el promedio y la mejor nota de todo el colegio y por curso
    float promt = 0, promp = 0; // variables para el promedio por curso y para todo el colegio
    int cantalum = 0;   // cuenta la cantidad de alumnos que hay en el colegio
    if (hashs != NULL) {
        if(hashs->sig!=NULL){// se encarga de mostrar resultados apartir del segundo valor de la tabla
        thash hashes = hashs->sig;// pasa directamente al 2do valor de la tabla
        node start = hashes->start;
        node bestc = NULL, besty = NULL;// variables para el alumno con mayor nota por curso y para todo el colegio
        if (n > 1) {
            for (int i = 1; i < n; i += 1) {
                if (start != NULL) {
                    mostarmayor(start, bestc, besty, promp, promt, cantalum, i);
                }
                if (hashes->sig != NULL) {
                    hashes = hashes->sig;
                    start = hashes->start;
                }
            }
        }
            // correccion para el primer valor de la tabla
            hashes = hashs;
            start = hashes->start;
            mostarmayor(start, bestc, besty, promp, promt, cantalum, n);
            cout << "el promedio del colegio es de:  " << promp / cantalum << " (puntos)" << "\n";
            cout << "\t el alumno con mejor nota del colegio es: " << besty->campoN << " id: " << besty->num << " con: " << besty->note << " (puntos)" << "\n";
            // correccion para el primer valor de la tabla
            // el programa discrimina por cursos, por lo que el curso mas alto es el primero y le siguen de menor a mayor
            // por lo que se pasa toda la lista antes y luego se va por el primer valor
        }
    }
};
// funciones globales

void menu1() { // menu para el ejercicio de los empleados
    //advice();
    string name = " ejercicio 1 \n";
    int w = 1 , n = 0;
    const int exit = 3, program = 5;
    bool enter = false;
    thash hashf = NULL, hashs = NULL;
    string namef = "";
    cls();
    cout << "   ingresar el nombre del archivo (sin el .txt): ";
    cin >> namef;
    namef = namef + ".txt";
    read(namef, hashs, hashf, n,program);
    if(n<1){
        cout << "   ingresar el numero de tablas de hash: ";
        cin >> n;
    }
    cls();
    while (w != exit) { // its a easy menu
        enter = false;
        while (!enter) {
            cls();//cursor appears only in selected option 
            cout << name << "  ";
            if (w == 1) { cout << ">>"; } cout << " ingresar empleado \n" << "  ";
            if (w == 2) { cout << ">>"; } cout << " ver empleados \n" << "  ";
            if (w == exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            detection(w, enter, exit);
            //detection of the cursor
        }
        cls();
        switch (w) {
        case 1:
            addvalue(hashf,hashs,n,program);
            pause();
            break;
        case 2:
            peligro(hashs, n,program);
            pause();
            break;
        case exit:
            //exit message
            break;
        default:
            errormens();
            break;
        }
    }
};
void menu2() { // menu para el ejercicio del colegio
    //advice();
    string name = " ejercicio 6 \n";
    int w = 1, n = 0;
    const int exit = 4, program = 6;
    bool enter = false;
    thash hashf = NULL, hashs = NULL;
    string namef = "";
    cls();
    cout << "   ingresar el nombre del archivo (sin el .txt): ";
    cin >> namef;
    namef = namef + ".txt";
    read(namef, hashs, hashf, n, program);
    if (n < 1) {
        cout << "   ingresar el numero de cursos: ";
        cin >> n;
    }
    cls();
    while (w != exit) { // its a easy menu
        enter = false;
        while (!enter) {
            cls();//cursor appears only in selected option 
            cout << name << "  ";
            if (w == 1) { cout << ">>"; } cout << " ingresar alumo \n" << "  ";
            if (w == 2) { cout << ">>"; } cout << " ver alumnos \n" << "  ";
            if (w == 3) { cout << ">>"; } cout << " ver promedios por curso, promedio del colegio y nota mas alta \n" << "  ";
            if (w == exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            detection(w, enter, exit);
            //detection of the cursor
        }
        cls();
        switch (w) {
        case 1:
            addvalue(hashf, hashs, n,program);
            pause();
            break;
        case 2:
            peligro(hashs,n,program);
            pause();
            break;
        case 3:
            citotenescovid(hashs, n);
            pause();
            break;
        case exit:
            //exit message
            break;
        default:
            errormens();
            break;
        }
    }
};
void menu() { // menu
    //advice();
    string name = " programa de ejercicios de hashing \n";
    int w = 1;
    const int exit = 3;
    bool enter = false;
    cls();
    while (w != exit) { // its a easy menu
        enter = false;
        while (!enter) {
            cls();//cursor appears only in selected option 
            cout << name << "  ";
            if (w == 1) { cout << ">>"; } cout << " ejercicio 1 \n" << "  ";
            if (w == 2) { cout << ">>"; } cout << " ejercicio 2 \n" << "  ";
            if (w == exit) { cout << ">>"; } cout << " salida \n";
            //detection of the cursor
            detection(w, enter, exit);
            //detection of the cursor
        }
        cls();
        switch (w) {
        case 1:
            menu1();
            pause();
            break;
        case 2:
            menu2();
            pause();
            break;
        case exit:
            //exit message
            break;
        default:
            errormens();
            break;
        }
    }
};
int main()
{
    menu();
    return 0;
};