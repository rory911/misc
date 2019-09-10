### Miscellaneous Algorithms

```
Coding examples in various languages (mostly C language)
```


### System Sort

```
Timing analyses of system sort routines in C++, Java, and Golang.
(See sortIntArray.cpp, sortIntArray.java, sortIntSlice.go)

The first diagram primarily shows timing date for the system
sort routines in Java and Golang.  The C++ execution is better
illustrated the second diagram.

```

![Figure 1.  System Sort v Quick v Shell for C++, Java, Golang](https://github.com/rory911/misc/blob/master/docs/SysSort1.JPG)


### System Sort for C++

```
Isolated timing analyses of system sort in C++
(See sortIntArray.cpp)
```

![Figure 2.  System Sort v Quick v Shell for C++](https://github.com/rory911/misc/blob/master/docs/SysSort2.JPG)


### Opinion
```
The system sort routines are fairly efficient.  In the case
of Java,  Arrays.sort is recommended as a default.  For Golang,
however, sort.Ints is currently discouraged until more data
proves otherwise, say newer versions, optimizations, etc.
In spite of the overhead created by activation records,
Quick Sort seems to be a good approach for Golang programs.
```
