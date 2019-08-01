
// src/Main
//  corsika libraries
#include "main.h"

// src/Main/Utils
//  readInput()
#include <corsis/utils/input.h>

// src/Main/Utils
#include <corsis/utils/Scenario.h>

#include <iostream>

// corsika base namespace
using namespace corsika;

// namespace for literals, e.g. _km, _GeV, etc...
using namespace phys::units::literals;

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
    return 0;

    ////////////////////////////////////////////////////////////////////////////

    // create a random number sequence named "corsis"
    // it's a Mersenne Twister (std::mt19937)
    random::RNGManager::GetInstance().RegisterRandomStream("corsis");
    random::RNGManager::GetInstance().RegisterRandomStream("s_rndm");
    random::RNGManager::GetInstance().RegisterRandomStream("pythia");

    // TODO: !!! RANDOM NUMBER IS SEQUENCE IS IDENTICAL EVERY TIME ITS RUN !!!
    // (for each stream too) -- NEED TO SET THE SEED FOR UNIQUE PERFORMANCE

    // IEnvironmentModel is currently set in SetupEnvironment.h as an alias for
    // environment::IMediumModel, the "I" I believe denotes "inhomogenious",
    // although src/Environment/InhomogeniousMedium.h isn't used(?) maybe that's
    // for a custom medium... anyway, inhomogeneous as in the properties of the
    // atmosphere change with altitude
    environment::Environment<setup::IEnvironmentModel> environment;

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

    // Helium with a silly model for Z(A)
    const particles::Code primary = particles::Code::Nucleus;
    int nucleus_A = 4;
    int nucleus_Z = int(nucleus_A / 2.15 + .7);
    units::si::HEPMassType mass = particles::GetNucleusMass(nucleus_A, nucleus_Z);
    units::si::HEPEnergyType energy = nucleus_A * 1_TeV;

    auto momentum = scenario.getMomentum(coord_sys);

    std::cout << "input particle: " << primary << std::endl;
    std::cout << "input angles: theta=" << scenario.getTheta() << " phi=" << scenario.getPhi() << std::endl;
    std::cout << "input momentum: " << momentum.GetComponents() / 1_GeV << " GeV" << std::endl;

    ////////////////////////////////////////////////////////////////////////////

    // I guess the particle stack keeps track of created particles(?)
    setup::Stack stack;
    stack.Clear();
    stack.AddParticle(
        std::tuple<particles::Code, units::si::HEPEnergyType, stack::MomentumVector, geometry::Point,
        units::si::TimeType, unsigned short, unsigned short>{
        primary, energy, momentum, start_altitude, 0_ns, nucleus_A, nucleus_Z});

    // setup processes, decays and interactions
    process::tracking_line::TrackingLine tracking;

    // NO IDEA WHY THE FIRST TWO ARGUMENTS APPEAR TO ALWAYS BE 1 and TRUE
    process::stack_inspector::StackInspector<setup::Stack> stack_inspector(1, true, energy);

    process::sibyll::Interaction sibyll;
    //process::pythia::Interaction pythia; <-- from proton
    process::sibyll::NuclearInteraction sibyllNuc(sibyll, environment);
    process::sibyll::Decay decay;

    // cascade with only HE model ==> HE cut
    process::particle_cut::ParticleCut cut(80_GeV);

    process::energy_loss::EnergyLoss energy_loss;

    process::track_writer::TrackWriter trackWriter("deleteme.dat");

    // assemble all processes into an ordered process list
    auto sequence = stack_inspector << sibyll << sibyllNuc << decay << energy_loss << cut
                                 << trackWriter;

    ////////////////////////////////////////////////////////////////////////////


    // define air shower object, run simulation
    //cascade::Cascade EAS(environment, tracking, sequence, stack);
    //EAS.Init();
    //EAS.Run();

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
}

