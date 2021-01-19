// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <shared_ptr.hpp>

class TestClass {
 public:
  int a;
};

TEST(testConstructor, pointNullptr) {
  SharedPtr <int> pointer;
  int* tmp = pointer.get();
  EXPECT_EQ(tmp, nullptr);
}

TEST(testOperator, boolTrueTest) {
  int* points = new int (609);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer2 = pointer;
  bool isPointer = pointer2;
  EXPECT_EQ(isPointer, true);
}

TEST(testOperator, arrowTest) {
  auto testClassPointer = new TestClass;
  testClassPointer -> a = 609;
  SharedPtr <TestClass> pointer(testClassPointer);
  EXPECT_EQ(pointer -> a, testClassPointer -> a);
}

TEST(testOperator, TestAsterisk) {
  int* points = new int (609);
  SharedPtr <int> pointer(points);
  EXPECT_EQ(609, *pointer);
}

TEST(testMethod, testGet) {
  int* points = nullptr;
  SharedPtr <int> pointer(points);
  int* tmp = pointer.get();
  EXPECT_EQ(tmp, nullptr);
}

TEST(testMethod, testGetInt) {
  int* points = new int (609);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer2 = pointer;
  EXPECT_EQ(pointer.get(), points);
}

TEST(testMethod, resetTest) {
  int* points = new int (609);
  SharedPtr <int> pointer(points);
  pointer.reset();
  EXPECT_EQ(pointer.get(), nullptr);
}

TEST(testMethod, resetTestElse){
  int* points = new int (609);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer2 = pointer;
  pointer.reset();
  EXPECT_EQ(pointer.get(), nullptr);
}

TEST (testMethod, resetTestPoint) {
  int* points = new int (609);
  int* points1 = new int (69);
  SharedPtr <int> pointer(points);
  pointer.reset(points1);
  EXPECT_EQ(pointer.get(), points1);
}

TEST (testMethod, resetTestPointElse) {
  int* points = new int (609);
  int* points1 = new int (69);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer2 = pointer;
  pointer.reset(points1);
  EXPECT_EQ(pointer.get(), points1);
}

TEST(testMethod, swapTest) {
  int* points = new int (609);
  int* points1 = new int (69);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer1(points1);
  pointer.swap(pointer1);
  EXPECT_EQ(pointer.get(), points1);
  EXPECT_EQ(pointer1.get(), points);
}

TEST(testOperator, equalityLvalueTest) {
  int* points = new int (609);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer2 = pointer;
  SharedPtr <int> pointer3 = pointer2;
  EXPECT_EQ(pointer3.get(), pointer.get());
}

TEST(testOperator, useCount){
  int* points = new int (609);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer2 = pointer;
  EXPECT_EQ(pointer.use_count(),2);
}

TEST(testConstructor,Move){
  int* points = new int (609);
  SharedPtr <int> pointer(points);
  SharedPtr <int> pointer1(move(pointer));
  SharedPtr <int> pointer3;
  pointer3 = std::move(pointer);
  SharedPtr <int> pointer4;
  pointer4 = pointer3;
  EXPECT_EQ(609, *pointer1.get());
  EXPECT_FALSE(pointer);
}

TEST(testIsMove, assignConstTest) {
  EXPECT_EQ(std::is_move_assignable<SharedPtr<int>>::value, true);
  EXPECT_EQ(std::is_move_constructible<SharedPtr<int>>::value, true);
  EXPECT_EQ(std::is_move_assignable<SharedPtr<double>>::value, true);
  EXPECT_EQ(std::is_move_constructible<SharedPtr<double>>::value,true);
  EXPECT_EQ(std::is_move_assignable<SharedPtr<TestClass>>::value,true);
  EXPECT_EQ(std::is_move_constructible<SharedPtr<TestClass>>::value,true);
}

TEST(testIsCopy, assignConstTest) {
  EXPECT_EQ(std::is_copy_assignable<SharedPtr<int>>::value, true);
  EXPECT_EQ(std::is_copy_constructible<SharedPtr<int>>::value, true);
  EXPECT_EQ(std::is_copy_assignable<SharedPtr<double>>::value, true);
  EXPECT_EQ(std::is_copy_constructible<SharedPtr<double>>::value,true);
  EXPECT_EQ(std::is_copy_assignable<SharedPtr<TestClass>>::value,true);
  EXPECT_EQ(std::is_copy_constructible<SharedPtr<TestClass>>::value,true);
}
