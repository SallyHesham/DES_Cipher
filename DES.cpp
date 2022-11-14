#include <iostream>
#include <vector>
using namespace std;

const int initial_permutation[64] = {
    58,	50,	42,	34,	26,	18,	10,	2,
    60,	52,	44,	36,	28,	20,	12,	4,
    62,	54,	46,	38,	30,	22,	14,	6,
    64,	56,	48,	40,	32,	24,	16,	8,
    57,	49,	41,	33,	25,	17,	9,	1,
    59,	51,	43,	35,	27,	19,	11,	3,
    61,	53,	45,	37,	29,	21,	13,	5,
    63,	55,	47,	39,	31,	23,	15,	7
};

const int final_permutation[64] = {
    40,	8,	48,	16,	56,	24,	64,	32,
    39,	7,	47,	15,	55,	23,	63,	31,
    38,	6,	46,	14,	54,	22,	62,	30,
    37,	5,	45,	13,	53,	21,	61,	29,
    36,	4,	44,	12,	52,	20,	60,	28,
    35,	3,	43,	11,	51,	19,	59,	27,
    34,	2,	42,	10,	50,	18,	58,	26,
    33,	1,	41,	9,	49,	17,	57,	25,
};

const int expansion[48]{
    32,	1,	2,	3,	4,	5,
    4,	5,	6,	7,	8,	9,
    8,	9,	10,	11,	12,	13,
    12,	13,	14,	15,	16,	17,
    16,	17,	18,	19,	20,	21,
    20,	21,	22,	23,	24,	25,
    24,	25,	26,	27,	28,	29,
    28,	29,	30,	31,	32,	1
};

const int permutation[32]{
    16,	7,	20,	21,	29,	12,	28,	17,
    1,	15,	23,	26,	5,	18,	31,	10,
    2,	8,	24,	14,	32,	27,	3,	9,
    19,	13,	30,	6,	22,	11,	4,	25
};

const int permuted_choice_1[56]{
    57,	49,	41,	33,	25,	17,	9,
    1,	58,	50,	42,	34,	26,	18,
    10,	2,	59,	51,	43,	35,	27,
    19,	11,	3,	60,	52,	44,	36,
    63,	55,	47,	39,	31,	23,	15,
    7,	62,	54,	46,	38,	30,	22,
    14,	6,	61,	53,	45,	37,	29,
    21,	13,	5,	28,	20,	12,	4
};

const int permuted_choice_2[48]{
    14,	17,	11,	24,	1,	5,
    3,	28,	15,	6,	21,	10,
    23,	19,	12,	4,	26,	8,
    16,	7,	27,	20,	13,	2,
    41,	52,	31,	37,	47,	55,
    30,	40,	51,	45,	33,	48,
    44,	49,	39,	56,	34,	53,
    46,	42,	50,	36,	29,	32
};

__int64 setBit(__int64 x, int position)
{
    __int64 mask = static_cast<long long>(1) << position;
    x |= mask;
    return x;
}

__int64 clearBit(__int64 x, int position)
{
    __int64 mask = static_cast<long long>(1) << position;
    x &= ~mask;
    return x;
}

bool isBitSet(__int64 x, int position)
{
    x >>= position;
    return (x & 1) != 0;
}

int calcPos(int pos, int size) {
    return abs(pos - size);
}

__int64 permutate(__int64 x, int sizex, const int table[], int sizet) {
    int pos = 0;
    __int64 result = 0;
    for (int i = 0; i < sizet; i++) {
        pos = calcPos(table[i], sizex);
        if (isBitSet(x, pos)) {
            pos = calcPos(i + 1, sizet);
            result = setBit(result, pos);
        }
    }
    return result;
}

