#include <stdio.h>
#include <stdint.h>

void binaryform(unsigned char a, unsigned char binary[8]) {
    int i;
    for (i = 7; i >= 0; i--) {
        binary[i] = a % 2;
        a /= 2;
    }
}

void xor_data(unsigned char binary[8], unsigned char r_data[8]) {
    int i;
    unsigned char xorwith69[8] = {0, 1, 1, 0, 1, 0, 0, 1}; // Binary representation of 0x69
    unsigned char xorwith59[8] = {0, 1, 0, 1, 1, 0, 0, 1}; // Binary representation of 0x59
    
    // XOR with 0x69
    for (i = 0; i < 8; i++) {
        binary[i] ^= xorwith69[i];
    }
    // XOR with 0x59
    for (i = 0; i < 8; i++) {
        r_data[i] = binary[i] ^ xorwith59[i];
    }
}

int binarytodecimal(unsigned char r_data[8]) {
    int val = 0, i;
    for (i = 0; i < 8; i++) {
        val += r_data[7 - i] * (1 << i); // Convert binary to decimal
    }
    return val;
}

void scrumble(unsigned char data_in[20], unsigned char data_out1[20]) {
    int i;
    unsigned char binary[8], r_data[8];
    for (i = 0; i < 20; i++) {
        binaryform(data_in[i], binary); // Convert byte to binary
        xor_data(binary, r_data);      // Perform XOR operations
        data_out1[i] = binarytodecimal(r_data); // Convert back to decimal
    }
}

void descrumble(unsigned char data_out1[20], unsigned char data_out2[20]) {
    scrumble(data_out1, data_out2); // Scrambling is reversible, so apply it again
}

int main() {
    int i;
    unsigned char data_in[20] = {0x21, 0x22, 0x23, 0x24, 0x25, 0x4E, 0x4A, 0x27, 0x28, 0x30, 
                                 0x32, 0x45, 0x29, 0x19, 0x38, 0x23, 0x24, 0x25, 0x14, 0x50};
    unsigned char data_out1[20], data_out2[20];

    // Display original input
    printf("Original Data:\n");
    for (i = 0; i < 20; i++) {
        printf("%02X ", data_in[i]);
    }
    printf("\n");

    // Scramble data
    scrumble(data_in, data_out1);

    // Display scrambled data
    printf("Scrambled Data:\n");
    for (i = 0; i < 20; i++) {
        printf("%02X ", data_out1[i]);
    }
    printf("\n");

    // Descramble data
    descrumble(data_out1, data_out2);

    // Display descrambled data
    printf("Descrambled Data:\n");
    for (i = 0; i < 20; i++) {
        printf("%02X ", data_out2[i]);
    }
    printf("\n");

    return 0;
}

