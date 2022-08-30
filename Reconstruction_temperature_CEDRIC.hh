TH1D* PSL_REF;
TH1D* Edep_REF;
TH1D* h;
TFile* file;
TH2F* Matrice = new TH2F("matrice", "matrice", 7, 0.5, 7.5, 200, 0, 200);
TH2F* MatriceHP = new TH2F("matriceHP", "matriceHP", 7, 0.5, 7.5, 100, 0, 10);
TH1D* PSL_Rec = new TH1D ("PSL_Rec", "PSL_Rec", 7, 0.5, 7.5);
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
bool HP=false;
float IP[7];
TPad *pad1;
TPad *pad2;
TCanvas* c;
TF1* f1;



void Create_Pad_Canvas()
{
  gStyle->SetOptTitle(kFALSE);
  c = new TCanvas("RESULTS", "RESULTS", 0, 10, 1600, 700);
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


void DefineMatrice(double coef_PSL)
{
  TFile* f_Matrice = new TFile("CEDRIC_Matrice_gamma.root");
  Matrice = (TH2F*)f_Matrice->Get("matrice");
  Matrice->Scale(Coef_PSL/(3.1415927*7*7));
}

void DefineMatriceHP(double coef_PSL)
{
  TFile* f_MatriceHP = new TFile("CEDRIC_MatriceHP_gamma.root");
  MatriceHP = (TH2F*)f_MatriceHP->Get("matriceHP");
  MatriceHP->Scale(Coef_PSL/(3.1415927*7*7));
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

  for (int i=1; i<=n; i++)
    {
      sigma = C->GetBinError(i);
      
      if(C->GetBinContent(i) !=0 && sigma !=0)
	{
	  Chi2+= ((O->GetBinContent(i) - C->GetBinContent(i)) * (O->GetBinContent(i) - C->GetBinContent(i))) / (C->GetBinContent(i) + (sigma*sigma));

	}
    }
}


Double_t fitFunc(float x, Double_t* par)
{
  Double_t PDF =0.0;
  PDF = exp(par[0]-(x/1)/par[1]);

  return PDF;
}


Double_t fitFuncHP(float x, Double_t* par)
{
  Double_t PDF =0.0;
  PDF = exp(par[0]-(x/10)/par[1]);
  
  return PDF;
}



void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  PSL_Rec->Reset();
  
  for (int i=1; i<=200; i++)
    {
      for (int j=1; j<=7; j++)
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
      for (int j=1; j<=7; j++)
	{
	  PSL_Rec->SetBinContent(j, PSL_Rec->GetBinContent(j) + fitFuncHP(i-0.5, par)*MatriceHP->GetBinContent(j, i));
	}
    }

  Calcul_Chi2(PSL_Rec, Data);
  f = Chi2;
}



void FIT_MINUIT(float start_0, float step_0, float low_0, float up_0, float start_1, float step_1, float low_1, float up_1, bool HP)
{
  gStyle->SetOptStat(0);
  
  TMinuit *gMinuit = new TMinuit(2);  //initialize TMinuit with a maximum of 4 params
  if (HP == false)gMinuit->SetFCN(fcn);
  if (HP == true)gMinuit->SetFCN(fcnHP);

  Double_t arglist[10];
  Int_t ierflg = 0;
  
  arglist[0] = 1;
  gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);
  
  // Set starting values and step sizes for parameters
  gMinuit->mnparm(0, "A", start_0, step_0, low_0, up_0, ierflg);
  gMinuit->mnparm(1, "E0", start_1, step_1, low_1, up_1, ierflg);
  
  // Now ready for minimization step
  arglist[0] = 500;
  arglist[1] = 1.;

  //  gMinuit->mnexcm("CALL FCN", arglist ,1,ierflg);
  gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);
  
  // Print results
  Double_t amin,edm,errdef;
  Int_t nvpar,nparx,icstat;
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);

  PSL_Rec->Draw();
  Data->Draw("PEsame");
  Data->SetLineColor(kBlack);
  PSL_Rec->SetLineColor(kRed);
  PSL_Rec->SetLineWidth(3);
  Data->SetLineWidth(3);
  PSL_Rec->GetXaxis()->SetTitle("IP number");
  PSL_Rec->GetYaxis()->SetTitle("PSL/mm2");
  PSL_Rec->GetYaxis()->SetLabelSize(0.02);

  gMinuit->GetParameter(0, A, err_A);
  gMinuit->GetParameter(1, E0, err_E0);

  float Max = PSL_Rec->GetMaximum();

  TLatex *lData = new TLatex(4,0.8*Max, "Data");
  lData->Draw();
  lData->SetTextSize(0.04);
  lData->SetTextColor(kBlack);

  TLatex *lFit = new TLatex(4,0.7*Max, "Fit");
  lFit->Draw();
  lFit->SetTextSize(0.04);
  lFit->SetTextColor(kRed);

  cout << "\n\n#######################################################" << endl;
  cout << "################## RESULTS OF FIT #####################" << endl;
  cout << "#######################################################" << endl;
  cout << "\nN0 = " << exp(A) << " +- " << exp(A+err_A)-exp(A) << endl;
  cout << "E0 = " << E0 << " +- " << err_E0 << " MeV" <<  endl;
  cout << "\n\n" << endl;
}


void Histo_DATA(float IP[])
{
  for (int i=0; i<7; i++)
    {
      Data->SetBinContent(i+1, IP[i]);
    }
}


void Draw_Incident_Gamma_Spectrum_Fit(float A, float E)
{
  f1 = new TF1("f1", "exp([0]-x/[1])", 0, 200);
  f1->SetParameter(0, A);
  f1->SetParameter(1, E);

  f1->Draw("");
  f1->SetLineColor(kBlack);
  f1->SetLineWidth(3);
  f1->SetMinimum(1);
  float Max = f1->GetMaximum();

  string sN = Form("No =  %g ", exp(A));
  TLatex *lN = new TLatex(30,0.1*Max, sN.c_str());
  lN->Draw();
  lN->SetTextSize(0.04);
  lN->SetTextColor(kRed);

  string seN = Form("+-  %g ", exp(A+err_A)-exp(A));
  TLatex *leN = new TLatex(115,0.1*Max, seN.c_str());
  leN->Draw();
  leN->SetTextSize(0.04);
  leN->SetTextColor(kRed);

  string sE = Form("Eo =  %g ", E0);
  TLatex *lE = new TLatex(30,0.01*Max, sE.c_str());
  lE->Draw();
  lE->SetTextSize(0.04);
  lE->SetTextColor(kRed);

  string seE = Form("+-  %g MeV", err_E0);
  TLatex *leE = new TLatex(95,0.01*Max, seE.c_str());
  leE->Draw();
  leE->SetTextSize(0.04);
  leE->SetTextColor(kRed);

  f1->GetYaxis()->SetTitle("N");
  f1->GetXaxis()->SetTitle("#gamma incident energy on CEDRIC [MeV]");


}
