#include<iostream>
using namespace std;

//Estructura Nodo.
struct Nodo{
    int dato;
    Nodo *der;
    Nodo *izq;
};


//Se define una variable arbol tipo Nodo y una variable entera que almacena el numero de iteraciones.
Nodo *arbol = NULL; 
int count = 0;

//Se define una flag para la funcion bool.
bool flag = NULL;


//Clase RankedABB.
class RankedABB {
    private:
        typedef int tElem;
    public:
        RankedABB();
        void insert(Nodo *&arbol,tElem x);
        bool find(Nodo *arbol,tElem x);
        int rank(Nodo *arbol,int &c,tElem x);
};

//Constructor del la clase RankedABB.
RankedABB::RankedABB (){
};


/*****
* Nodo *crear_Nodo.
******
* Al llamar a la funcion, crea un nuevo nodo para el arbol.
******
* Input:
* int n:    Recibe un numero entero y este lo añade al arbol.
******
* Returns:
* Retorna el nodo con el dato añadido y los respectivos punteros.
*****/
Nodo*crear_Nodo(int n){
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;

    return nuevo_nodo;
}


/*****
* void RankedABB::insert.
******
* Al llamar a la funcion, inserta un entero al arbol y lo posiciona.
******
* Input:
* Nodo *&arbol:    Recibe un arbol tipo nodo que contiene la informacion y sus respectivos punteros.
*       int n:     Por otra parte recibe un entero que representa el numero a agregar al arbol.
******
* Returns:
* Al ser una funcion tipo void, no retorna nada.
*****/
void RankedABB::insert(Nodo *&arbol,tElem x){
    if(arbol == NULL){
        Nodo *nuevo_nodo = crear_Nodo(x);
        arbol = nuevo_nodo;
    }
    else{
        int valorRaiz = arbol->dato;
        if(x < valorRaiz){
            insert(arbol->izq,x);
        }
        else{
            insert(arbol->der,x);
        }
    }
}


/*****
* bool RankedABB::find.
******
* Al llamar a la funcion, busca un elemento dentro del arbol.
******
* Input:
* Nodo *&arbol:    Recibe un arbol tipo nodo que contiene la informacion y sus respectivos punteros. 
*       int n:     Por otra parte recibe un entero que representa el numero que busca dentro del arbol.
******
* Returns:
* Retorna True si encuentra el elementro dentro del arbol y False si no esta.
*****/
bool RankedABB::find(Nodo *arbol,tElem x){
    for(int r=1;r<=1;r++){
        if(arbol == NULL){
            flag = false;
            break;
        }
        else{
            if(x > arbol->dato){
                find(arbol->der,x);
            }else if(x < arbol->dato){
                find(arbol->izq,x);
            }else if(x == arbol->dato){
                flag = true;
                break;
            }
        }
    }
    return flag;
    
}


/*****
* int RankedABB::rank.
******
* Al llamar a la funcion, busca la cantidad de elementos que son menores o iguales a lo pedido.
******
* Input:
* Nodo *arbol:    Recibe un arbol tipo nodo que contiene la informacion y sus respectivos punteros.
*       int n:    Por otra parte recibe un entero que representa el numero con el que se haran las comparaciones.
*       int c:    Finalmente recibe otro entero que representa un contador que itera cada vez que cumple con la condicion.
******
* Returns:
* Retorna un contador con la cantidad de veces que cumplio la regla.
*****/
int RankedABB::rank(Nodo *arbol,int &c,tElem x){
    for(int r=1;r<=1;r++){
        if(arbol == NULL){
            return c;
            break;
        }
        else{
            if(x >= arbol->dato){
                c++;
                rank(arbol->der,c,x);
            }else if(x <= arbol->dato){
                rank(arbol->izq,c,x);
            }
        }
    }
    return c;
}