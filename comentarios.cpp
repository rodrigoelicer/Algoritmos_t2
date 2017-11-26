#include <iostream>
//#include <sstream>
#include <tuple>
#include <vector>
using namespace std;

typedef vector< tuple<int, int, int> > vectorList;
typedef tuple<int, int> dronCoord;

void imprimirVector(vectorList v, int mark){
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

vectorList obtenerContorno(vectorList edificios){
	if(edificios.size() <= 1){
		vectorList temp;
		auto v = edificios.at(0);
		temp.push_back( tuple<int, int, int>( get<0>(v),get<1>(v),-1 ) );
		temp.push_back( tuple<int, int, int>( get<2>(v),0,-1 ) );
		return temp;
	}
	size_t n = edificios.size();
	vectorList::const_iterator first = edificios.begin();
	vectorList::const_iterator middle = edificios.begin() + n/2;
	vectorList::const_iterator end = edificios.end();

	vectorList c1 (first,middle);
	vectorList c2 (middle,end);

	c1 = obtenerContorno(c1);
	c2 = obtenerContorno(c2);

	cout << "Contorno1: ";
	imprimirVector(c1,0);
	cout << "Contorno2: ";
	imprimirVector(c2,0);

	size_t i = 0, j = 0;

	vectorList c3;
	size_t n1 = c1.size();
	size_t n2 = c2.size();
	while(i<n1 || j<n2){
		//Se acaba el contorno 1
		if(i == n1){
			cout << "A" << endl;
			c3.push_back(c2.at(j));
			j++;
		}
		//Se acaba el contorno 2
		else if(j == n2){
			cout << "B" << endl;
			c3.push_back(c1.at(i));
			i++;
		}
		//Verifica si la tupla en c1 es menor a la tupla en c2
		else if( get<0>(c1.at(i)) < get<0>(c2.at(j)) ){
			cout << "CDE" << endl;
			//Si no ha habido un elemento de c2 menor a c1
			if(j == 0){
				cout << "C" << endl;
				c3.push_back(c1.at(i));
			}
			//Si la altura en c1 es mayor a la altura previa de c2 (c2[j-1])
			else if( get<1>(c1.at(i)) > get<1>(c2.at(j-1)) ){
				cout << "D" << endl;
				c3.push_back(c1.at(i));
			}
			//Si la altura de c1[i] es menor a la altura previa de c2[j] (c2[j-1]),
			//PERO al mismo tiempo la altura previa de c1 (c1[i-1]) es mayor
			//a la altura previa de c2 (c2[j-1])
			else if(i!=0 && get<1>(c1.at(i)) < get<1>(c2.at(j-1))
						&& get<1>(c1.at(i-1)) > get<1>(c2.at(j-1)) ){
				cout << "E" << endl;
				c3.push_back(
					tuple<int, int, int>(get<0>(c1.at(i)),get<1>(c2.at(j-1)),-1)
				);
			}
			i++;
		}
		//Verifica si la tupla en c2 es menor a la tupla en c1
		else if( get<0>(c1.at(i)) > get<0>(c2.at(j)) ){
			cout << "FGH" << endl;
			//Si no ha habido un elemento de c1 menor a c2
			if(i == 0){
				cout << "F" << endl;
				c3.push_back(c2.at(j));
			}
			//Si la altura en c2 es mayor a la altura previa de c1 (c1[i-1])
			else if( get<1>(c2.at(j)) > get<1>(c1.at(i-1)) ){
				cout << "G" << endl;
				c3.push_back(c2.at(j));
			}
			//Si la altura de c2[j] es menor a la altura previa de c1[i] (c1[i-1]),
			//PERO al mismo tiempo la altura previa de c2 (c2[j-1]) es mayor
			//a la altura previa de c1 (c1[i-1])
			else if( j!=0 && get<1>(c2.at(j)) < get<1>(c1.at(i-1))
						&& get<1>(c2.at(j-1)) > get<1>(c1.at(i-1)) ){
				cout << "H" << endl;
				c3.push_back(
					tuple<int, int, int>(get<0>(c2.at(j)),get<1>(c1.at(i-1)),-1)
				);
			}
			j++;
		}
		//mismas coordenadas x
		else{
			cout << "IJKLMN" << endl;
			//Ambos contornos inician donde mismo
			if(j == 0 && i == 0){
				cout << "IJ" << endl;
				if( get<1>(c1.at(i)) > get<1>(c2.at(j)) ){
					cout << "I" << endl;
					c3.push_back(c1.at(i));
				}
				else{
					c3.push_back(c2.at(j));
				}
			}
			//Contorno 2 está en el inicio
			else if(j == 0){
				cout << "K1" << endl;
				//Si c1 tiene altura mayor, se agrega c1
				if( get<1>(c2.at(j)) < get<1>(c1.at(i)) ){
					cout << "K1.1" << endl;
					c3.push_back(c1.at(i));
				}
				//Si no tienen la misma altura, se agrega la tupla
				else if( get<1>(c2.at(j)) != get<1>(c1.at(i-1)) ){
					cout << "K1.2" << endl;
					c3.push_back(c2.at(j));
				}
			}
			//Contorno 1 está en el inicio
			else if(i == 0){
				cout << "L1" << endl;
				//Si c2 tiene altura mayor, se agrega c2
				if( get<1>(c1.at(i)) < get<1>(c2.at(j)) ){
					cout << "L1.1" << endl;
					c3.push_back(c2.at(j));
				}
				//Si no tienen la misma altura, se agrega la tupla
				else if( get<1>(c1.at(i)) != get<1>(c2.at(j-1)) ){
					cout << "L1.2" << endl;
					c3.push_back(c1.at(i));
				}
			}
			else if( get<1>(c2.at(j)) < get<1>(c1.at(i))
						&& get<1>(c1.at(i)) != get<1>(c2.at(j-1)) ){
				cout << "M" << endl;
				c3.push_back(c1.at(i));
			}
			else if( get<1>(c1.at(i)) < get<1>(c2.at(j))
						&& get<1>(c2.at(j)) != get<1>(c1.at(i-1)) ){
				cout << "N" << endl;
				c3.push_back(c2.at(j));
			}

			j++;
			i++;
		}
	}
	imprimirVector(c3,0);
	return c3;

}

void colision(vectorList contorno, dronCoord dron){
	//Caso donde el dron va por el suelo, sólo por si las moscas
	if( get<1>(dron) == 0 ){
		cout << "true" << endl;
		return;
	}
	//Está fuera de los límites, por lo tanto no choca
	if(contorno.size() == 0){
		cout << "false" << endl;
		return;
	}
	else{
		size_t medio = contorno.size()/2;
		cout << "Mitad contorno X: " << get<0>(contorno.at(medio)) << endl;
		cout << "Dron X: " << get<0>(dron) << endl;
		//Cae justo en una coordenada del contorno
		if( get<0>(contorno.at(medio)) == get<0>(dron) ){
			cout << "12" << endl;
			//Si la altura es mayor
			if( get<1>(contorno.at(medio)) >= get<1>(dron) ){
				cout << "1" << endl;
				cout << "true" << endl;
				return;
			}
			//Si la altura es menor, no necesariamente significa que no vaya
			//a chocar. Puede darse el caso donde se termina un edificio. Habrá
			//que verificar que la altura de la coord anterior también sea mayor.
			else{
				cout << "2" << endl;
				if( get<1>(contorno.at(medio-1)) >= get<1>(dron) ){
					cout << "2.1" << endl;
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
			cout << "34" << endl;
			//contorno es más alto, por lo que choca
			if( get<1>(contorno.at(medio-1)) >= get<1>(dron) ){
				cout << "3" << endl;
				cout << "true" << endl;
				return;
			}
			//no choca
			else{
				cout << "4" << endl;
				cout << "false" << endl;
				return;
			}
		}
		//recursividad, sigue buscando
		else{
			size_t n = contorno.size();
			vectorList::const_iterator first = contorno.begin();
			vectorList::const_iterator middle = contorno.begin() + n/2;
			vectorList::const_iterator end = contorno.end();

			if( get<0>(dron) < get<0>(contorno.at(medio)) ){
				vectorList c1 (first,middle);
				cout << "5" << endl;
				imprimirVector(c1, 0);
				colision(c1,dron);
			}
			else{
				vectorList c2 (middle+1,end);
				cout << "6" << endl;
				imprimirVector(c2, 0);
				colision(c2,dron);
			}
		}
	}
}

int main()
{
	vectorList edificios, contorno;
	int n, L, H, R;
	int X, Y;

	cout << "Ingrese número de edificios:" << endl;
	cin >> n;
	cout << n << endl;

	for(int i = 0; i<n; i++){
		cin >> L >> H >> R;
		cout << "ingresaste: " << L << H << R << endl;
		edificios.push_back( tuple<int, int, int>(L,H,R) );
	}

	cout << "Edificios: ";
	imprimirVector(edificios,1);

	contorno = obtenerContorno(edificios);

	cout << "Contorno final: ";
	imprimirVector(contorno,0);

	cout << "Ingrese número de drones:" << endl;
	cin >> n;
	cout << n << endl;

	for(int i = 0; i<n; i++){
		cin >> X >> Y;
		cout << "ingresaste: " << X << Y << endl;
		colision( contorno, tuple<int, int>(X,Y) );
	}

    return 0;
}
