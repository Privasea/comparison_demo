// Includes
#include "cryptocontext.h"
#include "lwecore.h"
#include "math/backend.h"
#include "ringcore.h"
#include <algorithm>
#include <bits/types/time_t.h>
#include <stdio.h>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <memory>
#include <ostream>
#include <string>
#include <sys/time.h>
// Multi-processing
#include <sys/wait.h>
#include <unistd.h>
#include <ctime>

//! binfhecontext
#define PROFILE
#include <vector>
// #include "binfhecontext.h"
#include "hesea.h"
using namespace lbcrypto;
using namespace std;



using namespace std;

bool comparexby(LWECiphertext x, LWECiphertext y, CryptoContextImpl<DCRTPoly>& cc, int p, LWEPrivateKey sk);
vector<LWECiphertext> sort(vector<LWECiphertext>& series, bool ascending, CryptoContextImpl<DCRTPoly>& cc, int p, LWEPrivateKey sk);

int main(){
    vector<int> original_data;
    int number;
    bool is_ascending = true;


    //! binfhecontext strat
    auto cc = CryptoContextImpl<DCRTPoly>();

    int p = 512;
    int N = 1024;
    int n = 128;
    int q_bits = 30;
    int qKS_bits = 30;
    int Q_bits = 55;
    int baseG_Q = 1<<15; 
    int baseKS = 1<<3; 
    int baseR = 2;
    NativeInteger Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(Q_bits, 2*N), 2*N);
    cc.HESea_GenerateBinFHEContext(n, N, NativeInteger(1<<q_bits), Q, NativeInteger(1ull<<qKS_bits), 0, baseKS, baseG_Q, baseR, lbcrypto::GINX);
    int q = cc.HESea_GetParams()->GetLWEParams()->Getq().ConvertToInt();
    // Sample Program: Step 2: Key Generation
    // Generate the secret key
    auto sk = cc.HESea_KeyGen02();

    std::cout << "Generating the bootstrapping keys..." << std::endl;

    // Generate the bootstrapping keys (refresh and switching keys)
    cc.HESea_BTKeyGen(sk);

    std::cout << "Completed the key generation." << std::endl;


    //! input number series
    cout<<"input the number series between [0,128) (enter q to exit) :"<<endl;
    while (cin>>number) {
        original_data.push_back(number);
        cout<<"(enter q to exit):"<<endl;
    }
    cout<<"your input "<< original_data.size() << " numbers totaly, they are "<< original_data<<endl;




    //! encrypt the number series
    vector<LWECiphertext> enc_data;
    cout << "encrypt numbers needed to be sorted" << endl;
    for(int i = 0; i < original_data.size(); i++){
        enc_data.push_back( cc.HESea_Encrypt(sk, original_data[i], p));
    }


    //! sort the series
    cout << "sort the ciphertext sequence " << endl;
    vector<LWECiphertext> sorted_enc_data = sort(enc_data, is_ascending, cc, p, sk);


    //! decrypt the series
    vector<int> sorted_original_data;
    for(int i = 0; i < sorted_enc_data.size(); i++){
        LWEPlaintext temp;
        cc.HESea_Decrypt(sk, sorted_enc_data[i], &temp, p);
        int temp_int = temp>= p/2 ? temp - p : temp;
        sorted_original_data.push_back(temp_int);
    }

    cout << "data after sorted are :"<< sorted_original_data <<endl;
    return 0;

}


//! compare x>y? if true return true else false
bool comparexby(LWECiphertext x, LWECiphertext y, CryptoContextImpl<DCRTPoly>& cc, int p, LWEPrivateKey sk){
    NativeInteger q = x->GetA().GetModulus();
    LWECiphertext temp = make_shared<LWECiphertextImpl>(*x);
    temp->SetA(y->GetA().ModMul(2).ModSub(x->GetA().ModMul(2)));
    temp->SetB(y->GetB().ModMul(2, q).ModSub(x->GetB().ModMul(2, q), q));

    // temp->SetA(y->GetA().ModSub(x->GetA()));
    // temp->SetB(y->GetB().ModSub(x->GetB(), q));

    auto ct_sign = cc.HESea_MyEvalSigndFunc(temp, p);

    LWEPlaintext sign;

    cc.HESea_Decrypt(sk, ct_sign, &sign, p);
    sign = sign >= p/2 ? 1 : 0;

    return bool(sign);
}



//! sort the series using Bubbling sorting
vector<LWECiphertext> sort(vector<LWECiphertext>& series, bool ascending, CryptoContextImpl<DCRTPoly>& cc, int p, LWEPrivateKey sk){
    int n = series.size();
    int * index = new int[n];
    for(int i = 0; i < n; i++){
        index[i] = i;
    }
    series[0];

    for(int i = 1; i < n; i++){
        bool flag = false;
        for(int j = 0; j < n - i; j++){
            if(comparexby(series[index[j]], series[index[j+1]], cc, p, sk)){
                int temp = index[j];
                index[j] = index[j+1];
                index[j+1] = temp;
                flag = true;
            }
        }
        if(!flag){
            break;
        }
    }

    vector<LWECiphertext> res;
    if(ascending){

    }
    else {
        for(int i = 0; i < n/2; i++){
            int temp = index[i];
            index[i] = index[n-1-i];
            index[n-1-i] = temp;
        }
    }

    for(int i = 0; i < n; i++){
        res.push_back(series[index[i]]);
    }

    return res;

}


