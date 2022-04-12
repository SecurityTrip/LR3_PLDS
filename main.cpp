# include <iostream>
#include <fstream>

using namespace std;
struct node;
class Tree;
void Reverse(node* root);

//Элемент дерева
struct node {
    int Key;
    node* Left;
    node* Right;
};

//Дерево
class Tree {
private:
    node* root; //Корень
public:
    Tree() { root = nullptr; }
    node** GetRoot() { return &root; }
    node* BalanceTree(int, node**, ifstream& fin);
    void file_print(node* root,ofstream& fout);
    void deleteTree(node** root);
};

//Рекурсивный метод создания сбалансированного дерева
node* Tree::BalanceTree(int n, node** p, ifstream& fin) {
    node* now;
    int x, nl, nr;

    now = *p;

    if (n == 0) *p = nullptr;
    else {
        nl = n / 2; nr = n - nl - 1;
        fin >> x;
        now = new(node);
        (*now).Key = x;
        BalanceTree(nl, &((*now).Left),fin);
        BalanceTree(nr, &((*now).Right),fin);
        *p = now;
    }
    return *p;
}

//Вывод в файл при помощи прямого прохода
void Tree::file_print(node* root, ofstream& fout)
{
    if (root)
    {
        file_print(root->Left, fout);
        file_print(root->Right, fout);
        fout <<root->Key << " ";
    }

}

//Удаление дерева
void Tree::deleteTree(node** root) {
    if (*root) {
        deleteTree(&((*root)->Left));
        deleteTree(&((*root)->Right));
        delete* root;
    }
}

//Отражение значений элементов дерева при помощи прямого прохода
void Reverse(node* root)
{
    if(root)
    {
        node *tmp;
        tmp->Right = root->Left;
        tmp->Left = root->Right;
        tmp->Key = root->Key;

        root = tmp;

        Reverse(root->Left);
        Reverse(root->Right);
    }
}

int main()
{
    Tree A;
    long long n = 0, x;

    ifstream fin("input.txt");
    while (fin >> x)++n;
    fin.close();

    ifstream in("input.txt");
    A.BalanceTree(n, A.GetRoot(), in);
    in.close();

    Reverse(*A.GetRoot());

    ofstream fout("output.txt");
    A.file_print(*A.GetRoot(),fout);
    A.file_print(*A.GetRoot(),fout);
    fout.close();

    A.deleteTree(A.GetRoot());

    return 0;
}

