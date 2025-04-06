// functions for producing cutflow histograms

std::vector<std::string> GetPath(int analysis,int region,int purity,int add,int kind,int signal,int vbf,int tag,int jetcollection){
    
    /*
     This function returns information about where the samples are stored based on the inputs provided.
     
     returns a vector of strings
     [folder name,
        path to folder,
            path to subfolder]
    
     example:
      [JetCollectCompar_v05_mc16a_VV_0lep_sig_PFlow_UFO ,
        /afs/cern.ch/work/j/jhinds/public/vvsemi/ntuplesJetCollectCompar_v05_mc16a_VV_0lep_sig_PFlow_UFO/,
                /afs/cern.ch/work/j/jhinds/public/vvsemi/ntuplesJetCollectCompar_v05_mc16a_VV_0lep_sig_PFlow_UFO/fetch/
            
     
     */
    
    std::vector<std::string> myNames;
    std::string path = "/eos/user/j/jhinds/VVSemileptonic/CMSE/";
    // Public space, can also be downloaded/viewed from here: https://cernbox.cern.ch/index.php/s/TOpNUxaIH58lzcO 
    
    std::string mainName = "cutflow_v06_mc16a_";
    //need to add if-statement for VV or VH

    // Below builds the name of the file based on the inputs
    if(analysis == 0){ // VV
        mainName.append("VV_");
    }
    if(analysis == 1){ // VH
        mainName.append("VH_");
    }
    if(analysis != 0 && analysis != 1){
        std::cout<<"analysis: "<<analysis<<std::endl;
        std::cout<<"ERROR! Analysis not defined!"<<std::endl;

    }
    
    mainName.append("0lep_");
    
    if(signal <= 5){//signal
        mainName.append("sig_");
    }
    if(signal == 6){//bkg
        mainName.append("bkg_");
    }
    if(signal < 0 | signal > 6){
        std::cout<<"signal: "<<signal<<std::endl;
        std::cout<<"ERROR! Signal not defined!"<<std::endl;

    }
    
    if(jetcollection==0){//EMTopo LCTopo
        mainName.append("EMTopo_LCTopo");
    }
    if(jetcollection==1){//EMTopo TCC
        mainName.append("EMTopo_TCC");
    }
    if(jetcollection==2){//PFlow UFO
        mainName.append("PFlow_UFO");
    }
    if(jetcollection < 0 | jetcollection > 2){
        std::cout<<"jetcollection: "<<jetcollection<<std::endl;
        std::cout<<"ERROR! Jet Collection not defined!"<<std::endl;

    }
    
    myNames.push_back(mainName);
    
    path.append(mainName);
    path.append("/");
    
    myNames.push_back(path);
    
    path.append("fetch/");
    
    myNames.push_back(path);
    
    
    return myNames;
    
}

std::vector<std::string> GetFiles(int analysis,int signal,std::string path){
    // This function gets analysis and signal information as well as the path to the main file. Then it opens the ROOT file and gets the names of the files contained in the ROOT file. It returns this list of names.
    
    std::vector<std::string> myFiles;
    std::string temppath = path;
    
    // Make a copy of the path name and convert to char type
    char src[100];
    strcpy(src, temppath.c_str());
    
    // Check to make sure the dieactory exists and open it
    char *dirFilename = src;
    DIR *directory = NULL;
    directory = opendir (dirFilename);
    
    // Whils inside the directory is open, look for a specific ROOT file
    struct dirent *dirp;
        while ((dirp = readdir (directory)) != NULL) {
            std::cout<<"test"<<std::endl;
            if ( strstr(dirp->d_name , ".root" )){
                if ( strstr(dirp->d_name , "amerged" )){
                
                        // If ROOT file is found, push back to a vector
                        myFiles.push_back(dirp->d_name);
                    
                    }
                    
                //else{
                    //printf( "found a .root file: %s\n", dirp->d_name );
                    //std::cout<<"No merged file found. Make sure you run hadd first!"<<std::endl;
                    //myFiles.push_back(dirp->d_name);
                        
                //}
                }
        }
    // Return the name of the file
    return myFiles;

}

bool mycomp(string a, string b){
    //returns 1 if string a is alphabetically
    //less than string b
    //quite similar to strcmp operation
    return a<b;
}

std::vector<std::string> alphabaticallySort(std::vector<std::string> a){
    int n=a.size();
    //mycomp function is the defined function which
    //sorts the strings in alphabatical order
    sort(a.begin(),a.end(),mycomp);
    std::cout<<"test"<<std::endl;
    return a;
}

std::string SaveName(int analysis,int region,int purity,int add,int kind,int signal,int vbf,int tag,int jetcollection){
    
    // Creates a string that will be the output file name based on the input parameters
    // Returns a string that will be made into a PDF
    
    std::string savename;
    if(analysis == 0){
        savename = "VV";
        savename.append("_validation_");
        // ADD HERE
        if( purity == 0){
            savename.append("LP_");
        }
        if( purity == 1){
            savename.append("HP_");
        }
        if(tag==0){
            savename.append("tagged_");
        }
        if(tag==1){
            savename.append("untagged_");
        }
        if(tag==2){
            savename.append("notag");
        }
    }
    if(analysis == 1){
        savename = "VH";
        savename.append("_validation_");
    
        if(kind==0){
            savename.append("merg_");
        }
        if(kind==1){
            savename.append("res_");
    }
        if(tag==0){
            std::cout<<"no tagging"<<std::endl;
        }
        if(tag==1){
            savename.append("onetagged");
        }
        if(tag==2){
            savename.append("twotagged");
        }
    }
    
    if(jetcollection==0){//EMTopo LCTopo
        savename.append("EMTopo_LCTopo");
    }
    if(jetcollection==1){//EMTopo TCC
        savename.append("EMTopo_TCC");
    }
    if(jetcollection==2){//PFlow UFO
        savename.append("PFlow_UFO");
    }
    if(jetcollection < 0 | jetcollection > 2){
        std::cout<<"jetcollection: "<<jetcollection<<std::endl;
        std::cout<<"ERROR! Jet Collection not defined!"<<std::endl;

    }
    
    savename.append(".pdf");
    return savename;
}
