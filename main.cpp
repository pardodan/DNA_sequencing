#include "ReedSolomon.h"
#include "BCH.h"
#include "encoder_functions.h"
#include <time.h>
#include <iomanip>
#include <iostream>
#include <algorithm>


////Input to main is a read file
//int main(int argc, char **argv) {
//
//    if (argc < 2) {
//        fprintf(stderr, "Usage: %s <reads filename>\n", argv[0]);
//        exit(1);
//    }
//
//    FILE *reads_file = fopen(argv[1], "r");
//    if (reads_file == 0) {
//        fprintf(stderr, "cannot open read file\n");
//        exit(2);
//    }
//
//
//    char line[1024];
//    while ((fgets(line, 9, reads_file) != nullptr)) {
//        if (line[0] == '\n') {
//            break;
//        }
//        unsigned long read =  atoi(line);
////        for(int i=0;i<8;i++)
////            cout<<read[i]<<endl;
//        cout<<run_reed_solomon(8, 9, 6, 5, true, nullptr, 4,&read)<<endl;
//    }
//
//    return 0;
//}

//#include "ReedSolomon.h"
//#include "BCH.h"
//#include <time.h>
//#include <iomanip>
//#include <iostream>

#include <cstdlib>


#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)
using namespace std;

typedef vector <int> READ;
typedef vector <unsigned long> LOCATION;
//typedef unsigned long PREF;

class PREFIX
{
    public:
        int length = 10;
        READ pre_fix_read;
        LOCATION candidate_position;

    PREFIX(int length, READ pre_fix_read)
    {
        this->length = length;
        this->pre_fix_read = pre_fix_read;
    }
};


class BSC
{
    public:
        int length = 1000;
        double probability = 0.01;
//        READ* orig;
        READ orig;
//        READ* reference;
        READ reference;
        int candidate_factor = 2;
        vector <PREFIX> prefix_array;

        BSC(int length, double probability){
            srand(time(0));
            this->length = length;
            this->probability = probability;
            this->candidate_factor = candidate_factor;
            for(int i=0; i<length;i++)
            {
                this->orig.push_back(rand()%2);
            }
            for (int i : orig) {
                double r = ((double) rand() / (RAND_MAX));
                if (r < this->probability) {
                    if(i==0)
                        this->reference.push_back(1);
                    else
                        this->reference.push_back(0);
                }
                else
                    this->reference.push_back(i);
            }
        };
//        ~BSC();

//        vector <int> sequence_simulator(READ orig, int length, double probability = 0.1)
//        {
//            vector <int> BSC_read;
//
//            for (int i : orig) {
//                double r = ((double) rand() / (RAND_MAX));
////                double r = 0;
//                if (r < probability) {
//                    if(i==0)
//                        BSC_read.push_back(1);
//                    else
//                        BSC_read.push_back(0);
//                }
//                else
//                    BSC_read.push_back(i);
//            }
//            return BSC_read;
//        };

        void print()
        {
            cout << "The orig DNA vector is:" << endl;
            for (int i: this->orig)
                cout << i << ' ';
            cout << endl << "The referenced DNA vector is:" << endl;
            for (int i: this->reference)
                cout << i << ' ';
            cout<<endl;
        };

        void print_loc()
        {
            cout << "The location of the possible candidate in the reference read is:" << endl;
            cout << "The size is:" << this->prefix_array[0].candidate_position.size()<< endl;
            cout << "The size of prefix array is:" << this->prefix_array.size()<< endl;
            for (unsigned long i: this->prefix_array[0].candidate_position)
                cout << i << ' ';
        };
        void set_Location_prefix(PREFIX & pre_fix)
        {
            for(unsigned long i = 0; i < this->reference.size() - pre_fix.pre_fix_read.size(); i++){	//only check for pre_fix where there is enough space for it
                int n;
                int error = 0;
                for(n = 0; n < pre_fix.pre_fix_read.size(); n++){
                    if(this->reference[i + n] != pre_fix.pre_fix_read[n]){		//if one of the elements is incorrect increase error
                        error++;
                    }
                }

                if(error <= this->candidate_factor){
//                    cout<< "location:" << i << endl;	//if error is less than error_rate it means we found a possible candidate at index i
                    pre_fix.candidate_position.push_back(i);

                }
            }
        };

//        void set_Location_prefix_array(vector <PREFIX> & prefix_array){
//
//            for()
//
//        };
        void set_Prefix(PREFIX pre_fix)
        {
            this->prefix_array.push_back(pre_fix);
        };

};

//vector <int> sequence_simulator(READ orig, int length, int probability);
//vector<vector<int>> split_read(vector<int>read , int k, int n);
//unsigned long ** split_reed_solomon(vector<int>read ,int k , int n);


//vector <int> sequence_simulator(vector<int> read, int length, double probability)
//{
//    vector <int> BSC_read;
//
//    for (int i : read) {
////        double r = ((double) rand() / (RAND_MAX));
//        double r = 0;
//        if (r < probability) {
//            if(i==0)
//                BSC_read.push_back(1);
//            else
//                BSC_read.push_back(0);
//        }
//        else
//            BSC_read.push_back(i);
//    }
//    return BSC_read;
//}




