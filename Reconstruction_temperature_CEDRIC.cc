#include "Reconstruction_temperature_CEDRIC.hh"

void Reconstruction_temperature_CEDRIC()
{

  float Calib_PSL = 0.695;
  float solid_angle1 = 0.0218;
  float solid_angle2 = 0.00815;

  //SHOT GSI
  
  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_1_A.txt", "Mesures_Shot_1_A", Calib_PSL, solid_angle1, 46.79);
  
  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_648_A.txt", "Mesures_Shot_648_A", Calib_PSL, solid_angle1, 10.38);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_649_A.txt", "Mesures_Shot_649_A", Calib_PSL, solid_angle1, 12.14);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_650_A.txt", "Mesures_Shot_650_A", Calib_PSL, solid_angle1, 11.57);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_655_A.txt", "Mesures_Shot_655_A", Calib_PSL, solid_angle1, 16.85);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_657_A.txt", "Mesures_Shot_657_A", Calib_PSL, solid_angle1, 11.57);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_659_A.txt", "Mesures_Shot_659_A", Calib_PSL, solid_angle1, 21.47);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_663_A.txt", "Mesures_Shot_663_A", Calib_PSL, solid_angle1, 14.05);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_667_A.txt", "Mesures_Shot_667_A", Calib_PSL, solid_angle1, 17.58);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_671_A.txt", "Mesures_Shot_671_A", Calib_PSL, solid_angle1, 16.09);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_674_A.txt", "Mesures_Shot_674_A", Calib_PSL, solid_angle1, 21.46);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_677_A.txt", "Mesures_Shot_677_A", Calib_PSL, solid_angle1, 14.05);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_678_A.txt", "Mesures_Shot_678_A", Calib_PSL, solid_angle1, 24.87);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_684_A.txt", "Mesures_Shot_684_A", Calib_PSL, solid_angle1, 14.74);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_687_A.txt", "Mesures_Shot_687_A", Calib_PSL, solid_angle1, 19.87);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_688_A.txt", "Mesures_Shot_688_A", Calib_PSL, solid_angle1, 17.56);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_698_A.txt", "Mesures_Shot_698_A", Calib_PSL, solid_angle1, 24.83);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_700_A.txt", "Mesures_Shot_700_A", Calib_PSL, solid_angle1, 18.32);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_702_A.txt", "Mesures_Shot_702_A", Calib_PSL, solid_angle1, 20.67);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_703_A.txt", "Mesures_Shot_703_A", Calib_PSL, solid_angle1, 16.85);

  //Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_704_A.txt", "Mesures_Shot_704_A", Calib_PSL, solid_angle2, 32.40);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_707_A.txt", "Mesures_Shot_707_A", Calib_PSL, solid_angle2, 19.07);
  

  //SHOT ELFIE

  //  Analyse();

  // TF1* f = new TF1("f", "[0]*exp(-(x/1)/[1])", 0, 300);
  // f->SetParameter(0, e9);
  // f->SetParameter(1, 1.208);
  // f->Draw();
  
  

}
