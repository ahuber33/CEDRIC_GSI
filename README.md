# CEDRIC_GSI analysis code for determination of temperature paramter from gamma spectrum incident on CEDRIC spectrometer.
#[huber@ecnbg.in2p3.fr, huberarnaud@gmail.com]

# HOW TO USE THE ANALYSE CODE ?

# First, you need to use ROOT. For that, if you don't have it on your computer, you can :
# 1/ Directly download and install ROOT from https://root.cern/install/
# or
# 2/ Download a VMware with ROOT directly installed here : https://heberge.lp2ib.in2p3.fr/G4VM/Vmware/Old-Versions/
# or
# 3/ If you're from LP2IB lab, you can connect on borlin333 for example with ssh, copy this folder and execute the code.

# For an analysis, you don't need to write/modify the code itself. Juste run the program with :
# root -l Reconstruction_temperature_CEDRIC.cc

# At this time, the code will ask you in order :
# 1/ What is the PSL coef for the scanner used
# 2/ What is the number of PSL/mm² in IP number 1
# 3/ What is the number of PSL/mm² in IP number 2
# 4/ What is the number of PSL/mm² in IP number 3
# 5/ What is the number of PSL/mm² in IP number 4
# 6/ What is the number of PSL/mm² in IP number 5
# 7/ What is the number of PSL/mm² in IP number 6
# 8/ What is the number of PSL/mm² in IP number 7

# After that, all is automatic, the code will fit the DATA PSL DISTRIBUTIONS in order to output 2 parameters :
# 1/ N0 = Maximum number of gammas emitted from an exponential law
# 2/ E0 = Temperature from the exponential law

# A canvas will appear with a comparison between the DATA PSL DISTRIBUTION and this one reconstructed from the FIT with the Matrix and an illustration of the exponential law.






# BACKUP FROM OLD Versions
# Commit #1 [CEDRIC_GSI.0.0.0]
# Code from debug version (creation of Matrix at start) present in ENLCEDRICSim folder
# Matrice et MatriceHP are coming from this code. In this present code, we will only use the ROOT file containing the Matrix
# If E0 from fit is < 2 MeV, a second fit is apply with the MatriceHP. The process is automatic.
