#include <iostream>
#include <regex>

using namespace std;

void cipherEncryption()
{
    string message;
    cout << "Enter message: ";
    getline(cin , message);
    cin.ignore();

    message = regex_replace(message, regex("\\s+"), "");

    cout << "Enter key(number of rails): ";
    int rails;
    cin >> rails;
    cin.ignore();

    char railMatrix[rails][message.length()];
    for (int i = 0; i < rails; i++){
        for (int j = 0; j < message.length(); j++){
            railMatrix[i][j] = '.';
        }
    }

    int row = 0;
    int check = 0;
    for (int i = 0; i < message.length(); i++){
        if (check == 0){
            railMatrix[row][i] = message[i];
            row++;
            if(row == rails){
                check = 1;
                row--;
            }
        } else if (check == 1){
            row--;
            railMatrix[row][i] = message[i];
            if (row == 0){
                check = 0;
                row = 1;
            }
        }
    }

    string encrypText = "";
    for (int i = 0; i < rails; i++){
        for (int j = 0; j < message.length(); j++){

            encrypText += railMatrix[i][j];
        }

    }

    encrypText = regex_replace(encrypText, regex("\\."), "");
    cout << "Encrypted Text: " << encrypText;
}

void ciphetDecryption(){
    string message;
    cout << "Enter message: ";
    getline(cin , message);
    cin.ignore();

    message = regex_replace(message, regex("\\s+"), "");

    cout << "Enter key(number of rails): ";
    int rails;
    cin >> rails;
    cin.ignore();

    char railMatrix[rails][message.length()];
    for (int i = 0; i < rails; i++){
        for (int j = 0; j < message.length(); j++){
            railMatrix[i][j] = '.';
        }
    }

    int row = 0;
    int check = 0;
    for (int i = 0; i < message.length(); i++){
        if (check == 0){
            railMatrix[row][i] = message[i];
            row++;
            if(row == rails){
                check = 1;
                row--;
            }
        } else if (check == 1){
            row--;
            railMatrix[row][i] = message[i];
            if (row == 0){
                check = 0;
                row = 1;
            }
        }
    }

    int ordr = 0;
    for (int i = 0; i < rails; i++){
        for (int j = 0; j < message.length(); j++){
            string temp = "";
            temp += railMatrix[i][j];
            if(regex_match(temp, regex("\\."))){
                // skipping '.'
                continue;
            } else {
                // adding cipher letters one by one diagonally
                railMatrix[i][j] = message[ordr];
                ordr++;
            }
        }
    }

    string decrypText = "";
    check = 0;
    row = 0;
    for (int i = 0; i < message.length(); i++){
        if (check == 0){
            decrypText += railMatrix[row][i];
            row++;
            if (row == rails){
                check = 1;
                row--;
            }
        } else if (check == 1){
            row--;
            decrypText += railMatrix[row][i];
            if (row == 0){
                check = 0;
                row = 1;
            }
        }
    }

    decrypText = regex_replace(decrypText, regex("\\.+"), "");
    cout << "Decrypted Text: " << decrypText;
}

int main()
{
    cout << "1. Encryption\n2. Decryption\nChoose(1,2): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1){
        cout << endl << "Encryption" << endl;
        cipherEncryption();

    } else if (choice == 2) {
        cout << endl << "Decryption" << endl;
        ciphetDecryption();

    } else {
        cout << endl << "Invalid Choice" << endl;
    }

    return 0;
}
