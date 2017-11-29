#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

typedef vector< tuple<unsigned int, unsigned int, unsigned int> > vectorList;
typedef tuple<unsigned int, unsigned int> dronCoord;
typedef tuple<unsigned int, unsigned int, unsigned int> nodo;

//Agrega o no una tupla al contorno temporal que retorna merge().
void compararMenorConMayor( unsigned int x1, unsigned int h1temp,
							unsigned int h1, unsigned int h2, unsigned int x2,
							vectorList &c3 )
{
	if( h1temp > h2 || (h1temp == h2 && h1 > h2) ){
		nodo nd = tuple<unsigned int, unsigned int, unsigned int>(x1,h1temp,0);
		c3.push_back( nd );
	}
	else if( h1temp < h2 && h1 > h2 && x1 != x2 ){
		nodo nd = tuple<unsigned int, unsigned int, unsigned int>(x1,h2,0);
		c3.push_back( nd );
	}
}

//Une dos contornos en tiempo O(n1+n2) = O(n)
//Retorna un contorno temporal.
vectorList merge(vectorList &c1, vectorList &c2)
{
	vectorList c3;
	size_t n1 = c1.size(), n2 = c2.size();
	unsigned int h1 = 0, h2 = 0;
	size_t  i = 0, j = 0;
	//Avanza con un índice i y j en los comienzos de ambos contornos, avanzando
	//de uno en uno mientras se comparan los valores.
	while( i < n1 && j < n2 ){
		//Si la coordenada x del contorno 1 es menor que la coordenada x
		//del contorno 2.
		if( get<0>(c1.at(i)) < get<0>(c2.at(j)) ){
			unsigned int x1 = get<0>(c1.at(i));
			unsigned int h1temp = get<1>(c1.at(i));
			unsigned int x2 = get<0>(c2.at(j));

			//Función que revisa los distintos casos. Agrega o no una tupla
			//al contorno temporal c3.
			compararMenorConMayor(x1, h1temp, h1, h2, x2, c3);
			h1 = h1temp;
			i++;
		}
		else{
			unsigned int x2 = get<0>(c2.at(j));
			unsigned int h2temp = get<1>(c2.at(j));
			unsigned int x1 = get<0>(c1.at(i));

			compararMenorConMayor(x2, h2temp, h2, h1, x1, c3);
			h2 = h2temp;
			j++;
		}
	}
	//Cuando ya se acaba un contorno, simplemente agrega los demás del otro.
	while(i < n1){
		c3.push_back(c1.at(i));
		i++;
	}
	while(j < n2){
		c3.push_back(c2.at(j));
		j++;
	}
	return c3;
}

//Obtiene un contorno a partir de 2 subcontornos.El problema se divide en 2
//partes, y se hace recursividad por ambos lados. Calcula un contorno en tiempo
//O(nlogn).
//Retorna un contorno.
vectorList obtenerContorno(vectorList &arr, size_t start, size_t end)
{
	if(start == end){
		vectorList temp;
		nodo nd = tuple<unsigned int, unsigned int, unsigned int>(
			get<0>(arr.at(start)), get<1>(arr.at(start)), 0
		);
		temp.push_back( nd );
		nd = tuple<unsigned int, unsigned int, unsigned int>(
			get<2>(arr.at(start)), 0, 0
		);
		temp.push_back( nd );
		return temp;
	}
	size_t middle = (start + end)/2;

	vectorList c1 = obtenerContorno(arr, start, middle);
	vectorList c2 = obtenerContorno(arr, middle+1, end);

	vectorList c3 = merge(c1,c2);
	return c3;
}

//Busca si un dron choca con el contorno haciendo búsqueda binaria, por ende lo
//hace en tiempo O(logn).
//Retorna void.
void colision(vectorList &contorno, unsigned int start,
									unsigned int end, dronCoord &dron)
{
	//Por si las moscas, sin un dron tiene altura menor o igual a 0, choca.
	if( get<1>(dron) <= 0 ){
		cout << "true" << endl;
		return;
	}
	else{
		//Si sobrepasa al último elemento, 'retorna' false
		if(start == end){
			cout << "false" << endl;
			return;
		}
		int medio = (end+start)/2;
		//Se llega al primer elemento
		if(start == 0 && end == 1){
			//Si el dron está antes que el contorno, retorna false
			if( get<0>(dron) < get<0>(contorno.at(medio)) ){
				cout << "false" << endl;
				return;
			}
			else{
				//Si está después, verifica si choca.
				if( get<1>(dron) > get<1>(contorno.at(medio)) ){
					cout << "false" << endl;
					return;
				}
				else{
					cout << "true" << endl;
					return;
				}
			}
		}
		//Cae justo en una coordenada del contorno
		if( get<0>(contorno.at(medio)) == get<0>(dron) ){
			//Si la altura es mayor
			if( get<1>(contorno.at(medio)) >= get<1>(dron) ){
				cout << "true" << endl;
				return;
			}
			//Si la altura es menor, no necesariamente significa que no vaya a
			//chocar. Puede darse el caso donde se termina un edificio. Habrá
			//que verificar que la altura de la coordenada anterior también sea
			//mayor.
			else{
				if( get<1>(contorno.at(medio-1)) >= get<1>(dron) ){
					cout << "true" << endl;
					return;
				}
				//El dron está más alto que la coordenada y la coordenada
				//anterior.
				else{
					cout << "false" << endl;
					return;
				}
			}
		}
		//Verifica cuando el dron está entre medio de 2 coordenadas
		else if( get<0>(contorno.at(medio)) > get<0>(dron)
					&& get<0>(contorno.at(medio-1)) <= get<0>(dron) ){
			//Contorno es más alto, por lo que choca.
			if( get<1>(contorno.at(medio-1)) >= get<1>(dron) ){
				cout << "true" << endl;
				return;
			}
			//No choca.
			else{
				cout << "false" << endl;
				return;
			}
		}
		//Recursividad, sigue buscando
		else{
			//Si la coordenada x del dron es menor que el valor del medio del
			//contorno, se sigue buscando en la mitad de la izquierda.
			if( get<0>(dron) < get<0>(contorno.at(medio)) ){
				colision(contorno, start, medio, dron);
			}
			//Sigue buscando en la mitad de la derecha.
			else{
				colision(contorno, medio+1, end, dron);
			}
		}
	}
}

int main()
{
	vectorList edificios, contorno;
	int n;
	unsigned int X, Y, L, H, R;
	//Obtiene cantidad de edificios.
	cin >> n;
	//Agrega los edificios en formato de tupla (L,H,R) a un vector.
	for(int i = 0; i<n; i++){
		cin >> L >> H >> R;
		nodo nd = tuple<unsigned int, unsigned int, unsigned int>(L,H,R);
		edificios.push_back( nd );
	}
	//Obtiene el contorno en tiempo O(nlogn).
	contorno = obtenerContorno(edificios, 0, n-1);
	//Imprime la cantidad de puntos del contorno, y sus coordenadas.
	cout << contorno.size() << endl;
	for(size_t i = 0; i<contorno.size(); i++){
		cout << get<0>(contorno.at(i)) << " " << get<1>(contorno.at(i)) << endl;
	}
	//Obtiene la cantidad de drones.
	cin >> n;
	cout << n << endl;
	//Itera sobre los drones.
	for(int i = 0; i<n; i++){
		cin >> X >> Y;
		dronCoord dron ( tuple<unsigned int, unsigned int>(X,Y) );
		//Chequea si el dron colisiona.
		colision( contorno, 0, contorno.size(), dron );
	}
    return 0;
}
