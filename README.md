### Miscellaneous Algorithms

```
Coding examples in various languages.  Each is a simple, independent file to be compiled
and run as a stand-alone executable.  

For Golang subdirectories, the README file contains instructions for downloading, building,
and running modules.  In some cases, knowledge of Postman, pdpMyAdmin, SQL, etc., will be
required to correctly exercise the code.

The remainder of this document examines the default system sort characteristics for C++,
Java, and Golang.
```


### System Sort for Java and Golang

```
Timing analyses of system sort routines in C++, Java, and Golang (see sortIntArray.cpp,
sortIntArray.java, sortIntSlice.go) are presented.  The first diagram primarily shows timing
data for the system sort routines in Java and Golang.  Time of execution in C++ is more easily
illustrated with the second diagram.

```

<img src="https://github.com/rory911/misc/blob/master/docs/SysSort1.JPG" alt="Figure 1.  System Sort v Quick v Shell" width="600" height="500"/>

### System Sort for C++

```
Isolated timing analyses of system sort in C++ (see sortIntArray.cpp only)
```

<img src="https://github.com/rory911/misc/blob/master/docs/SysSort2.JPG" alt="Figure 2.  System Sort v Quick v Shell" width="550" height="500"/>


### Opinion
```
The system sort routines are fairly efficient.  In the case of Java,  Arrays.sort is
recommended as a default.  For Golang, however, sort.Ints is currently discouraged
until more data proves otherwise, say newer versions, optimizations, etc.  In spite
of the overhead created by activation records, Quick Sort might still be a good approach
for Golang programs.
```
