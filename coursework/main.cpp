#include <iostream>
#include <fstream>
#include <map>
#include <cmath>

using namespace std;

// функция для проверки корректности номера
bool check_plate(string &value) {
    setlocale(LC_ALL, "Russia");
    string correct_letters = "АВЕКМНОРСТУХ";
    string correct_numbers = "0123456789";
    int count = 0;
    int i = 0;
    if (value.size() != 12) {
        return false;
    }
    for (int j = 0; j < 12; j++) {

    }
    for (auto c: value) {
        // первый четвертый и пятый элементы номера должны быть буквами из определенного набора
        if (i == 1 || i == 6 || i == 8) {
            for (int k = 1; k < 24; k += 2) {
                if ((int) correct_letters[k] == (int) value[i]) {
                    count++;
                }
            }
        } else {
            // остальные элементы  - любые из 10 цифр
            for (int k = 0; k < 10; k++) {
                if ((int) correct_numbers[k] == (int) value[i]) {
                    count++;

                }
            }
        }
        i++;
    }
    if (count == 9) {
        return true;
    }
    return false;
}

string isPlate() {
    setlocale(LC_ALL, "Russia");
    string value;

    while (true) {
        cin >> value;
        if (check_plate(value)) {
            return value;

        } else {
            cout << "Введенный номер не соответствует стандарту \"ANNNAANNN\" Повторите попытку: ";
            cin.clear();
            cin.ignore(32767, '\n');
        }
    }
}

// проверка на то, является ли введный символ числом
int isNumber() {
    int n;
    while (true) {
        cin >> n;
        if (cin.fail()) {
            cout << "Введено неверное значение, повторите попытку: ";
            cin.clear();
            cin.ignore(32767, '\n');
        } else {
            return n;
        }
    }
}

bool found(string a, string b) {
    int count = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) {
            count++;
        }
    }
    if (a.size() > b.size()) {
        return false;
    } else {
        if (count == a.size()) {
            return true;
        } else {
            return found(a, b.erase(0, 1));
        }

    }
    cout << a.size() << "  " << count;
}

// класс для описания автомобиля
class Auto {
private:
    string plate;
    string owner_name;
    string brand;
    int key;
    bool free = true;

public:
    // инициализация объекта
    Auto() {
        this->plate = "";
        this->owner_name = "";
        this->brand = "";
        this->key = 0;
    }

    void set(string pl, string name, string br) {
        this->plate = pl;
        this->owner_name = name;
        this->brand = br;
        this->free = false;
    }

    // функция для рассчета ключа(зависит от размера таблицы)
    void set_key(int M) {
        int i = 5, numbers = 0;
        for (auto c: this->plate) {
            if ((int) c < 58 && (int) c > 47) {
                numbers += ((int) c - 48) * pow(10, i);
                i--;
            }
        }
        this->key = numbers % M;
    }

    // функция нужна для удаления элемента из таблицы, при котором каждый элемент просто "зануляется"
    void set_null() {
        this->plate = "";
        this->owner_name = "";
        this->brand = "";
        this->key = 0;
        this->free = true;
    }

    // функции для получения  информации об автомобиле
    int get_key() const {
        return this->key;
    }

    string get_plate() const {
        return this->plate;
    }

    string get_brand() const {
        return this->brand;
    }

    string get_owner() const {
        return this->owner_name;
    };

    void output() {
        cout << "Автомобиль: " << this->brand <<
             "\nРегистрационный номер: " << this->plate
             << "\nВладелец: " << this->owner_name << "\n\n";
    }

// проверка на то, является ли ячейка занятой
    bool is_free() const {
        return this->free;
    }

    void engaged() {
        this->free = false;
    }

// деструктор
    ~Auto() {
    }

};

// класс, описывающий таблицу
class Cars {
private:
    Auto *cars;
    int arr_size;
    int length = 0;
    bool deleted = false;
public:
    Cars(int arr_size) {
        this->arr_size = arr_size;
        this->cars = new Auto[arr_size];
    }

