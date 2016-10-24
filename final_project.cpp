/******************************************
310 Project 1
Vitalii Stadnyk
File: final_project.cpp

Description: This program generates an array
and applied different sorting algorithms. 

*******************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <limits>
#include <new>

using namespace std;

//FUNCTION DECLARATIONS
void generate_rand(int array_size); //generates txt file with a list of int/floats
void merge_sort(float array_merge[], int p, int r); //sorts the array with merge-sort algorithm
void merge (float array_merge[], int p, int q, int r); //function that is used by merge-sort
void quicksort(float array[], int p, int r);//sorts the array with quicksort algorithm
int partition(float array[], int p, int r);//function that is used by quicksort
void insertion_sort(int array_size, float array_ins[]); //sorts the array with insertion-sort algorithm
void bubble_sort(int array_size, float array_bub[]); //sorts the array with bubble-sort algorithm
void print_array(int array_size, float array[]); //prints out the array


int main()
{
  cout << endl << "***********************************************************" << endl; //Welcome message
  cout << "*           Welcome to our Project 1 for CS 310           *" << endl;
  cout << "***********************************************************" << endl << endl;

  int array_size; //size of the array
  cout << "This program generates arrays and uses four sorting algorithms to sort them and record the time taken." << endl;
  cout << "It starts with a small array and increases the size progressively by the multiple of 10 each round." << endl;
  cout << "The algorithms that have been implemented here are merge sort, quick sort, insertion sort, bubble sort." << endl;
  cout << endl << "Please enter the desired length of the first small array: ";
  cin >> array_size;

  cout << endl <<"Sorting Algorithm"<<"\t\t"<<"Number of Elements"<<"\t\t"<<"Time Taken (seconds)"<<endl;
  cout << "____________________________________________________________________________________________" << endl;

  for(int v = array_size; v <= 1000000; v = v*10) { //for loop to increase the array size
      generate_rand(v); //funtion to generate a list of random floats and save it to list.txt
      
      //start of code to take list.txt and turn it into an array
      float* array = new float[v]; //declaring a pointer for the dynamic array
      ifstream myfile("list.txt");
   
      if(myfile.is_open()){
	  for(int i = 0; i < v; i++){
	      myfile >> array[i];}}
      myfile.close();
  
      /*-------------MERGE SORT----------------*/

      cout << "MERGE SORT" << "\t\t\t";
      float* array_merge = new float[v+1]; //array copy of the original for mergesort
      for (int i = 0; i < v; i++) 
          array_merge[i+1] = array[i];
      
      int start_index = 1;
      int end_index = v;
      clock_t begin = clock(); //start timer
      merge_sort(array_merge, start_index, end_index);
      clock_t end = clock(); //end timer
      
      double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
      cout << v<< "\t\t\t\t";
      cout << elapsed_secs << endl;
      
      for(int i = 1 ; i <= v ; i++)
      {
          array_merge[i-1]=array_merge[i];
      }
      ofstream out;
      out.open("list_merge.txt");
      for(int i=0;i<v;i++)
      {
          out <<array_merge[i]<<" ";
      }
      out.close();
      
      /*--------------QUICK SORT------------------*/

      cout << endl <<"QUICK SORT" << "\t\t\t";
      float* array_quick = new float[v]; //array copy of the original for quicksort
      for (int i = 0; i < v; i++)
          array_quick[i] = array[i];

      int start_index_one = 0;
      int end_index_one = v-1;
      begin = clock();
      quicksort(array_quick, start_index_one, end_index_one);
      end = clock();
      elapsed_secs = double(end-begin)/CLOCKS_PER_SEC;
      cout <<v<<"\t\t\t\t";
      cout <<elapsed_secs<<endl;
      ofstream outa;
      outa.open("list_quick.txt");
      for(int i=0;i<v;i++)
      {
          outa <<array_quick[i]<<" ";
      }

      outa.close();      

      
      /*----------------INSERTION SORT------------------*/

      cout << endl << "INSERTION SORT" << "\t\t\t"; 
      float* array_ins = new float[v]; //array copy of the original for insertion sort
      for (int i = 0; i < v; i++) 
          array_ins[i] = array[i];
      
      begin = clock();
      insertion_sort(v, array_ins);
      end = clock();
      elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
      cout << v << "\t\t\t\t";
      cout << elapsed_secs << endl;
      
      ofstream outb;
      outb.open("list_insertion.txt");
      for(int i=0; i < v ; i++)
      {
          outb <<array_ins[i]<<" ";
      }
      
      outb.close();      


      /*------------------BUBBLE SORT---------------------*/
    
      cout << endl << "BUBBLE SORT" << "\t\t\t"; 
      float* array_bub = new float[v]; //array copy of the original for bubble sort
      for (int i = 0; i < v; i++) 
          array_bub[i] = array[i];
      begin = clock();
      bubble_sort(v, array_bub);
      end = clock();
      elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
      cout << v << "\t\t\t\t";
      cout << elapsed_secs << endl <<"----------------------------------------------------------------------------" << endl;
      
      ofstream outc;
      outc.open("list_bubble.txt");
      for(int i=0;i<v;i++)
      {
          outc <<array_bub[i]<<" ";
      }
    
      outc.close();
    
     delete[] array; //deleting all the dynamic array pointers
      delete[] array_ins;
      delete[] array_quick;
      delete[] array_merge;
      delete[] array_bub;

  }

  cout << endl;
  return 0;
}

