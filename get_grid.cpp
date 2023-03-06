#include <iostream>
using namespace std;




int main( int argc, char ** argv ) {
	
	int pt1[2] = {0,0};
	int pt2[2] = {0,1};
	int pt3[2] = {1,0};
	int pt4[2] = {1,1};

	for( int j = 0; j < 10; j++ ) {
		int pt1[2] = {0+j,0};
		int pt2[2] = {0+j,1};
		int pt3[2] = {1+j,0};
		int pt4[2] = {1+j,1};
		
		for( int i = 0; i < 10; i++ ) {
			pt1[1] += 1;
			pt2[1] += 1;
			pt3[1] += 1;
			pt4[1] += 1;

			cout << pt1[0] << " | " << pt1[1] << endl;
			cout << pt2[0] << " | " << pt2[1] << endl;
			cout << pt3[0] << " | " << pt3[1] << endl;
			cout << pt4[0] << " | " << pt4[1] << endl;
			cout << "___________" << endl;
		}
	}
	return 0;
}

