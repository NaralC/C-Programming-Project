#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#define MAX_LEN 150
#define TRUE 1
#define FALSE 0

//List of functions sorted by order of usage
void displayTime();																		//Displays time on the upperleft corner of the screen

int main();																				//Starting point of the program
int displayStart();																		//Prints the starting banner and acts as the starting screen
void print_image(FILE *fptr);															//Prints most ASCII arts
int displayMenu();																		//Displays the movie selection screen

int displaySeat(int movieNum);															//Shows available seats and take user's input
int seatPreview(int movieNum);															//Previews seats
int noDupes(char arr[], int size, char input, int count);								//Makes sure the user doesn't enter a seat they've already picked in the same session

int displaySummary(int movieNum, int NumofSeat, char SeatNum[], char seatHolder[]);		//Displays a confirmation message (how many seats you picked, which seats you picked)
void printArray(char arr[], int size);													//Prints an array

int displayTicket(int movieNum, int NumofSeat, char SeatNum[]);							//Prints out your ticket with printf
void print_imageTicket(FILE *fptr);														//Prints ASCII art (which are aligned differently) present in the ticket printing

int displayFinal();																		//Displays a "thank you" message and taking you back to starting screen

int displayClose();																		//Displays a confirmation message asking whether the user really wants to terminate the program.

int displayHistory();																	//Displays history of purchase
void writeData(int movieNum, int NumofSeat, char SeatNum[]);							//Update the file storing the seat data
void writeTime();																		//Writes down the time of purchase into history

//Notes:
//usin stands for "User Input"

void displayTime() { //Shows time on the upperleft corner (based on the system's calendar)
	struct tm *local, *gm;
	time_t t;
	t = time(NULL);
	local = localtime(&t);

	char weekDays[][MAX_LEN] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" }; //local->tm_wday returns an int representing what day it is in this week, with 0 starting as Sunday
	char months[][MAX_LEN] = { "January","February","March","April","May","June","July","August","September","October","November","December" }; //local->tm_mon returns an int representing what month it is in this year, with 0 starting as January

	printf("%02d:%02d\n", local->tm_hour, local->tm_min); //Hour:Minute
	printf("%s,%02d %s %02d", weekDays[local->tm_wday], local->tm_mday, months[local->tm_mon], local->tm_year + 1900); //Weekday, Date Month Year 
	printf("\n\n");
}

int main()
{
	char usin; //usin stands for "User Input"
	displayStart();
	printf("\n'H' to access history of purchase // 'X' to terminate program");
	printf("\nPress any key to continue: ");
	usin = toupper(getchar());
	while (getchar() != '\n'); //Clearing Buffer

	if (usin == 'X') { displayClose(); }
	else if (usin == 'H') { displayHistory(); }
	else { displayMenu(); }
}

int displayStart() {
	system("cls");
	displayTime();
	printf("\t\t\t");


	//Printing ================================
	for (int i = 0; i < 80; i++) {
		printf("=");
		Sleep(10);
	}
	//Printing ================================


	//Printing "Mayor Cineplex" banner
	char *filename = "Headertext.txt";
	FILE *fptr = NULL;
	if ((fptr = fopen(filename, "r")) == NULL)
	{
		printf("Unable to open %s", filename); return 1;
	}
	print_image(fptr);
	fclose(fptr);
	//Printing "Mayor Cineplex" banner


	//Printing ================================
	printf("\n\t\t\t");
	for (int i = 0; i < 80; i++) {
		printf("="); Sleep(10);
	}
	//Printing ================================
}

void print_image(FILE *fptr)
{
	char read_string[MAX_LEN];
	while (fgets(read_string, sizeof(read_string), fptr) != NULL)
	{
		printf("\t\t%s", read_string);
		Sleep(100);
	}
}

