TH1D* PSL_REF;
TH1D* Edep_REF;
TH1D* h;
TFile* file;
TH2F* Matrice = new TH2F("matrice", "matrice", 7, 0.5, 7.5, 200, 0, 200);
TH2F* MatriceHP = new TH2F("matriceHP", "matriceHP", 7, 0.5, 7.5, 100, 0, 10);
TH1D* PSL_Rec = new TH1D ("PSL_Rec", "PSL_Rec", 7, 0.5, 7.5);
TH1D* h_e;
TH1D* h_g;
TH1D* Data = new TH1D ("Data", "Data", 7, 0.5, 7.5);
TH1F *Fit = new TH1F("fit", "fit", 200, 0, 200);
TH1F *FitHP = new TH1F("fitHP", "fitHP", 100, 0, 10);
TH1D* REF;
float Chi2=0;
double A=0;
double err_A=0;
double E0=0;
double err_E0=0;
double NEvents=0;
double Coef_PSL = 6.95E-1;
//double Coef_PSL = 1.3E-1;
int flag_electron = 0;
bool HP=false;
float IP[7];
TPad *pad1;
TPad *pad2;
TCanvas* c;
TF1* f1;
float Chi2_gamma_store=0;
float Chi2_gamma_HP_store=0;
float Chi2_store=0;
float Chi2_HP_store=0;
float Chi2_HPbis_store=0;
double N=0;
double eN=0;
float solid_angle=0;
double Surface =0;


void Create_Pad_Canvas(const char* name)
{
  gStyle->SetOptTitle(kFALSE);
  c = new TCanvas(name, name, 0, 10, 1600, 700);
  c->SetWindowPosition(600, 0);
  pad1 = new TPad("pad1", "", 0.0, 0.0, 0.5, 1);
  pad2 = new TPad("pad2", "", 0.51, 0.0, 1, 1);

  pad1->Draw();
  pad2->Draw();

}


void Init_IP()
{
  for (int i=0; i<7; i++)
  {
    IP[i] =0;
  }
}


double NumberOfEntries(const char* filename)
{
  TFile* file = new TFile(filename);
  TTree* Tree = (TTree*)file->Get("IP");
  int Entries = Tree->GetEntries();

  file->Close();

  return Entries;
}


void DefineMatrice(double coef_PSL, double Surface)
{
  TFile* f_Matrice = new TFile("CEDRIC_Matrice_gamma.root");
  Matrice = (TH2F*)f_Matrice->Get("matrice");
  Matrice->Scale(Coef_PSL/Surface);
}

void DefineMatriceHP(double coef_PSL, double Surface)
{
  TFile* f_MatriceHP = new TFile("CEDRIC_MatriceHP_gamma.root");
  MatriceHP = (TH2F*)f_MatriceHP->Get("matriceHP");
  MatriceHP->Scale(Coef_PSL/Surface);
}


void DefineMatriceElectron(double coef_PSL, double Surface)
{
  TFile* f_Matrice = new TFile("CEDRIC_Matrice_electron.root");
  Matrice = (TH2F*)f_Matrice->Get("matrice");
  Matrice->Scale(Coef_PSL/Surface);
}

void DefineMatriceHPElectron(double coef_PSL, double Surface)
{
  TFile* f_MatriceHP = new TFile("CEDRIC_MatriceHP_electron.root");
  MatriceHP = (TH2F*)f_MatriceHP->Get("matriceHP");
  MatriceHP->Scale(Coef_PSL/Surface);
}



TH1D* Histo_PSL(const char* filename)
{
  file = new TFile(filename, "update");
  PSL_REF = (TH1D*)file->Get("PSL vs IP");
  Edep_REF = (TH1D*)file->Get("edep_totale_eff");
  Edep_REF->Scale(0.001);

  int n = PSL_REF->GetNbinsX();
  NEvents = NumberOfEntries(filename);
  double Integral = Edep_REF->Integral();
  double Error_Edep=0;
  double Error_PSL=0;
  double Coef_PSL = 6.95E-1;

  for (int i=1; i<=n; i++)
  {
    Error_Edep = sqrt((Edep_REF->Integral(i,i)*Integral)/NEvents); //si graph Edep
    Error_PSL = Error_Edep*Coef_PSL; // si graph PSL
    Edep_REF->SetBinError(i, Error_Edep);
    PSL_REF->SetBinError(i, Error_PSL);
  }


  PSL_REF->SetDirectory(nullptr);
  Edep_REF->SetDirectory(nullptr);
  file->Close();
  //delete file;

  //return PSL_REF;
  return Edep_REF;

}


