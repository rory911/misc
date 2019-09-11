### Miscellaneous Algorithms

```
Coding examples in various languages.  Each is a simple, stand-alone file
to be compiled and executed.
```


### System Sort

```
Timing analyses of system sort routines in C++, Java, and Golang (see sortIntArray.cpp,
sortIntArray.java, sortIntSlice.go).  The first diagram primarily shows timing date for
the system sort routines in Java and Golang.  Time of execution in C++ is more easily
illustrated with the second diagram.

```

<img src="https://github.com/rory911/misc/blob/master/docs/SysSort1.JPG" alt="Figure 1.  System Sort v Quick v Shell" width="600" height="500"/>

### System Sort for C++

```
Isolated timing analyses of system sort in C++ (see sortIntArray.cpp only)
```

<img src="https://github.com/rory911/misc/blob/master/docs/SysSort2.JPG" alt="Figure 2.  System Sort v Quick v Shell" width="600" height="500"/>


### Opinion
```
The system sort routines are fairly efficient.  In the case of Java,  Arrays.sort is
recommended as a default.  For Golang, however, sort.Ints is currently discouraged
until more data proves otherwise, say newer versions, optimizations, etc.  In spite
of the overhead created by activation records, Quick Sort might be a good approach
for Golang programs.
```
