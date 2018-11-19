#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

const string RNACT = "AAA KAAC NAAG KAAU NACA TACC TACG TACU TAGA RAGC SAGG RAGU SAUA IAUC IAUG MAUU ICAA QCAC HCAG QCAU HCCA PCCC PCCG PCCU PCGA RCGC RCGG RCGU RCUA LCUC LCUG LCUU LGAA EGAC DGAG EGAU DGCA AGCC AGCG AGCU AGGA GGGC GGGG GGGU GGUA VGUC VGUG VGUU VUAA  UAC YUAG  UAU YUCA SUCC SUCG SUCU SUGA  UGC CUGG WUGU CUUA LUUC FUUG LUUU F";
const string TS = "G 057 A 071 S 087 P 097 V 099 T 101 C 103 I 113 L 113 N 114 D 115 K 128 Q 128 E 129 M 131 H 137 F 147 R 156 Y 163 W 186";
const int MASS[] = {57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186};

string ReverseComplement(string str)
{
	string res = "";

	for (int i = str.length() - 1; i > -1; i--)
	{
		if (str[i] == 'U')
			res += 'A';
		else if (str[i] == 'C')
			res += 'G';
		else if (str[i] == 'G')
			res += 'C';
		else if (str[i] == 'A')
			res += 'U';
	}	

	return res;
}

string ProteinTranslation(string str)
{
	int i = 0;
	string res, aminoacid, codon = str.substr(i, 3)+' ';
	aminoacid = RNACT[RNACT.find(codon) + 4];
	while (aminoacid != " " && i<str.length()-2)
	{
		res += aminoacid;
		i += 3;
		codon = str.substr(i, 3)+' ';
		aminoacid = RNACT[RNACT.find(codon) + 4];
	}
	return res;
}

void PeptideEncoding(string str, string aminoacid)
{
	string temp;
	int size = aminoacid.length() * 3;
	for (int i = 0; i < str.length()-size+1; i++)
	{
		temp = str.substr(i, size);
		
		while (temp.find('T')!=temp.npos)
			temp[temp.find('T')]= 'U';
		
		if (aminoacid == ProteinTranslation(temp) || ProteinTranslation(ReverseComplement(temp)) == aminoacid)
		{
			while (temp.find('U') != temp.npos)
				temp[temp.find('U')] = 'T';

			cout << temp << endl;
		}
	}
}

long long int SubpeptidesCount(int n)
{
	return n*(n - 1);
}

void GeneratingTheoreticalSpectrum(string str)
{
	int sizeres = str.length()*(str.length() - 1) + 2;
	int *res = new int[sizeres];
	string str2 = str + str;	

	for (int i = 0; i < sizeres; i++)
		res[i] = 0;
	
	for (int i=0; i < str.length(); i++)
		res[1]+= stoi(TS.substr(TS.find(str[i]) + 2, 3));

	int j = 2, m;

	for (int i = 0; i < str.length(); i++) 
	for (int k = 1; k < str.length(); k++)  
	{
		m = k;
		while (m > 0)
		{			
			res[j] += stoi(TS.substr(TS.find(str2[i + m - 1]) + 2, 3));
			m--;
		}
		j++;
	}
	sort(res, res + sizeres);

	for (int i = 0; i < sizeres; i++)
		cout<<res[i]<<' ';
}

long long int CountingPeptidesWithGivenMass(int n)
{
	map<int, long long int> mas;	

	mas[0] = 1;

	for (int i = 57; i < n + 1; i++)
	{
		for (int j = 0; j < 18; j++)
			if (mas[i - MASS[j]] > 0)
				mas[i] += mas[i - MASS[j]];
	}
	
	return mas[n];
}

