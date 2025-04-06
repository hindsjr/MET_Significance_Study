// Creation of my own unittest code

// Import relevent libraries
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
#include <cmath>

// Import code that contains function of interest
#include "../METSignificanceStudy/AnalysisOptions.C"


// Test functions

bool isSame1(std::vector<TH1F*> hists){
    // Checks to see if the significance from two constant histograms equal what we expect
    Double_t temp = CalculateSignificance(hists); // Calculated value
    Double_t a = 4.30791; // Expected value (computed by hand)
    if (round(temp/a) == 1) { // Must divide and round to see if they are similar since using ROOT's Double gives errors when comparing - even if they are they same printed value
        return TRUE;} // If it passes, then it returns true
    return FALSE; // Otherwise it returns false
}
bool isSame2(std::vector<TH1F*> hists){
    // Checks to see if the significance from a gaussian "signal" and two constant "backgrounds" give the significance we expect
    Double_t temp = CalculateSignificance(hists); // Calculated value
    Double_t a = 1.241545071; // Expected value (computed by hand)
    if (round(temp/a) == 1) { // Must divide and round to see if they are similar since using ROOT's Double gives errors when comparing - even if they are they same printed value
        return TRUE;} // If it passes, then it returns true
    return FALSE; // Otherwise it returns false
}
bool isNotPushedBack(std::vector<TH1F*> hists){
    // Checks to see if an empty vector is passed
    if (CalculateSignificance(hists) == -1) { // Main code will return a -1 if it is empty
        return TRUE;} // If it passes, then it returns true
    return FALSE; // Otherwise it returns false
}
bool tooFewHists(std::vector<TH1F*> hists){
    // Checks to make sure background histograms were pushed back
    if (CalculateSignificance(hists) == -1) { // Main code will return a -1 if there is only one (the signal) histogram
        return TRUE;} // If it passes, then it returns true
    return FALSE; // Otherwise it returns false
}
bool notSignal(std::vector<TH1F*> hists){
    // Checks to make sure the first signal is indeed a signal histogram (here, only checking for HVT signal)
    if (CalculateSignificance(hists) == -1) {// Main code will return a -1 if the first histogram does not contain the signal (HVT will be included in the signal hist name)
        return TRUE;} // If it passes, then it returns true
    return FALSE; // Otherwise it returns false
}



void myUnitTest(){
    
    /*
     This code is used to test the function CalculateSignificance(std::vector<TH1F*> hists) in AnalysisOptions.C
     
     */
    
    // First, generate some generic histograms for testing with simple binning
    
    const Int_t NBINS = 12;
    Double_t edges[NBINS + 1] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0};
    
    // Gaussian histograms
    TH1F *h = new TH1F("h", "Gaussian", NBINS, edges);
    TF1 *f = new TF1("f", "TMath::Gaus(x, 3.0, 3.0)", 0.0, 6.0);
    h->Eval(f);
    
    TH1F *h_gauss_sig = new TH1F("h_HVT", "Gaussian", NBINS, edges);
    TF1 *f_gauss_sig = new TF1("f_gauss_sig", "TMath::Gaus(x, 3.0, 3.0)", 0.0, 6.0);
    h_gauss_sig->Eval(f_gauss_sig);
    h_gauss_sig->SetBinContent(NBINS+1,100); // Testing overflow bin case
    
    // Constant histogram #1
    TH1F *h_const1 = new TH1F("h_const1", "Constant", NBINS, edges);
    TF1 *f_const1 = new TF1("f_const1", "TMath::Pi()", 0.0, 6.0);
    h_const1->Eval(f_const1);
    h_const1->SetBinContent(NBINS+1,100); // Testing overflow bin case
    
    // Constant histogram #2
    TH1F *h_const2 = new TH1F("h_const2", "Constant", NBINS, edges);
    TF1 *f_const2 = new TF1("f_const2", "TMath::PiOver2()", 0.0, 6.0);
    h_const2->Eval(f_const2);
    h_const2->SetBinContent(NBINS+1,100); // Testing overflow bin case
    
    // Visualization
//    TCanvas *c = new TCanvas("c1", "c1",900,900);
//    TColor *c1 = new TColor(9001,1,0.5,0); //is this your color?
//    TColor *c2 = new TColor(9002,0,1,0); //green
//    TColor *c3 = new TColor(9003,0,0,1); //blue
//
//    h_const1->SetLineColor(9001);
//    h_const2->SetLineColor(9002);
//    h_gauss_sig->SetLineColor(9003);
//
//    h_const1->Draw("hist");
//    h_const2->Draw("histsame");
//    h_gauss_sig->Draw("histsame");
//    c->Update();
    
    // Constant histogram #3
    TH1F *h3 = new TH1F("h_const3_HVT", "Constant", NBINS, edges);
    TF1 *f2 = new TF1("f2", "TMath::Pi()", 0.0, 6.0);
    h3->Eval(f2);
    
    // Now, some test variables to test the functions
    bool testing1 = FALSE;
    bool testing2 = FALSE;
    bool testing3 = FALSE;
    bool testing4 = FALSE;
    bool testing5 = FALSE;
    
    // make a vector of histograms for testing
    std::vector<TH1F*> hists;
    
    // testing to see if any histograms are pushed back
    std::cout<<"Running Test 1"<<std::endl;
    if(isNotPushedBack(hists)){
        testing1 = TRUE;
        std::cout<<"Passed Test 1"<<std::endl;
    }
    
    // push back a gaussian histograms
    hists.push_back(h);
    
    // after pushing back one histogram, test to see if there's more than 2 histograms (signal+bkg)
    std::cout<<"Running Test 2"<<std::endl;
    if(tooFewHists(hists)){
        testing2 = TRUE;
        std::cout<<"Passed Test 2"<<std::endl;
    }
    
    // push back a constant histograms
    hists.push_back(h_const1);
    
    // push back another histogram and check that the first one is indeed the signal histogram
    std::cout<<"Running Test 3"<<std::endl;
    if(notSignal(hists)){
        testing3 = TRUE;
        std::cout<<"Passed Test 3"<<std::endl;
    }
    
    // make another vector of histograms for testing
    // push back a two constant histograms
    std::vector<TH1F*> hists2;
    hists2.push_back(h3);
    hists2.push_back(h_const1);
    
    // check to see if the value we get is the one we expect
    std::cout<<"Running Test 4"<<std::endl;
    if(isSame1(hists2)){
        testing4 = TRUE;
        std::cout<<"Passed Test 4"<<std::endl;
    }
    
    // make another vector of histograms for testing
    // push back a signal gaussian and two constant backgrounds
    std::vector<TH1F*> hists3;
    hists3.push_back(h_gauss_sig);
    hists3.push_back(h_const1);
    hists3.push_back(h_const2);
    
    // check to see if the value we get is the one we expect
    std::cout<<"Running Test 5"<<std::endl;
    if(isSame2(hists3)){
        testing5 = TRUE;
        std::cout<<"Passed Test 5"<<std::endl;
    }

    // print if testing was sucessful or not
    if(testing1 && testing2 && testing3 && testing4 && testing5) {std::cout<<"Passed testing sucessfully."<<std::endl; }
    else{std::cout<<"ERROR. Testing not sucessful."<<std::endl;}
        
    std::cout<<"End of testing."<<std::endl;
    
    
}

