// main code for producing cutflow histograms
//#include "easytreeplotter/EasyTreePlotter.C"
#include "AtlasStyle.C"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <TLegend.h>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

//#include <stdio.h>
//#include <conio.h>

#include "CutFlowHistProduction_functions.C"

//Function definition
void Production(int analysis,int region,int purity,int add,int kind,int signal,int vbf,int tag,int jetcollection);

void CutFlowHistProduction(){
    // Function used to loop through different options
    
    // Main variables and what the options mean for both VV and VH
  int analysis = -1;          // analysis       | 0=VV  |   1=VH
  int region = -1;            // region         | 0=SR , 1 = preselection , 2=CR
  int purity = -1;            // purity         | 0=lp , 1 = hp
  int add = -1;               // add            | 0= not relevent | 0= zero add, 1= one add, 2= not relevent
  int kind = -1;              // Merg  or Res   | 0= not relevent | 0= Merg, 1= Res
  int signal = -1;            // signal         | 0=hvt, 1=rsg, 2=radion, 3=vbfhvt, 4=vbfrsg, 5=vbfradion, 6=bkg
  int vbf = -1;               // production     | 0=no vbf , 1=vbf true
  int tag = -1;               // tagging        | 0= tagged, 1 = untagged, 2 =no tag | 0=zero tagged, 1= one tagged, 2= two tagged, 3=three tagged
  int jetcollection = -1;     // jet collection | 0=EMTopo_LCTopo, 1 = EMTopo_TCC, 2= PFlow_UFO
  
    
    // VV
    //PFlow UFO
    Production(0,0,0,-1,-1,0,0,0,2);
    Production(0,0,1,-1,-1,0,0,0,2);
    
    // VH
    //EMTopo TCC
//      Production(1,0,-1,1,0,0,0,1,1);
//     Production(1,0,-1,1,1,0,0,1,1);
  
    //EMTopo LCTopo
  //Production(1,0,-1,1,0,0,0,1,0);
  //Production(1,0,-1,1,1,0,0,1,0);
  
  //PFlow UFO
  //    Production(1,0,-1,1,0,0,0,1,2);
  //    Production(1,0,-1,1,1,0,0,1,2);
  
}

