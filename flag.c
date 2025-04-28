#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ENCRYPTED_FILE "encrypted.bin"
#define KEY_LENGTH 8

int main() {
    FILE *fp;
    long file_size;
    unsigned char *encrypted_data;
    unsigned char key[KEY_LENGTH] = {0};

    char key_phrase[] = "CIPHER";
    for (int i = 0; i < 6 && i < KEY_LENGTH; i++) {
        key[i] = (unsigned char)key_phrase[i];
    }

    fp = fopen(ENCRYPTED_FILE, "rb");
    if (fp == NULL) {
        perror("Error opening encrypted file"); 
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    encrypted_data = (unsigned char *)malloc(file_size);
    if (encrypted_data == NULL) {
        perror("Error allocating memory");
        fclose(fp);  
        return 1;
    }
    fread(encrypted_data, 1, file_size, fp);
    fclose(fp);

    printf("Decrypted Message: ");
    for (long i = 0; i < file_size; i++) {
        printf("%c", encrypted_data[i] ^ key[i % KEY_LENGTH]);
    }
    printf("\n");

    free(encrypted_data);
    return 0;
}
