#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;


const size_t len = 8;
typedef union {
    uint8_t ik;
    char chk[len];
}key;

int combkey(int num, int param) {
    key n;
    n.ik = num;
    size_t index = 0;
    if (num % 2)
        index = 1;
    for (index; index < sizeof(int); index += 2)
        n.chk[index] *= param;
    return n.ik;
}

class Distribution {
public:
    int numbilets, parameter, size;
    vector<string> names;
    vector<int> number;
    Distribution();
    Distribution(int n, int p);
    void fillNames(string str);
    void printDistr();
    void hashing();
};

Distribution::Distribution() {
    this->numbilets = 0;
    this->parameter = 0;
    this->size = 0;
}
Distribution::Distribution(int n, int p) {
    this->numbilets = n;
    this->parameter = p;
    this->size = 0;
}

void Distribution::fillNames(string str) {
    this->names.push_back(str);
    this->size++;
}

void Distribution::printDistr() {
    for (int i = 0; i < size; i++) {
        cout << names[i] << ": " << number[i] << endl;
    }
    cout << numbilets << " " << parameter << " " << size << '\n';
}

void Distribution::hashing()
{
    hash<string> hasher;
    for (int i = 0; i < size; i++) {
        number.push_back(combkey(hasher(names[i]), parameter) % numbilets);
    }
}



int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");
    if (string(argv[1]) == "--file" && string(argv[3]) == "--numbilets" && 
    string(argv[5]) == "--parameter") {
        Distribution distr(atoi(argv[4]), atoi(argv[6]));
        ifstream in(argv[2]); // окрываем файл для чтения
        if (in.is_open())
        {
            string str_1;
            while (getline(in, str_1))
            {
                distr.fillNames(str_1);
            }
        }
        in.close();     // закрываем файл  
        distr.hashing();
        distr.printDistr();
    }
    else return 1;
    return 0;
}