#include <string>
#include <vector>

#pragma once

using namespace std;

const double pi = 3.141592653589793238463;

double toDegrees(double radians)
{
	return radians * ((double)180.0 / pi);
}
bool areSame(string ss1, string ss2)
{
	return ss1.compare(ss2) == 0 ? true : false;
}

string toLower(string ss)
{
	string ss1 = "";
	for (int i = 0; i < ss.length(); i++)
	{
		ss1 += (char)tolower(ss[i]);
	}
	return ss1;
}

bool hasThisChars(string ss, vector<char> collection)
{
	for (int i = 0; i < ss.length(); i++)
	{
		for (auto j= 0; j < collection.size(); j++)
		{
			if (ss[i] == (char) collection[j])
			{
				return true;
			}
		}
	}
	return false;
}

bool isEmptyOrWhiteSpaces(string ss)
{
	if (areSame(ss, "")) return true;
	bool flag = true;
	for (int i = 0; i < ss.length(); i++)
	{
		if (ss[i] == ' ') continue;
		else { flag = false; break;  }
	}
	return flag;
}

bool isEmpty(string ss)
{
	return areSame(ss, "") ? true : false;
}

double pythagorasC(double A, double B)
{
	return sqrt(pow(A, 2) + pow(B, 2));
}

double pythagorasA(double C, double B)
{
	return sqrt(pow(C, 2) - pow(B, 2));
}