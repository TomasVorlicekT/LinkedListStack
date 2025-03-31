#include "Stack.h"
#include <iostream>

Stack::Element::Element(int value_in, Element* nextPtr_in)
	:
	value(value_in),
	nextElementPtr(nextPtr_in)
{
}

void Stack::Element::SetValue(int value_in)
{
	value = value_in;
}

int Stack::Element::GetValue() const
{
	return value;
}

void Stack::Element::SetNextElement( Element* nextPtr_in)
{
	nextElementPtr = nextPtr_in;
}

Stack::Element* Stack::Element::GetNextElementPtr() const
{
	return nextElementPtr;
}

Stack::~Stack()
{
	Element* currentElementPointer = firstElementPtr;
	const int linkedListSize = Size();

	for (int i = 0; i < linkedListSize; i++)
	{
		Element* nextElement = currentElementPointer->GetNextElementPtr();
		delete currentElementPointer;
		currentElementPointer = nextElement;
	}

}

Stack::Stack(const Stack& source)
{
	// Handling of an empty stack
	if (source.Empty())
	{
		firstElementPtr = nullptr;
		lastElementPtr = nullptr;
		return;
	}

	//// Handling of a single element stack, where first and last pointer point to the same element
	//if (source.Size() == 1)
	//{
	//	Push(source.firstElementPtr->GetValue());
	//	return;
	//}

	// For other cases we have to go though the linked list and make a deep copy for each element
	Element* currentElementPtr_source = source.firstElementPtr;
	Push(currentElementPtr_source->GetValue());

	while (currentElementPtr_source != source.lastElementPtr)
	{
		currentElementPtr_source = currentElementPtr_source->GetNextElementPtr();
		Push(currentElementPtr_source->GetValue());
	}

	std::cout << "Copy Constuctor\n";

}

Stack& Stack::operator=(const Stack& source)
{
	// Copy Assign will not bother checking for existing objects, it will pop all  
	// the elements from the old stack and create a deep copy using Pop method
	
	const int size = Size();

	for (int i = 0; i < size; i++)
	{
		Pop();
	}

	// Deep Copy
	const int sizeSource = source.Size();
	Element* currentElementPtr = source.firstElementPtr;

	for (int i = 0; i < sizeSource; i++)
	{
		Push(currentElementPtr->GetValue());
		currentElementPtr = currentElementPtr->GetNextElementPtr();
	}

	std::cout << "Executing Copy Assign\n";

	return *this;

}

void Stack::Push(int val)
{
	Element* newElementPtr = new Element(val, nullptr);

	if (firstElementPtr == nullptr)
	{
		firstElementPtr = newElementPtr;
	}

	if (lastElementPtr)
	{
		lastElementPtr->SetNextElement(newElementPtr);
	}

	lastElementPtr = newElementPtr;
}

int Stack::Pop()
{
	if (firstElementPtr == nullptr)
	{
		return -1;
	}

	int valueToReturn = lastElementPtr->GetValue();
	Element* newLastElementPointer = firstElementPtr;

	while (newLastElementPointer->GetNextElementPtr() != lastElementPtr 
		   && newLastElementPointer->GetNextElementPtr() != nullptr)
	{
		newLastElementPointer = newLastElementPointer->GetNextElementPtr();
	}

	if (newLastElementPointer->GetNextElementPtr() == nullptr)
	{
		// this is a case when we are popping the first element of the linked list
		delete lastElementPtr;
		firstElementPtr = nullptr;
		lastElementPtr = nullptr;

	}
	else
	{
		delete lastElementPtr;
		newLastElementPointer->SetNextElement(nullptr);
		lastElementPtr = newLastElementPointer;
	}

	return valueToReturn;

}

int Stack::Size() const
{
	int size = 0;
	if (firstElementPtr == nullptr)
	{
		return size;
	}

	Element* currentElementPointer = firstElementPtr;

	while (firstElementPtr && currentElementPointer->GetNextElementPtr())
	{
		currentElementPointer = currentElementPointer->GetNextElementPtr();
		size++;
	}
	size++; // To account for the last element which has nullptr as its pointer

	return size;
}

bool Stack::Empty() const
{
	return Size() == 0 ? true : false; // implicit conversion from int to bool
}
