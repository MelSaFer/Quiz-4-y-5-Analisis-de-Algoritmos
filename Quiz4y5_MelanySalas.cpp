/*
Análisis de algoritmos
Melany Salas Fernández
Carné: 2021121147
*/

#include <iostream>
#include <list>
#include <cmath>


using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------------------
int costo(int N, int M, int x[], int y[]) {
   	//y con N - M con x
   	int max;

   	if(N > M){ //1 tiempo de comparaciones
   	   max = N; //1 tiempo de asignacion
   	}else{
   	   max = M; //1 tiempo de asignacion
   	}

   	int sumM=0; //1 tiempo de asignacion
   	int sumN=0; //1 tiempo de asignacion 
   	//-> Total parcial: 4

   	for(int i = 0; i < max; i++){ //1 tiempo de asignacion + (1 tiempo de comparacion + 1 tiempo de asignacion + 1 tiempo de oa)
		if (i < M-1){ // 1 tiempo de comparacion + 1 tiempo de oa
			sumM += x[i]; // 1 tiempo de asignacion + 1 tiempo de oa + 1 tiempo de indexacion
		}
		if (i < N-1){ // 1 tiempo de comparacion + 1 tiempo de oa
			sumN += y[i]; // 1 tiempo de asignacion + 1 tiempo de oa + 1 tiempo de indexacion
      	}
  	}
	//-> Total parcial: 4 + 1 + (max)(13)

  	int resulVert = sumN + N*sumM; // 1 tiempo de asigacion + 2 tiempos de oa
   	//cout<< "Suma vert: " << resulVert << endl;
   	int resulHor = sumM + M*sumN; // 1 tiempo de asigacion + 2 tiempos de oa
   	//cout<< "Suma Hor: " << resulHor << endl;

   	//-> Total parcial: 4 + 1 + (max)(13) + 6

   
   	if (resulHor < resulVert){ //1 tiempo de comparaciones
      	return resulHor; //1 tiempo de return
   	} else
      	return resulVert;
	//-> Total: 4 + 1 + (max)(13) + 6 + 2
}
/*
a)
F(N)= 4 + 1 + (max)(13) + 6 + 2
    = 13 + 13mas
f(n)= 13 + 13n

b)
El peor de los casos es O(n)

c) 
Loop Invariant: El resultado es <= que x1 + x2 +...+ xM-1 + (y1 + y2 + ...  + yN-1)
                  tomando x1 + x2 +...+ xM-1 + (y1 + y2 + ...  + yN-1) como el costo máximo

Demostracion:
Con un chocolate de 3x5 con los valores {5,3} y {2, 10, 9, 4} respectivamente: 
               -> Si comienzo vertical obtendria: 5 + 3 + 3( 2 + 10 + 9 + 4) = 83
               -> Si comienzo vertical obtendria: 2 + 10 + 9 + 4 + 5(5+3) = 65
   Mi resultado debe ser siempre inferior o igual al costo mayor, por lo que obtener un resultado mayor a
83 indicaria que el algoritmo esta fallando.
*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
void radixSort(int *arr, int n, int max) { 
	int i, j, m, p = 1, index, temp, count = 0; // 2 tiempos por asignaciones = 2
   	list<int> pocket[10];      //radix of decimal number is 10  //1 tiempo por asignacion = 1
   	//1 tiempo de asignacion = 1
   	//-> Total parcial: 3 + 1
   	for(i = 0; i < max; i++) {    //1 tiempo de comparacion + 1 tiempo de asignacion + 1 tiempo de operacion aritmetica = 3
     	m = pow(10, i+1); // 1 tiempo de asignacion + 2 tiempos de llamadas a funciones + 2 tiempos por paso de parametros + 1 tiempo de operacion aritmetica = 6
      	p = pow(10, i); // 1 tiempo de asignacion + 2 tiempos de llamadas a funciones + 2 tiempos por paso de parametros = 5
      	//1 tiempo de asignacion = 1
   		//->13n
      	for(j = 0; j < n; j++) {  //1 tiempo de comparacion + 1 tiempo de asignacion + 1 tiempo de operacion aritmetica = 3
        	temp = arr[j]%m;  //1 tiempo de asignacion + 1 tiempo de operacion aritmetica + 1 tiempo de indexacion = 3
        	index = temp/p;      //find index for pocket array //1 tiempo de asignacion + 1 tiempo de operacion aritmetica = 2
        	pocket[index].push_back(arr[j]);  //2 tiempos de indexacion + 2 tiempos de llamadas a funciones + 1 tiempo por paso de parametros = 5
      	}
      	count = 0;  //1 tiempo de asigacion = 1
      	//1 tiempo de asigacion = 1
		// -> 10 *( 3 + 18n) = 30 + 180n
      	for(j = 0; j < 10; j++) { //1 tiempo de comparacion + 1 tiempo de asignacion + 1 tiempo de operacion aritmetica = 3
         	//delete from linked lists and store to array
         	//->SE HACE N VECES ->18n
         	while(!pocket[j].empty()) {  //1 tiempo de indexacion + 2 tiempos de llamadas a funciones + 1 tiempo de comparacion = 4
            	arr[count] = *(pocket[j].begin());  //2 tiempos de indexacion + 2 tiempos de llamadas a funciones + 1 tiempo de asignacion = 5
            	pocket[j].erase(pocket[j].begin());  //2 tiempos de indexacion + 4 tiempos de llamadas a funciones + 1 tiempo por paso de parametros = 7
            	count++;  //1 tiempo de asignacion + 1 tiempo de operacion aritmetica = 2
            	
         	}
      	}
   	}
   	//-> Total parcial: 3 + 1 + max(14+ 1 + 13n + 2 + 30 + 180n)
}
/*
a)
NOTA= K es equivalente a max
F(N)= 3 + 1 + k(14 + 1 + 13n + 2 + 30 + 180n)
    = 4 + 47k + 13kn + 180kn
	= 4 + 47k + 193kn

b)
El peor de los casos es O(kn) y se da cuando tenemos un algoritmo en que el array list donde hay una gran difrentencia entre la cantidad de digitos significativamente
mayor entre el numero maximo y esl resto

c) 
Loop Invariant: Los números estan ordenados si tomamos en cuenta los digitos del menos significativo hasta el que esta en la posicion i
				-> Cada numero del array, viendo sus num%10^i digitos, estan ordenados.
*/

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
int main(){
	//LISTAS USADAS EN LAS PRUEBAS
    int list[5]= {2,1000,600,10,3};
	int list2[4]={2, 10, 9, 4};
    int list3[2]= {5,3};
	int listX[2]={8, 2};

	cout << "-----------------------------Prueba Radix Sort-----------------------------" << endl;
   	radixSort(list, 5, 4);
    for(int i = 0; i < 5; i++){
        cout << list[i] << " - ";
    }

	cout << "\n\n---------------------------Prueba Funcion Costo----------------------------" << endl;
	cout << "\nPruebas con N = 3, M = 5, X = {2, 10, 9, 4}, Y = {5, 3}" << endl;
    cout << "Resultado: " << costo(3, 5, list2, list3) << endl;

	cout << "\nPruebas con N = 5, M = 3, Y = {2, 10, 9, 4}, M = {5, 3}" << endl;
    cout << "Resultado: " << costo(5, 3, list3, list2) << endl;

	cout << "\nPruebas con N = 3, M = 3, Y = {8, 2}, M = {8, 2}" << endl;
    cout << "Resultado: " << costo(3, 3, listX, listX) << endl;


}
