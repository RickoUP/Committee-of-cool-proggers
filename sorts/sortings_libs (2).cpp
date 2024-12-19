#include <iostream>

// Сортирующие сети

void heap_sort(int* M, size_t size) { 
    if (size < 2) return;
    //make heap
    for (size_t i=1; i<size; ++i) {
        size_t pos = i;
        while (pos != 0) {
            size_t parent = (pos - 1) / 2;
            if (M[parent] < M[pos]) { //поднимаеам элемент на уровень выше
                std::swap(M[parent], M[pos]);
                pos = parent;
            } else {
                break; // элемен на своей позиции - выходим
            }
        } //куча построена nlogn
    }

    //shift down each element
    size_t N = size; // кол-во эл-ов пирамиды
    for (size_t i = 1; i<size; ++i) {
        std::swap(M[N-1], M[0]); //скидываем макс эл-т в конец массива
        --N;
        size_t pos = 0;
        size_t pos_maxChild; 
        while ( (pos_maxChild = 2*pos + 1) < N) { // пока есть эл-т слева
            if (pos_maxChild + 1 < N) { // есть кто то справа
                if (M[pos_maxChild] < M[pos_maxChild+1]) {
                    ++pos_maxChild;
                }
            }
            if (M[pos] < M[pos_maxChild]) {
                std::swap(M[pos], M[pos_maxChild]);
                pos = pos_maxChild;
            } else { 
                break; // элемен на своей позиции - выходим
            }
        }
    }
}


template <typename T>
void print_arr(T* M, size_t size, const char* str) {
    std::cout << str;
    for (size_t i=0; i<size; ++i) {
        std::cout << M[i] << " ";
    }
    std::cout << std::endl;
}


void _merge(int* M, size_t first, size_t mid, size_t last) {
    size_t size = last - first + 1;
    int* tmp = new int[size];
    size_t indextmp = 0;
    size_t start1 = first, end1 = mid;
    size_t start2 = mid+1, end2 = last;

    while (start1 <= end1 and start2 <= end2) {
        if (M[start1] < M[start2]) {
            tmp[indextmp++] = M[start1++]; //после присваивания делаем ++
        } else {
            tmp[indextmp++] = M[start2++];
        }
    } //один из массивов закончился

    while (start1 <= end1) { tmp[indextmp++] = M[start1++]; }
    while (start2 <= end2) { tmp[indextmp++] = M[start2++]; }

    //копируем обратно в M
    indextmp = 0;
    while (first <= last) { M[first++] = tmp[indextmp++]; }
    delete[] tmp;
}
void _split(int* M, size_t first, size_t last) {
    if (first < last) { //пока не встретились границы (1 эл в разбиении)
        size_t mid = first + (last - first)/2;
        _split(M, first, mid);
        _split(M, mid + 1, last);
        _merge(M, first, mid, last);
    }
}
void merge_sort(int* M, size_t size) { //рекурсия
    if (size < 2) return;
    _split(M, 0, size - 1);
}



void merge_sortA(int* M, size_t size) {  //выделение памяти tmp один раз, потом просто обновление
    if (size < 2) return;
    int* tmp = new int[size];
    int* from = M;
    int* to = tmp;
    for (size_t step = 1; step < size; step *= 2) {
        size_t start1, end1, start2, end2 ;
        size_t indexto = 0;
        for (size_t start = 0; start < size; start += 2*step) {
            start1 = start;
            end1 = start1 + step;
            end1 = (end1 < size) ? end1 : size;
            start2 = end1;
            end2 = start2 + step;
            end2 = (end2 < size) ? end2 : size;
            while (start1 < end1 and start2 < end2) { 
                to[indexto++] = (from[start1] < from[start2]) ? from[start1++]: from[start2++];
            }
            while (start1 < end1) { to[indexto++] = from[start1++]; }
            while (start2 < end2) { to[indexto++] = from[start2++]; }
        }
        std::swap(from, to);
    }
    if (from != M) {
        size_t index = 0;
        while(index < size) {
            M[index] = tmp[index];
            ++index;
        }
    }
    delete[] tmp;
}

template <typename T>
void quick_sortStack(T* M, size_t size) { //стеком
    if (size < 2) return;
    //print_arr(M, size, "Step: ");
    size_t leftStack[64];
    size_t rightStack[64];
    size_t sizeStack = 0;

    //полодим на сортируемый диапозон [0, size - 1]
    leftStack[sizeStack] = 0;
    rightStack[sizeStack] = size - 1;
    ++sizeStack;

    while (sizeStack > 0) {
        //заберем значения левой и правой границ сортируемого диапозона
        size_t from = leftStack[sizeStack- 1];
        size_t to = rightStack[sizeStack- 1];
        --sizeStack;

        size_t left = from, right = to;

        size_t pindex = left + rand()%(right - left); //ранд эл-т левее left
        T pivot = M[pindex]; //опорный элемент 

        while (left < right) {
            while (M[left] < pivot) { ++left; }; //ищем слева нетак стоящий
            while (pivot < M[right]) { --right; }; //ищем справа нетак стоящий

            if (left < right) {
                std::swap(M[left], M[right]);
                ++left;
                --right;
            } 
            else if (left == right) {
                ++left;
                if (right > 0) --right;
            }
        }

        //сначала на стек поместить больший диапозон, потом меньший
        if (right - from < to - left) {
            //справа больше чем слева
            if (left < to) {
                leftStack[sizeStack] = left;
                rightStack[sizeStack] = to;
                ++sizeStack;
            }
            if (right > from) {
                leftStack[sizeStack] = from;
                rightStack[sizeStack] = right;
                ++sizeStack;
            }
        } else {
            if (right > from) {
                leftStack[sizeStack] = from;
                rightStack[sizeStack] = right;
                ++sizeStack;
            }
            if (left < to) {
                leftStack[sizeStack] = left;
                rightStack[sizeStack] = to;
                ++sizeStack;
            }
        }
        print_arr(M, size, "Step: ");
    } //while (sizeStack > 0) {
}

