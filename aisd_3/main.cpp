/*3. Создать список с помощью массива целых чисел.
 * Все нечетные элементы списка вывести на экран.*/

#include <iostream>
#include <stdlib.h>
#define MAX 100

using namespace std;

//фукция инициализации списка, для начала записывает во все массивы нулевые значения
void init(int (&prev)[100],int (&next)[100],int (&list)[100]){
    for (int i=0; i<MAX; i++){
        list[i]=next[i]=prev[i]=0;
    }
}
// функция ввода элементов списка,
int input(int (&prev)[100],int (&next)[100],int (&list)[100],int &begin,int &end){
    int n;
    printf("Введите количество элементов: ");
    cin>>n;

    prev[0]=-1;
    printf("Введите элменты списка: ");
    int count=0;
    for (int i=0; i<n; i++)
    {
        cin>>list[i];
        next[i]=i+1;//создание ссылки на следующий элемент
        prev[i]=i-1;// ссылка на предущий, обе отталкиваются от текущего элемента
                    // и хранят в себе соответствующие инлексы других элеемнтов
        count++;//счетчик количества элементов
    }

    prev[0]=-1;//ссылка на предыдщей элемент у первого элемента так как он ни на что не указывает
    next[count]=-1;// ссылка на следующий элемент у последнего строится по тому же принципу
    begin=0; // индекс первого элемента
    end=count-1;//индекс последнего элемента
    return count;
}
// функция вывода всех нечетных чисел
void odd_output(int begin, int (&next)[100],int (&list)[100]){
    printf("Нечетные элементы списка: ");
    int temp=begin;// вспомогательная переменная принимает ссылку  на первый элемент
    do {
        if(list[temp]%2 != 0){
            cout<<list[temp]<<' ';
        }
        temp=next[temp];//переход к следующему элеемнту
    } while (next[temp]!=-1);// пока не встречен конец массива
    cout<<endl;
}
int main (){
    // двусвязный список создан на основе трехмерного массива
    int list[MAX];
    int next[MAX];
    int prev[MAX];
    int end=0,begin=0;
    int a[2] = {1,2};

    setlocale(LC_ALL,"Russia");


    init(prev,next,list);

    input(prev,next,list,begin,end);

    odd_output(begin, next,list);

    cout<<"Program finished!"<<endl;
    return 0;
}
