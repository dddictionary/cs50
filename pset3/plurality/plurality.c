#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int mostVotes = 0;
    int currentCandidate = 0;
    /*Go through the list of candidates votes and check to see who has the most votes.
    Record that value of the most votes in a variable.*/
    while(currentCandidate < candidate_count)
    {
        if (mostVotes < candidates[currentCandidate].votes)
        {
            mostVotes = candidates[currentCandidate].votes;
        }
        currentCandidate++;
    }
    /*Go through the list of names and check to see whose number of votes is the largest.
    This counts for ties as well because if there are ties, everyone will have the same
    number of votes and thus their name will get printed*/
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == mostVotes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    //TODO
    return;
}

