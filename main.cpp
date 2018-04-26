#include <iostream>
#include <map>
using namespace std;
double arithCompress(char[], int, double[], string);
string arithDecompress(char[], int, double[], double, int);

int main(){

    char arr[] = {'a','b','c'};
    double prob[] = {0.8,0.02,.18};
    double comProb[] = {0, 0.8, 0.82, 1};
    double n = arithCompress(arr, 3, prob, "acaba");
    cout << n << endl;
    cout << arithDecompress(arr, 3, comProb, n, 5);
    return 0;
}
double arithCompress(char charSet[], int charSetLength, double probability[], string str){
    map<char, int> index;
    for(int i = 0; i < charSetLength; ++i){
        index[charSet[i]] = i + 1;
    }
    double comProb[charSetLength + 1];
    comProb[0] = 0;
    copy(probability, probability + charSetLength, comProb + 1);
    for(int i = 1; i <= charSetLength; ++i){
        comProb[i] += comProb[i - 1];
    }
    double lNew = 0, l = 0, uNew = 1, u = 1;
    for(int i = 0; i < (int) str.length(); ++i){
        lNew = l + (u - l) * comProb[index[str[i]] - 1];
        uNew = l + (u - l) * comProb[index[str[i]]];
        l = lNew;
        u = uNew;
    }
    return (l + u) / 2;
}
string arithDecompress(char charSet[], int charSetLength, double comProb[], double tag, int compLenght){
    map<int, char> index;
    for(int i = 0; i < charSetLength; ++i){
        index[i + 1] = charSet[i];
    }
    double lNew = 0, l = 0, uNew = 1, u = 1;
    string decoding = "";
    for(int k = 0; k < compLenght; ++k){
        for(int i = 1; i <= charSetLength; ++i){
            lNew = l + (u - l) * comProb[i - 1];
            uNew = l + (u - l) * comProb[i];
            if(tag >= lNew && tag <= uNew){
                decoding += index[i];
                l = lNew;
                u = uNew;
                break;
            }
        }
    }
    return decoding;
}
