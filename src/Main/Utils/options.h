
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
{" Option      GNU long option    Required    Meaning"},
//{""},
{"  -A <num>   --nucleons=<num>               <num> is the Atomic Number of"},
{"                                            the cosmic ray primary nucleus."},
{"                                            Cannot be co-specified with -M."},
{"                                            Default: inactive"},
//{""},
{"  -c <num>   --cut=<num>        Advised     Particles with energy less than"},
{"                                            <num> are not tracked (thinning)."},
{"                                            Default: 100_GeV"},
//{""},
{"  -d <num>   --density=<num>                Density of air at ground-level."},
{"                                            Default: 1.0 [implied kg/m^3]"},
//{""},
{"  -E <num>   --energy=<num>     Yes         <num> is the energy of the cosmic"},
{"                                            ray primary nucleus. It is an"},
{"                                            error if not specified."},
//{""},
{"  -H <num>   --height=<num>                 Altitude limit of the atmosphere."},
{"                                            Default: 112.8_km"},
//{""},
{"  -i <num>   --impact=<num>     Advised     Altitude of first collision of"},
{"                                            CR nucleus and atmosphere."},
{"                                            Default: -H limit"},
//{""},
{"  -M <num>   --mass=<num>       Advised     Molar mass of CR nucleus."},
{"                                            Default: value from the periodic"},
{"                                            table coorisponding to -Z"},
//{""},
{"  -n <num>   --nitrogen=<num>               <num> is between 0 and 1, it is"},
{"                                            the molar fraction of Nitrogen"},
{"                                            in the atmosphere. Cannot be"},
{"                                            co-specified with -x."},
{"                                            Default: 0.79054"},
//{""},
{"  -o <name>  --output=<name>    Advised     <name> is the output filename."},
{"                                            Default: corsis_out.dat"},
//{""},
{"  -p <num>   --phi=<num>        Advised     Azimuthal angle (from south?)."},
{"                                            Can be radians or degrees, e.g."},
{"                                            --phi=1.234_rad, or -p 45_deg."},
{"                                            Default: 0._deg"},
//{""},
{"  -P         --pythia                       Hadronic interaction generator."},
{"                                            Cannot be co-specified with -S."},
{"                                            Default: inactive"},
//{""},
{"  -s <num>   --seed=<num>                   Use <num> as a random number seed"},
{"                                            for the simulation."},
{"                                            Default: _____ todo"},
//{""},
{"  -S         --sibyll                       Hadronic interaction generator."},
{"                                            Cannot be co-specified with -P."},
{"                                            Default: active"},
//{""},
{"  -t <num>   --theta=<num>      Advised     Polar angle (from zenith)."},
{"                                            Can be radians or degrees, e.g."},
{"                                            --theta=4.321_rad, or -t 0_deg."},
{"                                            Default: 0._deg"},
//{""},
{"  -x <num>   --oxygen=<num>                 <num> is between 0 and 1, it is"},
{"                                            the molar fraction of Oxygen in"},
{"                                            the atmosphere. Cannot be co-"},
{"                                            specified with -n."},
{"                                            Default: 0.20946"},
//{""},
{"  -Z <num>   --protons=<num>    Yes         <num> is the Atomic Number of"},
{"                                            the cosmic ray primary nucleus."},
{"                                            It is an error if not specified."},
{""},
{"  -h         --help             n/a         Display this help and exit."},
{"             --version          n/a         Output version information and exit."},
};

#endif
