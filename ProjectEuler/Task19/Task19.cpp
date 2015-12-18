#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// You are given the following information, but you may prefer to do some research for yourself.
//
// 1 Jan 1900 was a Monday.
// Thirty days has September,
// April, June and November.
// All the rest have thirty - one,
// Saving February alone,
// Which has twenty - eight, rain or shine.
// And on leap years, twenty - nine.
// A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
//
// How many Sundays fell on the first of the month during the twentieth century(1 Jan 1901 to 31 Dec 2000) ?

int main(int argc, char **argv)
{
	printf("\nThe weekday when 'Task19' was created: %Iu\n", get_weekday(18, 12, 2015));

	size_t result = 0;

	for (size_t year = 1901; year <= 2000; ++year)
	{
		for (size_t month = 1; month <= 12; ++month)
		{
			if (get_weekday(1, month, year) == 7)
				result++;
		}
	}

	printf("\nResult: %Iu\n", result);

    return 0;
}