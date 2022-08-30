#include "Reconstruction_temperature_CEDRIC.hh"

void Reconstruction_temperature_CEDRIC()
{
  Init_IP();
  cout << "PSL Coef = " << Coef_PSL << endl;
  cout << "Enter the PSL coefficient [PSL/MeV] (default is 6.95E-1) :" << endl;
  cin >> Coef_PSL;
  cout << "PSL Coef = " << Coef_PSL << endl;

  cout << "Enter the number of PSL/mm² in IP number 1 :" << endl;
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


  DefineMatrice(Coef_PSL);
  DefineMatriceHP(Coef_PSL);

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
  FIT_MINUIT(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
  if (E0 <=2)
    {
      HP=true;
      FIT_MINUIT(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
    }

  pad2->cd();
  pad2->SetLogy();
  Draw_Incident_Gamma_Spectrum_Fit(A, E0);




}
