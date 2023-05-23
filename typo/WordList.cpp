#include <cmath>
#include <fstream>
#include "WordList.h"

WordList::WordList(std::istream& stream) {
    std::string word;
    while (std::getline(stream, word)) {
        auto add = [](const std::string& word)->bool {
            for (char c : word) {
               if (!islower(c)) {
                    return false;
                }
            }
            return true;
        };
        if (add(word)) {
            mWords.push_back(word);
        }
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const
{
    Heap result(maxcount);

    for (const auto& word : mWords) {
        if (word.length() == points.size()) {
            float totalScore = 0.0f;
            for (size_t i =0;i < points.size();++i){

                float dx = points[i].x - QWERTY[word[i]-'a'].x;
                float dy = points[i].y - QWERTY[word[i]-'a'].y;
                float distance = std::sqrt(std::pow(dx , 2) + std::pow(dy , 2));
                float score = 1.0f / (10 * distance * distance + 1);

                totalScore += score;
            }
            float score = totalScore / static_cast<float>(points.size());
            if (score >= cutoff) {
                result.push(word, score);
            }
        }
    }

    return result;
}




