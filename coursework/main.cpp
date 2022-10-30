#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <Windows.h>
using namespace std;

class Auto{
    private:
        string plate;
        string owner_name;
        string brand;
        int key;
        bool free = true;

    public:
        Auto(){
            this->plate = "";
            this->owner_name = "";
            this->brand = "";
            key = 0;
        }
        void set(string pl, string name, string br){
            this->plate = pl;
            this->owner_name = name;
            this->brand = br;
            this->free = false;
        }
        void set_key(int M){
            char numbers[5];
            int i=0;
            for(auto c: this->plate){
                if((int)c <58 && (int) c >47 ){
                    numbers[i] = c;
                    i++;

                }
            }
            this->key = atoi(numbers)%M;
        }
        int get_key() const{
            return this->key;
        }
        void output(){
            cout<< "Автомобиль: "<<this->brand<<
            "\nРегистрационный номер: "<<this->plate
            <<"\nВладелец: "<<this->owner_name<<"\n\n";
        }

        bool is_free(){
            return this->free;
        }
        ~Auto(){
            cout<<"Deleted\n";
        }

};

//string isPlate(){
//    setlocale(LC_ALL,"Russia");
//    string value;
//    char correct_letters[12] = "АВЕКМНОРСТУХ";
//    string correct_numbers = "0123456789";
//    bool flag;
//    cout<<"Введите номер автомобиля: ";
//}
//реформирать эту функцию так, чтобы ключи менялись для новой длиныы массива
int resize_arr(Auto* cars, int size)
{
    Auto* new_cars = new Auto[size*2];
    for(int i = 0; i < size; i++)
    {
        if(!cars[i].is_free()){
            cars[i].set_key(size*2);
            new_cars[cars[i].get_key()] = cars[i];
        }

    }
    size*=2;
    cars = new_cars;
    delete[] new_cars;
    return size;
}
void setup(Auto *cars, int &size){
    string name,brand,plate;
    Auto obj;
    int i = 0,key;
    for(int i = 0; i<size/2;i++){
        i = 0;
        cout<<"Введите номер автомобиля: ";
        cin>>plate;
        cin.clear();
        cin.ignore(32767, '\n');
        cout<<"Введите ФИО владельца: ";
        getline(cin, name);
        cout<<"Введите марку автомобиля: ";
        cin>>brand;
        obj.set(plate,name,brand);
        obj.set_key(size);
        cout<<obj.get_key()<<endl;
        while(true){
            key = obj.get_key();
            if(cars[key + i].is_free()){
                cars[key + i] = obj;
                cout<<cars[key+ i].is_free()<<endl;
                break;
            }
            else{
                i++;
                if(key+i>=size){
                    size = resize_arr(cars,size);
                }
            }
        }

    }
}
void print(Auto cars[], int size){
    cout<<"Данные обо всех автомобилях\n"<<endl;
    for(int i =0;i<size;i++){
        cars[i].output();
    }
}


//М416ЕВ178
int main(){
    setlocale(LC_ALL,"Russia");
    int arr_size;
    Auto obj;
    Auto *cars;
    cout<<"Введите количество автомобилей: ";
    cin>>arr_size;
    arr_size*=2;
    cars = new Auto[arr_size];
    setup(cars, arr_size);
    print(cars,arr_size);

    return 0;
}
