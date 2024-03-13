# BtagEfficiencyMaps
To compute the final weight factor for BTagging efficiency, you need two key parameters:

1. Scale Factor (SF) from POG:
  a. This factor is obtained from the Physics Object Group (POG).
  b. It serves as one component for calculating the final BTagging SF.

2. Efficiency Calculated for Background Processes:
  a. Efficiency is determined for various background processes, taking into account event kinematics, and is expressed       as a function of Pt and Eta.
  b.This accounts for the impact of bTagging on event kinematics and is the second essential factor for the calculation.

Combining these two parameters in a specific manner yields the ultimate BTagging SF. For the exact implementation and mathematical details, please refer to Section 1(a) of the following link: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagSFMethods.

Additionally, you can find information on different BTagging working points, such as Loose, Medium, and Tight, for various schemes like Run2(UL) and Run3, in the BTV Internal Twiki: https://btv-wiki.docs.cern.ch/ScaleFactors/. This resource provides the numerical values associated with these working points, allowing you to select the appropriate ones for your specific needs.
