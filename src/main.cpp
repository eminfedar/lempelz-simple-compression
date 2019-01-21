#include <iostream>
#include "lempelz.hpp"
#include <cmath>

using namespace std;

int main(int argc, char **argv)
{
    // If any arguments. 
    // (example: './app AABBABA' outputs -> '01000001010100001000010000100110000010' )
    if (argc > 1)
    {
        string text;
        bool isEncode = 1; // there is only encoding now. Maybe someone will implement decoding.
        for (int i = 1; i < argc; i++)
        {
            if (argv[i] == "-d")
            {
                isEncode = 0;
                continue;
            }

            text += argv[i];
        }

        vector<bool> encoded = Lempelz::encode(text);
        for (int i = 0; i < encoded.size(); ++i)
        {
            cout << encoded[i];
        }
        cout << endl << endl << text.size() << " bytes -> " << encoded.size()/8 << " bytes." << endl;
    }

    // If no arguments, ask for input.
    else
    {
        string input;
        do
        {
            system("clear");
            cout << "Enter the text you want to compress with LempelZ(LZ78)\n->";
            string text;
            cin >> text;

            // Encode and decode again the text.
            vector<bool> encoded = Lempelz::encode(text);
            string decoded = Lempelz::decode(encoded);

            // Print to the screen
            // Text -->
            cout << "Text : (" << text.size() * 8 << ")" << endl;
            for (int i = 0; i < text.size(); ++i)
            {
                for (int a = 0; a < 8; ++a)
                {
                    cout << ((text.at(i) >> a) & 1);
                }
                cout << "(" << text.at(i) << ") ";
            }
            // ---------------

            // %% Calculate compress ratio %%
            float realBitSize = text.size() * 8;
            float encodedBitSize = encoded.size();
            float compressRatio = (realBitSize - encodedBitSize) / realBitSize;

            if (compressRatio < 0)
                cout << endl
                     << endl
                     << "!! -- Compression technique did not worked on that data. -- !!";
            // ---------------

            // Compressed Text -->
            cout << endl
                 << endl
                 << "Compressed Text: (" << encoded.size() << ")"
                 << " [ " << compressRatio * 100 << "% compressed ]" << endl;
            for (int i = 0; i < encoded.size(); ++i)
            {
                cout << encoded[i];
            }
            // ---------------

            // Decompressed Text -->
            cout << endl
                 << endl;
            cout << "Decoded from encoded data : (" << decoded.size() * 8 << ")" << endl;
            for (int i = 0; i < decoded.size(); ++i)
            {
                for (int a = 0; a < 8; ++a)
                {
                    cout << ((decoded.at(i) >> a) & 1);
                }
                cout << "(" << decoded[i] << ") ";
            }
            // ---------------

            cout << endl
                 << endl
                 << "( Write 'q' or 'quit' to close the program, anything to write again. )";
        } while (cin >> input && input != "quit" && input != "q");
    }

    return 0;
}