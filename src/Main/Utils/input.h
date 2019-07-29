
#ifndef _include_corsis_utils_input_h_
#define _include_corsis_utils_input_h_

#include <corsika/units/PhysicalUnits.h>
#include <phys/units/quantity.hpp>

#include <getopt.h>
#include <stdio.h>  /* for printf */
#include <string>

using namespace corsika;
using namespace phys::units::literals;

const std::string VERSION = "1.0.0";

struct Scenario {
    std::string nucleons;
    std::string cut;
    std::string density;
    std::string energy;
    std::string height;
    std::string impact;
    std::string mass;
    std::string nitrogen;
    std::string output;
    std::string phi;
    bool pythia;
    std::string seed;
    bool sibyll;
    std::string theta;
    std::string oxygen;
    std::string protons;
    /*
    double nucleons;
    units::si::HEPEnergyType cut;
    double density;
    units::si::HEPEnergyType energy;
    units::si::LengthType height;
    units::si::LengthType impact;
    double mass;
    double nitrogen;
    std::string output;
    double phi;
    bool pythia;
    int seed; // what is the seed type?
    bool sibyll;
    double theta;
    double oxygen;
    int protons;
    */
    bool exit;
};

/*
 * TODO: documentation
 */
void readInput(int argc, char *argv[], Scenario& scenario);

#endif
