void concat_strings(char *str1, const char *str2) {
    // Here, we create a new pointer called end and initialize it to point to the same location as str1. 
    // This pointer will be used to find the end of the first string.
    char end = str1;

    // *end means "the value that end is pointing to"
    // '\0' is the null character, which marks the end of a string in C
    // The loop continues as long as we haven't reached the null character
    // end++ moves the end pointer to the next character in the string

    // After this loop, end will be pointing to the null character at the end of str1.
    while (end != '\0') {
        end++;
    }

    // The loop continues as long as we haven't reached the end of str2
    // *end = *str2 copies the character that str2 is pointing to into the location that end is pointing to
    // end++ moves the end pointer to the next position in str1
    // str2++ moves the str2 pointer to the next character in str2
    
    while (*str2 != '\0') {
        *end = *str2;
        end++;
        str2++;
    }

    // add a null character to the end of the concatenated string to properly terminate it.
    *end = '\0';
}