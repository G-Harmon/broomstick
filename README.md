The Problem
===================
* Given K types of eVOTL aircrafs
* C chargers
* Run T min of simulation
* 1 min of simulation = 1 hour of real-time. 1 sec sim time = 1 min of real time
* Total 20 vehicles of *ANY* type used (out of given 5 types)

Produce
========

* Avg time in flight
* Avg time charging
* Avg time waiting in line to charge
* Max num of faults
* Total distance travelled by passengers

 Building 
================
mkdir build

cd build

cmake ..

make -j12

Running 
================
./joby_main

 Unit Test 
=================
cd build; ./test/tests
