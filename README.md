# README

This README file provides detailed instructions on how to generate the shim and binary files for the application contained in the provided zip file, as well as how to run the benchmark and generate the resulting text files.

## Prerequisites
Before proceeding, ensure that you have the following prerequisites installed on your system:
- `Linux` (tested on Ubuntu 22.04 LTS)
- `make`
- `gcc` (adhering to at-least the C++11 Standard)
- `Python 3` (for running the script to generate the visual graph)
    - `Plotly` (for generating the visual graph.  Can be installed using `pip install plotly`)

## USAGE: Generating the Shim and Binary Files
1. Extract the contents of the provided zip file to a directory of your choice.
2. Open a terminal and navigate to the extracted directory.
3. Type `make` and press Enter. This will execute the Makefile and generate the shim and binary files for the application.

## Running the Benchmark
Once you have successfully generated the shim and binary files, follow the below steps to run the benchmark and generate the text files for analysis:

1. In the terminal, navigate to the directory where the shim and binary files are located.
2. Type the following command and press Enter:
    ```
    LD_PRELOAD="./open_shim.so" ./benchmark
    ```
    This command sets the `LD_PRELOAD` environment variable to load the shim library before executing the `benchmark` binary.

3. Wait for the benchmark to complete. After it is complete, there will be a cue in the terminal indicating that the benchmark has generated the text files.

## Viewing the Results
After the benchmark has finished running, two text files will be generated in the same directory. These files contain the following information:

- `readlink_nanoseconds.txt`: This file contains the measured time in nanoseconds for the `readlink` operation during the benchmark.
- `open_nanoseconds.txt`: This file contains the measured time in nanoseconds for the `open` operation during the benchmark.

To aid a visual display of this analysis, we have a Python script called `script.py` that utilizes the Plotly library.
You can run it using the command `python3 script.py` to generate a nice visual graph.

