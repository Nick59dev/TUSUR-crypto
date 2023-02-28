// Tiny Encryption Algorithm cipher, Zimin Nikita

#include <iostream>
#include <cstdint>

void encrypt(uint32_t *wrd, uint32_t *key)
{
  uint32_t i, wrd0 = wrd[0], wrd1 = wrd[1], sum = 0;
	uint32_t delta = 0x9e3779b9;

	uint32_t key0 = key[0], key1 = key[1], key2 = key[2], key3 = key[3];

	for(i = 0; i < 32; ++i)
	{
		sum += delta;
		wrd0 += ((wrd1 << 4) + key0) ^ (wrd1 + sum) ^ ((wrd1 >> 5) + key1);
		wrd1 += ((wrd0 << 4) + key2) ^ (wrd0 + sum) ^ ((wrd0 >> 5) + key3);
	}

	wrd[0] = wrd0;
	wrd[1] = wrd1;
}

void decrypt(uint32_t *wrd, uint32_t *key)
{
	uint32_t wrd0 = wrd[0], wrd1 = wrd[1], sum = 0xC6EF3720, i;
  uint32_t delta = 0x9e3779b9;

  uint32_t key0 = key[0], key1 = key[1], key2 = key[2], key3 = key[3];

  for (i = 0; i < 32; ++i) {
      wrd1 -= ((wrd0<<4) + key2) ^ (wrd0 + sum) ^ ((wrd0>>5) + key3);
      wrd0 -= ((wrd1<<4) + key0) ^ (wrd1 + sum) ^ ((wrd1>>5) + key1);
      sum -= delta;
  }

  wrd[0] = wrd0;
	wrd[1] = wrd1;
}

int main()
{
	using namespace std;
	uint64_t temp;
	uint32_t key[4];

  unsigned char *ptemp = (unsigned char*)&temp;

	char decrypted[9];
  char encrypted[9];

  decrypted[8] = '\0';
  encrypted[8] = '\0';

	short int offset, iterations;

	const char some_string[] = "secret string heh";
  char tempString[25]; tempString[24] = '\0';
	const long length = 17;

  cout << "source string: " << some_string << endl;

	key[0] = 0x02; // byte
	key[1] = 0x11; // key
	key[2] = 0xee; // values
	key[3] = 0x10; // for encryption & decryption

	offset = (8 - (length % 8)) * 8; // counting offset for bitwise shifting
  iterations = (unsigned int)(length / 8);

  // cout << iterations << " " << offset << endl;

  for(size_t i = 0; i < iterations; ++i)
  {
    for(size_t j = 0; j < 8; ++j)
    {
      ptemp[j] = (unsigned char)some_string[i*8 + j];
    }
    encrypt((uint32_t*)&temp, key);
    for(size_t j = 0; j < 8; ++j)
    {
      tempString[i*8 + j] = (char)ptemp[j];
    }
  }

  for(size_t i = 0; i < length % 8; ++i)
  {
    ptemp[i] = (unsigned char)some_string[iterations*8 + i];
  }

  temp = (temp << offset);

  encrypt((uint32_t*)&temp, key);
  for(size_t j = 0; j < 8; ++j)
  {
    tempString[iterations*8 + j] = (char)ptemp[j];
  }

  cout << "encrypted string: " << tempString << endl;

  for(size_t i = 0; i < iterations; ++i)
  {
    for(size_t j = 0; j < 8; ++j)
    {
      ptemp[j] = (unsigned char)tempString[i*8 + j];
    }
    decrypt((uint32_t*)&temp, key);
    for(size_t j = 0; j < 8; ++j)
    {
      tempString[i*8 + j] = (char)ptemp[j];
    }
  }

  for(size_t i = 0; i < 8; ++i)
  {
    ptemp[i] = (unsigned char)tempString[iterations*8 + i];
  }
  decrypt((uint32_t*)&temp, key);
  temp = (temp >> offset);

  for(size_t i = 0; i < length % 8; ++i)
  {
    tempString[iterations*8 + i] = (char)ptemp[i];
  }

  tempString[length] = '\0';

  cout << "decrypted string: "<< tempString << endl << endl;

	return 0;
}

