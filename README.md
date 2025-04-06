# MET Significance Study

CMSE 802 Final Project: MET Significance Study

By Julia Hinds
ATLAS Collaboration

## Overview
Particle physics is the physics that probes the fundamental building blocks of nature. One way in which this is done is by colliding particles near the speed of light. The European Organization for Nuclear Research (CERN) is the largest facility in the world that conducts this research. It is comprised of the world’s largest particle accelerator - the Large Hadron Collider (LHC) - and four detectors along the LHC's path. The detector we are focusing on is the ATLAS Detector (A Toroidal LHC ApparatuS). Here, particles are collided at extremely high energies in hopes of discovering new physics. 
In order for us to be able to detect new physics in the ATLAS detector (which is a rare process - showing up as a small signal, or "bump", in our data), we want to minimize the background processes while maximizing the signal making it easier for us to identify. We have several variables that describe an event or collision in the detector, and the signal would have a subtly different distribution in these variables to the background (which sometimes have to be teased out). Thus, optimizing the selection of events which have certain restrictions (i.e. cuts) to some variables, could enhance the number of signal events selected compared to the background.
Additionally, if an optimal cut is achieved, then it could be used to replace current cuts to the data to try to bring increased sensitivity to the entire analysis.

## Structure

The main structure of this repository is as follows:
- METSignificanceStudy
    - Contains the codes to run the study 
        - ```AtlasStyle```  are used and provided by the ATLAS collaboration
        - ```CutFlowProduction``` is used to produce the cutflow of the analysis
        - ```VV_VH_distributions_plotting``` is a plotting notebook used to produce 1D and 2D histograms
        - ```METSigStudy``` is used to calculate the signal significance vs METSig cut for different signal masses from the 2D histograms in the data file
        - ```Additional/``` contains supplemental code that was used for different milestones throughout the semester
        
- LICENSE
    - Contains licensing information
- Models
    - Contains model reports
- doc
    - Contains documentation of the project (as well as a copy of model reports)
    - ```Documentation.md``` contains information about issues, problems, and challenges encountered throughout the semester
- Samples
    - Contains ROOT samples which one could use to run the code with (main samples are contained on CERN's server)
- Example
    - Instructions on how to run an example version of the code
    - ```EXAMPLE.md``` contains steps and information about each piece of code
- Tests
    - Code that can be used to test the main function of interest. Since C++ and ROOT are used, the test is not a traditional unit test but a hand-made version that is meant to be similar.
    - ```TESTS.md``` contains information about each test and how to run them
- Results
    - Contains plots and histograms which are the outputs for each piece of code
- ```setup_env.sh``` 
    - Sets up the environment (see below)
- ```remove_env.sh``` 
    - Removes the environment (see below)
- Dockerfile
    - attempt of making a Docker Image
    - see ```doc/Documentation.md``` for more information
- ```METSigStudy.pptx```
    - Final presentation powerpoint
- ```PROJECT_PROPOSAL.ipynb```
    - Original project proposal
- ```FINAL_REPORT.ipynb```
    - Final project report

## Installation of the environment

- To setup the ROOT environment
    - ```source setup_env.sh```
- To deactivate the environment
    - ```source remove_env.sh```
    - NOTE: inside ```remove_env.sh``` contains information and commented code to completely remove the environment if desired
    

## Current Issues
- None. 

## References
- CxAOD Reader Framework. ```https://gitlab.cern.ch/CxAODFramework/CxAODReader_VVSemileptonic/-/tree/dev-hinds```
- Search for heavy diboson resonances in semileptonic final states in pp collisions at sqrt(s)=13  TeV with the ATLAS detector. ```https://arxiv.org/abs/2004.14636```

## Licensing
Copyright (C) 2002-2022 CERN for the benefit of the ATLAS collaboration 

All METSignificanceStudy analysis code is my own. 

