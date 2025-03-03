#include <stdio.h>
#include <stdlib.h>

// Custom implementation of strlen
int my_strlen(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

// Custom implementation of strcpy
void my_strcpy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
}

// Custom implementation of strcat
void my_strcat(char *dest, const char *src) {
    while (*dest != '\0') {
        dest++;
    }
    while (*src != '\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
}

char *concat(const char *s1, const char *s2) {
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (result == NULL) {
        return NULL;
    }
    my_strcpy(result, s1);
    my_strcat(result, s2);
    return result;
}

int main() {
    char s1[100], s2[100];
    printf("Enter two strings: ");
    scanf("%99s", s1);
    scanf("%99s", s2);

    char *result = concat(s1, s2);
    if (result != NULL) {
        printf("Concatenated string: %s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}
