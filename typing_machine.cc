// Copyright 2018 <Author>

#include "typing_machine.h"

TypingMachine::TypingMachine() {
	m_pCursorPoint = new Node(' ');
	m_nDataCount = 0;
	return;
}

void TypingMachine::HomeKey() {
	Node* prev = m_pCursorPoint->GetPreviousNode();
	if (prev == nullptr)
	{
		return;
	}
	prev->EraseNextNode();

	Node* Target = nullptr;

	do 
	{
		Target = prev;
		prev = Target->GetPreviousNode();
	} while (prev != nullptr);

	m_pCursorPoint = Target->InsertPreviousNode(' ');
	return;
}

void TypingMachine::EndKey() {
	Node* next = m_pCursorPoint->GetNextNode();
	if (next == nullptr)
	{
		return;
	}
	next->ErasePreviousNode();

	Node* Target = nullptr;

	do
	{
		Target = next;
		next = Target->GetNextNode();
	} while (next != nullptr);

	m_pCursorPoint = Target->InsertNextNode(' ');
	return;
}

void TypingMachine::LeftKey() {
	Node* prev = m_pCursorPoint->GetPreviousNode();
	if (prev == nullptr)
	{
		return;
	}

	if (prev->EraseNextNode())
	{
		m_pCursorPoint = prev->InsertPreviousNode(' ');
	}
	return;
}

void TypingMachine::RightKey() {
	Node* next = m_pCursorPoint->GetNextNode();
	if (next == nullptr)
	{
		return;
	}

	if (next->ErasePreviousNode())
	{
		m_pCursorPoint = next->InsertNextNode(' ');
	}
	return;
}

bool TypingMachine::TypeKey(char key) {
	if (m_nDataCount >= 100)
	{
		return false;
	}
	if (key > 126 || key < 32)
	{
		return false;
	}

	m_pCursorPoint->InsertPreviousNode(key);
	m_nDataCount++;

	return true;
}

bool TypingMachine::EraseKey() {

	if (m_pCursorPoint->ErasePreviousNode())
	{
		--m_nDataCount;
		return true;
	}

  return false;
}

std::string TypingMachine::Print(char separator) {
	std::string prevData;
	std::string nextData;

	Node* prev = m_pCursorPoint->GetPreviousNode();
	Node* next = m_pCursorPoint->GetNextNode();
	while (prev != nullptr)
	{
		prevData = prev->GetData() + prevData;
		prev = prev->GetPreviousNode();
	}
	while (next != nullptr)
	{
		nextData = nextData + next->GetData();
		next = next->GetNextNode();
	}

	if (separator == 0)
	{
		return prevData + nextData;
	}
	return prevData + separator + nextData;
}
