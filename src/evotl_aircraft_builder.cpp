//
// Created by Dhara Balaji on 8/31/21.
//

#include "evotl_aircraft_builder.h"

namespace dharas
{
EvotlAircraftBuilder::EvotlAircraftBuilder()
{
    buildAlpha();
    buildBeta();
    buildCharlie();
    buildDelta();
    buildEcho();
}
// Dhara has combined Abstract Factory and Builder into a sandwich.
EvotlAirCraftPtr EvotlAircraftBuilder::BuildAircraft(const AircraftType t)
{
    return aircraft[t];
}

void EvotlAircraftBuilder::buildAlpha()
{
    aircraft[AircraftType::ALPHA] = std::make_shared<EvotlAircraft>(AircraftType::ALPHA, 120,
                                                                    320,1.6,
                                                                    0.6, 4,
                                                                    0.25);
}

void EvotlAircraftBuilder::buildBeta()
{
    aircraft[AircraftType::BETA] = std::make_shared<EvotlAircraft>(AircraftType::BETA, 100,
                                                                   100, 1.5,
                                                                   0.2, 5,
                                                                   0.10);
}

void EvotlAircraftBuilder::buildCharlie()
{
    aircraft[AircraftType::CHARLIE] = std::make_shared<EvotlAircraft>(AircraftType::CHARLIE, 160,
                                                                      220,2.2, 0.8, 3, 0.05);
}

void EvotlAircraftBuilder::buildDelta()
{
    aircraft[AircraftType::DELTA] = std::make_shared<EvotlAircraft>(AircraftType::DELTA, 90, 120,
                                                      0.8, .62, 2, 0.22);
}

void EvotlAircraftBuilder::buildEcho()
{
    aircraft[AircraftType::ECHO] = std::make_shared<EvotlAircraft>(AircraftType::ECHO, 30, 150,
                                                      5.8, 0.3, 2, 0.61);
}

}