#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <set>
#define SIZE 5000

using namespace std;
//Структура - узел дерева
struct TNode {
    int field;           
    TNode* left;        
    TNode* right;      

    TNode(int x) : field(x), left(nullptr), right(nullptr) {} 
};

//Вывод узлов дерева (обход в инфиксной форме)
void treePrint(TNode* tree) {
    if (tree != nullptr) { 
        treePrint(tree->left); 
        cout << tree->field << " "; 
        treePrint(tree->right); 
    }
}

//Добавление узлов в дерево
TNode* addNode(int x, TNode* tree) {
    if (tree == nullptr) { 
        return new TNode(x); 
    }
    if (x < tree->field) { 
        tree->left = addNode(x, tree->left); 
    } else { 
        tree->right = addNode(x, tree->right); 
    }
    return tree;
}

//Освобождение памяти дерева
void freeMem(TNode* tree) {
    if (tree != nullptr) { 
        freeMem(tree->left); 
        freeMem(tree->right); 
        delete tree; 
    }
}
//генерирование уникальных целых чисел
void generateUniqueNumbers(int* arr, int size, int min, int max) {
    set<int> uniqueNumbers;
    while (uniqueNumbers.size() < size) {
        uniqueNumbers.insert(rand() % (max - min + 1) + min);
    }
    copy(uniqueNumbers.begin(), uniqueNumbers.end(), arr);
}

int main() {
    srand(static_cast<unsigned int>(time(0))); 
    int arr[SIZE];
    
    //Генерация 20 уникальных случайных чисел
    generateUniqueNumbers(arr, SIZE, 1, 50000); 

    TNode* root = nullptr; 
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; i++) {
        root = addNode(arr[i], root); 
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> dur = end - start;
    cout << "Отсортированные числа: ";
    treePrint(root); 
    cout << endl;
    cout << "Время выполнения сортировки: " << dur.count() << " микросекунд" << endl;
    freeMem(root); 
    return 0;
}