//  Timing of Arrays.sort vs Quick vs Shell
//
//  The system sort provided by Java is relatively fast.  Compare this to the
//  system sort provided by Golang, namely sort.Ints, which is disappointingly
//  slow (see sortIntSlice.go).  Shell and Quick each completed sorting in under
//  twice the time of their counterparts in Golang for the same size array, thus
//  there is merit to the claim that Arrays.sort is faster than sort.Ints for
//  sorting an array of integers initially in descending order.
//
//  Sample output:
// 
//      $ go run sortIntSlice.go                $ java sortIntArray.java
//      sort.Ints: 64.323ms                     Arrays.sort:  17 msec
//          Quick: 23.512ms                      Quick Sort:  39 msec
//          Shell: 31.044ms                      Shell Sort:  48 msec

import java.util.*;
import java.lang.*;

class sortIntArray
{
	public static void QuickSort(int a[], int lo, int hi) {
		if (lo >= hi)
			return;

		int idx = lo + ((hi - lo)>>1);
		int pivot = a[idx];
		int i = lo, j = hi;
		while (i <= j) {
			while (a[i] < pivot)
				i++;
			while (a[j] > pivot)
				j--;
			if (i <= j) {
				int temp = a[j];
				a[j] = a[i];
				a[i] = temp;
				i++;
				j--;
			}
		}
		
		if (lo < j)
			QuickSort(a, lo, j);

		if (hi > i)
			QuickSort(a, i, hi);
	}

	public static void ShellSort(int a[]) {
		for (int gap = a.length>>1; gap > 0; gap>>=1) {
			for (int i = gap; i < a.length; i++) {
				int j, temp;

				j = i;
	                        temp = a[i];
	                        for (; j >= gap && a[j-gap] > temp; j -= gap) {
	                                a[j] = a[j-gap];
	                        }
	                        a[j] = temp;
	                }
		}
	}

	public static boolean VerifyAscendingOrder(int a[]) {
		for(int i = 0; i < a.length - 1; i++) {
			if (a[i] > a[i + 1]) {
				System.out.println("failed");
				return (false);
			}
		}
		return (true);
	}

	public static void DescendingOrder(int a[]) {
		for (int i = 0, j = a.length; i < a.length; i++, j--)
			a[i] = j;
	}

	public static void main(String args[]) {
		long bgn, end;
		int[] a = new int [1000000];

		DescendingOrder(a);
		bgn = System.currentTimeMillis(); 
		Arrays.sort(a); 
		end = System.currentTimeMillis(); 
		if (VerifyAscendingOrder(a))
			System.out.println("Arrays.sort:  " + (end - bgn) + " msec");

		DescendingOrder(a);
		bgn = System.currentTimeMillis(); 
		QuickSort(a, 0, a.length - 1);
		end = System.currentTimeMillis(); 
		if (VerifyAscendingOrder(a))
			System.out.println(" Quick Sort:  " + (end - bgn) + " msec");

		DescendingOrder(a);
		bgn = System.currentTimeMillis(); 
		ShellSort(a);
		end = System.currentTimeMillis(); 
		if (VerifyAscendingOrder(a))
			System.out.println(" Shell Sort:  " + (end - bgn) + " msec");

	}
}
