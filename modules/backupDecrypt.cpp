/*
string plainText;

vector<bool> leftTextI;
vector<bool> rightTextI;
vector<bool> leftKey;
vector<bool> rightKey;
vector<bool> leftTextIPlus1;
vector<bool> rightTextIPlus1;
vector<bool> permKey;
initPerm(cipherTextBits, leftTextIPlus1, rightTextIPlus1);
pc1Perm(keyBits, leftKey, rightKey);

for (short i = ROUND_COUNT - 1; i >= 0; i--)
{
  vector<bool> shiftedLeftKey = leftKey;
  vector<bool> shiftedRightKey = rightKey;
  rightTextI = leftTextIPlus1;
  //Right text is permuted and expanded to 48 bits
  leftTextIPlus1 = eTablePerm(leftTextIPlus1);
  //PC-2 Table permutation for keys, also now 48 bits
  for (short j = 0; j <= i; j++)
  {
    shiftedLeftKey = leftShiftSched(shiftedLeftKey, j);
    shiftedRightKey = leftShiftSched(shiftedRightKey, j);
  }

  permKey = pc2Perm(shiftedLeftKey, shiftedRightKey);
  for (unsigned short j = 0; j < leftTextIPlus1.size(); j++)
  {
    //XOR each bit of the right text with the key
    leftTextIPlus1.at(j) = leftTextIPlus1.at(j)^permKey.at(j);
  }
  leftTextIPlus1 = sBoxSub(leftTextIPlus1);
  leftTextIPlus1 = pTablePerm(leftTextIPlus1);
  for (unsigned short j = 0; j < leftTextIPlus1.size(); j++)
  {
    //XOR each bit of the right text with the key
    leftTextIPlus1.at(j) = leftTextIPlus1.at(j)^rightTextIPlus1.at(j);
  }
  rightTextIPlus1 = rightTextI;
}
//32-bit swap
leftTextIPlus1.insert(rightTextIPlus1.end(), leftTextIPlus1.begin(), leftTextIPlus1.end());
//Inverse IP Table
leftTextIPlus1 = invInitPerm(leftTextIPlus1);


//Converting binary back into chars
for (int i = 0; i < CHARS_IN_BLOCK; i++)
{
  string tempString = "";
  for (int j = 0; j < BITS_IN_CHAR; j++)
  {
    tempString += leftTextIPlus1.at((i * CHARS_IN_BLOCK) + j);
  }
  bitset<BITS_IN_CHAR> temp(tempString);
  plainText += static_cast<char>(temp.to_ulong());
}

return plainText;
}
*/
