FROM atlas/analysisbase:21.2.205
ADD . /VVSemi/CxAODReader_VVSemileptonic
WORKDIR /VVSemi/build
RUN source /home/atlas/release_setup.sh && \
      sudo chown -R atlas /VVSemi && \
      asetup,AnalysisBase,21.2.205 && \
      cmake -DBUILTIN_BOOST=true -DBUILTIN_EIGEN=true ../CxAODReader_VVSemileptonic && \
      make -j8
      
#FROM atlas/centos7-atlasos:latest
#ADD . /VVSemi/CxAODReader_VVSemileptonic
#WORKDIR /VVSemi/build
#RUN export ATLAS_LOCAL_ROOT_BASE="/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase" && \
#      alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh' && \
#      export AtlasSetup="/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/AtlasSetup/current/AtlasSetup" && \
#      alias asetup='source $AtlasSetup/scripts/asetup.sh $*' 
#      setupATLAS && \
#      asetup,AnalysisBase,21.2.205 && \
#      sudo chown -R atlas /VVSemi && \
#      cmake -DBUILTIN_BOOST=true -DBUILTIN_EIGEN=true ../CxAODReader_VVSemileptonic && \
#      make -j8
