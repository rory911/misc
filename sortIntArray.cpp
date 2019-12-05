//  Timing of std::array.sort vs Quick vs Shell
//
//  Sorting routines in C++ are expectedly quick because of the absence of portable
//  runtime environments such as RJE for Java and runtime for Golang.  Therefore, it
//  is an apples and oranges comparison.  Nevertheless, the system sort can be tested
//  against other common sorts such as Quick sort and Shell sort to get a rough idea
//  of effiency.  Although comparisons are unfair, array sizes and descending order
//  are identical with sortIntSlice.go and sortIntArray.java for consistency.
//
//  Sample output:
//
//	$ sortArrayInt
//	 std::sort:  0.0609172 msec
//	quick_sort:  0.0393171 msec
//	shell_sort:  0.0734051 msec

#include <iostream>
// Array template
#include <array>
#include <algorithm>
// High resolution timer
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

void
quick_sort(int *bgn, int *end)
{
	if (bgn >= end - 1)
		return;

	int *i = bgn;
	int *pivot = bgn + ((end - bgn)>>1);
	int *j = end;
	
	while (i < j) {
		while (*i < *pivot)
			++i;
		while (*j > *pivot) 
			--j;
		if (i < j) {
			int temp = *j;
			*j = *i;
			*i = temp;
			i++;
			j--;
		}
	}

	quick_sort(bgn, i);
	quick_sort(i + 1, end);
}

void
shell_sort(int *bgn, int *end)
{
	for (int *gap = bgn + ((end - bgn)>>1); gap > bgn; gap = bgn + ((gap - bgn)>>1)) {
		for (int *ip = gap; ip < end; ip++) {
			int *jp = ip, temp = *ip;

			for (int *kp = bgn + (jp - gap);
			    jp >= gap && *kp > temp;
			    jp = kp, kp = bgn + (kp - gap)) {
				*jp = *kp;
			}
			*jp = temp;
		}
	}
}

bool
verify_sort(const auto a, string msg)
{
	cout << msg;
	for(int i = 0; i < a.size() - 1; ++i) {
		if (a[i] > a[i + 1]) {
			cout << "Failed\n";
			return (false);
		}
	}
	return (true);
}

void
descending_order(auto &a)
{
	for (int i = 0, j = a.size(); i < a.size(); i++, j--) 
		a[i] = j;
}

void
hi_res_timer(void (*f)(int *, int *), auto &a, string msg)
{
	using namespace std::chrono;

	high_resolution_clock::time_point t1, t2;
	duration<double> time_span;

	descending_order(a);
	t1 = high_resolution_clock::now();
	f(a.begin(), a.end());
	t2 = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(t2 - t1);
	if (verify_sort(a, msg))
		cout << time_span.count() << " msec\n";
}

int
main()
{
	array <int, 1000000> a;

	hi_res_timer(sort, a, " std::sort:  ");
	hi_res_timer(quick_sort, a, "quick_sort:  ");
	hi_res_timer(shell_sort, a, "shell_sort:  ");
}
