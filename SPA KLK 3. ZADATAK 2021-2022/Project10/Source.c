#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct Team {
	char* name;
	char group;
	int points;
	int goals;
}Team;
typedef struct Match {
	char* firstTeam;
	int ftGoals;
	char* secondTeam;
	int stGoals;
}Match;
void loadTeams(Team** teams, int* numTeams) {
	FILE *teamsFile = fopen("reprezentacija.txt", "r");
	if (teamsFile == NULL) {
		printf("ERROR loading file TEAMS");
		exit(0);
	}

	fscanf(teamsFile, "%d", numTeams);
	fgetc(teamsFile);
	*teams = (Team*)malloc(sizeof(Team) * *numTeams);
	for (int i = 0; i < *numTeams; i++) {
		char name[40];
		
		fgets(name, sizeof(name), teamsFile);
		name[strlen(name) - 1] = '\0';
		(*teams)[i].name = (char*)malloc(strlen(name));
		
		strcpy((*teams)[i].name, name);

		fscanf(teamsFile,"%c", &(*teams)[i].group);
		fgetc(teamsFile);
		(*teams)[i].points = 0;
		(*teams)[i].goals = 0;
		
	}
	
}
void loadMatches(Match**matches, int *num) {
	FILE* matchesFile = fopen("utakmice.txt", "r");
	if (matchesFile == NULL) {
		printf("ERROR loading file MATCHES");
		exit(0);
	}

	fscanf(matchesFile, "%d", num);
	fgetc(matchesFile);
	*matches = (Match*)malloc(sizeof(Match) * *num);
	for (int i = 0; i < *num; i++) {
		char firstTeamName[40];
		char secondTeamName[40];
		
		fgets(firstTeamName, sizeof(firstTeamName), matchesFile);
		firstTeamName[strlen(firstTeamName) - 1] = '\0';
		(*matches)[i].firstTeam = (char*)malloc(strlen(firstTeamName));
		strcpy((*matches)[i].firstTeam, firstTeamName);
		
		fscanf(matchesFile, "%d", &(*matches)[i].ftGoals);
		
		fgetc(matchesFile);
		
		fgets(secondTeamName, sizeof(secondTeamName), matchesFile);
		secondTeamName[strlen(secondTeamName) - 1] = '\0';
		(*matches)[i].secondTeam = (char*)malloc(strlen(secondTeamName));
		strcpy((*matches)[i].secondTeam, secondTeamName);
		
		fscanf(matchesFile, "%d", &(*matches)[i].stGoals);
		
		fgetc(matchesFile);
	}
}
void printData(Team* teams, int NUM_TEAMS, Match* matches, int NUM_MATCHES) {
	
	for (int i = 0; i < NUM_TEAMS; i++) {
		printf("%s %c %d %d\n", teams[i].name, teams[i].group, teams[i].points, teams[i].goals);
	}
	printf("\n \n");
	for (int i = 0; i < NUM_MATCHES; i++) {
		printf("%s %d %s %d\n", matches[i].firstTeam, matches[i].ftGoals, matches[i].secondTeam, matches[i].stGoals);
	}
}


void updateData(Match* matches, Team** teams, int NUM_TEAMS, int NUM_MATCHES) {
	const int winPts = 3;
	const int drawPts = 1;

	for (int i = 0; i < NUM_MATCHES; i++) {
		char firstTeamGroup = NULL;
		char secondTeamGroup = NULL;
		int firstTeamIndex;
		int secondTeamIndex;
		for (int j = 0; j < NUM_TEAMS; j++) {
			
			if (strcmp(matches[i].firstTeam, (*teams)[j].name) == 0) {
				firstTeamGroup = (*teams)[j].group;
				firstTeamIndex = j;
			}
			if (strcmp(matches[i].secondTeam, (*teams)[j].name) == 0) {
				secondTeamGroup = (*teams)[j].group;
				secondTeamIndex = j;
			}
		}
		if (firstTeamGroup == secondTeamGroup) {
			if (matches[i].ftGoals > matches[i].stGoals) {
				(*teams)[firstTeamIndex].points += winPts;
			}
			else if (matches[i].ftGoals < matches[i].stGoals) {
				(*teams)[secondTeamIndex].points += winPts;
			}
			else {
				(*teams)[firstTeamIndex].points += drawPts;
				(*teams)[secondTeamIndex].points += drawPts;
			}
			(*teams)[firstTeamIndex].goals += matches[i].ftGoals;
			(*teams)[secondTeamIndex].goals += matches[i].stGoals;
		}
	}
}
void sort(Team **teams, int NUM_TEAMS) {
	Team temp;
	for (int i = NUM_TEAMS - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if ((*teams)[j].goals < (*teams)[j + 1].goals) {
				temp = (*teams)[j];
				(*teams)[j] = (*teams)[j + 1];
				(*teams)[j + 1] = temp;
			}
		}
	}
}
void findWinner(Team *teams, int NUM_TEAMS) {
	int counter = 0;
	char* numGroups = NULL;
	numGroups = (char*)realloc(numGroups, sizeof(numGroups) * (counter + 1));
	counter += 1;
	numGroups[0] = teams[0].group;
	for (int i = 1; i < NUM_TEAMS; i++) {
		int flag = 0;
		for (int j = 0; j < counter; j++) {
			if (teams[i].group == numGroups[j]) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			numGroups = (char*)realloc(numGroups, sizeof(numGroups) * (counter + 1));
			numGroups[counter] = teams[i].group;
			counter += 1;
		}
	}
	printf("\n \n");
	for (int i = 0; i < counter; i++) {
		printf("%c", numGroups[i]);
	}

}
int main() {
	Team* teams;
	Match* matches;
	const int NUM_TEAMS;
	const int NUM_MATCHES;
	loadTeams(&teams, &NUM_TEAMS);
	loadMatches(&matches, &NUM_MATCHES);
	printData(teams, NUM_TEAMS, matches, NUM_MATCHES);
	updateData(matches, &teams, NUM_TEAMS, NUM_MATCHES);
	printf("\n \n");
	printData(teams, NUM_TEAMS, matches, NUM_MATCHES);
	sort(&teams, NUM_TEAMS);
	printf("\n \n");
	printData(teams, NUM_TEAMS, matches, NUM_MATCHES);
	findWinner(teams, NUM_TEAMS);

}