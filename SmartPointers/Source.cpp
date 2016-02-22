#include"Tests.h"

#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    test_create() ? cout <<"Create Succuss!"<<endl:cout <<"Create Failure!"<<endl ;
    test_crt() ? cout << "crt Test Passed!" <<endl : cout << "crt Test Failed!" << endl;

	time_t ini = time(NULL);
	ini *= 1000;
	
    test_Iterative_algo() ? cout << "Iterative Multiplication Success!" << endl : cout << "Iterative Multiplication Failure!" << endl;

	time_t finalT = time(NULL);
    finalT *= 1000;
    
	cout<<"Time Taken is "<<finalT-ini<<" sec"<<endl;
		
	ini = time(NULL);
    test_StrassenAlgo() ? cout << "StrassenAlgo Multiplication Test Passed!" << endl :cout << " StrassenAlgo Multiplication Test Failed!" << endl;

	finalT = time(NULL);
	cout<<"Time Taken "<<finalT-ini<<" sec"<<endl;
    
    return 0;
}