void Calcul_Chi2(TH1D* O, TH1D* C)
{
  Chi2=0;
  int n = C->GetNbinsX();
  float sigma=0;

  for (int i=1; i<=6; i++)
  {
    sigma = C->GetBinError(i);

    if(C->GetBinContent(i) !=0 && sigma !=0)
    {
      // Chi2+= ((O->GetBinContent(i) - C->GetBinContent(i)) * (O->GetBinContent(i) - C->GetBinContent(i))) / (C->GetBinContent(i) + (sigma*sigma));
      Chi2+= ((O->GetBinContent(i) - C->GetBinContent(i)) * (O->GetBinContent(i) - C->GetBinContent(i))) / (sigma*sigma);

    }
  }
}


Double_t fitFunc(float x, Double_t* par)
{
  Double_t PDF =0.0;
  PDF = par[0]*exp(-(x/1)/par[1]);

  return PDF;
}


Double_t fitFuncHP(float x, Double_t* par)
{
  Double_t PDF =0.0;
  PDF = 0.1*par[0]*exp(-(x/10)/par[1]);

  return PDF;
}



void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  PSL_Rec->Reset();

  for (int i=1; i<=200; i++)
  {
    for (int j=1; j<=6; j++)
    {
      PSL_Rec->SetBinContent(j, PSL_Rec->GetBinContent(j) + fitFunc(i-0.5, par)*Matrice->GetBinContent(j, i));
    }
  }

  Calcul_Chi2(PSL_Rec, Data);
  f = Chi2;
}


void fcnHP(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  PSL_Rec->Reset();

  for (int i=1; i<=100; i++)
  {
    for (int j=1; j<=6; j++)
    {
      PSL_Rec->SetBinContent(j, PSL_Rec->GetBinContent(j) + fitFuncHP(i-0.5, par)*MatriceHP->GetBinContent(j, i));
    }
  }

  Calcul_Chi2(PSL_Rec, Data);
  f = Chi2;
}



void FIT_MINUIT_E(float start_0, float step_0, float low_0, float up_0, float start_1, float step_1, float low_1, float up_1, bool HP)
{
  gStyle->SetOptStat(0);

  TMinuit *gMinuit = new TMinuit(2);  //initialize TMinuit with a maximum of 4 params
  if (HP == false)gMinuit->SetFCN(fcn);
  if (HP == true)gMinuit->SetFCN(fcnHP);

  Double_t arglist[10];
  Int_t ierflg = 0;

  arglist[0] = 1;
  gMinuit->SetPrintLevel(-1);
  gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

  // Set starting values and step sizes for parameters
  gMinuit->mnparm(0, "A", start_0, step_0, low_0, up_0, ierflg);
  gMinuit->mnparm(1, "E0", start_1, step_1, low_1, up_1, ierflg);

  // Now ready for minimization step
  arglist[0] = 500;
  arglist[1] = 1.;

  //  gMinuit->mnexcm("CALL FCN", arglist ,1,ierflg);
  gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);
  gMinuit->mnexcm("HESSE", arglist ,2,ierflg);

  // Print results
  Double_t amin,edm,errdef;
  Int_t nvpar,nparx,icstat;
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);

  h_e = (TH1D*)PSL_Rec->Clone("h_e");
  h_e->Draw();
  h_e->GetYaxis()->SetRangeUser(1, 50000);
  Data->Draw("PEsame");
  Data->SetLineColor(kBlack);
  h_e->SetLineColor(kRed);
  h_e->SetLineWidth(3);
  Data->SetLineWidth(3);
  h_e->GetXaxis()->SetTitle("IP number");
  h_e->GetYaxis()->SetTitle("PSL/mm^{2}");
  h_e->GetYaxis()->SetLabelSize(0.02);

  gMinuit->GetParameter(0, A, err_A);
  gMinuit->GetParameter(1, E0, err_E0);


  float Max = h_e->GetMaximum();

  TLatex *lData = new TLatex(4, 10000, "Data");
  lData->Draw();
  lData->SetTextSize(0.04);
  lData->SetTextColor(kBlack);

  TLatex *lFit = new TLatex(4, 1000, "Fit");
  lFit->Draw();
  lFit->SetTextSize(0.04);
  lFit->SetTextColor(kRed);


  // cout << "\n\n#######################################################" << endl;
  // cout << "################## RESULTS OF FIT #####################" << endl;
  // cout << "#######################################################" << endl;
  // cout << "\nN0 = " << A << " +- " << err_A << endl;
  // cout << "E0 = " << E0 << " +- " << err_E0 << " MeV" <<  endl;
  // cout << "Chi2 = " << Chi2 << endl;
  // cout << "\n\n" << endl;
}



