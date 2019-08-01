
#ifndef _include_corsis_utils_input_h_
#define _include_corsis_utils_input_h_

#include <corsis/utils/Scenario.h>

#include <getopt.h>
#include <stdio.h>  /* for printf */

const std::string VERSION = "1.0.0";
const std::string DATE = "Aug 2019";

/*
 * TODO: documentation
 */
void readInput(int v_argc, char *v_argv[], Scenario &v_scenario);

#endif
