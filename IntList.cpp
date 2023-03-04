#include <iostream>
using namespace std;

#include "IntList.h"

IntList::IntList()
{
    head = nullptr;
    tail = nullptr;
}
IntList::~IntList()
{
    //delete head;
    //delete tail;
    clear();
}
void IntList::push_front(int value)
{
    IntNode *newNode = new IntNode(value);
    //The new node is pointing to the first head 
    newNode->next = this->head;
    //Now the head is pointing to the new node
    this->head = newNode;
    //If the new node is the first node, then it is both the head and tail
    if(tail==nullptr)
        tail = head;
    return;
}
void IntList::pop_front()
{
    //The head pointer is pointing to the node after the first,
    //Essentially disregarding the first node
    //this->head = head->next; 
    if(empty())
    {
        return;
    }
    IntNode* tempNode = head->next;
    delete head;
    head = tempNode;
    return;
}
bool IntList::empty() const
{
    if(head == nullptr)
        return true;
    else
        return false;

}
const int &IntList::front() const
{
    return head->value;
}
const int &IntList::back() const
{
    return tail->value;
}
ostream &operator<<(ostream &out, const IntList &list)
{
    IntNode*currNode = list.head;
    while(currNode != nullptr)
    {
        out << currNode->value;
        currNode = currNode->next;
        //Placing a space expect for the end
        if(currNode != 0)
            out << " ";
    }
    return out;
}

IntList::IntList(const IntList &cpy): head(nullptr), tail(nullptr)
{
    IntNode* copyHead = cpy.head;
    IntNode* currentCopy = copyHead;
    while(currentCopy != nullptr)
    {
        push_back(currentCopy->value);
        currentCopy = currentCopy->next;
    }
}
IntList& IntList::operator=(const IntList &rhs)
{
    if(this!=&rhs)
    {
        clear();
        IntNode* currNode = rhs.head;
        while(currNode != nullptr)
        {
            push_back(currNode->value);
            currNode = currNode->next;
        }
    }
    return *this;
}
void IntList::push_back(int value)
{
    IntNode* tempNode = new IntNode(value);
    if (empty())
    {
        head = tempNode;
        tail = tempNode;
        tempNode->next = nullptr;
    }
    else
    {
        tempNode->next = nullptr;
        tail->next = tempNode;
        tail = tempNode;
    }
}
void IntList::clear()
{
    //While there are still nodes, pop them
    while(!empty())
    {
        IntNode* tempNode = head;
        head = head->next;
        delete tempNode;
    }
    this->head = nullptr;
    this->tail = nullptr;
}
void IntList::selection_sort()
{
    if(empty())
    {
        //If it's empty, return it as it is
        return;
    }
    else
    {
        for(IntNode* i = head; i != nullptr; i = i->next)
        {
            for(IntNode* j = i->next; j != nullptr; j = j->next)
            {
                if(i->value > j->value)
                {
                    int tempNum = i->value;
                    i->value = j->value;
                    j->value = tempNum;
                }
            }
        }
    }
}
void IntList::insert_ordered(int value)
{
    IntNode* tempNode = new IntNode(value);
    if(empty())
    {
        push_back(value);
        delete tempNode;
        tempNode = nullptr;
    }
    else if (tempNode->value <= head->value)
    {
        push_front(value);
        delete tempNode;
        tempNode = nullptr;
    }
    else if (tempNode->value >= tail->value)
    {
        push_back(value);
        delete tempNode;
        tempNode = nullptr;
    }
    else if (head->next == nullptr)
    {
        if(head->value < value)
            push_back(value);
        else
            push_front(value);
        delete tempNode;
        tempNode = nullptr;
    }
    else
    {
        IntNode* currNode = head;
        while(currNode->next->value < tempNode->value && currNode->next != nullptr)
        {
            currNode = currNode->next;
        }
        tempNode->next = currNode->next;
        currNode->next = tempNode;
    }
}
void IntList::remove_duplicates()
{
    if(!empty())
    {
        IntNode* tempNode = nullptr;
        IntNode* currentNode = head;
        while(currentNode != nullptr && currentNode->next != nullptr)
        {
            tempNode = currentNode;
            while(tempNode->next != nullptr)
            {
                if(currentNode->value==tempNode->next->value)
                    tempNode->next = tempNode->next->next;
                else
                    tempNode = tempNode->next;
                if(tempNode->next == nullptr)
                    tail = tempNode;
            }
            currentNode = currentNode->next;
        }
    }
}
