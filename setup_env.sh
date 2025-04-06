#Sets up environmental variables

# install ROOT environment
conda config --set channel_priority strict
conda create -c conda-forge --name hinds_CMSE802_env root
conda activate hinds_CMSE802_env

