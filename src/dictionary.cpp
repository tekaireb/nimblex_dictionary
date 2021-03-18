#include "dictionary.h"

using namespace std;

Dictionary::Dictionary() {}

void Dictionary::load_from_file(string filename) {
    // Open dataset file
    fstream f;
    f.open(filename, ios::in);
    if (!f.is_open()) {
        cout << "File cannot be opened." << endl;
        return;
    }

    int pos;                // Holds position of each quote temporarily
    string line;            // Holds text from each line of file
    int positions[4];       // Holds positions of quotes for every line (each valid line has 4: "WORD": "DEFINITION")
    int num_positions = 0;  // Keeps track of number of positions found
    string word, def;

    while (getline(f, line) && t.num_words < 10000) {  // Process each line of file
        pos = line.find("\"", 0);                      // Get position of first quote
        while (pos != string::npos) {
            if (line.at(pos - 1) != '\\')          // Ignore escaped quotes
                positions[num_positions++] = pos;  // Save position
            pos = line.find("\"", pos + 1);        // Find successive quotes
        }
        if (num_positions == 4) {
            word = line.substr(positions[0] + 1, positions[1] - positions[0] - 1);
            def = line.substr(positions[2] + 1, positions[3] - positions[2] - 1);
            t.insert(word, def);
            // cout << word << ": " << def << endl;
        }

        num_positions = 0;  // Reset position count
        t.num_words++;      // Increment word count
    }
    f.close();  // Close file

    /*
    Dataset file format:
    {
        "first word": "first definition.",
        "second word": "second definition.",
        "...": "...",
    }
    */
}