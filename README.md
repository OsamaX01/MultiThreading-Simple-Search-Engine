# MultiThreading Simple Search Engine README

## Overview
This C++ program is a multi-threaded search engine that reads a set of files, counts occurrences of a specified character in each file, and provides statistics and a sorted list of files based on the character count.

## Usage
To use the program, follow these steps:

1. **Compile the program:**
```bash
   g++ code.cpp -o search_engine -pthread
```
2. Run the executable with the following command-line arguments:
```bash
./search_engine <numThreads> <character>
```

numThreads: Number of threads to be used for parallel processing.

character: The character to search for in the files.

Example: `./search_engine 4 a`

## Input Files

The program expects input from both standard input (`stdin`) and command-line arguments.

### Standard Input (stdin)

The program reads the following input from `stdin`:

- Number of files (`numFiles`).
- Threshold for character count (`threshold`).
- List of file names.

### Command-line Arguments

The program takes two command-line arguments:

1. Number of threads (`numThreads`).
2. Character to search for (`character`).

### Execution

The program utilizes multi-threading to process the files concurrently. It distributes the files among threads and counts the occurrences of the specified character in each file. The statistics are then aggregated, and the files are sorted based on the character count.

### Output

The program produces the following output:

1. Total number of occurrences of the specified character (`TotalFound`).
2. Number of files with character count above the threshold (`AboveThreshold`).
3. Number of files with character count equal to the threshold (`EqualsThreshold`).
4. Number of files with character count below the threshold (`BelowThreshold`).
5. Sorted list of files based on character count in the file (`out.txt`).

## Sample

### in.txt file 
```txt
4 2
inputFile1.txt
inputFile2.txt
inputFile3.txt
inputFile4.txt
```

### Files to search for (should be located in the same directory where your program is located)

inputFile1.txt:
```txt
abb aatbbarbbbc
abbb aabtbarbcc
ababbb arbbbabcc
```

inputFile3.txt:
```txt
baatbRbb 
```

inputFile2.txt:
```txt
1 r
@ a
```

inputFile4.txt:
```txt
Hello World!
```

### Sample Output (STDOUT terminal part): → Notice that some of threads’ output got reordered, that is fine!
```txt
Main --> Search Engine searching for (r) in 4 files, using 4 threads (with threshold=2)
TID0 --> Starting thread firstItem=0, lastItem=1
TID1 --> Starting thread firstItem=1, lastItem=2
TID2 --> Starting thread firstItem=2, lastItem=3
TID0 --> File: inputFile1.txt, (r) found=3
TID0 --> Ending thread firstItem=0, lastItem=1
TID3 --> Starting thread firstItem=3, lastItem=4
TID2 --> File: inputFile3.txt, (r) found=1
TID2 --> Ending thread firstItem=2, lastItem=3
TID1 --> File: inputFile2.txt, (r) found=0
TID1 --> Ending thread firstItem=1, lastItem=2
TID3 --> File: inputFile4.txt, (r) found=1
TID3 --> Ending thread firstItem=3, lastItem=4
Main --> TotalFound=5, AboveThreshold=1, EqualsThreshold=0, BelowThreshold=3
Main --> Sorted list of files in out.txt
```

### Sample Output (out.txt part):
```txt
Sorted list of files:
1.[ inputFile1.txt ] (found = 3)
2.[ inputFile4.txt ] (found = 1)
3.[ inputFile3.txt ] (found = 1)
4.[ inputFile2.txt ] (found = 0)
```

## Notes:
- The program uses mutual exclusion (mutex) to ensure thread safety for shared variables.
- If the number of threads is greater than the number of files, some threads may have no work to perform.
- The sorted list of files is written to the file named out.txt.
- Feel free to modify the code or incorporate it into your project as needed.
