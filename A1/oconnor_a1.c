#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* print_any_base(unsigned long num, unsigned int base)
{
    char chars[36] = "0123456789abcdefghijklmnopqrstuvwxyz";

    if(base < 2 || base > 36){
        printf("Invalid Base!!");
        return NULL;
    }

    unsigned long temp = num;
    int length = 0;

    while(temp > 0){
        temp /= base;
        length++;
    }

    // special case
    if(num == 0){
        length = 1;
    }

    char* result = (char*)malloc((length + 1) * sizeof(char));

    if(result == NULL){
        printf("Error: Failed to allocate memory.\n");
        return NULL;
    }

    // Convert the number to the base
    result[length] = '\0';
    while(num > 0){
        length--;
        result[length] = chars[num % base];
        num /= base;
    }

    return result;
}



unsigned int count_vowels(char *str)
{
    unsigned int count = 0;

    if(str == NULL){
        return 0; 
    }

    while(*str != '\0'){
        char currentChar = *str;
        switch(tolower(currentChar)) 
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                count++;
                break;
            default:
                break;
        }
        str++;
    }

    return count;
}

void reverse_string(char* str, int start, int end) 
{
    while(start < end){
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void reverse_words(char* str) 
{
    if(str == NULL){
        return;
    }

    int length = strlen(str);
    int start = 0;

    // Reverse the entire string
    reverse_string(str, 0, length - 1);

    // Reverse individual words
    for (int i = 0; i <= length; i++){
        if (str[i] == ' ' || str[i] == '\0'){
            reverse_string(str, start, i - 1);
            start = i + 1;
        }
    }
}

void rotate_string_in_place(char* str, unsigned int disp) 
{
    if(str == NULL){
        return;
    }

    for(int i = 0; str[i] != '\0'; i++){
        if(isalpha(str[i])){  // Check if alphabetic
            char base;
            if(islower(str[i])){
                base = 'a';
            } 
            else{
                base = 'A';
            }
            str[i] = (str[i] - base + disp) % 26 + base;  // Rotate the character
        }
    }
}
