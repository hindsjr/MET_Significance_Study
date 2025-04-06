
// To VV or not to VV


std::vector<std::string> AnalysisOption(int option, int signal, int region, int tag, int vbf, int purity,int add, int kind){
    // Function which produces cut names to use as the names for the histograms based on the inputs. Returns a vector os strings which are the cut names.

    // Define vector where the names will be stored
  std::vector<std::string> mystrings;
    
  std::cout<<"Entered Analysis option code"<<std::endl;

    // int option = 0; VV Analysis
    // int option = 1; VH Analysis
    
    int number;
    
    
    // Based on the signal and the analysis type, the number of histogram names will vary
    
    if(option == 0){//VV
      //HVTWZ
      if(signal == 0){number = 25;}
      
      //RSG
      if(signal == 1){ number = 28;}
      
      //Radion
      if(signal == 2){ number = 21;}
      
      //VBF HVTWZ
      if(signal == 3){ number = 23;}
      
      //VBF RSG
      if(signal == 4){number = 21;}
      
      //VBF Radion
      if(signal == 5){number = 21;}
      
      //background
      if(signal == 6){number = 1;}
    }
    
    if(option == 1){//VH}
      //HVTWZ
      if(signal == 0){number = 22;}
      
      //RSG
      if(signal == 1){ number = 28;}
      
      //Radion
      if(signal == 2){ number = 21;}
      
      //VBF HVTWZ
      if(signal == 3){ number = 23;}
      
      //VBF RSG
      if(signal == 4){number = 21;}
      
      //VBF Radion
      if(signal == 5){number = 21;}
      
      //background
      if(signal == 6){number = 1;}
    }

    // DSID Configuration
   
    std::string VV_hvt_dsid[25] = {"302241","302242","302243","302244","302245","302246","302247","302248","302249","302250","302251","302252","302253","302254","302255","302256","302257","302258","302259","302260","302261","302262","302263","302264","302265"};
    std::string rsg_dsid[28] = {"303342","303343","303344","303302","303303","303304","303305","303306","303307","303308","303309","303310","303311","303312","303313","303314","303315","303316","303317","303318","303319","303320","303321","303322","303323","303324","303325","303326"};
    std::string radion_dsid[21] = {"451204","451205","451206","451207","451208","451209","451210","451211","451212","451213","451214","451215","451216","451217","451218","451219","451220","451221","451222","451223","451224"};
    //  std::string radion_dsid[8] = {"310039","310040","310041","310042","310043","310044","310045","310046"};
    std::string vbfhvt_dsid[23]={"307705","307706","307707","307708","307709","307710","307711","307712","307713","307714","307715","307716","307717","307718","307719","307720","307721","307722","307723","307724","307725","307726","307727"};
    std::string vbfrsg_dsid[21]={"451183","451184","451185","451186","451187","451188","451189","451190","451191","451192","451193","451194","451195","451196","451197","451198","451199","451200","451201","451202","451203"};
    //  std::string vbfrsg_dsid[8]={"310031","310032","310033","310034","310035","310036","310037","310038"};
    std::string vbfradion_dsid[21]={"451225","451226","451227","451228","451229","451230","451231","451232","451233","451234","451235","451236","451237","451238","451239","451240","451241","451242","451243","451244","451245"};
    //  }
    std::string VH_hvt_dsid[22] = {"307371","307372","302416","302417","302418","302419","302420","302421","302423","302425","302427","302429","302431","302432","302433","302434","302435","302436","302437","302438","302439","302440"};
    //  }
  
    // Loop through the DSIDs and build the cut based on the analysis
    int i = 0;
    while (i<number){
      
        string tempname;
        if (option==0){//VV
            if(signal == 0){
                tempname = VV_hvt_dsid[i];
            }
            else if(signal == 1){
                tempname = rsg_dsid[i];
            }
            else if(signal == 2){
                tempname = radion_dsid[i];
            }
            else if(signal == 3){
                tempname = vbfhvt_dsid[i];
            }
            else if(signal == 4){
                tempname = vbfrsg_dsid[i];
            }
            else if(signal == 5){
                tempname = vbfradion_dsid[i];
            }
            else if(signal == 6){
	  //      std::cout<<"No DSID for background samples."<<std::endl;
                tempname = "No DSID for background samples.";
            }
        }
        if (option==1){//VH
            if(signal == 0){
                tempname = VH_hvt_dsid[i];
            }}
      
      // Building Cuts specifically based on Analysis (+ other options defined)
        
      if (option == 0){ // VV
          std::cout<<"VV"<<std::endl;
          if(signal <= 5){ // If it's actually a signal and not bkg
              if(region == 0){ // SR
                  if(tag == 2){ // no tag
                      if(vbf == 0){ // not VBF process
                          if(purity == 1){ tempname = "Pass_MergHP_GGF_WZ_SR==1 && std::abs(weight)<=50 && DSID==" + tempname;
                              std::cout<<tempname<<std::endl;
                          }
                          if(purity == 0){ tempname = "Pass_MergLP_GGF_WZ_SR==1 && std::abs(weight)<=50 && DSID==" + tempname;
                              std::cout<<tempname<<std::endl;
                          }
	      }
	      if(vbf == 1){ // If not ggF process
		//          if(purity == 1){ tempname = "Pass_MergHP_VBF_WZ_SR==1 && std::abs(weight)<=50 && DSID==" + tempname;
              if(purity == 1){ tempname = "Pass_MergHP_GGF_WZ_SR==1 && std::abs(weight)<=50 && DSID==" + tempname;
                  std::cout<<tempname<<std::endl;
              }
		//          if(purity == 0){ tempname = "Pass_MergLP_VBF_WZ_SR==1 && std::abs(weight)<=50 && DSID==" + tempname;}
              if(purity == 0){ tempname = "Pass_MergLP_GGF_WZ_SR==1 && std::abs(weight)<=50 && DSID==" + tempname;}
              std::cout<<tempname<<std::endl;
                }
                  }
                  if(tag == 0){ // no tag
                      if(purity == 1){tempname = "Pass_MergHP_GGF_ZZ_Tag_SR==1 && std::abs(weight)<=50 && DSID==" + tempname;
                          std::cout<<tempname<<std::endl;
                      }
                      if(purity == 0){ tempname = "Pass_MergLP_GGF_ZZ_Tag_SR==1 && std::abs(weight)<=50 && DSID==" + tempname;
                          std::cout<<tempname<<std::endl;
		
                      }
                  }
                  if(tag == 1){ // untag
	      
                      if(purity == 1){tempname = "Pass_MergHP_GGF_ZZ_Untag_SR==1 && std::abs(weight)<=50 && DSID==" + tempname;
                          std::cout<<tempname<<std::endl;
                      }
                      if(purity == 0){ tempname = "Pass_MergLP_GGF_ZZ_Untag_SR==1 && std::abs(weight)<=50 && DSID== " + tempname;
                          std::cout<<tempname<<std::endl;
                      }
                  }
              }
        if( region == 1){ // preselection
                tempname = "std::abs(weight)<=50 && DSID==" + tempname;
                std::cout<<tempname<<std::endl;
        }
          }
	
	
	if(signal == 6){ // Background
	  if(region == 0){ //SR
	    if(tag == 2){ // no tag
	      
	      if(vbf == 0){ // not VBF
              if(purity == 1){ tempname = "Pass_MergHP_GGF_WZ_SR==1 && std::abs(weight)<=50";
            std::cout<<tempname<<std::endl;
              }
              if(purity == 0){ tempname = "Pass_MergLP_GGF_WZ_SR==1 && std::abs(weight)<=50";
                  std::cout<<tempname<<std::endl;
              }
          }
	      if(vbf == 1){ // not ggF
		//          if(purity == 1){ tempname = "Pass_MergHP_VBF_WZ_SR==1 && std::abs(weight)<=50";
              if(purity == 1){ tempname = "Pass_MergHP_GGF_WZ_SR==1 && std::abs(weight)<=50";
		  //if(purity == 1){ tempname = "Pass_MergHP_GGF_ZZ_SR==1 && std::abs(weight)<=50";
                  std::cout<<tempname<<std::endl;
              }
		//          if(purity == 0){ tempname = "Pass_MergLP_VBF_WZ_SR==1 && std::abs(weight)<=50";}
              if(purity == 0){ tempname = "Pass_MergLP_GGF_WZ_SR==1 && std::abs(weight)<=50";}
		//          if(purity == 0){ tempname = "Pass_MergLP_GGF_ZZ_SR==1 && std::abs(weight)<=50";}
              std::cout<<tempname<<std::endl;
          }
        }
	    if(tag == 0){ // tagged
            if(vbf == 0){ // not VBF
                if(purity == 1){tempname = "Pass_MergHP_GGF_ZZ_Tag_SR==1 && std::abs(weight)<=50";
                    std::cout<<tempname<<std::endl;
                }
                if(purity == 0){ tempname = "Pass_MergLP_GGF_ZZ_Tag_SR==1 && std::abs(weight)<=50";
                    std::cout<<tempname<<std::endl;
                }
            }
	      if(vbf == 1){ // not ggF
		//          if(purity == 1){tempname = "Pass_MergHP_VBF_ZZ_Tag_SR==1 && std::abs(weight)<=50";
		//          if(purity == 1){tempname = "Pass_MergHP_GGF_ZZ_Tag_SR==1 && std::abs(weight)<=50";
              if(purity == 1){tempname = "Pass_MergHP_GGF_ZZ_Tag_SR==1 && std::abs(weight)<=50";
                  std::cout<<tempname<<std::endl;
              }
		//          if(purity == 0){ tempname = "Pass_MergLP_VBF_ZZ_Tag_SR==1 && std::abs(weight)<=50";
              if(purity == 0){ tempname = "Pass_MergLP_GGF_ZZ_Tag_SR==1 && std::abs(weight)<=50";
                  std::cout<<tempname<<std::endl;
              }}
        }
          if(tag == 1){ // untag
              if(vbf == 0){ // not VBF
                  if(purity == 1){tempname = "Pass_MergHP_GGF_ZZ_Untag_SR==1 && std::abs(weight)<=50";
                      std::cout<<tempname<<std::endl;
                  }
                  if(purity == 0){ tempname = "Pass_MergLP_GGF_ZZ_Untag_SR==1 && std::abs(weight)<=50";
                      std::cout<<tempname<<std::endl;
                  }
              }
              if(vbf == 1){ // not ggF
                  if(purity == 1){tempname = "Pass_MergHP_GGF_ZZ_Untag_SR==1 && std::abs(weight)<=50";
                      std::cout<<tempname<<std::endl;
                  }
                  if(purity == 0){ tempname = "Pass_MergLP_GGF_ZZ_Untag_SR==1 && std::abs(weight)<=50";
                      std::cout<<tempname<<std::endl;
                  }}
          }
      }
        if( region == 1){ //preselection
          tempname = "std::abs(weight)<=50";
            std::cout<<tempname<<std::endl;
        }
    }}
      
      
      if (option == 1){ // VH Analysis
	
          std::cout<<"VH"<<std::endl;
          if(signal <= 5){ // all signals with DSID's
              if (kind == 0){ // Merg

                  if(tag == 0){ // no tag
                      std::cout<<"Zero tag is not an option!"<<std::endl;}

                  if (tag == 1){ // one tagged
                      if (add ==2){// add not relevent
                          if(region == 0){//SR}
                              tempname = "Pass_Merg_VH_1tag_SR && std::abs(weight)<=50 && DSID=="+ tempname;
                              //		  std::cout<<tempname<<std::endl;
                          }
                          if(region == 2){// CR
                              tempname = "Pass_Merg_VH_1tag_MCR && std::abs(weight)<=50 && DSID=="+ tempname;}
                      }
                      if (add == 0){// zero add
		//		tempname = "Pass_Merg_VH_1tag0add_SR==0 && std::abs(weight)<=50"; // *****
                          tempname = "Pass_Merg_VH_1tag0add_SR==1 && std::abs(weight)<=50 && DSID=="+ tempname; // *****
		
                      }
                      if (add == 1){// one add
                          tempname = "Pass_Merg_VH_1tag1add_SR && std::abs(weight)<=50 && DSID=="+ tempname;}
                  }
                  if (tag == 2){ // two tagged
                      if (add ==2){// add not relevent
                          if(region == 0){//SR}
                              tempname = "Pass_Merg_VH_2tag_SR && std::abs(weight)<=50 && DSID=="+ tempname;}
                          if(region == 2){// CR
                              tempname = "Pass_Merg_VH_2tag_MCR && std::abs(weight)<=50 && DSID=="+ tempname;}
                      }
                      if (add == 0){// zero add
                          tempname = "Pass_Merg_VH_2tag0add_SR && std::abs(weight)<=50 && DSID=="+ tempname;}
                    }
                }
                        if (kind == 1){ // Res
                if (tag == 1){ // one tagged
                    if(region == 0){//SR
                        tempname = "Pass_Res_VH_1tag_SR && std::abs(weight)<=50 && DSID=="+ tempname;}
                    if(region == 2){// CR
                        tempname = "Pass_Res_VH_1tag_MCR && std::abs(weight)<=50 && DSID=="+ tempname;}
                }
                if (tag == 2){ // two tagged
                    if(region == 0){//SR
                        tempname = "Pass_Res_VH_2tag_SR && std::abs(weight)<=50 && DSID=="+ tempname;}
                    if(region == 2){// CR
                        tempname = "Pass_Res_VH_2tag_MCR && std::abs(weight)<=50 && DSID=="+ tempname;}
                }
                        }
          }
        
        if(signal == 6){ // bkg
            if (kind == 0){ // Merg
                if (tag == 1){ // one tagged
                    if (add ==2){// add not relevent
                        if(region == 0){//SR}
                            tempname = "Pass_Merg_VH_1tag_SR && std::abs(weight)<=50";}
                        if(region == 2){// CR
                            tempname = "Pass_Merg_VH_1tag_MCR && std::abs(weight)<=50";}
                    }
                    if (add == 0){// zero add
                        tempname = "Pass_Merg_VH_1tag0add_SR && std::abs(weight)<=50";}
                    if (add == 1){// one add
                        tempname = "Pass_Merg_VH_1tag1add_SR && std::abs(weight)<=50";}
                }
                if (tag == 2){ // two tagged
                    if (add ==2){// add not relevent
                        if(region == 0){//SR}
                            tempname = "Pass_Merg_VH_2tag_SR && std::abs(weight)<=50";}
                        if(region == 2){// CR
                            tempname = "Pass_Merg_VH_2tag_MCR && std::abs(weight)<=50";}
                    }
                    if (add == 0){// zero add
                        tempname = "Pass_Merg_VH_2tag0add_SR && std::abs(weight)<=50";}
                }
            }
            if (kind == 1){ // Res
                if (tag == 1){ // one tagged
                    if(region == 0){//SR
                        tempname = "Pass_Res_VH_1tag_SR && std::abs(weight)<=50";}
                    if(region == 2){// CR
                        tempname = "Pass_Res_VH_1tag_MCR && std::abs(weight)<=50";}
                }
                if (tag == 2){ // two tagged
                    if(region == 0){//SR
                        tempname = "Pass_Res_VH_2tag_SR && std::abs(weight)<=50";}
                    if(region == 2){// CR
                        tempname = "Pass_Res_VH_2tag_MCR && std::abs(weight)<=50";}
                }
            }
        }
          std::cout<<tempname<<std::endl;
        }

      std::string cut= tempname;
      mystrings.push_back(cut);
      i = i+1;

    }        
  std::cout<<"Finished making histnames."<<std::endl;
  
  return mystrings; // return list og cuts
  
}

        
std::string DefineFileName(int option, int jetcollection, int signal, int region, int tag, int vbf, int purity,int add, int kind){
    // Function to define the data file name based on the inputs given. Returns a string which is the file name.
    
    // Building the file name
    std::string filename;
    
    if(option == 0){
        filename = "VV";
      if(region == 0){
          filename.append("_SR");}
      if(region == 1){
          filename.append("_preselection");}
      if(jetcollection == 0){filename.append("_EMTopo_LCTopo");}
      if(jetcollection == 1){filename.append("_EMTopo_TCC");}
      if(jetcollection == 2){filename.append("_PFlow_UFO");}
      if(signal == 0){filename.append("_HVT");}
      if(signal == 1){filename.append("_RSG");}
      if(signal == 2){filename.append("_Radion");}
      if(signal == 3){filename.append("_VBFHVT");}
      if(signal == 4){filename.append("_VBFRSG");}
      if(signal == 5){filename.append("_VBFRadion");}
      if(signal == 6){filename.append("_Bkg");}
      if(purity == 1){filename.append("_HP");}
      if(purity == 0){filename.append("_LP");}
      if(tag == 2){filename.append("_noTag");}
      if(tag == 0){filename.append("_Tagged");}
      if(tag == 1){filename.append("_Untagged");}}

    if(option == 1){ filename = "VH";
        if(region == 0){
            filename.append("_SR");}
        if(region == 1){
            filename.append("_preselection");}
        if(jetcollection == 0){filename.append("_EMTopo_LCTopo");}
        if(jetcollection == 1){filename.append("_EMTopo_TCC");}
        if(jetcollection == 2){filename.append("_PFlow_UFO");}
	if(jetcollection == -1){std::cout<<"no jet collection specified"<<std::endl;}
        if(signal == 0){filename.append("_HVT");}
        if(signal == 1){filename.append("_RSG");}
        if(signal == 2){filename.append("_Radion");}
        if(signal == 3){filename.append("_VBFHVT");}
        if(signal == 4){filename.append("_VBFRSG");}
        if(signal == 5){filename.append("_VBFRadion");}
        if(signal == 6){filename.append("_Bkg");}
      if(add == 2){filename.append("_noAdd");}
      if(add == 1){filename.append("_oneAdd");}
      if(kind == 0){filename.append("_Merg");}
      if(kind == 1){filename.append("_Res");}
      if(tag == 2){filename.append("_twoTagged");}
      if(tag == 1){filename.append("_oneTagged");}}
    
    // Print name of file to screen so the user is aware
    std::cout<<"Name of file: "<<filename<<std::endl;
    
    return filename; // return the name
    
}

