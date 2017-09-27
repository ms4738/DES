#include <iostream>
#include <bitset>
#include <vector>
#include <string>
using namespace std;

vector<bool> SBoxes(vector<bool> inputVector)
{
  short s1[4][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}};

  short s2[4][16] = {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}};

  short s3[4][16] = {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}};

  short s4[4][16] = {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}};

  short s5[4][16] = {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}};

  short s6[4][16] = {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}};

  short s7[4][16] = {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}};

  short s8[4][16] = {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};
  vector<vector<bool>> sboxes;
  vector<bool> outputvector;
  for(int i=0; i < 48;)
  {
    vector<bool> temp;
    for(int j=0; j<6; j++)
    {
      temp.push_back(inputVector.at(i));
      i++;
    }
    sboxes.push_back(temp);
  }

  for(int j=0; j <8; j++)
  {
    string rowstring;
    string colstring;
    rowstring.append(sboxes.at(j).at(0) ? "1" : "0");
    rowstring.append(sboxes.at(j).at(5) ? "1" : "0");
    for(int i = 1; i <5; i++)
    {
      colstring.append(sboxes.at(j).at(i) ? "1" : "0");
    }
    bitset<2> row (rowstring);
    bitset<4> col (colstring);
    bitset<4> newbinary;
    if (j == 0)
    {
      newbinary= (s1[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 1)
    {
      newbinary= (s2[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 2)
    {
      newbinary= (s3[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 3)
    {
      newbinary= (s4[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 4)
    {
      newbinary= (s5[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 5)
    {
      newbinary= (s6[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 6)
    {
      newbinary= (s7[row.to_ulong()][col.to_ulong()]);
    }
    if (j == 7)
    {
     newbinary= (s8[row.to_ulong()][col.to_ulong()]);
    }

    for(int i=0; i<4; i++)
    {
      outputvector.push_back(newbinary[i]);
    }

  }

  return outputvector;

}
int main()
{
  bitset<48> bs(15);
  cout << "Initial: " << endl;
  cout << bs << endl;
  vector<bool> bitsetvec;
  for(int i=0; i < 64; i++)
  {
    bitsetvec.push_back(bs[i]);
  }
  vector<bool> sboxVector = SBoxes(bitsetvec);
  cout << "Sbox Result: " << endl;
  for(int i=0; i<32; i++)
  {
    cout << sboxVector.at(i);
  }

}
