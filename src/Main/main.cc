// corsika libraries
#include <corsika/random/RNGManager.h> /* for corsika::random */
#include <corsika/setup/SetupEnvironment.h> /* for corsika::environment */
#include <corsika/units/PhysicalUnits.h> /* for corsika::units::si */
#include <corsika/utl/CorsikaFenv.h> /* for feenableexcept */

// corsis libraries
#include <corsis/utils/input.h> /* for readInput */

// standard libraries
#include <iostream>

using namespace corsika::environment; /* for Environment */
using namespace corsika::random; /* for RNGManager */
using namespace corsika::units::si; /* for LengthType */


int main(int argc, char* argv[]) {

    // TODO: have readInput somehow affect variables
    // Candidates:
    //      height_atmosphere: double (km)
    //      random seed: uint64_t
    readInput(argc, argv);

    // this is the CORSIKA 7 start of atmosphere/universe
    const LengthType height_atmosphere = 112.8_km;

    // TODO: logger
    std::cout << "[Setting] Atmosphere height: " << height_atmosphere << "\n";

    // For reasons unclear to me, the floating-point invalid exception trap
    // is set in many examples and tests.. so I'm setting it too..
    // The invalid exception occurs when there is no well-defined result for an
    // operation, as for (0/0) or (infinity - infinity) or sqrt(-1).
    feenableexcept(FE_INVALID);

    // create a random number sequence named "corsis"
    // it's a Mersenne Twister (std::mt19937)
    RNGManager::GetInstance().RegisterRandomStream("corsis");

    std::cout << "[Info] Random streams (who knows what the numbers mean):\n";
    // TODO: split at new lines and indent
    std::cout << RNGManager::GetInstance().dumpState().str() << "\n\n";

    RNG corsis_rng = RNGManager::GetInstance().GetRandomStream("corsis");
    std::cout << "Here are some random numbers:\n";
    std::cout << corsis_rng() << " " << corsis_rng() << " " << corsis_rng() << "\n";

    // TODO: !!! RANDOM NUMBER IS SEQUENCE IS IDENTICAL EVERY TIME ITS RUN !!!
    // NEED TO SET THE SEED FOR UNIQUE PERFORMANCE
}

