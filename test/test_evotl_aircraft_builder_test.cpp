//
// Created by Dhara Balaji on 9/9/21.
//

#include <gtest/gtest.h>
#include "evotl_aircraft_builder.h"

using namespace dharas;

class TestEvotlAircraftBuilder : public testing::Test
{
public:
    TestEvotlAircraftBuilder() : aircraftBuilder() {}
    EvotlAircraftBuilder aircraftBuilder;
};

TEST_F(TestEvotlAircraftBuilder, testUnitConversionForSim)
{
    auto alpha = aircraftBuilder.BuildAircraft(AircraftType::ALPHA);
    EXPECT_FALSE(alpha == nullptr);
    EXPECT_EQ(alpha->GetCruiseSpeed(), 2);
    EXPECT_EQ(alpha->GetTimeToCharge(), 36.0);
}