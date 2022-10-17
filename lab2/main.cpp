#include <iostream>
#include <stdio.h>
#include <malloc.h>

using namespace std;

//3.Создать очередь для целых (положительных и отрицательных) чисел. Максимальный размер очереди вводится с экрана.
// Создать функции для ввода, вывода и определения размера очереди. Ввести 6 элементов.
// Вывести 2 первых элемента очереди. Вывести размер оставшейся очереди.


//Создание структуры очереди на основе массива
typedef struct
{
    int *queue;
    int head;
    int tail;
    int size;

} QUEUE;

// Поскольку структура содержит только целые числа, введем дополнительную функцию для проверки,
// что считанный символ - число
int isInteger(){
    int n;
    while(true){
        cin>> n;
        if(cin.fail()){
            cout<<"Введенный символ не является числом! Повторите ввод: ";
            cin.clear();
            cin.ignore();
            continue;
        }
        else{
            return n;
        }
    }
}

// инициализация очереди(выделение памяти под числа)
int Init(QUEUE* Queue, int nSize)
{
    Queue->queue = (int*)malloc(nSize*(sizeof(int)));

    if (Queue->queue == nullptr) return -1;

    Queue->size = nSize;
    Queue->head = 0;
    Queue->tail = 0;

    return nSize;
}

// функция добавления числа
int Add(QUEUE* Queue, int nElement) {
    if (Queue->tail + 1 == Queue->head){
        return -1;//проверка на наличие свободных ячеек в очереди
    }
    if ((Queue->tail == Queue->size) && (Queue->head > 1)){
        Queue->tail = 0;
    }//Показывает, что достигнут конец памяти и перемещает "указатель" в начало для проверки на наличие свободных ячеек
    Queue->queue[Queue->tail++] = nElement;// запись числа
    return 1;
}

// функция, аналогичная pop для стека
int Extract(QUEUE* Queue)
{
    int w;
    if (Queue->head == Queue->tail) return -1;// очередь пуста
    w = Queue->queue[Queue->head];
    if (Queue->head == Queue->size - 1)
        Queue->head = 0; // достигнут конец очереди, "указатель" перемещен в начало
    else
        Queue->head++;//удаление связи с последним элементом
    return w;
}

//функции для очистки очереди и памяти от нее
void Clear(QUEUE* Queue)
{
    Queue->head = 0;
    Queue->tail = 0;
}
void Free(QUEUE* Queue)
{ free(Queue->queue); }

// получение размера очереди
int GetSize(QUEUE* Queue)
{
    if (Queue->head == Queue->tail)
        return 0; // Очередь пуста
    if (Queue->head < Queue->tail) // в зависимости от положения указателей, число непустых ячеек вычисляется по-разному
        return (Queue->tail - Queue->head);
    else
        return (Queue->size - (Queue->head - Queue->tail));

}


// функция вывода определенного количества элементов очереди(если количество не задано, выводится вся)
void output(QUEUE*Queue, int count = 0){
    int x  = 0;
    if(count == 0){
        count = Queue->tail;
    }
    for(int i = 0; i<count;i++){
        x = Extract(Queue);
        cout<<x<<' ';
        if(Queue->head == 0) {
            break;
        }
    }

}
// функция ввода и инициализации
void input(QUEUE *Queue){
    int qsize,x;
    cout<<"Введите размер очереди: ";
    qsize = isInteger();
    Init(Queue, qsize);
    cout<<"Введите элементы через пробел: ";
    for(int i  = 0; i<qsize; i++){
        x = isInteger();
        Add(Queue,x);
    }

}
int main()
{
    QUEUE Queue;
    int n;

    input(&Queue);
    cout<<"Введите количество элементов, которые хотите вывести(0, чтобы вывести все доступные): ";
    n = isInteger();
    output(&Queue,n);
    cout<<"\nРазмер оставшейся очереди: ";
    cout<<GetSize(&Queue);


    Clear(&Queue);
    Free(&Queue);

    return 0;
}
