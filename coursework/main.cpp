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
            int i=5, numbers = 0;
            for(auto c: this->plate){
                if((int)c <58 && (int) c >47 ){
                    numbers += ((int)c - 48) * pow(10, i);
                    i--;
                }
            }
            this->key = numbers%M;
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
        string get_brand()const{
            return this->brand;
        }
        void output(){
            cout<< "Автомобиль: "<<this->brand<<
            "\nРегистрационный номер: "<<this->plate
            <<"\nВладелец: "<<this->owner_name<<"\n\n";
        }

        bool is_free() const{
            return this->free;
        }
        ~Auto(){
        }

};
bool check_plate(string &value){
    setlocale(LC_ALL,"Russia");
    string correct_letters = "АВЕКМНОРСТУХ";
    string correct_numbers = "0123456789";
    int count = 0;
    int i = 0;
    if(value.size() != 12){
        return false;
    }
    for(int j= 0; j<12;j++){

    }
    for (auto c: value){
        if(i==1 || i == 6 || i == 8){
            for(int k = 1; k<24; k+=2){

                if((int)correct_letters[k] == (int)value[i]){
                    count ++;
                }
            }
        }
        else{

            for( int k = 0; k<10; k++){
                if((int)correct_numbers[k] == (int)value[i]){
                    count ++;

                }
            }
        }
        i++;
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
            cout<<"Введенный номер не соответствует стандарту \"ANNNAANNN\" Повторите попытку: ";
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

class Cars{
private:
    Auto* cars;
    int arr_size;
    int length = 0;
    bool deleted = false;
public:
    Cars(int arr_size){
        this->arr_size = arr_size;
        this->cars = new Auto[arr_size];
    }
    void set(int new_size){
        this->arr_size = new_size;
        this->cars = new Auto[new_size];
    }

    void resize_arr()
    {
        int new_size = this->arr_size*2;
        Auto* new_cars = new Auto[new_size];

        for(int i = 0; i < this->arr_size; i++)
        {
            if(!this->cars[i].is_free()){
                this->cars[i].set_key(new_size);
                new_cars[this->cars[i].get_key()] = this->cars[i];
            }
        }
        this->arr_size = new_size;
        delete[] this->cars;
        this->cars =  new_cars;
    }
    void add_car( string name, string brand, string plate){
        Auto obj;
        int i = 0,key;
        obj.set(plate,name,brand);

        while(true){
            obj.set_key(this->arr_size);
            key = obj.get_key();
            if(this->cars[key+i].is_free()){
                this->cars[key+i] = obj;
                break;
            }
            else{
                i++;
                if(key+i>=this->arr_size){
                    i=0;
                    this->resize_arr();
                }
            }
        }
        this->length ++;
    }
    int plate_search(string num){
        Auto obj;
        int key, i = 0;
        obj.set(num, "", "");
        obj.set_key(this->arr_size);
        key = obj.get_key();
        while (true){
            if(this->cars[key + i].get_key()== key){
                if(this->cars[key + i].get_plate() == num  ){
                    cout<<"Автомобиль с указанным номером найден!\n\nИнформация об автомобиле:\n";
                    this->cars[key + i].output();
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


    void print(){
        if(!this->deleted){
            cout<<"Данные обо всех автомобилях\n"<<endl;
            for(int i =0;i<this->arr_size;i++){
                if(!this->cars[i].is_free()){
                    this->cars[i].output();
                }
            }
        }
        else{
            cout<<"База пуста!\n"<<endl;
        }

    }
    void remove_last(){
        int last_key;
        for (int i = 0; i<this->arr_size; i++){
            if( !this->cars[i].is_free()){
                last_key = i;
            }
        }
        this->cars[last_key].set_null();
        cout<<"Запись о последнем автомобиле в базе удалена!"<<endl;
        this->length --;
        if(this->length == 0){
            this->deleted = true;
        }
    }
    void remove_first(){
        for (int i = 0; i<this->arr_size; i++){
            if( !this->cars[i].is_free()){
                this->cars[i].set_null();
                break;
            }
        }
        cout<<"Запись о последнем автомобиле в базе удалена!"<<endl;
        this->length --;
        if(this->length == 0){
            this->deleted = true;
        }
    }
   void remove_by_plate(string dplate){
        int key = plate_search(dplate);
        int choise;
        if(key == -1){
            cout<<"Невозможно удалить данные об автомобиле, так как его нет в базе";
        }
        else{
            cout<<"Вы точно хотите удалить этот автомобиль из базы? (1-да/0-нет)"<<endl;
            choise = isNumber();
            if(choise == 1){
                cout<<"\nДанные об автомобиле "<< this->cars[key].get_plate()<<" удалены!"<<endl;
                this->cars[key].set_null();
            }
            else{
                cout<<"Удаление отменено."<<endl;
            }
            this->length --;
            if(this->length == 0){
                this->deleted = true;
            }
        }
    }
   int* brand_search(string br){
       int *brand_indexes = new int[this->arr_size];
       int k = 0;
       for(int i  = 0; i<this->arr_size; i++){
           brand_indexes[i] = -1;
       }
        for(int i = 0; i<this->arr_size; i++){
            if(br == cars[i].get_brand()){
                brand_indexes[k] = i;
                k++;
            }
        }
       k  = 0;
        if(brand_indexes[k] != -1){
            cout<<"Автомибили марки \""<<br<<"\":"<<endl;
            while(brand_indexes[k] != -1){
                this->cars[brand_indexes[k]].output();
                k++;
            }
        }
        else{
            cout<<"Автомобилей такой марки нет в базе!"<<endl;
        }
        return brand_indexes;
    }

   Auto* get_cars(){
        return this->cars;
   }
   int get_size() const{
        return this->arr_size;
    }
    void clear(){
       delete[] this->cars;
       this->deleted = true;
       cout<<"Данные об автомобилях удалены"<<endl;
    }
};

void setup(Cars &cars){
    string name,brand,plate;
    const int count = cars.get_size();
    for(int j = 0; j<count/2;j++){

        cout<<"Введите номер автомобиля: ";
        plate = isPlate();
        cin.clear();
        cin.ignore(32767, '\n');
        cout<<"Введите ФИО владельца: ";
        getline(cin, name);
        cout<<"Введите марку автомобиля: ";
        getline(cin, brand);

        cars.add_car( name, brand,plate);
    }

}

//М416ЕВ098
int main(){
    int size, choose1, choose2, i;
    string plate, own_name, brand;
    int *brands;
    cout<<"Введите предполагаемое количество автомобилей: ";
    size = isNumber();
    size*=2;
    Cars car_db(size);
    setup(car_db);
    car_db.print();
    while(true){
    cout<<"Меню: \n1.Добавить новый автомобиль в базу \n 2.Удалить автомобиль из базы \n "
          "3. Просмотреть все имеющиейся записи \n 4. Поиск автомобиля по номеру \n "
          "5. Поиск автомобилей по марке \n 6. Удалить базу данных \n 7.Задать новую базу данных \n 0. Завершить работу\n\n ";
    choose1 = isNumber();
    switch(choose1){
        case 1:
            cout<<"Введите номер автомобиля: ";
            plate=isPlate();
            cin.clear();
            cin.ignore(32767, '\n');
            cout<<"Введите ФИО владельца: ";
            getline(cin, own_name);
            cout<<"Введите марку автомобиля: ";
            getline(cin, brand);

            car_db.add_car( own_name, brand,plate);
            break;
        case 2:
            cout<< "Выберите способ удаления: \n 1.Удалить первую запись в базе \n 2.Удалить последнюю запись в базе \n 3.Удалить автомобиль по номеру \n\n ";
            choose2  = isNumber();
            switch (choose2) {
                case 1:
                    car_db.remove_first();
                    break;
                case 2:
                    car_db.remove_last();
                    break;
                case 3:
                    cout<<"Введите номер автомобиля, который хотите удалить: ";
                    plate = isPlate();
                    car_db.remove_by_plate(plate);
                    cin.clear();
                    cin.ignore(32767, '\n');
                    break;
                default:
                    cout<<"Введенные данные неверны"<<endl;
                    break;
            }
            break;
        case 3:
            car_db.print();
            break;
        case 4:
            cout<<"Введите номер автомобиля, который хотите найти: ";
            plate = isPlate();
            car_db.plate_search(plate);
            break;
        case 5:
            cout<<"Введите марку автомобилей, о которых хотите получить информацию: ";
            cin.clear();
            cin.ignore(32767, '\n');
            getline(cin, brand);
            brands = car_db.brand_search(brand);
            break;
        case 6:
            car_db.clear();
            break;
        case 0:
            cout<<"Вы действительно хотите завершить работу программы? (1/0)";
            choose2 = isNumber();
            if(choose2){
                return 0;
            }
            else{
                break;

            }
        case 7:
            cout<<"Введите предполагаемое количество автомобилей: ";
            size = isNumber();
            size*=2;
            car_db.set(size);
            setup(car_db);
            car_db.print();
            break;
        default:
            cout<<"Действие нераспознано!"<<endl;
            break;
    }
    }



}
