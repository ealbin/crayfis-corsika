// TODO: --help doesn't work right yet
// TODO: options

#include <corsis/utils/input.h>

#include <getopt.h>
#include <stdio.h>  /* for printf */
#include <string>

// long option struct defined in getopt.h
// { name, has_arg, flag, val }
//    name: (const char*) duh
// has_arg: (int) no_argument(or 0),
//                required_argument(or 1),
//                optional_argument(or 2)
//    flag: (int*) variable that is set to val only if option is found
//     val: (int) value returned by getopt_long() if option is found
// The last element of the array has to be filled with zeros
int help_flag = 0;
const int NEED_HELP = 1;
const struct option long_options[] = {
    {"help",    no_argument,       &help_flag,  NEED_HELP },
    {"add",     required_argument, 0,  0 },
    {"append",  no_argument,       0,  0 },
    {"delete",  required_argument, 0,  0 },
    {"verbose", no_argument,       0,  0 },
    {"create",  required_argument, 0, 'c'},
    {"file",    required_argument, 0,  0 },
    {0,         0,                 0,  0 }
};

/*
 * Things:
 *  assume this is for nuclei only
 *
 *  reserved:  -h --help
 *
 *  -H --height
 *  (opt) atmosphere height (default 112.8_km)
 *  -i --impact
 *  (opt) start altitude (default atmosphere height)
 *  -s --seed
 *  (opt) random seed (default: _____ todo)
 *  -d --density
 *  (opt) air density
 *  -x --oxygen
 *  -n --nitrogen (can't specify both)
 *  (opt) oxygen fraction (nitrogen fraction implied) (default: .20946)
 *  -Z --protons
 *  (req) Z
 *  -A --nucleons
 *  -M --mass
 *  (req?) A or mass
 *  -E --energy
 *  (req) E
 *  -t --theta
 *  (opt) theta (default 0)
 *  -p --phi
 *  (opt) phi (default 0)
 *  -S --sibyll, -P --pythia
 *  (opt) sibyll or pythia (default sibyll)
 *  -c --cut
 *  (opt) particle cut (default ? 80_GeV)
 *  -o --output
 *  (opt) output file(s)
 *
 */


// simple options as a single-character list
// characters with a following colon(:) have arguments, e.g. -a 5 => "a:"
const char *options = "habc:d:012";

void help(char *command) {
    std::string cmd (command);
    const std::size_t last_slash_index = cmd.find_last_of("\\/");
    if (std::string::npos != last_slash_index)
        cmd.erase(0, last_slash_index + 1);
    printf("\n");
    printf("Usage: %s [OPTION]...\n", cmd.c_str());
    printf("Simulate extensive air showers\n");
    printf("\n");
    printf("Options are listed here:\n");
}

void readInput(int argc, char *argv[]) {

    // ?
    int digit_optind = 0;

    // parse input
    while (1) {

        // getopt_long returns -1 when option parsing is exhausted, otherwise
        // it's the options character as specified in options above
        static int option_val = 0;

        // index of long_options[] if long option is found
        int long_option_index = 0;

        // makes sure to begin with argv[1] if readInput is called again
        int this_option_optind = optind ? optind : 1;

        option_val = getopt_long(argc, argv,
                                 options, long_options, &long_option_index);
        if (option_val == -1)
            break;

        switch (option_val) {
        case NEED_HELP:
            help(argv[0]);
            break;
        case 'h':
            help(argv[0]);
            help_flag = NEED_HELP;
            break;

        case 0:
            printf("option %s", long_options[long_option_index].name);
            if (optarg)
                printf(" with arg %s", optarg);
            printf("\n");
            break;

        case '0':
        case '1':
        case '2':
            if (digit_optind != 0 && digit_optind != this_option_optind)
                printf("digits occur in two different argv-elements.\n");
            digit_optind = this_option_optind;
            printf("option %c\n", option_val);
            break;

        case 'a':
            printf("option a\n");
            break;

        case 'b':
            printf("option b\n");
            break;

        case 'c':
            printf("option c with value '%s'\n", optarg);
            break;

        case 'd':
            printf("option d with value '%s'\n", optarg);
            break;

        case '?':
            help(argv[0]);
            help_flag = NEED_HELP;
            break;

        default:
            printf("?? getopt returned character code 0%o ??\n", option_val);
        }
    }

    if (help_flag == NEED_HELP) {
        return;
    }

    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }
}
