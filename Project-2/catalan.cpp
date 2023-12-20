
#include <iostream> 
using namespace std;

/**
 * C0 = 1; // Base provided 
 * n = 0: C(n+1) = C1 = C0*C0 = 1; // Base since it yield to provided base 
 * n = 1: C(1+1) = C0*C1 + C1*C0 => C2 = 2(C0*C1) = 2;
 * n = 2: C(2+1) = C0*C2 + C1*C1 + C2*C0 => 
 *          C(3) = 2(C0 * 2(C0*C1)) + C1*C1 = 5;
 * Since formula the provided formula finding next nth number I 
 * need to find (n-1)th to find nth element:
 * n = (n-1): C(n-1 +1)  = C0*C(n-1- 0) + C1*C(n-1 -1) + C2*C(n-1 -2) + ... 
 *                         C(n -2)*C(n-1 - (n -2)) + C(n -1)*C(n-1 - (n -1))
 * Thus: 
 * C(n) will be equal recursive sum of Ci*C(n-1 - i) where i start from 0 to 
 * n -1. 
*/
long catalan(int n){
    if(n < 0){ // Ensures number is greater then 0 
        cout << "Provided parameter should be posive:" << endl;
        cout << "Please enter whole number greater than zero." << endl;
        return -1;
    }
    if (n == 0 || n == 1){
        return 1; // Base case
    }
    long sum = 0; 
    n = n -1;
    int i = 0;
    while(i <= n){
        sum += catalan(i)*catalan(n - i);
        i++;
    }
    return sum;
}
/**
 * Ensures correct number of command line parameters passed before 
 * proceeding to calculate nth catalan number. 
*/
int main(int argc, const char * argv[]) {
    if (argc > 2){
         cout << "Please enter valid input:There should be 2 arguments" << endl;
    }else if(argc < 2){
        cout << "Please enter valid input:There should be 2 arguments" << endl;  
    }else{
        int cat_number  = stoi(argv[1]);
        long nth_catalan = catalan(cat_number);
        if(nth_catalan > 0){
            cout << nth_catalan << endl;
        }
    }
    return 0;
}


