#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_LENGTH 100
#define MAX_QUESTIONS 10

void signUp();
void signin();
void adminLogin();
void playGame(int difficulty, const char *topic, int *lives);
void addQuestion(int difficulty, const char *topic);
void removeQuestion(int difficulty, const char *topic);
void addUser();

const char *userFile = "users.txt";
const char *topics[] = {
    "science", "technology", "movies", "sports",
    "general_health", "geography", "history", "math"
};

typedef struct {
    char question[MAX_LENGTH];
    char options[4][MAX_LENGTH];
    char correctOption;
} Question;

void signUp() {
    char username[MAX_LENGTH], password[MAX_LENGTH];
    FILE *file = fopen(userFile, "a");
    if (file == NULL) {
        printf("Error opening file for sign-up!\n");
        return;
    }
    printf("Enter a username: ");
    scanf("%s", username);
    printf("Enter a password: ");
    scanf("%s", password);
    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    printf("Sign-up successful!\n");
}

void signin() {
    char username[MAX_LENGTH], password[MAX_LENGTH];
    char fileUsername[MAX_LENGTH], filePassword[MAX_LENGTH];
    int authenticated = 0;

    FILE *file = fopen(userFile, "r");
    if (file == NULL) {
        printf("Error opening file for sign-in!\n");
        return;
    }

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            authenticated = 1;
            break;
        }
    }
    fclose(file);

    if (authenticated) {
        printf("Login successful!\n");
        int difficulty;
        int topicChoice;
        int lives = 3;

        while (lives > 0) {
            printf("\nSelect Topic:\n");
            for (int i = 0; i < sizeof(topics) / sizeof(topics[0]); i++) {
                printf("%d. %s\n", i + 1, topics[i]);
            }
            printf("Enter your choice: ");
            scanf("%d", &topicChoice);

            if (topicChoice < 1 || topicChoice > sizeof(topics) / sizeof(topics[0])) {
                printf("Invalid topic choice!\n");
                continue;
            }

            printf("\nSelect Difficulty Level:\n");
            printf("1. Easy\n");
            printf("2. Moderate\n");
            printf("3. Difficult\n");
            printf("Enter your choice: ");
            scanf("%d", &difficulty);

            playGame(difficulty, topics[topicChoice - 1], &lives);

            if (lives > 0) {
                printf("Do you want to play another game? (yes=1 / no=0): ");
                int playAgain;
                scanf("%d", &playAgain);
                if (!playAgain) {
                    break;
                }
            }
        }

        if (lives == 0) {
            printf("\nYou are out of lives! Logging out.\n");
        }
    } else {
        printf("Invalid username or password.\n");
    }
}

void playGame(int difficulty, const char *topic, int *lives) {
    char filename[MAX_LENGTH];
    snprintf(filename, sizeof(filename), "%s_%s.txt", topic,
             difficulty == 1 ? "easy" : (difficulty == 2 ? "moderate" : "difficult"));

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for playing game!\n");
        return;
    }

    Question question;
    int score = 0;
    char answer;
    int points = (difficulty == 1) ? 100 : ((difficulty == 2) ? 200 : 300);

    printf("\n--- Quiz Game ---\n");
    while (fgets(question.question, MAX_LENGTH, file) && *lives > 0) {
        question.question[strcspn(question.question, "\n")] = 0;

        for (int i = 0; i < 4; i++) {
            fgets(question.options[i], MAX_LENGTH, file);
            question.options[i][strcspn(question.options[i], "\n")] = 0;
        }
        fscanf(file, "%c\n", &question.correctOption);

        printf("\n%s\n", question.question);
        for (int i = 0; i < 4; i++) {
            printf("%d. %s\n", i + 1, question.options[i]);
        }
        printf("Enter your answer (1-4): ");
        scanf(" %c", &answer);

        if (answer == question.correctOption) {
            printf("Correct! You earned %d points.\n", points);
            score += points;
        } else {
            printf("Wrong! The correct answer was option %c.\n", question.correctOption);
            (*lives)--;
            printf("You lost a life. Lives remaining: %d\n", *lives);
        }
        printf("Current score: %d\n", score);
    }
    fclose(file);

    if (*lives == 0) {
        printf("\nGame over! You have no lives left.\n");
    }
    printf("Your final earned score is: %d\n", score);
}

