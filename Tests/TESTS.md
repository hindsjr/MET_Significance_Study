# MET Significance Study Tests

CMSE 802 Final Project: MET Significance Study

By Julia Hinds
ATLAS Collaboration

## Overview
This document contains information regarding testing the significance calculation code. For information on how to run the framework, please see the example documentation in the Example/ directory. 

## Types of Tests

The beginning of the code consists of actual tests functions. Unfortunately, the C++ assert function was not cooperating so the workaround used was dividing the two values to see if they were similar. Otherwise, the significance calculation function was set to return a value of -1 if there were any issues encountered. 

```isSame1``` checks to see if the significance from two constant histograms (values of pi and pi/2) equal what we expected

```isSame2``` checks to see if the significance from a gaussian "signal" and two constant "backgrounds" (values of pi and pi/2) give the significance we expected

```isNotPushedBack``` checks to see if an empty vector of histograms is passed

```tooFewHists``` checks to make sure background histograms were pushed back

```notSignal``` checks to make sure the first signal is indeed a signal histogram (here, only checking for HVT signal)

Also, the overflow bin was set to 100 to ensure it was not being included in the calculation. 

## How to Run

First, ensure the ROOT environment is activated (see the README for further information).

To run:
```root myUnitTest.C```

## Interpreting the Results

The code should print out the test it is running and if it passes. Then it will print to screen if they are pass or if one fails. If a test fails, then final result will indicate they all did not pass and you can see which test did not pass.

