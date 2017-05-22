# RootTutorial

Welcome to the root tutorial! 

This is intended for incoming undergrad (or even grad students) interested high energy physics given during the summer 2017 session at Rutgers. Almost all experiments in the field utilize ROOT as the standard data analysis and visualization toolkit. The following tutorial assumes that you have ROOT 6.04 (or above) installed in your personal laptop and the corresponding pre-requisites. We begin with an assumption of familiarity with bash and c++ (or maybe some python).   

I will be running this on my mac book air and its quite easy to install root via the source code from here: https://root.cern.ch/ 

If you do not have root installed by the start of this tutorial, please start the install procedure (with the help of someone, either myself of Ian) and in the meanwhile, you can run root (if you have a cern account) on the swan system here: https://swanserver.web.cern.ch/swanserver/rootdemo/.   

This tutorial is based on the excellent 2015 summer school lectures at CERN https://indico.cern.ch/event/395198/attachments/791523/1084984/ROOT_Summer_Student_Tutorial_2015.pdf   

The following are some of the most fundamental tasks
1. Read a text file with input information   
2. Create and fit the histogram/distributions based on a given function 
3. Make plots/histograms and save the plots as .pdf   

More advanced tasks 
1. Read and analyze events from a ROOT file with the tree structure  
2. Visualize the information in the trees via a object browser 
3. Loop over the events and create histograms to store meaningful variables
4. Perform simple operations on the histograms and write the output to a ROOT file 
