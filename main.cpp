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

	vectorList temp1 (first,middle);
	vectorList temp2 (middle,end);

	temp1 = obtenerContorno(temp1);
	temp2 = obtenerContorno(temp2);

	vectorList temp3;
	int i = 0, j = 0;

	/*vectorList temp3;
	temp3.reserve( temp1.size() + temp2.size() ); // preallocate memory
	temp3.insert( temp3.end(), temp1.begin(), temp1.end() );
	temp3.insert( temp3.end(), temp2.begin(), temp2.end() );*/

	//temp.push_back( tuple<int, int, int>(1,2,3) );
	return temp3;

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

	imprimirVector(edificios,1);

	contorno = obtenerContorno(edificios);

	imprimirVector(contorno,0);

    return 0;
}
