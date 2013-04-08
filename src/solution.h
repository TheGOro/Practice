/*
 * solution.h
 *
 *  Created on: 2013.04.07.
 *      Author: GOro
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_


#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

class Solution {
/*
 * Two Sum
 * Given an array of integers, find two numbers such that they add up to a specific target number.
 * The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
 *
 * You may assume that each input would have exactly one solution.
 *
 * Input: numbers={2, 7, 11, 15}, target=9
 * Output: index1=1, index2=2
 *
 * http://leetcode.com/onlinejudge#question_1
 */
public:
	vector<int> twoSum(vector<int> &numbers, int target) {
		vector<int> result;
		for (vector<int>::const_iterator i = numbers.begin(); i!= numbers.end(); ++i) {
			if (*i > target) continue;

			for (vector<int>::const_iterator j = i + 1; j != numbers.end(); ++j) {
				if (*i + *j == target) {
					result.push_back(i - numbers.begin() + 1);
					result.push_back(j - numbers.begin() + 1);
					break;
				}
			}
			if (result.size() != 0) break;
		}
		return result;
    }

/*
 * Reverse digits of an integer.
 *
 * Example1: x = 123, return 321
 * Example2: x = -123, return -321
 *
 * Have you thought about this?
 * Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!
 *
 * If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.
 *
 * Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?
 *
 * Throw an exception? Good, but what if throwing an exception is not an option? You would then have to re-design the function (ie, add an extra parameter).
 *
 * http://leetcode.com/onlinejudge#question_7
 */
    int reverse(int x) {
    	bool negative = false;
    	if (x < 0) {
    		negative = true;
    		x *= -1;
    	}
    	int result = 0;
    	int length = log10(x);
    	for (int i = 0; i <= length; ++i) {
    		result *= 10;
    		result += ((int) (x / pow(10.0, i))) % 10;
    	}
    	result *= negative ? -1 : 1;
    	return result;
    }

/*
 * Palindrome Number
 *
 * Determine whether an integer is a palindrome. Do this without extra space.
 *
 * Some hints:
 * Could negative integers be palindromes? (ie, -1)
 *
 * If you are thinking of converting the integer to string, note the restriction of using extra space.
 *
 * You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?
 *
 * There is a more generic way of solving this problem.
 *
 * http://leetcode.com/onlinejudge#question_9
 */
	bool isPalindrome(int x) {
		if (x < 0) return false;
		int length = log10(x) + 1;
		int checkrange = length >> 1;
		for (int i = 0; i < checkrange; ++i) {
			if ((((int) (x / pow(10.0, i))) % 10) !=
				(((int) (x / pow(10.0, length - i - 1))) % 10)) return false;
		}
		return true;
	}

/*
 * Valid Parentheses
 *
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 *
 * The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
 *
 * http://leetcode.com/onlinejudge#question_20
 */
    bool isValid(string s) {
        stack<char> brackets;
        for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
            if (*it == '(' || *it == '[' || *it == '{') {
                brackets.push(*it);
            } else if (*it == ')' || *it == ']' || *it == '}') {
                if (brackets.empty()) return false;
                if ((brackets.top() == '(' && *it == ')') ||
                    (brackets.top() == '[' && *it == ']') ||
                    (brackets.top() == '{' && *it == '}')) brackets.pop();
                else return false;
            }
        }
        if (brackets.empty()) return true;
        else return false;
    }

/*
 * Generate Parentheses
 *
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
 *
 * For example, given n = 3, a solution set is:
 *
 * "((()))", "(()())", "(())()", "()(())", "()()()"
 *
 * http://leetcode.com/onlinejudge#question_22
 */
private:
	void appendParenthesis(const string& prefix, const unsigned int opened, const unsigned int closed, const unsigned int n, vector<string>& result) {
		if (closed == opened && closed == n) {
			result.push_back(prefix);
			return;
		}
		if (opened > closed) {
			if (opened < n) {
				string left(prefix);
				left.append("(");
				appendParenthesis(left, opened + 1, closed, n, result);
			}
			string right(prefix);
			right.append(")");
			appendParenthesis(right, opened, closed + 1, n, result);
		} else {
			string left(prefix);
			left.append("(");
			appendParenthesis(left, opened + 1, closed, n, result);
		}

	}

public:
	vector<string> generateParenthesis(int n) {
		vector<string> result;
		appendParenthesis("(", 1, 0, n, result);
		return result;
	}

/*
 * Length of Last Word
 * Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.
 *
 * If the last word does not exist, return 0.
 *
 * Note: A word is defined as a character sequence consists of non-space characters only.
 *
 * For example,
 * Given s = "Hello World",
 * return 5.
 *
 * http://leetcode.com/onlinejudge#question_58
 */
    int lengthOfLastWord(const char* s) {
    	if (s == NULL) return 0;
        int count = 0;
        bool reset = false;
        for (int i = 0; s[i] != '\0'; ++i) {
        	if (s[i] != ' '  && reset) {
        		count = 1;
        		reset = false;
        	} else if (s[i] == ' ') {
        		reset = true;
        	} else {
        		++count;
        		reset = false;
        	}
        }
        return count;
    }
};

#endif
