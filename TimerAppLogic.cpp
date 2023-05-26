// TimerAppLogic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "TimerApp.h"

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread> // std::this_thread::sleep_for


class Task {
private:
    std::string m_taskName;
    //std::chrono::system_clock::time_point m_startTime;
    std::time_t m_startTime;

public:
    Task(){}
    Task(std::string name) : m_taskName(name) {
        m_startTime = time(NULL); // std::chrono::system_clock::now();
    }

    std::time_t getStartTime() const {
        return m_startTime; // std::chrono::system_clock::to_time_t(m_startTime);
    }

    void setStartTime(int seconds) {
        m_startTime = static_cast<time_t>(seconds);
    }

    void restartTime() {
        m_startTime = time(NULL);
    }

    std::string getName()  const {
        return m_taskName;
    }

    void setName(std::string newName) {
        m_taskName = newName;
    }
    

    void printStartDate()  const {
        std::time_t temp = getStartTime();
        struct tm tempTime;
        localtime_s(&tempTime, &temp);
        std::cout << tempTime.tm_hour << ':' << tempTime.tm_min << ' ' << tempTime.tm_mday << '/' << tempTime.tm_mon + 1 << '/' << tempTime.tm_year + 1900;
    }

    void printDuration() const {
        std::time_t duration = time(NULL) - m_startTime;

        int minutes = static_cast<int>(duration) / 60;
        int hours = minutes / 60;
        int seconds = static_cast<int>(duration) % 60;

        std::cout << "\nDuration: ";
        if (hours > 0) std::cout << hours << " hours ";
        if (minutes > 0) std::cout << minutes << " minutes ";
        std::cout << seconds << " seconds.";
        //std::cout << duration;
    }

    friend std::ostream& operator<<(std::ostream& out, const Task& task) {
        std::cout << "Task name: " << task.getName() << "\nTask start date: ";
        task.printStartDate();

        return out;
    }

    void saveToFile() {
        std::ofstream fout("data.sql");
        fout << m_taskName << ' ' << m_startTime;
        fout.close();
    }

    friend Task readTask();
};

Task createTask() {
    std::cout << "Please, input a name of the task (without spaces): ";
    std::string name;
    std::cin >> name;

    Task temp(name);
    temp.saveToFile();

    return temp;
}

Task readTask() {
    Task item_from_disk;
    std::ifstream fin("data.sql");
    fin >> item_from_disk.m_taskName >> item_from_disk.m_startTime;
    fin.close();

    return item_from_disk;
}

Task startWork() {
    char answer;
    do {
        std::cout << "Would you like to create a (n)ew task or continue (o)ld one? n / o \n";
        std::cin >> answer;
    } while (answer != 'n' && answer != 'o');

    if (answer == 'n')
        return createTask();
    else
        return readTask();
}
int main() {

    Task testTask2 = startWork();


    std::cout << testTask2;
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    testTask2.printDuration();


    return 1;
}