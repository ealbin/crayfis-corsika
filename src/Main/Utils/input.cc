
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
    printf("COsmic Ray SImulations for Smartphones (CORSIS)\n");
    printf("using CORSIKA v8 (Milestone 2) as the backend\n");
    printf("\n");
    for (Help help_line : options_help)
        printf("%s\n", help_line.option.c_str());
}

void showVersion(const std::string& v_cmd) {
    printf("\n");
    printf("%s version %s, %s\n", v_cmd.c_str(), VERSION.c_str(), DATE.c_str());
    printf("Extensive Air Shower Simulator for the CRAYFIS Project\n");
    printf("University of California, Irvine\n");
    printf("Department of Physics and Astronomy\n");
    printf("Author: Eric Albin, Eric.K.Albin@gmail.com\n");
    printf("Source code: https://github.com/ealbin/crayfis-corsika\n");
}

void showFormatErr(const std::string& v_cmd, char *v_arg) {
    printf("%s: option '%s' is not formatted properly\n", v_cmd.c_str(), v_arg);
    printf("Try '%s --help' for more information.\n", v_cmd.c_str());
}

void showRepeatErr(const std::string& v_cmd, char *v_arg) {
    printf("%s: option '%s' is set more than once\n", v_cmd.c_str(), v_arg);
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
                switch (v_scenario.setNucleons(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::INCOMPAT_ERR:
                    printf("%s: options '-A and -M' cannot both be set\n", cmd.c_str());
                    printf("Try '%s --help' for more information.\n", cmd.c_str());
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // cut
            case 'c':
                switch (v_scenario.setCut(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // density
            case 'd':
                switch (v_scenario.setDensity(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // energy
            case 'E':
                switch (v_scenario.setEnergy(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // height
            case 'H':
                switch (v_scenario.setHeight(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // impact
            case 'i':
                switch (v_scenario.setImpact(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // mass
            case 'M':
                switch (v_scenario.setMass(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::INCOMPAT_ERR:
                    printf("%s: options '-A and -M' cannot both be set\n", cmd.c_str());
                    printf("Try '%s --help' for more information.\n", cmd.c_str());
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // nitrogen
            case 'n':
                switch (v_scenario.setNitrogen(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::INCOMPAT_ERR:
                    printf("%s: options '-n and -x' cannot both be set\n", cmd.c_str());
                    printf("Try '%s --help' for more information.\n", cmd.c_str());
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // output
            case 'o':
                switch (v_scenario.setOutput(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // phi
            case 'p':
                switch (v_scenario.setPhi(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // pythia
            case 'P':
                switch (v_scenario.setPythia()) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::INCOMPAT_ERR:
                    printf("%s: options '-P and -S' cannot both be set\n", cmd.c_str());
                    printf("Try '%s --help' for more information.\n", cmd.c_str());
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // seed
            //case 's':
            //    v_scenario.seed = std::string(optarg);
            //    break;

            // sibyll
            case 'S':
                switch (v_scenario.setSibyll()) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::INCOMPAT_ERR:
                    printf("%s: options '-P and -S' cannot both be set\n", cmd.c_str());
                    printf("Try '%s --help' for more information.\n", cmd.c_str());
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // theta
            case 't':
                switch (v_scenario.setTheta(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // oxygen
            case 'x':
                switch (v_scenario.setPhi(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::INCOMPAT_ERR:
                    printf("%s: options '-n and -x' cannot both be set\n", cmd.c_str());
                    printf("Try '%s --help' for more information.\n", cmd.c_str());
                    v_scenario.setError();
                    return;
                default:
                    break;
                }
                break;

            // protons
            case 'Z':
                switch (v_scenario.setProtons(optarg)) {
                case err::FORMAT_ERR:
                    showFormatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                case err::REPEAT_ERR:
                    showRepeatErr(cmd, v_argv[start_index]);
                    v_scenario.setError();
                    return;
                default:
                    break;
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
        return;
    }

    if (!v_scenario.isValid()) {
        printf("%s: at minimum, options '-Z and -E' must be set\n", cmd.c_str());
        printf("Try '%s --help' for more information.\n", cmd.c_str());
        v_scenario.setError();
        return;
    }
}
