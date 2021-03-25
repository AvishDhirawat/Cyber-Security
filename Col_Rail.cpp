#include <iostream>
#include <regex>
#include <string>
#include <sstream>

using namespace std;

string getNumberLocation(string keyword, string kywrdNumListStr) {

    int kywrdNumList[keyword.length()];
    for (int i = 0; i < sizeof(kywrdNumList)/sizeof(kywrdNumList[0]); i++)
    {
        kywrdNumList[i] = kywrdNumListStr[i] - 48;
    }

    string numLoc = "";
    for (int i = 1; i < keyword.length() + 1; i++) {
        for (int j = 0; j < keyword.length(); j++) {
            if (kywrdNumList[j] == i){
                numLoc += to_string(j);
            }
        }
    }
    return numLoc;
}

string keywordNumAssign(string keyword){
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int kywrdNumList[keyword.length()];

    int init = 0;
    for (int i = 0; i < alpha.length(); i ++){
        for (int j = 0; j < keyword.length(); j++) {
            if (alpha[i] == keyword[j]){
                init++;
                kywrdNumList[j] = init;
            }
        }
    }

    string str = "";
    for (int i = 0; i < sizeof(kywrdNumList)/sizeof(kywrdNumList[0]); i++){
        str += to_string(kywrdNumList[i]);
    }
    return str;
}

void cipherEncryption(){
    string msg;
    cout << "Enter Plain Text: ";
    getline(cin, msg);

    string keyword;
    cout << "Enter Keyword: ";
    getline(cin, keyword);

    for (int i = 0; i < msg.length(); i++){
        msg[i] = toupper(msg[i]);
    }

    msg = regex_replace(msg,regex("\\s+"), "");

    for (int i = 0; i < keyword.length(); i++){
        keyword[i] = toupper(keyword[i]);
    }

    for (int i = 0; i < keyword.length(); i++){
        cout << keyword[i] << " ";
    }
    cout << endl;

    string kywrdNumListStr = keywordNumAssign(keyword);

    int kywrdNumList[keyword.length()];
    for (int i = 0; i < sizeof(kywrdNumList)/sizeof(kywrdNumList[0]); i++){
        kywrdNumList[i] = kywrdNumListStr[i] - 48;
    }
    for (int i: kywrdNumList){
        cout << i << " ";
    }

    int extraLetters = msg.length() % keyword.length();
    int dummyCharacters = keyword.length() - extraLetters;

    if (extraLetters != 0){
        for (int i = 0; i < dummyCharacters; i++) {
            msg += ".";
        }
    }

    int numOfRows = msg.length() / keyword.length();
    char arr[numOfRows][keyword.length()];

    int z = 0;
    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < keyword.length(); j++) {
            arr[i][j] = msg[z];
            z++;
        }
    }

    cout << endl;
    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < keyword.length(); j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    string cipherText = "";
    string numLoc = getNumberLocation(keyword, kywrdNumListStr);
    cout << numLoc << endl;
    cout << endl;

    for (int i = 0, k = 0; i < numOfRows; i++, k++) {
        int d;
        if (k == keyword.length()){
            break;
        } else {
            d = numLoc[k];
            d = d- '0';
        }
        for (int j = 0; j < numOfRows; j++) {
            cipherText += arr[j][d];
        }
    }

    cout << cipherText;

}

void cipherDecryption(){
    string msg;
    cout << "Enter Cipher Text: ";
    getline(cin, msg);

    string keyword;
    cout << "Enter Keyword: ";
    getline(cin, keyword);

    for (int i = 0; i < keyword.length(); i++){
        keyword[i] = toupper(keyword[i]);
    }

    string kywrdNumListStr = keywordNumAssign(keyword);
    int kywrdNumList[keyword.length()];
    for (int i = 0; i < sizeof(kywrdNumList)/sizeof(kywrdNumList[0]); i++)
    {
        kywrdNumList[i] = kywrdNumListStr[i] - 48;
    }

    int numOfRows = msg.length() / keyword.length();
    char arr[numOfRows][keyword.length()];
    string numLoc = getNumberLocation(keyword, kywrdNumListStr);

    for (int i = 0, k = 0; i < msg.length(); i++, k++) {
        int d;
        if (k == keyword.length()){
            k = 0;
        } else {
            d = numLoc[k];
            d = d- '0';
        }
        for (int j = 0; j < numOfRows; j++, i++) {
            arr[j][d] = msg[i];
        }
        i--;

    }

    cout << endl;

    string plainText = "";

    for (int i = 0; i < numOfRows; i++) {
        for (int j = 0; j < keyword.length(); j++) {
            plainText += arr[i][j];

        }
    }

    cout << "Plain Text: " << plainText << endl;


}

int main()
{
    cout << "Columnar Transposition Cipher" << endl;
    cout << "1. Encryption\n2. Decryption\nChoose(1,2): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1){
        cout << endl << "Encryption" << endl;
        cipherEncryption();
    } else if (choice == 2){
        cout << endl << "Decryption" << endl;
        cipherDecryption();
    } else {
        cout << endl << "Wrong Choice" << endl;
    }

    return 0;
}
