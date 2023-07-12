# real-time-granular VST

Real time granular VST effect built in C++ and JUCE. Built for FL Studio, but compatibable for all Digital Audio Workstations

## Building

Clone the repository:
```
$ git clone https://github.com/hashcoins/real-time-granular.git --recursive
$ cd real-time-granular
```
Export the RNBO patch with the following configuration options:
- Output Directory: `YOUR_PATH_TO_THIS_PROJECT/real-time-granular/RnboExport`
- Export Name: `rnbo_granular.cpp`

Build with CMake:
```
$ cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build --config Release
```

## References
- [JUCE Demo](https://github.com/szkkng/kengo-dev)
- [Programming a Custom UI with JUCE](https://rnbo.cycling74.com/learn/programming-a-custom-ui-with-juce)
- [RNBO C++ API Reference](https://rnbo.cycling74.com/cpp)
- [Cycling74/gen-plugin-export](https://github.com/Cycling74/gen-plugin-export)

