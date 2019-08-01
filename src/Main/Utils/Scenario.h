
#ifndef _include_corsis_utils_Scenario_h_
#define _include_corsis_utils_Scenario_h_

#include <phys/units/io.hpp> /* to_string */
#include <phys/units/quantity.hpp> /* SI literals, units and prefix constants */

#include <corsika/particles/ParticleProperties.h> /* GetNucleusMass */
#include <corsika/geometry/Vector.h> /* MomentumVector */
#include <corsika/units/PhysicalUnits.h> /* HEP (eV) unit types */

#include <ctype.h> /* isalpha */
#include <math.h> /* acos, nan */

#include <iostream>
#include <string>

using namespace corsika;
using namespace phys::units::literals;

typedef geometry::Vector<units::si::hepmomentum_d> MomentumVector;

const double PI = acos(-1.);

class Scenario {
private:
    bool f_nucleons_set;
    bool f_mass_set;
    bool f_energy_set;
    bool f_nitrogen_set;
    bool f_oxygen_set;
    bool f_pythia_set;
    bool f_sibyll_set;
    bool f_protons_set;

    int f_nucleons;
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
    int f_protons;
    bool f_error;

    double getScale(const std::string& v_str);
    units::si::HEPMassType getHEPMass();

public:
    Scenario();

    bool isValid();
    units::si::HEPEnergyType getCut();
    units::si::MassDensityType getDensity();
    units::si::HEPEnergyType getEnergy();
    units::si::LengthType getHeight();
    units::si::LengthType getImpact();
    units::si::HEPMassType getMass();
    float getNitrogen();
    std::string getOutput();
    double getPhi();
    bool usingPythia();
    //uint64_t getSeed();
    bool usingSibyll();
    double getTheta();
    float getOxygen();
    int getProtons();
    MomentumVector getMomentum(const geometry::CoordinateSystem& v_coordsys);
    bool error();

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
