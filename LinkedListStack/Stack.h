#pragma once

class Stack
{
private:
	class Element
	{
	public:
		Element(int value_in, Element* nextPtr_in);
		void SetValue( int value_in );
		int GetValue() const;
		void SetNextElement( Element* nextPtr_in);
		Element* GetNextElementPtr() const;

	private:
		int value{};
		Element* nextElementPtr = nullptr;
	};

public:
	Stack() = default;
	Stack(const Stack& source);
	Stack& operator=(const Stack& source);
	~Stack();
	void Push( int val );
	int Pop();
	int Size() const;
	bool Empty() const;
private:
	Element* firstElementPtr = nullptr;
	Element* lastElementPtr = nullptr;
};