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
            temp->next->prev = newNode; //then temp->next->prev points to newNode
        else
            tail = newNode; //newNode is the tail node if temp->next is not valid
        temp->next = newNode; //temp->next pointer points to newNode
    }

    void delete_val(int value) { //deleting by value passed in
        if (!head) return; //if no head, then list empty and nothing to delete

        Node* temp = head; //create temp pointer pointing to head
        
        while (temp && temp->data != value) //while temp is valid and we dont reach the node that has the data value we want to delete
            temp = temp->next; //traverse temp to next node

        if (!temp) return; //if you go past range of the list, value was not found, exit

        if (temp->prev) //if temp is not pointing to head node
            temp->prev->next = temp->next; //temp->prev->next pointer is not going to point to temp, but to temp->next instead
        else //if it is the pointing to head
            head = temp->next; //new head will be node temp->next is pointing to

        if (temp->next) //if not the tail node
            temp->next->prev = temp->prev; //temp->next->prev will point to node before temp instead of temp itself
        else //if it is tail
            tail = temp->prev; //change tail to be node before temp 

        delete temp; //delete temporary node
    }

    void delete_pos(int pos) { //deleting by position, passing in position to delete
        if (!head) { //if head not valid output list is empty
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) { //if the node to delete is the head node
            pop_front(); //call pop_front function
            return;
        }
    
        Node* temp = head; //create temp node pointing to head
    
        for (int i = 1; i < pos; i++){ //traverse to position to delete
            if (!temp) { //if temp no longer valid
                cout << "Position doesn't exist." << endl; //position was less than or greater than range of list
                return;
            }
            else
                temp = temp->next; //else continue moving down the list
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) { //if node to delete is tail
            pop_back(); //call pop_back function
            return;
        }
    
        Node* tempPrev = temp->prev; //create new pointer to node which will point to temp->prev node
        tempPrev->next = temp->next; //temp->prev->next aka tempPrev-> points to node after temp instead of temp itself
        temp->next->prev = tempPrev; //temp->next>prev points to tempPrev rearranging the pointers around temp allowing us to get rid of it while keeping the list whole
        delete temp; //delete temp node
    }

    void push_back(int v) { //push_back adds node to end of list and sets value passed in 
        Node* newNode = new Node(v); //creating dynamically allocated node setting value passed in and creating pointer to it
        if (!tail) //if list is empty
            head = tail = newNode; //newnode is head and tail since its the only node
        else { //if list not empty
            tail->next = newNode; //make tail's next pointer point to newnode
            newNode->prev = tail; //and newnode->prev to the tail
            tail = newNode; //make newnode the new tail
        }
    }
    
    void push_front(int v) { //adds node to front of list
        Node* newNode = new Node(v); //creates dynamically allocated node ^ same as above
        if (!head) //if list empty
            head = tail = newNode; //head is the tail which is the newnode bc its the only node
        else { //if not empty
            newNode->next = head; //newnode->next points to head
            head->prev = newNode; //head->prev is newnode
            head = newNode; //make newnode the new head
        }
    }
    
    void pop_front() { //deletes head node

        if (!head) { //if list empty
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head; //create temp node pointing to head

        if (head->next) { //if there is more than just the head node
            head = head->next; //head->next node is now the head
            head->prev = nullptr; //set head->prev to nullptr
        }
        else //if there is only one node
            head = tail = nullptr; //head is tail which is nullptr, list is empty
        delete temp; //delete
    }

    void pop_back() { //deletes node from back
        if (!tail) { //list empty
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail; //create temp node pointer pointing to tail

        if (tail->prev) { //if more than one node
            tail = tail->prev; //set tail to point to node before tail
            tail->next = nullptr; //set tail->next to nullptr
        }
        else
            head = tail = nullptr; //list is empty
        delete temp;
    }

    ~DoublyLinkedList() { //destructor
        while (head) { //while list is not empty
            Node* temp = head; //temp points to head
            head = head->next; //head traverses down the list
            delete temp; //delete temp
        }
    }
    void print() { //print
        Node* current = head; //create current pointing to head
        if (!current) { //list empty
            cout << "List is empty." << endl;
            return;
        }
        while (current) { //while current is pointing to valid data
            cout << current->data << " "; //output the data
            current = current->next; //keep current moving forward
        }
        cout << endl;
    }

    void print_reverse() { //print in reverse
        Node* current = tail; //current points to tail instead of head
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) { //while there is valid data
            cout << current->data << " "; //print the data
            current = current->prev; //move backwards through list
        }
        cout << endl;
    }

    void every_other_element() { //need to make sure index is not even so %2 does not = 0
        Node* current = head;
        int i = 1;

        while (current) {
            if (i % 2 != 0) 
                cout << current->data << " ";
            current = current->next;
            i++;
        }
        
        cout << endl;
    }
};

int main() {
    DoublyLinkedList list;
    list.push_back(1);
    list.push_back(24);
    list.push_back(67);
    list.push_back(3);
    list.push_back(99);
    list.push_back(45);
    list.push_back(10);

    cout << "Printing list:\n";
    list.print();

    cout << endl;

    cout << "Printing every other node:\n";
    list.every_other_element();

    
    return 0;
}