// сложность алгоритма nlog_2 (n)
void quick_sort(int* M, size_t size) { //рекурсия
    if (size < 2) return; //сорт не нужен
    size_t left = 0, right = size - 1;
    size_t pindex = rand() % size;
    int p = M[pindex]; //опорный элемент с индексом рандомного элемента массива

    while (left < right) {
        while (M[left] < p) { ++left; }; //ищем слева нетак стоящий
        while (p < M[right]) { --right; }; //ищем справа нетак стоящий

        if (left < right) {
            std::swap(M[left], M[right]);
            ++left;
            --right;
        } 
        else if (left == right) {
            ++left;
            if (right > 0) --right;
        }
    }
    quick_sort(M, right+1);
    quick_sort(M+left, size- left); //пользуемся указателем на массив
}
void quick_sort_killer(int* M, size_t n) { 
    for (size_t i =0; i<n; ++i) {
        M[i] = i;
    }
    for (size_t i=2; i<n; i+=2) {
        std::swap(M[i], M[i-1]);
    }
}

// сложность алгоритма nlogn
template <typename T> //подойдет для любого типа массива
void insert_bin_sort(T* M, size_t size) {  //сортировка вставками с бинпоиском
    T tmp;
    for (size_t j=1; j<size; ++j) {
        size_t left = 0, right = j;
        size_t mid;
        do { //бинарный поиск
            // mid = (right+right) / 2; переполнение, перепишем:
            mid = left + (right - left) / 2;
            if (M[j] < M[mid]) {
                right = mid ? (mid-1) : 0;
            }
            else {
                left = mid + 1;
            }

        } while (left < right);
        right  += (M[j] < M[right]) ? 0: 1;

        if (j > right) { //сдвигаем на 1 каждый элемент
            tmp = M[j];
            for (size_t i = j; i>right; --i) {
                M[i] = M[i-1];
            }
            M[right] = tmp;
        }
    }
}

void insert_sort(int* M, size_t size) { //сортировка вставками
    for (size_t j=1; j<size; ++j){
        //j - номер вставляемого элемента
        int tmp = M[j];
        size_t i;

        for (i = j; i >= 0; --i) {

            if (tmp < M[i-1]) {
                M[i] = M[i-1]; 
            } else break;
        }
        if (i!=j) {
            M[i] = tmp;
        }
    }
}

// сложность алгоритма O(n^2)
void choose_sort(int* M, size_t size) {  //сортировка выбором  
    if (size == 0) {
        return;
    }
    for (size_t step = 0; step < size-1; ++step) {
        size_t min_ind = step;
        for (size_t i = min_ind +1; i < size; ++i) {

            if (M[i] < M[min_ind]) {
                min_ind = i;
            }
        }
        if (step < min_ind) {
            std::swap(M[step], M[min_ind]);
        }
    }
}


// сложность алгоритма O(n^2)
template <typename T> //подойдет для любого типа массива
void bubble_sort(T* M, size_t size) { 
}


void random_arr(int *M, size_t n) { 
    for (size_t i = 0; i<n; ++i) {
        M[i] = rand()%900 + 100;
    }
}
void reversed_arr(int *M, size_t n) {
    for (size_t i = 0; i<n; ++i) {
        M[i] = n-i;
    }
}
void sorted_arr(int *M, size_t n) {
    for (size_t i = 0; i<n; ++i) {
        M[i] = i;
    }
}
void const_arr(int *M, size_t n) {
    for (size_t i = 0; i<n; ++i) {
        M[i] = 1;
    }
}
template <typename T>
bool is_sorted(T *M, size_t n) {
    for (size_t i = 1; i<n; ++i) {
        if (M[i] < M[i-1]) {
            return false;
        }
    }
    return true;
}

void sort_arr(int *M, size_t n, const char* arr_name) {
    std::cout << "--- array: " << arr_name << std::endl;
    if (n<25) print_arr(M, n, "Before: ");

    heap_sort(M, n);
    if (n<25) print_arr(M, n, "After: ");
    if (!is_sorted(M, n)) {
        std::cout << "ERROR: not sorted!\n";
    }
}

void tester(size_t n, const int* randarr, const char* sorter_name) {
    std::cout << "\n============ Method " << sorter_name << "===========\n";

    int* A = new int[n];
    if (A == nullptr) {
        std::cout << "Out of memory\n";
        return;
    }

    for (size_t i =0; i<n; ++i) {
        A[i] = randarr[i];
    } 
    sort_arr(A, n, "rand2");

    reversed_arr(A, n);
    sort_arr(A, n, "reversed");

    sorted_arr(A, n);
    sort_arr(A, n, "sorted");

    const_arr(A, n);
    sort_arr(A, n, "const");   

    quick_sort_killer(A, n);
    sort_arr(A, n, "killer");   
    
    delete[] A;
}