std::string GetFileName(int analysis,int region,int purity,int add,int kind,int signal,int vbf,int tag,int jetcollection){
    
    
    std::string mysecondstring;
    //need to add if-statement for VV or VH
    
    if(region == 0){// SR
        mysecondstring = "sr_";
    }
    if(region == 1){// preselection
//        mysecondstring = "sr_";
        std::cout<<"No preselection!"<<std::endl;
    }
    if(region == 2){// CR
        mysecondstring = "CR_";
    }
    if(jetcollection==0){//EMTopo LCTopo
        mysecondstring.append("EMTopo_LCTopo_");
    }
    if(jetcollection==1){//EMTopo TCC
        mysecondstring.append("EMTopo_TCC_");
    }
    if(jetcollection==2){//PFlow UFO
        mysecondstring.append("PFlow_UFO_");
    }
    if(signal==0){//HVT
        mysecondstring.append("HVT_");
    }
    // add other signals here
    if(signal==6){//bkg
        mysecondstring.append("bkg_");
    }
    if(purity==0){//LP
        mysecondstring.append("LP_");
    }
    if(purity==1){//HP
        mysecondstring.append("HP_");
    }
    if(tag==0){//tagged
        mysecondstring.append("tagged");
    }
    if(tag==2){//tagged
        mysecondstring.append("notag");
    }
    //add other tagging
    
    
    return mysecondstring;
    
}

