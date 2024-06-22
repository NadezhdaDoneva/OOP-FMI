#pragma once
char getCharFromDigit(int digit)
{
	if (digit < 0 || digit > 9)
		return '\0';
	return digit + '0';
}

unsigned getNumberLength(unsigned int n)
{
	if (n == 0)
		return 1;
	unsigned int res = 0;

	while (n != 0)
	{
		res++;
		n /= 10;
	}
	return res;
}

const MyString& toString(unsigned int n)
{
	unsigned int len = getNumberLength(n);
	MyString str;
	for (int i = len - 1; i >= 0; i--)
	{
		str[i] = getCharFromDigit(n % 10);
		n /= 10;
	}
	str[len] = '\0';
	return str;
}
