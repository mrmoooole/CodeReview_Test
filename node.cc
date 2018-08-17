// Copyright 2018 <Author>

#include "node.h"

Node::Node(char data) : m_prevNode(nullptr), m_nextNode(nullptr), m_myData(data)
{
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
	Node* newPrevNode = new Node(data);
	newPrevNode->m_prevNode = m_prevNode;
	newPrevNode->m_nextNode = this;
	if (m_prevNode != nullptr) {
		m_prevNode->m_nextNode = newPrevNode;
	}
	m_prevNode = newPrevNode;

	return newPrevNode;
}

Node* Node::InsertNextNode(char data) {
	Node* newNextNode = new Node(data);
	newNextNode->m_prevNode = this;
	newNextNode->m_nextNode = m_nextNode;
	if (m_nextNode != nullptr) {
		m_nextNode->m_prevNode = newNextNode;
	}
	m_nextNode = newNextNode;

	return newNextNode;
}

bool Node::ErasePreviousNode() {
	if (m_prevNode != nullptr) {
		Node* PrevNode = m_prevNode;
		Node* PrevPrevNode = m_prevNode->GetPreviousNode();
		m_prevNode = PrevPrevNode;
		if (PrevPrevNode != nullptr) {
			PrevPrevNode->m_nextNode = this;
		}
		delete PrevNode;
		PrevNode = nullptr;
		return true;
	}
	return false;
}

bool Node::EraseNextNode() {
	if (m_nextNode != nullptr) {
		Node* NextNode = GetNextNode();
		Node* NextNextNode = NextNode->GetNextNode();
		m_nextNode = NextNextNode;
		if (NextNextNode != nullptr) {
			NextNextNode->m_prevNode = this;
		}
		delete NextNode;
		NextNode = nullptr;
		return true;
	}
	return false;
}



