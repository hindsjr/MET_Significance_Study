/* This code is meant to extract 2D histograms from a data file, then make a 1D
 histogram from the projection of a certain METSig cut. From that 1D histogram,
 the significance is calculated and plotted for each METSig cut.
 */

// Importing general libraries
#include <TH1F.h>
#include <TLegend.h>
#include <TFile.h>
#include <TMath.h>
#include <TCanvas.h>
#include <iostream>
#include <string>
#include <sstream>
#include <TLine.h>
#include <TGraph.h>
#include <fstream>
#include <vector>
#include <map>

// Importing analysis-specific libraries
#include "AnalysisOptions.C"

void myMain(int analysis,int region,int purity,int add,int kind,int signal,int vbf,int tag,int jetcollection); // Main calculation is done here


void METSigStudy(){ // Main function, calls myMain to actually perform the analysis
    // Declaration of variables and their meaning - mostly to use as a reference
    int analysis = -1;          // analysis       | 0=VV  |   1=VH
    int region = -1;            // region         | 0=SR , 1 = preselection , 2=CR
    int purity = -1;            // purity         | 0=lp , 1 = hp
    int add = -1;               // add            | 0= not relevent | 0= zero add, 1= one add, 2= not relevent
    int kind = -1;              // Merg  or Res   | 0= not relevent | 0= Merg, 1= Res
    int signal = -1;            // signal         | 0=hvt, 1=rsg, 2=radion, 3=vbfhvt, 4=vbfrsg, 5=vbfradion, 6=bkg
    int vbf = -1;               // production     | 0=no vbf , 1=vbf true
    int tag = -1;               // tagging        | 0= tagged, 1 = untagged, 2 =no tag | 0=zero tagged, 1= one tagged, 2= two tagged, 3=three tagged
    int jetcollection = -1;     // jet collection | 0=EMTopo_LCTopo, 1 = EMTopo_TCC, 2= PFlow_UFO
    
    // Now call myMain() with specific inputs
//    main(analysis,region,purity,add,kind,signal,vbf,tag,jetcollection);
    myMain(0,0,0,-1,-1,0,0,2,2); //VV, SR, LP, not relevent, not relevent, HVT WZ, no vbf, no tag, PFlow UFO
    
}