    void set(int new_size) {
        this->arr_size = new_size;
        this->cars = new Auto[new_size];
        this->deleted = false;
    }

// в некоторых случаях, при большом объеме коллизий, размер таблицы приходится увеличивать, для этого и нужна эта функция
    void resize_arr() {
        int new_size = this->arr_size * 2;
        Auto *new_cars = new Auto[this->arr_size];
        for (int i = 0; i < this->arr_size; i++) {
            new_cars[i] = this->cars[i];
        }
        this->cars = new Auto[new_size];
        this->arr_size = new_size;
        for (int i = 0; i < this->arr_size / 2; i++) {
            if (!new_cars[i].is_free()) {
                this->add_car(new_cars[i].get_owner(), new_cars[i].get_brand(), new_cars[i].get_plate());
            }
        }


    }

// доабвление нового автомобиля
    void add_car(string name, string brand, string plate) {
        Auto obj;
        int i = 0, key;
        obj.set(plate, name, brand);
        if (this->deleted) {
            cout << "Добавление невозжможно! База данных удалена!" << endl;
            return;
        } else {
            while (true) {
                obj.set_key(this->arr_size);
                key = obj.get_key();
                if (this->cars[key +
                               i].is_free()) { // перед записью в таблицу, надо проверить что ячейка пуста , иначе увеличим индекс на 1
                    this->cars[key + i].set(plate, name, brand);
                    this->cars[key + i].set_key(this->arr_size);
                    break;

                } else {
                    i++;
                    if (key + i >= this->arr_size) {
                        i = 0;
                        this->resize_arr();
                    }
                }
            }
            this->length++;
        }

    }

// поиск по номеру
    int plate_search(string num) {
        Auto obj;
        int key, i = 0;
        // создается объект - пустышка, который нуден просто для получения ключа
        obj.set(num, "", "");
        obj.set_key(this->arr_size);
        key = obj.get_key();

        while (true) {
            // пока ключ равен ключу элемента массива идет сравнение самих номеров, если номер не найден, значит такого элемента в массиве нет

            if (this->cars[key + i].get_key() == key) {

                if (this->cars[key + i].get_plate() == num) {
                    cout << "Автомобиль с указанным номером найден!\n\nИнформация об автомобиле:\n";
                    this->cars[key + i].output();
                    return key + i;
                } else {
                    i++;
                }
            } else {
                if( i <= this->arr_size){
                    i++;
                }
                else{
                    cout << "\nАвтомобиль отсутствует в базе!\n" << endl;
                    return -1;
                }

            }
        }
    }

// функция вывода все таблицы
    void print() {
        if (!this->deleted) {
            cout << "\nДанные обо всех автомобилях\n" << endl;
            for (int i = 0; i < this->arr_size; i++) {
                if (!this->cars[i].is_free()) {
                    this->cars[i].output();
                }
            }
        } else {
            cout << "База пуста!\n" << endl;
        }

    }

//удвление последнего элемента
    void remove_last() {
        int last_key;
        // получение последнего ключа пееребором
        for (int i = 0; i < this->arr_size; i++) {
            if (!this->cars[i].is_free()) {
                last_key = i;
            }
        }
        //удаление
        this->cars[last_key].set_null();
        cout << "Запись о последнем автомобиле в базе удалена!" << endl;
        this->length--;
        if (this->length == 0) {
            this->deleted = true;
        }
    }

// удаление первого элемента, логика аналогична последнему
    void remove_first() {
        for (int i = 0; i < this->arr_size; i++) {
            if (!this->cars[i].is_free()) {
                this->cars[i].set_null();
                break;
            }
        }
        cout << "Запись о последнем автомобиле в базе удалена!" << endl;
        this->length--;
        if (this->length == 0) {
            this->deleted = true;
        }
    }

// удаление элемента по номеру
    void remove_by_plate(string dplate) {
        int key = plate_search(dplate); // применяется поиск по номеру, чтобы получить индекс элемента
        int choise;
        if (key == -1) {
            cout << "Невозможно удалить данные об автомобиле, так как его нет в базе";
        } else {
            // еще раз удостоверимся в намерениях пользователя
            cout << "Вы точно хотите удалить этот автомобиль из базы? (1-да/0-нет)" << endl;
            choise = isNumber();
            if (choise == 1) {
                cout << "\nДанные об автомобиле " << this->cars[key].get_plate() << " удалены!" << endl;
                this->cars[key].set_null();
            } else {
                cout << "Удаление отменено." << endl;
            }
            this->length--;
            if (this->length == 0) {
                this->deleted = true;
            }
        }
    }

// поиск по марке
    int *brand_search(string br) {
        // индексы всех автомобилей введенной марки заприсываются в массив размер которого определяется размером самой таблицы
        int *brand_indexes = new int[this->arr_size];
        int k = 0;
        for (int i = 0; i < this->arr_size; i++) {
            brand_indexes[i] = -1;
        }
        for (int i = 0; i < this->arr_size; i++) {
            if (found(br, this->cars[i].get_brand())) {
                brand_indexes[k] = i;
                k++;
            }
        }
        k = 0;
        // вывод информации об автомобилях заданной марки
        if (brand_indexes[k] != -1) {
            cout << "Найдены автомобили:" << endl;
            br = "";
            while (brand_indexes[k] != -1) {
                if (br != this->cars[brand_indexes[k]].get_brand()) {
                    br = this->cars[brand_indexes[k]].get_brand();
                    cout << "Автомобили марки \"" << br << "\":" << endl;
                }
                this->cars[brand_indexes[k]].output();
                k++;
            }
        } else {
            cout << "Автомобилей такой марки нет в базе!" << endl;
        }
        return brand_indexes;
    }

// получение свойств класса
    Auto *get_cars() {
        return this->cars;
    }

