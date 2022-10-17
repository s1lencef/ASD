#include <iostream>
#include <map>
#include <fstream>

using namespace std;

// словарь с соотнесением символов и индексов массивов в Большом массиве
map <int, string> arrays = {{0,"a"},
                            {1,"b"},
                            {2,"c"},
                            {3,"d"},
                            {4,"e"}
                            };


// функция проверки корректности ввода
int is_number(int*index = 0){
    int n;
    while(true){
        cin>>n;
        if(cin.fail()){
            cout<<"Введено неверное значение, повторите попытку: ";
            cin.clear();
            cin.ignore(32767, '\n');

        }
        else{
            return n;
        }

    }
}
// функция обмена значениями двух переменных через вспомогательную
void swap(int *x, int *y)
{
    int t = *x ;//t - вспомогательная переменная
    *x = *y;
    *y = t;
}

// вывод одного массива на экран
void print(int a[],int n){
    for(int j = 0; j<n;j++){
        cout<<a[j]<<' ';
    }
    cout<<endl;
}
// функция инициализации массивов
void init( int *arr[5],int (&len)[5]){
    cout<< "Введите размерности массивов: "<<endl;
    for(int i = 0; i<5;i++){
        len[i] = is_number();
        arr[i] = new int[len[i]];
    }
    for(int i = 0; i<5;i++){
        cout<<"Введите элементы массива "<<arrays[i]<<": ";
        for(int j = 0; j<len[i];j++){
            arr[i][j] = is_number();
        }
    }
    cout<<"Получены массивы: "<<endl;
    for(int i = 0; i<5;i++){
        cout<<arrays[i]<<": ";
        print(arr[i],len[i]);
    }
}
// вызов меню, возвращается соответвующий номер пункта
int get_menu(){
    int n;
    cout<<"Menu:\n "
          "1.Initilization arrays and output file\n "
          "2.Result of bubble sort\n "
          "3.Result of min sort\n "
          "4.Result of insert sort\n "
          "5.Result of Shell sort\n "
          "6.Result of Hoor sort\n "
          "0. Finish programm\n";
    while(true) {
        n = is_number();
        // проверка на то, что такой номер действительно есть в меню
        if (n < 7 && n >= 0) {
            return n;
        } else {
            cout << "Try again: ";
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }
    }
}
// получение индекса массива из его буквы
int get_index(){
    char c;
    cout<<"Введите название массива, который вы хотите отсортировать(a,b,c,d,e) Чтобы отсортировать все массивы введите <0>"<<endl;
    cin>>c;
    return (int) c - ((int)'a');
}
//функция сортировки пузырьком(обменом)
void bubble_sort(int a[],int n){
    int i, j;
    for (i=0; i<n; i++){
        for (j=n-1; j>i; j--){
            if (a[j-1] > a[j]){
                swap(&a[j-1],&a[j]);// если следующий элемент больше текущего, то проиходит обмен
            }
        }
    }
}
// функция сортировки выбором
void min_sort(int a[], int n)
{ int i, j, k;
    for (i=0; i<n-1; i++)
    { for (j=i+1; j<n; j++) { // находим в цикле
            k = i;
            if (a[j] < a[k]) // минимальный элемент
            {
                k = j; // запоминаем его номер в к
                swap(&a[k], &a[i]);// меняем местами минимальный и
            } // элемент, с которого начинался цикл
        }
    }
}
// функция сортировки вставкой
void insert_sort (int a[], int n){
    int i, j;
    for (i=1; i<=n-1; i++){ //упорядочивание начинается со второго  и первого элментов
        j=i; // записываем предыдущий элемент
        while (a[j]<a[j-1] && j>=1){
            swap(&a[j],&a[j-1]);
            j--;
        }
    }
}
// функция сортировки методом Шелла
void shell_sort(int *x,int n)
{ int i,j;
    int gap; //шаг сортировки
    int sorted; //флаг окончания этапа сортировки
    for(gap=n/2;gap>0;gap/=2)//начало сортировки
        do
        { sorted = 0;
            for(i=0,j=gap;j<n;i++,j++){
                if(*(x+i)>*(x+j)){
                    swap((x+i),(x+j));
                    sorted = 1;
                }
            }
        }
        while(sorted); }
