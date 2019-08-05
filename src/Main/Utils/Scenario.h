
#ifndef _include_corsis_utils_Scenario_h_
#define _include_corsis_utils_Scenario_h_

#include <phys/units/io.hpp> /* to_string */
#include <phys/units/quantity.hpp> /* SI literals, units and prefix constants */

#include <corsika/particles/ParticleProperties.h> /* GetNucleusMass */
#include <corsika/geometry/Point.h> /* Point */
#include <corsika/geometry/Vector.h> /* MomentumVector */
#include <corsika/units/PhysicalUnits.h> /* HEP (eV) unit types */

#include <ctype.h> /* isalpha */
#include <math.h> /* acos, nan */

#include <iostream>
#include <limits> /* std::numeric_limits */
#include <string>

using namespace corsika;
using namespace phys::units::literals;

typedef geometry::Vector<units::si::hepmomentum_d> MomentumVector;

constexpr double PI = acos(-1.);

namespace err {
    constexpr int NO_ERR = 0;
    constexpr int FORMAT_ERR = 1;
    constexpr int REPEAT_ERR = 2;
    constexpr int INCOMPAT_ERR = 3;
} // namespace err

class Scenario {
private:
    bool f_nucleons_set;
    bool f_cut_set;
    bool f_density_set;
    bool f_mass_set;
    bool f_energy_set;
    bool f_height_set;
    bool f_impact_set;
    bool f_nitrogen_set;
    bool f_oxygen_set;
    bool f_output_set;
    bool f_phi_set;
    bool f_pythia_set;
    bool f_sibyll_set;
    bool f_theta_set;
    bool f_protons_set;

    unsigned short f_nucleons;
    units::si::HEPEnergyType f_cut;
    units::si::MassDensityType f_density;
    units::si::HEPEnergyType f_energy;
    units::si::LengthType f_height;
    units::si::LengthType f_impact;
    units::si::HEPMassType f_mass;
    float f_nitrogen;
    std::string f_output;
    double f_phi;  // degrees
    bool f_pythia;
    //uint64_t f_seed;
    bool f_sibyll;
    double f_theta; // degrees
    float f_oxygen;
    unsigned short f_protons;
    bool f_error;

    double getScale(const std::string& v_str);
    units::si::HEPMassType getHEPMass();
    unsigned short getHEPNucleons();

public:
    Scenario();

    bool isValid();
    const unsigned short& getNucleons();
    const units::si::HEPEnergyType& getCut();
    const units::si::MassDensityType& getDensity();
    const units::si::HEPEnergyType& getEnergy();
    const units::si::LengthType& getHeight();
    geometry::Point getImpact(const geometry::CoordinateSystem& v_coordsys);
    const units::si::HEPMassType& getMass();
    const float& getNitrogen();
    const std::string& getOutput();
    const double& getPhi();
    const bool& usingPythia();
    //uint64_t getSeed();
    const bool& usingSibyll();
    const double& getTheta();
    const float& getOxygen();
    const unsigned short& getProtons();
    MomentumVector getMomentum(const geometry::CoordinateSystem& v_coordsys);
    const bool& error();

    void print();

    int setNucleons(const char* v_nucleons);
    int setCut(const char* v_cut);
    int setDensity(const char* v_density);
    int setEnergy(const char* v_energy);
    int setHeight(const char* v_height);
    int setImpact(const char* v_impact);
    int setMass(const char* v_mass);
    int setNitrogen(const char* v_nitrogen);
    int setOutput(const char* v_output);
    int setPhi(const char* v_phi);
    int setPythia();
    //int setSeed(const char* v_seed);
    int setSibyll();
    int setTheta(const char* v_theta);
    int setOxygen(const char* v_oxygen);
    int setProtons(const char* v_protons);
    void setError();
};

#endif
