#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>
using namespace std;

typedef vector< tuple<int, int, int> > vectorList;

int main()
{
	vectorList edificios;
	int n, L, H, R;

	cout << "Ingrese número de edificios:" << endl;
	cin >> n;
	cout << n << endl;

	for(int i = 0; i<n; i++){
		cin >> L >> H >> R;
		cout << "ingresaste: " << L << H << R << endl;
		edificios.push_back( tuple<int, int, int>(L,H,R) );
	}

    /*for (size_t i = 0; i != edificios.size(); ++i) {
		cout << get<0>(edificios.at(i));
	    cout << get<1>(edificios.at(i));
	    cout << get<2>(edificios.at(i)) << endl;
    }*/

    return 0;
}
