# MET Significance Study Documentation

CMSE 802 Final Project: MET Significance Study

By Julia Hinds
ATLAS Collaboration

## Overview
This document contains information on issues that occurred during the development of this framework. For information on how to run the framework, please see the example documentation in the Example/ directory. 

## Creating a Docker Image

The first two steps in the analysis framework must be ran from CERN's server because of specific libraries that exist there. I tried to generate a docker image that would allow someone to temporarily generate the same environment and run the codes - however, this process was actually very difficult since I am still trying to learn how the setup works. An alternative method would be to download the CxAOD framework (which is the precursor to this analysis); however, that also required CERN authorization. After about 4 hours of trying to get this to work, I decided to just include a setup script to create a general ROOT environment where someone could at least run the last piece of code (which is arguably the most important piece in this analysis). 

The Docker file is still contained in this git repo, and I am open to suggestions on how to improve it.

## Cross validation with external analysis code

A validation I needed to do for my PhD thesis analysis was to look at different jet collection significances to see if the most recent jet collection algorithm (PFlow+UFO) was indeed the best one. Here, I developed a hard-coded method of calculating the significance from data files. Thus, when this project started going I developed a simpler function to calculate the significance from input histograms. One way I tried to validate this function's accuracy was comparing the zero-METSig cut significance for a specific jet collection to previous results. However, there was a slight disagreement between the two calculated significances. The first cross validation I tried was to implement the significance calculation function into my previous code (where it was originally hard-coded). This produced results that differed from original results with the significance hard-coded. Due to the fact the significance calculation in the function was cleaner and easier to follow (and not hard coded), I believed that the function was indeed more correct and the hard-coded version was probably taking into account the overflow or underflow bin into the calculation. Thus, I produced some tests (included in the Tests/myUnitTest.C code) where I calculated the significance by hand with simple histograms and compared it to the function output; and indeed they match. I plan to use the function going forward in my PhD analysis. 

## Cutflow validation for VH

During the course of this semester, my original analysis group (the VV Semileptonic Analysis) merged with the VH Semileptonic Analysis. This is because both groups have historically been looking in the same signal regions and looking for semi-leptonic final states. The only difference was VV consisted of WW, WZ, and ZZ states whereas the VH consisted of WH and ZH states (where W = W boson, Z = Z boson, and H = Higgs boson). So, merging increasing the manpower with both analysis groups. My research focuses on the 0-lepton channel so I've been added as the main analyzer for the VH-analysis group as well. This meant we had to implement VH changes into the CxAOD framework. Thus, I had to cross check the cutflow for VH and modify it slightly to make sure the framework was working correctly. This took about a month to implement and check, which means the 0-lep channel is fully harmonized between VV and VH; but unfortunately, was not something I originally foresaw when proposing this project. 


## Unit tests, linting, and auto-documentation with C++ and ROOT

Unit testing with C++ is not extremely challenging (not something covered in class but there were a few examples online). However, including the ROOT variables in the C++ code complicated the unit testing codes and I was unable to get any of them to recognize the ROOT variables (which were oftentimes the inputs into functions). Thus, I developed my over version of testing to ensure the calculation was actually producing the results we wanted. 

Linting and auto-documentation also proved to be difficult with C++ and ROOT. Honestly, I could not figure it out and did not find anything useful online.




