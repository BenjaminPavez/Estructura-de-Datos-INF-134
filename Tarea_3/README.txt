Nombre: Benjamin Alejandro Pavez Ortiz

Rol USM: 202173628-K

IDE: Visual Studio Code

SO: Ubuntu 22.04.1 LTS

Compilador: g++ (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0 (WSL)

Instrucciones de Uso:

1) El programa funciona sin ningun problema

2) Para la pregunta 1 realizamos una version de prueba que utiliza todas la funciones creadas, para su uso, solo bastara copiar la prueba al final del archivo de la pregunta

//Prueba_1
int main(){
    CacheDiccionario obj1;
    string defi_palabra;
    int var1 = 0, var2 = 0, var3 = 0;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
    obj1.insert("Palabra1", "Definicion1");
    obj1.insert("Palabra2", "Definicion2");
    obj1.insert("Palabra3", "Definicion3");
    obj1.insert("Palabra4", "Definicion4");
    obj1.insert("Palabra5", "Definicion5");
    obj1.insert("Palabra6", "Definicion6");
    obj1.insert("Palabra1", "Definicion1");

    obj1.query("Palabra1", defi_palabra);
    obj1.query("Palabra1", defi_palabra);
    obj1.query("Palabra1", defi_palabra);
    obj1.query("Palabra1", defi_palabra);
    obj1.query("Palabra1", defi_palabra);
    obj1.query("Palabra1", defi_palabra);

    string otro;
    cout<<"_____________________________________"<<endl;
    obj1.query("Palabra10", otro);
    cout<<"_____________________________________"<<endl;

    obj1.query("Palabra2", defi_palabra);
    obj1.query("Palabra3", defi_palabra);
    obj1.query("Palabra4", defi_palabra);
    obj1.query("Palabra5", defi_palabra);
    obj1.query("Palabra6", defi_palabra);

    obj1.querystats(var1, var2, var3);
    cout<<"Total: "<<var1<<endl;
    cout<<"Conocidos: "<<var2<<endl;
    cout<<"Desconocidos: "<<var3<<endl;

    obj1.perfstats(v1, v2, v3, v4);
} 

Resultado esperado:

Insercion exitosa
Palabra1 = Definicion1
Clave insercion: 8
--------------------------------
Insercion exitosa
Palabra2 = Definicion2
Clave insercion: 24
--------------------------------
Insercion exitosa
Palabra3 = Definicion3
Clave insercion: 40
--------------------------------
Insercion exitosa
Palabra4 = Definicion4
Clave insercion: 56
--------------------------------
Insercion exitosa
Palabra5 = Definicion5
Clave insercion: 72
--------------------------------
Insercion exitosa
Palabra6 = Definicion6
Clave insercion: 88
--------------------------------
Insercion exitosa
Palabra1 = Definicion1
Clave insercion: 104
--------------------------------
Palabra Encontrada: Palabra1
Visitas: 1
Definicion: Definicion1
Palabra Encontrada: Palabra1
Visitas: 2
Definicion: Definicion1
Palabra Encontrada: Palabra1
Visitas: 3
Definicion: Definicion1
Palabra Encontrada: Palabra1
Visitas: 4
Definicion: Definicion1
Palabra Encontrada: Palabra1
Visitas: 5
Definicion: Definicion1
Palabra Encontrada: Palabra1
Visitas: 6
Definicion: Definicion1
_____________
Definicion: vacio
No se encontro
_____________
Palabra Encontrada: Palabra2
Visitas: 1
Definicion: Definicion2
Palabra Encontrada: Palabra3
Visitas: 1
Definicion: Definicion3
Palabra Encontrada: Palabra4
Visitas: 1
Definicion: Definicion4
Palabra Encontrada: Palabra5
Visitas: 1
Definicion: Definicion5
Palabra Encontrada: Palabra6
Visitas: 1
Definicion: Definicion6
Total: 12
Conocidos: 11
Desconocidos: 0
