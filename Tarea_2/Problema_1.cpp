#include<iostream>
#include <fstream>
#include<string>
using namespace std;
typedef char tElemLista; 

//Estructura Nodo.
struct tNodo{
    tElemLista info;
    tNodo* sig;
};


//Clase tLista.
class tLista{
    private:
        tNodo* head;
        tNodo* tail;
        tNodo* curr;
        unsigned int listSize;
        unsigned int pos;
    public:
        tLista();
        int insert(tElemLista);
        void moveToStart();
        void moveToEnd();
        void prev();
        void next();
        int getsize();
        void printcurr(ofstream&);
        void clearList();
};


//Constructor de la clase tLista.
tLista::tLista(){
    head = tail = curr = new tNodo;
    listSize = 0;
    pos = 0;
}


/*****
* void tLista::clearList.
******
* Al llamar a la funcion, elimina la lista, inicializandola (head, tail y curr) en new.
******
* Input:
* No tiene entradas.
* Returns:
* Al ser una funcion tipo void no retorna nada.
*****/
void tLista::clearList(){
    head = tail = curr = new tNodo;
    listSize = 0;
    pos = 0;
}


/*****
* int tLista::insert.
******
* Al llamar a la funcion, inserta el elemento item a la lista enlazada.
******
* Input:
* tElemLista item:    Recibe un item tipo tElemLista el que se inserta en la lista. 
******
* Returns:
* Retorna la posicion en la cual se inserto.
*****/
int tLista::insert(tElemLista item){
    tNodo* aux = curr->sig;
    curr->sig = new tNodo;
    curr->sig->info = item;
    curr->sig->sig = aux;
    if (curr == tail) tail = curr->sig;
    listSize++;
    return pos;
}


/*****
* int tLista::getsize.
******
* Al llamar a la funcion, guarda el largo de la lista.
******
* Input:
* No tiene entradas.
* Returns:
* Retorna el largo de la lista (cantidad de nodos).
*****/
int tLista::getsize(){
    int h = listSize;
    return h;
}


/*****
* void tLista::printcurr.
******
* Al llamar a la funcion, añade cada nodo a la linea del archivo de salida.
******
* Input:
* ofstream& out:    Recibe un string que contiene el nombre del archivo para insertar los elementos.
* Returns:
* Al ser una funcion tipo void no retorna nada.
*****/
void tLista::printcurr(ofstream& out){
    out << curr->info;
}


/*****
* void tLista::moveToStart.
******
* Al llamar a la funcion, se posiciona al inicio de la lista.
******
* Input:
* No tiene entradas.
* Returns:
* Al ser una funcion tipo void no retorna nada.
*****/
void tLista::moveToStart(){ 
    curr = head; 
    pos = 0; 
}


/*****
* void tLista::moveToEnd.
******
* Al llamar a la funcion, se posiciona al final de la lista.
******
* Input:
* No tiene entradas.
* Returns:
* Al ser una funcion tipo void no retorna nada.
*****/
void tLista::moveToEnd(){
    curr = tail;
    pos = listSize -1 ;
}


/*****
* void tLista::prev.
******
* Al llamar a la funcion, retorcede al nodo anterior de la lista.
******
* Input:
* No tiene entradas.
* Returns:
* Al ser una funcion tipo void no retorna nada.
*****/
void tLista::prev(){
    tNodo* temp;
    if (curr == head) return;
    temp = head;
    while (temp->sig != curr) temp = temp->sig;
    curr = temp;
    pos--;
}


/*****
* void tLista::next.
******
* Al llamar a la funcion, avanza hacia el siguente nodo.
******
* Input:
* No tiene entradas.
* Returns:
* Al ser una funcion tipo void no retorna nada.
*****/
void tLista::next(){ 
    if (curr != tail){ 
        curr = curr->sig; 
        pos++;
    } 
}


int main(){
    tLista cara;
    string nombreArchivo = "teclado-entrada.txt";
    int iter = 0, q, n;
    ifstream archivo(nombreArchivo.c_str());
    string linea;
    ofstream arch_salida;
    arch_salida.open("teclado-salida.txt");
    while (getline(archivo, linea)){
        q = 0;
        n = 0;
        while(n < linea.length()){
            if(linea[n] != '\n' && linea[n] != '\r'){
                if(linea[n] == '['){
                cara.moveToStart();
                }else if(linea[n] == ']'){
                    cara.moveToEnd();
                }else if(linea[n] == '>'){
                    cara.next();
                }else if(linea[n] == '<'){
                    cara.prev();
                }else{
                    cara.insert(linea[n]);
                    cara.next();
                }
            }
            n++;    
        }
        cara.moveToStart();
        cara.next();
        while(q < cara.getsize()){
            cara.printcurr(arch_salida);
            cara.next();
            q++;
        }
        cara.clearList();
        arch_salida << endl;
    }
    arch_salida.close();
    return 0;
}