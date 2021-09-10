//
// Created by Dhara Balaji on 9/5/21.
//

#include <chrono>
#include <thread>
#include <iostream>
#include <shared_mutex>
#include <aircraft_simulation_runner.h>
#include "simulation_runner.h"

namespace dharas
{

// condition variable to wake threads running actor to call update
// on them
std::condition_variable g_updateActorTick;
std::mutex g_tickerWaitLock;

// Decorator (wrapper on actor. Each of them runs on single thread
// and when the tick happens, they all update their state)
class SimulationRunnerPrivate
{
public:
    explicit SimulationRunnerPrivate(SimActorPtr& actor,
                                     TickerPtr& ticker);
    ~SimulationRunnerPrivate();
    void Stop();
private:
    // actor
    std::thread actorThread;

    // we are asked to stop
//    std::atomic<bool> stop;
    bool stop;

    // ticker to get ticks
    TickerPtr ticker;

    SimActorPtr actor; //TODO remove, debug
    AircraftSimulationRunnerPtr aircraftSimRunner;

    uint64_t prevTick{0};
    void Run();
};


// Ticker takes care of only thing which is to tick and wake
// the SimRunners
class Ticker
{
public:
    Ticker() = default;
    uint64_t GetTick();
    void RunFor(std::chrono::duration<double> duration);
private:
    uint64_t tick{0};
    mutable std::shared_timed_mutex protectTick; // should have picked C++17!
};

void Ticker::RunFor(std::chrono::duration<double> duration)
{

    auto tStart = std::chrono::steady_clock::now();
    auto sleepDur = std::chrono::seconds(1);
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - tStart) <
           duration)
    {
        std::unique_lock<std::shared_timed_mutex> l(protectTick);
        tick = (std::chrono::steady_clock::now() - tStart).count();
        l.unlock();
        g_updateActorTick.notify_all();
//        for (auto& actor : actors)
//        {
//            actor->Update((std::chrono::steady_clock::now() - tStart).count());
//        }
        std::this_thread::sleep_for(sleepDur);
        std::cout << "\n\ntick: " << tick << "\n";
    }
    g_updateActorTick.notify_all();
}

uint64_t Ticker::GetTick() {
    std::shared_lock<std::shared_timed_mutex> readLock(protectTick);
    return tick;
}

SimulationRunnerPrivate::SimulationRunnerPrivate(SimActorPtr &actor,
                                                 TickerPtr &ticker) : stop(false), ticker(ticker), actor(actor)
{
    aircraftSimRunner = std::dynamic_pointer_cast<AircraftSimulationActor>(actor);
    this->actorThread = std::thread(&SimulationRunnerPrivate::Run, this);
}

void SimulationRunnerPrivate::Run()
{
    std::unique_lock<std::mutex> guard(g_tickerWaitLock, std::defer_lock);
//    std::cout << "created a SIM thread for aircraft " << aircraftSimRunner->CollectStats().t << "\n";
    while (!stop)
    {
        guard.lock();
        g_updateActorTick.wait(guard, [&]{
            return ticker->GetTick() > prevTick || stop; //for spurious wake up calls
        });
        guard.unlock();
        prevTick = ticker->GetTick();
        // woke-up at tick -> update simActor
        actor->Update(ticker->GetTick());
    }
//    std::cout << "[CLOSING] a SIM thread for aircraft " << aircraftSimRunner->CollectStats().t << "\n";
}

void SimulationRunnerPrivate::Stop()
{
    stop = true;
//    std::cout << "STOPPING a SIM thread for aircraft " << aircraftSimRunner->CollectStats().t << "\n";
    g_updateActorTick.notify_all();
    if (actorThread.joinable())
        actorThread.join();
}

SimulationRunnerPrivate::~SimulationRunnerPrivate()
{
    this->Stop();
}

void SimulationRunner::RegisterActor(SimActorPtr& actor)
{
    // this will start "actor" thread, waiting to start simulation (tick)
    actors.emplace_back(std::make_unique<SimulationRunnerPrivate>(actor, ticker));
}

void SimulationRunner::StartSimulation()
{
    // start ticker
    ticker->RunFor(duration);
    for (std::unique_ptr<SimulationRunnerPrivate> &runner : this->actors)
    {
        runner->Stop();
    }
}

SimulationRunner::~SimulationRunner()
{
    for (std::unique_ptr<SimulationRunnerPrivate> &runner : this->actors)
    {
        runner->Stop();
    }
}

SimulationRunner::SimulationRunner(std::chrono::duration<double> duration) : duration(duration)
{
    ticker = std::make_shared<Ticker>();
}
}