void Production(int analysis,int region,int purity,int add,int kind,int signal,int vbf,int tag,int jetcollection){
    
    std::cout<<"kind: "<<kind<<std::endl;
    if(analysis==0){//VV
        if(purity==1){kind = 1;} //HP
        if(purity==0){kind = 0;}} //LP
    
    // These will be the signal and background files
    TFile *sfile;
    TFile *bfile;
    
    std::vector<std::string> sigPathNames;
    std::vector<std::string> bkgPathNames;
    std::vector<std::string> Files;
    
    // First get the file
    sigPathNames = GetPath(analysis,region,purity,add,kind,signal,vbf,tag,jetcollection);
    bkgPathNames = GetPath(analysis,region,purity,add,kind,6,vbf,tag,jetcollection);
    
    // Pull out specific names from the returned vectors and print to screen to make sure they are correct
    std::string mainName = sigPathNames[0];
    std::string subpath = sigPathNames[1];
    std::string spath = sigPathNames[2];
    
    std::cout<<"s mainName: "<<mainName<<std::endl;
    std::cout<<"s subpath: "<<subpath<<std::endl;
    std::cout<<"s path: "<<spath<<std::endl;
    
    std::string bmainName = bkgPathNames[0];
    std::string bsubpath = bkgPathNames[1];
    std::string bpath = bkgPathNames[2];
    
    std::cout<<"b mainName: "<<bmainName<<std::endl;
    std::cout<<"b subpath: "<<bsubpath<<std::endl;
    std::cout<<"b path: "<<bpath<<std::endl;
    
    // Convert the name to a string
    std::string stemp = spath.c_str();
    std::string btemp = bpath.c_str();
    
    std::vector<std::string> fSigHists;
    std::vector<std::string> SigHists;
    std::vector<std::string> fBkgHists;
    std::vector<std::string> BkgHists;
    
    // Now, go into the file and return the ROOT file
    fSigHists = GetFiles(analysis,0,stemp.c_str());
    fBkgHists = GetFiles(analysis,6,btemp.c_str());
    
    // Sort the names of the files
    SigHists = alphabaticallySort(fSigHists);
    BkgHists = alphabaticallySort(fBkgHists);
    
    printf("after alphabetical sorting\n");
    
    for (int i=0;i<SigHists.size();i++){
//      std::cout<<"test"<<std::endl;
        std::cout<<SigHists[i]<<std::endl;}
    for (int i=0;i<BkgHists.size();i++){
        std::cout<<BkgHists[i]<<std::endl;}
    
//    std::string SigHists[1] = {"hist-HVTZH-1.root"};
//    std::string BkgHists[5] = {"hist-Diboson-1.root","hist-Wjets-1.root","hist-Zjets-1.root","hist-stop-1.root","hist-ttbar-1.root"};
    
    std::vector<std::string> sigHistNames;
    std::vector<std::string> dibosonHistNames;
    std::vector<std::string> wjetsHistNames;
    std::vector<std::string> zjetsHistNames;
    std::vector<std::string> stopHistNames;
    std::vector<std::string> ttbarHistNames;
    
    if(analysis==0){ //VV
        sigHistNames.push_back("Merged_GGF_LP_CutFlowCuts");
        sigHistNames.push_back("Merged_GGF_HP_CutFlowCuts");
        dibosonHistNames.push_back("Merged_GGF_LP_CutFlowCuts");
        dibosonHistNames.push_back("Merged_GGF_HP_CutFlowCuts");
        wjetsHistNames.push_back("Merged_GGF_LP_CutFlowCuts");
        wjetsHistNames.push_back("Merged_GGF_HP_CutFlowCuts");
        zjetsHistNames.push_back("Merged_GGF_LP_CutFlowCuts");
        zjetsHistNames.push_back("Merged_GGF_HP_CutFlowCuts");
        stopHistNames.push_back("Merged_GGF_LP_CutFlowCuts");
        stopHistNames.push_back("Merged_GGF_HP_CutFlowCuts");
        ttbarHistNames.push_back("Merged_GGF_LP_CutFlowCuts");
        ttbarHistNames.push_back("Merged_GGF_HP_CutFlowCuts");
        
    }
    
    if(analysis==1){ //VH
        sigHistNames.push_back("HVTZHvvqq3500_cutflow_merg");
        sigHistNames.push_back("HVTZHvvqq800_cutflow_res");
        dibosonHistNames.push_back("ZZ_cutflow_merg");
        dibosonHistNames.push_back("ZZ_cutflow_res");
        wjetsHistNames.push_back("W_cutflow_merg");
        wjetsHistNames.push_back("W_cutflow_res");
        zjetsHistNames.push_back("Z_cutflow_merg");
        zjetsHistNames.push_back("Z_cutflow_res");
        stopHistNames.push_back("stopWt_cutflow_merg");
        stopHistNames.push_back("stopWt_cutflow_res");
        ttbarHistNames.push_back("ttbar_cutflow_merg");
        ttbarHistNames.push_back("ttbar_cutflow_res");
        
    }
        
    // Define a canvas to draw on
    TCanvas *c1 = new TCanvas("c1", "c1",200, 100, 800, 600);
    
    // Define minimum and maximum values
    Double_t mmin = 0;
    Double_t mmax = 1.15;
    
    // Create a legend
    auto leg_hist = new TLegend(0.6,0.75,0.8,0.9); //(xmin,ymin,xmax,ymax)
      leg_hist->SetTextSize(0.02);
      leg_hist->SetFillColor(0);
      leg_hist->SetTextFont(42);
    
    // List of colors
    //  std::string colors1[11] = {"kRed","kBlack","kGreen","kBlue","kCyan","kOrange-2"}
    int colors[6] = {632,1,416,600,432,798};
    
    gStyle->SetOptStat(0);
    
    // Path to signal histogram
    std::string sPath = spath;
    sPath.append(SigHists[0]);
    
    sfile = new TFile(sPath.c_str());
    // Change to cutflow firectory
    sfile->cd("CutFlow");
     //Print out the paths
    std::cout<<"my sig file: "<< sPath<<std::endl;
    std::cout<<"my sig hist: "<< sigHistNames[kind]<<std::endl;
    // Open the file and clone the histogram, have it be the first color (Red)
    TH1F *sh1 = (TH1F*)gDirectory->Get(sigHistNames[kind].c_str());
    TH1F *h_1 = (TH1F*)sh1->Clone("h_1");
    h_1->SetLineColor(colors[0]);

    // Scaling factor
    Double_t factor = 1.;
    
    // Need to find the first non-zero bin, that will be the first bin
    Int_t sbin = h_1->FindFirstBinAbove(1,1,0,-1);
    Double_t stest = h_1->GetBinContent(sbin);
    if(stest==0){
        std::cout<<"Error! Can't fine non-zero bin!"<<std::endl;
        
    }
    else{
        // Scale the histogram
        h_1->Scale((factor/stest));
        std::string name;
        // Add some descriptors
        if(analysis==1){//VH
            if(kind==1){name="HVT Z' m=800 GeV";}
            if(kind==0){name="HVT Z' m=3500 GeV";}}
        if(analysis==0){//VV
            if(purity==1){name="HVT Z' HP ";}
            if(purity==0){name="HVT Z' LP ";}}
        // Add to legend
        leg_hist->AddEntry(h_1, name.c_str(), "l");
        h_1->SetMinimum(mmin);  // Define Y ..
        h_1->SetMaximum(mmax); // .. range
        // Draw the histogram
        h_1->Draw("hist");
    }
    h_1->GetYaxis()->SetTitle("Relative yield after applying given cuts");
    
    // Loop through backgrounds
    for (int i = 0; i<5;i++){
        std::string tempHists[2];
        std::string name;
        
        for (int j =0 ; j <2; j++){
            if( i == 0){ tempHists[j] = dibosonHistNames[j];name = "diboson";}
            if( i == 1){ tempHists[j] = wjetsHistNames[j];name = "W+jets";}
            if( i == 2){ tempHists[j] = zjetsHistNames[j];name = "Z+jets";}
            if( i == 3){ tempHists[j] = stopHistNames[j];name = "stop";}
            if( i == 4){ tempHists[j] = ttbarHistNames[j];name = "ttbar";}
        }
        
        // Path to bkg histograms
        std::string bPath = bpath;
        bPath.append(BkgHists[i]);
        bfile = new TFile(bPath.c_str());

        // Change to cutflow directory
        bfile->cd("CutFlow");
        //Print out the paths
        std::cout<<"my bkg file: "<< bPath<<std::endl;
        std::cout<<"my bkg hist: "<< tempHists[kind]<<std::endl;
        // Open the file and clone the histogram, have it be the rest of the colors
        TH1F *h2 = (TH1F*)gDirectory->Get(tempHists[kind].c_str());
        TH1F *h_2 = (TH1F*)h2->Clone("h_2");
        h_2->SetLineColor(colors[i+1]);
        
        // Need to find the first non-zero bin, that will be the first bin
        Int_t bbin = h_2->FindFirstBinAbove(1,1,0,-1);
        Double_t btest = h_2->GetBinContent(bbin);
        if(btest==0){
            std::cout<<"Error! First bin is zero!"<<std::endl;
        }
        else{
            // Scale the histogram
            h_2->Scale((factor/btest));
            // Add some descriptors
            leg_hist->AddEntry(h_2, name.c_str() , "l");
            h_2->SetMinimum(mmin);  // Define Y ..
            h_2->SetMaximum(mmax); // .. range
            // Draw the histogram
            h_2->Draw("HIST SAME");
        }
  
    }
    
    leg_hist->SetFillStyle(0);
    leg_hist->Draw("same");//draws the legend on the same histogram
    // Update the canvas
    c1->Update();
    
    // Save the cutflow to the file name from SaveName()
    std::string savename;
    std::string tempsavename;
    tempsavename = SaveName(analysis,region,purity,add,kind,signal,vbf,tag, jetcollection);
    
    savename = "../Results/";
    savename.append(tempsavename.c_str());
    
    c1->SaveAs(savename.c_str());

    
}