void FIT_MINUIT_G(float start_0, float step_0, float low_0, float up_0, float start_1, float step_1, float low_1, float up_1, bool HP)
{
  gStyle->SetOptStat(0);

  TMinuit *gMinuit = new TMinuit(2);  //initialize TMinuit with a maximum of 4 params
  if (HP == false)gMinuit->SetFCN(fcn);
  if (HP == true)gMinuit->SetFCN(fcnHP);

  Double_t arglist[10];
  Int_t ierflg = 0;

  //gMinuit->SetPrintLevel(-1);
  gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

  // Set starting values and step sizes for parameters
  gMinuit->mnparm(0, "A", start_0, step_0, low_0, up_0, ierflg);
  gMinuit->mnparm(1, "E0", start_1, step_1, low_1, up_1, ierflg);

  //gMinuit->FixParameter(0);
  //gMinuit->FixParameter(1);

  // Now ready for minimization step
  arglist[0] = 500;
  arglist[1] = 1.;

  //  gMinuit->mnexcm("CALL FCN", arglist ,1,ierflg);
  gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);
  gMinuit->mnexcm("HESSE", arglist ,2,ierflg);

  // Print results
  Double_t amin,edm,errdef;
  Int_t nvpar,nparx,icstat;
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);

  h_g = (TH1D*)PSL_Rec->Clone("h_g");
  h_g->Draw();
  h_g->GetYaxis()->SetRangeUser(1, 50000);
  Data->Draw("PEsame");
  Data->SetLineColor(kBlack);
  h_g->SetLineColor(kRed);
  h_g->SetLineWidth(3);
  Data->SetLineWidth(3);
  h_g->GetXaxis()->SetTitle("IP number");
  h_g->GetYaxis()->SetTitle("PSL/mm^{2}");
  h_g->GetYaxis()->SetLabelSize(0.02);

  gMinuit->GetParameter(0, A, err_A);
  gMinuit->GetParameter(1, E0, err_E0);


  float Max = h_g->GetMaximum();

  TLatex *lData = new TLatex(4, 10000, "Data");
  lData->Draw();
  lData->SetTextSize(0.04);
  lData->SetTextColor(kBlack);

  TLatex *lFit = new TLatex(4, 1000, "Fit");
  lFit->Draw();
  lFit->SetTextSize(0.04);
  lFit->SetTextColor(kRed);


  // cout << "\n\n#######################################################" << endl;
  // cout << "################## RESULTS OF FIT #####################" << endl;
  // cout << "#######################################################" << endl;
  // cout << "\nN0 = " << A << " +- " << err_A << endl;
  // cout << "E0 = " << E0 << " +- " << err_E0 << " MeV" <<  endl;
  // cout << "Chi2 = " << Chi2 << endl;
  // cout << "\n\n" << endl;
}



void Programme_Test()
{
  IP[0] = 1374.23;
  IP[1] = 1242.29;
  IP[2] = 1047.96;
  IP[3] = 767.745;
  IP[4] = 565.226;
  IP[5] = 414.813;
  IP[6] = 144.842;

  cout << "Test program with gammas" << endl;
}

void Histo_DATA(float IP[])
{
  for (int i=0; i<7; i++)
  {
    Data->SetBinContent(i+1, IP[i]);
  }
}


