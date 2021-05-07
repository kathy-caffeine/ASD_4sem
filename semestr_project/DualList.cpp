#include "DualList.h"

using namespace std;

void dList::push_back(int add)
{
	if (size == 0) //if list is empty
	{
		head = new Node(add); //create head
		tail = head;
	}
	else
	{
		Node* curr = new Node(add);
		curr->before = tail;
		tail->next = curr;
		tail = curr;  //set new tail
	}
	size++;
}

void dList::push_front(int add)
{
	if (size == 0)
	{
		head = new Node(add);
		tail = head;
	}
	else
	{
		Node* curr = new Node(add);
		curr->next = head;
		head->before = curr;
		head = curr;  //set new head
	}
	size++;
}

size_t dList::get_size()
{
	return size;
}

void dList::pop_back()
{
	if (size == 1)
	{
		size = 0;  //setup zero position
		head = NULL;
		tail = NULL;
	}
	else if (size > 1) //if list is not empty
	{
		tail = tail->before; //set new tail
		delete tail->next;
		tail->next = NULL;
		size--;
	}
	else  //else return error
		throw out_of_range("Segmentation fault");
}

void dList::pop_front()
{
	if (size == 1)
	{
		size = 0;  //setup zero position
		head = NULL;
		tail = NULL;
	}
	else if (size > 1) //if list is not empty
	{
		head = head->next; //set new head
		delete head->before;
		head->before = NULL;
		size--;
	}
	else //else return error
		throw out_of_range("Segmentation fault");
}

void dList::remove(size_t i)
{
	if (i >= size) //if index is larger than size return error
		throw out_of_range("Index is greater than list size");
	else if (i == 0) // if index points to first
		pop_front();
	else if (i == size - 1)	 // if index points to first
		pop_back();
	else
	{
		Node* cur = head;
		while (i) //go to "i" item
		{
			cur = cur->next;
			i--;
		}
		cur->before->next = cur->next; //cut item from list
		size--;
		delete cur;
	}
}

int dList::at(size_t i)
{
	if (i >= size) //if index is larger than size return error
		throw out_of_range("Index is greater than list size");
	else if (i == size - 1)
	{
		return tail->content;
	}
	else {
		Node* cur = head;
		while (i) //go to "i" item
		{
			cur = cur->next;
			i--;
		}
		return cur->content;
	}
}

void dList::insert(int add, size_t i)
{
	if (i >= size)  //if index is larger than size return error
		throw out_of_range("Index is greater than list size");
	else if (i == 0) //if insert before first item
		push_front(add);
	else
	{
		Node* cur = head;
		while (i)
		{
			cur = cur->next;
			i--;
		}
		Node* nadd = new Node(add, cur->before, cur);  //create new Node with new connection
		cur->before->next = nadd; //add poin to new Node
		cur->before = nadd;
		size++;
	}
}

void dList::print_to_console()
{
	Node* cur = head;
	while (cur != NULL)
	{
		cout << cur->content << "| ";
		cur = cur->next;
	}
}

void dList::clear()
{
	if (head != NULL)
	{
		while (head->next != NULL)  //delete all item
		{
			head = head->next;
			delete head->before;
		}
		size = 0;  //setup zero position
		head = NULL;
		tail = NULL;
	}
}

void dList::set(size_t i, int ins)
{
	if (i >= size) //if index is larger than size return error
		throw out_of_range("Index is greater than list size");
	else {
		Node* cur = head;
		while (i) //go to "i" item
		{
			cur = cur->next;
			i--;
		}
		cur->content = ins; //change content
	}
}

bool dList::isEmpty()
{
	if (head == NULL)
		return true;
	return false;
}

void dList::push_back(dList AddToEnd)
{
	Node* head_AddToEnd = AddToEnd.head;
	while (head_AddToEnd != NULL)
	{
		this->push_back(head_AddToEnd->content); //push new item to the end with content from transmitted list
		head_AddToEnd = head_AddToEnd->next;
	}
}

Iterator* dList::create_iterator(int start) {
	return new dualList_Iterator(head, start, size);
}

bool dList::dualList_Iterator::has_next() {
	return (current != NULL);
}

int dList::dualList_Iterator::next() {
	if (!has_next()) {
		throw std::out_of_range("No more elements");
	}
	int temp = current->content;
	current = current->next;
	return temp;
}