std::string GetFiles(std::string filename){
  // If on lxplus:
  //    std::string mystring = "/afs/cern.ch/work/j/jhinds/public/vvsemi/vvsemileptonic-hinds/Root/NewTreePlotter/";
  // If locally:
  std::string mystring = "../Samples/";
    
    std::string tempname = filename;
    std::string myname = tempname.append(".root");
    mystring.append(myname.c_str());
    
    std::cout<<"Using file: "<<mystring<<std::endl;
    
    return mystring;
    
}

std::vector<std::string> GetHistNames(int analysis,int region,int purity,int add,int kind,int signal,int vbf,int tag,int jetcollection){
    // Function used to produce 2D histogram names based on the inputs given. Returns a vector of strings which are the histogram names.
    
    // Define vectors which will be used to store names
    std::vector<std::string> myHistNames;
    std::vector<std::string> tempHistNames;
    
    // Call AnalysisOptions() from above to get cut names
    tempHistNames = AnalysisOption(analysis, signal, region, tag, vbf, purity, add, kind);
    // Define bkgs and signals
    std::string BKGS[5] = {"Wjets","Zjets","stop","ttbar","Diboson"};
    std::string SIGSVV[1] = {"HVTWZ"};
    std::string SIGSVH[1] = {"HVTZH"};
    
    // Loop through cut names and make them into histogram names
    for (int i=0; i<tempHistNames.size(); i++){
        std::string tempname = "";
        tempname = tempHistNames[i];
        
        if(signal == 6){//Bkg
            // Loop through bkgs to make 2D histogram name
            for (int j=0; j< sizeof(BKGS)/sizeof(BKGS[0]);j++){
                std::string s = BKGS[j];
                s.append("_Nominal_");
                s.append(tempname.c_str());
                if (analysis == 0){ // VV
                    s.append("_METSig_mVV");
                    myHistNames.push_back(s);
                }
                if (analysis == 1){ // VH
                    s.append("_METSig_mVH");
                    myHistNames.push_back(s);
                }
            }
        }
        if(signal < 6){//Sig
            if (analysis == 0){ // VV
                // Loop through signals to make 2D histogram name
                for (int j=0; j< sizeof(SIGSVV)/sizeof(SIGSVV[0]);j++){
                    std::string s = SIGSVV[j];
                    s.append("_Nominal_");
                    s.append(tempname.c_str());
                    s.append("_METSig_mVV");
                    myHistNames.push_back(s);
                }
            }
            if (analysis == 1){ // VH
                // Loop through signals to make 2D histogram name
                for (int j=0; j< sizeof(SIGSVH)/sizeof(SIGSVH[0]);j++){
                    std::string s = SIGSVH[j];
                    s.append("_Nominal_");
                    s.append(tempname.c_str());
                    s.append("_METSig_mVH");
                    myHistNames.push_back(s);
                }
            }
        }
    }
    
    
    return myHistNames; // Return 2D histogram names
}


