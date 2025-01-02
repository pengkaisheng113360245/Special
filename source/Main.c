#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// �w�]�m�߳�r�P�y�l
const char* easy_words[] = {
    "cat", "dog", "apple", "tree", "book", "sun", "moon", "star", "fish", "bird"
};

const char* medium_words[] = {
    "elephant", "computer", "keyboard", "universe", "giraffe", "mountain", "language", "sunflower", "diamond", "penguin"
};

const char* hard_words[] = {
    "pneumonia", "juxtaposition", "extraterrestrial", "hippopotamus", "conundrum", "antidisestablishmentarianism", "flabbergasted", "quintessential", "sesquipedalian", "kaleidoscope"
};

// �������
const char** choose_level(int* size) {
    int level;
    printf("\nChoose difficulty level: \n1. Easy\n2. Medium\n3. Hard\nEnter your choice (1-3): ");
    scanf_s("%d", &level);  // �ϥΦw������ scanf_s

    switch (level) {
    case 1:
        *size = sizeof(easy_words) / sizeof(easy_words[0]);
        return easy_words;
    case 2:
        *size = sizeof(medium_words) / sizeof(medium_words[0]);
        return medium_words;
    case 3:
        *size = sizeof(hard_words) / sizeof(hard_words[0]);
        return hard_words;
    default:
        printf("Invalid choice. Defaulting to Easy level.\n");
        *size = sizeof(easy_words) / sizeof(easy_words[0]);
        return easy_words;
    }
}

// Fisher-Yates �~�P��k
void shuffle(const char** array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        const char* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// �D�C���޿�
void typing_game(const char** words, int size) {
    srand((unsigned)time(NULL)); // �]�w�H���ؤl

    // �ϥΰʺA���t�s�x�~�P�᪺��r
    const char** shuffled_words = (const char**)malloc(size * sizeof(const char*));
    for (int i = 0; i < size; i++) {
        shuffled_words[i] = words[i];
    }

    // �~�P��r�}�C
    shuffle(shuffled_words, size);

    int correct_count = 0;
    int total_count = size < 5 ? size : 5; // ����̦h 5 �ӳ�r
    char input[100];

    printf("\nThe game begins! Type 'exit' anytime to quit.\n");

    // �O���}�l�ɶ�
    clock_t start_time = clock();

    for (int i = 0; i < total_count; i++) {
        const char* target_word = shuffled_words[i];
        printf("\nTarget: %s\nYour input: ", target_word);
        scanf_s("%99s", input, (unsigned)_countof(input)); // �ϥΦw������ scanf_s

        if (strcmp(input, "exit") == 0) {
            printf("Game exited early by user.\n");
            break;
        }

        if (strcmp(input, target_word) == 0) {
            printf("Correct!\n");
            correct_count++;
        }
        else {
            printf("Wrong! The correct word is: %s\n", target_word);
        }
    }

    // �O�������ɶ�
    clock_t end_time = clock();

    // �p�⥴�r�t�׻P���T�v
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    double accuracy = (double)correct_count / total_count * 100;

    printf("\nGame Over!\n");
    printf("Total time taken: %.2f seconds\n", time_taken);
    printf("Accuracy: %.2f%%\n", accuracy);

    // ����ʺA���t�����s
    free(shuffled_words);
}

int main() {
    printf("\nWelcome to the Typing Practice Game!\n");

    int size;
    const char** words = choose_level(&size);
    typing_game(words, size);

    printf("\nThank you for playing!\n");
    return 0;
}
