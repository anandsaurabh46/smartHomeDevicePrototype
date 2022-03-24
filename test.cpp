#include <bits/stdc++.h>
using namespace std;

pair<int,int> userPublicKey, userPrivateKey, serverPublicKey, serverPrivateKey;
 
int modInverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;
    if(m == 1) return 0;
    while(a > 1) {
        int q = a / m;
        int t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if(x < 0) x += m0; 
    return x;
}
 
int power(int x, int y, int p) {
    int res = 1;    
    x = x % p; 
    if(x == 0) return 0; 
    while(y > 0) {
        if(y & 1) res = (res*x) % p;
        y = y/2; 
        x = (x*x) % p;
    }
    return res;
}
 
vector<int> encrypt(string &s, pair<int,int> &key) {
    vector<int> res;
    for(int i=0;i<s.size();i++) {
        res.push_back(power(s[i],key.first,key.second));
    }
    return res;
}
 
string decrypt(vector<int> &v, pair<int,int> &key) {
    string res;
    for(int i=0;i<v.size();i++) {
        res += (power(v[i],key.first,key.second));
    }
    return res;
}
 
string generateString() {
    string res;
    for(int i=0;i<6;i++) {
        int temp = rand()%26;
        res += 'a' + temp;
    }
    return res;
}
 
string sendToServer(vector<int> &v) {
    string res = decrypt(v,serverPrivateKey);
    return res;
}
 
bool userSideAuth() {
    string s = generateString();
    vector<int> v = encrypt(s,serverPublicKey);
    string res = sendToServer(v);
    if(res==s) return true;
    return false;
}
 
string sendToUser(vector<int> &v) {
    string res = decrypt(v,userPrivateKey);
    return res;
}
 
bool serverSideAuth() {
    string s = generateString();
    vector<int> v = encrypt(s,userPublicKey);
    string res = sendToUser(v);
    if(res==s) return true;
    return false;
}
 
void RSA() {
    int p = 17, q = 29; 
    int n = p*q;
    int z = (p-1)*(q-1);
    int e = z - 1;
    int d = modInverse(e, z);
    userPublicKey = make_pair(e,n), userPrivateKey = make_pair(d,n);
    p = 37, q = 59;
    n = p*q;
    z = (p-1)*(q-1);
    e = z - 1;
    d = modInverse(e, z);
    serverPublicKey = make_pair(e,n), serverPrivateKey = make_pair(d,n);
}
 
bool authenticate(string &user) {
    RSA();
    if(serverSideAuth() && userSideAuth()) return true;
    return false;
}

void call() {
    string name;
    cout << "Enter name of contact\n";
    cin >> name;

    cout << "calling " << name << '\n';
}

void play() {
    string name;
    cout << "Enter name of song\n";
    cin >> name;

    cout << "playing " << name << '\n';
}

void alarm() {
    string name;
    cout << "Enter time of alarm\n";
    cin >> name;

    cout << "set for time " << name << '\n';
}

void search() {
    string name;
    cout << "Enter keyword to search\n";
    cin >> name;

    cout << "searching " << name << '\n';
}

void turnOff() {
    cout << "Turned off\n";
}

bool connected = false;
string username;

int main() {
    bool exit = true;
    while(exit==false) {
        cout << "Enter your choice:\n";
        cout << "Press 1 for registering a new smart-home Device\n"; 
        cout << "Press 2 for quick actions\n"; 
        cout << "Press 3 to turn off the device\n";
        cout << "Press 4 to disconnect the device\n"; 
        cout << "Press anything else to exit\n";
        int t;
        cin >> t;
        switch(t) {
                case 1: 
                    {
                        if(connected==true) {
                            cout << "A device is already Connected, please disconnect first\n"; 
                            break;
                        }
                        cout << "Enter device username\n";
                        string user;
                        cin >> user;
                        if(authenticate(user)) {
                            connected = true;
                            user = username;
                        }
                        else {
                            cout << "Wrong Username, please try again";
                        }
                        break;
                    }
            case 2: 
                {
                    if(connected==false) {
                        cout << "No device connected\n";
                        break;
                    }
                    bool exit1 = false;
                    while(exit1==false) {
                        cout << "Enter your choice:\n";
                        cout << "Press A to call a contact\n"; 
                        cout << "Press B to play music\n"; 
                        cout << "Press C to set alarm\n";
                        cout << "Press D to search web\n"; 
                        cout << "Press anything else to exit\n";
                        char action;
                        cin >> action;
                        switch(action) {
                            case 'A': call(); break;
                            case 'B': play(); break;
                            case 'C': alarm(); break;
                            case 'D': search(); break;
                            default: exit1 = true;
                        }
                    }
                    break;
                }
            case 3:
                {
                    if(connected==false) {
                        cout << "No device connected\n";
                        break;
                    }
                    turnOff();
                    break;
                }
            case 4:
                {
                    if(connected==false) {
                        cout << "No device connected\n";
                        break;
                    }
                    connected = false;;
                    username = "";
                    cout << "Disconnected\n";
                    break;
                }
            default: exit = true;
        }
    }
}
