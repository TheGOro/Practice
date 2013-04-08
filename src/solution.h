/*
 * solution.h
 *
 *  Created on: 2013.04.07.
 *      Author: GOro
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_


#include <vector>
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
public:
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
};

#endif
