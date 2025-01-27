#include <stdio.h>

// Function to convert a byte into its binary representation
void binaryform(unsigned char a, unsigned char binary[8]) {
    int i;
    for (i = 7; i >= 0; i--) {
        binary[i] = a % 2;
        a /= 2;
    }
}

// Function to perform bit replacement (bit stuffing)
void replacement(unsigned char binary[8], unsigned char arr1[9], int *len) {
    int count = 0;
    int k = 0;
    int i;
    for (i = 0; i < 8; i++) {
        arr1[k++] = binary[i]; // Add the current bit to `arr1`
        if (binary[i] == 1) {
            count++;
            if (count == 5) { // Insert a stuffed bit if 5 consecutive 1s are found
                arr1[k++] = 0;
                count = 0;
            }
        } else {
            count = 0; // Reset the count if the bit is 0
        }
    }
    *len = k; // Update the length of the stuffed array
}

void byte_stuffing(unsigned char a[22], unsigned char b[22 * 10], int *b_len) {
    unsigned char binary[8];
    unsigned char arr1[9];
    int k = 0;
    int i, j;
    for (i = 0; i < 22; i++) {
        binaryform(a[i], binary);
        int stuffed_len = 0;
        replacement(binary, arr1, &stuffed_len);

        for (j = 0; j < stuffed_len; j++) {
            b[k++] = arr1[j];
        }
    }
    *b_len = k;
}

void reverse_byte_stuffing(unsigned char b[22 * 10], unsigned char c[22 * 8], int b_len, int *c_len) {
    int i;
    int count = 0;
    int k = 0;

    for (i = 0; i < b_len; i++) {
        c[k++] = b[i]; 
        if (b[i] == 1) {
            count++;
            if (count == 5) { 
                if (i + 1 < b_len && b[i + 1] == 0) {
                    i++;
                }
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    *c_len = k;
}

int main() {
    int i;h)
    unsigned char a[22] = {
        0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E,
        0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E
    };
    

    unsigned char b[22 * 10]; 
    int b_len = 0;
    byte_stuffing(a, b, &b_len);
    printf("Stuffed binary array:\n");
    for (i = 0; i < b_len; i++) {
        printf("%d", b[i]);
        if((i+1)%8==0){
        	printf(" ");
		}
    }
    printf("\n");
    unsigned char c[22 * 8]; 
    int c_len = 0;
    reverse_byte_stuffing(b, c, b_len, &c_len);
    printf("Original binary array after reverse stuffing:\n");
    for (i = 0; i < c_len; i++) {
        printf("%d", c[i]);
        if((i+1)%8==0){
        	printf(" ");
		}
    }
    printf("\n");

    return 0;
}

