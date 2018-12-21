//
// Created by keldon on 21/12/18.
//

#include <gtest/gtest.h>
#include <emcee/literal.hpp>


TEST(Literal, CreatesLiteral) {
  auto l = LITERAL("123456789");
  ASSERT_EQ(9, l.length());
}

TEST(Literal, FailsCompilationOnFalseLiteralIfUncommented) {
//  const char str[100] = "false_literal";
//  auto l = LITERAL(str);
  ASSERT_TRUE(true);
}

TEST(Literal, CorrectlyComparesEqualLengthedLiterals) {
  auto lower = LITERAL("aaa");
  auto higher = LITERAL("bbb");
  ASSERT_TRUE(lower < higher);
}

TEST(Literal, CorrectlyComparesDifferentlyLengthedLiterals) {
  auto shorter = LITERAL("12345");
  auto longer = LITERAL("123456");
  ASSERT_TRUE(shorter < longer);
}

TEST(Literal, CorrectlyComparesEqualLiterals) {
  auto l1 = LITERAL("abc");
  auto l2 = LITERAL("abc");
  ASSERT_EQ(l1, l2);
}