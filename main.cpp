//Avleen Gill - 210 Midterm #1
// fully comment each instruction in the code
// explain what is hapenning on that line
// write a function every_other_element() that will output the data
// structure starting with first and skipping secnod, etc

#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node { //creating node data structure which will hold
        int data; //integer data
        Node* prev; //pointer pointing to the prev node
        Node* next; //pointer pointing to next node
        //constructor used to intialize 
        Node(int val, Node* p = nullptr, Node* n = nullptr) { //takes in 3 parameters, sets p and n pointers to nullptr
            data = val; //int val was passed in, and int data is set to that value
            prev = p; //prev set to nullptr as a default
            next = n; //next set to nullptr
        }
    };

    //creating pointers head and tail which will point to objects of Node type
    Node* head; //generally used to point at the first node
    Node* tail; //generally used to point at last node

public:
    //default constructor which sets pointers head and tail declared above to nullptr
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //function takes in and integer value and position
    void insert_after(int value, int position) { //position tells us where to add/insert a node, value tells us what int data to inset
        if (position < 0) { //if position is < 0, it is not valid so exit
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value); //new Node(Value) creates dynamically allocated Node and sets int data as the value passed in, newNode is the pointer to that node
        if (!head) { //if the list is empty
            head = tail = newNode; //the new node is now the tail and the head since it is the only node
            return;
        }

        Node* temp = head; //create temporary pointer temp which points to the same node as the head pointer (head node)
        for (int i = 0; i < position && temp; ++i) //traverse to the position passed in while making sure temp is valid (not = nullptr)
            temp = temp->next; //then temp now points to the node after it
                               //temp->next is pointing to the next pointer

        if (!temp) { //if temp is not valid (=nullptr), then it could not locate the position passed in
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; //delete dynamically allocated node
            return;
        }

        newNode->next = temp->next; //newNode->next pointer is now pointing to temp->next pointer
        newNode->prev = temp; //newNode->prev is pointint to temp
        if (temp->next) //if temp->next exists meaning if temp is not the tail node
            temp->next->prev = newNode; //then temp->next->prev points to newNode, inserting the newNode where
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}