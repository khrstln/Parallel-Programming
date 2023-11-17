#include <iostream>
#include <windows.h>
#include <vector>
#include <thread>
#include <cstdlib>
#include <ctime>

struct ThreadData {
    int* MatrixRow;
    int RowNumber;
    int Size;
    int seed;
    int product;
};

DWORD WINAPI ThreadProc(LPVOID lpParameter) {
    ThreadData* pData = reinterpret_cast<ThreadData*>(lpParameter);
    std::srand(pData->seed);
    for (int i = 0; i < pData->Size; ++i)
    {
        pData->MatrixRow[i] = rand() % 10 + 1;
    };



    pData->product = 1;
    for (int i = 0; i < pData->Size; i += 2) {
        pData->product *= pData->MatrixRow[i];
    }

    return 0;
}


int main() {
    int MatrixSize = 6;
    
    int Matrix[MatrixSize][MatrixSize];

    std::vector<HANDLE> threadHandles(MatrixSize);
    std::vector<ThreadData> threadData(MatrixSize);

    for (int i = 0; i < MatrixSize; ++i) {
        threadData[i].MatrixRow = Matrix[i];
        threadData[i].RowNumber = i;
        threadData[i].Size = MatrixSize;
        threadData[i].seed = rand();

        threadHandles[i] = CreateThread(
            nullptr,               
            0,                     
            ThreadProc,            
            &threadData[i],        
            0,                    
            nullptr                
        );

        if (threadHandles[i] == nullptr) {
            std::cerr << "Error creating thread " << i << std::endl;
            return 1;
        }
    }

    WaitForMultipleObjects(MatrixSize, threadHandles.data(), TRUE, INFINITE);


    for (int i = 0; i < MatrixSize; ++i) {
        std::cout << "Row " << i << ": ";
        for (int j = 0; j < MatrixSize; ++j) {
            std::cout << Matrix[i][j] << " ";
        }
        std::cout << "| Product of odd elements: " << threadData[i].product << std::endl;
    }

    for (int i = 0; i < MatrixSize; ++i) {
        CloseHandle(threadHandles[i]);
    }

    return 0;

}
