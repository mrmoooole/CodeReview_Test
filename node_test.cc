// Copyright 2018 Minkyu Jo

#include "node.h"
#include "node_test.h"
#include "test.h"



static Node* InitTest() {
	Node *node = new Node('A');
	node = node->InsertNextNode('B');
	node = node->InsertNextNode('C');
	node = node->InsertNextNode('D');
	return node->InsertNextNode('E');
}
static void FinalizeTest(Node* node) {
	Node* base = nullptr;
	do {
		base = node;
		node = base->GetNextNode();
	} while (node != nullptr);

	bool bRet = false;
	do {
		bRet = base->ErasePreviousNode();
	} while (bRet == true);
	delete base;
}
static Node* MoveToFirst(Node* node) {
	Node* base = nullptr;
	do {
		base = node;
		node = base->GetPreviousNode();
	} while (node != nullptr);
	return base;
}
static Node* MoveToLast(Node* node) {
	Node* base = nullptr;
	do {
		base = node;
		node = base->GetNextNode();
	} while (node != nullptr);
	return base;
}


class NodeConstructorTestSuite
{
private:
  static void SingleNodeTest() {
    Node *node = new Node('A');
    ASSERT_EQ(node->GetData(), 'A');
    delete node;
  }
  static void EmptyNodeTest() {
	  Node *node = new Node(' ');
	  ASSERT_EQ(node->GetData(), ' ');
	  delete node;
  }

public:
  static void RunTest() {
    SingleNodeTest();
	EmptyNodeTest();
  }
};

class GetNodeTestSuite
{
private:

	static void GetPreviousNodeTest() {
		Node* node = InitTest();
		ASSERT_EQ(node->GetData(), 'E');
		node = node->GetPreviousNode();
		ASSERT_EQ(node->GetData(), 'D');
		node = node->GetPreviousNode();
		ASSERT_EQ(node->GetData(), 'C');
		node = node->GetPreviousNode();
		ASSERT_EQ(node->GetData(), 'B');
		node = node->GetPreviousNode();
		ASSERT_EQ(node->GetData(), 'A');
		FinalizeTest(node);
	}

	static void GetPreviousNodeTest_FIRST() {
		Node* node = InitTest();
		node = MoveToFirst(node);
		ASSERT_EQ(node->GetData(), 'A');
		FinalizeTest(node);
	}

	static void GetNextNodeTest() {
		Node* node = InitTest();
		node = MoveToFirst(node);
		node = node->GetNextNode();
		ASSERT_EQ(node->GetData(), 'B');
		FinalizeTest(node);
	}

	static void GetNextNodeTest_LAST() {
		Node* node = InitTest();
		node = MoveToFirst(node);
		node = MoveToLast(node);
		ASSERT_EQ(node->GetData(), 'E');
		FinalizeTest(node);
	}
public:
	static void RunTest() {
		GetPreviousNodeTest();
		GetPreviousNodeTest_FIRST();
		GetNextNodeTest();
		GetNextNodeTest_LAST();
	}
};

class InsertNodeTestSuite
{
private:

	static void InsertPreviousNodeTest_01() {
		Node* node = InitTest();
		Node* newNode = node->InsertPreviousNode('F');

		ASSERT_EQ(newNode != nullptr, true);
		ASSERT_EQ(newNode->GetData(), 'F');
		ASSERT_EQ(newNode->GetPreviousNode() != nullptr, true);
		ASSERT_EQ(newNode->GetPreviousNode()->GetData(), 'D');
		ASSERT_EQ(newNode->GetNextNode() != nullptr, true);
		ASSERT_EQ(newNode->GetNextNode()->GetData(), 'E');

		ASSERT_EQ(node->GetPreviousNode() != nullptr, true);
		ASSERT_EQ(node->GetPreviousNode()->GetData(), 'F');
		FinalizeTest(node);
	}	

