#include <iostream>
using namespace std;

//Node class to create nodes that contain numbers as string
class Node{
public:
    string data;
    Node* next;

    Node(string numbers){
        data = numbers;
        next = nullptr;
    }
};

//The linked list class which will store the big number
class LargeNumberLinkedList{
public:
    Node* head;
    Node* tail;
    int numOfNodes;

    //Constructor for linked list
    LargeNumberLinkedList(){
        head = nullptr;
        tail = nullptr;
        numOfNodes = 0;
    }

    //Adding bits of the number to the linked list
    void addToNumber(string numbers){
        Node* newNode = new Node(numbers);
        if(!head){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
        numOfNodes++;
    }

    //Function to display the entire number by traversing the list and displaying data of each node
    void displayNumber(){
        Node* current = head;
        while(current){
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

//Using unsigned numbers from here on because of their ability to store more values compared to signed numbers, as we're not going to be dealing with negative signs

    //Function to perform modulo on the large number stored in the linked list
    unsigned long mod(unsigned long modFactor){
        //starting from the head
        Node* current = head;
        unsigned long result = 0;
        //traversing the list node by node and applying modulo arithmetic to each node
        while(current){
            for (char digit : current->data) {
                //In C++, we can convert a char digit to an int by subtracting zero from it, which is what is happening here with each character digit
                //Multiplying the current result by 10 to shift it left, adding the current digit and then taking mod with the modfactor
                result = (result * 10 + (digit - '0')) % modFactor;
            }
            current = current->next;
        }
        return result;
    }

    //Function to calculate (base^exp) % mod
    unsigned long exponentiation(unsigned long base, unsigned long exp, unsigned long mod){
    unsigned long result = 1; //Result initiazlied as 1
        base = base % mod; //Base reduced by mod
        while (exp > 0) {
            //If exponent is odd, multiply the baase with the result and then apply modulus
            if (exp % 2 == 1) {
                result = (result * base) % mod;
            }
            //Bitwise right shift of exp, which is similar to dividing by 2
            exp = exp >> 1;
            //Squaring the base and applying modulus
            base = (base * base) % mod;
        }
        return result;
    }

};

//Function to split a string containing the number into small chunks, each of 64 bits, and adding it to the linked list
void splitNumber(string bigNumber, LargeNumberLinkedList &list){
    int len = bigNumber.length();
    //Making each node contain 64 bit numbers as specified in the task
    int nodeSize = 64;

    //Splitting the number into 64 bit blocks and sotring them to nodes of the linked list
    for(int i=0; i<len; i+= nodeSize){
        string numString = bigNumber.substr(i, min(nodeSize, len-i));
        list.addToNumber(numString);
    }
}

//Function to perform the miller-rabin primality test
bool millerRabin(LargeNumberLinkedList& bigNum, unsigned long modFactor){
    //Computing the modulus of the large number in linked list using the provided modfactor to reduce the large number
    unsigned long mod = bigNum.mod(modFactor); 

    //Handling cases where the number is very little i.e if its less than 1 or equal to 4, its composite
    //If its less than or equal to 3 i.e 2 or 3, its prime
    if (mod <= 1 || mod == 4) {
        return false;
    } else if (mod <= 3) {
        return true;
    }

    //Decomposing mod-1 into d * 2^r where d is odd (this is necessary for miller rabin algorithm)
    unsigned long d = mod - 1;
    //r is a counter for the number of times d was divided by 2(it tracks the power of 2)
    int r = 0;
    //Continously divide d by 2 until it becomes odd, and track the power of 2 in r by incrementing it each time d is divided
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    //Choosing the base 'a' for the test, and using 2 for simplicity
    unsigned long a = 2;
    //Calculating a^d % mod using the exponentiation function created earlier and storing it in variable x
    unsigned long x = bigNum.exponentiation(a, d, mod);

    //Checking if x is 1 or -1. If it is, the number is probably prime
    if (x == 1 || x == mod - 1) {
        return true;
    }

    //Repeatedly performing the squaring step on x to check if it eventually reached mod-1
    for (int i = 0; i < r - 1; i++) {
        //Squaring x and taking modulus
        x = (x * x) % mod;
        
        //If x becomes mod-1 at any iteration of the for loop, the number is probably prime
        if (x == mod - 1) {
            return true;
        }
    }

    //If none of the conditions resulted in the number being prime, its composite
    return false; 
};

int main(){
    string bigNumber = "1000000009";

    LargeNumberLinkedList largeNumList;

    splitNumber(bigNumber, largeNumList);
    
    cout << "Number stored in Linked List: " << endl;
    largeNumList.displayNumber();
    cout << endl;

    unsigned long modFactor = 1000000007;
    if (millerRabin(largeNumList, modFactor)) {
        cout << "The number is prime" << endl;
    } else {
        cout << "The number is composite" << endl;
    }
}