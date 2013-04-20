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
#include <limits>
#include <bitset>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
/*
 * Two Sum
 *
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
 * Add Two Numbers
 *
 * You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 *
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 *
 * http://leetcode.com/onlinejudge#question_2
 */
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		int carry = 0;
		ListNode *result, *p = NULL;
		while (l1 != NULL || l2 != NULL || carry > 0) {
			if (p == NULL) {
				p = new ListNode(0);
				result = p;
			} else {
				p->next = new ListNode(0);
				p = p->next;
			}
			p->val += carry;
			p->val += l1 != NULL ? l1->val : 0;
			p->val += l2 != NULL ? l2->val : 0;
			carry = p->val / 10;
			p->val = p->val % 10;
			l1 = l1 != NULL ? l1->next : l1;
			l2 = l2 != NULL ? l2->next : l2;
		}
		return result;
	}

/*
 * ZigZag Conversion
 *
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)
 *
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * And then read line by line: "PAHNAPLSIIGYIR"
 * Write the code that will take a string and make this conversion given a number of rows:
 *
 * string convert(string text, int nRows);
 * convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
 *
 * http://leetcode.com/onlinejudge#question_6
 */
	string convert(string s, int nRows) {
		int len = s.length();
		if (nRows <= 1 || nRows >= len) return s;
		string result;
		result.resize(len, ' ');
		int period = nRows * 2 - 2;
		int position[nRows];
		position[0] = 0;
		for (int i = 0; i < nRows - 1; ++i) {
			int left = len >= i + 1 ? floor((len - i - 1) / period) + 1 : 0;
			int right = len >= period + 1 - i && i > 0 ? floor((len - (period + 1 - i)) / period) + 1 : 0;
			position[i + 1] = position[i] + left + right;
		}
		for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
			int i = it - s.begin();
			int phase = i % period;
			int row = phase >= nRows -  1? period - phase : phase;
			result[position[row]++] = *it;
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
			result += ((int) (x / ::pow(10.0, i))) % 10;
		}
		result *= negative ? -1 : 1;
		return result;
	}

/*
 * String to Integer (atoi)
 *
 * Implement atoi to convert a string to an integer.
 *
 * Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.
 *
 * Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.
 *
 * http://leetcode.com/onlinejudge#question_8
 */
	// Not valid and not complete solution!
	int atoi(const char *str) {
		int result = 0;
		int prev = 0;
		bool begin = false;
		int sign = 0;
		for (int i = 0; str[i] != '\0'; ++i) {
			if (!begin && str[i] == 32) {
				continue;
			} else if (!begin && sign == 0 && (str[i] == 43 || str[i] == 45)) {
				begin = true;
				sign = str[i] == 45 ? -1 : 1;
			} else if (str[i] >= 48 && str[i] <= 57 ) {
				if (begin == false && sign == 0) {
					begin = true;
					sign = 1;
				}
				result *= 10;
				result += str[i] - 48;
				if ((prev > 0 && result < 0) || (prev < 0 && result > 0)) {
					if (prev > 0) return sign * numeric_limits<int>::min();
					else return sign * numeric_limits<int>::min();
				}
				prev = result;
			} else {
				break;
			}
		}
		result *= sign;
		if (result >= numeric_limits<int>::max()) return numeric_limits<int>::max();
		else if (result <= numeric_limits<int>::min()) return numeric_limits<int>::min();
		else return result;
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
			if ((((int) (x / ::pow(10.0, i))) % 10) !=
				(((int) (x / ::pow(10.0, length - i - 1))) % 10)) return false;
		}
		return true;
	}

/*
 * Integer to Roman
 *
 * Given an integer, convert it to a roman numeral.
 *
 * Input is guaranteed to be within the range from 1 to 3999.
 *
 * http://leetcode.com/onlinejudge#question_12
 */
	string intToRoman(int num) {
		static char romans[4][2] = {{'I','V'},{'X','L'},{'C','D'},{'M','\0'}};
		string result;
		int digits = log10(num);
		for (int i = digits; i >= 0; --i) {
			int v = ((int) (num / ::pow(10.0, i))) % 10;
			if (v == 4 || v == 9) {
				result.push_back(romans[i][0]);
				result.push_back(romans[v == 4 ? i : i + 1][v == 4 ? 1 : 0]);
			} else {
				if (v > 4) result.push_back(romans[i][1]);
				for (int j = v > 4 ? v - 5 : v; j > 0; --j) result.push_back(romans[i][0]);
			}
		}
		return result;
	}

