#include <iostream>
#include <string>
#include "linkedlist.h"

using namespace std;
int getInputValues (string line, string &command, string &value);

/*
 Destructor that cleans up all the nodes in the linked list
 */
linkedlist :: ~linkedlist () {
    linkedlist::clear();
}

/*
 Adds a node to the front of the queue
 */
std::string linkedlist::enqueue_front(int i) {
    Node *current = new Node;
    current -> data = i;
    if (list_head == nullptr) {
        current -> next = list_head;
        list_head = current;
        list_tail = current;
    } else {
        current -> next = list_head;
        list_head -> prev = current;
        list_head = current;
    }
    list_size += 1;
    return "success";
};

/*
 Adds a node to the back of the queue
 */
std::string linkedlist::enqueue_back(int i) {
    Node *current = new Node;
    current -> data = i;
    if (list_tail == nullptr) {
        list_tail = current;
        list_head = current;
    } else{
        current -> prev = list_tail;
        list_tail -> next = current;
        list_tail = current;
    }
    list_size += 1;
    return "success";
};

/*
 Removes a node from the front of the queue
 Throws an exception if the list is already empty
 */
std::string linkedlist::dequeue_front() {
    if (list_head == nullptr) {
        throw deque_empty();
    }
    if (list_size == 1 || list_head == list_tail) {
        delete list_head;
        list_head = nullptr;
        list_tail = nullptr;
    } else {
        Node *temp {nullptr};
        temp = list_head->next;
        delete list_head;
        list_head = temp;
        list_head -> prev = nullptr;
    }
    list_size -= 1;
    return "success";
}
 
/*
Removes a node from the back of the queue
Throws an exception if the list is already empty
*/
std::string linkedlist::dequeue_back() {
    if (list_tail == nullptr || list_head == nullptr) {
        throw deque_empty();
    }
    // if its the last entry, set both pointers to null
    if (list_tail == list_head) {
        delete list_head;
        list_head = nullptr;
        list_tail = nullptr;
    } else {
        Node *temp = list_tail -> prev;
        delete list_tail;
        list_tail = temp;
        list_tail -> next = nullptr;
    }
    list_size -= 1;
    return "success";
}

/*
 Removes all nodes in the linked list
 */
std::string linkedlist::clear() {
    Node *temp {nullptr};
    
    if (list_size == 1){
        delete list_head;
        list_head = nullptr;
        list_tail = nullptr;
    } else {
        while (list_head != nullptr) {
            temp = list_head -> next;
            delete list_head;
            list_head = temp;
        }
        list_tail = nullptr;
    }
    temp = nullptr;
    list_size = 0;
    return "success";
}

/*
 Checks if the front of the list is equal to a given value
 Throws an exception if it is not equal
 */
std::string linkedlist::front(int i) {
    if (list_head != nullptr && list_head -> data == i) {
        return "success";
    }
    throw deque_empty();
}

/*
Checks if the back of the list is equal to a given value
Throws an exception if it is not equal
*/
std::string linkedlist::back(int i) {
    if (list_tail != nullptr && list_tail -> data == i) {
        return "success";
    }
    throw deque_empty();
}

/*
 Checks if the linked list is empty
 Throws an exception if it is not empty
*/
std::string linkedlist::empty(){
    if (list_size != 0) {
        throw deque_empty();
    }
    return "success";
}

/*
 returns the size of the list
 */
int linkedlist::size() {
    return list_size;
}

/*
 print out the linekd list from the front and back
 */
void linkedlist::print(){
    Node *temp {nullptr};
    temp = list_head;
        // store the size of the array in the first entry
    int i {0};
    if (list_head != nullptr && list_tail != nullptr) {
        while(temp != nullptr) {
            cout << temp -> data;
            if (i != list_size - 1) {
                cout << " ";
            }
            temp = temp -> next;
            i++;
        }
        cout << endl;
        // Print backwards
        temp = list_tail;
        i = 0;

        while (temp != nullptr) {
            cout << temp -> data;
            if (i != list_size - 1) {
                cout << " ";
            }
            temp = temp -> prev;
            i++;
        }
        cout << endl;
    }
    delete temp;
}


int main() {
    string line{};
    linkedlist queue;

    while(getline(cin, line)){
        string command{""};
        string value{""};
        string message{""};
        int data {0};
        getInputValues(line, command, value);
        int valueLength = value.length();

        // only convert value to integer if it exists
        if (value != "") {
            // If the value is not of type int, throw an error
            try {
                data = stoi(value);
            } catch(...){
                valueLength = 0;
                message = "";
            }
        }
        
        // Call the appropriate member function for the given command
        try {
            if (command == "enqueue_front") {
                message = valueLength == 0? "" : queue.enqueue_front(data);
            } else if (command == "enqueue_back") {
                message = message = valueLength == 0 ? "" : queue.enqueue_back(data);
            } else if (command == "dequeue_front") {
                message = queue.dequeue_front();
            } else if (command == "dequeue_back") {
                message = queue.dequeue_back();
            } else if (command == "clear") {
                message = queue.clear();
            } else if (command == "front") {
                if (valueLength == 0){
                    throw deque_empty();
                }
                message = queue.front(data);
            } else if (command == "back") {
                if (valueLength == 0){
                    throw deque_empty();
                }
                message = queue.back(data);
            } else if (command == "empty") {
                message = queue.empty();
            } else if (command == "size") {
                int r_size = queue.size();
                message = "size is " + to_string(r_size);
            } else if (command == "print") {
                queue.print();
            }
            } catch (deque_empty msg) {
            cout << "failure" << endl;
        }
        if (message != "" && command != "") {
            cout << message << endl;
        }
    }
    return 0;
}

/*
 Parses the input value and splits it into command and value
 */
int getInputValues (string line, string &command, string &value){
    int i = 0;
    string temp{};
    int lineLength = line.length();
     // Checking each character until it hits the first white space
     // Getting the command
    while (line[i] != ' ' && i < lineLength){
        temp += line[i];
        command = temp;
        i++;
    }
    // Get values only if it exists
    if (i < lineLength) {
        temp = "";
        // Case: extra whitespace between command and values

        int j = i;
        while (line[j] == ' ') {
        j += 1;
        }
    
         // Getting the values
        while ( j < lineLength ){
            temp += line[j];
            value = temp;
            j++;
        }
    }
    return 0;
}


