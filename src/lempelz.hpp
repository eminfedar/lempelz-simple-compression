#ifndef Lempelz_H
#define Lempelz_H

#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Lempelz
{
  private:

    static int findIndex(vector<string> array, string search)
    {

        for (int i = 0; i < array.size(); i++)
        {
            if (array[i] == search)
                return i;
        }

        return -1;
    }

  public:
    static vector<bool> encode(string data)
    {
        vector<bool> encodedString;
        string encodedStringTEST = "";
        vector<string> dictionary;
        dictionary.push_back("");

        string prefix = "";

        for (int i = 0; i < data.length(); ++i)
        {
            int searchResult = findIndex(dictionary, prefix + data.at(i));
            if (searchResult != -1)
                prefix += data.at(i);
            else
            {

                int index = findIndex(dictionary, prefix);

                int byteSize = dictionary.size() - 1 > 1 ? (log2(dictionary.size() - 1) + 1) : 1;
                for (int a = 0; a < byteSize; a++)
                {
                    encodedString.push_back(((index >> a) & 1));
                }

                for (int a = 0; a < 8; a++)
                {
                    encodedString.push_back(((data.at(i) >> a) & 1));
                }

                dictionary.push_back(prefix + data.substr(i, 1));
                prefix = "";
            }
        }

        if (prefix != "")
        {
            // last element
            int index = findIndex(dictionary, prefix);
            int byteSize = dictionary.size() - 1 > 1 ? (log2(dictionary.size() - 1) + 1) : 1;
            for (int a = 0; a < byteSize; a++)
            {
                encodedString.push_back(((index >> a) & 1));
            }
        }

        return encodedString;
    }

    static string decode(vector<bool> data)
    {
        vector<string> dictionary;
        dictionary.push_back(""); // 0 index is empty
        string decodedString = "";

        int c = 0;
        while (c < data.size())
        {
            int number = 0;

            // read number.
            int byteSize = dictionary.size() - 1 > 1 ? (log2(dictionary.size() - 1) + 1) : 1;
            for (int a = 0; a < byteSize; ++a)
            {
                if (c - a + byteSize <= data.size())
                {
                    number += data.at(c) * pow(2, a);
                    c++;
                }
                else
                    break;
            }

            // read character after number.
            char character = 0;
            for (int a = 0; a < 8; ++a)
            {
                if (c - a + 8 <= data.size())
                {
                    character += data.at(c) * pow(2, a);
                    c++;
                }
                else
                    break;
            }

            // Last number for last letter.
            if (number != 0 && character == 0)
            {
                decodedString.append(dictionary[number]);
            }
            else
            {
                // Add new word to dictionary
                dictionary.push_back("");

                // Follow the number sequence until 0 and add it
                if (number != 0)
                {
                    dictionary[dictionary.size() - 1] += dictionary[number];
                    dictionary[dictionary.size() - 1] += character;
                    decodedString.append(dictionary[number]);
                    decodedString += character;
                }
                else // If first time, add the word to the dictionary
                {
                    dictionary[dictionary.size() - 1] += character;
                    decodedString += character;
                }
            }
        }

        return decodedString;
    }
};

#endif