/*
 * Roman to Integer
 *
 * Given a roman numeral, convert it to an integer.
 *
 * Input is guaranteed to be within the range from 1 to 3999.
 *
 * http://leetcode.com/onlinejudge#question_13
 */
	int romanToInt(string s) {
		static char romans[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
		static int values[] = {1, 5, 10, 50, 100, 500, 1000};
		int highest = 0;
		int result = 0;
		for (string::const_reverse_iterator it = s.rbegin(); it != s.rend(); ++it) {
			for (int i = 0; i < (int) sizeof romans; ++i) {
				if (*it == romans[i]) {
					if (i < highest) {
						result -= values[i];
					} else {
						result += values[i];
					}
					highest = highest < i ? i : highest;
					break;
				}
			}
		}
		return result;
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
 * Swap Nodes in Pairs
 *
 * Given a linked list, swap every two adjacent nodes and return its head.
 *
 * For example,
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 *
 * Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
 *
 * http://leetcode.com/onlinejudge#question_24
 */
	ListNode *swapPairs(ListNode *head) {
		ListNode *first, *i = head;
		ListNode *j, *k, *l = NULL;
		while (i != NULL) {
			j = i->next;
			if (j == NULL) break;
			k = j->next;
			if (k == NULL) l = NULL;
			else l = k->next;
			j->next = i;
			i->next = l == NULL ? k : l;
			if (i == head) first = j;
			i = k;
		}
		return first;
	}
/*
 * Valid Sudoku
 * Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
 *
 * The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
 *
 * http://leetcode.com/onlinejudge#question_36
 */
	bool isValidSudoku(vector<vector<char> > &board) {
		int checkTable[8] = {0}; // Bitset is not available
		for (vector<vector<char> >::const_iterator i = board.begin(); i != board.end(); ++i) {
			for (vector<char>::const_iterator j = i->begin(); j != i->end(); ++j) {
				if (*j == '.') continue;
				else {
					int value = *j - 48;
					int row = i - board.begin();
					int column = j - i->begin();
					int positions[3] = {
						row * 9 + value - 1,
						81 + column * 9 + value - 1,
						162 + (((int) (floor(row / 3))) * 3  + ((int) (floor(column / 3)))) * 9 + value - 1
					};
					for (int v = 0; v < 3; ++v) {
						int part = floor(positions[v] / 32);
						int shift = positions[v] % 32;

						if ((checkTable[part] >> shift) & 1) return false; 	// Test
						checkTable[part] = checkTable[part] | (1 << shift); // Set
					}
				}
			}
		}
		return true;
	}

/*
 * Pow(x, n)
 *
 * Implement pow(x, n).
 *
 * http://leetcode.com/onlinejudge#question_50
 */
	double pow(double x, int n) {
		double result = 1.0;
		int highestBit = (sizeof(int) << 3) - 1;
		if (n < 0) {
			n *= -1;
			x = 1 / x;
		}
		for (int i = highestBit; !((n >> i) & 1) && i > 0; --i) --highestBit;
		for (int i = 0; i <= highestBit; ++i) {
			if ((n >> i) & 1) result *= x;
			x *= x;
		}
		return result;
	}

/*
 * Length of Last Word
 *
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

/*
 * Add Binary
 *
 * Given two binary strings, return their sum (also a binary string).
 *
 * For example,
 * a = "11"
 * b = "1"
 * Return "100".
 *
 * http://leetcode.com/onlinejudge#question_67
 */
private:
	string& prepend(string& target, const char value) {
		target.insert(0, 1, value);
		return target;
	}
	bool truth(string& cont, string::const_iterator& it) {
		if (it <= cont.begin() - 1) {
			return false;
		} else if (*it == '0') {
			return false;
		} else {
			return true;
		}
	}
public:
	string addBinary(string a, string b) {
		bool carry = false;
		string result("");
		for (string::const_iterator i = a.end() - 1, j = b.end() - 1;
			i != a.begin() - 1 || j != b.begin() - 1;
			i = i != a.begin() - 1 ? --i : i, j = j != b.begin() - 1 ? --j : j)
		{
			bool bi = truth(a, i);
			bool bj = truth(b, j);
			if (bi && bj) {
				if (carry) {
					prepend(result, '1');
				} else {
					prepend(result, '0');
					carry = true;
				}
			} else if (!bi && !bj) {
				if (carry) {
					prepend(result, '1');
					carry = false;
				} else {
					prepend(result, '0');
				}
			} else {
				if (carry) {
					prepend(result, '0');
				} else {
					prepend(result, '1');
				}
			}
		}
		if (carry) prepend(result, '1');
		return result;
	}

/*
 * Search a 2D Matrix
 *
 * Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
 *
 * Integers in each row are sorted from left to right.
 * The first integer of each row is greater than the last integer of the previous row.
 * For example,
 *
 * Consider the following matrix:
 *
 * [
 *  [1,   3,  5,  7],
 *  [10, 11, 16, 20],
 *  [23, 30, 34, 50]
 * ]
 * Given target = 3, return true.
 *
 * http://leetcode.com/onlinejudge#question_74
 */
	bool searchMatrix(vector<vector<int> > &matrix, int target) {
		int top = 0;
		int bottom = matrix.size() - 1;
		while (top <= bottom) {
			int sum = top + bottom;
			int i = sum & 1 ? (sum >> 1) + 1 : sum >> 1;
			vector<int>& row = matrix[i];
			int low = row.front();
			int high = row.back();
			if (target == low || target == high) {
				return true;
			} else if (target > low && target < high) {
				int left = 0;
				int right = row.size() - 1;
				while (left <= right) {
					sum = left + right;
					i = sum & 1 ? (sum >> 1) + 1 : sum >> 1;
					if (row[i] == target) {
						return true;
					} else if (target < row[i]) {
						right = i - 1;
					} else if (target > row[i]) {
						left = i + 1;
					}
				}
				return false;
			} else if (target < low) {
				bottom = i - 1;
			} else if (target > high) {
				top = i + 1;
			}
		}
		return false;
	}

/*
 * Interleaving String
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
 *
 * For example,
 * Given:
 * s1 = "aabcc",
 * s2 = "dbbca",
 *
 * When s3 = "aadbbcbcac", return true.
 * When s3 = "aadbbbaccc", return false.
 *
 * http://leetcode.com/onlinejudge#question_97
 */
	// Work in progress
private:
	unsigned int s1len;
	unsigned int s2len;
	unsigned int s3len;

	bool constructStep(const string& s1, unsigned int p1, const string& s2, unsigned int p2, const string& s3) {
		if (p1 + p2 == s3len && p1 == s1len && p2 == s2len) return true;
		return (s1len > p1 && s1[p1] == s3[p1 + p2] ? constructStep(s1, p1 + 1, s2, p2, s3) : false) ||
		(s2len > p2 && s2[p2] == s3[p1 + p2] ? constructStep(s1, p1, s2, p2 + 1, s3) : false);
	}
public:
	bool isInterleave(string s1, string s2, string s3) {
		s1len = s1.length();
		s2len = s2.length();
		s3len = s3.length();
		if (s3len != s2len + s1len) return false;
		return constructStep(s1, 0, s2, 0, s3);
	}

/*
 * Same Tree
 * Given two binary trees, write a function to check if they are equal or not.
 *
 * Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
 *
 * http://leetcode.com/onlinejudge#question_100
 */
	bool isSameTree(TreeNode *p, TreeNode *q) {
		if (p == NULL && q == NULL) return true;
		if (p == NULL || q == NULL) return false;
		if (p->val != q->val) return false;
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}

/*
 * Maximum Depth of Binary Tree
 * Given a binary tree, find its maximum depth.
 *
 * The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
 *
 * http://leetcode.com/onlinejudge#question_104
 */
	int maxDepth(TreeNode *root) {
		if (root == NULL) return 0;
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);
		return 1 + (left > right ? left : right);
	}

/*
 * Minimum Depth of Binary Tree
 * Given a binary tree, find its minimum depth.
 *
 * The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
 *
 * http://leetcode.com/onlinejudge#question_111
 */
	int minDepth(TreeNode *root) {
		if (root == NULL) return 0;
		else if (root->left == NULL) return 1 + minDepth(root->right);
		else if (root->right == NULL) return 1 + minDepth(root->left);
		int left = minDepth(root->left);
		int right = minDepth(root->right);
		return 1 + (left < right ? left : right);
	}
};

#endif
