# CEDRIC_GSI analysis code for determination of temperature parameter from gamma spectrum incident on CEDRIC spectrometer.
# [huber@cenbg.in2p3.fr, huberarnaud@gmail.com]

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
# 1/ Measurement was done with electrons or only with gammas ?
# 2/ What is the PSL coef for the scanner used
# 3/ What is the number of PSL/mm² in IP number 1
# 4/ What is the number of PSL/mm² in IP number 2
# 5/ What is the number of PSL/mm² in IP number 3
# 6/ What is the number of PSL/mm² in IP number 4
# 7/ What is the number of PSL/mm² in IP number 5
# 8/ What is the number of PSL/mm² in IP number 6
# 9/ What is the number of PSL/mm² in IP number 7

# After that, all is automatic, the code will fit the DATA PSL DISTRIBUTIONS in order to output 2 parameters :
# 1/ N0 = Maximum number of gammas/electrons emitted from an exponential law
# 2/ E0 = Temperature from the exponential law

# A canvas will appear with a comparison between the DATA PSL DISTRIBUTION and this one reconstructed from the FIT with the Matrix and an illustration of the exponential law.

# If you want just to see an example, please enter a number >1 when the code ask you if the measurement was done with electrons or only with gammas. You will have an example of output !!!






# BACKUP FROM OLD Versions
# Commit #1 [CEDRIC_GSI.0.0.0]
# - Code from debug version (creation of Matrix at start) present in ENLCEDRICSim folder
# - Matrice et MatriceHP are coming from this code. In this present code, we will only use the ROOT file containing the Matrix
# - If E0 from fit is < 2 MeV, a second fit is apply with the MatriceHP. The process is automatic.

# Commit #2 [CEDRIC_GSI.0.0.1]
# - Pour le calcul permettant de ramener l'énergie déposée effective en énergie déposée effective par mm², le calcul de la surface effective des IPs de la simulation utilise désormais la vraie valeur de Pi au lieu d'une approximation
# - MAJ des fichiers ROOT afin de prendre en compte la surface effective du cylindre par rapport à la surface définie lors du tir avec un angle de 0.09 rad.

# Commit #3 [CEDRIC_GSI.0.1.0] le 26/09/2022
# - Ajout des matrices électrons général et HP
# - Modifications dans le code pour prendre en compte ces deux aspects. Question en début de programme pour savoir si on utilise les matrices électrons ou gammas.
# - Si mesures avec électrons, le programme effectue 3 fits différents (générale, HP large et HP avec bornes rétrecies à basses énergies) car il a été démontrée que cela permettait d'avoir un spectre correct sur l'ensemble de la gamme en énergie. A suivre avec des données réelles !!!!

# Commit #4 [CEDRIC_GSI.0.2.0] le 20/01/2023
# - Modifications du code pour le rendre automatique à partir des fichiers d'analyses de multigauge. Il suffit de rentrer les noms de fichiers et de lancer le code qui va analyser et sortir les résultats sous forme de .png
# - Corrections de quelques bugs concernant l'utilisation des matrices et la normalisation pour connaitre le nombre de particules totales émises pendant un tir.

# Commit #5 [CEDRIC_GSI.0.3.0] le 09/01/2024
# - Passage du code sur la version 11.2.0 de GEANT4
# - Passage de Atom vers Visual Code Studio avec notamment création d'une branche save permettant de push les changements d'une journée avant demerge sur la branche principale