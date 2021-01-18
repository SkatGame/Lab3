// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include <header.hpp>

class TestClass {
 public:
  int a;
};

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(testConstructor, pointNullptr) {
  SharedPtr <int> pointer;
  int* tmp = pointer.get();
  EXPECT_EQ(tmp, nullptr);
}

TEST(testConstructor, pointIntNullptr) {
  int *points = new int (22);
  SharedPtr <int> pointer(points);
  int* tmp = pointer.get();
  EXPECT_EQ(tmp, points);
}

TEST(testConstructor, rvalueTest) {
  int *points = new int (922);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer2 = pointer;
  SharedPtr <int> pointer3(std::move(pointer));
  EXPECT_EQ(pointer3.use_count(), 2);
}

TEST(testMethod, testGet) {
  int *points = nullptr;
  SharedPtr <int> pointer(points);
  int* tmp = pointer.get();
  EXPECT_EQ(tmp, nullptr);
}

TEST(testMethod, testGetInt) {
  int *points = new int (827);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer2 = pointer;
  EXPECT_EQ(pointer.get(), points);
}

TEST(testMethod, resetTest) {
  int  *points = new int (922);
  SharedPtr <int> pointer(points);
  pointer.reset();
  EXPECT_EQ(pointer.get(), nullptr);
}

TEST (testMethod, resetTestPoint) {
  int *points = new int (922);
  int *points1 = new int (279);
  SharedPtr <int> pointer(points);
  pointer.reset(points1);
  EXPECT_EQ(pointer.get(), points1);
}

TEST(testMethod, swapTest) {
  int *points = new int (922);
  int *points1 = new int (279);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer1(points1);
  pointer.swap(pointer1);
  EXPECT_EQ(pointer.get(), points1);
  EXPECT_EQ(pointer1.get(), points);
}

TEST(testOperator, boolTest) {
  int *points = new int (227);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer2 = pointer;
  bool is_pointer = pointer2;
  EXPECT_EQ(is_pointer, true);
}

TEST(testOperator, arrowTest) {
  auto testClassPointer = new TestClass;
  testClassPointer-> a = 922;
  SharedPtr <TestClass> pointer(testClassPointer);
  EXPECT_EQ(pointer-> a, testClassPointer->a);
}

TEST(testOperator, equalityLvalueTest) {
  int *points = new int (922);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer2;
  SharedPtr <int> pointer3 = pointer2 = pointer;
  EXPECT_EQ(pointer3.get(), pointer.get());
}

TEST(testIsMove, assignConstTest) {
  EXPECT_EQ(std::is_move_assignable<SharedPtr<int>>::value, true);//proveryaet yavlyatsya li tip prisvaemim pri move
  EXPECT_EQ(std::is_move_constructible<SharedPtr<int>>::value, true);//proveryaet imeet li tip constructor move
  EXPECT_EQ(std::is_move_assignable<SharedPtr<double>>::value, true);
  EXPECT_EQ(std::is_move_constructible<SharedPtr<double>>::value,true);
  EXPECT_EQ(std::is_move_assignable<SharedPtr<TestClass>>::value,true);
  EXPECT_EQ(std::is_move_constructible<SharedPtr<TestClass>>::value,true);
}

TEST(testIsCopy, assignConstTest) {
  EXPECT_EQ(std::is_copy_assignable<SharedPtr<int>>::value, true);//proveryaet yavlyatsya li tip prisvaemim pri copy
  EXPECT_EQ(std::is_copy_constructible<SharedPtr<int>>::value, true);//proveryaet imeet li tip constructor copy
  EXPECT_EQ(std::is_copy_assignable<SharedPtr<double>>::value, true);
  EXPECT_EQ(std::is_copy_constructible<SharedPtr<double>>::value,true);
  EXPECT_EQ(std::is_copy_assignable<SharedPtr<TestClass>>::value,true);
  EXPECT_EQ(std::is_copy_constructible<SharedPtr<TestClass>>::value,true);
}