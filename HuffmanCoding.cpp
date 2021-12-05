#include <iostream>
#include <string.h>
using namespace std;

class node
{
    int frequency;
    node *left;
    node *right;
    string data;
    int code;
    string char_code;

public:
    node(string data = "", int frequency = 0)
    {
        left = NULL;
        right = NULL;
        this->data = data;
        this->frequency = frequency;
        code = 7;
        char_code = "";
    }

    void node_create(string data = "", int frequency = 0)
    {
        left = NULL;
        right = NULL;
        this->data = data;
        this->frequency = frequency;
        code = 7;
        char_code = "";
    }
    void assign_Left(node *lchild)
    {
        left = lchild;
    }

    int get_frequency()
    {
        return frequency ;
    }

    friend class MinHeap;
    friend class HuffmanTree;
};

struct Table
{
    string data = "";
    string char_code = "";
};

class MinHeap
{
    node *Heap;
    int size;

public:
    void Insert(node *);
    node *Delete();

    MinHeap(int n)
    {
        Heap = new node[n];
        size = 0;
    }
    int get_size()
    {
        return size;
    }
};

class HuffmanTree
{

public:
    node *root;
    HuffmanTree()
    {
        root = NULL;
    }
    void Assign_root(node *p)
    {
        root = p;
    }

    node *InsertHuffman(node *, node *);
    void AssignCode(node *);
    void CharCodes(node *, string, Table *);
    void Encode(string, Table *, int);
    void Decode(string, Table *, int);
    
};

node *HuffmanTree ::InsertHuffman(node *a, node *b)
{
    node *t = new node;
    t->frequency = a->frequency + b->frequency;
    t->data = "";
    t->left = a;
    t->right = b;

    return t;
}

void HuffmanTree ::AssignCode(node *root)
{
    if (root->left)
    {
        root->left->code = 0;
        AssignCode(root->left);
    }
    if (root->right)
    {
        root->right->code = 1;
        AssignCode(root->right);
    }
}

void HuffmanTree ::CharCodes(node *root, string a, Table *t)
{
    static int j = 0;

    if (root == NULL)
        return;

    if (root->code == 1)
        a += "1";
    else if (root->code == 0)
        a += "0";

    if (root->left == NULL && root->right == NULL)
    {
        t[j].data = root->data;
        root->char_code = a;
        t[j].char_code = root->char_code;
        j++;
    }
    else
    {
        CharCodes(root->left, a, t);
        CharCodes(root->right, a, t);
    }
}

void HuffmanTree ::Encode(string s, Table *t, int size)
{
    int i = 0;
    string encoded_string = "";
    while (s[i] != '\0')
    {
        for (int j = 0; j < size; j++)
        {
            if (t[j].data[0] == s[i])
            {
                encoded_string += t[j].char_code;
            }
        }
        i++;
    }
    cout << encoded_string << endl;
}

void HuffmanTree ::Decode(string s, Table *t, int size)
{
    string decodedString = "";
    string x = "";
    int i = 0;
    while (s[i] != '\0')
    {

        if (s[i] == '0')
            x += "0";
        else
            x += "1";

        for (int j = 0; j < size; j++)
        {
            if (x == t[j].char_code)
            {
                decodedString += t[j].data;
                x = "";
            }
        }
        i++;
    }
    cout << decodedString << endl;
}
void MinHeap::Insert(node *n)
{
    size++;
    Heap[size] = *n;
    int index = size;

    while (index > 1)
    {
        if (Heap[index].frequency < Heap[index / 2].frequency)
        {
            node temp = Heap[index];
            Heap[index] = Heap[index / 2];
            Heap[index / 2] = temp;
            index = index / 2;
        }
        else
        {
            break;
        }
    }
}

node *MinHeap::Delete()
{
    node *x = new node;
    *x = Heap[1];
    Heap[1] = Heap[size];
    size--;
    int i = 1;

    while (2 * i <= size)
    {
        int index;
        if (2 * i == size)
        {
            index = 2 * i;
        }
        else if (Heap[2 * i].frequency < Heap[2 * i + 1].frequency)
        {
            index = 2 * i;
        }
        else
        {
            index = 2 * i + 1;
        }
        if (Heap[index].frequency < Heap[i].frequency)
        {
            node temp = Heap[index];
            Heap[index] = Heap[i];
            Heap[i] = temp;
            i = index;
        }
        else
        {
            break;
        }
    }
    return x;
}

int main()
{
    int n;
    cout << "Enter number of characters.\n";
    cin >> n;
    Table t[n];

    node *p = new node[n];

    MinHeap hp(n + 1);

    HuffmanTree ht;

    for (int i = 0; i < n; i++)
    {
        string x;
        int frequency;
        cout << "Enter Character. ";
        cin >> x;
        t[i].data = x;
        cout << "Enter Frequency. ";
        cin >> frequency;

        p[i].node_create(x, frequency);
        hp.Insert(&p[i]);
    }
    if (n == 1)
    {
        node *z = hp.Delete();
        node *q = new node("",z->get_frequency());
        q->assign_Left(z);
        hp.Insert(q);
    }
    else
    {
        do
        {
            node *z = hp.Delete();
            node *q = hp.Delete();

            node *r = ht.InsertHuffman(z, q);
            

            hp.Insert(r);

        } while (hp.get_size() != 1);
    }

    ht.root = hp.Delete();

    ht.AssignCode(ht.root);

    string a = "";
    ht.CharCodes(ht.root, a, t);

    cout << "\nCharacter   "
         << "Huffman Code" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "    " << t[i].data << "\t\t  " << t[i].char_code;
        cout << endl;
    }

    cout << "\nCodes are ready.\n\n";
    string b;
    cout << "Enter String to be Encoded.\n";
    cin >> b;
    if(b.length() != ht.root->get_frequency())
    {
        cout << "Wrong string entered. Run again.\n\n" ;
    }
    else
    {
        ht.Encode(b, t, n);
        cout << endl ;
    }

    string c;
    cout << "Enter String to be Decoded.\n";
    cin >> c;
    ht.Decode(c, t, n);
    cout << endl ;
}
