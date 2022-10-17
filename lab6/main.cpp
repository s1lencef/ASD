#include  <iostream>

using namespace std;

struct Tree{
    int value;
    Tree *right;
    Tree *left;
};
// функция проверки корректности ввода
int is_number(){
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
void add(Tree*&h, int n){

    if (h == nullptr){
        h = new Tree;
        h ->value = n;
        h->left = h->right = nullptr;
        cout<<"Число "<<n<<" добавлено в дерево!"<<endl;
    }
    else{
        if (h->value > n){
            add(h->left,n);
        }
        else if (h->value < n){
            add(h->right, n);
        }
        else{
            cout<<"Число "<<n<<" уже есть в дереве!"<<endl;
        }
    }

}
void del(Tree*&h){
    if (h->left){
        del(h->left);
    }
    if (h->right){
        del(h->right);
    }
    delete h;
}
void show_straight(Tree *h){

    if( h != nullptr){
        cout<<h->value<<" ";
        show_straight(h->left);
        show_straight(h->right);
    }
}

void show_symmetric(Tree *h){
    if( h != nullptr) {
        show_symmetric(h->left);
        cout << h->value << " ";
        show_straight(h->right);
    }
}
void show_reverse(Tree *h){
    if( h != nullptr) {
        show_reverse(h->left);
        show_reverse(h->right);
        cout << h->value << " ";
    }
}


int main(){
    int x, length, choise;
    bool flag;
    Tree *root;
    while(true){
    flag = true;
    root = nullptr;
    cout<<"Введите количество элементов в дереве: ";
    length = is_number();
    cout<<"Введите последовательность чисел: ";
    for (int i = 0; i<length;i++){
        x = is_number();
        add(root, x);
    }
    cout<<endl;
    while(flag){
        cout<<"Выберите действие:\n 1.Совершить прямой обход\n 2.Совершить симметричный обход\n 3.Совершить обратный обход\n "
              "4.Ввести новые данные\n 0.Завершить программу\n";
        choise = is_number();
        switch (choise) {
            case 1:
                cout<<"\nПрямой обход дерева"<<endl;
                show_straight(root);
                cout<<"\n\n";
                break;
            case 2:
                cout<<"\nСимметричный обход дерева"<<endl;
                show_symmetric(root);
                cout<<"\n\n";
                break;
            case 3:
                cout<<"\nОбратный обход дерева"<<endl;
                show_reverse(root);
                cout<<"\n\n";
                break;
            case 4:
                del(root);
                flag = false;
                break;
            case 0:
                cout<<"Program finished!"<<endl;
                del(root);
                return 0;
            default:
                break;

        }
    }
    }
}