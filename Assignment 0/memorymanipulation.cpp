

// Write a function that resizes a dynamic array. It takes a pointer to a dynamically allocated array, its current size,
// and a new size as parameters and creates a new array with the new size, copies the old 
// elements, and deletes the old array. 
// int* resizeArray(int* arr, int currentSize, int newSize);
// Write a main function that demonstrates the operation of your function. 


//dynamic array are created using pointers and the new delete operators 

// key concepts: 
//dynamic array are created using pointers and the new delete operators 
// pointers: accessing and manipulating data in dynamically allocated memory 
// array resizing

#include <iostream>
using namespace std; 

int* resizeArray(int* arr, int currentSize, int newSize){
// int* arr is a poitner to a current dynamic array 
// returns a pointer to the new dynaic array 

    // allocates a new array of the new size 
    int * newArray = new int [newSize];

    //now need to decide how many elements from inital array to copy 
    int elementstoCopy;
    if (currentSize < newSize) {
        elementstoCopy = currentSize; // if newsize is bigger copy everything 
    } else {
        elementstoCopy = newSize; // if new size is smaller only copy number of elements that is the size of the array 
    }


    // now that we know how many elements to copy lets copy them 
    for (int i = 0; i < elementstoCopy; i ++){
        newArray[i] = arr[i];
    }

    // delete the old array --> wait does this delete the array or the memeory or is it the same thing 
    delete[] arr;

    return newArray;
}

//main function 
int main() {
    //create first array 
    int currentSize = 5;
    int* myArray = new int[currentSize];

    //lets put numbers in the array 
    //myArray = (1, 2, 3, 4, 5); apparently you cant do this and have to assign values to each element of the array indivifdually
    for (int i = 0; i < 5; i++) {
        myArray[i] = i + 1; // Fills the array with 1, 2, 3, 4, 5
    }

    //or this
    // myArray[0] = 1;
    // myArray[1] = 2;
    // myArray[2] = 3;
    // myArray[3] = 4;
    // myArray[4] = 5;

    // print original array 
    cout << "original array";
    for (int i = 0; i < currentSize; i ++){
        cout << myArray[i];
    }

    //resize array 
    int newSize = 13; 

    myArray = resizeArray(myArray, currentSize, newSize);
    
    // this array is bigger so lets gilly slots with 100
        for (int i = currentSize; i < newSize; i++) {
        myArray[i] = 100;
    }
    
    //print resized array
    cout << "resized new array";
    for (int i = 0; i < newSize; i++) {
        cout << myArray[i] << " ";
    }
    cout << endl;

    delete[] myArray;

    return 0; 
}






 



















