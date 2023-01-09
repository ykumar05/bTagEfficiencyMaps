double VLLAna::getScaleFactors_bTagJets_MedWP_UL18(float eta, float pt){
  double scale_factor = 1.0;

  if(fabs(eta)<0.8){
    if( 20<pt && pt<30)
      scale_factor =  0.9385400437200391;
    if( 30<pt && pt<50)
      scale_factor =  0.948300458728094;
    if( 50<pt && pt<70)
      scale_factor =  0.9569614973550692;
    if( 70<pt && pt<100)
      scale_factor =  0.96395228595033;
    if( 100<pt && pt<140)
      scale_factor =  0.969881763737521;
    if( 140<pt && pt<200)
      scale_factor =  0.9729258947186322;
    if( 200<pt && pt<300)
      scale_factor =  0.9766315701807073;
    if( 300<pt && pt<600)
      scale_factor =  0.9748256225693339;
    if( 600<pt && pt<1000)
      scale_factor =  0.9603165903672826;
    
  }
  
  else if(0.8<fabs(eta) && fabs(eta)<1.6){
    if( 20<pt && pt<30)
      scale_factor =  0.9385400437200391;
    if( 30<pt && pt<50)
      scale_factor =  0.948300458728094;
    if( 50<pt && pt<70)
      scale_factor =  0.9569614973550692;
    if( 70<pt && pt<100)
      scale_factor =  0.96395228595033;
    if( 100<pt && pt<140)
      scale_factor =  0.969881763737521;
    if( 140<pt && pt<200)
      scale_factor =  0.9729258947186322;
    if( 200<pt && pt<300)
      scale_factor =  0.9766315701807073;
    if( 300<pt && pt<600)
      scale_factor =  0.9748256225693339;
    if( 600<pt && pt<1000)
      scale_factor =  0.9603165903672826;
    
  }
  
  else if(1.6<fabs(eta) && fabs(eta)<2.5){
    if( 20<pt && pt<30)
      scale_factor =  0.9385400437200391;
    if( 30<pt && pt<50)
      scale_factor =  0.948300458728094;
    if( 50<pt && pt<70)
      scale_factor =  0.9569614973550692;
    if( 70<pt && pt<100)
      scale_factor =  0.96395228595033;
    if( 100<pt && pt<140)
      scale_factor =  0.969881763737521;
    if( 140<pt && pt<200)
      scale_factor =  0.9729258947186322;
    if( 200<pt && pt<300)
      scale_factor =  0.9766315701807073;
    if( 300<pt && pt<600)
      scale_factor =  0.9748256225693339;
    if( 600<pt && pt<1000)
      scale_factor =  0.9603165903672826;
  }
  return scale_factor;
}
double VLLAna::getScaleFactors_cTagJets_Mis_UL18(float eta, float pt){
  double scale_factor = 1.0;

  if(fabs(eta)<0.8){
    if( 20<pt && pt<30)
      scale_factor =  0.9385400437200391;
    if( 30<pt && pt<50)
      scale_factor =  0.948300458728094;
    if( 50<pt && pt<70)
      scale_factor =  0.9569614973550692;
    if( 70<pt && pt<100)
      scale_factor =  0.96395228595033;
    if( 100<pt && pt<140)
      scale_factor =  0.969881763737521;
    if( 140<pt && pt<200)
      scale_factor =  0.9729258947186322;
    if( 200<pt && pt<300)
      scale_factor =  0.9766315701807073;
    if( 300<pt && pt<600)
      scale_factor =  0.9748256225693339;
    if( 600<pt && pt<1000)
      scale_factor =  0.9603165903672826;
  }
  
  else if(0.8<fabs(eta) && fabs(eta)<1.6){
    if( 20<pt && pt<30)
      scale_factor =  0.9385400437200391;
    if( 30<pt && pt<50)
      scale_factor =  0.948300458728094;
    if( 50<pt && pt<70)
      scale_factor =  0.9569614973550692;
    if( 70<pt && pt<100)
      scale_factor =  0.96395228595033;
    if( 100<pt && pt<140)
      scale_factor =  0.969881763737521;
    if( 140<pt && pt<200)
      scale_factor =  0.9729258947186322;
    if( 200<pt && pt<300)
      scale_factor =  0.9766315701807073;
    if( 300<pt && pt<600)
      scale_factor =  0.9748256225693339;
    if( 600<pt && pt<1000)
      scale_factor =  0.9603165903672826;
    
  }
  
  else if(1.6<fabs(eta) && fabs(eta)<2.5){
    if( 20<pt && pt<30)
      scale_factor =  0.9385400437200391;
    if( 30<pt && pt<50)
      scale_factor =  0.948300458728094;
    if( 50<pt && pt<70)
      scale_factor =  0.9569614973550692;
    if( 70<pt && pt<100)
      scale_factor =  0.96395228595033;
    if( 100<pt && pt<140)
      scale_factor =  0.969881763737521;
    if( 140<pt && pt<200)
      scale_factor =  0.9729258947186322;
    if( 200<pt && pt<300)
      scale_factor =  0.9766315701807073;
    if( 300<pt && pt<600)
      scale_factor =  0.9748256225693339;
    if( 600<pt && pt<1000)
      scale_factor =  0.9603165903672826;
  }
  return scale_factor;
}
double VLLAna::getScaleFactors_LightTagJets_Mis_UL18(float eta, float pt){
  double scale_factor = 1.0;

  if(fabs(eta)<0.8){
    if( 20<pt && pt<30)
      scale_factor =  1.261626821875;
    if( 30<pt && pt<50)
      scale_factor =  1.2635281156;
    if( 50<pt && pt<70)
      scale_factor =  1.2572170342666669;
    if( 70<pt && pt<100)
      scale_factor =  1.245687416592647;
    if( 100<pt && pt<140)
      scale_factor =  1.2282338337333334;
    if( 140<pt && pt<200)
      scale_factor =  1.2135829041666668;
    if( 200<pt && pt<300)
      scale_factor =  1.1712895614999999;
    if( 300<pt && pt<600)
      scale_factor =  1.131385225;
    if( 600<pt && pt<1000)
      scale_factor =  1.1725721725000002;
    
  }
  
  else if(0.8<fabs(eta) && fabs(eta)<1.6){
    if( 20<pt && pt<30)
      scale_factor =  1.261626821875;
    if( 30<pt && pt<50)
      scale_factor =  1.2635281156;
    if( 50<pt && pt<70)
      scale_factor =  1.2572170342666669;
    if( 70<pt && pt<100)
      scale_factor =  1.245687416592647;
    if( 100<pt && pt<140)
      scale_factor =  1.2282338337333334;
    if( 140<pt && pt<200)
      scale_factor =  1.2135829041666668;
    if( 200<pt && pt<300)
      scale_factor =  1.1712895614999999;
    if( 300<pt && pt<600)
      scale_factor =  1.131385225;
    if( 600<pt && pt<1000)
      scale_factor =  1.1725721725000002;
    
  }
  
  else if(1.6<fabs(eta) && fabs(eta)<2.5){
    if( 20<pt && pt<30)
      scale_factor =  1.261626821875;
    if( 30<pt && pt<50)
      scale_factor =  1.2635281156;
    if( 50<pt && pt<70)
      scale_factor =  1.2572170342666669;
    if( 70<pt && pt<100)
      scale_factor =  1.245687416592647;
    if( 100<pt && pt<140)
      scale_factor =  1.2282338337333334;
    if( 140<pt && pt<200)
      scale_factor =  1.2135829041666668;
    if( 200<pt && pt<300)
      scale_factor =  1.1712895614999999;
    if( 300<pt && pt<600)
      scale_factor =  1.131385225;
    if( 600<pt && pt<1000)
      scale_factor =  1.1725721725000002;
  }
  return scale_factor;
}
