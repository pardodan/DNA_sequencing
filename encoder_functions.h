#ifndef DSC_DNA_SEQ_ENCODER_FUNCTIONS_H
#define DSC_DNA_SEQ_ENCODER_FUNCTIONS_H
#include <vector>
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
//#include <cstdlib>

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)
using namespace std;

//typedef vector <int> READ;
//typedef vector <unsigned long> LOCATION;
//typedef unsigned long PREF;




//class PREFIX
//{
//    public:
//        int length = 10;
//        LOCATION* candidate_position;
//        READ pre_fix;
//};


//class BSC
//{
//    public:
//        int length;
////        READ* orig;
//        READ orig;
////        READ* reference;
//        READ reference;
//        int candidate_factor = 8;
//        vector <PREFIX> prefix_array;
//
//        BSC(int length){
//            this->length = length;
//            for(int i=0; i<length;i++)
//            {
////        this->orig.push_back(rand()%2);
//                this->orig.push_back(0);
//            }
//        };
////        ~BSC();
//
//        vector <int> sequence_simulator(READ orig, int length, int probability);
//        void setCopy(int length, READ* read);
//        void setRef(int length, READ* read);
//        void print();
//
//};
//
//vector <int> sequence_simulator(READ orig, int length, int probability);
//vector<vector<int>> split_read(vector<int>read , int k, int n);
//unsigned long ** split_reed_solomon(vector<int>read ,int k , int n);
//


#endif //DSC_DNA_SEQ_ENCODER_FUNCTIONS_H
