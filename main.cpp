#include <iostream>
//#include <sstream>
#include <tuple>
#include <vector>
using namespace std;

typedef vector< tuple<int, int, int> > vectorList;

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
				//Si no hay continuidad (misma altura), se agrega la tupla
				if( get<1>(c2.at(j)) != get<1>(c1.at(i-1)) ){
					cout << "K2" << endl;
					c3.push_back(c2.at(j));
				}
			}
			//Contorno 1 está en el inicio
			else if(i == 0){
				cout << "L1" << endl;
				//Si no hay continuidad (misma altura), se agrega la tupla
				if( get<1>(c1.at(i)) != get<1>(c2.at(j-1)) ){
					cout << "L2" << endl;
					c3.push_back(c1.at(i));
				}
			}
			//Si no hay continuidad (misma altura), se agrega la tupla
			else if( get<1>(c2.at(j)) != get<1>(c1.at(i-1)) ){
				cout << "M" << endl;
				c3.push_back(c2.at(j));
			}
			//Si no hay continuidad (misma altura), se agrega la tupla
			else if( get<1>(c1.at(i)) != get<1>(c2.at(j-1)) ){
				cout << "N" << endl;
				c3.push_back(c1.at(i));
			}

			j++;
			i++;
		}
	}
	imprimirVector(c3,0);
	return c3;

}

int main()
{
	vectorList edificios, contorno;
	int n, L, H, R;

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

    return 0;
}
