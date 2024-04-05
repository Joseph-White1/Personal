#include <iostream>
#include <fstream>
#include <list>
#include <string>

struct candidateType
{
  string name;
  int region1, region2, region3, region4, total;
};

int main()
{
    list<candidateType> candidates;

    ifstream candDataFile("candData.txt");
    while (candDataFile.good())
    {
        candidateType candidate;
        candDataFile >> candidate.name >> candidate.region1 >> candidate.region2 >> candidate.region3 >> candidate.region4;
        candidate.total = candidate.region1 + candidate.region2 + candidate.region3 + candidate.region4;
        candidates.push_back(candidate);
    }
        candDataFile.close();

        ifstream voteDataFile("voteData.txt");
        while (voteDataFile.good()) {
        string region;
        int votes;
        voteDataFile >> region >> votes;
        for (list<candidateType>::iterator it = candidates.begin(); it != candidates.end(); ++it)
        {
            if (region == "Region1") {
            it->region1 = votes;
            } else if (region == "Region2") {
            it->region2 = votes;
            } else if (region == "Region3") {
            it->region3 = votes;
            } else if (region == "Region4") {
            it->region4 = votes;
            }
            it->total = it->region1 + it->region2 + it->region3 + it->region4;
        }
    }
        voteDataFile.close();

        cout << "--------------------Election Results--------------------" << endl;
        cout << "Votes\tCandidate Name\tRegion1\tRegion2\tRegion3\tRegion4\tTotal" << endl;
        cout << "------------------\t-------\t-------\t-------\t-------\t------" << endl;
        for (list<candidateType>::iterator it = candidates.begin(); it != candidates.end(); ++it) {
        cout << it->name << "\t\t" << it->region1 << "\t\t" << it->region2 << "\t\t" << it->region3 << "\t\t" << it->region4 << "\t\t" << it->total << endl;
    }

    candidates.sort([](const candidateType &a, const candidateType &b) { return a.total > b.total; });
    cout << "Winner: " << candidates.front().name << ", Votes Received: " << candidates.front().total << endl;

    int totalVotes = 0;
    for (list<candidateType>::iterator it = candidates.begin(); it != candidates.end(); ++it)
    {
        totalVotes += it->total;
    }
    cout << "Total votes polled: " << totalVotes << endl;

    return 0;
}