void Draw_Incident_Spectrum_Fit(float A, float E, float solid_angle, int flag)
{

  string seN, seNN;
  
  A = A/solid_angle;
  err_A = err_A/solid_angle;
  float test = -E*log(1/A);
  //cout << "test = " << test << endl;
  f1 = new TF1("f1", "[0]*exp(-x/[1])", 0, 1.5*test);
  f1->SetParameter(0, A);
  f1->SetParameter(1, E);
  f1->SetNpx(200);


  f1->Draw("");
  f1->SetLineColor(kBlack);
  f1->SetLineWidth(3);
  f1->SetMinimum(1);
  float Max = f1->GetMaximum();
  N = f1->Integral(0, 200);
  eN = (N*(err_E0/E0 + err_A/A));

  if (flag ==0)
    {
      seN = Form("+-  %g e-/(MeV.sr)", err_A);
      seNN = Form("+-  %g e-/sr", eN);
      cout << "N e- [ >10MeV] = " << f1->Integral(10,200) << endl;
    }
  
  if (flag ==1)
    {
      seN = Form("+-  %g #gamma/(MeV.sr)", err_A);
      seNN = Form("+-  %g #gamma/sr", eN);
      cout << "N gammas [ >10MeV] = " << f1->Integral(10,200) << " +- " << f1->Integral(10,200)*(err_E0/E0+err_A/A) <<  endl;
    }
  
  
  // string sN = Form("No =  %g ", A);
  // TLatex *lN = new TLatex(20,0.01*Max, sN.c_str());
  // lN->Draw();
  // lN->SetTextSize(0.035);
  // lN->SetTextColor(kRed);

  // TLatex *leN = new TLatex(105,0.01*Max, seN.c_str());
  // leN->Draw();
  // leN->SetTextSize(0.035);
  // leN->SetTextColor(kRed);

  string sE = Form("Eo =  %g ", E0);
  TLatex *lE = new TLatex(test/2.5,0.001*Max, sE.c_str());
  lE->Draw();
  lE->SetTextSize(0.035);
  lE->SetTextColor(kRed);

  string seE = Form("+-  %g MeV", err_E0);
  TLatex *leE = new TLatex(test,0.001*Max, seE.c_str());
  leE->Draw();
  leE->SetTextSize(0.035);
  leE->SetTextColor(kRed);

  string sNN = Form("N =  %g ", N);
  TLatex *lNN = new TLatex(test/2.5,0.0001*Max, sNN.c_str());
  lNN->Draw();
  lNN->SetTextSize(0.035);
  lNN->SetTextColor(kRed);

  TLatex *leNN = new TLatex(test,0.0001*Max, seNN.c_str());
  leNN->Draw();
  leNN->SetTextSize(0.035);
  leNN->SetTextColor(kRed);

  string sChi = Form("Chi2 =  %g ", Chi2);
  TLatex *lChi = new TLatex(test,0.00001*Max, sChi.c_str());
  lChi->Draw();
  lChi->SetTextSize(0.035);
  lChi->SetTextColor(kRed);

  f1->GetYaxis()->SetTitle("dN/dE [MeV^{-1} sr^{-1}]");
  f1->GetXaxis()->SetTitle("Energy [MeV]");


}



void Lecture_analyse_file(const char* filename)
{
  ifstream file(filename);
  string junk1, junk2, junk3;
  
  for (int i=0; i<=7; i++)
    {
      if (i==0)
	{
	  file >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 ;
	  //cout << "junk = " << junk1 << endl;
	}
      if (i >0)
	{
	  file >> junk2 >> junk2 >> junk2 >> junk2 >> junk2 >> junk2 >> junk2 >> junk2 >> junk2 >> IP[i-1] >> junk3 >> junk3;
	  //cout << "junk2 = " << junk2 << endl;
	  cout << "IP[" << i-1<< "] = " << IP[i-1] << endl;
	}
    }
  
}