vector<vector<int>> split_read(vector<int>read ,int k , int n)
{
    vector<vector<int>> vec;
    int num_of_words = k/n + 1;

    // Inserting elements into vector
    for (int i = 0; i < num_of_words ; i++) {

        // Vector to store "column" elements
        vector<int> v1;

        for (int j = 0; j < n; j++) {
            if((n*i + j)<k) {
                v1.push_back(read[(n * i) + j]);
            }
                //padding with zeroes the last vector
            else{
                v1.push_back(0);
            }

        }

        // Pushing back above 1D vector
        // to create the 2D vector
        vec.push_back(v1);
    }
    cout << "The 2-D vector is:" <<endl;

    // Displaying the 2D vector
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++)
            cout << vec[i][j] << " ";
        cout << endl;
    }
    return vec;
}

//returns an array of pointers , every "element" in the array is an unsigned long pointer (RS_WORD)
unsigned long** split_reed_solomon(vector<int>read ,int k , int n)
{

    int num_of_words = k/n + 1;
    unsigned long** a = new unsigned long*[num_of_words];
    for(int i = 0; i < num_of_words; ++i) {
        a[i] = new unsigned long[n];
        for (int j = 0; j < n; j++) {
            if((n*i + j)<k) {

                a[i][j] = read[(n * i) + j];
            }
                //padding with zeroes the last vector
            else{
                a[i][j] = 0;

            }

        }

    }
    cout << "The 2-D array is:" <<endl;

    // Displaying the 2D array
    for (int i = 0; i < num_of_words; i++) {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    return a;
}



int main(int argc, char **argv) {

    srand(time(0));
    cout<<"MAIN FUNC"<<endl;

    BSC DNA_seq = BSC(10000,0.01);
    DNA_seq.print();

    READ pre_fix_1;
    READ pre_fix_0;
    //test for algo
    pre_fix_1.assign (10,1);
    pre_fix_0.assign (10,0);

//    cout << "The test pre_fix vector is:" << endl;
//    for (int i: pre_fix)
//        cout << i << ' ';
//    cout << endl;


//    for(int i = 0; i < DNA_seq.reference.size() - pre_fix.size(); i++){	//only check for pre_fix where there is enough space for it
//        int n;
//        int error = 0;
//        for(n = 0; n < pre_fix.size(); n++){
//            if(DNA_seq.reference[i + n] != pre_fix[n]){		//if one of the elements is incorrect increase error
//                error++;
//            }
//        }
//        if(error <= 1)
//            cout<< "location:" << i << endl;	//if error is less than error_rate it means we found a possible candidate at index i
//    }

    PREFIX test_0_pre_fix = PREFIX(10,pre_fix_0);
    PREFIX test_1_pre_fix = PREFIX(10,pre_fix_1);

    DNA_seq.set_Prefix(test_0_pre_fix);
    DNA_seq.set_Location_prefix(DNA_seq.prefix_array[0]);

    DNA_seq.set_Prefix(test_1_pre_fix);
    DNA_seq.set_Location_prefix(DNA_seq.prefix_array[1]);

    cout << "The location of test_pre_fix_0 the possible candidate in the reference read is:" << endl;
    for (unsigned long i : DNA_seq.prefix_array[0].candidate_position)
        cout << i << ' ';
    cout << endl;

    cout << "The location of test_pre_fix_1 the possible candidate in the reference read is:" << endl;
    for (unsigned long i : DNA_seq.prefix_array[1].candidate_position)
        cout << i << ' ';
    cout << endl;

      return 0;
}


//Input to main is a read file
//int main(int argc, char **argv) {
//    char line[63];
//
//    if (argc < 2) {
//        fprintf(stderr, "Usage: %s <reads filename>\n", argv[0]);
//        exit(1);
//    }
//
//    FILE *reads_file = fopen(argv[1], "r");
//    if (reads_file == 0) {
//        fprintf(stderr, "cannot open read file\n");
//        exit(2);
//    }
//
//    vector<vector<int>>  reads;
//    while ((fgets(line, 64, reads_file) != nullptr)) {
//        vector<int> v_temp;
//        /*if (line[0] == '\n') {
//            cout<<"done"<<endl;
//            break;
//        }*/
//        for(char c : line) {
//            // NOTE: cast to (int) doesn't change value of 'c'.
//            v_temp.push_back(( c)-48);
//        }
//        reverse(v_temp.begin(),v_temp.end());
//        reads.push_back(v_temp);
//    }
//    print_vector(*reads.begin());
//    cout<<reads.begin()->size()<<endl;
//    // vector <int> read_vec = {1,0,0,1,0,1,0,0,1,1,1,0,0,0,0,0,1,0,0,1,
//    //  1,0,0,0,0,1,1,1,0,0,0,1,0,1,1,0,
//    // 1,0,0,1,1,1,1,0,1,0,1,1,1,0
//    // ,1,1,0,1,1,1,0,1,0,1,0,0,1 };*/
////    binary_syndrom_calc(*reads.begin());
//
//    int k =30;
//    int n=8;
//    vector<vector<int>> res_vector = split_read(*reads.begin(),k,n);
//
//    unsigned long** res_array = split_reed_solomon(*reads.begin(),k,n);
//
//    return 0;
//}