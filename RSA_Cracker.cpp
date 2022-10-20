#include <iostream>
#include <string>
#include <math.h>
#include <map>

using namespace std;

bool Is_Prime(int number) {
    if (number > 1) {
        for (int i = 2; i < number; i++)
            if (number % i == 0) return false;
    }
    return true;
};

bool Get_Primes(int n, int &p, int &q) {
    bool is_valid = false;
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            if (Is_Prime(i)) {
                int maybe_q = n / i;
                if (Is_Prime(maybe_q)) {
                    p = i;
                    q = maybe_q;
                    is_valid = true;
                    return is_valid;
                }
            }
        }
    }
    cout << "Public key is not valid!" << endl;
    return is_valid;
};

int Char_Decrypt(int c, int base, int d, int n) {
    // cout << c << "(" << base << ")^" << d << " (mod " << n << ")\n";
    if (d <= 1) return (c * base) % n;
    else if (d % 2 == 0) {
        double base_sq = pow(static_cast<double>(base), 2.0);
        base = static_cast<int>(base_sq) % n;
        return Char_Decrypt(c, base, d/2, n);
    }
    else {
        double base_sq = pow(static_cast<double>(base), 2.0);
        c *= base;
        c %= n;
        base = static_cast<int>(base_sq) % n;
        d -= 1;
        return Char_Decrypt(c, base, d/2, n);
    }
}

char Decrypted_Char(int decrypted_int) {
    map<int, char> char_vals;
    char_vals.insert(pair<int, char>(5, 'A'));
    char_vals.insert(pair<int, char>(6, 'B'));
    char_vals.insert(pair<int, char>(7, 'C'));
    char_vals.insert(pair<int, char>(8, 'D'));
    char_vals.insert(pair<int, char>(9, 'E'));
    char_vals.insert(pair<int, char>(10, 'F'));
    char_vals.insert(pair<int, char>(11, 'G'));
    char_vals.insert(pair<int, char>(12, 'H'));
    char_vals.insert(pair<int, char>(13, 'I'));
    char_vals.insert(pair<int, char>(14, 'J'));
    char_vals.insert(pair<int, char>(15, 'K'));
    char_vals.insert(pair<int, char>(16, 'L'));
    char_vals.insert(pair<int, char>(17, 'M'));
    char_vals.insert(pair<int, char>(18, 'N'));
    char_vals.insert(pair<int, char>(19, 'O'));
    char_vals.insert(pair<int, char>(20, 'P'));
    char_vals.insert(pair<int, char>(21, 'Q'));
    char_vals.insert(pair<int, char>(22, 'R'));
    char_vals.insert(pair<int, char>(23, 'S'));
    char_vals.insert(pair<int, char>(24, 'T'));
    char_vals.insert(pair<int, char>(25, 'U'));
    char_vals.insert(pair<int, char>(26, 'V'));
    char_vals.insert(pair<int, char>(27, 'W'));
    char_vals.insert(pair<int, char>(28, 'X'));
    char_vals.insert(pair<int, char>(29, 'Y'));
    char_vals.insert(pair<int, char>(30, 'Z'));
    char_vals.insert(pair<int, char>(31, ' '));
    char_vals.insert(pair<int, char>(32, '\"'));
    char_vals.insert(pair<int, char>(33, ','));
    char_vals.insert(pair<int, char>(34, '.'));
    char_vals.insert(pair<int, char>(35, '\''));

    return char_vals[decrypted_int];
}

bool RSA_Decrypt(int e, int n, int m) {
    int p, q, phi_n, d;

    // Step 1: Find primes p & q s.t. n = pq
    bool public_validity = Get_Primes(n, p, q);
    if (!public_validity) return false;

    // Step 2: Use p&q to get phi(n)
    phi_n = (p-1) * (q-1);

    // Step 3: Solve for d
    d = 0;
    for (int i = 1; d == 0; i += phi_n)
        if (i % e == 0) d = i / e;
    
    // Printing Values
    cout << "p: " << p << endl;
    cout << "q: " << q << endl;
    cout << "phi(n): " << phi_n << endl;
    cout << "d: " << d << endl;

    // Take in encrypted message
    cout << endl << "Please input your encypted message" << endl;
    int secret_message[m];
    for (int i = 0; i < m; i++)
        cin >> secret_message[i];

    // Decrypt each char
    cout << endl << "Decrypting" << endl;
    int decrypted_message[m];
    for (int i = 0; i < m; i++)
        decrypted_message[i] = Char_Decrypt(1, secret_message[i], d, n);

    // Printing Decrypted ints
    cout << endl;
    for (int i = 0; i < m; i++)
        cout << decrypted_message[i] << " ";
    cout << endl;

    // Decyphering
    char decrypted_str[m];
    for (int i = 0; i < m; i++)
        decrypted_str[i] = Decrypted_Char(decrypted_message[i]);

    // Printing Decyphered Msg
    cout << endl;
    for (int i = 0; i < m; i++)
        cout << decrypted_str[i];

    return true;
};

int main() {
    int e, n, m;
    cout << "Enter e of public key (e,n)" << endl;
    cin >> e;
    cout << "Enter n of public key (e,n)" << endl;
    cin >> n;
    cout << "Enter length of message" << endl;
    cin >> m;    

    RSA_Decrypt(e,n,m);
    return 0;
};

/* Example Message and values */

// Private Key: (7, 7387)
// Message Length: 181

// Encrypted Message:
// 1695 6617 6875 1316 5930 3339 5389 5930 1316 4858 3580 5930 4255 4372 4372 417 6627 5930 3339 2020 5930 2020 1316 4372 4255 3339 265 4858 1316 5930 4255 246 6631 5930 1316 4858 3580 5930 2801 417 3339 246 1316 5930 3339 2020 5930 2020 6650 3339 3586 5452 3369 5930 3339 1316 5930 3586 4255 246 5930 2801 3339 3580 4372 3586 3580 5930 1316 4858 4372  417 6875  265 4858 5930 6631 6875 2020 1316 5930  246 417 5930 5597 4255 1316 1316 3580 4372 5930 4858  417 6627 5930 1316 4858 3339 3586 5452 7264 5930 2020 417 5930 3339 4275 6650 6650 5930 5597 4255 5452 3580 5930 5597 5067 5930 2020 1316 4255  246 6631 5930 4255  246 6631 5930 4372 3580 5597 4255 3339  246 5930 4255 2020 5930 3339 5930 4255 5597 5930 4255  246 6631 5930 6617 3339 6631 5930 5389 4255 4372 3580 6627 3580 6650 6650 5930 4255  246 6631 5930  246 417 1316 5930  265 3339 6333 3580 5930 4255 5930 6631 4255 5597  246 7264 1695