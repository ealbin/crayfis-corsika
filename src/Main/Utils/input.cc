
#include <corsis/utils/input.h>
#include <corsis/utils/options.h>

std::string getCmdName(char *v_cmd) {
    std::string cmd(v_cmd);
    const std::size_t last_slash_index = cmd.find_last_of("\\/");
    if (std::string::npos != last_slash_index)
        cmd.erase(0, last_slash_index + 1);
    return cmd;
}

void showHelp(const std::string& v_cmd) {
    printf("\n");
    printf("Usage: %s [OPTION]...\n", v_cmd.c_str());
    printf("Simulate extensive air showers\n");
    printf("\n");
    for (Help help_line : options_help)
        printf("%s\n", help_line.option.c_str());
}

void showVersion(const std::string& v_cmd) {
    printf("\n");
    printf("%s version %s\n", v_cmd.c_str(), VERSION.c_str());
    printf("2019 CRAYFIS Project.. or something\n");
}

void showFormatErr(const std::string& v_cmd, char *v_arg) {
    printf("%s: option '%s' is not formatted properly\n", v_cmd.c_str(), v_arg);
    printf("Try '%s --help' for more information.\n", v_cmd.c_str());
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
                if (v_scenario.setNucleons(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // cut
            case 'c':
                if (v_scenario.setCut(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // density
            case 'd':
                if (v_scenario.setDensity(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // energy
            case 'E':
                if (v_scenario.setEnergy(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // height
            case 'H':
                if (v_scenario.setHeight(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // impact
            case 'i':
                if (v_scenario.setImpact(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // mass
            case 'M':
                if (v_scenario.setMass(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // nitrogen
            case 'n':
                if (v_scenario.setNitrogen(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // output
            case 'o':
                if (v_scenario.setOutput(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // phi
            case 'p':
                if (v_scenario.setPhi(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // pythia
            case 'P':
                if (v_scenario.setPythia()) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // seed
            //case 's':
            //    v_scenario.seed = std::string(optarg);
            //    break;

            // sibyll
            case 'S':
                if (v_scenario.setSibyll()) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // theta
            case 't':
                if (v_scenario.setTheta(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // oxygen
            case 'x':
                if (v_scenario.setOxygen(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // protons
            case 'Z':
                if (v_scenario.setProtons(optarg)) {
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                }
                break;

            // help
            case 'h':
                showHelp(cmd);
                v_scenario.setError();
                return;

            // version
            case 'V':
                showVersion(cmd);
                v_scenario.setError();
                return;

            case '?':
                printf("%s: option '%s' requires an argument\n", cmd.c_str(), v_argv[start_index]);
                printf("Try '%s --help' for more information.\n", cmd.c_str());
                v_scenario.setError();
                return;

            // in case of error
            default:
                printf("%s: unrecognized option '%s'\n", cmd.c_str(), v_argv[start_index]);
                printf("Try '%s --help' for more information.\n", cmd.c_str());
                v_scenario.setError();
                return;
        }
    }

    if (optind < v_argc) {
        printf("%s: unrecognized option '%s'\n", cmd.c_str(), v_argv[optind]);
        printf("Try '%s --help' for more information.\n", cmd.c_str());
        v_scenario.setError();
    }
}
