const int n=7;
float PSL[n];

void Lecture_analyse_file(const char* filename)
{
  ifstream file(filename);
  string junk1, junk2, junk3;
  
  for (int i=0; i<=n; i++)
    {
      if (i==0)
	{
	  file >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 >> junk1 ;
	  cout << "junk = " << junk1 << endl;
	}
      if (i >0)
	{
	  file >> junk2 >> junk2 >> junk2 >> junk2 >> junk2 >> junk2 >> junk2 >> junk2 >> junk2 >> PSL[i-1] >> junk3 >> junk3;
	  cout << "junk2 = " << junk2 << endl;
	  cout << "PSL = " << PSL[i-1] << endl;
	}
    }
  
}
