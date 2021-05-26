#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

// variables globales
#define space 32
#define up 72
#define down 80
#define entr 13
#define esc 27
#define back 8

struct list {// definicion de la estructura
    int num = 0;//valor del nodo
    int note = 0;//valor del nodo
    int curso = 0;//valor del nodo
    string campoN = "";// valor campoN?
    struct list* sig = NULL;// apunta al nodo siguiente
    struct list* ant = NULL;// apunta al nodo anterior
};
typedef struct list* node;//definicion del tipo

struct list2 {// definicion de la estructura
    int hash = 0;//valor de la tabla de hash
    int num = 0;// valor de la cantidad de nodos en el hash
    struct list* start = NULL;// apunta al valor de inicio del hash
    struct list* end = NULL;// apunta al valor de final del hash
    struct list2* sig = NULL;// apunta al nodo siguiente
    struct list2* ant = NULL;// apunta al nodo anterior
};
typedef struct list2* thash;//definicion del tipo

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
thash tabhash(thash& s, int n, int i) {
    int h = i % n;
    thash z = s;
    while (z != NULL) {
        if (z->hash == h) {
            return z;
        }
        z = z->sig;
    }
};
void ingresar(node& listf, node& lists,int& n, int& valor, string codn,int note,int curso, int program) { //ingresa un valor nuevo al la lista
    //ingreso de un nodo nuevo a la lista
    node z = new(struct list);
    z->num = (int)valor;
    z->campoN = (string)codn;
    if (program == 6) { 
        z->curso = curso;
        z->note = note;
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
    thash z = new(struct list2);
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
void addvalue(thash& hashf, thash& hashs, int n,int program) {
    node add = new(struct list);
    thash s = NULL;
    if(program == 5) cout << "   ingresar el codigo de empleado: ";
    if (program == 6) cout << "ingresar numero de identificacion del alumno: ";
    cin >> add->num;
    cout << "   ingresar el nombre: ";
    cin >> add->campoN;
    if(program == 5){
        s = tabhash(hashs, n, add->num);
    }
    if (program == 6) {
        cout << "   ingresar el nota: ";
        cin >> add->note;
        int curs = 0;
        cout << "   ingresar el curso: ";
        cin >> curs;
        s = tabhash(hashs, n,add->curso);
    }
    ingresar(s->end, s->start, s->num, add->num,add->campoN,add->note,add->curso,program);
    free(add);
    cls();
};
void read(string name, thash& tables, thash& tablef, int& n, int program) {// lee un archivo binario y lo ingresa en memoria dinamica
    fstream file;// sirve para abrir el archivo
    thash s;
    int cod = 0, note = 0, curso = 0;
    string codn;
    file.open(name, ios::in);
    if (file.fail()) {
        cout << "error abriendo el archivo " << name << "\n";
        pause();
    }
    else {
        file >> n;
        if (n > 0) {
            crearhash(tables, tablef, n);
            while (!file.eof()) {
                if (program == 5) { 
                    file >> cod >> codn;
                    s = tabhash(tables, n, cod);
                    ingresar(s->end, s->start, s->num, cod, codn, note, curso, program);
                }
                if (program == 6) {
                    file >> curso >> cod >> codn >> note;
                    s = tabhash(tables, n, curso);
                    ingresar(s->end, s->start, s->num, cod, codn, note, curso, program);
                }
            }
        }
        file.close();
    }

};
void mostrarfifotest(thash& s, int i, int program) {// muestra el vector desde el primer ingresado
    node z = s->start;// cursor
    int n = 0;
    if (program == 6) {
        n = i + 6;
        if (n > 6) n -= 6;
    }
    //system("cls");
    if (z != NULL) {
        if (program == 5) {
            cout << " hash = " << i << "\n";
        }
        if (program == 6) {
            cout << " curso = " << n << "\n";
        }
        while (z != NULL) {
            cout << " cod: " << z->num << " nom: " << z->campoN;
            if(program == 6) cout <<" nota: "<< z->note;
            cout << " \n";
            z = z->sig;
        }
        cout << " -----------------------------------" << "\n";
    }
};
void tabhashow(thash& s, int i,int program) {
    thash z = s; 
    while (z != NULL) {
        if (z->hash == i) {
            mostrarfifotest(z, i, program);
            exit;
        }
        z = z->sig;
    }
};
void peligro(thash& hashs, int n, int program) {
    thash s = hashs;
    if (program == 6) {
        for (int i = 1; i < n; i += 1) {
            tabhashow(s, i, program);
        }
        tabhashow(s, 0, program);
    }
    if (program == 5) {
        for (int i = 0; i < n; i += 1) {
            tabhashow(s, i, program);
        }
    }
    //  WHAAAT A WOOOOONDERFUUUUL WOOOOORLLLLDDD
}
// funciones globales
void menu1() { // menu
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
void menu2() { // menu
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
}
