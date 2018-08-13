// Copyright 2018 <Author>

#include "node.h"

Node::Node(char data) {
	m_myData = data;
	m_prevNode = nullptr;
	m_nextNode = nullptr;
	return;
}

char Node::GetData() {
	return m_myData;
}

Node* Node::GetPreviousNode() {
	return m_prevNode;
}

Node* Node::GetNextNode() {
	return m_nextNode;
}




Node* Node::InsertPreviousNode(char data) {
	Node* orgPrevNode = GetPreviousNode();
	Node* newPrevNode = new Node(data);
	if (orgPrevNode != nullptr)
	{
		orgPrevNode->m_nextNode = newPrevNode;
	}
	newPrevNode->m_prevNode = orgPrevNode;
	newPrevNode->m_nextNode = this;
	m_prevNode = newPrevNode;

	return newPrevNode;
}

Node* Node::InsertNextNode(char data) {
	Node* orgNextNode = GetNextNode();
	Node* newNextNode = new Node(data);
	if (orgNextNode != nullptr)
	{
		orgNextNode->m_prevNode = newNextNode;
	}
	newNextNode->m_prevNode = this;
	newNextNode->m_nextNode = orgNextNode;
	m_nextNode = newNextNode;

	return newNextNode;
}

bool Node::ErasePreviousNode() {
	Node* PrevNode = GetPreviousNode();
	if (PrevNode == nullptr)
	{
		return false;
	}
	Node* PrevPrevNode = PrevNode->GetPreviousNode();
	m_prevNode = nullptr;
	if (PrevPrevNode != nullptr)
	{
		m_prevNode = PrevPrevNode;
		PrevPrevNode->m_nextNode = this;
	}

	delete PrevNode;
	PrevNode = nullptr;

	return true;
}

bool Node::EraseNextNode() {
	Node* NextNode = GetNextNode();
	if (NextNode == nullptr)
	{
		return false;
	}
	Node* NextNextNode = NextNode->GetNextNode();
	m_nextNode = nullptr;
	if (NextNextNode != nullptr)
	{
		m_nextNode = NextNextNode;
		NextNextNode->m_prevNode = this;
	}

	delete NextNode;
	NextNode = nullptr;

	return true;
}



