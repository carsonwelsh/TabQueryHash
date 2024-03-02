#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;

uint64_t djb2(string str) { 
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class Person {
public:
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;

    string sortValue; 
    Person *next; 

    Person(string id, string first, string last, string email, string phone, string city, string state, string postalCode, Person *next = nullptr){
        this->id = id;
        this->first = first;
        this->last = last;
        this->email = email;
        this->phone = phone;
        this->city = city;
        this->state = state;
        this->postalCode = postalCode;
        this->sortValue = "Unknown";
        this->next = nullptr;
    }
};

class HashTable {
        Person *head;
        
        list<Person> *arr; 

    public:
        HashTable() {
            head = nullptr;
        }

        void hashSize (int size) {
            arr = new list<Person>[size];
        }

        int h(string key, int  tableSize) { 
            int hashKey = djb2(key) % tableSize;
            return (hashKey);
        }

        int h2(string key, int  tableSize) { 
            int hashKey2 = 43 - (djb2(key) % 43);
            return (hashKey2);
        }

        void addPerson(string id, string first, string last, string email, string phone, string city, string state, string postalCode) {
            Person *n = new Person(id, first, last, email, phone, city, state, postalCode);
            if (head == nullptr) {
                head = n;
                return;
            }
            Person *cur = head;
            while (cur->next != nullptr) {
                cur = cur->next;
            }
            cur->next = n;
            return;
        }

        void insert(string key, int tableSize) { 
            for (Person *cur = head; cur != nullptr; cur = cur->next) { 
                if (key == "Id") {
                    cur->sortValue = cur->id;
                } 
                else if (key == "FirstName") {
                    cur->sortValue = cur->first;
                } 
                else if (key == "LastName") {
                    cur->sortValue = cur->last;
                } 
                else if (key == "Email") {
                    cur->sortValue = cur->email;
                } 
                else if (key == "Phone") {
                    cur->sortValue = cur->phone;
                } 
                else if (key == "City") {
                    cur->sortValue = cur->city;
                } 
                else if (key == "State") {
                    cur->sortValue = cur->state;
                } 
                else {
                    cur->sortValue = cur->postalCode;
                }
                int index = h(cur->sortValue, tableSize); 
                if (arr[index].empty()) { 
                    arr[index].push_back(*cur); 
                } 
                else if (arr[index].front().sortValue == cur->sortValue) { 
                    arr[index].push_back(*cur); 
                } 
                else { 
                    for (int j = 0; j < tableSize; j++) {
                        int index2 = (h(cur->sortValue, tableSize) + j*h2(cur->sortValue, tableSize)) % tableSize; 
                        if (arr[index2].empty()) { 
                            arr[index2].push_back(*cur); 
                            break;
                        }
                        else if (arr[index2].front().sortValue == cur->sortValue) { 
                            arr[index2].push_back(*cur);
                            break; 
                        }
                    }
                }
            }
        }


        void print(int tableSize) { 
            for(int i = 0; i < tableSize; i++) {
                if(!(arr[i].empty())) { 
                    int index = i; 
                    string keyValue = arr[i].front().sortValue; 
                    int numPeople = arr[i].size();
                    cout << index << ": " << keyValue << " (" << numPeople << ")," << endl;
                }
            }    
        }
        

        void lookup(string val, int tableSize) {
            bool result = false;
            bool first = true;
            for (int j = 0; j < tableSize; j++) {
                int index = (h(val, tableSize) + j*h2(val, tableSize)) % tableSize; 
                if (arr[index].front().sortValue == val) {
                    result = true;
                    if (first) {
                        cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                    }
                    first = false;
                    int numPeople = arr[index].size();
                    for (int i = 0; i < numPeople; i++) {
                        Person &person = arr[index].front();
                        cout << person.id << "," << person.first << "," << person.last << "," << person.email << "," << person.phone << "," << person.city << "," << person.state << "," << person.postalCode << endl;
                        arr[index].pop_front();
                    }
                }
            }
            if (!result) {
                cout << "No results" << endl; 
            }
        }

        ~HashTable() { 
            delete[] arr;
        }

};

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}


int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }

    HashTable hash1; 
    hash1.hashSize(tableSize);
    
    string line, token;
    getline(file, line); 
    while (getline(file, line)) { 
        istringstream iss(line);
        while (getline(iss, token, '\t')) {
            string id = token;
            getline(iss, token, '\t');
            string first = token;
            getline(iss, token, '\t');
            string last = token;
            getline(iss, token, '\t');
            string email = token;
            getline(iss, token, '\t');
            string phone = token;
            getline(iss, token, '\t');
            string city = token;
            getline(iss, token, '\t');
            string state = token;
            getline(iss, token, '\t');
            string postalCode = token;
            hash1.addPerson(id, first, last, email, phone, city, state, postalCode);
        }
    }
    
    hash1.insert(key, tableSize);

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            hash1.print(tableSize);
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            // lookup code here
            hash1.lookup(val, tableSize);
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