// S-box Table
int s[8][4][16] = {
    { 14, 4,  13, 1, 2,  15, 11, 8,  3,  10, 6,  12, 5,
      9,  0,  7,  0, 15, 7,  4,  14, 2,  13, 1,  10, 6,
      12, 11, 9,  5, 3,  8,  4,  1,  14, 8,  13, 6,  2,
      11, 15, 12, 9, 7,  3,  10, 5,  0,  15, 12, 8,  2,
      4,  9,  1,  7, 5,  11, 3,  14, 10, 0,  6,  13 },
    { 15, 1,  8,  14, 6,  11, 3, 4,  9,  7,  2,  13, 12,
      0,  5,  10, 3,  13, 4,  7, 15, 2,  8,  14, 12, 0,
      1,  10, 6,  9,  11, 5,  0, 14, 7,  11, 10, 4,  13,
      1,  5,  8,  12, 6,  9,  3, 2,  15, 13, 8,  10, 1,
      3,  15, 4,  2,  11, 6,  7, 12, 0,  5,  14, 9 },

    { 10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12,
      7,  11, 4,  2,  8,  13, 7,  0,  9,  3,  4,
      6,  10, 2,  8,  5,  14, 12, 11, 15, 1,  13,
      6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12,
      5,  10, 14, 7,  1,  10, 13, 0,  6,  9,  8,
      7,  4,  15, 14, 3,  11, 5,  2,  12 },
    { 7,  13, 14, 3,  0,  6,  9,  10, 1,  2, 8,  5,  11,
      12, 4,  15, 13, 8,  11, 5,  6,  15, 0, 3,  4,  7,
      2,  12, 1,  10, 14, 9,  10, 6,  9,  0, 12, 11, 7,
      13, 15, 1,  3,  14, 5,  2,  8,  4,  3, 15, 0,  6,
      10, 1,  13, 8,  9,  4,  5,  11, 12, 7, 2,  14 },
    { 2,  12, 4, 1,  7,  10, 11, 6, 8,  5,  3,  15, 13,
      0,  14, 9, 14, 11, 2,  12, 4, 7,  13, 1,  5,  0,
      15, 10, 3, 9,  8,  6,  4,  2, 1,  11, 10, 13, 7,
      8,  15, 9, 12, 5,  6,  3,  0, 14, 11, 8,  12, 7,
      1,  14, 2, 13, 6,  15, 0,  9, 10, 4,  5,  3 },
    { 12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3, 4, 14,
      7,  5,  11, 10, 15, 4,  2,  7,  12, 9,  5, 6, 1,
      13, 14, 0,  11, 3,  8,  9,  14, 15, 5,  2, 8, 12,
      3,  7,  0,  4,  10, 1,  13, 11, 6,  4,  3, 2, 12,
      9,  5,  15, 10, 11, 14, 1,  7,  6,  0,  8, 13 },
    { 4,  11, 2,  14, 15, 0,  8, 13, 3,  12, 9,  7,  5,
      10, 6,  1,  13, 0,  11, 7, 4,  9,  1,  10, 14, 3,
      5,  12, 2,  15, 8,  6,  1, 4,  11, 13, 12, 3,  7,
      14, 10, 15, 6,  8,  0,  5, 9,  2,  6,  11, 13, 8,
      1,  4,  10, 7,  9,  5,  0, 15, 14, 2,  3,  12 },
    { 13, 2,  8, 4,  6,  15, 11, 1,  10, 9, 3, 14, 5,
      0,  12, 7, 1,  15, 13, 8,  10, 3,  7, 4, 12, 5,
      6,  11, 0, 14, 9,  2,  7,  11, 4,  1, 9, 12, 14,
      2,  0,  6, 10, 13, 15, 3,  5,  8,  2, 1, 14, 7,
      4,  10, 8, 13, 15, 12, 9,  0,  3,  5, 6, 11 }
};