    int get_size() const {
        return this->arr_size;
    }

// удаление всей таблицы
    void clear() {
        delete[] this->cars;
        this->deleted = true;
        cout << "Данные об автомобилях удалены" << endl;
    }

    //сохранение данных в текстовый файл
    void save() {
        string filename;
        ofstream outfile;
        while (true) {
            cout << "Введите полное имя файла для считывания:";
            cin >> filename;
            outfile.open(filename);
            if (outfile.fail()) {
                cerr << "Ошибка доступа к файлу" << endl;
                continue;
            } else {
                break;
            }

        }
        outfile << "Сведения об автомобилях: \n\n";
        for (int i = 0; i < this->arr_size; i++) {
            if (!this->cars[i].is_free()) {
                outfile << "Автомобиль: " << this->cars[i].get_brand() <<
                        "\nРегистрационный номер: " << this->cars[i].get_plate()
                        << "\nВладелец: " << this->cars[i].get_owner() << "\n\n";
            }

        }
        outfile << "\n\n";
        outfile.close();
        cout << "\nДанные записаны в файл!\n";
    }
};

// функция для записи даннных в таблицу
void setup(Cars &cars) {
    string name, brand, plate;
    const int count = cars.get_size();
    for (int j = 0; j < count / 2; j++) {
        cout << endl;
        cout << "Введите номер автомобиля: ";
        plate = isPlate();
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "Введите ФИО владельца: ";
        getline(cin, name);
        cout << "Введите марку автомобиля: ";
        getline(cin, brand);
        cars.add_car(name, brand, plate);


    }

}

//М416ЕВ098
int main() {
    int size, choose1, choose2, i;
    string plate, own_name, brand;
    int *brands;
    cout << "Введите предполагаемое количество автомобилей: ";
    size = isNumber();
    size *= 2;
    Cars car_db(size);
    setup(car_db);
    car_db.print();
    while (true) {
        cout << "Меню: \n1.Добавить новый автомобиль в базу \n 2.Удалить автомобиль из базы \n "
                "3. Просмотреть все имеющиейся записи \n 4. Поиск автомобиля по номеру \n "
                "5. Поиск автомобилей по марке \n 6. Удалить базу данных \n 7.Задать новую базу данных \n 8.Сохранить данные в текстовый файл \n 0. Завершить работу\n\n ";
        choose1 = isNumber();
        switch (choose1) {
            case 1:
                cout << "Введите номер автомобиля: ";
                plate = isPlate();
                cin.clear();
                cin.ignore(32767, '\n');
                cout << "Введите ФИО владельца: ";
                getline(cin, own_name);
                cout << "Введите марку автомобиля: ";
                getline(cin, brand);

                car_db.add_car(own_name, brand, plate);
                break;
            case 2:
                cout
                        << "Выберите способ удаления: \n 1.Удалить первую запись в базе \n 2.Удалить последнюю запись в базе \n 3.Удалить автомобиль по номеру \n\n ";
                choose2 = isNumber();
                switch (choose2) {
                    case 1:
                        car_db.remove_first();
                        break;
                    case 2:
                        car_db.remove_last();
                        break;
                    case 3:
                        cout << "Введите номер автомобиля, который хотите удалить: ";
                        plate = isPlate();
                        car_db.remove_by_plate(plate);
                        cin.clear();
                        cin.ignore(32767, '\n');
                        break;
                    default:
                        cout << "Введенные данные неверны" << endl;
                        break;
                }
                break;
            case 3:
                car_db.print();
                break;
            case 4:
                cout << "Введите номер автомобиля, который хотите найти: ";
                plate = isPlate();
                car_db.plate_search(plate);
                break;
            case 5:
                cout << "Введите марку автомобилей, о которых хотите получить информацию: ";
                cin.clear();
                cin.ignore(32767, '\n');
                getline(cin, brand);
                brands = car_db.brand_search(brand);
                break;
            case 6:
                car_db.clear();
                car_db;
                break;
            case 0:
                cout << "Вы действительно хотите завершить работу программы? (1/0)";
                choose2 = isNumber();
                if (choose2) {
                    return 0;
                } else {
                    break;

                }
            case 7:
                cout << "Введите предполагаемое количество автомобилей: ";
                size = isNumber();
                size *= 2;
                car_db.set(size);
                setup(car_db);
                car_db.print();
                break;
            case 8:
                car_db.save();
                break;
            default:
                cout << "Действие нераспознано!" << endl;
                break;
        }
    }


}