// функция методом Хоора (быстрая сортировка)
void quick_sort(int a[], int n, int left, int right)
{
    int i=left, j=right; //Инициализируем переменные левой иправой границами подмассива
    int test=a[(left+right)/2]; //Выбираем в качестве элемента разбиения средний элемент массива

    do { while (a[i] < test)
            i++;
//находим элемент, больший элемента разбиения
        while (a[j] > test)
            j--;
//находим элемент, меньший элемента разбиения
        if (i<=j)
        { swap(&a[i], &a[j]);
            i++; j--; }
    }
    while(i <= j); //рекурсивно вызываем алгоритм дляправого и левого подмассива
    if (i<right)
        quick_sort(a, n, i, right);
    if (j>left)
        quick_sort(a, n, left, j);
}
// функция записи в файл
void write_file(int *arr[5],int len[5], int index, int type, string name){
    ofstream output_file(name,ios::app);
// в зависимости от типа сортировки записывается соответствующий заголовок
    switch(type){
        case 2:
            output_file<<"Отсортировано пузырьком:\n";
            break;
        case 3:
            output_file<<"Отсортировано методом выбора:\n";
            break;
        case 4:
            output_file<<"Отсортировано методом вставки:\n";
            break;
        case 5:
            output_file<<"Отсортировано методом Шелла:\n";
            break;
        case 6:
            output_file<<"Отсортировано методом Хоора:\n";
            break;
        default:
            break;
    }
    // если были отсортированы все массивы
    if(index<0){
        for(int i = 0; i<5;i++){
            output_file<<arrays[i]<<": ";
            for(int j = 0; j<len[i];j++){
                output_file<<arr[i][j]<<' ';
            }
            output_file<<"\n\n";
        }
    }
    // если отсортирован 1 массив
    else{
        output_file<<arrays[index]<<": ";
        for(int j = 0; j<len[index];j++){
            output_file<<arr[index][j]<<' ';
        }
        output_file<<"\n\n";
    }

    cout<<"Запись осуществлена в файл <"<<name<<">"<<endl;
    output_file.close();
}
int main() {
    int *BigArray[5];
    int w2d, index, change;
    int arr_len[5];
    bool flag = false;
    string filename;
    while(true){
        // узнаем, что пользователь хочет сделать
        w2d = get_menu();
        if (w2d == 0){
            return 0;
        }
        else if (w2d == 1){
            init(BigArray,arr_len);
            cout<<"Хотите добавить файл для записи? (1 - да, 2 - нет)\n";
            change = is_number();
            if(change== 1){
                cout<<"Введите полное имя файла, в который вы хотите записать результаты: ";
                cin>>filename;
            }
        }
        else{
            //выбор способа сортировки
            index = get_index();
            // переменная, чтобы проще было определять, необходимо обрарботать все массивы или какой-то один
            flag = index < 0;
            switch (w2d) {
                case 2:
                    if(flag){
                        for(int i = 0; i<5;i++){
                            bubble_sort(BigArray[i],arr_len[i]);
                            print(BigArray[i], arr_len[i]);
                        }
                    }
                    else{
                        bubble_sort(BigArray[index],arr_len[index]);
                        print(BigArray[index], arr_len[index]);
                    }
                    write_file(BigArray,arr_len,index,w2d,filename);
                    break;
                case 3:
                    if(flag){
                        for(int i = 0; i<5;i++){
                            min_sort(BigArray[i],arr_len[i]);
                            print(BigArray[i], arr_len[i]);
                        }
                    }
                    else{
                        min_sort(BigArray[index],arr_len[index]);
                        print(BigArray[index], arr_len[index]);
                    }
                    write_file(BigArray,arr_len,index,w2d,filename);
                    break;
                case 4:
                    if(flag){
                        for(int i = 0; i<5;i++){
                            insert_sort(BigArray[i],arr_len[i]);
                            print(BigArray[i], arr_len[i]);
                        }
                    }
                    else{
                        insert_sort(BigArray[index],arr_len[index]);
                        print(BigArray[index], arr_len[index]);
                    }
                    write_file(BigArray,arr_len,index,w2d,filename);
                    break;
                case 5:
                    if(flag){
                        for(int i = 0; i<5;i++){
                            shell_sort(BigArray[i],arr_len[i]);
                            print(BigArray[i], arr_len[i]);
                        }
                    }
                    else{
                        shell_sort(BigArray[index],arr_len[index]);
                        print(BigArray[index], arr_len[index]);
                    }
                    write_file(BigArray,arr_len,index,w2d,filename);
                    break;
                case 6:
                    if(flag){
                        for(int i = 0; i<5;i++){
                            quick_sort(BigArray[i],arr_len[i],0,arr_len[i]-1);
                            print(BigArray[i], arr_len[i]);
                        }
                    }
                    else{
                        quick_sort(BigArray[index],arr_len[index],0,arr_len[index]-1);
                        print(BigArray[index], arr_len[index]);
                    }
                    write_file(BigArray,arr_len,index,w2d,filename);
                    break;
                default:
                    break;
            }
        }
    }
}
