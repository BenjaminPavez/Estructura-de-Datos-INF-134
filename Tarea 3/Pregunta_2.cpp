#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;
#define INT_MAX 100000


const int V = 78;



//Se definen variables "globales"
int prin;
int secundario = -1;
int sec;
int contador_global_di = 0;
int contador_global_dp = 0;



/*****
* int minima_distancia()
******
* La funcion calcula la minima distancia entre vertices para luego almacenarlo en variables.
******
* Input:
* int dist[] : La funcion recibe un arreglo entero que almacenan las minimas distancias entre los vertices.
* bool sptSet[] : La funcion recibe un arreglo booleanos que almacena false si no hay nada almacenado.
******
* Returns:
* La funcion retorna un entero con la minima distancia.
*****/
int minima_distancia(int dist[], bool sptSet[]){
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 


/*****
* void solucion()
******
* La funcion itera sobre el arreglo obtenido y agrega otros parametros como los contadores para funciones posteriores.
******
* Input:
* int dist[] : La funcion recibe una arreglo donde se encuentran almacenados los caminos mas cortos.
******
* Returns:
* Al ser una funcion tipo void, no retorna nada.
*****/
void solucion(int dist[]){
    for (int i = 0; i < V; i++){
        if(i>0 && dist[i]>secundario && dist[i]<INT_MAX){
            secundario = dist[i];
            sec = i;
        }
        contador_global_di++;
        contador_global_dp+=dist[i];
    }
}



/*****
* void dijkstra()
******
* La funcion recorre el grafo y busca el camino mas corto desde un vertice hacia todos los demas.
******
* Input:
* int graph[V][V] : La funcion recibe una matriz adyacente con la informacion del grafo.
* int src : La funcion recibe un entero representando el origen del grafo, a partir de el buscara el camino mas corto.
******
* Returns:
* Al ser una funcion tipo void, no retorna nada.
*****/
void dijkstra(int graph[V][V], int src){
    int dist[V]; 
    bool sptSet[V]; 
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    //dist[src] = 0;
 
    for (int count = 0; count < V - 1; count++){
        int u = minima_distancia(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    solucion(dist);
}



/*****
* void traductor()
******
* La funcion recorre el archivo csv y transforma el numero el nombre del personaje.
******
* Input:
* string name_arch : String que contiene el nombre del archivo con el numero de nodo y el nombre.
* int nodo : Entero que representa el numero del nodo que hay que traducir.
* string& traduccion : String que entrega la traduccion.
******
* Returns:
* Al ser una funcion tipo void, no retorna nada
*****/
void traductor(string name_arch, int nodo, string& traduccion){
    ifstream arch(name_arch);
    string line;
    char deli = ',';
    // Leemos la primer línea para descartarla, pues es el encabezado
    getline(arch, line);
    // Leemos todas las líneas
    while (getline(arch, line)){
        stringstream stream(line);
        string Id,Label;
        getline(stream, Id, deli);
        getline(stream, Label, deli);
        if(nodo == stoi(Id)){
            traduccion = Label;
        }
    }
    arch.close();

}



/*****
* string personaje_principal()
******
* La funcion recorre la matriz de adyacencia buscando el nodo con mayor grado, y luego busca el nombre en el archivo.
******
* Input:
* int matriz_adj[V][V] : La funcion recibe una matriz adyacente con la informacion del grafo.
******
* Returns:
* La funcion retorna un string con el nombre del personaje principal.
*****/
string personaje_principal(int matriz_adj[V][V]){
    string name_principal;
    int j, var3 = 1, principal = -1;
    int count = 0;
    for(int i=1; i<=V; i++){
        for(j=1; j<=V; j++){
            if(matriz_adj[i][j] != 0){
                count++;
            }
        }
        if(count>principal){
            prin = matriz_adj[var3][0];
            principal = count;
        }
        var3++;
        count = 0;
    }
    traductor("miserables_id_to_names.csv", prin, name_principal);
    return name_principal;
}



/*****
* string personaje_secundario()
******
* La funcion busca utilizando dijkstra la distancia mayor a la del personaje principal. 
******
* Input:
* int matriz_adj[V][V] : La funcion recibe una matriz adyacente con la informacion del grafo.
******
* Returns:
* La funcion retorna un string con el nombre del personaje secundario.
*****/
string personaje_secundario(int matriz_adj[V][V]){
    string name_secundario;
    dijkstra(matriz_adj, prin);
    traductor("miserables_id_to_names.csv", sec, name_secundario);
    return name_secundario;
}



/*****
* int combinatoria()
******
* La funcion calcula total de combinaciones de pares de vértices posibles que se pueden obtener. 
******
* Input:
* int val_superior : Corresponde al valor superior en la combinatoria.
* int val_inferior : Corresponde al valor inferior en la combinatoria.
******
* Returns:
* La funcion retorna un entero con la formula de la combinatoria.
*****/
int combinatoria(int val_superior, int val_inferior){
    int formula;
    int factorial_1 = 1, factorial_2 = 1, resta = val_superior - val_inferior;
    for(int f_1 = resta+1; f_1<=val_superior; f_1++){
        factorial_1 *= f_1;
    }
    for(int f_2 = 1; f_2<=val_inferior; f_2++){
        factorial_2 *= f_2;
    }
    formula = (factorial_1/factorial_2);
    cout<<formula<<endl;
    return formula;
}



/*****
* float averageDistance()
******
* La funcion realiza dijkstra con todos los nodos del grafo, para luego calcular la longitud de los caminos promedios.
******
* Input:
* int matrix[V][V] : La funcion recibe una matriz adyacente con la informacion del grafo.
******
* Returns:
* La funcion retorna un flotante con el diametro sin contar los pesos del grafo.
*****/
float averageDistance(int matrix[V][V]){
    float diametro, combinacion;
    for(int n = 1; n<=V; n++){
        dijkstra(matrix, n);
    }
    combinacion = combinatoria(77,2);
    diametro = (contador_global_di/combinacion);
    return diametro;

}



/*****
* float averageWeightedDistance()
******
* La funcion calcula la longitud de los caminos promedios considerando los pesos, apartir de informacion obtenida de la funcion averageDistance().
******
* Input:
* No recibe ninguna entrada, ya que dentro de la funcion averageDistance se agrego parametros como contador_global_dp.
******
* Returns:
* La funcion retorna un flotante con el diametro contando los pesos del grafo.
*****/
float averageWeightedDistance(){
    float diametro_pesos;
    diametro_pesos = (contador_global_dp/contador_global_di);
    return diametro_pesos;
}


int main(){
    //Se crea la matriz de adyacencia a partir del archivo csv
    int max_peso = -1, var2 = 0;
    string name_node1, name_node2, name_principal, linea, secu;
    char delimitador = ';';
    bool flag = true;
    ifstream archivo("miserables.csv");

    //Prueba
    int AdjMatrix[V][V];

    while (getline(archivo, linea)){
        stringstream input_stringstream(linea);
        string numero;
        int var1 = 0;
        while(getline(input_stringstream, numero, delimitador)){
            if(flag == true){
                numero = '0';
                AdjMatrix[var1][var2] = stoi(numero);
                flag = false;
            }else{
                AdjMatrix[var1][var2] = stoi(numero);
            }
            var1++;
        }
        var2++;
    }
    archivo.close();
    

    
    //Declaracion de variables para llamar a las funciones
    string nombre_principal, nombre_secundario;
    
    nombre_principal = personaje_principal(AdjMatrix);
    nombre_secundario = personaje_secundario(AdjMatrix);
    float diam, diam_pesos;
    diam = averageDistance(AdjMatrix);
    diam_pesos = averageWeightedDistance();
    

    
    //Salida
    cout<<"Personaje Principal: "<<nombre_principal<<endl;
    cout<<"Personaje Secundario: "<<nombre_secundario<<endl;
    cout<<"Diametro: "<<diam<<endl;
    cout<<"Diametro ( con pesos ): "<<diam_pesos<<endl;
    
}
