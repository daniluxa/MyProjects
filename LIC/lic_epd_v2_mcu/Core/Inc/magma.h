#ifndef MAGMA_H
#define MAGMA_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

extern uint8_t uzly[1024];
extern uint8_t invert_uzly[1024];

void One(uint32_t key, uint8_t *uz, uint32_t *ptr_a0, uint32_t *ptr_a1, uint8_t i);
//void One_Invert(uint32_t key, uint8_t *uz, uint32_t &a0, uint32_t &a1, unsigned int i);
void Simple_Cypher(uint32_t *key, uint8_t *uz, uint32_t *ptr);
//void Simple_DeCypher(uint32_t *key, uint8_t *uz, uint32_t *ptr);
void Simple_Cypher_Invert(uint32_t *key, uint8_t *uz, uint32_t *ptr);
//void Simple_DeCypher_Invert(uint32_t *key, uint8_t *uz, uint32_t *ptr);
uint8_t encrypt(uint8_t * plainData, uint8_t plainSize, uint8_t * encryptedData, uint8_t * encryptedSize);
uint8_t decrypt(uint8_t * encryptedData, uint8_t encryptedSize, uint8_t * plainData, uint8_t * plainSize);

static uint8_t CYPHER_COUNTER = 0;
static uint32_t Key[8] = { 0xffeeddcc, 0xbbaa9988, 0x77665544, 0x33221100,
0xf0f1f2f3, 0xf4f5f6f7, 0xf8f9fafb, 0xfcfdfeff };

//static uint32_t Plaintext[2] = { 0x76543210, 0xfedcba98 };
//static uint32_t Cyphertext[2] = { 0xc2d8ca3d, 0x4ee901e5 };

#endif
