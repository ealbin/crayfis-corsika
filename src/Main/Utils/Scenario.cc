
#include <corsis/utils/Scenario.h>
#include <math.h> /* acos, nan */
#include <iostream>

const double PI = acos(-1.);

Scenario::Scenario() {
    f_nucleons = 0;
    f_cut = 100_GeV;
    f_density = 1_kg / (1_m * 1_m * 1_m);
    f_energy = 0_eV;
    f_height = 112.8_km; // CORSIKA 7 default
    f_impact = 0_m;
    f_mass = 0_GeV;
    f_oxygen = 0.20946;
    f_nitrogen = 1.f - f_oxygen;
    f_output = "corsis_output.dat";
    f_phi = 0.; // degrees
    f_pythia = false;
    //f_seed = ;
    f_sibyll = true;
    f_theta = 0.; // degrees
    f_protons = 0;
    f_error = false;
}

units::si::HEPEnergyType Scenario::getCut() { return f_cut; }
units::si::MassDensityType Scenario::getDensity() { return f_density; }
units::si::HEPEnergyType Scenario::getEnergy() { return f_energy; }
units::si::LengthType Scenario::getHeight() { return f_height; }
units::si::LengthType Scenario::getImpact() { return f_impact; }
units::si::HEPMassType Scenario::getMass() { return f_mass; }
float Scenario::getNitrogen() { return f_nitrogen; }
std::string Scenario::getOutput() { return f_output; }
double Scenario::getPhi() { return f_phi; }
bool Scenario::usingPythia() { return f_pythia; }
//uint64_t getSeed();
bool Scenario::usingSibyll() { return f_sibyll; }
double Scenario::getTheta() { return f_theta; }
float Scenario::getOxygen() { return f_oxygen; }
int Scenario::getProtons() { return f_protons; }
bool Scenario::error() { return f_error; }

MomentumVector Scenario::getMomentum(const geometry::CoordinateSystem& v_coordsys) {
    units::si::HEPMomentumType momentum_mag =
            sqrt( f_energy*f_energy - f_mass*f_mass );

    double theta = PI / 180. * f_theta;
    double phi   = PI / 180. * f_phi;
    auto px = momentum_mag * sin(theta) * cos(phi);
    auto py = momentum_mag * sin(theta) * sin(phi);
    auto pz = momentum_mag * cos(theta) * -1.; // downward
    return MomentumVector(v_coordsys, {px, py, pz});
}

double Scenario::getScale(const std::string& v_str) {
    if (v_str.size() == 0)
        return 1.;
    if (v_str.size() != 1) {
        if (v_str == "da")
            return (double) units::si::deka;
        else
            throw std::exception {};
    }
    if (v_str.size() > 2)
        throw std::exception {};

    // size is 1
    switch (v_str[0]) {
        case 'Y':
            return (double) units::si::yotta;
        case 'Z':
            return (double) units::si::zetta;
        case 'E':
            return (double) units::si::exa;
        case 'P':
            return (double) units::si::peta;
        case 'T':
            return (double) units::si::tera;
        case 'G':
            return (double) units::si::giga;
        case 'M':
            return (double) units::si::mega;
        case 'k':
            return (double) units::si::kilo;
        case 'h':
            return (double) units::si::hecto;
///        case "da":
///            return (double) units::si::deka;
        case 'd':
            return (double) units::si::deci;
        case 'c':
            return (double) units::si::centi;
        case 'm':
            return (double) units::si::milli;
        case 'u':
            return (double) units::si::micro;
        case 'n':
            return (double) units::si::nano;
        case 'p':
            return (double) units::si::femto;
        case 'a':
            return (double) units::si::atto;
        case 'z':
            return (double) units::si::zepto;
        case 'y':
            return (double) units::si::yocto;
        default:
            throw std::exception {};
    }

    return nan(""); // silence compiler warning
}

int Scenario::setNucleons(const char* v_nucleons) {
    try {
        f_nucleons = std::stoi(std::string(v_nucleons));
    }
    catch (...) {
        return 1;
    }
    return 0;
}

int Scenario::setCut(const char* v_cut) {
    try {
        std::string cut(v_cut);
        double value = std::stod(cut);

        std::size_t unit_start = cut.find_first_of('_');
        if (unit_start == std::string::npos) {
            f_cut = value * 1_eV;
            return 0;
        }

        std::size_t prefix_start = cut.find("eV");
        std::size_t len = std::string::npos;
        if (prefix_start != std::string::npos)
            len = prefix_start - unit_start - 1;

        f_cut = value * getScale(cut.substr(unit_start + 1, len)) * 1_eV;
    }
    catch (...) {
        return 1;
    }
    return 0;
}

int Scenario::setDensity(const char* v_density) {
    try {
        std::string density(v_density);
        double value = std::stod(density);

        std::size_t unit_start = density.find_first_of('_');
        if (unit_start == std::string::npos) {
            f_density = value * 1_kg / (1_m * 1_m * 1_m);
            return 0;
        }

        f_density = value * getScale(density.substr(unit_start + 1)) * 1_kg / (1_m * 1_m * 1_m);
    }
    catch (...) {
        return 1;
    }
    return 0;
}

