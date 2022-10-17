
#include <malloc.h>
#include <iostream>
using namespace std;
//Стек для символов на основе массива
typedef struct
{char *stack; // массив элементов стека(динамический)
    int head; // количество заполненных элементов
    int size; // максимальный размер стека
}STACK;

//Инициализация функций, которые будут обрабатывать Стек

//выделение памяти под стек
int Init(STACK* Stack, int nSize)
{
    Stack->stack = (char*)malloc(nSize);
    if (Stack->stack == NULL) return -1;
    Stack->size = nSize;
    Stack->head = 0;
    return nSize;
}

// запись нового элемента
int Push(STACK* Stack, char cElement)
{if (Stack->head == Stack->size) return -1;
    Stack->stack[Stack->head++] = cElement;
    return 1;
}

// функция считывает верхний элемент, возвращая его и закрывая ему доступ к стеку
char Pop(STACK* Stack)
{if (Stack->head == 0) return 0;
    return Stack->stack[--Stack->head]; }

// получение размера стека
int GetSize(STACK* Stack)
{ return Stack->head;
}
// функции, необходимые для очистки памяти после работы со стеком
void Clear(STACK* Stack)//
{Stack->head = 0;}

void Free(STACK* Stack)
{ free(Stack->stack); }

// обобщенная функция вывода стека
void print(STACK* Stack){
    if (Stack->head == 0) return;
    int length = Stack->head;
    cout<<"Стек: ";
    while(length){
        cout<<Stack->stack[--length]<<' ';
    }
}


// функция заполнения стека
void input(STACK* Stack){
    const char end = '0';// эталонный символ
    char e;
    cout<< "Введите элементы (для окончания введите: 0) : ";
    while(Stack->head < Stack->size){
        cin>> e;
        if (e == end) {
            break;
        }
        Push(Stack, e);

    }

}
int main()
{
    int stack_size;
    STACK Top;
    cout<< "Введите размер стека: ";
    cin>> stack_size;
    Init(&Top,stack_size);
    input(&Top);
    print(&Top);
    Clear(&Top);
    Free(&Top);
    return 0;
}