std::string MakeFileName(bool normalize, bool ALL, std::string FileName){
    // Funtion to make a file name for the significance vs METSig cut. Returns a string which is the file name

    // basline file name
    std::string tempname = "METSig_cut";

    // modify file name based on specific requirements
    if(ALL == TRUE){
        tempname.append("_");
        tempname.append("ALLmass");
    }
    if(normalize == TRUE){
        tempname.append("_");
        tempname.append("normalized");
    }
    tempname.append("_");
    tempname.append(FileName);
    tempname.append(".pdf");
    
    return tempname; // return the file name
    
}

Double_t CalculateSignificance(std::vector<TH1D*> hists){
//    TCanvas *c2 = new TCanvas("c2", "c2",900,900);
   
    if (hists.empty()) {  return -1;}
    if (hists.size() < 2) { return -1;}
    
    TH1D * signal = hists[0];
    std::string name = signal->GetName();
    if(name.find("HVT") == -1) {
        return -1;}
    
//    signal->Draw("");
//    c2->Update();
//    c2->SaveAs("tempname.pdf");
    
    TH1D * btest = hists[1];
    std::cout<<"-----------------"<<std::endl;
    int nbins = signal->GetNbinsX();
//    std::cout<<"nbins: "<<nbins<<std::endl;
    int nbins_btest = btest->GetNbinsX();
//    std::cout<<"nbins btest: "<<nbins_btest<<std::endl;
    
    Double_t sigmai_i = 0;
    Double_t sigma = 0;
    
    for (int i = 0; i<nbins;i++){
        Double_t s_i = 0;
        Double_t b_i = 0;
        
        s_i = signal->GetBinContent(i+1);
//        std::cout<<"s_i "<<s_i<<std::endl;
        
        for (int j=1;j<hists.size();j++){
            
            b_i += hists[j]->GetBinContent(i+1);
//            std::cout<<"b_i "<<b_i<<std::endl;
            
        }
        
        if(s_i <= 0 ){
            Double_t temp_sigmai_i = 0;
//            temp_sigmai_i = s_i/std::sqrt(s_i + b_i + pow(0.1*b_i,2));
//            std::cout<<"temp_sigmai_i "<<temp_sigmai_i<<std::endl;
//            sigmai_i += pow(temp_sigmai_i,2);
            sigmai_i += 0;
//            std::cout<<"sigmai_i "<<sigmai_i<<std::endl;
            
        }
        
        else{
            Double_t temp_sigmai_i = 0;
            temp_sigmai_i = s_i/std::sqrt(s_i + b_i + pow(0.1*b_i,2));
//            std::cout<<"temp_sigmai_i "<<temp_sigmai_i<<std::endl;
            sigmai_i += pow(temp_sigmai_i,2);
//            std::cout<<"sigmai_i "<<sigmai_i<<std::endl;
        }
        
    }
    
    sigma = pow(sigmai_i,0.5);
    std::cout<<"Calculated sigma 1: "<<sigma<<std::endl;
    
    
    return sigma;
}

