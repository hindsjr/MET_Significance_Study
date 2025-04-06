# MET Significance Study Example

CMSE 802 Final Project: MET Significance Study

By Julia Hinds
ATLAS Collaboration

## Overview
This example provides you with steps to run the METSignificanceStudy analysis framework. Please note, parts I and II can only be completed on CERN's server (lxplus). Part III can be completed locally with just the initial ROOT environment installed. Results from all parts will exist in the Result/ directory.

## General setup on lxplus

If you are able to connect to CERN's server, download the main CxAODReader git repository in order to set up the environment.
```git clone -b dev-hinds https://gitlab.cern.ch/CxAODFramework/CxAODReader_VVSemileptonic.git```

Next, run the following commands to compile the package:
```
mkdir build run
cd CxAODReader_VVSemileptonic/
git submodule update
for p in CxAODTools ; do cp -R /afs/cern.ch/work/v/vhbbframework/public/data/dataForCxAODFramework_190225/$p/* $p/data/; done
#---
cd ../build
asetup AnalysisBase, 21.2.178, here
cp CMakeLists.txt ../CxAODReader_VVSemileptonic/.
cmake -DBUILTIN_BOOST=true -DBUILTIN_EIGEN=true ../CxAODReader_VVSemileptonic/
make -j8
source  x86_64-*/setup.sh
```

Now that the environment has been set up, proceed to the METSignificanceStudy analysis framework and proceed to the rest of the example.

## Jupyter notebook setup on lxplus

If you are able to connect to CERN's server, follow these directions to properly log-in so that Jupyter Notebook can be used.

First, ssh into lxplus  ```ssh -L 8099:localhost:8095 xxx@lxplus.cern.ch```, where xxx is your username.

Next, source a setup script that will setup lxplus permissions:
```source /cvmfs/sft.cern.ch/lcg/views/LCG_95apython3/x86_64-centos7-gcc7-opt/setup.sh```

Now, move to the directory that you will want to launch Jupyter Notebook and launch like the following:
```jupyter notebook --no-browser --port=8095```

This will prompt a url be displayed on your terminal screen. Copy and paste that into an internet browser and change ```8095``` to ```8099```.

You should now have access to your files via the Jupyter Notebook interface.


## Part I: Cutflow Production

The cutflow is a representation of how many events pass each sequential cut. It is an important visualization to see how the amount of signal and background events are passes with each cut. The overall goal is to improve the significance (which can be thought of loosely as the signal-to-background ratio), so visually seeing the separation  is important.

The main code is contained in ```CutFlowProduction.C``` with some specific functions defined in ```CutFlowProduction_functions.C```.

Once the environment is setup (see the above section General setup on lxplus), the cutflow code can be ran by using the following command on the command line in the terminal:
```root CutFlowProduction.C```

The resulting cutflow histogram will be in the Results/ folder. It is only running over a single sample: VV PFlow+UFO HVT LP no-tag


## Part II: 1D and 2D Distribution Plotting

1D and 2D histograms are a great way to visualize the overall method being applied in this analysis. The 2D histogram is directly pulled from the sample file produced with the CxAOD framework (external to this project), from there 1D histograms are projected based on a specific METSig cut. These 1D histograms are what are actually used to calculate the significance for a given METSig cut. 

The main code is contained in ```VV_VH_distributions_plotting.ipynb``` . This notebook will walk through producing example 1D histograms of various kinematic variables (the main one we are interested being the invariant  mass, mVV) and then a 2D histogram of METSig vs invariant  mass.

The resulting histograms will be in the Results/ folder. 
    
## Part III: Calculating the signal significance for certain METSig cuts

The signal significance is the significance per bin added in quadrature, where the significance per bin is determined by the amount of signal in a bin divided by the square root of the signal per bin plus the background per bin plus the uncertainty in the bin squared. This is done by first extracting the 2D histogram of METSig vs invariant mass from the data file, then making a 1D histogram projection after applying a METSig cut. Then the calculation is performed on that 1D histogram. This is done for each signal mass point (ranging from 100 GeV to 5 TeV) as well as the corresponding backgrounds (W+jets, Z+jets, stop, diboson, and ttbar).

The main code is contained in ```METSigStudy.C``` with some specific functions defined in ```AnalysisOptions.C```.

Once the environment is setup (see the README for activating the ROOT environment), the METSigSignificance code can be ran by using the following command on the command line in the terminal:
```root METSigStudy.C```

The resulting normalized Significance vs METSig cut plot will be in the Results/ folder. It is only running over a single sample: VV PFlow+UFO HVT LP no-tag. Also note when ```ALL = FALSE``` then only a selected amount of signal samples will be plotted. This is to aide in visualization. 




## Licensing
Copyright (C) 2002-2022 CERN for the benefit of the ATLAS collaboration 

All analysis code is my own.