int displayMenu() {
	int usin; //Accepts the movie number
	system("cls"); 
	displayTime();

	FILE *fptr1 = NULL;
	FILE *fptr2 = NULL;
	FILE *fptr3 = NULL;
	char *filename1 = "Art1.txt";
	char *filename2 = "Art2.txt";
	char *filename3 = "Art3.txt";


	if ((fptr1 = fopen(filename1, "r")) == NULL) {  //The file pointer points to the seat file of whichever movie you picked
		printf("Unable to open %s", filename1);
		return 1;
	}
	if ((fptr2 = fopen(filename2, "r")) == NULL) {
		printf("Unable to open %s", filename2);
		return 1;
	}
	if ((fptr3 = fopen(filename3, "r")) == NULL) {
		printf("Unable to open %s", filename3);
		return 1;
	}

	printf("\n\t"); //Printing ===========
	for (int i = 0; i < 60; i++) {
		printf("=");
		Sleep(10);
	}
	printf("\n");
	print_image(fptr1); //Printing movie posters
	printf("\n\n\t");
	for (int i = 0; i < 60; i++) {
		printf("=");
		Sleep(10);
	}
	printf("\n");
	print_image(fptr2); //Printing movie posters
	printf("\n\n\t");
	for (int i = 0; i < 60; i++) {
		printf("=");
		Sleep(10);
	}

	printf("\n\t");
	printf("\n");
	print_image(fptr3); //Printing movie posters
	printf("\n\n\t");


	for (int i = 0; i < 60; i++) {//Printing ===========
		printf("=");
		Sleep(10);
	}

	fclose(fptr1);
	fclose(fptr2);
	fclose(fptr3);

	printf("\nPick your movie!\n");
	printf("<1> <2> <3>\n");

	//ACCEPTING USER INPUT
	printf("Note: input '0' to go back\n");
	while (1) {
		
		printf("Your input: ");
		scanf("%d", &usin);
		if (usin == 0) { //Inputting a '0' will take you back to the start
			while (getchar() != '\n'); //Clearing buffer
			system("cls");
			printf("Taking you back to start.");
			for (int i = 0; i < 3; i++) {
				printf(".");
				Sleep(1000);
			}
			return main();
		}
		if (usin == 1 || usin == 2 || usin == 3) { break; } //Only accepts 1 or 2 or 3
		printf("Please pick one of the three movies.\n");
		while (getchar() != '\n');
	}
	//ACCEPTING USER INPUT


	printf("You picked movie number %d", usin);


	//LOADING BAR %|=======|%
	printf("\nLoading...\n");
	for (int loop = 0; loop < 2; loop++) {
		printf("%%||");
		for (int i = 0; i < 30; i++) {
			printf("="); Sleep(25);
		}
		printf("||%%");
		printf("\n");
	}
	//LOADING BAR %|=======|%

	system("pause");
	printf("\n");
	displaySeat(usin); //Passing the movie number into the DisplaySeat() function
}

int displaySeat(int movieNum) {
	system("cls");
	displayTime();
	int usinNum; //Accepts HOW MANY seats the user wants to book
	char usinSeat[MAX_LEN]; //Accepts WHICH seats the user wants to book
	char temp;
	seatPreview(movieNum); //A preview of seats according to what movie the user picked

	//Accept user input
	printf("Note: input '0' to go back");
	while (1) {
		printf("\nHow many seats (up to 5 seats): ");
		scanf("%d", &usinNum);
		if (usinNum > 0 && usinNum <= 5) { //The user can pick up to 5 seats
			break; 
		}
		else if (usinNum == 0) {
			system("cls");
			printf("Taking you back to the movie selection screen."); //Inputting a '0' will take you back to the movie selection screen
			for (int i = 0; i < 3; i++) {
				printf(".");
				Sleep(1000);
			}
			displayMenu();
		}
		getchar();
		printf("Only integers of value 1-5 are accepted.");
	}
	while (getchar() != '\n');


	//// PULLS IN THE SEAT DATA
	char *filename1 = "Seat1.txt";
	char *filename2 = "Seat2.txt";
	char *filename3 = "Seat3.txt";
	char seatHolder[MAX_LEN]; //Accepts the seat data from text file
	FILE *fptr = NULL;

	if (movieNum == 1) { fptr = fopen(filename1, "r"); } //Points to the seat file of whichever movie you picked
	else if (movieNum == 2) { fptr = fopen(filename2, "r"); }
	else if (movieNum == 3) { fptr = fopen(filename3, "r"); }

	if (fptr == NULL)
	{
		printf("Unable to open file"); return 1; //In case of not being able to open the file
	}
	else {
		fscanf(fptr, "%s", seatHolder); //Putting seat data into this variable
		fclose(fptr);
	}
	//// PULLS IN THE SEAT DATA


	//Accept user input
	printf("\n");
	printf("Note - X represents occupied seats\n"); //Occupied seats are represented with 'X'
	for (int i = 0; i < usinNum;) {
		printf("Input seat number %d : ", i + 1);
		scanf("%c", &usinSeat[i]);
		usinSeat[i] = toupper(usinSeat[i]);
		temp = usinSeat[i];
		while (getchar() != '\n');

		if (!isalpha(temp)) { //Seats are represented as alphabets, so non-alphabets are ignored
			printf("Please input the seat number with alphabets.\n");
			continue; 
		} 
		else if (temp == 'X') { //X = occupied seat
			printf("Invalid Input (X represents an occupied seat).\n"); 
		}
		else if (noDupes(usinSeat, usinNum, temp, i) == TRUE) { //No duplicate inputs
			continue; 
		} 
		else if (strchr(seatHolder, temp) != NULL) { //Input matches seat (seat available)
			printf("Seat input: %c\n", usinSeat[i]);
			i++;
			for (int i = 0; i < strlen(seatHolder); i++) {
				if (seatHolder[i] == temp) {
					seatHolder[i] = 'X'; //Replacing with X (occupied seat)
					printf("Input successful!\n\n");
				}
			}
		}
		else {//Input does not match seat (seat taken)
			printf("Seat is either taken or non-existent\n");
			continue;
		}
	}
	usinSeat[usinNum] = '\0'; //Attaching this puts an EOF to the string
	system("pause");
	return displaySummary(movieNum, usinNum, usinSeat, seatHolder);
	//					Movie number, How many seats, Which seats, Seat data
}

