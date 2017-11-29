#include <iostream>
//#include <sstream>
#include <tuple>
#include <vector>
using namespace std;

typedef vector< tuple<unsigned int, unsigned int, unsigned int> > vectorList;
typedef tuple<unsigned int, unsigned int> dronCoord;
typedef tuple<unsigned int, unsigned int, unsigned int> nodo;

void imprimirVector(vectorList &v, int mark){
	cout << "[";
    for (size_t i = 0; i != v.size(); i++) {
		cout << "(";
		cout << get<0>(v.at(i));
		cout << ",";
	    cout << get<1>(v.at(i));
		if(mark == 1){
			cout << ",";
		    cout << get<2>(v.at(i));
		}
		cout << ")";
		if(i < v.size()-1) cout << ", ";
    }
	cout << "]" << endl;
}

void compararMenorConMayor( unsigned int x1, unsigned int h1temp,
							unsigned int h1, unsigned int h2, vectorList &c3 ){
	if( h1temp > h2 || (h1temp == h2 && h1 > h2) ){
		nodo nd = tuple<unsigned int, unsigned int, unsigned int>(x1,h1temp,0);
		c3.push_back( nd );
	}
	else if( h1temp < h2 && h1 > h2 ){
		nodo nd = tuple<unsigned int, unsigned int, unsigned int>(x1,h2,0);
		c3.push_back( nd );
	}
}

vectorList merge(vectorList &c1, vectorList &c2){
	vectorList c3;

	size_t n1 = c1.size(), n2 = c2.size();
	unsigned int h1 = 0, h2 = 0;
	size_t  i = 0, j = 0;

	while( i < n1 && j < n2 ){
		if( get<0>(c1.at(i)) < get<0>(c2.at(j)) ){
			//cout << "1" << endl;
			unsigned int x1 = get<0>(c1.at(i));
			unsigned int h1temp = get<1>(c1.at(i));

			compararMenorConMayor(x1, h1temp, h1, h2, c3);

			h1 = h1temp;
			i++;
		}
		else{
			//cout << "2" << endl;
			unsigned int x2 = get<0>(c2.at(j));
			unsigned int h2temp = get<1>(c2.at(j));

			compararMenorConMayor(x2, h2temp, h2, h1, c3);

			h2 = h2temp;
			j++;
		}
	}
	while(i < n1){
		//cout << "3" << endl;
		c3.push_back(c1.at(i));
		i++;
	}
	while(j < n2){
		//cout << "4" << endl;
		c3.push_back(c2.at(j));
		j++;
	}
	//imprimirVector(c3,0);
	return c3;
}

vectorList obtenerContorno(vectorList &arr, size_t start, size_t end){
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

	/*cout << "Contorno1: ";
	imprimirVector(c1,0);
	cout << "Contorno2: ";
	imprimirVector(c2,0);*/

	vectorList c3 = merge(c1,c2);

	return c3;
}

void colision(vectorList &contorno, unsigned int start, unsigned int end, dronCoord &dron){
	if( get<1>(dron) == 0 ){
		cout << "true" << endl;
		return;
	}
	else{
		//si sobrepasa al último elemento
		if(start == end){
			cout << "false" << endl;
			return;
		}
		int medio = (end+start)/2;
		//Se llega al primer elemento
		if(start == 0 && end == 1){
			if( get<0>(dron) < get<0>(contorno.at(medio)) ){
				cout << "false" << endl;
				return;
			}
			else{
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
			//Si la altura es menor, no necesariamente significa que no vaya
			//a chocar. Puede darse el caso donde se termina un edificio. Habrá
			//que verificar que la altura de la coord anterior también sea mayor.
			else{
				if( get<1>(contorno.at(medio-1)) >= get<1>(dron) ){
					cout << "true" << endl;
					return;
				}
				//El dron está más alto que la coordenada y la coord anterior.
				else{
					cout << "false" << endl;
					return;
				}
			}
		}
		//Verifica cuando el dron está entre medio de 2 coordenadas
		else if( get<0>(contorno.at(medio)) > get<0>(dron)
					&& get<0>(contorno.at(medio-1)) <= get<0>(dron) ){
			//contorno es más alto, por lo que choca
			if( get<1>(contorno.at(medio-1)) >= get<1>(dron) ){
				cout << "true" << endl;
				return;
			}
			//no choca
			else{
				cout << "false" << endl;
				return;
			}
		}
		//recursividad, sigue buscando
		else{
			//entra c1
			if( get<0>(dron) < get<0>(contorno.at(medio)) ){
				colision(contorno, start, medio, dron);
			}
			//entra c2
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

	cin >> n;
	//cout << n << endl;

	for(int i = 0; i<n; i++){
		cin >> L >> H >> R;
		//cout << "ingresaste: " << L << H << R << endl;
		edificios.push_back( tuple<unsigned int, unsigned int, unsigned int>(L,H,R) );
	}

	//cout << "Edificios: " << endl;
	//imprimirVector(edificios,1);

	contorno = obtenerContorno(edificios, 0, n-1);

	cout << contorno.size() << endl;

	for(size_t i = 0; i<contorno.size(); i++){
			cout << get<0>(contorno.at(i)) << " " << get<1>(contorno.at(i)) << endl;
	}

	//cout << "Contorno final: ";
	//imprimirVector(contorno,0);

	//cout << "Ingrese número de drones:" << endl;
	cin >> n;
	cout << n << endl;

	for(int i = 0; i<n; i++){
		cin >> X >> Y;
		//cout << "ingresaste: " << X << Y << endl;
		dronCoord dron ( tuple<unsigned int, unsigned int>(X,Y) );
		colision( contorno, 0, contorno.size(), dron );
	}

    return 0;
}
