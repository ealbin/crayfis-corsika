# CORSIKA 8 (CRAYFIS) Framework for Particle Cascades in Astroparticle Physics 

## Taken from: https://gitlab.ikp.kit.edu/AirShowerPhysics/corsika

The purpose of CORSIKA is to simulate any particle cascades in
astroparticle physics or astrophysical context. A lot of emphasis is
put on modularity, flexibility, completeness, validation and
correctness. To boost computational efficiency different techniques
are provided, like thinning or cascade equations. The aim is that
CORSIKA remains the most comprehensive framework for simulating
particle cascades with stochastic and continuous processes.

The software makes extensive use of static design patterns and
compiler optimization. Thus, the most fundamental configuration
decision of the user must be performed at compile time. At run time
only specific model parameters can still be changed.

CORSIKA 8 is released under the GPLv3 license. This does not exclude
that specific CORSIKA 8 versions can be released for specific purposes
under different licensing. See [license 
file](https://gitlab.ikp.kit.edu/AirShowerPhysics/corsika/blob/master/LICENSE)
which is part of every release and the source code.

If you use, or want to refer to, CORSIKA 8 please cite ["Towards a Next
Generation of CORSIKA: A Framework for the Simulation of Particle
Cascades in Astroparticle Physics", Comput.Softw.Big Sci. 3 (2019)
2](https://doi.org/10.1007/s41781-018-0013-0). We kindly ask (and
expect) any relevant improvement or addition to be offered or
contributed to the main CORSIKA 8 repository for the benefit of the
whole community.

## Minimum Requirements
* Ubuntu 18.04
* gcc7.3.0
* clang-6.0.0
* cmake3.9.0

## Full Requirements
* libeigen3-dev
* doxygen
* graphviz
* gnuplot

## Installation

On a bare Ubuntu 18.04 (if needed),
```
sudo apt install cmake g++ libeigen3-dev doxygen graphviz
mkdir build
```
Then,
```
cd ./build
cmake ../src -DCMAKE_INSTALL_PREFIX=../install
make -j8
make install
make test
```

If you want to see how the first simple hadron cascade develops, see `Documentation/Examples/cascade_example.cc` for a starting point. 

Run the cascade_example with: 
```
cd ../install
share/examples/cascade_example
```

Visualize output (needs gnuplot installed): 
```
bash share/tools/plot_tracks.sh tracks.dat 
firefox tracks.dat.gif 
```

### Generating doxygen documentation

To generate the documentation, do:
```
cd ../build
make doxygen
make install
```
browse with firefox:
```
firefox ../corsika-install/share/doc/html/index.html
```

### CRAYFIS customizations
(CORSIS) COsmic Ray SImulations for Smartphones
TODO: this documentation
