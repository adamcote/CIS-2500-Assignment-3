/*
 * decode_lib.c
 * 
 * This file implements the Caesar cipher decoding functions declared in decode_lib.h.
 * It uses statistical analysis (chi-squared testing) to break the cipher by comparing
 * letter frequencies in the encoded text with known English letter frequencies.
 * 
 * Key Implementation Details:
 * 1. English Letter Frequencies: Stored in EF[] array (percentages of each letter in English text)
 * 2. Chi-Squared Analysis: Used to find the most likely shift value
 * 3. Character Encoding: Handles both uppercase and lowercase letters
 * 4. Memory Management: Properly allocates and frees frequency tables
 * 
 * The chi-squared test works by:
 * 1. Taking a guess at the shift value
 * 2. Applying that shift to the standard English frequencies
 * 3. Comparing the shifted expected frequencies with observed frequencies
 * 4. The shift that produces the smallest chi-squared value is likely the correct one
 */

#include "decode_lib.h"
#include "frequency_table.h"
#include <math.h>     /* For mathematical operations */
#include <stdlib.h>   /* For memory management */
#include <string.h>   /* For string operations */
#include <ctype.h>    /* For character type checking */
#include <stdio.h>    /* For debugging output */

/* 
 * English letter frequencies (as percentages) from most to least common:
 * E(12.7%), T(9.1%), A(8.2%), O(7.7%), I(7.0%), N(6.7%), S(6.3%), H(6.1%),
 * R(6.0%), D(4.3%), L(4.0%), C(2.8%), U(2.8%), M(2.4%), W(2.4%), F(2.2%),
 * G(2.0%), Y(2.0%), P(1.9%), B(1.5%), V(1.0%), K(0.8%), J(0.2%), X(0.2%),
 * Q(0.1%), Z(0.1%)
 */
double EF[26] = {
    0.08167,  /* A */ 0.01492,  /* B */ 0.02782,  /* C */ 0.04253,  /* D */
    0.12702,  /* E */ 0.02228,  /* F */ 0.02015,  /* G */ 0.06094,  /* H */
    0.06966,  /* I */ 0.00153,  /* J */ 0.00772,  /* K */ 0.04025,  /* L */
    0.02406,  /* M */ 0.06749,  /* N */ 0.07707,  /* O */ 0.01929,  /* P */
    0.00095,  /* Q */ 0.05987,  /* R */ 0.06327,  /* S */ 0.09056,  /* T */
    0.02758,  /* U */ 0.00978,  /* V */ 0.02360,  /* W */ 0.00150,  /* X */
    0.01974,  /* Y */ 0.00074   /* Z */
};

/*
 * encode
 * 
 * Purpose: Encodes a single character using Caesar cipher
 * 
 * Parameters:
 *   c     - The character to encode
 *   shift - How many positions to shift (0-25)
 * 
 * Returns:
 *   The encoded character, or the original character if not a letter
 * 
 * How it works:
 * 1. Convert character to uppercase for processing
 * 2. If it's a letter:
 *    - If shift doesn't wrap around alphabet, simply add shift
 *    - If shift wraps around, calculate new position from start of alphabet
 * 3. Preserve case (uppercase/lowercase) of original character
 * 
 * Example:
 *   encode('A', 3) returns 'D'
 *   encode('Z', 3) returns 'C'
 *   encode('a', 3) returns 'd'
 *   encode('!', 3) returns '!'
 */
char encode(char c, int shift) {
    int l = toupper(c);  /* Convert to uppercase for processing */
    int tot = shift;     /* Total shift to apply */
    
    if (isalpha(l)) {    /* Only process letters */
        if (l + shift <= 'Z') {
            /* Simple case: shift doesn't wrap around alphabet */
            c += shift;
        } else {
            /* Complex case: shift wraps around alphabet */
            tot -= offset('Z') - offset(l) + 1;  /* Calculate remaining shift */
            if (c == l) {
                /* Preserve uppercase */
                c = 'A' + tot;
            } else {
                /* Preserve lowercase */
                c = 'a' + tot;
            }
        }
    }
    return c;
}

/*
 * encode_string
 * 
 * Purpose: Encodes an entire string using Caesar cipher
 * 
 * Parameters:
 *   string - The string to encode (modified in place)
 *   shift  - How many positions to shift each letter
 * 
 * How it works:
 * 1. Process each character in the string
 * 2. Apply encode() function to each character
 * 3. Modify string in place
 */
void encode_string(char * string, int shift) {
    for (int i = 0; i < strlen(string); i++) {
        string[i] = encode(string[i], shift);
    }
}