int main()
{
	//string str= "AUGGCCAUGGCGCCCAGAACUGAGAUCAAUAGUACCCGUAUUAACGGGUGA";
	//cin >> str;
	//cout << ProteinTranslation(str)<<endl;

	//string str="CAGATTATTTGATTTACCCGCGGAAGGCGCTTTTAGAGTCAAGACTTATGTGTGAATTCTCGGTATTCTAGCCTGCACGACCCATGTGCCGCTAGAATTATAGTCTTTGCAGGCCCGGATAATCTGGATGAAGTTCATTCGTAAGTGGGCATGGCTCTCGAACCGTATTGAATCTTTAAGGGCTGATGACAGATTTCTTATTGCCTTATCCTCAGAGGCAAAGGGACTTAAAGCTCCACAATGCTGTAGACGATTAATAGCCGTGGGTAATCCCTTAAGTAGTCTCAACGGTACTGGACTCCCCGCAGGCCCACCCTATGGCAGTCGCCTGTCAGGAGAGCTTTGGTAGTACTAAATGGCTCCAGCGCCAGACGGCTAATCCCGCGAGCCATTCGAATACAGCTGGACTGACCGTTCGCGCTAAATCGAAATACCAATAGCTATACGATAGTCTGAGTATGTAGATGGCTCACTTAGCCGGCCGCGCCAGGCGGATAGGATCGCCGTGACTGGCGATTAGATGCTACAAGGTCGCGGGCCCCTGAACAGCCAGGACTTGAGGCGCAGGTCTCCCAGGGCCAAGACCATTTGGAGCTTACGGATGAAGGCAAGTGCAAAAGATGCAGCGTAATGTCACTGGCCTTCCCAACTCTCAGCCACTAATTGCTCTGCTCCAGTTTTCTACTGATTCATTCCTTCAGAGAACTAGACATCAGACAACCTTCATTGGAGTCCTAGTCACCGAAGTCGAGAGTACAGACTGTAATGGTCGGAACCCCAAGGATCTGATGATTGACTCAGCAGGCTGCTCAGTGGGCAGCTGCCAGCATTGCTACCCCTATTTTATGCGTCTCGAAGTGATCCTGCGCTAATGAAAACATCGATAATTGCATGGCGCTATCAAGTTATGTCTTGGGGTATAGCCCAACGAGAGACCCGAGTGATTCGTCCTGAAGTGATGTGGTTTGTAATTTTAAAGATCCGCCCTATCTTGCCAGCAGCCCAACATCAATAGGGGTTCTGTCGGTACGAATACCGGTGAGAGGGACCTTGCCTGGCGAGAGACCGGCGGGGCGTAGGAAAAACTCTATATGCATATAAACAGCCCCCTATGCTAGTCCTACTGAAGTCCCGGTATTAGCCCCGCTATGCGGGACCTCGGATCTCAAGGTGCGAAAGCGCCACGGGACAGAAGACGCATGTTCTTATTGCCCCAAAAACGTCCGATTGATTTTGTCACTGGGTGGGGTTTTTACATATTATTTGGTGTTGTCAAGCCGTGGGAACACCGCATATACGGGGATACGGAGTGAAGGGATAGGAATGTATCTCAATTTAACTGGTTAAAGTTTCGTCTTTGTATTAACCTAAAGCCTTTGTGAGGAAGTGTCTGTGGGCCCCCTCGGACAGACAATCATCTAAGCCCAGAGTCCTATCTTTGCAGATAAGGAGTCCCTCAGGCGTGCGTATAGATAAACAGGCGTTGTAAACCGTCCCCGCCGATGCATACTATACGGTACCGCTTGGTTACCACCCGACAGCCGCGTAGTCACCAAGCGGTATCGTCTAGCCTGCAGCACATATGCCAAATCGGGAGGCTTAAGTATAATGTGGAAGCCGCACGACCCTGGGTGCGTGCATGGGCCTAGCCTCCGTCGGGTGTACCATGTTCCCCCCAATTCCCATAGCACCACATATCGCATCCAGATGACTCTGTATGCAATTTCGCAAGTGCGGGATGAAGAGATACCCGCAGTTACTGTTTCAGGGCTCTGGTTGGTGTTACAATTGGAGGGGGGTCACTTCGTCTACTGGGGTCTCAGGGCACGGCTGTTTCCTGGCTCTGGGTATCCTACTAGGATTTGCGAACAGGAACATACGCGGATGCCGGGTTGTCACTAAAAGGTACCGAACCTTGACCCTGCGACGGGTGGCTGCAGGGTGGTAACCAAGAGGTACAGAAAAAGGCCGCCGATTGGTCACATTAGTCTTCCATTGGCGCGTCAAGTGCATAGTAGATTGGAGACATGTTGCGTCAAATAGATTACAGTTTTTGGGTGCAATAAGACGAGCAGCGTATGCTTGTGATGTTCCAGAGTGCTGCTTGAAAAAGACTATGGGATCAGACTCAGGCCGCCCCTATGACAGTGGTGAACCCTTAGTAAGAGCTATATTAAAAGGATTAACAGGGGGAGTCCACAAATTTTAAAGGCTAACAGCCCCCACCATCTGGAGCACTCTATTGGCAGGCACGTCTCTATTGTAAGAAGATCCGCACCGCAGAGTCTATTGGGGGATACCCCTAGTCCTGCTACGCGACAGTGAGAACTGTGCGCAGGCTGACGGGCGCGAAGTAACGACAATCTCCTACGGGACTATAGGGTCCCTGATAGCACTGATACTCGTACCCGAGGGCATCCCTTATTGGTATCAATTAGACCTATTCCCTTCTGGATCGTCGGTCGATACGTAACGTTAAACTCGCAAAGCCGGGCCCGCGTAAAGCAAGGATTGGGCTTAATCTTGCATTGGTTTTGCTTTGGAGGGTAGTTGATAAAATTTATGACCCGTAGATTTCGCCTTCCATTGGCACCGCGAGCATAGATACCCGTCATACTTAGAACCCAAGGTAGTGCATTCAGGCTGTAGTGGGTCGCCATCACCGATGGCTATATAAACTGGCGGAAAGGATCTCATGCCCTCACCATTGCTCAACCACCCCACATTGGGTGACATTCCTATAACTATTCAGCTCGAGATAGATCATTGTAATGGACGTGGGATACATCATCTGACTGTTGAGGCAATGAGCGTGTACACTTGGAGCCGACTTCATGAATAGAGTGCAGACAGTCGGTCGACTGTACCTTAATTAAGTGGTGCGTAATCTCCAATCAACTAGGCTGGCGAGTGGGTCAATTTGATGTGTTATCGGGTTCCGACCACTATTACCCTGTGGCGTTGGGACTCCTGTAACACAGAGCATCGGTACGCCGACGTGCAAGTGGTGCATCGCTCTTATACAAGTGCCGCCGTGGTGGGATCCGAATTGGTCATAAAAAAGTCTGCGACAAGTCACGGCCGTATACTATCCCACATGTGCCGCCCGGCACTAGCATAGTTATTGCCCGAGGAACGAGTACATTCTCTCGCTAGAGGTATCACGTTGGACCAGCATGTTCCGTCAGATATATCTCGGGTCGGGCTGTCACCAGCTCTATAAAAAAGCGTCCAGTGTGAGACCCGACAGCCCCCGCGCTTAATACGAAAAATAGTATAGTTCACCAACAATCAATGGTTAGTATCGTTTTCAGAAACAGCCGAAATAAATGCGTACAGTCAATAAGACTCAGCCCGGTAACACTAGTCGAATGCAGACTCTGCATTGTTGATTGTCAGATTTTGAGCCCTGGGAGGTGACATGCAAAACGCGATCGGCAGGTTCGCCTATTTCGGTTCTGTAGATGGGCCTACTTTTATATAGCTTGTTTGGACTACCACCTGCGACATAAAATCAGCGTCAGCTAACGACGTGTTTGACGGGGAGGTTCATTGCAGACCCAGCATGCCGCCCGGCGTCCGCGGCTGTCGCGTAGTAACTAAAAGATATAGGTAGTGACGCGTGACGCCGCGCCCACACTAGAAACATCTTACGCAGCGTAGGGCGGCCCACTTAGGAGCCGCACCTGGGAGTCCAGATCTTTAATACCCGAGATCGAACATACCATAGGTTCGGCATGCGTATCAGCTCACGCCAGTCGCGCCATGGTTTCGCAGCCTTCAAGCATCATAGGGAGAAGGAGAGGATAACTAATCCTGCCGACCCGAATTCTCCACTTCCTGTACCTCTTTGTCACAACCCTACAACCTGTAAACCACGAGACGGGATAAGTGCAACCCTCCGAAGTGTCTTCCGGTTCGGGAGAATGCCAAATTACGCCCAACTCCTGTCAGGGCCGGACATTCATAAAAATGACCTTGAGTTATAGCAGGAATTGCGTGGTACACCTGTTCATCCGTAACCCAATACCTTGGCTGCCGGGTAGTTACCAAGCGTTATCGATAAGGGAGGGATCTAACTTGCTTGGTAGAGGCTATTTCGTGAGAAGGTAAAGGGACCCTCTAGATTGGACTGTAGACTCCACCAACGGAGGCACTCAACTATATTCTAAATCCCGTTTACCTACATGTACCGTTCCCGACGGTGTACAATAAATCCTTGAGCAGATCTTGGGTTGTAACAATCAGAGGTGCAATGAATTATTTTTTCCTTGAATAAAATCCGAGCGTGTTGTTTTGGCCTACCAGCACAATTAAGCGGCTGTCGCGTAGTGACTAAGCGATATCGCCTCCAGACAATGTATGAATAATCAGTAGGGGTGCCGCGGGCTGGTCGTTCGACGTGGTCCATATTTAAAGTCCTGGACTACGGGAAATTCGAGCCTATTTCCCGTAGTAAATTGGCCGTCTACGTCACCTTGAAGGCTGTCGTGTAGTTACGAAGAGATACCGCGGCCCTAACAGGTCTCGTTGGTCTCCGGGACAGCGCCGGCGCTGCAATATATCTGCTCTAAGGCGAGCCGGCTGTAGGGTAGTTACCAAAAGATATCGTGGTTCCCTTAGGGTGTTGCGGCATTCTCTGAATCATAGAGGGTAGGGCCGCCCCCAGCAGGTCTTAAAGCCAGCCTGTCCCCCACAACTTCGCTCACGCAACTACATCCGACGAAGATATATCCTAACTAGCCTTGCTCAACTGAAGTAAATAATCGAAAGTCGGCCTAATCGTCCCATTTCTTACTTAGCACCTCTCAGCAGACCGTATCTGTTTGTTATGTTACTCTCCGCACGTCTAATGCTGGGAAGTCCATAGCATTAGAAGGACCGGCGCCGCATAAACACCGTCGAGCTACATTTTTTACTTTGCTTAAACGAATCCAAGGCTGGCGAACCGACAACCTCCTGTAATTTACCAACAATATTTGCTTCTCATGTCGGACCTTAGACAATTAACGAGGGGTCGCTGTGATGTATATCCACAGCCTCGAGTGTATCACCTGTCGAACTGTGATTACTCGTTGCGGAACTCACGCGTGGCCGCTTACGGATCGGTCCTCCAACCTAGCAGTCCGTTGTTCAAACAAGTTAGTGCAGCCTCCCAATCAGGGTGACTGGATTCTCTTGGCTACCGTATGATTCGCGTCTGCCACTAGGGTTAACAAAGGGCGACATGTCCCGGTGGGTGATACGTATCACCGAACCCTACCCCTCGCGTTAGCGGCTGCAGGGTAGTCACTAAGCGATATAGGGTTGAGGCACAGGCGACGCCTCTACCTCCATCCATCAGAGGGCATCCAGCTACACACTCGGCGTATGACGTCCCGGACGGGGTACAAAACGACGGTTGCGCCCTTGACTGTTCTCTTGTGCATGCGGAAATCTCAGTGGTCACCGAGGCCCCCTCCCGGAATAGAATGAGTGTGCAGGGGTCGCGGCCAGATGGGGCGCTCATTTTCACACTAGCACATTTAGTCGAGCCGCACACGCAAATTCCGGCGGTATAAGCGTGTTACTTCGGGTTATAGGATGCTTGATGCTGACTCCGCGGTTTCGAAAACGCGCCCCATAACATTCTGGTTCCAAGCGAACCTCTCCTGCGCCTGGGGTAGCCCCATGAGGGGCCGGTTCCTGAAATGGGATAGTACATCCCAGTCGGAAGGGTACCGTTGTGTGGGACCTACAAACCCAGAAACGTACTCAATGGCGCTCCTACGTGCTCACCGCTAAGCATTACCGCAATCTTGCTAAAGTTATTAGGGTCTAAATGAAATGCAATGAGGGTTGGTTCTGGCAAAGAAGACCGCCGTGCGCCGACAGGGATATTGAGAGCCTTCGGGACCCCCTACATAGTATTTGTGAGCGCACTTGTATCGTCAATTAGGAATGACTCCATTTCTCGGAAATCCGGGTATCTGCCATCAATCGGTCTGATGCACTGATGGTGGGAAAATTTCTCTGTTCTTAACGCTGACAGCATGTTTCGTGGGGTCCATTCTAAGCTTATAGCTTTGAACATGACATACGCCGTATGCCGTGCTTGTCTACAGGGCACGCGCAGGTCGGACTACACCCAGGAGGCCGTCGCTACTGGATGCCGGGTAGTAACAAAAAGATATAGAATGTTCCATCAGGAGCGATACCATCTGACCGTTCCCAGACACGACCACCGGGACTCGGGCTTCTGTACTCGCTTAGGGAGGGCGAGCGAGAACCATTCCGGGTGATAGAGTATCTATACCGCTTCGTAACGACGCGGCAGCCACGTGGTGTTATGCTCTGCTTATACATACACGTCGCATTACCTAAGACGACTACTGGGTTTGATAGAGGAATCACAACGGATTCGACATGTCCTAAAGGCGTTAAAGAGGTCTAGGCGCTACTGAACTTGGCCTTGTGTCCTGTACCGTTTCGTGACTACCCTACAGCCACGATAAGGTGTGTGGCGGCGGTTGTAGGGTTGTTACCAAACGTTATCGGCCATACTTGTCGCAGCGCACAGACTCAAGTGCGTTCTACTGCAACTAACTGCTTCTACTACGTCGAGGGTGTAGGAATTTCAGTGGCCCCAGTAGTAACACTCCCGCGTGGAGCATCTAGACGTCCCGCGGTCCAATTGCCACAGTCGGTGATTCGGATGTCGTGTAGTAACGAAAAGGTATCGCCAGTGCTGTTAGTTCCGTCTCTCTTCACCCCACATCTGTACGGAACTCCGTTTTTAAGGCAACTGGAACCATCTAGGAGTAGTGTGGGCTAGACGTCCTTTACTGAATAATTTATGCGCTATGGTTTGGGCGGTTCCATTGAAACTACCTCTTGGTCAGCTCAAAGGAGATTGAATTCGACGGGTCGCATAAAGCACATTGGCTGAGGATTCACAGTTTAAGTCGAGCTTCTTCACTATTGTCATTCCTTTCTGAGGTTCATTATAGTTGCCTGACCTTCAACCAAGGAAAAGGTGGCTGCCCGACCCAGTCACGGCCCCGCAACCCTCGGGTATCGGTAGCGGCTAGTAGTAGGTACGGTAACGCTTCGTTACTACGCGGCACCCATGGGGCCTTTCTAGGGGCATCTAATGTCACACAAACAAAGTCTTGCTCAGCGGTATGCGGCAAGCGCTACGCACGCGACGTCCGATGCGCGATGTTAATCTCCAGCTTTCTTCCTTTTATTCGACCGCCATTCCGGGGTGAGAACCCTTGGCTCCGGATTTAGGACGATGGTGAGCACGTGGGATCGTGCCTCCAACTTGCCACGACAAGTGACCAACACAATCCTGAAGGTGGTCGCTTACGTTGAAGGGAATTTACAGTTAACTAAACGACCGCTGTATCGGTACTATCGAAATAGGATCCCTTTTGAGCTAGCGGAATGTCTAGATGCTACCCTATTGGTTGTCGTGTCGTGACAAAGCGGTATCGCTGTGAGAATACCGTGCCACTGATAAGGAGAACCACACTGGTTGTACCCATCGTTGGGGCGGGAACCCCCGTAACATTTTGGTTCCCACTCATAGTTAGCTGGTTTCTCGAATGAACTACGCTGGCTAAGAAGTGGGGCTGCATAACATATGTATTTTCCGTTATCCAGAATAGCTTAAACCGAGACACAAACTAGAGTTGCCGCCAGAAGTTTTGCAGTATCCTATCTACCTTAGCCCTTGTGAATGTCGAGCAGCACTTTAAGCTTAGGATGAATGTGACGTCCCACAGGGCAGCGACATTCGGACTGCCCTCGTCACGGAAGCCAGTCTTTTAAGGTTCTCTATACCAACGCTGCATGTCGTTTGTTTTGTGGAATGACAGTGTTATTTTTCCTCTAATAAAGACCCGGGAGCTCATAAGAGCTCCCTTATGGAATCACTCTAGTTGTTCAACAATGTTACGGTTCATCCTCTAGGGCTTACGGCTATGGGCGAACATAAGAAAACTTCTCTAACGGCTCAGCTCTGACAGCGCTCCATCCTGCGCAGGCAGCTAGCAACCGGGTAAAGTTGGACAAGTTGACTAGGTTGGGATTTGGATATGAGACCAACTGGCTCCTCTCCCTATTACCATCTAAGTTGTAAATAACCCTGTGTACATTTTGCCCGGTTTCTATCACCGACGGTATGTCGGAGCCTCTTACTATGTCTCAATATCTGTATGCGCTGTGAGGGTGTCGGGTTGTCACGAAGCGCTATCGTCCTGGGATCGGGTAGAGGCGAATATAATCACCGTTGGATATCTCTGTTCGGAGAGTCTGTGCGAATGACGGTTGTCTCGTTGGCTGCACGGCCGGGTCTTTCACGAACCAAAGCCTGGAGCAATAAGAGCGAAGATCACTGCCGGAGACGGAACATATTATGAGAACTAGACCCCAATCAGTCTATGGCCAACCTCAACGCTGGAATGAGTAGGCTGCAACTAGCGGACTAAGGGGGCGCCACCACCTGCAAGCCTGGCCATGCGACGACCCGCAGTGGGCTCACTTTGCGGTAGGTATCGACACTTATCGCACTAAAGAAACGGTACCTCTTGGTGACTACACGACATCCATACATACCCTTAGATGGTCTATAACCTTCAGAGGTGATGTTACACCTCACACTTTCCCGCGACTAGGGGCCGTATCTTGGTTCGCTTACTTAGGCATTTACACAGAAAGGCCCGAGGGGGCCATAGTGATACGAACTAATTCTGTTCGTTCTCTTCAAACGTACCCAATACCGACGACCGG",aminoacid="GCRVVTKRYR";
	//cin >> str>>aminoacid;
	//PeptideEncoding(str, aminoacid);

	//int n;
	//cin >> n;
	//cout << SubpeptidesCount(n);

	string str = "NQEL";
	//cin >> str;
	GeneratingTheoreticalSpectrum(str);

	//int n = 1024;
	//cin >> n;
	//cout << CountingPeptidesWithGivenMass(n);

	system("pause");
	return 0;
}