int seatPreview(int movieNum) { //Preview seats
	char tempChar; //A placeholder for reading single characters from the seat file

	char *filename1 = "Seat1.txt"; //Seat files store each seat's availability
	char *filename2 = "Seat2.txt";
	char *filename3 = "Seat3.txt";

	FILE *fptr = NULL;
	if (movieNum == 1) { fptr = fopen(filename1, "r"); } //The file pointer points to the seat file of whichever movie you picked
	else if (movieNum == 2) { fptr = fopen(filename2, "r"); }
	else if (movieNum == 3) { fptr = fopen(filename3, "r"); }

	if (fptr == NULL)
	{
		printf("Unable to open seat preview"); return 1;//In case of not being able to open the file
	}
	else {
		int countofThree = 0;
		int countRow = 0;
		printf("\t============================================= Screen =============================================\n\n");
		for (int i = 0; i < 24; i++) { //An indentation(\t) every 3 seats
			if (countofThree == 3) {
				countofThree = 0;
				printf("\t");
			}
			if (countRow == 6) { //New row every 6 seats with --------- being inbetween each row
				countRow = 0;
				printf("\n\n\t---------------------------------------------------------------------------------------------------\n\n");
			}

			tempChar = fgetc(fptr);
			printf("\t");
			Sleep(250); //Putting a 0.25 delay between each printf's makes it more stylish
			printf("  |   %c   |  ", tempChar);
			countofThree += 1;
			countRow += 1;
		}
		printf("\n\n\t---------------------------------------------------------------------------------------------------\n\n");
		fclose(fptr);
	}
}

int noDupes(char arr[], int size, char input, int count) { //TRUE = there is a dupe, FALSE = no dupe
	switch (size) { //Hard coding coming up. This prevents the user from entering the same seat input in the same session
	case 1:
		return FALSE;
	case 2:
		if (count == 0) { return FALSE; }
		else if (count == 1) {
			if (input == arr[count - 1]) {
				printf("That seat has already been picked.\n");
				return TRUE;
			}
		}
	case 3:
		if (count == 0) { return FALSE; }
		else if (count == 1) {
			if (input == arr[count - 1]) {
				printf("That seat has already been picked.\n");
				return TRUE;
			}
		}
		else if (count == 2) {
			if (input == arr[count - 1] || input == arr[count - 2]) {
				printf("That seat has already been picked.\n");
				return TRUE;
			}
		}
	case 4:
		if (count == 0) { return FALSE; }
		else if (count == 1) {
			if (input == arr[count - 1]) {
				printf("That seat has already been picked.\n");
				return TRUE;
			}
		}
		else if (count == 2) {
			if (input == arr[count - 1] || input == arr[count - 2]) {
				printf("That seat has already been picked.\n");
				return TRUE;
			}
		}
		else if (count == 3) {
			if (input == arr[count - 1] || input == arr[count - 2] || input == arr[count - 3]) {
				printf("That seat has already been picked.\n");
				return TRUE;
			}
		}
	case 5:
		if (count == 0) { return FALSE; }
		else if (count == 1) {
			if (input == arr[count - 1]) {
				printf("That seat has already been picked.\n");
				return TRUE;
			}
		}
		else if (count == 2) {
			if (input == arr[count - 1] || input == arr[count - 2]) {
				printf("That seat has already been picked.\n");
				return TRUE;
			}
		}
		else if (count == 3) {
			if (input == arr[count - 1] || input == arr[count - 2] || input == arr[count - 3]) {
				printf("That seat has already been picked.\n");
				return TRUE;
			}
		}
		else if (count == 4) {
			if (input == arr[count - 1] || input == arr[count - 2] || input == arr[count - 3] || input == arr[count - 4]) {
				printf("That seat has already been picked.\n");
				return TRUE;
			}
		}
	}

}

