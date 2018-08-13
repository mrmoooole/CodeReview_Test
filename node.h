// Copyright 2018 <Author>

#ifndef NODE_H_
#define NODE_H_

class Node {
public:
  explicit Node(char data);
  char GetData();
  Node* InsertPreviousNode(char data);
  Node* InsertNextNode(char data);
  Node* GetPreviousNode();
  Node* GetNextNode();
  bool ErasePreviousNode();
  bool EraseNextNode();

  Node* m_prevNode;
  Node* m_nextNode;
private:
	char m_myData;
};

#endif  // NODE_H_
