#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "playfair.h"

int main()
{
    string key = "WakWaw!123";
    char playfair_table[10][10];
    buatplayfairtable(key, playfair_table);

    // Membaca teks terenkripsi dari file
    ifstream encrypted_file("encrypted_text.txt");
    string ciphertext;
    if (encrypted_file.is_open())
    {
        getline(encrypted_file, ciphertext);
        encrypted_file.close();
    }
    else
    {
        cerr << "Gagal membuka file terenkripsi." << endl;
        return 1;
    }

    string decrypted_text = dekripsi_playfair(ciphertext, playfair_table);
    cout << "Hasil Dekripsi: " << decrypted_text << endl;

    return 0;
}
void buatplayfairtable(string key, char playfair_table[10][10])
{

    string add_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;:,.<>?/`~©ÜüØ ";
    int row = 0, col = 0;

    // Memasukkan key ke dalam tabel Playfair
    for (char c : key)
    {
        playfair_table[row][col] = c;
        col++;
        if (col == 10)
        {
            col = 0;
            row++;
        }
    }

    // Memasukkan karakter tambahan ke dalam tabel Playfair
    for (char c : add_chars)
    {
        if (row == 10)
            break;
        if (key.find(c) == string::npos)
        {
            playfair_table[row][col] = c;
            col++;
            if (col == 10)
            {
                col = 0;
                row++;
            }
        }
    }
}
void cekposisi(char playfairtable[10][10], char c, int &row, int &col)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++) // Perbaikan: Perulangan harus untuk iterasi kolom (j), bukan i
        {
            if (playfairtable[i][j] == c)
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string dekripsi_playfair(string ciphertext, char playfairtable[10][10])
{
    string decrypted_text;
    size_t len = ciphertext.length();

    if (len % 2 != 0)
    {
        ciphertext.pop_back();
    }

    for (size_t i = 0; i < len; i += 2)
    {
        int row1, col1, row2, col2;
        cekposisi(playfairtable, ciphertext[i], row1, col1);
        cekposisi(playfairtable, ciphertext[i + 1], row2, col2);
        if (ciphertext[i] != ciphertext[i + 1])
        {
            // Jika huruf-huruf berada di baris yang sama, ganti dengan huruf di sebelah kiri
            if (row1 == row2)
            {
                decrypted_text.push_back(playfairtable[row1][(col1 + 9) % 10]);
                decrypted_text.push_back(playfairtable[row2][(col2 + 9) % 10]);
            }
            // Jika huruf-huruf berada di kolom yang sama, ganti dengan huruf di atasnya
            else if (col1 == col2)
            {
                decrypted_text.push_back(playfairtable[(row1 + 9) % 10][col1]);
                decrypted_text.push_back(playfairtable[(row2 + 9) % 10][col2]);
            }
            // Jika huruf-huruf membentuk persegi, ganti dengan huruf yang membentuk persegi lain di sampingnya
            else
            {
                decrypted_text.push_back(playfairtable[row1][col2]);
                decrypted_text.push_back(playfairtable[row2][col1]);
            }
        }
    }
    return decrypted_text;
}