void Routine_Analyse(const char* filename, const char* name, float Coef_PSL, float solid_angle, double Surface)
{
  
  cout << "\n\nfilename = " << filename << endl;
  cout << "PSL Coef = " << Coef_PSL << endl;
  cout << "Solid angle = " << solid_angle << endl;
  cout << "Surface = " << Surface << endl;

  Init_IP();
  Lecture_analyse_file(filename);
  //cout << "\n\n1/ Measurement with electrons [1] or only with gammas [0] ?" << endl;
  //cin >> flag_electron;
  //if(flag_electron ==0) cout << "Measurement only with gammas !!!!" << endl;
  //if(flag_electron ==1) cout << "Measurement with electrons !!!!" << endl;
  //if(flag_electron >1) Programme_Test();

  //if(flag_electron <=1)
  //{
    //    cout << "\n\n2/ Enter the PSL coefficient [PSL/MeV] (default is 6.95E-1) :" << endl;
    //cin >> Coef_PSL;

    // cout << "\n\nEnter the solid angle :" << endl;
    // cin >> solid_angle;

    // cout << "Enter the number of PSL/mm² in IP number 1 :" << endl;
    // cin >> IP[0];

    // cout << "Enter the number of PSL/mm² in IP number 2 :" << endl;
    // cin >> IP[1];

    // cout << "Enter the number of PSL/mm² in IP number 3 :" << endl;
    // cin >> IP[2];

    // cout << "Enter the number of PSL/mm² in IP number 4 :" << endl;
    // cin >> IP[3];

    // cout << "Enter the number of PSL/mm² in IP number 5 :" << endl;
    // cin >> IP[4];

    // cout << "Enter the number of PSL/mm² in IP number 6 :" << endl;
    // cin >> IP[5];

    // cout << "Enter the number of PSL/mm² in IP number 7 :" << endl;
    // cin >> IP[6];

    // //}


  float start_0 = 1e9;
  float step_0 = 1e8;
  float low_0 = 1e6;
  float up_0 = 1e15;
  
  float start_1 = 10;//10
  float step_1 = 0.1;
  float low_1 = 0; //-1
  float up_1 = 30; //30

  //MATRICE GAMMA PART

  DefineMatrice(Coef_PSL, Surface);
  DefineMatriceHP(Coef_PSL, Surface);

  Create_Pad_Canvas("RESULTS GAMMA");
  Histo_DATA(IP);
  pad1->cd();
  pad1->SetLogy();
  FIT_MINUIT_G(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
  Chi2_gamma_store=Chi2;
  if (E0 <=1.5)
    {
      HP=true;
      FIT_MINUIT_G(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
      Chi2_gamma_HP_store=Chi2;
    }

  pad2->cd();
  pad2->SetLogy();
  Draw_Incident_Spectrum_Fit(A, E0, solid_angle, 1);

  //char pngname1[100], pngname2[100];

  string fname = name;
  string part = "_Gamma.png";
  string pngname1 = fname+part;
  //cout << "png name = " << pngname1 << endl;

  c->SaveAs(pngname1.c_str());


  //ELECTRONS GAMMA PART

  Create_Pad_Canvas("RESULTS ELECTRONS");
  pad1->cd();
  pad1->SetLogy();
  DefineMatriceElectron(Coef_PSL, Surface);
  DefineMatriceHPElectron(Coef_PSL, Surface);

  HP=false;
  FIT_MINUIT_E(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
  Chi2_store=Chi2;
  HP=true;
  FIT_MINUIT_E(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
  Chi2_HP_store=Chi2;
  FIT_MINUIT_E(start_0, step_0, low_0, up_0, 0.5, step_1, low_1, 1., HP);
  Chi2_HPbis_store=Chi2;

  if(Chi2_store < Chi2_HP_store && Chi2_store < Chi2_HPbis_store)
    {
      HP=false;
      FIT_MINUIT_E(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
    }
  
  if(Chi2_HP_store < Chi2_store && Chi2_HP_store < Chi2_HPbis_store) FIT_MINUIT_E(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
  if(Chi2_HPbis_store < Chi2_store && Chi2_HPbis_store < Chi2_HP_store) FIT_MINUIT_E(start_0, step_0, low_0, up_0, 0.5, step_1, low_1, 1.5, HP);


  pad2->cd();
  pad2->SetLogy();
  Draw_Incident_Spectrum_Fit(A, E0, solid_angle, 0);

  part = "_Electron.png";
  string pngname2 = fname+part;
  //cout << "png name = " << pngname2 << endl;

  c->SaveAs(pngname2.c_str());
  

  cout << "\nGAMMA RESULTS : " << endl;
  cout << "Chi2 gen = " << Chi2_gamma_store << endl;
  cout << "Chi2 HP = " << Chi2_gamma_HP_store << endl;

  cout << "\nELECTRONS RESULTS : " << endl;
  cout << "Chi2 gen = " << Chi2_store << endl;
  cout << "Chi2 HP = " << Chi2_HP_store << endl;
  cout << "Chi2 HP réduit = " << Chi2_HPbis_store << endl;

}










void Analyse()
{

  Init_IP();
  
  // cout << "\n\n1/ Measurement with electrons [1] or only with gammas [0] ?" << endl;
  // cin >> flag_electron;
  // if(flag_electron ==0) cout << "Measurement only with gammas !!!!" << endl;
  // if(flag_electron ==1) cout << "Measurement with electrons !!!!" << endl;
  // if(flag_electron >1)

  
  // if(flag_electron <=1)
  //   {
    cout << "\n\n2/ Enter the PSL coefficient [PSL/MeV] (default is 6.95E-1) :" << endl;
    cin >> Coef_PSL;

    cout << "\n\nEnter the solid angle :" << endl;
    cin >> solid_angle;

    //Programme_Test();

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

    //  }


  float start_0 = 1e8;
  float step_0 = 1e7;
  float low_0 = 1e6;
  float up_0 = 1e13;
  
  float start_1 = 10;//10
  float step_1 = 0.1;
  float low_1 = 0; //-1
  float up_1 = 30; //30

  //MATRICE GAMMA PART

  DefineMatrice(Coef_PSL, Surface);
  DefineMatriceHP(Coef_PSL, Surface);

  Create_Pad_Canvas("RESULTS GAMMA");
  Histo_DATA(IP);
  pad1->cd();
  pad1->SetLogy();
  FIT_MINUIT_G(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
  Chi2_gamma_store=Chi2;
  if (E0 <=1.5)
    {
      HP=true;
      FIT_MINUIT_G(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
      Chi2_gamma_HP_store=Chi2;
    }

  pad2->cd();
  pad2->SetLogy();
  Draw_Incident_Spectrum_Fit(A, E0, solid_angle, 1);


  //ELECTRONS GAMMA PART

  Create_Pad_Canvas("RESULTS ELECTRONS");
  pad1->cd();
  pad1->SetLogy();
  DefineMatriceElectron(Coef_PSL, Surface);
  DefineMatriceHPElectron(Coef_PSL, Surface);

  HP=false;
  FIT_MINUIT_E(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
  Chi2_store=Chi2;
  HP=true;
  FIT_MINUIT_E(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
  Chi2_HP_store=Chi2;
  FIT_MINUIT_E(start_0, step_0, low_0, up_0, 0.5, step_1, low_1, 1., HP);
  Chi2_HPbis_store=Chi2;

  if(Chi2_store < Chi2_HP_store && Chi2_store < Chi2_HPbis_store)
    {
      HP=false;
      FIT_MINUIT_E(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
    }
  
  if(Chi2_HP_store < Chi2_store && Chi2_HP_store < Chi2_HPbis_store) FIT_MINUIT_E(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1, HP);
  if(Chi2_HPbis_store < Chi2_store && Chi2_HPbis_store < Chi2_HP_store) FIT_MINUIT_E(start_0, step_0, low_0, up_0, 0.5, step_1, low_1, 1.5, HP);


  pad2->cd();
  pad2->SetLogy();
  Draw_Incident_Spectrum_Fit(A, E0, solid_angle, 0);


  cout << "\nGAMMA RESULTS : " << endl;
  cout << "Chi2 gen = " << Chi2_gamma_store << endl;
  cout << "Chi2 HP = " << Chi2_gamma_HP_store << endl;

  cout << "\nELECTRONS RESULTS : " << endl;
  cout << "Chi2 gen = " << Chi2_store << endl;
  cout << "Chi2 HP = " << Chi2_HP_store << endl;
  cout << "Chi2 HP réduit = " << Chi2_HPbis_store << endl;

}
