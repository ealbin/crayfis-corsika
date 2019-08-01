
#include <corsis/utils/Scenario.h>

Scenario::Scenario() {
    f_nucleons_set = false;
    f_cut_set      = false;
    f_density_set  = false;
    f_mass_set     = false;
    f_energy_set   = false;
    f_height_set   = false;
    f_impact_set   = false;
    f_nitrogen_set = false;
    f_oxygen_set   = false;
    f_output_set   = false;
    f_phi_set      = false;
    f_pythia_set   = false;
    f_theta_set    = false;
    f_sibyll_set   = false;
    f_protons_set  = false;

    // defaults
    f_nucleons = 0;
    f_cut      = 100_GeV;
    f_density  = 1_kg / (1_m * 1_m * 1_m);
    f_energy   = 0_eV;
    f_height   = 112.8_km; // CORSIKA 7 default
    f_impact   = 0_m;
    f_mass     = 0_GeV;
    f_oxygen   = 0.20946;
    f_nitrogen = 1.f - f_oxygen;
    f_output   = "corsis_output.dat";
    f_phi      = 0.; // degrees
    f_pythia   = false;
    //f_seed   = ;  // TODO
    f_sibyll   = true;
    f_theta    = 0.; // degrees
    f_protons  = 0;
    f_error    = false;
}

bool Scenario::isValid() {
    return f_energy_set && f_protons_set;
}

units::si::HEPEnergyType   Scenario::getCut()      { return f_cut; }
units::si::MassDensityType Scenario::getDensity()  { return f_density; }
units::si::HEPEnergyType   Scenario::getEnergy()   { return f_energy; }
units::si::LengthType      Scenario::getHeight()   { return f_height; }
units::si::LengthType      Scenario::getImpact()   { return f_impact; }
units::si::HEPMassType     Scenario::getMass()     { return f_mass; }
float                      Scenario::getNitrogen() { return f_nitrogen; }
std::string                Scenario::getOutput()   { return f_output; }
double                     Scenario::getPhi()      { return f_phi; }
bool                       Scenario::usingPythia() { return f_pythia; }
//uint64_t                 Scenario::getSeed(); // TODO
bool                       Scenario::usingSibyll() { return f_sibyll; }
double                     Scenario::getTheta()    { return f_theta; }
float                      Scenario::getOxygen()   { return f_oxygen; }
int                        Scenario::getProtons()  { return f_protons; }
bool                       Scenario::error()       { return f_error; }

