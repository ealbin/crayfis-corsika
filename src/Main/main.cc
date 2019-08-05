
// src/Main
//  corsika libraries
#include "main.h"

// src/Main/Utils
//  readInput()
#include <corsis/utils/input.h>

// src/Main/Utils
#include <corsis/utils/Scenario.h>

//#include <execinfo.h> /* backtrace... */
//#include <unistd.h> /* STDERR_FILENO */


#include <iostream>

// corsika base namespace
using namespace corsika;

// namespace for literals, e.g. _km, _GeV, etc...
using namespace phys::units::literals;

/*
void handler(int sig) {
    const int history = 20;
    void *array[history];
    std::size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, history);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}
*/


int main(int argc, char* argv[]) {

    // For reasons unclear to me, the floating-point invalid exception trap
    // is set in many examples and tests.. so I'm setting it too..
    // The invalid exception occurs when there is no well-defined result for an
    // operation, as for (0/0) or (infinity - infinity) or sqrt(-1).
    feenableexcept(FE_INVALID);

    Scenario scenario;
    readInput(argc, argv, scenario);
    if (scenario.error())
        return 1;

    std::cout << "\nSetup:\n\n";
    scenario.print();

    ////////////////////////////////////////////////////////////////////////////

    // it's a Mersenne Twister (std::mt19937)
    // cascade has to be cascade for cascade.h
    random::RNGManager::GetInstance().RegisterRandomStream("cascade");
    random::RNGManager::GetInstance().RegisterRandomStream("s_rndm");
    random::RNGManager::GetInstance().RegisterRandomStream("pythia");

    // TODO: !!! RANDOM NUMBER IS SEQUENCE IS IDENTICAL EVERY TIME ITS RUN !!!
    // (for each stream too) -- NEED TO SET THE SEED FOR UNIQUE PERFORMANCE

    // IEnvironmentModel is currently set in SetupEnvironment.h as an alias for
    // environment::IMediumModel, the "I" I believe denotes "inhomogenious",
    // although src/Environment/InhomogeniousMedium.h isn't used(?) maybe that's
    // for a custom medium... anyway, inhomogeneous as in the properties of the
    // atmosphere change with altitude
    const environment::Environment<setup::IEnvironmentModel> environment;

    // TODO: no clue what the universe is
    // but environment.GetUniverse() returns a std::unique_ptr pointer
    // while environment.GetCoordinateSystem() returns a object
    auto& universe = *(environment.GetUniverse());
    const geometry::CoordinateSystem& coord_sys = environment.GetCoordinateSystem();

    // This *should* represent an atmosphere model that extends to infinity
    // also a std::make_unique pointer
    auto base_atmosphere =
            environment::Environment<setup::IEnvironmentModel>::CreateNode<geometry::Sphere>(
            geometry::Point{coord_sys, 0_m, 0_m, 0_m},
            1_m * std::numeric_limits<double>::infinity());

    // TODO: This *should* represent an atmosphere model near ground(?)
    // In the example, the radius is set to 5,000 meters (!?) that's less than
    // the radius of the Earth (~6,371 km) what?!?!
    // Update: it appears 0,0,0 is not the center of the Earth, but ground zero
    // 5 km still is only half way up the troposphere...
    auto ground_atmosphere =
            environment::Environment<setup::IEnvironmentModel>::CreateNode<geometry::Sphere>(
            geometry::Point{coord_sys, 0_m, 0_m, 0_m},
            5_km);

    // TODO: make inhomogenious??  Where is the Code:: enum explicitly done??
    auto const model_props = base_atmosphere->SetModelProperties<
            environment::HomogeneousMedium<setup::IEnvironmentModel>>(
            scenario.getDensity(), // air density, 1kg/m^3
            environment::NuclearComposition(
            std::vector<particles::Code>{particles::Code::Nitrogen, particles::Code::Oxygen},
            std::vector<float>{scenario.getNitrogen(), scenario.getOxygen()}));

    ground_atmosphere->SetModelProperties(model_props);
    base_atmosphere->AddChild(std::move(ground_atmosphere));
    universe.AddChild(std::move(base_atmosphere));    

    // Not clear if this is where first collission occurs!?
    // I'm starting to think 0,0,0 is not the center of the Earth, it's
    // ground zero...
    // this is the CORSIKA 7 start of atmosphere/universe
    geometry::Point start_altitude(coord_sys, 0_m, 0_m, scenario.getHeight());

    ////////////////////////////////////////////////////////////////////////////

    const particles::Code primary = particles::Code::Nucleus;
    auto momentum = scenario.getMomentum(coord_sys);

    std::cout << "input particle: " << primary << std::endl;
    std::cout << "input angles: theta=" << scenario.getTheta() << " phi=" << scenario.getPhi() << std::endl;
    std::cout << "input momentum: " << momentum.GetComponents() / 1_GeV << " GeV" << std::endl;

    ////////////////////////////////////////////////////////////////////////////

    std::cout << "\n\nHere we go:\n";

    // I guess the particle stack keeps track of created particles(?)
    std::cout << "\n - Stack\n";
    setup::Stack stack;
    stack.Clear();
    stack.AddParticle(
        std::tuple<particles::Code, units::si::HEPEnergyType, stack::MomentumVector, geometry::Point,
        units::si::TimeType, unsigned short, unsigned short>{
        particles::Code::Nucleus, scenario.getEnergy(), momentum, scenario.getImpact(coord_sys),
                    0_ns, 4, 2});

    std::cout << "\n - Tracking Line\n";
    // setup processes, decays and interactions
    process::tracking_line::TrackingLine tracking;

    std::cout << "\n - Stack Inspector\n";
    // NO IDEA WHY THE FIRST TWO ARGUMENTS APPEAR TO ALWAYS BE 1 and TRUE
    process::stack_inspector::StackInspector<setup::Stack>
            stack_inspector(1, true, scenario.getEnergy());

    if (scenario.usingSibyll()) {
        std::cout << "\n - Sibyll\n";
        process::sibyll::Interaction interaction;
        process::sibyll::NuclearInteraction nuclear(interaction, environment);
        process::sibyll::Decay decay;

        std::cout << "\n - Cut\n";
        // cascade with only HE model ==> HE cut
        process::particle_cut::ParticleCut cut(scenario.getCut());

        std::cout << "\n - Energy Loss\n";
        process::energy_loss::EnergyLoss energy_loss;

        std::cout << "\n - TrackWriter\n";
        process::track_writer::TrackWriter trackWriter(scenario.getOutput());

        std::cout << "\n - Load into stack inspector\n";
        // assemble all processes into an ordered process list
        auto sequence = stack_inspector << interaction << nuclear << decay
                                        << energy_loss << cut << trackWriter;

        std::cout << "\n - Make Cascade\n";
        // define air shower object, run simulation
        cascade::Cascade EAS(environment, tracking, sequence, stack);
        std::cout << "\n - EAS.Init()\n";
        EAS.Init();
        std::cout << "\n - EAS.Run()\n";
        EAS.Run();
    }
    else {
        //process::pythia::Interaction pythia; <-- from proton
        std::cout << "Pythia stuff would go here\n";
    }

    return 0;

    /*

    ////////////////////////////////////////////////////////////////////////////


    std::cout << "\n\nEnergy Loss Profile:\n";
    energy_loss.PrintProfile(); // print longitudinal profile

    std::cout << "\n\nCut results:\n";
    cut.ShowResults();


    const units::si::HEPEnergyType Efinal =
        cut.GetCutEnergy() + cut.GetInvEnergy() + cut.GetEmEnergy();
    std::cout << "total cut energy (GeV): " << Efinal / 1_GeV << std::endl
         << "relative difference (%): " << (Efinal / energy - 1) * 100 << std::endl;
    std::cout << "total dEdX energy (GeV): " << energy_loss.GetTotal() / 1_GeV << std::endl
         << "relative difference (%): " << energy_loss.GetTotal() / energy * 100 << std::endl;
    */
}

