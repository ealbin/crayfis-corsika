
#include <corsis/utils/input.h>
#include <corsis/utils/options.h>

#include <stdlib.h> /* atof */


std::string getCmdName(char *v_cmd) {
    std::string cmd(v_cmd);
    const std::size_t last_slash_index = cmd.find_last_of("\\/");
    if (std::string::npos != last_slash_index)
        cmd.erase(0, last_slash_index + 1);
    return cmd;
}

void showHelp(const std::string& cmd) {
    printf("\n");
    printf("Usage: %s [OPTION]...\n", cmd.c_str());
    printf("Simulate extensive air showers\n");
    printf("\n");
    for (Help help_line : options_help)
        printf("%s\n", help_line.option.c_str());
}

void showVersion(const std::string& cmd) {
    printf("\n");
    printf("%s version %s\n", cmd.c_str(), VERSION.c_str());
    printf("2019 CRAYFIS Project.. or something\n");
}

void readInput(int v_argc, char *v_argv[], Scenario &v_scenario) {

    const std::string& cmd = getCmdName(v_argv[0]);

    // disable automatic error messages from getopt
    opterr = 0;

    // parse input
    while (true) {

        // getopt_long returns -1 when option parsing is exhausted, otherwise
        // it's the options character as specified in options above
        int opt_val = -1;

        // index of long_options[] if long option is found
        int long_opt_index = -1;

        // option index before getopt()
        int start_index = optind ? optind : 1;

        // process next option
        opt_val = getopt_long(v_argc, v_argv, options,
                              long_options, &long_opt_index);

        // all options have been parsed
        if (opt_val == -1)
            break;

        switch (opt_val) {

            // nucleons
            case 'A':
                v_scenario.nucleons = std::string(optarg);
                break;

            // cut
            case 'c':
                v_scenario.cut = std::string(optarg);
                break;

            // density
            case 'd':
                v_scenario.density = std::string(optarg);
                break;

            // energy
            case 'E':
                v_scenario.energy = std::string(optarg);
                break;

            // height
            case 'H':
                v_scenario.height = std::string(optarg);
                break;

            // impact
            case 'i':
                v_scenario.impact = std::string(optarg);
                break;

            // mass
            case 'M':
                v_scenario.mass = std::string(optarg);
                break;

            // nitrogen
            case 'n':
                v_scenario.nitrogen = std::string(optarg);
                break;

            // output
            case 'o':
                v_scenario.output = std::string(optarg);
                break;

            // phi
            case 'p':
                v_scenario.phi = std::string(optarg);
                break;

            // pythia
            case 'P':
                v_scenario.pythia = true;
                break;

            // seed
            case 's':
                v_scenario.seed = std::string(optarg);
                break;

            // sibyll
            case 'S':
                v_scenario.sibyll = true;
                break;

            // theta
            case 't':
                v_scenario.theta = std::string(optarg);
                break;

            // oxygen
            case 'x':
                v_scenario.oxygen = std::string(optarg);
                break;

            // protons
            case 'Z':
                v_scenario.protons = std::string(optarg);
                break;

            // help
            case 'h':
                showHelp(cmd);
                v_scenario.exit = true;
                return;

            // version
            case 'V':
                showVersion(cmd);
                v_scenario.exit = true;
                return;

            case '?':
                printf("%s: option '%s' requires an argument\n", cmd.c_str(), v_argv[start_index]);
                printf("Try '%s --help' for more information.\n", cmd.c_str());
                v_scenario.exit = true;
                return;

            // in case of error
            default:
                printf("%s: unrecognized option '%s'\n", cmd.c_str(), v_argv[start_index]);
                printf("Try '%s --help' for more information.\n", cmd.c_str());
                v_scenario.exit = true;
                return;
        }
    }

    if (optind < v_argc) {
        printf("%s: unrecognized option '%s'\n", cmd.c_str(), v_argv[optind]);
        printf("Try '%s --help' for more information.\n", cmd.c_str());
        v_scenario.exit = true;
    }
}