int displaySummary(int movieNum, int NumofSeat, char SeatNum[], char seatHolder[]) {
	system("cls");
	displayTime();
	char usin;
	char *filename1 = "Seat1.txt";
	char *filename2 = "Seat2.txt";
	char *filename3 = "Seat3.txt";
	FILE *fptr = NULL;

	if (movieNum == 1) { fptr = fopen(filename1, "w"); } //Points to the seat file of whichever movie you pick
	else if (movieNum == 2) { fptr = fopen(filename2, "w"); }
	else if (movieNum == 3) { fptr = fopen(filename3, "w"); }

	Sleep(250);
	printf("You picked %d seat(s) (Movie <%d>)!\n", NumofSeat, movieNum);
	Sleep(250);
	printf("Here are your seats: ");
	printArray(SeatNum, NumofSeat); //Print out which seats you picked

	do {
		printf("\nConfirm? (Y/N): ");
		usin = toupper(getchar());
		while (getchar() != '\n');
	} while ((usin != 'Y') && (usin != 'N'));

	if (usin == 'Y') { //'Y' represents "Yes, I want to confirm my seat(s)."

		if (fptr == NULL)
		{
			printf("Unable to open re-write seat"); return 1; //In case of not being able to open the file
		}
		else {
			fprintf(fptr, "%s", seatHolder); //Updates the seat data file with selected seats
			fclose(fptr);
			printf("%%||");
			for (int i = 0; i < 30; i++) {
				printf("="); Sleep(70);
			}
			printf("%%||");
			printf("\nSeat Updated!\n"); //Signifies that the process is successful
		}

	}
	else if (usin == 'N') { //'N' represents "No, take me back to the seat selection screen."
		return displaySeat(movieNum);
	}
	system("pause");
	return displayTicket(movieNum, NumofSeat, SeatNum); //Now we print out our ticket

}

void printArray(char arr[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%c ", arr[i]);
	}
}

int displayTicket(int movieNum, int NumofSeat, char SeatNum[]) {
	system("cls");
	displayTime();
	printf("Printing ticket...\n");

	char *filename1 = "Art1.txt";
	char *filename2 = "Art2.txt";
	char *filename3 = "Art3.txt";
	FILE *fptr = NULL;

	if (movieNum == 1) { fptr = fopen(filename1, "r"); } //Points to the seat file of whichever movie you pick
	else if (movieNum == 2) { fptr = fopen(filename2, "r"); }
	else if (movieNum == 3) { fptr = fopen(filename3, "r"); }


	printf("\t\t"); //Printing ======== as top of the ticket, making it look more refined
	for (int i = 0; i < 45; i++) {
		printf("="); Sleep(25);
	}
	printf("\n");
	printf("\t\t   | Movie Number << %d >> | Airing Now!\n", movieNum); //Movie number (1-3) that the user picked shows up here

	print_imageTicket(fptr);
	fclose(fptr);
	printf("\n");

	printf("\n\t\t\t%6d Seat(s): ", NumofSeat); //This shows how many seats the user picked
	printArray(SeatNum, NumofSeat);
	printf("\n");
	printf("\t\t");
	for (int i = 0; i < 45; i++) {
		printf("="); Sleep(25); //Printing ========
	}
	printf("\n\n");

	Sleep(1000);
	printf("Writing data to history..\n"); //Signifies the user that their purchase history is being written into the history file
	printf("%%||");
	for (int i = 0; i < 30; i++) {
		printf("="); Sleep(70);
	}
	printf("||%%");

	writeTime(); //Write time of purchase and other info into history file
	writeData(movieNum, NumofSeat, SeatNum);

	printf("\n");

	system("pause");
	displayFinal();
}

void print_imageTicket(FILE *fptr) //This function is created solely because the ASCII on ticket has to be aligned differently from the other ASCII arts
{
	char read_string[MAX_LEN];
	while (fgets(read_string, sizeof(read_string), fptr) != NULL)
	{
		printf("\t\t %s", read_string);
		Sleep(250);
	}
}