/*
 * offset
 * 
 * Purpose: Converts a letter to its position in the alphabet (0-25)
 * 
 * Parameters:
 *   i - The letter to convert
 * 
 * Returns:
 *   Position in alphabet (0 for A/a, 1 for B/b, etc.)
 * 
 * How it works:
 * 1. For lowercase letters, subtract 'a' (97)
 * 2. For uppercase letters, subtract 'A' (65)
 * 3. Return the resulting offset
 * 
 * Example:
 *   offset('A') returns 0
 *   offset('b') returns 1
 *   offset('Z') returns 25
 */
int offset(char i) {
    if (i >= 'a' && i <= 'z') {
        return i - 97;  /* Convert lowercase to 0-25 */
    } else if (i >= 'A' && i <= 'Z') {
        return i - 65;  /* Convert uppercase to 0-25 */
    }
    return 0;  /* Default case (shouldn't happen with proper input) */
}

/*
 * to_decode
 * 
 * Purpose: Converts an encoding shift to a decoding shift
 * 
 * Parameters:
 *   shift - The shift used to encode the text
 * 
 * Returns:
 *   The shift needed to decode the text
 * 
 * How it works:
 * 1. If shift is 0, return 0 (no encoding/decoding needed)
 * 2. Otherwise, return (26 - shift)
 *    This works because shifting by 3 and then by 23 is the same as no shift
 * 
 * Example:
 *   to_decode(3) returns 23
 *   to_decode(25) returns 1
 *   to_decode(0) returns 0
 */
int to_decode(int shift) {
    if (shift == 0) {
        return 0;
    } else {
        return (26 - shift);  /* Convert encode shift to decode shift */
    }
}

/*
 * chi_sq
 * 
 * Purpose: Calculates chi-squared value for a given shift
 * 
 * Parameters:
 *   c     - The text to analyze
 *   shift - The shift value to test
 * 
 * Returns:
 *   Chi-squared value (lower is better match)
 * 
 * How it works:
 * 1. Get letter count and frequency table for input text
 * 2. For each letter in alphabet:
 *    - Calculate expected frequency (n * EF[letter])
 *    - Calculate observed frequency after applying shift
 *    - Add to sum: ((expected - observed)²) / (n * expected)
 * 3. Return final chi-squared value
 * 
 * The formula used is:
 * χ² = Σ((n * EF[c] - text_freq[encode(c,shift)])²) / (n * n * EF[c])
 * where:
 * - n is total letter count
 * - EF[c] is expected frequency of letter c
 * - text_freq[encode(c,shift)] is observed frequency after shift
 */
double chi_sq(char * c, int shift) {
    double sum = 0;  /* Running sum for chi-squared calculation */
    
    /* Get total letter count and frequency table */
    int n = letter_count(c);
    int * text_freq = frequency_table(c);
    if (text_freq == NULL) {
        return -1;  /* Error case */
    }
    
    /* Calculate chi-squared value for each letter */
    for (int ch = 0; ch < 26; ch++) {
        double expected = n * EF[offset('a' + ch)];
        double observed = text_freq[offset(encode('a' + ch, shift))];
        double diff = expected - observed;
        sum += (diff * diff) / (n * n * EF[offset('a' + ch)]);
    }
    
    free(text_freq);  /* Clean up frequency table */
    return sum;
}

/*
 * encode_shift
 * 
 * Purpose: Determines most likely shift used to encode the text
 * 
 * Parameters:
 *   c - The encoded text to analyze
 * 
 * Returns:
 *   The most likely shift value (0-25)
 * 
 * How it works:
 * 1. Try each possible shift (0-25)
 * 2. Calculate chi-squared value for each shift
 * 3. Remember the shift that gave the lowest chi-squared value
 * 4. Return that shift
 * 
 * Note: If the lowest chi-squared value is too high (>= 0.5),
 * the text might not be English, and 0 is returned.
 */
int encode_shift(char * c) {
    float value = -1;    /* Best chi-squared value found so far */
    float chi = 0;       /* Current chi-squared value */
    int num_shift = 0;   /* Shift that gave best value */
    
    /* Try each possible shift */
    for (int i = 0; i < 26; i++) {
        chi = chi_sq(c, i);
        if (value == -1 || value > chi) {
            value = chi;
            num_shift = i;
        }
    }
    
    /* If chi-squared value is too high, text might not be English */
    if (value >= 0.5) {
        return 0;
    }
    
    return num_shift;
}