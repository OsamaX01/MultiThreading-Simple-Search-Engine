#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

vector<string> files;
char ch;
int threshold;

void distribute(int leftThread, int rightTread, int filesPerThread) {

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