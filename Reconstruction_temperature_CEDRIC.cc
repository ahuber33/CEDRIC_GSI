#include "Reconstruction_temperature_CEDRIC.hh"

void Reconstruction_temperature_CEDRIC()
{
  Init_IP();
  cout << "\n\n1/ Measurement with electrons [1] or only with gammas [0] ?" << endl;
  cin >> flag_electron;
  if(flag_electron ==0) cout << "Measurement only with gammas !!!!" << endl;
  if(flag_electron ==1) cout << "Measurement with electrons !!!!" << endl;
  if(flag_electron >1) Programme_Test();

  if(flag_electron <=1)
  {
    cout << "\n\n2/ Enter the PSL coefficient [PSL/MeV] (default is 6.95E-1) :" << endl;
    cin >> Coef_PSL;
    cout << "PSL Coef = " << Coef_PSL << endl;

    cout << "\n\nEnter the number of PSL/mm² in IP number 1 :" << endl;
    cin >> IP[0];

    cout << "Enter the number of PSL/mm² in IP number 2 :" << endl;
    cin >> IP[1];

    cout << "Enter the number of PSL/mm² in IP number 3 :" << endl;
    cin >> IP[2];

    cout << "Enter the number of PSL/mm² in IP number 4 :" << endl;
    cin >> IP[3];

    cout << "Enter the number of PSL/mm² in IP number 5 :" << endl;
    cin >> IP[4];

    cout << "Enter the number of PSL/mm² in IP number 6 :" << endl;
    cin >> IP[5];

    cout << "Enter the number of PSL/mm² in IP number 7 :" << endl;
    cin >> IP[6];

  }


  if(flag_electron==0 || flag_electron >1)
  {
    DefineMatrice(Coef_PSL);
    DefineMatriceHP(Coef_PSL);
  }

  if(flag_electron==1)
  {
    DefineMatriceElectron(Coef_PSL);
    DefineMatriceHPElectron(Coef_PSL);
  }

  new TCanvas;
  MatriceHP->Draw("colz");

  new TCanvas;
  Matrice->Draw("colz");


  float start_0 = 10;
  float step_0 = 0.1;
  float low_0 = 1;
  float up_0 = 100;

  float start_1 = 10;//10
  float step_1 = 0.1;
  float low_1 = 0; //-1
  float up_1 = 30; //30



  Create_Pad_Canvas();
  Histo_DATA(IP);
  pad1->cd();
  if(flag_electron==0 || flag_electron >1)
  {
    FIT_MINUIT(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
    if (E0 <=2)
    {
      HP=true;
      FIT_MINUIT(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
    }
  }

  if(flag_electron==1)
  {
    FIT_MINUIT(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
    Chi2_store=Chi2;
    HP=true;
    FIT_MINUIT(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
    Chi2_HP_store=Chi2;
    FIT_MINUIT(start_0, step_0, low_0, up_0, 0.5, step_1, low_1, 1., HP);
    Chi2_HPbis_store=Chi2;

    if(Chi2_store < Chi2_HP_store && Chi2_store < Chi2_HPbis_store)
    {
      HP=false;
      FIT_MINUIT(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
    }
    if(Chi2_HP_store < Chi2_store && Chi2_HP_store < Chi2_HPbis_store) FIT_MINUIT(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
    if(Chi2_HPbis_store < Chi2_store && Chi2_HPbis_store < Chi2_HP_store) FIT_MINUIT(start_0, step_0, low_0, up_0, 0.5, step_1, low_1, 1.5, HP);
  }
  pad2->cd();
  pad2->SetLogy();
  Draw_Incident_Spectrum_Fit(A, E0, flag_electron);





}