MomentumVector Scenario::getMomentum(const geometry::CoordinateSystem& v_coordsys) {
    if (!f_energy_set || !f_mass_set) {
        std::cout << "*** energy and/or mass is unset, cannot getMomentum() ***\n";
        throw std::exception {};
    }

    units::si::HEPMomentumType momentum_mag =
            sqrt( f_energy*f_energy - f_mass*f_mass );

    double theta = PI / 180. * f_theta; // radians
    double phi   = PI / 180. * f_phi;   // radians
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
///        "da" has to be handled special, above
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

units::si::HEPMassType Scenario::getHEPMass() {
    if (!f_nucleons_set || !f_protons_set) {
        std::cout << "*** atomic number and/or atomic mass is unset, cannot getHEPMass() ***\n";
        throw std::exception {};
    }
    // TODO: this isn't a good model
    return particles::GetNucleusMass(f_nucleons, f_protons);
}

int Scenario::setNucleons(const char* v_nucleons) {
    try {
        if (f_nucleons_set)
            return err::REPEAT_ERR;
        if (f_mass_set)
            return err::INCOMPAT_ERR;

        f_nucleons = std::stoi(std::string(v_nucleons));
        f_nucleons_set = true;

        if (f_protons_set) {
            f_mass = getHEPMass();
            f_mass_set = true;
        }
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

int Scenario::setCut(const char* v_cut) {
    try {
        if (f_cut_set)
            return err::REPEAT_ERR;

        std::string cut(v_cut);
        double value = std::stod(cut);

        std::size_t unit_start = cut.find_first_of('_');
        if (unit_start == std::string::npos) {
            if (!isdigit(cut.back()) && cut.back() != '.')
                return err::FORMAT_ERR;
            f_cut = value * 1_eV;
            return err::NO_ERR;
        }

        std::size_t prefix_start = cut.find("eV");
        std::size_t len = std::string::npos;
        if (prefix_start != std::string::npos)
            len = prefix_start - unit_start - 1;

        f_cut = value * getScale(cut.substr(unit_start + 1, len)) * 1_eV;
        f_cut_set = true;
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

int Scenario::setDensity(const char* v_density) {
    try {
        if (f_density_set)
            return err::REPEAT_ERR;

        std::string density(v_density);
        double value = std::stod(density);

        std::size_t unit_start = density.find_first_of('_');
        if (unit_start == std::string::npos) {
            if (!isdigit(density.back()) && density.back() != '.')
                return err::FORMAT_ERR;
            f_density = value * 1_kg / (1_m * 1_m * 1_m);
            f_density_set = true;
            return err::NO_ERR;
        }

        f_density = value * getScale(density.substr(unit_start + 1)) * 1_kg / (1_m * 1_m * 1_m);
        f_density_set = true;
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

int Scenario::setEnergy(const char* v_energy) {
    try {
        if (f_energy_set)
            return err::REPEAT_ERR;

        std::string energy(v_energy);
        double value = std::stod(energy);

        std::size_t unit_start = energy.find_first_of('_');
        if (unit_start == std::string::npos) {
            if (!isdigit(energy.back()) && energy.back() != '.')
                return err::FORMAT_ERR;
            f_energy = value * 1_eV;
            f_energy_set = true;
            return err::NO_ERR;
        }

        std::size_t prefix_start = energy.find("eV");
        std::size_t len = std::string::npos;
        if (prefix_start != std::string::npos)
            len = prefix_start - unit_start - 1;

        f_energy = value * getScale(energy.substr(unit_start + 1, len)) * 1_eV;
        f_energy_set = true;
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

int Scenario::setHeight(const char* v_height) {
    try {
        if (f_height_set)
            return err::REPEAT_ERR;

        std::string height(v_height);
        double value = std::stod(height);

        std::size_t unit_start = height.find_first_of('_');
        if (unit_start == std::string::npos) {
            if (!isdigit(height.back()) && height.back() != '.')
                return err::FORMAT_ERR;
            f_height = value * 1_m;
            f_height_set = true;
            return err::NO_ERR;
        }

        std::size_t prefix_start = height.find_last_of('m');
        std::size_t len = std::string::npos;
        if (prefix_start != std::string::npos)
            len = prefix_start - unit_start - 1;

        f_height = value * getScale(height.substr(unit_start + 1, len)) * 1_m;
        f_height_set = true;
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

int Scenario::setImpact(const char* v_impact) {
    try {
        if (f_impact_set)
            return err::REPEAT_ERR;

        std::string impact(v_impact);
        double value = std::stod(impact);

        std::size_t unit_start = impact.find_first_of('_');
        if (unit_start == std::string::npos) {
            if (!isdigit(impact.back()) && impact.back() != '.')
                return err::FORMAT_ERR;
            f_impact = value * 1_m;
            return err::NO_ERR;
        }

        std::size_t prefix_start = impact.find_last_of('m');
        std::size_t len = std::string::npos;
        if (prefix_start != std::string::npos)
            len = prefix_start - unit_start - 1;

        f_impact = value * getScale(impact.substr(unit_start + 1, len)) * 1_m;
        f_impact_set = true;
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

int Scenario::setMass(const char* v_mass) {
    try {
        if (f_mass_set)
            return err::REPEAT_ERR;
        if (f_nucleons_set)
            return err::INCOMPAT_ERR;

        f_mass = std::stod(std::string(v_mass)) * 1_GeV;

        std::string mass(v_mass);
        double value = std::stod(mass);

        std::size_t unit_start = mass.find_first_of('_');
        if (unit_start == std::string::npos) {
            if (!isdigit(mass.back()) && mass.back() != '.')
                return err::FORMAT_ERR;
            f_mass = value * 1_eV;
            f_mass_set = true;
            return err::NO_ERR;
        }

        std::size_t prefix_start = mass.find("eV");
        std::size_t len = std::string::npos;
        if (prefix_start != std::string::npos)
            len = prefix_start - unit_start - 1;

        f_mass = value * getScale(mass.substr(unit_start + 1, len)) * 1_eV;
        f_mass_set = true;
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

int Scenario::setNitrogen(const char* v_nitrogen) {
    try {
        if (f_nitrogen_set)
            return err::REPEAT_ERR;
        if (f_oxygen_set)
            return err::INCOMPAT_ERR;

        f_nitrogen = std::stof(std::string(v_nitrogen));
        f_nitrogen_set = true;
        f_oxygen = 1. - f_nitrogen;
        f_oxygen_set = true;
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

int Scenario::setOutput(const char* v_output) {
    if (f_output_set)
        return err::REPEAT_ERR;
    f_output = std::string(v_output);
    f_output_set = true;
    return err::NO_ERR;
}

int Scenario::setPhi(const char* v_phi) {
    try {
        if (f_phi_set)
            return err::REPEAT_ERR;
        f_phi = std::stod(std::string(v_phi));
        f_phi_set = true;
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

int Scenario::setPythia() {
    if (f_pythia_set)
        return err::REPEAT_ERR;
    if (f_sibyll_set)
        return err::INCOMPAT_ERR;

    f_pythia = true;
    f_pythia_set = true;
    f_sibyll = false;
    return err::NO_ERR;
}

//int setSeed(const char* v_seed); // TODO

int Scenario::setSibyll() {
    if (f_sibyll_set)
        return err::REPEAT_ERR;
    if (f_pythia_set)
        return err::INCOMPAT_ERR;

    f_sibyll = true;
    f_sibyll_set = true;
    f_pythia = false;
    return err::NO_ERR;
}

int Scenario::setTheta(const char* v_theta) {
    try {
        if (f_theta_set)
            return err::REPEAT_ERR;
        f_theta = std::stod(std::string(v_theta));
        f_theta_set = true;
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

int Scenario::setOxygen(const char* v_oxygen) {
    try {
        if (f_oxygen_set)
            return err::REPEAT_ERR;
        if (f_nitrogen_set)
            return err::INCOMPAT_ERR;

        f_oxygen = std::stof(std::string(v_oxygen));
        f_oxygen_set = true;
        f_nitrogen = 1. - f_oxygen;
        f_nitrogen_set = true;
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

int Scenario::setProtons(const char* v_protons) {
    try {
        if (f_protons_set)
            return err::REPEAT_ERR;

        f_protons = std::stoi(std::string(v_protons));
        f_protons_set = true;

        if (f_nucleons_set) {
            f_mass = getHEPMass();
            f_mass_set = true;
        }
    }
    catch (...) {
        return err::FORMAT_ERR;
    }
    return err::NO_ERR;
}

void Scenario::setError() {
    f_error = true;
}

void Scenario::print() {
    const int digits = 5;
    std::cout << "Primary Particle  " << std::endl;
    std::cout << "   Energy:        " << phys::units::io::eng::to_string(f_energy, digits) << std::endl;
    std::cout << "   Protons:       " << f_protons  << std::endl;
    std::cout << "   Nucleons:      " << (f_nucleons_set ? std::to_string(f_nucleons) : "unspecified") << std::endl;
    std::cout << "   Mass:          " << phys::units::io::eng::to_string(f_mass, digits) << std::endl;
    std::cout << "   Theta:         " << f_theta    << " deg" << std::endl;
    std::cout << "   Phi:           " << f_phi      << " deg" << std::endl;
    std::cout << std::endl;
    std::cout << "Simulation        " << std::endl;
    std::cout << "   Cut Energy:    " << phys::units::io::eng::to_string(f_cut, digits) << std::endl;
    std::cout << "   Impact Height: " << phys::units::io::eng::to_string(f_impact, digits) << std::endl;
    std::cout << "   Using Pythia:  " << (f_pythia ? "yes" : "no") << std::endl;
    std::cout << "   Using Sibyll:  " << (f_sibyll ? "yes" : "no") << std::endl;
    //std::cout << "Random Seed:      " << f_seed     << std::endl;
    std::cout << "   Output file:   " << f_output   << std::endl;
    std::cout << std::endl;
    std::cout << "Atmosphere Model  " << std::endl;
    std::cout << "   Height:        " << phys::units::io::eng::to_string(f_height, digits) << std::endl;
    std::cout << "   Density:       " << f_density  << std::endl;
    std::cout << "   Nitrogen Frac: " << f_nitrogen << std::endl;
    std::cout << "   Oxygen Frac:   " << f_oxygen   << std::endl;
}
