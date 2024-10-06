#include <iostream>
using namespace std;

//Class which creates processes
class Process{
public:
    string process_id;
    int execution_time;
    int remaining_time;

    Process(string process_id, int execution_time, int remaining_time){
        this->process_id = process_id;
        this->execution_time = execution_time;
        this->remaining_time = remaining_time;
    }
};

//Nodes whose "data" is a pointer to a process
class Node{
public:
    Process* proc;
    Node* next;

    //Constructor for assigning a process to a node
    Node(Process* proc){
        this->proc = proc;
        next = nullptr;
    }
};

//Class which will create the circular linked list that will have processes on its nodes
class CircularLinkedList{
public:
    Node* head;
    Node* tail;

    CircularLinkedList(){
        head = nullptr;
        tail = nullptr;
    }

    //Simple function to check whether list is empty
    bool isEmpty(){
        return head == nullptr;
    }

    //Adding a new process to the list 
    void addProcess(string process_id, int execution_time){
        //Creating the new process, then assigning a new node which points to that process using the constructor
        Process* newProc = new Process(process_id, execution_time, execution_time);
        Node* newNode = new Node(newProc);
        
        //If list is empty, the new node(process) will be the first node and also the last node i.e. the head and tail will be the same
        if(!head){
            head = newNode;
            tail = newNode;
            newNode->next = head;
        }
        //Otherwise, the new node will be inserted at the end and the tail will point to it
        else{
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        }
    }

    //Function to remove a process from the list
    void removeProcess(Node* node){
        //If list is empty, return 
        if(!head){
            cout << "There are no processes" << endl;
            return;
        }


        Node* temp = head;
        Node* prev = nullptr;

        //Case which handles the node to be removed being the head
        if(head == node){
            //If the head is the same as tail i.e. the list has just one node, delete the head and make the head and tail point to nullptr to avoid memory issues
            if(head == tail){
                delete head;
                head = nullptr;
                tail = nullptr;
            }
            else{
                tail->next = head->next;
                head = head->next;
                delete node;
            }
        }
        else{
            //Normal case where head isn't the node to be removed
            do{
                prev = temp;
                temp = temp->next;
            }while(temp!=head && temp!=node);

            if(temp == node){
                prev->next = temp->next;
                if(temp==tail){
                    tail = prev;
                }
                delete temp;
            }
        }
    }

    //Function to display all the processes
    void displayProcesses(){
        //If list is empty, return
        if(!head){
            cout << "No process in list" << endl;
            return;
        }

        //Creating a temp node to traverse the list and print the list using a do while loop as it is a circular linked list
        Node* temp = head;
        do{
            cout << temp->proc->process_id << " (Remaining: " << temp->proc->remaining_time << "), ";
            temp = temp->next;
        }while(temp!=head);
        cout << endl;
    }

    //Function to get the next node of a specific node, to be used later while running cycles
    Node* getNextNode(Node* current){
        if(current == nullptr){
            return nullptr;
        }
        return current->next;
    }



};

//Scheduler class to run cycles
class Scheduler{
public:
    CircularLinkedList* processList;
    int cpu_time_per_cycle;

    Scheduler(CircularLinkedList* processList, int cpu_time_per_cycle){
        this->processList = processList;
        this->cpu_time_per_cycle = cpu_time_per_cycle;
    }

    //Function that runs cycles
    void runCycle(){
        //If list is empty, return
        if(processList->isEmpty()){
            cout << "There are no processes in the list" << endl;
            return;
        }

        //Creating two new nodes to traverse the list
        Node* current = processList->head;
        Node* prev = nullptr;
        //do while loop as its a circular linked list
        do{
            //Displaying a message about which process is running, then updating and reducing its remaining time
            cout << "Running process: " << current->proc->process_id << "..." << endl;
            current->proc->remaining_time = current->proc->remaining_time - cpu_time_per_cycle;

            //If the remaining time reaches zero or becomes negative, display the process as completed and remove it from the list using the removeProcess() function
            if(current->proc->remaining_time <= 0){
                cout << current->proc->process_id << " completed" << endl;
                Node* toRemove = current;
                current = processList->getNextNode(current);
                if (toRemove == processList->head && toRemove == processList->tail){
                    processList->removeProcess(toRemove);
                    break;
                }
                processList->removeProcess(toRemove);
            }
            else{
                prev = current;
                current=processList->getNextNode(current);
            }
            processList->displayProcesses();
        }while(current!=processList->head && current!=nullptr);
    }

    //Function to dynamically add a new process while the cycle is runnning, as mentioned in the optional task
    void insertNewProcess(string process_id, int execution_time){
        processList->addProcess(process_id,execution_time);
        cout << "New process " << process_id << " with execution time " << execution_time << " added" << endl;
    }
};




int main(){
    //Creating the list, then adding processes
    CircularLinkedList processList;

    processList.addProcess("P1",10);
    processList.addProcess("P2",5);
    processList.addProcess("P3",8);

    //Specifying the time per cycle
    int timePerCycle = 3;
    Scheduler scheduler(&processList, timePerCycle);

    cout << "Initial processes: "; 
    processList.displayProcesses();
    cout << endl << "CPU time per Process per cycle: " << timePerCycle << endl;

    int cycles = 0;
    //Running the scheduler until the list becomes empty by all processes getting completed
    while(!processList.isEmpty()){
        cout << "Cycle " << ++cycles << endl;
        scheduler.runCycle();

        //Adding a new process after two cycles to showcase the optional task
        if (cycles == 2) {
                scheduler.insertNewProcess("P4", 9);
        }
        cout << endl;
    }
    cout << "All processes completed" << endl;
}