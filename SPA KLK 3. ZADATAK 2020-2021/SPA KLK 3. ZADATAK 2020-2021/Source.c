#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Artist {
	char* name;
	int members;
	float averageRatings;
}Artist;
typedef struct Voter {
	int cardID;
	char* name;
	int points;
}Voter;
void loadArtists(Artist** artists, int *artistsNumber) {
	FILE* file_artist = fopen("artists.txt", "r");
	

	if (file_artist == NULL) {
		printf("Error loading artists file!");
		exit(0);
	}
	fscanf(file_artist, "%d", artistsNumber);
	fgetc(file_artist);
	*artists = (Artist*)malloc(sizeof(Artist) * *artistsNumber);
	for (int i = 0; i < *artistsNumber; i++) {
		char artistName[40];
		fgets(artistName, sizeof(artistName), file_artist);
		artistName[strlen(artistName) - 1] = '\0';
		(*artists)[i].name = (char*)malloc(strlen(artistName));
		strcpy((*artists)[i].name, artistName);
		(*artists)[i].averageRatings = 0.0;
		fscanf(file_artist, "%d", &(*artists)[i].members);
		fgetc(file_artist);
	}
}
void loadVoters(Voter**voters, int *votersNumber) {
	FILE* file_voters = fopen("voters.txt", "r");


	if (file_voters == NULL) {
		printf("Error loading voters file!");
		exit(0);
	}
	fscanf(file_voters, "%d", votersNumber);
	fgetc(file_voters);
	*voters = (Voter*)malloc(sizeof(Voter) * *votersNumber);
	for (int i = 0; i < *votersNumber; i++) {
		
		fscanf(file_voters, "%d", &(*voters)[i].cardID);
		char c;
		(*voters)[i].name = NULL;
		fgetc(file_voters);
		int counter = 0;
		while ((c = fgetc(file_voters)) != '\n') {
			(*voters)[i].name = realloc((*voters)[i].name, sizeof(char) * (counter + 1));
			(*voters)[i].name[counter] = c;
			counter += 1;
		}
		(*voters)[i].name[counter] = '\0';
		fscanf(file_voters, "%d", &(*voters)[i].points);
		fgetc(file_voters);
		
	}
}
void printData(Artist* artists, int artistsNumber, Voter *voters, int votersNumber) {
	for (int i = 0; i < artistsNumber; i++) {
		printf("%s %.1f\n", artists[i].name, artists[i].averageRatings);
	}
	printf("\n");
	for (int i = 0; i < votersNumber; i++) {
		printf("%s %d %d\n", voters[i].name, voters[i].cardID, voters[i].points);
	}
	printf("\n");
}
void updateData(Artist** artists, Voter* voters, int artistsNumber, int votersNumber) {
	for (int i = 0; i < artistsNumber; i++) {
		int numberOfVotes = 0;
		for (int j = 0; j < votersNumber; j++) {
			if (strcmp((*artists)[i].name, voters[j].name) == 0) {
				(*artists)[i].averageRatings += voters[j].points;
				numberOfVotes += 1;
			}
		}
		if (numberOfVotes > 0) {
			(*artists)[i].averageRatings /= (float)numberOfVotes;
		}
		

	}
}
void merge(Artist** artists, int artistNumber, int low, int mid, int high) {
	Artist* temp = (Artist*)malloc(sizeof(Artist) * artistNumber);
	int i = low;
	int j = mid + 1;
	int k = low;
	while (i <= mid && j <= high) {
		if ((*artists)[i].averageRatings > (*artists)[j].averageRatings) {
			temp[k++] = (*artists)[i++];
		}
		else temp[k++] = (*artists)[j++];
	}
	for (; i <= mid; i++) {
		temp[k++] = (*artists)[i];
	}
	for (; j <= high; j++) {
		temp[k++] = (*artists)[j];
	}
	for (i = low; i <= high; i++) {
		(*artists)[i] = temp[i];
	}
}
void mergeSort(Artist **artists, int artistNumber, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		mergeSort(artists, artistNumber, low, mid);
		mergeSort(artists, artistNumber, mid + 1, high);
		merge(artists, artistNumber, low, mid, high);
	}
}
void printWinners(Artist* artists) {
	printf("\n");
	for (int i = 0; i < 4; i++) {
		printf("%s %.1f\n", artists[i].name, artists[i].averageRatings);
	}
}
int main() {
	Voter* voters;
	Artist* artists;
	int artistsNumber;
	int votersNumber;
	loadArtists(&artists, &artistsNumber);
	loadVoters(&voters, &votersNumber);
	printData(artists, artistsNumber, voters, votersNumber);
	updateData(&artists, voters, artistsNumber, votersNumber);
	printData(artists, artistsNumber, voters, votersNumber);
	mergeSort(&artists, artistsNumber, 0, artistsNumber-1);
	printData(artists, artistsNumber, voters, votersNumber);
	printWinners(artists);
}