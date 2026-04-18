#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================= NODE =================
struct Song {
    char title[50];
    char artist[50];
    int duration;
    struct Song* next;
    struct Song* prev;
};

// Pointers
struct Song* head = NULL;
struct Song* tail = NULL;
struct Song* current = NULL;

// ================= CHECK EMPTY =================
int isEmpty() {
    return head == NULL;
}

// ================= ADD (TAIL) =================
void addSong(char title[], char artist[], int duration) {
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));

    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->duration = duration;
    newSong->next = NULL;
    newSong->prev = NULL;

    if (isEmpty()) {
        head = tail = current = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    printf("-> Added: %s by %s\n", title, artist);
}

// ================= VIEW PLAYLIST =================
void viewPlaylist() {
    if (isEmpty()) {
        printf("Playlist is empty.\n");
        return;
    }

    struct Song* temp = head;
    int i = 1;

    printf("\n--- Playlist ---\n");

    while (temp != NULL) {
        if (temp == current)
            printf(">> "); // current song marker
        else
            printf("   ");

        printf("[%d] %s (%s) - %d sec\n",
               i++, temp->title, temp->artist, temp->duration);

        temp = temp->next;
    }

    printf("-----------------\n");
}

// ================= PLAY CURRENT =================
void playCurrent() {
    if (isEmpty()) {
        printf("Playlist is empty.\n");
        return;
    }

    printf("\n🎵 Now Playing: %s (%s)\n",
           current->title, current->artist);
}

// ================= NEXT SONG =================
void nextSong() {
    if (isEmpty()) return;

    if (current->next != NULL) {
        current = current->next;
        playCurrent();
    } else {
        printf("Already at last song.\n");
    }
}

// ================= PREVIOUS SONG =================
void prevSong() {
    if (isEmpty()) return;

    if (current->prev != NULL) {
        current = current->prev;
        playCurrent();
    } else {
        printf("Already at first song.\n");
    }
}

// ================= REMOVE CURRENT =================
void removeCurrent() {
    if (isEmpty()) {
        printf("Playlist is empty.\n");
        return;
    }

    struct Song* temp = current;

    printf("Removing: %s\n", temp->title);

    if (head == tail) {
        head = tail = current = NULL;
    }
    else if (current == head) {
        head = head->next;
        head->prev = NULL;
        current = head;
    }
    else if (current == tail) {
        tail = tail->prev;
        tail->next = NULL;
        current = tail;
    }
    else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        current = temp->next;
    }

    free(temp);
}

// ================= TOTAL DURATION =================
void totalDuration() {
    struct Song* temp = head;
    int total = 0;

    while (temp != NULL) {
        total += temp->duration;
        temp = temp->next;
    }

    printf("Total: %d sec (%d min %d sec)\n",
           total, total / 60, total % 60);
}

// ================= MAIN =================
int main() {

    // ===== 10 SONG LIBRARY =====
    char titles[10][50] = {
        "Shape of You", "Blinding Lights", "Perfect",
        "Someone Like You", "Levitating", "Stay",
        "Havana", "Senorita", "Bad Guy", "Counting Stars"
    };

    char artists[10][50] = {
        "Ed Sheeran", "The Weeknd", "Ed Sheeran",
        "Adele", "Dua Lipa", "Justin Bieber",
        "Camila Cabello", "Shawn Mendes",
        "Billie Eilish", "OneRepublic"
    };

    int durations[10] = {
        233, 200, 263, 285, 203,
        141, 217, 191, 194, 257
    };

    int choice, num;

    while (1) {

        printf("\n--- SONG LIBRARY ---\n");
        for (int i = 0; i < 10; i++) {
            printf("[%d] %s (%s)\n", i+1, titles[i], artists[i]);
        }

        printf("\nMENU:\n");
        printf("1. Add Song\n");
        printf("2. View Playlist\n");
        printf("3. Play Current\n");
        printf("4. Next Song\n");
        printf("5. Previous Song\n");
        printf("6. Remove Current\n");
        printf("7. Total Duration\n");
        printf("8. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter song number (1-10): ");
                scanf("%d", &num);

                if (num >= 1 && num <= 10) {
                    addSong(titles[num-1], artists[num-1], durations[num-1]);
                } else {
                    printf("Invalid.\n");
                }
                break;

            case 2:
                viewPlaylist();
                break;

            case 3:
                playCurrent();
                break;

            case 4:
                nextSong();
                break;

            case 5:
                prevSong();
                break;

            case 6:
                removeCurrent();
                break;

            case 7:
                totalDuration();
                break;

            case 8:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}