void myMain(int analysis,int region,int purity,int add,int kind,int signal,int vbf,int tag,int jetcollection){
    // Main calculation and plotting is done here
    
    // Default to normalization = TRUE
    // Default to all mass points = FALSE
    bool normalize = TRUE;
    bool ALL = FALSE;
    
    // Grab file of interest and define specific names
    TFile *sfile;
    TFile *bfile;
    std::vector<TH2D*> histsTempList;
    
    std::string sFileName = DefineFileName(analysis, jetcollection, signal, region, tag, vbf, purity,add, kind);
    std::string smyFiles = GetFiles(sFileName);
    std::string bFileName = DefineFileName(analysis, jetcollection, 6, region, tag, vbf, purity,add, kind);
    std::string bmyFiles = GetFiles(bFileName);
    
    // Open signal and bkg files
    sfile =TFile::Open(smyFiles.c_str(),"OPEN");
    bfile =TFile::Open(bmyFiles.c_str(),"OPEN");

    std::vector<std::string> bkgHistNames, sigHistNames;
    
    // Grab the 2D histogram names
    bkgHistNames = GetHistNames(analysis,region,purity,add,kind,6,vbf,tag,jetcollection);
    sigHistNames = GetHistNames(analysis,region,purity,add,kind,signal,vbf,tag,jetcollection);
    
    // Making array of cuts:
    Double_t count = 0;
    Double_t MaxCut = 40;
    Double_t iteration = 5;
    
    std::vector<Double_t> cuts;
    while (count < MaxCut){
        cuts.push_back(count);
        count += iteration;
        std::cout<<count<<std::endl;
    }
    
    // Define mass vectors to use later when plotting
    std::vector<int> mass;
    std::vector<std::string> massName;
    std::vector<std::string> tempmassName;
    
    int HVTWZmass[25] = {500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2200,2400,2600,2800,3000,3500,4000,4500,5000};
    std::string sHVTWZmass[25] = {"500","600","700","800","900","1000","1100","1200","1300","1400","1500","1600","1700","1800","1900","2000","2200","2400","2600","2800","3000","3500","4000","4500","5000"};
    for (int i=0;i<24;i++){
        mass.push_back(HVTWZmass[i]);
        massName.push_back(sHVTWZmass[i]);
        }
    
    // Initialize multi-graph
    TMultiGraph *mg = new TMultiGraph();
    TGraph *aGraph[25];
    TGraph *bGraph[25];
    
    // Initalize the canvas
    TCanvas *c1 = new TCanvas("c1", "c1",900,900);
    gStyle->SetOptStat(0);
    
    int color_count = 0; // initalize to zero
    
    // Loop through the signal masses
    for (int i = 0; i<sigHistNames.size(); i++){
        std::vector<Double_t> METSig; // initalize list of METsig to zero
        
        Double_t sigma; // initalize sigma to zero
        
        // Loop through the cuts
        for (int j=0; j<cuts.size();j++){
            std::vector<TH1D*> hists; // initalize exmpty vector of 1D histograms
            
            std::cout<<"Cut: "<<cuts[j]<<std::endl;
            std::cout<<"accessing Signal hist "<<sigHistNames[i].c_str()<<std::endl;
            
            // From example: https://root.cern.ch/root/html534/tutorials/hist/h2proj.C.html
            
            Double_t startcut = cuts[j]; // define start cut
            
            // Get the 2D histogram
            TH2D *signalhist = (TH2D*)sfile->Get(sigHistNames[i].c_str());
            // Find the bin which corresponds to the equvilent METSig cut
            Double_t ActualSigCut = signalhist->GetYaxis()->FindBin(startcut);
            // Make a temporary hist name
            std::string mtemp1 = sigHistNames[i];
            std::string temp1 = mtemp1.append("_temp");
            // Find the signal histogram end number of bins
            Int_t sendbin = signalhist->GetNbinsY();
            // Produce a 1D projection histogram from the cut bin to the end of the bins
            TH1D * sigprojh2X = signalhist->ProjectionX(temp1.c_str(),ActualSigCut,sendbin,"d");
            // Add to the vector of histograms - the first one (this one) will be the signal
            hists.push_back(sigprojh2X);
            
            // Loop through all the backgrounds
            for (int k = 0; k< bkgHistNames.size();k++){
                std::cout<<"accessing Bkg hist "<<bkgHistNames[k].c_str()<<std::endl;
                // Get the 2D histogram
                TH2D *bkghist = (TH2D*)bfile->Get(bkgHistNames[k].c_str());
                // Find the bin which corresponds to the equvilent METSig cut
                Double_t ActualBkgCut = bkghist->GetYaxis()->FindBin(startcut);
                // Find the bkg histogram end number of bins
                Int_t bendbin = bkghist->GetNbinsY();
                // Make a temporary hist name
                std::string mtemp2 = bkgHistNames[k];
                std::string temp2 = mtemp2.append("_temp");
                // Produce a 1D projection histogram from the cut bin to the end of the bins
                TH1D * bkgprojh2X = bkghist->ProjectionX(temp2.c_str(),ActualBkgCut,bendbin,"d");
                // Add to the vector of histograms - the rest of the list will be bkg histograms
                hists.push_back(bkgprojh2X);
            }
            
            // Calculate the signal significance of the set of histograms
            sigma = CalculateSignificance(hists);
            std::cout<<"Calculated sigma: "<<sigma<<std::endl;
            std::cout<<"-----------------"<<std::endl;
            // Add the significance to the list
            METSig.push_back(sigma);

        }
        
        // Must create a de-references array of these vectors because TGraph does not reconize std::vectors as a valid input
        double* acuts = &cuts[0];
        double* aMETSig = &METSig[0];
        
        std::vector<Double_t> NewVals; // initalize another list of significance values - these will be the normalized list
        
        Int_t n = cuts.size(); // number of cuts
        aGraph[i] = new TGraph(n, acuts, aMETSig); // this will contain ALL of the un-normalized significance plots (for every signal mass)
        
        Double_t scale = aMETSig[0]; // when normalize == TRUE, you will normalize each signal to the first bin of the zero-cut histogram

        // Loop through ALL of the signal masses
        for (int k=0;k<aGraph[i]->GetN();k++){
            Double_t temp = aGraph[i]->GetY()[k]; // Get the bin content
            aGraph[i]->GetY()[k] *= temp/scale; // Normalize
            NewVals.push_back(temp/scale); // Store the normalized values
        }
        // again, must de-references array of these vectors because TGraph does not reconize std::vectors as a valid input
        double* bNewVals = &NewVals[0];
        bGraph[i] = new TGraph(n, acuts, bNewVals); // create new TGraphs of the normalized values
            
        // Initially set all the colors to the just an indexed value
        aGraph[i]->SetMarkerColor(i);
        bGraph[i]->SetMarkerColor(i);
        
        // Set the name to the signal mass name
        aGraph[i]->SetName(massName[i].c_str());
        bGraph[i]->SetName(massName[i].c_str());

        // black, red, green, blue, pink, aqua, violot
        Int_t colors[7] = {1,2,3,4,6,7,9};
        
        // Check to see if any of the values are NaN
        bool testing = TRUE;
        for (int u=0;u<NewVals.size();u++){
            Double_t temp = NewVals[u];
            if(std::isnan(temp) == 1){
                testing = FALSE;
            }
        }
        
        if(ALL == FALSE){ // If we just want to look at a few mass points
            if (i%2 == 0 && testing == TRUE){ // and the current iteration passes these requirements
                
                // record the mass that is currently present
                tempmassName.push_back(sHVTWZmass[i]);
            
                // set a more reasonable color that can easily be identified
                aGraph[i]->SetMarkerColor(colors[color_count]);
                aGraph[i]->SetLineColor(colors[color_count]);
                bGraph[i]->SetMarkerColor(colors[color_count]);
                bGraph[i]->SetLineColor(colors[color_count]);
                
                if(normalize==FALSE){ // for non-normalized results
                    mg->Add(aGraph[i],"*");
                }
                if(normalize==TRUE){ // for normalized results
                    mg->Add(bGraph[i],"L*");
                }
                color_count += 1; // keep track of how many we are plotting
            }
        }
        
        if(ALL == TRUE){ // if we want to plot them all, then we don't care if some one them are NaN or changing the colors
            if(normalize==FALSE){ // for non-normalized results
                mg->Add(aGraph[i],"*");
            }
            if(normalize==TRUE){ // for normalized results
                mg->Add(bGraph[i],"L*");
            }
        }
        
        
    }
    
    // Change axis' title and set a range
    if(normalize == TRUE){
        mg->GetYaxis()->SetTitle("Normalized Significance");
    }
    if(normalize == FALSE){
        mg->GetYaxis()->SetTitle("Significance");
    }
    mg->GetXaxis()->SetTitle("METSig cut");
    mg->GetYaxis()->SetRangeUser(0,3);
    
    mg->Draw("A*"); // Draw them all on the multigraph
    
    if (ALL == FALSE){ // if we are only plotting a few mass point, build a unique legend
        TLegend *l = c1->BuildLegend();
        TList *p = l->GetListOfPrimitives();

        TIter next(p);
        TObject *obj;
        TLegendEntry *le;
        int i = 0;

        while ((obj = next())) {
            le = (TLegendEntry*)obj;
            i++;
            std::string histname = tempmassName[i-1].c_str(); // make the names in the legend be the mass names
            histname.append(" GeV"); // with the correct units
            le->SetLabel(histname.c_str());
        }
    }
    if (ALL == TRUE){ // if we are plotting all mass points, just make a generic legend
        c1->BuildLegend();
        
    }
    
    c1->Update(); // update the canvas
    
    // Save the histogram to a unique file name
    string filename;
    filename = MakeFileName(normalize,ALL,sFileName);
    
    // Save the file to the Results/ directory
    string tempfilename = "../Results/";
    tempfilename.append(filename);
    std::cout<<"filename:" <<tempfilename<<std::endl;
    c1->Print(tempfilename.c_str());

    std::cout<<"Done."<<std::endl;
    
    return;
    
}
