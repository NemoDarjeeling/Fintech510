#include <iostream>
using namespace std;

// Function to print an array
void printArray(int array[], int size) {
  for (int i = 0; i < size; i++) {
    cout << array[i] << " ";
  }
  cout << endl;
}

int partition(int array[], int low, int high, int num) {
  int pivot = array[high];
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      int temp = array[i];
      array[i] = array[j];
      array[j] = temp;
      num += 1;
    }
  }

  int temp = array[i + 1];
  array[i + 1] = array[high];
  array[high] = temp;
  num += 1;

  return (i + 1);
}

void sort(int array[], int low, int high, int num) {
  if (low < high) {
    if(num == 5) {
      std::cout << "num == 5: ";
      for (int i = 0; i < 9; i++) {
        std::cout << array[i] << " ";
      }
      std::cout << std::endl;
    }
    if(num == 6) {
      std::cout << "num == 6: ";
      for (int i = 0; i < 9; i++) {
        std::cout << array[i] << " ";
      }
      std::cout << std::endl;
    }
    int pi = partition(array, low, high, num);
    sort(array, low, pi - 1, num);
    sort(array, pi + 1, high, num);
  }
}

// Driver code
int main() {
  int num = 0;
  int data[] = {5, 6, 4, 7, 3, 8, 2, 9, 1};
  int size = sizeof(data) / sizeof(data[0]);
  sort(data, 0, size-1, num);
  cout << "Sorted array in ascending order:\n";
  printArray(data, size);
}