void generate_rand(int array_size) {
  float temp1, temp2;
  ofstream myfile;
  srand(time(NULL));

  myfile.open ("list.txt");
  
  for(int n = 0; n < array_size; n++){ //generating floats and writing to list.txt
    temp1 = (rand() % 1000 + 1);
    temp2 = (rand() % 10) + 1;
    myfile << temp1/temp2 << " ";}

  myfile.close();
  return;
}

//Pseudocodes for the functions have been attached in another file

void merge_sort(float array_merge[], int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    merge_sort(array_merge, p, q);
    merge_sort(array_merge, q+1, r);
    merge(array_merge, p, q, r);}}

void merge(float array_merge[], int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;
  float L[n1 + 2], R[n2 + 2];

  for (int i = 1; i <= n1; i++) 
    L[i] = array_merge[p + i - 1];
  for (int j = 1; j <= n2; j++)
    R[j] = array_merge[q + j];

  L[n1 + 1] = numeric_limits<float>::max(); //using max value of float for sentinal
  R[n2 + 1] = numeric_limits<float>::max();

  int i = 1;
  int j = 1;

  for (int k = p; k <= r; k++) {
    if (L[i]<= R[j]) {
      array_merge[k] = L[i];
      i++;}
    else {
      array_merge[k] = R[j];
      j++;}}}

int partition(float array[], int p, int r)
{
  float x = array[r];
  int k = p-1;
  float holder, holder1;
  for(int j=p;j<r;j++) {
      if(array[j]<=x){
	  k++;
	  holder=array[k];
	  array[k]=array[j];
	  array[j]=holder;}}
    holder1=array[k+1];
    array[k+1]=x;
    array[r] = holder1;
  return(k+1);}

void quicksort(float array[], int p, int r){
  if (p < r){
      int q;
      q = partition(array,p,r);
      quicksort(array,p,q-1);
      quicksort(array, q+1, r);}}


void insertion_sort(int array_size, float array_ins[]) { 
  for (int j=1; j < array_size; j++){
    float key = array_ins[j];
    int i = j - 1;
    while (i >= 0 && array_ins[i] > key) {
      array_ins[i+1] = array_ins[i];
      i = i - 1;}
    array_ins[i+1]=key;}}

void bubble_sort(int array_size, float array_bub[]) {
  for (int i = (array_size - 1) ; i >= 0; i--){
    for (int n = 0; n < i; n++) {
      if (array_bub[n] > array_bub[n+1]) {
	float swap = array_bub[n];
	array_bub[n] = array_bub[n+1];
	array_bub[n+1] = swap;}}}}

void print_array(int array_size, float array[]) {
  cout << "[";
  for (int i = 0; i < array_size; i++) {
    cout << array[i];
    if (i != (array_size - 1)) cout << ", ";
    else cout << "]" << endl;} }