Double_t CalculateSignificance(std::vector<TH1F*> hists){
//    TCanvas *c2 = new TCanvas("c2", "c2",900,900);
    
    if (hists.empty()) {  return -1;}
    if (hists.size() < 2) { return -1;}
    
    TH1F * signal = hists[0];
    std::string name = signal->GetName();
    if(name.find("HVT") == -1) {
        return -1;}
    
//    std::cout<<"testing"<<std::endl;
//    signal->Draw("");
//    c2->Update();
//    c2->SaveAs("tempname.pdf");
    
    TH1F * btest = hists[1];
//    std::cout<<"-----------------"<<std::endl;
    int nbins = signal->GetNbinsX();
//    std::cout<<"nbins: "<<nbins<<std::endl;
    int nbins_btest = btest->GetNbinsX();
//    std::cout<<"nbins btest: "<<nbins_btest<<std::endl;
    
    Double_t sigmai_i = 0;
    Double_t sigma = 0;
    
//    std::cout<<"hist size:"<<hists.size()<<std::endl;
    
    for (int i = 0; i<nbins;i++){
        Double_t s_i = 0;
        Double_t b_i = 0;
        
        s_i = signal->GetBinContent(i+1);
//        std::cout<<"s_i "<<s_i<<std::endl;
        
        for (int j=1;j<hists.size();j++){
//            std::cout<<"--"<<std::endl;
//            std::cout<<"j "<<j<<std::endl;
            b_i += hists[j]->GetBinContent(i+1);
//            std::cout<<"b_i "<<b_i<<std::endl;
//            std::cout<<"--"<<std::endl;
            
        }
        
        if(s_i <= 0 ){
            Double_t temp_sigmai_i = 0;
//            temp_sigmai_i = s_i/std::sqrt(s_i + b_i + pow(0.1*b_i,2));
//            std::cout<<"temp_sigmai_i "<<temp_sigmai_i<<std::endl;
//            sigmai_i += pow(temp_sigmai_i,2);
            sigmai_i += 0;
//            std::cout<<"sigmai_i "<<sigmai_i<<std::endl;
            
        }
        
        else{
            Double_t temp_sigmai_i = 0;
            temp_sigmai_i = s_i/std::sqrt(s_i + b_i + pow(0.1*b_i,2));
//            std::cout<<"temp_sigmai_i "<<temp_sigmai_i<<std::endl;
            sigmai_i += pow(temp_sigmai_i,2);
//            std::cout<<"sigmai_i "<<sigmai_i<<std::endl;
        }
        
    }
    
    sigma = pow(sigmai_i,0.5);
//    std::cout<<"Calculated sigma 1: "<<sigma<<std::endl;
    
    
    return sigma;
}


