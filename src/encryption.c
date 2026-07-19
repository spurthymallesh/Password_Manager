#include "../include/password_manager.h"

#include <openssl/evp.h>
#include <string.h>

static const unsigned char iv[AES_IV_SIZE] =
{
    0x00,0x01,0x02,0x03,
    0x04,0x05,0x06,0x07,
    0x08,0x09,0x0A,0x0B,
    0x0C,0x0D,0x0E,0x0F
};

int aes_encrypt(const char *plaintext,
                const unsigned char *key,
                unsigned char *ciphertext,
                int *cipher_len)
{
    EVP_CIPHER_CTX *ctx;

    int len;
    int total_len;

    ctx = EVP_CIPHER_CTX_new();

    if(ctx == NULL)
        return FAILURE;

    if(EVP_EncryptInit_ex(ctx,
                          EVP_aes_256_cbc(),
                          NULL,
                          key,
                          iv) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }

    if(EVP_EncryptUpdate(ctx,
                         ciphertext,
                         &len,
                         (unsigned char *)plaintext,
                         strlen(plaintext)) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }

    total_len = len;

    if(EVP_EncryptFinal_ex(ctx,
                           ciphertext + len,
                           &len) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }

    total_len += len;

    *cipher_len = total_len;

    EVP_CIPHER_CTX_free(ctx);

    return SUCCESS;
}

int aes_decrypt(const unsigned char *ciphertext,
                int cipher_len,
                const unsigned char *key,
                char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;
    int total_len;

    ctx = EVP_CIPHER_CTX_new();

    if(ctx == NULL)
        return FAILURE;

    if(EVP_DecryptInit_ex(ctx,
                          EVP_aes_256_cbc(),
                          NULL,
                          key,
                          iv) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }

    if(EVP_DecryptUpdate(ctx,
                         (unsigned char *)plaintext,
                         &len,
                         ciphertext,
                         cipher_len) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }

    total_len = len;

    if(EVP_DecryptFinal_ex(ctx,
                           (unsigned char *)plaintext + len,
                           &len) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        return FAILURE;
    }

    total_len += len;

    plaintext[total_len] = '\0';

    EVP_CIPHER_CTX_free(ctx);

    return SUCCESS;
}


void test_aes(void)
{
    unsigned char key[AES_KEY_SIZE] =
    {
        0,1,2,3,4,5,6,7,
        8,9,10,11,12,13,14,15,
        16,17,18,19,20,21,22,23,
        24,25,26,27,28,29,30,31
    };

    char plain[] = "Spurthy@123";

    unsigned char cipher[128];
    unsigned char cipher2[128];

    char hex[256];
    char output[128];

    int len;
    int len2;

    aes_encrypt(plain,
                key,
                cipher,
                &len);

    bytes_to_hex(cipher,
                 len,
                 hex);

    printf("\nHEX : %s\n", hex);

    len2 = hex_to_bytes(hex,
                        cipher2);

    aes_decrypt(cipher2,
                len2,
                key,
                output);

    printf("Plain : %s\n", plain);
    printf("After : %s\n", output);
}

void bytes_to_hex(const unsigned char *bytes, int len, char *hex)
{
    for(int i = 0; i < len; i++)
    {
        sprintf(hex + (i * 2), "%02X", bytes[i]);
    }

    hex[len * 2] = '\0';
}

int hex_to_bytes(const char *hex, unsigned char *bytes)
{
    int len = strlen(hex);

    if(len % 2 != 0)
        return FAILURE;

    for(int i = 0; i < len / 2; i++)
    {
        sscanf(hex + (2 * i), "%2hhx", &bytes[i]);
    }

    return len / 2;
}