
#ifndef _include_corsis_utils_options_h_
#define _include_corsis_utils_options_h_

#include <corsis/utils/input.h>

// simple options as a single-character list
// characters with a following colon(:) have arguments, e.g. "a:" <=> -a 5
const char *options = "A:c:d:E:H:i:M:n:o:p:Ps:St:x:Z:h";


// long option struct defined in getopt.h
// { name, has_arg, flag, val }
//    name: (const char*) duh
// has_arg: (int) no_argument(or 0),
//                required_argument(or 1),
//                optional_argument(or 2)
//    flag: (int*) variable that is set to val only if option is found
//     val: (int) value returned by getopt_long() if option is found
// The last element of the array has to be filled with zeros
const struct option long_options[] = {
    {"nucleons", required_argument, 0, 'A'},
    {"cut",      required_argument, 0, 'c'},
    {"density",  required_argument, 0, 'd'},
    {"energy",   required_argument, 0, 'E'},
    {"height",   required_argument, 0, 'H'},
    {"impact",   required_argument, 0, 'i'},
    {"mass",     required_argument, 0, 'M'},
    {"nitrogen", required_argument, 0, 'n'},
    {"output",   required_argument, 0, 'o'},
    {"phi",      required_argument, 0, 'p'},
    {"pythia",   no_argument      , 0, 'P'},
    {"seed",     required_argument, 0, 's'},
    {"sibyll",   no_argument      , 0, 'S'},
    {"theta",    required_argument, 0, 't'},
    {"oxygen",   required_argument, 0, 'x'},
    {"protons",  required_argument, 0, 'Z'},
    {"help",     no_argument,       0, 'h'},
    {"version",  no_argument,       0, 'V'},
    {0,          0,                 0,  0 }
};


// Descriptions
struct Help { std::string option; };
const Help options_help[] = {
{" Option      GNU long option    Units    Required    Meaning"},
//{""},
{"  -A <num>   --nucleons=<num>   none                 <num> is the (integer) Atomic Number"},
{"                                                     of the cosmic ray primary nucleus."},
{"                                                     Cannot be co-specified with -M."},
{"                                                     Default: inactive, see -M"},
//{""},
{"  -c <num>   --cut=<num>        _eV      Advised     Particles with energy less than"},
{"                                                     <num> are not tracked (thinning)."},
{"                                                     Default: 100_GeV"},
//{""},
{"  -d <num>   --density=<num>    none                 Density of air at ground-level."},
{"                                                     Default: 1.0 [implied kg/m^3]"},
//{""},
{"  -E <num>   --energy=<num>     _eV      Yes         <num> is the energy of the cosmic"},
{"                                                     ray primary nucleus. It is an"},
{"                                                     error if not specified."},
//{""},
{"  -H <num>   --height=<num>     _m                   Altitude limit of the atmosphere."},
{"                                                     Default: 112.8_km"},
//{""},
{"  -i <num>   --impact=<num>     _m       Advised     Altitude (z) of first collision of"},
{"                                                     CR nucleus and atmosphere."},
{"                                                     The x and y location is implicitly"},
{"                                                     determined by choice of --theta and"},
{"                                                     --phi such that the shower develops"},
{"                                                     heading towards (x,y,z) = (0,0,0)."},
{"                                                     Default: -H limit"},
//{""},
{"  -M <num>   --mass=<num>       _eV      Advised     Molar mass of CR nucleus."},
{"                                                     Default: value estimated from"},
{"                                                     the periodic table for -Z"},
//{""},
{"  -n <num>   --nitrogen=<num>   none                 <num> is between 0 and 1, it is"},
{"                                                     the molar fraction of Nitrogen"},
{"                                                     in the atmosphere. Cannot be"},
{"                                                     co-specified with -x."},
{"                                                     Default: 0.79054"},
//{""},
{"  -o <name>  --output=<name>    n/a      Advised     <name> is the output filename."},
{"                                                     Default: corsis_out.dat"},
//{""},
{"  -p <num>   --phi=<num>        none     Advised     Azimuthal angle (south=x, east=y)."},
{"                                                     Default: 0. [implied degrees]"},
//{""},
{"  -P         --pythia           n/a                  Hadronic interaction generator."},
{"                                                     Cannot be co-specified with -S."},
{"                                                     Default: disabled"},
//{""},
{"  -s <num>   --seed=<num>       n/a                  Use <num> as a random number seed"},
{"                                                     for the simulation."},
{"                                                     TODO: **DOES NOTHING**"},
//{""},
{"  -S         --sibyll           n/a                  Hadronic interaction generator."},
{"                                                     Cannot be co-specified with -P."},
{"                                                     Default: active"},
//{""},
{"  -t <num>   --theta=<num>      none     Advised     Polar angle (from zenith)."},
{"                                                     Default: 0. [implied degrees]"},
//{""},
{"  -x <num>   --oxygen=<num>     none                 <num> is between 0 and 1, it is"},
{"                                                     the molar fraction of Oxygen in"},
{"                                                     the atmosphere. Cannot be co-"},
{"                                                     specified with -n."},
{"                                                     Default: 0.20946"},
//{""},
{"  -Z <num>   --protons=<num>    none     Yes         <num> is the (integer) Atomic Number of"},
{"                                                     the cosmic ray primary nucleus."},
{"                                                     It is an error if not specified."},
{""},
{"  -h         --help             n/a      n/a         Display this help and exit."},
{"             --version          n/a      n/a         Output version information and exit."},
{""},
{"Optional metric prefixes for units: y z a p n u m c d da h k M G T P E Z Y"},
{"If no units accompany a number, the default base unit is assumed,"},
{"e.g. --mass 32_G or 32e9 is understood as 32_GeV"},
{""},
{" examples:"},
{""},
{"   $ corsis -E 1.23e18 -Z 8"},
{"   $ corsis --energy 4.56_PeV --protons=26 -i1E3_m --mass 6e1_GeV -t 45 -P"},
{""},
{" source code: https://github.com/ealbin/crayfis-corsika"}
};

#endif
