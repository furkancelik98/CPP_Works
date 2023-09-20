/*
Bu program, kullanıcıların temel kimlik doğrulama işlemlerini gerçekleştirebilen basit bir metin tabanlı kullanıcı yönetim sistemi içerir. Kullanıcılar, bu sistem aracılığıyla aşağıdaki işlemleri gerçekleştirebilir:

Giriş Yapma (Login): Kullanıcılar kayıtlı bir kullanıcı adı ve şifre ile sisteme giriş yapabilirler. Eğer kullanıcı adı ve şifre doğru ise, kullanıcı bilgileri ekrana yazdırılır ve oturum açılır.

Kullanıcı Kaydı (Sign-Up): Yeni kullanıcılar, kullanıcı adı, e-posta ve şifre girerek sisteme kayıt olabilirler. Bu bilgiler "Login_Data.txt" adlı bir metin dosyasında saklanır.

Şifre Unuttum (Forgot Password): Kullanıcılar kullanıcı adı ve kayıtlı e-posta adresini girdiklerinde, sistem bu bilgilere sahip bir kullanıcıyı bulmaya çalışır ve bu kullanıcının şifresini ekrana yazdırır.

Şifre Değiştirme (Change Password): Kullanıcılar kullanıcı adı ve kayıtlı e-posta adresini girdikten sonra, yeni bir şifre girmeleri istenir. Ardından, bu yeni şifre ilgili kullanıcının veritabanındaki şifresi ile değiştirilir.

Çıkış: Kullanıcılar programı çıkış seçeneği ile sonlandırabilirler.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class User {
    string username, email, password;
    string searchName, searchPass, searchEmail;
    fstream file;

public:
    void login();
    void signUP();
    void forgot();
    void changePassword();
};

int main() {
    User obj;
    char choice;
    
    cout << "1- Login"<< endl;
    cout << "2- Sign-Up"<< endl;
    cout << "3- Forgot Password"<< endl;
    cout << "4- Change Password"<< endl;
    cout << "5- Exit"<< endl;
    cin >> choice;

    switch (choice) {
    case '1':
        cin.ignore();
        obj.login();
        break;
    case '2':
        cin.ignore();
        obj.signUP();
        break;
    case '3':
        cin.ignore();
        obj.forgot();
        break;
    case '4':
        cin.ignore();
        obj.changePassword();
        break;
    case '5':
        return 0;
    default:
        cout << "ERROR";
    }
}

void User::signUP() {
    cout << "\nUser Name : ";
    getline(cin, username);
    cout << "Email Address : ";
    getline(cin, email);
    cout << "Your Password : ";
    getline(cin, password);

    file.open("Login_Data.txt", ios::out | ios::app);
    file << username << "*" << email << "*" << password << endl;
    file.close();
}

void User::login() {
    cout << "Login" << endl;
    cout << "User Name : " << endl;
    getline(cin, searchName);
    cout << "Password : " << endl;
    getline(cin, searchPass);

    file.open("Login_Data.txt", ios::in);
    getline(file, username, '*');
    getline(file, email, '*');
    getline(file, password, '\n');
    while (!file.eof()) {
        if (username == searchName) {
            if (password == searchPass) {
                cout << "\nAccount Login Successful.";
                cout << "\nUsername : " << username << endl;
                cout << "\nEmail : " << email << endl;
                file.close();
                return;
            } else {
                cout << "Wrong Password!";
                file.close();
                return;
            }
        }
        getline(file, username, '*');
        getline(file, email, '*');
        getline(file, password, '\n');
    }
    file.close();
    cout << "ERROR\n";
}

void User::forgot() {
    cout << "\nUser Name :: ";
    getline(cin, searchName);
    cout << "\nEmail Address : ";
    getline(cin, searchEmail);

    file.open("Login_Data.txt", ios::in);
    getline(file, username, '*');
    getline(file, email, '*');
    getline(file, password, '\n');
    while (!file.eof()) {
        if (username == searchName) {
            if (email == searchEmail) {
                cout << "\nAccount Found." << endl;
                cout << "Password : " << password << endl;
                file.close();
                return;
            } else {
                cout << "ERROR\n";
                file.close();
                return;
            }
        }
        getline(file, username, '*');
        getline(file, email, '*');
        getline(file, password, '\n');
    }
    file.close();
    cout << "Account not found...!\n";
}

void User::changePassword() {
    cout << "\nUser Name : ";
    getline(cin, searchName);
    cout << "\nEmail Address : ";
    getline(cin, searchEmail);

    file.open("Login_Data.txt", ios::in);
    getline(file, username, '*');
    getline(file, email, '*');
    getline(file, password, '\n');
    while (!file.eof()) {
        if (username == searchName) {
            if (email == searchEmail) {
                cout << "\nAccount Found" << endl;
                cout << "New Password : ";
                getline(cin, password);
                file.close();

                file.open("Login_Data.txt", ios::in);
                ofstream tempFile("temp.txt");
                while (getline(file, username, '*')) {
                    getline(file, email, '*');
                    getline(file, password, '\n');
                    if (username == searchName && email == searchEmail) {
                        tempFile << username << "*" << email << "*" << password << endl;
                    } else {
                        tempFile << username << "*" << email << "*" << password << endl;
                    }
                }
                file.close();
                tempFile.close();
                remove("Login_Data.txt");
                rename("temp.txt", "Login_Data.txt");

                cout << "Password Changed!" << endl;
                return;
            } else {
                cout << "ERROR\n";
            }
        } else {
            cout << "\nERROR\n";
        }
        getline(file, username, '*');
        getline(file, email, '*');
        getline(file, password, '\n');
    }
    file.close();
    cout << "ERROR\n";
}
