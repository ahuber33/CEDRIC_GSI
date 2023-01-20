#include "Reconstruction_temperature_CEDRIC.hh"

void Reconstruction_temperature_CEDRIC()
{

  float Calib_PSL = 0.695;
  float solid_angle1 = 0.0218;
  float solid_angle2 = 0.00815;

  //SHOT GSI

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_1_A.txt", "Mesures_Shot_1_A", Calib_PSL, solid_angle1);
  
  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_648_A.txt", "Mesures_Shot_648_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_649_A.txt", "Mesures_Shot_649_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_650_A.txt", "Mesures_Shot_650_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_655_A.txt", "Mesures_Shot_655_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_657_A.txt", "Mesures_Shot_657_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_659_A.txt", "Mesures_Shot_659_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_663_A.txt", "Mesures_Shot_663_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_667_A.txt", "Mesures_Shot_667_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_671_A.txt", "Mesures_Shot_671_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_674_A.txt", "Mesures_Shot_674_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_677_A.txt", "Mesures_Shot_677_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_678_A.txt", "Mesures_Shot_678_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_684_A.txt", "Mesures_Shot_684_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_687_A.txt", "Mesures_Shot_687_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_688_A.txt", "Mesures_Shot_688_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_698_A.txt", "Mesures_Shot_698_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_700_A.txt", "Mesures_Shot_700_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_702_A.txt", "Mesures_Shot_702_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_703_A.txt", "Mesures_Shot_703_A", Calib_PSL, solid_angle1);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_704_A.txt", "Mesures_Shot_704_A", Calib_PSL, solid_angle2);

  Routine_Analyse("Analyses_MultiGauge/Mesures_Shot_707_A.txt", "Mesures_Shot_707_A", Calib_PSL, solid_angle2);


  //SHOT ELFIE

}
