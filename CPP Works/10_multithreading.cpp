/*
Bu kodun çalıştırılması sonucunda, üretici threadlerin ürettiği verileri tüketici threadlerin tükettiğini göreceksiniz.
Threadler arasındaki eşzamanlılık ve veri paylaşımı, mutex ve koşul değişkenleri kullanılarak yapılır.
Bu kod, multithreadlerin güvenli bir şekilde veri paylaşımını nasıl yaptığını ve eşzamanlı işlemlerin nasıl yönetilebileceğini gösteren bir örnektir. 
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

const int NUM_PRODUCERS = 3;
const int NUM_CONSUMERS = 2;
const int MAX_QUEUE_SIZE = 10;
const int MAX_ITEMS = 20;

std::queue<int> dataQueue;
std::mutex mtx;
std::condition_variable cv_producer, cv_consumer;

bool isDone = false;

void producerFunction(int id) {
    for (int i = 0; i < MAX_ITEMS; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate data generation
        int data = id * MAX_ITEMS + i;
        
        {
            std::unique_lock<std::mutex> lock(mtx);
            while (dataQueue.size() >= MAX_QUEUE_SIZE) {
                cv_producer.wait(lock);
            }
            dataQueue.push(data);
            std::cout << "Producer " << id << " produced: " << data << std::endl;
            cv_consumer.notify_all();
        }
    }
}

void consumerFunction(int id) {
    while (!isDone) {
        int data;
        {
            std::unique_lock<std::mutex> lock(mtx);
            while (dataQueue.empty() && !isDone) {
                cv_consumer.wait(lock);
            }
            if (!dataQueue.empty()) {
                data = dataQueue.front();
                dataQueue.pop();
                std::cout << "Consumer " << id << " consumed: " << data << std::endl;
                cv_producer.notify_all();
            }
        }
    }
}

int main() {
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producers.emplace_back(producerFunction, i);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumers.emplace_back(consumerFunction, i);
    }

    // Allow producers to finish their work
    for (auto& producer : producers) {
        producer.join();
    }

    // Signal consumers that no more data will be produced
    {
        std::lock_guard<std::mutex> lock(mtx);
        isDone = true;
    }
    cv_consumer.notify_all();

    // Allow consumers to finish processing
    for (auto& consumer : consumers) {
        consumer.join();
    }

    return 0;
}
