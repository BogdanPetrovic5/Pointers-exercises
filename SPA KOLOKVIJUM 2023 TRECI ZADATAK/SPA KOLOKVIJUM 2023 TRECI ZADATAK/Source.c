#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct Club {
	char* name;
	char* cityOfOrigin;
	int points;
	int goals;
}Club;
typedef struct Match {
	char* host;
	char* guest;
	int hostGoals;
	int guestGoals;
}Match;
void loadClubs(Club** clubs, int* numClubs) {
	FILE* clubFile = fopen("klubovi.txt", "r");
	fscanf(clubFile, "%d", numClubs);

	fgetc(clubFile);
	*clubs = (Club*)malloc(*numClubs * sizeof(Club));

	for (int i = 0; i < *numClubs; i++) {
		char clubName[40];
		char origin[40];
		fgets(clubName, 40, clubFile);
		(*clubs + i)->name = (char*)malloc(strlen(clubName));
		strcpy((*clubs)[i].name, clubName);
		(*clubs)[i].name[strlen(clubName)-1] = '\0';
		fgets(origin, 40, clubFile);
		(*clubs + i)->cityOfOrigin = (char*)malloc(strlen(origin));
		strcpy((*clubs)[i].cityOfOrigin, origin);
		(*clubs)[i].cityOfOrigin[strlen(origin) - 1] = '\0';
		fscanf(clubFile, "%d", &(*clubs)[i].points);
		fgetc(clubFile);
		fscanf(clubFile, "%d", &(*clubs)[i].goals);
		fgetc(clubFile);
	}
}
void loadMatches(Match** matches, int* numMatches) {
	FILE* matchesFile = fopen("bodovanje.txt", "r");
	*matches = NULL;
	while (feof(matchesFile) == 0) {
		char hostName[40];
		char guestName[40];
		*matches = (Match*)realloc(*matches, sizeof(Match) * (*numMatches + 1));

		fgets(hostName, 40, matchesFile);
		(*matches)[*numMatches].host = (char*)malloc(strlen(hostName));
		strcpy((*matches)[(*numMatches)].host, hostName);
		fgets(guestName, 40, matchesFile);
		(*matches)[(*numMatches)].host[strlen(hostName) - 1] = '\0';
		(*matches)[(*numMatches)].guest = malloc(strlen(guestName));
		strcpy((*matches)[(*numMatches)].guest, guestName);
		(*matches)[(*numMatches)].guest[strlen(guestName) - 1] = '\0';
		fscanf(matchesFile, "%d", &(*matches)[(*numMatches)].hostGoals);
		fgetc(matchesFile);
		fscanf(matchesFile, "%d", &(*matches)[(*numMatches)].guestGoals);
		fgetc(matchesFile);
		*numMatches = (*numMatches) + 1;
	}
}
void printData(Club* club, int numClubs, Match* matches, int numMatches) {
	printf("Klubovi:\n");
	for (int i = 0; i < numClubs; i++) {
		printf("%s %s %d %d\n", club[i].name, club[i].cityOfOrigin, club[i].points, club[i].goals);
	}
	printf("\n");
	printf("Utakmice:\n");
	for (int i = 0; i < numMatches; i++) {
		printf("%s %s %d %d\n", matches[i].host, matches[i].guest, matches[i].hostGoals, matches[i].guestGoals);
	}
}
void updateData(Club** clubs, Match* matches, int numClubs, int numMatches) {
	char* winner = NULL;
	int nPoints;
	for (int i = 0; i < numMatches; i++) {
		winner = NULL;
		int guest = 0, host = 0;
		if (matches[i].guestGoals < matches[i].hostGoals) {
			winner = (char*)malloc(strlen(matches[i].host));
			strcpy(winner, matches[i].host);
			host = 1;
			nPoints = 3;
		}
		else if (matches[i].guestGoals > matches[i].hostGoals) {
			winner = (char*)malloc(strlen(matches[i].guest));
			strcpy(winner, matches[i].guest);
			guest = 1;
			nPoints = 3;
		}
		else {
			nPoints = 1;
		}
		if (winner != NULL) {
			for (int j = 0; j < numClubs; j++) {

				if (strcmp((*clubs)[j].name, winner) == 0) {
					if (host == 1) {
						(*clubs)[j].goals += matches[i].hostGoals;
					}
					if (guest == 1) {
						(*clubs)[j].goals += matches[i].guestGoals;
					}
					(*clubs)[j].points += nPoints;
				}

			}
		}
		else {
			for (int j = 0; j < numClubs; j++) {
				if (strcmp((*clubs)[j].name, matches[i].guest) == 0) {
					(*clubs)[j].goals += matches[i].guestGoals;
					(*clubs)[j].points += nPoints;
				}
				else if (strcmp((*clubs)[j].name, matches[i].host) == 0) {
					(*clubs)[j].goals += matches[i].hostGoals;
					(*clubs)[j].points += nPoints;
				}
			}
		}

	}
}
void merge(Club** clubs, int low, int mid, int high, int numClubs) {
	int i = low;
	int j = mid + 1;
	
	int k = low;
	int n = numClubs;
	static Club tempClubs[100];
	while (i <= mid && j <= high) {
		if ((*clubs)[i].points > (*clubs)[j].points){
			tempClubs[k++] = (*clubs)[i++];
		}else tempClubs[k++] = (*clubs)[j++];
	}
	for (; i <= mid; i++) {
		tempClubs[k++] = (*clubs)[i];
	}
	for (; j <= high; j++) {
		tempClubs[k++] = (*clubs)[j];
	}
	for (i = low; i <= high; i++) {
		(*clubs)[i] = tempClubs[i];
	}
	
}
void mergeSort(Club **clubs, int numClubs, int low, int high) {

	if (low < high) {
		int mid = (low + high) / 2;
		mergeSort(clubs, numClubs, low, mid);
		mergeSort(clubs, numClubs, mid + 1, high);
		merge(clubs, low, mid, high, numClubs);
	}
	
}
int main() {
	Club* clubs;
	Match* matches;
	int numClubs;
	int numMatches = 0;
	loadClubs(&clubs, &numClubs);
	loadMatches(&matches, &numMatches);
	printData(clubs, numClubs, matches, numMatches);
	updateData(&clubs, matches, numClubs, numMatches);
	printf("\n \n");
	int low = 0;
	int high = numClubs - 1;
	mergeSort(&clubs, numClubs, low, high);
	printData(clubs, numClubs, matches, numMatches);
}