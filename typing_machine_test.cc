// Copyright 2018 Minkyu Jo

#include "typing_machine.h"
#include "typing_machine_test.h"
#include "test.h"


static void InitTest(TypingMachine& tm) {
	tm.TypeKey('A');
	tm.TypeKey('B');
	tm.TypeKey('C');
	tm.TypeKey('D');
	tm.TypeKey('E');
}

class TmConstructorTestSuite
{
private:
  static void BarSeparatorTest() {
    TypingMachine tm;
    ASSERT_EQ(tm.Print('|'), std::string("|"));
  }

  static void BarSeparatorTest_Empty() {
	  TypingMachine tm;
	  ASSERT_EQ(tm.Print('\0'), std::string(""));
  }

public:
  static void RunTest() {
    BarSeparatorTest();
	BarSeparatorTest_Empty();
  }
};


class TmTypeEraseTestSuite
{
private:
	static void TypeTest() {
		TypingMachine tm;
		InitTest(tm);
		ASSERT_EQ(tm.Print('\0'), std::string("ABCDE"));
	}

	static void TypeTest_MAX() {
		TypingMachine tm;
		for (int i = 0; i < 110; i++)
		{
			tm.TypeKey('A');
		}
		ASSERT_EQ(tm.Print('\0'), std::string("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"));
	}

	static void EraseTest() {
		TypingMachine tm;
		InitTest(tm);
		tm.EraseKey();
		ASSERT_EQ(tm.Print('\0'), std::string("ABCD"));
	}

	static void MoveAndEraseTest() {
		TypingMachine tm;
		InitTest(tm);
		tm.LeftKey();
		tm.LeftKey();
		tm.EraseKey();
		ASSERT_EQ(tm.Print('\0'), std::string("ABDE"));
	}

	static void EraseTest_Exception() {
		TypingMachine tm;
		InitTest(tm);
		tm.HomeKey();
		tm.EraseKey();
		ASSERT_EQ(tm.Print('\0'), std::string("ABCDE"));
	}

public:
	static void RunTest() {
		TypeTest();
		TypeTest_MAX();
		EraseTest();
		MoveAndEraseTest();
		EraseTest_Exception();
	}
};

class TmMovePointerTestSuite
{
private:
	static void HomeKeyTest() {
		TypingMachine tm;
		InitTest(tm);
		tm.HomeKey();
		ASSERT_EQ(tm.Print('|'), std::string("|ABCDE"));
	}
	static void EndKeyTest() {
		TypingMachine tm;
		InitTest(tm);
		tm.HomeKey();
		tm.EndKey();
		ASSERT_EQ(tm.Print('|'), std::string("ABCDE|"));
	}
	static void LeftKeyTest_01() {
		TypingMachine tm;
		InitTest(tm);
		tm.LeftKey();
		ASSERT_EQ(tm.Print('|'), std::string("ABCD|E"));
	}
	static void LeftKeyTest_02() {
		TypingMachine tm;
		InitTest(tm);
		tm.HomeKey();
		tm.LeftKey();
		ASSERT_EQ(tm.Print('|'), std::string("|ABCDE"));
	}
	static void RightKeyTest_01() {
		TypingMachine tm;
		InitTest(tm);
		tm.HomeKey();
		tm.RightKey();
		ASSERT_EQ(tm.Print('|'), std::string("A|BCDE"));
	}
	static void RightKeyTest_02() {
		TypingMachine tm;
		InitTest(tm);
		tm.EndKey();
		tm.RightKey();
		ASSERT_EQ(tm.Print('|'), std::string("ABCDE|"));
	}
public:
  static void RunTest() {
	  HomeKeyTest();
	  EndKeyTest();
	  LeftKeyTest_01();
	  LeftKeyTest_02();
	  RightKeyTest_01();
	  RightKeyTest_02();
  }
};

void TypingMachineTest() {
  TmConstructorTestSuite::RunTest();
  TmTypeEraseTestSuite::RunTest();
  TmMovePointerTestSuite::RunTest();
  // add more..
}