void adminLogin() {
    char adminUsername[MAX_LENGTH] = "admin";
    char adminPassword[MAX_LENGTH] = "admin123";
    char username[MAX_LENGTH], password[MAX_LENGTH];

    printf("Enter admin username: ");
    scanf("%s", username);
    printf("Enter admin password: ");
    scanf("%s", password);

    if (strcmp(username, adminUsername) == 0 && strcmp(password, adminPassword) == 0) {
        printf("Admin login successful!\n");
        int choice, difficulty, topicChoice;

        while (1) {
            printf("\n--- Admin Menu ---\n");
            printf("1. Add Question\n");
            printf("2. Remove Question\n");
            printf("3. Add User\n");
            printf("4. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("\nSelect Topic:\n");
                    for (int i = 0; i < sizeof(topics) / sizeof(topics[0]); i++) {
                        printf("%d. %s\n", i + 1, topics[i]);
                    }
                    printf("Enter your choice: ");
                    scanf("%d", &topicChoice);

                    if (topicChoice < 1 || topicChoice > sizeof(topics) / sizeof(topics[0])) {
                        printf("Invalid topic choice!\n");
                        break;
                    }

                    printf("\nSelect Difficulty Level:\n");
                    printf("1. Easy\n");
                    printf("2. Moderate\n");
                    printf("3. Difficult\n");
                    printf("Enter your choice: ");
                    scanf("%d", &difficulty);

                    addQuestion(difficulty, topics[topicChoice - 1]);
                    break;

                case 2:
                    printf("\nSelect Topic:\n");
                    for (int i = 0; i < sizeof(topics) / sizeof(topics[0]); i++) {
                        printf("%d. %s\n", i + 1, topics[i]);
                    }
                    printf("Enter your choice: ");
                    scanf("%d", &topicChoice);

                    if (topicChoice < 1 || topicChoice > sizeof(topics) / sizeof(topics[0])) {
                        printf("Invalid topic choice!\n");
                        break;
                    }

                    printf("\nSelect Difficulty Level:\n");
                    printf("1. Easy\n");
                    printf("2. Moderate\n");
                    printf("3. Difficult\n");
                    printf("Enter your choice: ");
                    scanf("%d", &difficulty);

                    removeQuestion(difficulty, topics[topicChoice - 1]);
                    break;

                case 3:
                    addUser();
                    break;

                case 4:
                    printf("Logging out...\n");
                    return;

                default:
                    printf("Invalid choice!\n");
            }
        }
    } else {
        printf("Invalid admin credentials.\n");
    }
}

void addQuestion(int difficulty, const char *topic) {
    Question question;
    char filename[MAX_LENGTH];
    snprintf(filename, sizeof(filename), "%s_%s.txt", topic,
             difficulty == 1 ? "easy" : (difficulty == 2 ? "moderate" : "difficult"));

    FILE *file = fopen(filename, "a+");
    if (file == NULL) {
        printf("Error opening file for adding question!\n");
        return;
    }

    int questionCount = 0;
    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        questionCount++;
    }

    if (questionCount >= MAX_QUESTIONS * 6) {
        printf("This difficulty level already has %d questions.\n", MAX_QUESTIONS);
        fclose(file);
        return;
    }

    printf("Enter the question: ");
    getchar(); // Clear trailing newline
    fgets(question.question, MAX_LENGTH, stdin);
    question.question[strcspn(question.question, "\n")] = 0;

    for (int i = 0; i < 4; i++) {
        printf("Enter option %d: ", i + 1);
        fgets(question.options[i], MAX_LENGTH, stdin);
        question.options[i][strcspn(question.options[i], "\n")] = 0;
    }

    printf("Enter the correct option (1-4): ");
    scanf(" %c", &question.correctOption);

    fprintf(file, "%s\n", question.question);
    for (int i = 0; i < 4; i++) {
        fprintf(file, "%s\n", question.options[i]);
    }
    fprintf(file, "%c\n", question.correctOption);

    fclose(file);
    printf("Question added successfully!\n");
}

void removeQuestion(int difficulty, const char *topic) {
    char filename[MAX_LENGTH];
    snprintf(filename, sizeof(filename), "%s_%s.txt", topic,
             difficulty == 1 ? "easy" : (difficulty == 2 ? "moderate" : "difficult"));

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for removing question!\n");
        return;
    }

    Question questions[MAX_QUESTIONS];
    int questionCount = 0;

    while (fgets(questions[questionCount].question, MAX_LENGTH, file)) {
        questions[questionCount].question[strcspn(questions[questionCount].question, "\n")] = 0;
        for (int i = 0; i < 4; i++) {
            fgets(questions[questionCount].options[i], MAX_LENGTH, file);
            questions[questionCount].options[i][strcspn(questions[questionCount].options[i], "\n")] = 0;
        }
        fscanf(file, " %c\n", &questions[questionCount].correctOption);
        questionCount++;
    }
    fclose(file);

    if (questionCount == 0) {
        printf("No questions available to remove.\n");
        return;
    }

    printf("\nSelect the question to remove:\n");
    for (int i = 0; i < questionCount; i++) {
        printf("%d. %s\n", i + 1, questions[i].question);
    }

    int questionChoice;
    printf("Enter your choice: ");
    scanf("%d", &questionChoice);

    if (questionChoice < 1 || questionChoice > questionCount) {
        printf("Invalid choice!\n");
        return;
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < questionCount; i++) {
        if (i == questionChoice - 1)
            continue;
        fprintf(file, "%s\n", questions[i].question);
        for (int j = 0; j < 4; j++) {
            fprintf(file, "%s\n", questions[i].options[j]);
        }
        fprintf(file, "%c\n", questions[i].correctOption);
    }

    fclose(file);
    printf("Question removed successfully!\n");
}

void addUser() {
    signUp();
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Quiz Game Menu ---\n");
        printf("1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. Admin Login\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            break;
        }

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                signin();
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}