	static void InsertPreviousNodeTest_02() {
		Node* node = InitTest();
		node = MoveToFirst(node);
		Node* newNode = node->InsertPreviousNode('F');

		ASSERT_EQ(newNode != nullptr, true);
		ASSERT_EQ(newNode->GetData(), 'F');
		ASSERT_EQ(newNode->GetPreviousNode() == nullptr, true);
		ASSERT_EQ(newNode->GetNextNode() != nullptr, true);
		ASSERT_EQ(newNode->GetNextNode()->GetData(), 'A');

		ASSERT_EQ(node->GetPreviousNode() != nullptr, true);
		ASSERT_EQ(node->GetPreviousNode()->GetData(), 'F');
		FinalizeTest(node);
	}

	static void InsertNextNodeTest_01() {
		Node* node = InitTest();
		Node* newNode = node->InsertNextNode('G');
		ASSERT_EQ(newNode != nullptr, true);
		ASSERT_EQ(newNode->GetData(), 'G');
		ASSERT_EQ(newNode->GetPreviousNode() != nullptr, true);
		ASSERT_EQ(newNode->GetPreviousNode()->GetData(), 'E');
		ASSERT_EQ(newNode->GetNextNode() == nullptr, true);

		ASSERT_EQ(node->GetNextNode() != nullptr, true);
		ASSERT_EQ(node->GetNextNode()->GetData(), 'G');
		FinalizeTest(node);
	}

	static void InsertNextNodeTest_02() {
		Node* node = InitTest();
		node = MoveToFirst(node);
		Node* newNode = node->InsertNextNode('G');
		ASSERT_EQ(newNode != nullptr, true);
		ASSERT_EQ(newNode->GetData(), 'G');
		ASSERT_EQ(newNode->GetPreviousNode() != nullptr, true);
		ASSERT_EQ(newNode->GetPreviousNode()->GetData(), 'A');
		ASSERT_EQ(newNode->GetNextNode()->GetData(), 'B');

		ASSERT_EQ(node->GetNextNode() != nullptr, true);
		ASSERT_EQ(node->GetNextNode()->GetData(), 'G');
		FinalizeTest(node);
	}
public:
  static void RunTest() {
	  InsertPreviousNodeTest_01();
	  InsertPreviousNodeTest_02();
	  InsertNextNodeTest_01();
	  InsertNextNodeTest_02();
  }
};

class EraseNodeTestSuite
{
private:

	static void ErasePreviousNodeTest() {
		Node* node = InitTest();
		bool bRet = node->ErasePreviousNode();
		ASSERT_EQ(bRet, true);
		ASSERT_EQ(node->GetData(), 'E');
		ASSERT_EQ(node->GetPreviousNode()->GetData(), 'C');
		FinalizeTest(node);
	}

	static void ErasePreviousNodeTest_EXCEPTION() {
		Node* node = InitTest();
		node = MoveToFirst(node);
		bool bRet = node->ErasePreviousNode();
		ASSERT_EQ(bRet, false);
		ASSERT_EQ(node->GetData(), 'A');
		FinalizeTest(node);
	}

	static void EraseNextNodeTest() {
		Node* node = InitTest();
		node = MoveToFirst(node);
		bool bRet = node->EraseNextNode();
		ASSERT_EQ(bRet, true);
		ASSERT_EQ(node->GetData(), 'A');
		ASSERT_EQ(node->GetNextNode()->GetData(), 'C');
		FinalizeTest(node);
	}

	static void EraseNextNodeTest_EXCEPTION() {
		Node* node = InitTest();
		node = MoveToLast(node);
		bool bRet = node->EraseNextNode();
		ASSERT_EQ(bRet, false);
		ASSERT_EQ(node->GetData(), 'E');
		FinalizeTest(node);
	}
public:
	static void RunTest() {
		ErasePreviousNodeTest();
		ErasePreviousNodeTest_EXCEPTION();
		EraseNextNodeTest();
		EraseNextNodeTest_EXCEPTION();
	}
};

void NodeTest() {
  NodeConstructorTestSuite::RunTest();
  GetNodeTestSuite::RunTest();
  InsertNodeTestSuite::RunTest();
  EraseNodeTestSuite::RunTest();
}