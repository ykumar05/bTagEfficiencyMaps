double VLLAna::getScaleFactors_bTagJets_MedWP_UL17(float eta, float pt){
  double scale_factor = 1.0;

  if(fabs(eta)<0.8){
    if( 20<pt && pt<30)
      scale_factor =  0.9519682519133669;
    if( 30<pt && pt<50)
      scale_factor =  0.9563256715252757;
    if( 50<pt && pt<70)
      scale_factor =  0.9608449158737093;
    if( 70<pt && pt<100)
      scale_factor =  0.9652537745696852;
    if( 100<pt && pt<140)
      scale_factor =  0.9700498537954898;
    if( 140<pt && pt<200)
      scale_factor =  0.9733563500565519;
    if( 200<pt && pt<300)
      scale_factor =  0.9814313982850057;
    if( 300<pt && pt<600)
      scale_factor =  0.9893550594758295;
    if( 600<pt && pt<1000)
      scale_factor =  1.0016175321086023;
    
  }
  
  else if(0.8<fabs(eta) && fabs(eta)<1.6){
    if( 20<pt && pt<30)
      scale_factor =  0.9519682519133669;
    if( 30<pt && pt<50)
      scale_factor =  0.9563256715252757;
    if( 50<pt && pt<70)
      scale_factor =  0.9608449158737093;
    if( 70<pt && pt<100)
      scale_factor =  0.9652537745696852;
    if( 100<pt && pt<140)
      scale_factor =  0.9700498537954898;
    if( 140<pt && pt<200)
      scale_factor =  0.9733563500565519;
    if( 200<pt && pt<300)
      scale_factor =  0.9814313982850057;
    if( 300<pt && pt<600)
      scale_factor =  0.9893550594758295;
    if( 600<pt && pt<1000)
      scale_factor =  1.0016175321086023;
  }
  
  else if(1.6<fabs(eta) && fabs(eta)<2.5){
    if( 20<pt && pt<30)
      scale_factor =  0.9519682519133669;
    if( 30<pt && pt<50)
      scale_factor =  0.9563256715252757;
    if( 50<pt && pt<70)
      scale_factor =  0.9608449158737093;
    if( 70<pt && pt<100)
      scale_factor =  0.9652537745696852;
    if( 100<pt && pt<140)
      scale_factor =  0.9700498537954898;
    if( 140<pt && pt<200)
      scale_factor =  0.9733563500565519;
    if( 200<pt && pt<300)
      scale_factor =  0.9814313982850057;
    if( 300<pt && pt<600)
      scale_factor =  0.9893550594758295;
    if( 600<pt && pt<1000)
      scale_factor =  1.0016175321086023;
  }
  return scale_factor;
}
double VLLAna::getScaleFactors_cTagJets_Mis_UL17(float eta, float pt){
  double scale_factor = 1.0;

  if(fabs(eta)<0.8){
    if( 20<pt && pt<30)
      scale_factor =  0.9519682519133669;
    if( 30<pt && pt<50)
      scale_factor =  0.9563256715252757;
    if( 50<pt && pt<70)
      scale_factor =  0.9608449158737093;
    if( 70<pt && pt<100)
      scale_factor =  0.9652537745696852;
    if( 100<pt && pt<140)
      scale_factor =  0.9700498537954898;
    if( 140<pt && pt<200)
      scale_factor =  0.9733563500565519;
    if( 200<pt && pt<300)
      scale_factor =  0.9814313982850057;
    if( 300<pt && pt<600)
      scale_factor =  0.9893550594758295;
    if( 600<pt && pt<1000)
      scale_factor =  1.0016175321086023;
    
  }
  
  else if(0.8<fabs(eta) && fabs(eta)<1.6){
    if( 20<pt && pt<30)
      scale_factor =  0.9519682519133669;
    if( 30<pt && pt<50)
      scale_factor =  0.9563256715252757;
    if( 50<pt && pt<70)
      scale_factor =  0.9608449158737093;
    if( 70<pt && pt<100)
      scale_factor =  0.9652537745696852;
    if( 100<pt && pt<140)
      scale_factor =  0.9700498537954898;
    if( 140<pt && pt<200)
      scale_factor =  0.9733563500565519;
    if( 200<pt && pt<300)
      scale_factor =  0.9814313982850057;
    if( 300<pt && pt<600)
      scale_factor =  0.9893550594758295;
    if( 600<pt && pt<1000)
      scale_factor =  1.0016175321086023;
    
  }
  
  else if(1.6<fabs(eta) && fabs(eta)<2.5){
    if( 20<pt && pt<30)
      scale_factor =  0.9519682519133669;
    if( 30<pt && pt<50)
      scale_factor =  0.9563256715252757;
    if( 50<pt && pt<70)
      scale_factor =  0.9608449158737093;
    if( 70<pt && pt<100)
      scale_factor =  0.9652537745696852;
    if( 100<pt && pt<140)
      scale_factor =  0.9700498537954898;
    if( 140<pt && pt<200)
      scale_factor =  0.9733563500565519;
    if( 200<pt && pt<300)
      scale_factor =  0.9814313982850057;
    if( 300<pt && pt<600)
      scale_factor =  0.9893550594758295;
    if( 600<pt && pt<1000)
      scale_factor =  1.0016175321086023;
  }
  return scale_factor;
}
double VLLAna::getScaleFactors_LightTagJets_Mis_UL17(float eta, float pt){
  double scale_factor = 1.0;

  if(fabs(eta)<0.8){
    if( 20<pt && pt<30)
      scale_factor =  1.253307440625;
    if( 30<pt && pt<50)
      scale_factor =  1.2712693499999999;
    if( 50<pt && pt<70)
      scale_factor =  1.2714768433333332;
    if( 70<pt && pt<100)
      scale_factor =  1.2610167726838233;
    if( 100<pt && pt<140)
      scale_factor =  1.2405895966666667;
    if( 140<pt && pt<200)
      scale_factor =  1.2216736958333334;
    if( 200<pt && pt<300)
      scale_factor =  1.1608665224999999;
    if( 300<pt && pt<600)
      scale_factor =  1.088226675;
    if( 600<pt && pt<1000)
      scale_factor =  1.0281731374999998;
    
  }
  
  else if(0.8<fabs(eta) && fabs(eta)<1.6){
    if( 20<pt && pt<30)
      scale_factor =  1.253307440625;
    if( 30<pt && pt<50)
      scale_factor =  1.2712693499999999;
    if( 50<pt && pt<70)
      scale_factor =  1.2714768433333332;
    if( 70<pt && pt<100)
      scale_factor =  1.2610167726838233;
    if( 100<pt && pt<140)
      scale_factor =  1.2405895966666667;
    if( 140<pt && pt<200)
      scale_factor =  1.2216736958333334;
    if( 200<pt && pt<300)
      scale_factor =  1.1608665224999999;
    if( 300<pt && pt<600)
      scale_factor =  1.088226675;
    if( 600<pt && pt<1000)
      scale_factor =  1.0281731374999998;
    
  }
  
  else if(1.6<fabs(eta) && fabs(eta)<2.5){
    if( 20<pt && pt<30)
      scale_factor =  1.253307440625;
    if( 30<pt && pt<50)
      scale_factor =  1.2712693499999999;
    if( 50<pt && pt<70)
      scale_factor =  1.2714768433333332;
    if( 70<pt && pt<100)
      scale_factor =  1.2610167726838233;
    if( 100<pt && pt<140)
      scale_factor =  1.2405895966666667;
    if( 140<pt && pt<200)
      scale_factor =  1.2216736958333334;
    if( 200<pt && pt<300)
      scale_factor =  1.1608665224999999;
    if( 300<pt && pt<600)
      scale_factor =  1.088226675;
    if( 600<pt && pt<1000)
      scale_factor =  1.0281731374999998;
  }
  return scale_factor;
}
