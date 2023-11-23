#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <limits>


class Product{
private:
    std::mutex mtx;
public:
    int storage_size;
    std::vector<int> storage;
    Product(int storage_size) : storage_size(storage_size){}

    void send_to_storage(const int& val){
        std::lock_guard<std::mutex> lock(this->mtx);
        if (this->storage.size() < this->storage_size) {
            this->storage.push_back(val);
            std::cout << "The produceк thread with id " << std::this_thread::get_id() << " sent the product " << val << " to the storage" << std::endl;
        }
        else {
            std::cout << "The storage is full! Take something from the storage!" << std::endl;
        }
    }

    int take_from_storage(){
        std::lock_guard<std::mutex> lock(this->mtx);
        if (this->storage.empty()){
            std::cout << "The storage is empty!" << std::endl;
            return std::numeric_limits<int>::max();
        }
        else {
            int val = this->storage.back();
            this->storage.pop_back();
            std::cout << "The consumer thread with id " << std::this_thread::get_id() << " took the product " << val << " from the storage" << std::endl;
            return val;
        }
    }
};

Product myProduct(5);

int main()
{   
    std::cout << "Max storage size: " << myProduct.storage_size << std::endl;

    const int numThreads = 7;
    std::vector<std::thread> threads;

    for (int i = 1; i < numThreads; ++i) {
        threads.push_back(std::thread(&Product::send_to_storage, &myProduct, (i + 1) * 10));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "The storage consists next products: ";
    for (auto val : myProduct.storage){
        std::cout <<  val << " ";
    }
    std::cout << std::endl;

    std::vector<std::thread> new_threads;

    for (int i = 0; i < numThreads; ++i) {
        new_threads.push_back(std::thread(&Product::take_from_storage, &myProduct));
    }

    
    for (auto& thread : new_threads) {
        thread.join();
    }

    std::cout << "The storage consists next products: ";
    for (auto val : myProduct.storage){
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // std::thread producer_thread(&Product::send_to_storage, &myProduct, 23);
    // std::thread consumer_thread(&Product::take_from_storage, &myProduct);

    // producer_thread.join();
    // consumer_thread.join();
}


