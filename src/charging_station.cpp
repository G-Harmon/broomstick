//
// Created by Dhara Balaji on 8/31/21.
//

#include <iostream>
#include <thread>
#include "charging_station.h"

dharas::ChargingStation::ChargingStation(int count) : total(count)
{
}

bool dharas::ChargingStation::isAvailable()
{
    std::lock_guard<std::mutex> guard(mutex);
    return chargingStations.size() < total;
}

void dharas::ChargingStation::doneCharging()
{
    std::lock_guard<std::mutex> guard(mutex);
    chargingStations.pop_front();
}

bool dharas::ChargingStation::charge()
{
    std::lock_guard<std::mutex> guard(mutex);
    if (chargingStations.size() < total) {
        chargingStations.push_back(true);
        return true;
    } else {
        return false;
    }
}

//void dharas::ChargingStation::charge(const std::chrono::duration<double> time_to_charge)
//{
//    std::unique_lock<std::mutex> lock(mutex);
//
////    mutex.lock(); // taking lock to see if any of the charging station is available
//    // wait till a charging station is available
//    cv.wait(lock, [this]() {
//        return std::find(chargingStations.begin(), chargingStations.end(), true) != chargingStations.end();
//    });
//    auto itr = std::find(chargingStations.begin(), chargingStations.end(), true);
//    if (itr != chargingStations.end()) {
//        // great this charging station is available
//        lock.unlock();
//        std::this_thread::sleep_for(time_to_charge);
//        // we're done, let's wake someone if they were waiting for charging
//        cv.notify_one();
//    } else {
//        std::cout << "We shouldn't be here\n";
//    }
