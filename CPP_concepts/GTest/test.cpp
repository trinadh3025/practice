#include <gtest/gtest.h>
#include "fibonacci.h"
#include "evenodd.h"
#include "armstrong.h"

TEST(FibonacciTest, TestNthFibonacci){
	Fibonacci fib;
	EXPECT_EQ(fib.getNthFibonacci(0), 0);
	EXPECT_EQ(fib.getNthFibonacci(1), 1);
	EXPECT_EQ(fib.getNthFibonacci(5), 5);
	EXPECT_EQ(fib.getNthFibonacci(10), 55);

}

TEST(EvenOddTest, TestIsEven){
	EvenOdd eo;
	EXPECT_TRUE(eo.isEven(10));
	EXPECT_FALSE(eo.isEven(15));
}

TEST(EvenOddTest, TestIsOdd){
	EvenOdd eo;
	EXPECT_FALSE(eo.isEven(15));
	EXPECT_TRUE(eo.isEven(10));
}

TEST(ArmstrongTest, TestIsArmstrong){
	Armstrong arm;
	EXPECT_TRUE(arm.isArmstrong(153));
	EXPECT_TRUE(arm.isArmstrong(9474));
}

TEST(ArmstrongTest, TestIsNotArmstrong){
	Armstrong arm;
	EXPECT_FALSE(arm.isArmstrong(152));
	EXPECT_FALSE(arm.isArmstrong(122));
	EXPECT_FALSE(arm.isArmstrong(9473));
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