__int64 sBox(__int64 input) {
    __int64 mask = 0x0F;
    __int64 output = 0;
    for (int i = 0; i < 8; i++) {
        __int64 temp = input >> abs(i - 7) * 6;
        int x;
        int y;
        if (isBitSet(temp, 5)) {
            if (isBitSet(temp, 0)) {
                x = 3;
            }
            else {
                x = 2;
            }
        }
        else {
            if (isBitSet(temp, 0)) {
                x = 1;
            }
            else {
                x = 0;
            }
        }
        temp = temp >> 1;
        temp = temp & mask;
        y = temp;
        output = output << 4;
        output = output | s[i][x][y];
    }
    return output;
}

__int64 shiftLeft(__int64 key, __int64 round) {
    int shifts = 0;
    if (round == 1 || round == 2 || round == 9 || round == 16) {
        shifts = 1;
    }
    else {
        shifts = 2;
    }
    for (int i = shifts; i > 0; i--) {
        bool lastBit = isBitSet(key, 55);
        key = key << 1;
        if (isBitSet(key, 28)) {
            key = setBit(key, 0);
        }
        if (lastBit) {
            key = setBit(key, 28);
        }
        else {
            key = clearBit(key, 28);
        }
    }
    return key;
}

__int64 shiftRight(__int64 key, __int64 round) {
    int shifts = 0;
    if (round == 1 || round == 2 || round == 9 || round == 16) {
        shifts = 1;
    }
    else {
        shifts = 2;
    }
    for (int i = shifts; i > 0; i--) {
        bool lastBit = isBitSet(key, 0);
        key = key >> 1;
        if (isBitSet(key, 27)) {
            key = setBit(key, 55);
        }
        if (lastBit) {
            key = setBit(key, 27);
        }
        else {
            key = clearBit(key, 27);
        }
    }
    return key;
}

void printBinary(__int64 in) {
    for (int i = 63; i >= 0; i--) {
        cout << isBitSet(in, i);
    }
}

vector<__int64> createKeys(__int64 key) {
    vector<__int64> keys;
    for (int i = 1; i <= 16; i++) {
        key = shiftLeft(key, i);
        keys.push_back(permutate(key, 56, permuted_choice_2, 48));
    }
    return keys;
}

__int64 des(__int64 key, __int64 text, bool encrypt) {
    //setup
    key = permutate(key, 64, permuted_choice_1, 56);
    text = permutate(text, 64, initial_permutation, 64);
    __int64 leftText = text & (__int64)0xFFFFFFFF00000000;
    __int64 rightText = text & (__int64)0x00000000FFFFFFFF;
    leftText = leftText >> 32;
    vector<__int64>roundKeys = createKeys(key);
    if (!encrypt) reverse(roundKeys.begin(), roundKeys.end());
    //rounds
    for (int i = 1; i <= 16; i++) {
        __int64 roundKey = roundKeys[i - 1];
        __int64 feistel = rightText;
        feistel = permutate(feistel, 32, expansion, 48);
        feistel = feistel ^ roundKey;
        feistel = sBox(feistel);
        feistel = permutate(feistel, 32, permutation, 32);
        feistel = feistel ^ leftText;
        leftText = rightText;
        rightText = feistel;
        rightText = rightText & 0x00000000FFFFFFFF;
        
    }
    //final steps
    rightText = rightText << 32;
    text = rightText | leftText;
    text = permutate(text, 64, final_permutation, 64);
    return text;
}

int main()
{
    __int64 num = 0x0123456789ABCDEF;
    //encryption test
    cout << "Test in Hex\n\nEncryption:\n";
    __int64 res = des(num, num, true);
    cout << "Plaintext: 0123456789ABCDEF\nKey: 0123456789ABCDEF\nCiphertext: " << hex << res << endl<< endl;
    __int64 oldRes = res;
    res = des(num, res, false);
    cout << "Decryption:\nCiphertext: " << hex << oldRes << "\nKey: 0123456789ABCDEF\nPlaintext: " << hex << res << endl << endl;
    cout << "Test end" << endl;

}