#include "playfair.h"

/*File ini adalah untuk proses yang ada di enkripsi dan dekripsi*/

/*Menjadikan hasil yang unik karakter saja */
string unik(string key)
{
    string karakter;
    string addchar = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;:,.<>?/` '~✓®×¢€§×";

    for (char c : key) 
    {
        if (karakter.find(c) == string::npos) // Jika karakter tambahan belum ada di key, masukkan ke dalam tabel
        {
            karakter += c;
        }
    }
    for (char c : addchar)
    {
        if (karakter.find(c) == string::npos)
        {
            karakter += c;
        }
    }

    return karakter;
}


// Membuat tabel sekaligus menginputkan karakter
address createTable(int size_board, string karakter){
    address Head = NULL;
    address rowStart = NULL;
    address upNode = NULL;
    address temp_last = NULL;

    // string add_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;:,.<>?/` '~✓®×¢€§×";
    int index = 0;  // Index to iterate over add_chars

    for(int i = 1; i <= size_board; i++) {
        for(int j = 1; j <= size_board; j++) {
            address newNode = (address) malloc(sizeof(node));
            if (newNode == NULL) {
                printf("Memory Full\n");
                return NULL; // Exiting if memory allocation fails
            }
            else {
                if(index < karakter.length()){
                newNode->text = karakter[index];  // Use modulo to cycle through add_chars if necessary
                index++;

                newNode->right = NULL;
                newNode->left = NULL;
                newNode->top   = NULL;
                newNode->down = NULL;
                }
                
            }

            if (Head == NULL) {
                Head = newNode;
            }
            if (rowStart == NULL) {
                rowStart = newNode;
            }
            else {
                newNode->left = temp_last;
                temp_last->right = newNode;
            }

            if (upNode != NULL) {
                upNode->down = newNode;
                newNode->top = upNode;
                upNode = upNode->right;
            }
            temp_last = newNode;
        }

        upNode = rowStart;
        rowStart = NULL;
    }

    return Head;
}


//traversal dan mencari tahu posisi node 
address searchingNode(address Head, infotype nilai){
    address rowStart = NULL;
    address node = Head;
    address result = NULL;

    // loop down
    while(node != NULL){
        // loop right
        while(node != NULL){
            if (node -> text == nilai){
                result = node;
                return result;
            }
            
            if (rowStart == NULL){
                rowStart = node;
            }
            node = node -> right;
        }
        node = rowStart -> down;
        rowStart = NULL;
    }
    return result;
}

bool cek_vertikal(address c1, address c2)
{
    address temp;
    bool first;
    temp = c1;
    first = true;
    while (temp != NULL)
    {
        while (temp != NULL)
        {
            if (temp == c2 && first)
            {
                return true;
            }
            else if (temp == c1 && !first)
            {
                return true;
            }
            else
            {
                temp = temp->down;
            }
        }
        if (first == true)
        {
            cout << endl;
            temp = c2;
            first = false;
        }
        else
        {
            return false;
        }
    }
}

bool cek_horizontal(address c1, address c2)
{
    address temp;
    bool first;
    temp = c1;
    first = true;
    while (temp != NULL)
    {
        while (temp != NULL)
        {
            if (temp == c2 && first)
            {
                return true;
            }
            else if (temp == c1 && !first)
            {
                return true;
            }
            else
            {
                cout << temp->text;
                temp = temp->right;
            }
        }
        if (first == true)
        {
            temp = c2;
            first = false;
        }
        else
        {
            return false;
        }
    }
}

/*Kalau yang di ambil tengah nya waktu dekripsi juga sama aja ya kan?*/
char kotak(address c1, address c2)
{
    address temp1, temp2;
    temp1 = c1;
    temp2 = c2;

    while (temp1 != NULL)
    {
        if (temp1->text == c2->text)
        {
            return temp1->text;
        }
        temp1 = temp1->right;
    }

    while (temp2 != NULL)
    {
        if (temp2->text == c1->text)
        {
            return temp2->text;
        }
        temp2 = temp2->down;
    }
    return '\0';
}

    /*Keperluan debugging*/
void display_table(address Head, int size_board)
{
    address current = Head;

    for (int i = 1; i <= size_board; i++)
    {
        for (int j = 1; j <= size_board; j++)
        {
            cout << current->text << " | ";
            current = current->right;
        }
        cout << "\n";
        current = Head;
        for (int k = 0; k < i; k++)
        {
            current = current->down;
        }
    }
}

int main()
{
    int size = 10; // var x var
    string pass = "Wakwaw1123 olo";
    string hasil;
    address head;
    hasil = unik(pass);
    head = createTable(size, hasil);

    display_table(head, size);
}