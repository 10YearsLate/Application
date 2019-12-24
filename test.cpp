#include <iostream>
#include<ctime>
#include <fstream>
#include <string>
using namespace std;
using std::ofstream;

struct book
{
    string author;
    string title;
    string publisher;
    string description;
    string ISBN;
    string year_published;
    book *link;
};

void sortedInsert(struct book**, struct book*);
void insertionSort(struct book **head_ref) 
{ 
    // Initialize sorted linked list 
    struct book *sorted = NULL; 
  
    // Traverse the given linked list and insert every 
    // node to sorted 
    struct book *current = *head_ref; 
    while (current != NULL) 
    { 
        // Store next for next iteration 
        struct book *next = current->link; 
  
        // insert current in sorted linked list 
        sortedInsert(&sorted, current); 
  
        // Update current 
        current = next; 
    } 
  
    // Update head_ref to point to sorted linked list 
    *head_ref = sorted; 
} 

void sortedInsert(struct book** head_ref, struct book* new_node) 
{ 
    struct book* current; 
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->author >= new_node->author) 
    { 
        new_node->link = *head_ref; 
        *head_ref = new_node; 
    } 
    else
    { 
        /* Locate the node before the point of insertion */
        current = *head_ref; 
        while (current->link!=NULL && 
               current->link->author < new_node->author) 
        { 
            current = current->link; 
        } 
        new_node->link = current->link; 
        current->link = new_node; 
    } 
} 

void addbook(book** head_ref){
    book* new_node = new book();
    cout<<"Enter Author :";
    cin >> new_node->author;
    cout<<"Enter Title :";
    cin >> new_node->title;
    cout<<"Enter Publisher:";
    cin >> new_node->publisher;
    cout<<"Enter Description :";
    cin >> new_node->description;
    cout<<"Enter Year :";
    cin >> new_node->year_published;

    book *last = *head_ref; 

    new_node->link = NULL;  

    if (*head_ref == NULL)  
    {  
        *head_ref = new_node;  
        return;  
    }  
  
    while (last->link != NULL)  
        last = last->link;  
  
    /* 6. Change the next of last node */
    last->link = new_node;  
    return;  

}
void removebook(book** head_ref){

    book* current = *head_ref;  
    book* next;  
  
    while (current != NULL)  
    {  
        next = current->link;  
        free(current);  
        current = next;  
    }  
      
    *head_ref = NULL;  
} 

void deletebook(book** head_ref){
    cout<<"Enter Title of the book to be removed :";
    string t;
    cin >> t;
    book *last = *head_ref; 
    book *prev=NULL;
    while (last->link != NULL)  {
        if(last->title==t) {
            if(prev==NULL) {
                *head_ref=last->link;
                last=NULL;
            }
            else{
                prev->link=last->link;
                last=NULL;
            }
        }
        last = last->link; 
    }
         

}


bool booksearch(book* head, string criteria)  
{  
    book* current = head; // Initialize current  
    if(criteria=="Author"){
        cout << "Enter Author Name :";
        string name;
        cin >> name;
        while (current != NULL)  
         {  
            if (current->author == name)  
                return true;  
            current = current->link;  
        }  
    }

    if(criteria=="Title"){
        cout << "Enter Title :";
        string name;
        cin >> name;
        while (current != NULL)  
         {  
            if (current->title == name)  
                return true;  
            current = current->link;  
        }  
    }

    if(criteria=="ISBN"){
        cout << "Enter ISBN :";
        string name;
        cin >> name;
        while (current != NULL)  
         {  
            if (current->ISBN == name)  
                return true;  
            current = current->link;  
        }  
    }
    
    return false;  
}  


int main(){
    book *head = NULL;
    book *newNode;
    book *p;
    ifstream reeaad;
    reeaad.open("book.txt");
    newNode = new book;
    head = newNode;  
    while(!EOF)
    {
        getline(reeaad,newNode->author);
        getline(reeaad,newNode->title);
        getline(reeaad,newNode->publisher);
        getline(reeaad,newNode->description);
        getline(reeaad,newNode->year_published);
        newNode->link = new book;
        newNode = newNode->link;
    }
    reeaad.close();
    time_t tt;
    struct tm * ti; 
    time (&tt); 
    ti = localtime(&tt); 
  
    cout << "Welcome to Library Current Day, Date and Time(UTC) is = " 
         << asctime(ti); 

    std::cout << "Please select item from below Menu";
    int ch;
    while(1)
    {
        cout<<"\n 1. Add new book";
        cout<<"\n 2. Remove Book";
        cout<<"\n 3. Remove All";
        cout<<"\n 4. Sort Book List";
        cout<<"\n 5. Search By Author";
        cout<<"\n 6. Search by Title";
        cout<<"\n 7. Search by ISBN";
        cout<<"\n 8. Exit";
        cout<<"\n enter your choice:";
        cin >>ch;

        switch(ch)
            {
            case 1:
                addbook(&head);
                break;
            case 2:
                deletebook(&head);
                break;
            case 3:
                removebook(&head);
                break;
            case 4:
                insertionSort(&head);
                break;
            case 5:
                cout <<booksearch(head, "Author");
                break;
            case 6:
                cout << booksearch(head, "Title");
                break;
            case 7:
                cout <<booksearch(head, "ISBN");
                break;
            case 8:
                exit(0);
                break;
            default:
                cout<<"\n invalid choice";
                break;
            }
    }

    ofstream outdata;
    outdata.open("book.txt");
    for (book* p = head; p != NULL; p = p->link){  
        outdata << p->author << endl;
        outdata << p->title << endl;
        outdata << p->publisher << endl;
        outdata << p->description << endl;
        outdata << p->ISBN << endl;
        outdata << p->year_published << endl;
    
        outdata.close();
  }  

}