int displayFinal() {
	system("cls");
	displayTime();

	//Printing "thank you" banner
	char *filename = "Thankyou.txt";
	FILE *fptr = NULL;
	if ((fptr = fopen(filename, "r")) == NULL)
	{
		printf("Unable to open %s", filename); return 1;
	}
	print_image(fptr);
	printf("\n");
	fclose(fptr);
	//Printing "thank you" banner

	system("pause");
	return main();
}

int displayClose() {
	char usin;
	FILE *fptr;
	FILE *fptr_cat;
	char *filename = "Close.txt";
	char *filename_cat = "Cat.txt";

	system("cls");
	displayTime();

	if ((fptr_cat = fopen(filename_cat, "r")) == NULL)
	{
		printf("error opening %s\n", filename_cat); //In case of the file failing to open
		return 1;
	}

	printf("Terminating Console....\n");
	print_image(fptr_cat); //Prints an image of a cat
	Sleep(1000);
	fclose(fptr_cat);


	if ((fptr = fopen(filename, "r")) == NULL)
	{
		printf("error opening %s\n", filename); //In case of the file failing to open
		return 1;
	}
	
	
	printf("\n");
	do {
		printf("You are leaving us? (Y/N): ");
		usin = toupper(getchar());
		while (getchar() != '\n');
	} while ((usin != 'Y') && (usin != 'N'));

	if (usin == 'Y') { 
		system("cls");
		printf("\n\n");
		print_image(fptr); //Prints an image of a plane with the word "Goodbye!"
		Sleep(1500);
		fclose(fptr);
		return 0;
	}
	else if (usin == 'N') { return main(); }
}

int displayHistory() {
	//LOADING SCREEN
	system("cls");
	printf("Displaying History of Purchase...\n");
	printf("%%||");
	for (int i = 0; i < 30; i++) {
		printf("="); Sleep(70);
	}
	printf("%%||");
	//LOADING SCREEN

	//ACTUAL DISPLAY
	system("cls");
	displayTime();
	char *filename = "History.txt";
	FILE *fptr = NULL;
	int movieNum; //These variables takes in data read from the history file
	int NumofSeat;
	int date;
	int month;
	int year;
	int minute;
	int hour;
	char SeatNum[MAX_LEN];
	
	////IN CASE OF THE HISTORY FILE BEING EMPTY
	fptr = fopen(filename, "r");
	if (NULL != fptr) {
		fseek(fptr, 0, SEEK_END);
		int size = ftell(fptr);

		if (0 == size) {
			printf("No Record Found...\n"); system("pause"); return main(); 
		}
	}
	////IN CASE OF THE HISTORY FILE BEING EMPTY

	fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		fprintf(stderr, "error opening %s\n", filename); return 1;
	}
	else {
		printf("Time of Purchase\tDate of Purchase\tMovie Number\tNumber of Seats\t\tSeat Number(s)\n");
		printf("\n");
		while (!feof(fptr)) {
			fscanf(fptr, "%02d:%02d\t%02d:%02d:%d\t%d\t%d\t%s\n", &hour, &minute, &date, &month, &year, &movieNum, &NumofSeat, SeatNum);
			printf("   %02d:%02d\t\t   %02d:%02d:%d\t\t     %d\t\t      %d\t\t\t    %s\n", hour, minute, date, month, year, movieNum, NumofSeat, SeatNum);
			Sleep(500);
		}

		fclose(fptr);
		printf("\nData read successfully!\n"); //Signifies that the data was read successfully
	}
	system("pause");
	return main();
	//ACTUAL DISPLAY
}

void writeData(int movieNum, int NumofSeat, char SeatNum[]) {
	char *filename = "History.txt";
	FILE *fptr = NULL;
	if ((fptr = fopen(filename, "a")) == NULL)
	{
		printf("error opening %s\n", filename); return 1; //In case of file opening failure
	}
	else {
		fprintf(fptr, "\t%d\t%d\t%s", movieNum, NumofSeat, SeatNum); //Writes data into history
		fclose(fptr);
		printf("\nData written successfully!\n"); //Signifies data being written successfully
	}
}

void writeTime() {
	char *filename = "History.txt";
	FILE *fptr = NULL;
	struct tm *local, *gm;
	time_t t;
	t = time(NULL);
	local = localtime(&t);
	if ((fptr = fopen(filename, "a")) == NULL)
	{
		printf("error opening %s\n", filename); return 1; //In case of file opening failure
	}
	else {
		fprintf(fptr, "\n%02d:%02d\t%02d:%02d:%d", local->tm_hour, local->tm_min, local->tm_mday, local->tm_mon, local->tm_year + 1900); //Writes time of purchase into history
		fclose(fptr);
	}
}