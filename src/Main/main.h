
#ifndef _include_corsis_main_h_
#define _include_corsis_main_h_

// CORSIKA Library
//================

// src/Framework
//..............

// src/Framework/Cascade
//  corsika::cascade
#include <corsika/cascade/Cascade.h>

// src/Framework/Environment
//  corsika::environment
#include <corsika/environment/Environment.h>
#include <corsika/environment/HomogeneousMedium.h>
#include <corsika/environment/NuclearComposition.h>

// src/Framework/Geometry
//  corsika::geometry
#include <corsika/geometry/CoordinateSystem.h>
#include <corsika/geometry/Point.h>
#include <corsika/geometry/Sphere.h>

// src/Framework/Particles
//  corsika::particles
//      enum class Code
//      constexpr GetNucleusMass
#include <corsika/particles/ParticleProperties.h>

// src/Framework/ProcessSequence
//  corsika::process
//      inline auto operator<<(P1&& vA, P2&& vB) -> ProcessSequence<P1, P2>
//      class ProcessSequence<P1, P2>
#include <corsika/process/ProcessSequence.h>

// src/Framework/Random
//  corsika::random
//      class RNGManager
//      using RNG = std::mt19937
#include <corsika/random/RNGManager.h>

// src/Framework/Units
//  corsika::units::si
//      using LengthType      = phys::units::quantity<phys::units::length_d, double>
//      using TimeType        = phys::units::quantity<phys::units::time_interval_d, double>
//      using HEPEnergyType   = phys::units::quantity<phys::units::hepenergy_d, double>
//      using HEPMassType     = phys::units::quantity<hepmass_d, double>
//      using HEPMomentumType = phys::units::quantity<hepmomentum_d, double>
//      (also adds eV and barns to phys::units::literals)
#include <corsika/units/PhysicalUnits.h>

// src/Framework/Utilities
//      Redeclaration of GLIBC feenableexcept
#include <corsika/utl/CorsikaFenv.h>

// src/Processes
//..............

// src/Processes/EnergyLoss
//  corsika::process::energy_loss
#include <corsika/process/energy_loss/EnergyLoss.h>

// src/Processes/ParticleCut
//  corsika::process::particle_cut
#include <corsika/process/particle_cut/ParticleCut.h>

// src/Processes/Sibyll
//  corsika::process::sibyll
#include <corsika/process/sibyll/Interaction.h>
#include <corsika/process/sibyll/NuclearInteraction.h>
#include <corsika/process/sibyll/Decay.h>

// src/Processes/TrackingLine
//  corsika::process::tracking_line
#include <corsika/process/tracking_line/TrackingLine.h>

// src/Processes/TrackWriter
//  corsika::process::track_writer
#include <corsika/process/track_writer/TrackWriter.h>

// src/Processes/StackInspector
//  corsika::process:stack_inspector
#include <corsika/process/stack_inspector/StackInspector.h>

// src/Setup
//..........

// src/Setup
//  corsika::setup
//      using IEnvironmentModel = environment::IMediumModel
#include <corsika/setup/SetupEnvironment.h>

// src/Setup
//  corsika::stack
//      using Stack = detail::StackWithGeometry
#include <corsika/setup/SetupStack.h>

// src/Stack
//..........

// src/Stack
//  corsika::stack
//      typedef corsika::geometry::Vector<corsika::units::si::hepmomentum_d> MomentumVector
//      typedef for MomentumVector is found in either:
#include <corsika/stack/nuclear_extension/NuclearStackExtension.h>
#include <corsika/stack/super_stupid/SuperStupidStack.h>
// note, both the above are already included in <corsika/setup/SetupStack.h>

// src/ThirdParty
//...............

// src/ThirdParty/phys/units
//  phys::units::literals
//      constexpr quantity<dim, double> operator"" _##sfx(unsigned long long x)
//      constexpr quantity<dim, double> operator"" _##sfx(long double x)
//      (aka _km, _GeV, etc...)
#include <phys/units/quantity.hpp>


#endif
