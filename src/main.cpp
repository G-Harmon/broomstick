#include "simulation_pipeline.h"

int main()
{
    auto pipeline = dharas::SimulationPipeline();
    pipeline.run(20, 3, std::chrono::minutes (3));
    return 0;
}