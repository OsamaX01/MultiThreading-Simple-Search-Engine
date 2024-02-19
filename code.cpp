#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

char ch;
int threshold;
long long totalFound = 0;
int aboveThreshold = 0;
int equalsThreshold = 0;
int belowThreshold = 0;
mutex m1, m2, m3, m4;
vector<string> files;

void increaseTotalFound(int x) {
    m1.lock();
    totalFound += x;
    m1.unlock(); 
}

void increaseAboveThreshold() {
    m2.lock();
    aboveThreshold++; 
    m2.unlock();
}

void increaseEqualsThreshold() {
    m3.lock();
    equalsThreshold++; 
    m3.unlock();
}

void increaseBelowThreshold() {
    m4.lock();
    belowThreshold++; 
    m4.unlock();
}

void secrchInFiles(int threadId, int leftFile, int rightFile) {
    printf("TID%d --> Starting thread firstItem=%d, lastItem=%d\n", threadId, leftFile, rightFile + 1);
    for (int i = leftFile; i <= rightFile; i++) {
        ifstream curFile(files[i]);
        int count = 0;
        char c;
        while (curFile >> c) {
            if (c == ch) {
                count++;
            }
        }

        printf("TID%d --> File: %s, (%c) found=%d\n", threadId, files[i].c_str(), ch, count);
        
        increaseTotalFound(count);
        if (count < threshold) increaseBelowThreshold();
        else if (count == threshold) increaseEqualsThreshold();
        else increaseAboveThreshold();
    }

    printf("TID%d --> Ending thread firstItem=%d, lastItem=%d\n", threadId, leftFile, rightFile);
}

void distribute(int leftThread, int rightTread, int filesPerThread) {
    if (filesPerThread == 0) {
        for (int i = leftThread; i <= rightTread; i++) {
            printf("TID%d --> I have nothing to do\n", i);
        }
        return;
    }

    int numThreads = rightTread - leftThread + 1;
    thread threads[numThreads]; 

    for (int i = leftThread; i <= rightTread; i++) {
        threads[i] = thread(secrchInFiles, i, i * filesPerThread, i * filesPerThread + filesPerThread - 1);
    }
    
    for (int i = leftThread; i <= rightTread; i++) {
        threads[i].join();
    }

}

int main(int argc, char *argv[]) {
    freopen("in.txt", "r", stdin);
    // take input from stdin
    int numFiles, numThreads;
    cin >> numFiles >> threshold;
    files.resize(numFiles);
    for (int i = 0; i < numFiles; i++) {
        cin >> files[i];
    }

    // take arguments input
    if (argc == 3) {
        numThreads = atoi(argv[1]);
        ch = *argv[2];
    } else {
        printf("Please provide the number of threads and the character to search for\n");
        return 0;
    }

    printf("Main --> Search Engine searching for (%c) in %d files, using %d threads (with threshold=%d)\n", ch, numFiles, numThreads, threshold);

    if (numThreads > numFiles) {
        distribute(0, numFiles - 1, 1); 
        distribute(numFiles, numThreads - 1, 0);
    }
    else if (numThreads <= numFiles && numFiles % numThreads == 0) {
        int filesPerThread = numFiles / numThreads;
        distribute(0, numThreads - 1, filesPerThread); 
    }
    else {
        printf("Unexpected input :))\n");
        return 0;
    }

    return 0;
}