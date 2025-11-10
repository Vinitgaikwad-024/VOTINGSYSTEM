#include <stdio.h>
#include <string.h>
#define MAX_VOTERS 100
#define MAX_CANDIDATES 10

struct Voter {
    int id;
    char name[50];
    int hasVoted;
};

struct Candidate {
    int id;
    char name[50];
    int votes;
};

struct Voter voters[MAX_VOTERS];
struct Candidate candidates[MAX_CANDIDATES];
int voterCount = 0, candidateCount = 0;

int findVoter(int id) {
    for (int i = 0; i < voterCount; i++)
        if (voters[i].id == id) return i;
    return -1;
}
int findCandidate(int id) {
    for (int i = 0; i < candidateCount; i++)
        if (candidates[i].id == id) return i;
    return -1;
}

void addCandidate() {
    if (candidateCount >= MAX_CANDIDATES) {
        printf("Limit reached!\n");
        return;
    }
    struct Candidate c;
    printf("Enter Candidate ID: "); scanf("%d", &c.id);
    printf("Enter Name: "); scanf(" %[^\n]", c.name);
    c.votes = 0;
    candidates[candidateCount++] = c;
    printf("Candidate added!\n");
}

void registerVoter() {
    if (voterCount >= MAX_VOTERS) {
        printf("Limit reached!\n");
        return;
    }
    struct Voter v;
    printf("Enter Voter ID: "); scanf("%d", &v.id);
    if (findVoter(v.id) != -1) {
        printf("ID already exists!\n");
        return;
    }
    printf("Enter Name: "); scanf(" %[^\n]", v.name);
    v.hasVoted = 0;
    voters[voterCount++] = v;
    printf("Voter registered!\n");
}

void showCandidates() {
    if (candidateCount == 0) {
        printf("No candidates yet!\n");
        return;
    }
    printf("\n--- Candidates ---\n");
    for (int i = 0; i < candidateCount; i++)
        printf("%d. %s (%d votes)\n", candidates[i].id, candidates[i].name, candidates[i].votes);
}

void castVote() {
    int id;
    printf("Enter Voter ID: "); scanf("%d", &id);
    int vi = findVoter(id);
    if (vi == -1) {
        printf("Voter not found!\n");
        return;
    }
    if (voters[vi].hasVoted) {
        printf("Already voted!\n");
        return;
    }

    showCandidates();
    int cid;
    printf("Vote for Candidate ID: "); scanf("%d", &cid);
    int ci = findCandidate(cid);
    if (ci == -1) {
        printf("Invalid Candidate!\n");
        return;
    }

    candidates[ci].votes++;
    voters[vi].hasVoted = 1;
    printf("Vote cast successfully!\n");
}

void showResults() {
    if (candidateCount == 0) {
        printf("No results to show!\n");
        return;
    }
    int maxIndex = 0;
    printf("\n--- RESULTS ---\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%s got %d votes.\n", candidates[i].name, candidates[i].votes);
        if (candidates[i].votes > candidates[maxIndex].votes) maxIndex = i;
    }
    printf("\nWinner: 🏆 %s (%d votes) 🏆\n", candidates[maxIndex].name, candidates[maxIndex].votes);
}

void employeeMenu() {
    int pass;
    printf("Enter Employee Passcode (1234): ");
    scanf("%d", &pass);
    if (pass != 1234) {
        printf("Access Denied!\n");
        return;
    }
    int ch;
    while (1) {
        printf("\n1.Add Candidate\n2.View Candidates\n3.View Results\n4.Logout\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) addCandidate();
        else if (ch == 2) showCandidates();
        else if (ch == 3) showResults();
        else if (ch == 4) break;
        else printf("Invalid!\n");
    }
}

void voterMenu() {
    int ch;
    while (1) {
        printf("\n1.Register\n2.Vote\n3.View Candidates\n4.Logout\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) registerVoter();
        else if (ch == 2) castVote();
        else if (ch == 3) showCandidates();
        else if (ch == 4) break;
        else printf("Invalid!\n");
    }
}

int main() {
    int ch;
    printf("===== ONLINE VOTING SYSTEM =====\n");
    while (1) {
        printf("\n1.Employee Login\n2.Voter Login\n3.Exit\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) employeeMenu();
        else if (ch == 2) voterMenu();
        else if (ch == 3) break;
        else printf("Invalid choice!\n");
    }
    printf("Thank you for using the system!\n");
    return 0;
}