int Scenario::setEnergy(const char* v_energy) {
    try {
        std::string energy(v_energy);
        double value = std::stod(energy);

        std::size_t unit_start = energy.find_first_of('_');
        if (unit_start == std::string::npos) {
            f_energy = value * 1_eV;
            return 0;
        }

        std::size_t prefix_start = energy.find("eV");
        std::size_t len = std::string::npos;
        if (prefix_start != std::string::npos)
            len = prefix_start - unit_start - 1;

        f_energy = value * getScale(energy.substr(unit_start + 1, len)) * 1_eV;
    }
    catch (...) {
        return 1;
    }
    return 0;
}

int Scenario::setHeight(const char* v_height) {
    try {
        std::string height(v_height);
        double value = std::stod(height);

        std::size_t unit_start = height.find_first_of('_');
        if (unit_start == std::string::npos) {
            f_height = value * 1_m;
            return 0;
        }

        std::size_t prefix_start = height.find_last_of('m');
        std::size_t len = std::string::npos;
        if (prefix_start != std::string::npos)
            len = prefix_start - unit_start - 1;

        f_height = value * getScale(height.substr(unit_start + 1, len)) * 1_m;
    }
    catch (...) {
        return 1;
    }
    return 0;
}

int Scenario::setImpact(const char* v_impact) {
    try {
        std::string impact(v_impact);
        double value = std::stod(impact);

        std::size_t unit_start = impact.find_first_of('_');
        if (unit_start == std::string::npos) {
            f_impact = value * 1_m;
            return 0;
        }

        std::size_t prefix_start = impact.find_last_of('m');
        std::size_t len = std::string::npos;
        if (prefix_start != std::string::npos)
            len = prefix_start - unit_start - 1;

        f_impact = value * getScale(impact.substr(unit_start + 1, len)) * 1_m;
    }
    catch (...) {
        return 1;
    }
    return 0;
}

int Scenario::setMass(const char* v_mass) {
    try {
        f_mass = std::stod(std::string(v_mass)) * 1_GeV;

        std::string mass(v_mass);
        double value = std::stod(mass);

        std::size_t unit_start = mass.find_first_of('_');
        if (unit_start == std::string::npos) {
            f_mass = value * 1_eV;
            return 0;
        }

        std::size_t prefix_start = mass.find("eV");
        std::size_t len = std::string::npos;
        if (prefix_start != std::string::npos)
            len = prefix_start - unit_start - 1;

        f_mass = value * getScale(mass.substr(unit_start + 1, len)) * 1_eV;
    }
    catch (...) {
        return 1;
    }
    return 0;
}

int Scenario::setNitrogen(const char* v_nitrogen) {
    try {
        f_nitrogen = std::stof(std::string(v_nitrogen));
    }
    catch (...) {
        return 1;
    }
    return 0;
}

int Scenario::setOutput(const char* v_output) {
    f_output = std::string(v_output);
    return 0;
}

int Scenario::setPhi(const char* v_phi) {
    try {
        f_phi = std::stod(std::string(v_phi));
    }
    catch (...) {
        return 1;
    }
    return 0;
}

int Scenario::setPythia() {
    f_pythia = true;
    return 0;
}

//int setSeed(const char* v_seed);

int Scenario::setSibyll() {
    f_sibyll = true;
    return 0;
}

int Scenario::setTheta(const char* v_theta) {
    try {
        f_theta = std::stod(std::string(v_theta));
    }
    catch (...) {
        return 1;
    }
    return 0;
}

int Scenario::setOxygen(const char* v_oxygen) {
    try {
        f_oxygen = std::stof(std::string(v_oxygen));
    }
    catch (...) {
        return 1;
    }
    return 0;
}

int Scenario::setProtons(const char* v_protons) {
    try {
        f_protons = std::stoi(std::string(v_protons));
    }
    catch (...) {
        return 1;
    }
    return 0;
}

void Scenario::setError() {
    f_error = true;
}

void Scenario::print() {
    std::cout << "Primary Nucleons: " << f_nucleons << std::endl;
    std::cout << "Cut Energy:       " << f_cut      << std::endl;
    std::cout << "Atm. Density:     " << f_density  << std::endl;
    std::cout << "Primary Energy:   " << f_energy   << std::endl;
    std::cout << "Atm. Height:      " << f_height   << std::endl;
    std::cout << "Impact Height:    " << f_impact   << std::endl;
    std::cout << "Primary Mass:     " << f_mass     << std::endl;
    std::cout << "Nitrogen Frac:    " << f_nitrogen << std::endl;
    std::cout << "Output file:      " << f_output   << std::endl;
    std::cout << "Phi:              " << f_phi      << " deg" << std::endl;
    std::cout << "Pythia?           " << f_pythia   << std::endl;
    std::cout << "Sibyll?           " << f_sibyll   << std::endl;
    std::cout << "Theta:            " << f_theta    << " deg" << std::endl;
    std::cout << "Oxygen Frac:      " << f_oxygen   << std::endl;
    std::cout << "Primary Protons:  " << f_protons  << std::endl;
}
