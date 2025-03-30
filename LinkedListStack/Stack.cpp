#include "Stack.h"

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

	while (newLastElementPointer->GetNextElementPtr() != lastElementPtr &&
		   newLastElementPointer->GetNextElementPtr() != nullptr)
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
