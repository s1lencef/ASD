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
            this->key = 0;
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
        void set_null(){
            this->plate = "";
            this->owner_name = "";
            this->brand = "";
            this->key = 0;
            this->free = true;
        }
        int get_key() const{
            return this->key;
        }
        string get_plate()const{
            return this->plate;
        }
        void output(){
            cout<< "Автомобиль: "<<this->brand<<
            "\nРегистрационный номер: "<<this->plate
            <<"\nВладелец: "<<this->owner_name<<"\n\n";
        }

        bool is_free(){
            return this->free;
        }
//        ~Auto(){
//            cout<<"Deleted\n";
//        }

};

bool check_plate(string &value){
    string correct_letters = "АВЕКМНОРСТУХ";
    string correct_numbers = "0123456789";
    int count = 0;
    if(value.size() != 12){
        return false;
    }
    for (int i = 0; i<9;i++){
        cout<<"int:"<<(int)value[i]<<endl;
        if(i==0 || i == 4 || i == 5){

            for( auto c: correct_letters){
                if(c == value[i]){
                    count ++;

                }
            }
        }
        else{

            for( auto c: correct_numbers){
                if(c == value[i]){
                    count ++;

                }
            }
        }
        cout<<count<<endl;
    }
    if (count == 9){
        return true;
    }
    return false;
}
string isPlate(){
    setlocale(LC_ALL,"Russia");
    string value;

    while(true){
        cin>>value;
        if(check_plate(value)){
            return value;
        }
        else{
            cout<<"Введенный номер не соответствует стандарту ANNNAANNN Повторите попытку: ";
            cin.clear();
            cin.ignore(32767, '\n');
        }
    }
}

int isNumber(){
    int n;
    while (true){
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
//реформирать эту функцию так, чтобы ключи менялись для новой длиныы массива
Auto*  resize_arr(Auto* cars, int &size)
{   cout<<"\nresize\n";
    Auto* new_cars = new Auto[size*2];

    for(int i = 0; i < size; i++)
    {
        if(!cars[i].is_free()){
            cout<<i<<endl;
            cars[i].set_key(size*2);
            cout<<cars[i].get_key()<<endl;
            new_cars[cars[i].get_key()] = cars[i];
        }
    }
    size *=2;
    cout<<"\n"<<size<<endl;
    delete[] cars;
    return new_cars;
}
Auto* add_car(Auto *cars, int &size){
    string name,brand,plate;
    Auto obj;
    int i = 0,key;
    cout<<"Введите номер автомобиля: ";
    cin>>plate;
    cin.clear();
    cin.ignore(32767, '\n');
    cout<<"Введите ФИО владельца: ";
    getline(cin, name);
    cout<<"Введите марку автомобиля: ";
    cin>>brand;
    obj.set(plate,name,brand);
    while(true){
        obj.set_key(size);
        key = obj.get_key();
        cout<<"\n"<<key+i<<"   "<<obj.get_plate()<<"   "<<cars[key+i].is_free()<<endl;
        if(cars[key+i].is_free()){
            cars[key+i] = obj;
            break;
        }
        else{
            i++;
            if(key+i>=size){
                i=0;
                cars = resize_arr(cars,size);
                cout<<"\n"<<size<<endl;
            }
        }
    }
    return cars;
}
Auto* setup(Auto *cars, int &size){

    const int count = size;
    for(int j = 0; j<count/2;j++){
        cars = add_car(cars, size);
    }
    return cars;
}
void print(Auto cars[], int size){
    cout<<"Данные обо всех автомобилях\n"<<endl;
    for(int i =0;i<size;i++){
        if(!cars[i].is_free()){
            cars[i].output();
        }

    }
}

int plate_search(string num, Auto * cars, int size){
    Auto obj;
    int key, i = 0;
    obj.set(num, "", "");
    obj.set_key(size);
    key = obj.get_key();
    while (true){
        if(cars[key + i].get_key()== key){
            if(cars[key + i].get_plate() == num  ){
                cout<<"Автомобиль с указанным номером найден!\n\nИнформация об автомобиле:\n";
                cars[key + i].output();
                return  key+i;
            }
            else{
                i++;
            }
        }
        else{
            cout<<"Автомобиль отсутствует в базе!"<<endl;
            return -1;
        }
    }
}

Auto* remove_last(Auto * cars, int size){
    int last_key;
    for (int i = 0; i<size; i++){
        if( !cars[i].is_free()){
            last_key = i;
        }
    }
    cars[last_key].set_null();
    cout<<"Запись о последнем автомобиле в базе удалена!"<<endl;
    return cars;
}
Auto* remove_first(Auto * cars, int size){
    for (int i = 0; i<size; i++){
        if( !cars[i].is_free()){
            cars[i].set_null();
            break;
        }
    }
    cout<<"Запись о последнем автомобиле в базе удалена!"<<endl;
    return cars;
}

Auto *remove_by_plate(Auto * cars, int size, string dplate){
    int key = plate_search(dplate,cars,size);
    int choise;
    if(key == -1){
        cout<<"Невозможно удалить данные об автомобиле, так как его нет в базе";
    }
    else{
        cout<<"Вы точно хотите удалить этот автомобиль из базы? (1-да/0-нет)"<<endl;
        choise = isNumber();
        if(choise == 1){
            cout<<"\nДанные об автомобиле "<< cars[key].get_plate()<<" удалены!"<<endl;
            cars[key].set_null();
        }
        else{
            cout<<"Удаление отменено."<<endl;
        }


    }
    return cars;

}

//М416ЕВ098
int main(){
    setlocale(LC_ALL,"Russia");
    int arr_size, k = 0;
    string plate;
    Auto obj;
    Auto *cars;
    cout<<"Введите количество автомобилей: ";
    arr_size = isNumber();
    arr_size*=2;
    cars = new Auto[arr_size];
    cars = setup(cars, arr_size);
    print(cars,arr_size);
    cout<<"Введите номер автомобиля, который хотите удалить: ";
    cin>>plate;
    cars  = remove_by_plate(cars, arr_size,plate);
    print(cars,arr_size);

    return 0;
}
