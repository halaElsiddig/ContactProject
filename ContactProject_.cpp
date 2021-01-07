/*Name:Hala Siddig
class:second year
Department:computer engineering
*/



#include <iostream>
#include <iterator>
#include <map>
#include <list>

using namespace std;
const string FIELDS_LIST[] = {"Name", "Given Name", "Additional Name", "Family Name", "Yomi Name", "Given Name Yomi",
                              "Additional Name Yomi", "Family Name Yomi", "Name Prefix", "Name Suffix", "Initials",
                              "Nickname", "Short Name", "Maiden Name", "Birthday", "Gender", "Location", "Notes",
                              "Billing Information", "Directory Server", "Mileage", "Occupation", "Hobby", "Phone",
                              "Priority", "Subject", "Language", "Photo", "Group Membership", "E-mail",
                              "Sensitivity", "Organization", "Website",};


class Contact {
    map<string, string> data;

public:
    Contact() { for (string field: FIELDS_LIST)data[field] = ""; }

    ~Contact() { data.clear(); }

    void setField(string field, string value) { data[field] = value; }

    string getField(string field) const {
        string value;
        try { value = data.at(field); }
        catch (...) { value = ""; }
        return value;
    }


    friend ostream &operator<<(ostream &os, const Contact &contact) {
        os << "Contact{";
        for (string field: FIELDS_LIST) {
            string value = contact.getField(field);
            if (value.empty()) continue;
            os << "\n\t" << field << ": " << value;
        }
        os << "\n}";
        return os;
    }
};


Contact read_contact();

bool edit_contact(list<struct Contact> &database);

bool mainMenu(list<struct Contact> &database);

bool show_contacts(list<struct Contact> &database);

Contact *getByIndex(int index, list<struct Contact> *pList);

bool delete_contact(list<struct Contact> &database);

int main() {
    list<Contact> database;
    bool mainloop = true;
    while (mainloop) {
        mainloop = mainMenu(database);
    }


    return 0;
}

bool edit_contact(list<struct Contact> &database) {
    int index = show_contacts(database) - 1;
    Contact *c = getByIndex(index, &database);
    cout << "Read Contact:\n";
    string input;
    for (string field: FIELDS_LIST) {
        cout << "\t" << field << "(" << c->getField(field) << ")" << ": ";
        getline(cin, input);
        if (input.empty()) continue;
        c->setField(field, input);
    }
    return true;
}

Contact *getByIndex(int index, list<struct Contact> *pList) {
    auto current = pList->begin();
    for (int i = 0; i < index; i++) {
        current++;
    }
    return &(*current);
}

bool read_contact(list<struct Contact> &database) {
    cout << "Read Contact:\n";
    Contact contact = Contact();
    string input;
    for (string field: FIELDS_LIST) {
        cout << "\t" << field << ": ";
        getline(cin, input);
        contact.setField(field, input);
    }
    database.push_back(contact);
    return true;
}

bool mainMenu(list<struct Contact> &database) {
    string inputChar;
    cout << "0- Exit" << endl;
    cout << "1- Show Contacts" << endl;
    cout << "2- Add New Contact" << endl;
    cout << "3- Update Contacts" << endl;
    cout << "4- Delete Contact" << endl;
    getline(cin, inputChar);
    switch (inputChar[0]) {
        case '0': return false;
        case '1': return show_contacts(database);
        case '2': return read_contact(database);
        case '3': return edit_contact(database);
        case '4': return delete_contact(database);

    }
}

bool delete_contact(list<struct Contact> &database) {
    int index = show_contacts(database) - 1;
    Contact *c = getByIndex(index, &database);
    auto eraseRange = database.insert(database.end(), *c);
    database.erase(eraseRange);
    return true;
}

bool show_contacts(list<struct Contact> &database) {

    int index = 1;
    for (Contact c: database)
        cout << index++ << "-" << c << endl;
    string inputChar;
    return  inputChar[0]+1;
}
