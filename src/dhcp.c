/************************************************ 
EXERCISE      : DHCP
Implmented by : Snir Holland
Reviewed by   : 
Date          : 
File          : dhcp.c
*************************************************/

#include <assert.h>   /* assert */
#include <stdlib.h>   /* malloc, free */
#include <string.h>   /* memcpy */
#include <limits.h>   /* CHAR_BIT */

#include "dhcp.h"

#define MASK 1

enum addresses
{
    NETWORK_ADDRESS,
    SERVER_ADDRESS,
    BROADCAST_ADDRESS,
    TOTAL_RESTRICTED_ADDRESSES,
    ADDRESS_BUFFER
};

/* Helper function: returns 2 to the power of an exponent */
static size_t PowerWithBaseTwo(size_t exp);

/* Helper function: convert a string in decimal form to binary and stores result */
static void DecimalToBinary(char *dest, char *src, size_t len);

/* Helper function: convert a string in binary form to decimal and stores result */
static void BinaryToDecimal(unsigned char *dest, unsigned char *src, size_t len);

/* Helper function: insert restricted ip addresses into the dhcp */
static dhcp_status_t PreallocateRestrictedIps(dhcp_t *dhcp);

/* -------------- DHCPCreate -------------- */
dhcp_t *DHCPCreate(const unsigned char subnet_ip[IPV], size_t host_size)
{
    dhcp_t *dhcp = NULL;

    assert(NULL != subnet_ip);
    assert(0 != host_size);

    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if (NULL == dhcp)
    {
        return NULL;
    }

    dhcp->addresses = TrieCreate(host_size);
    if (NULL == dhcp->addresses)
    {
        free(dhcp);
        return NULL;
    }

    memcpy(dhcp->subnet_ip, subnet_ip, IPV);
    dhcp->host_size = host_size;

    if (DHCP_SUCCESS != PreallocateRestrictedIps(dhcp))
    {
        TrieDestroy(dhcp->addresses);
        free(dhcp);
        return NULL;
    }

    return dhcp;
}

/* -------------- DHCPDestroy -------------- */
void DHCPDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);

    TrieDestroy(dhcp->addresses);
    dhcp->addresses = NULL;

    free(dhcp);
}

/* -------------- DHCPDHCPAllocateIp -------------- */
dhcp_status_t DHCPAllocateIp(dhcp_t *dhcp, const unsigned char Ip[IPV], unsigned char result[IPV])
{
    unsigned char ip_binary[IPV * CHAR_BIT + 1] = {0};
    unsigned char *host_binary = NULL;
    unsigned char subnet_binary[IPV * CHAR_BIT + 1] = {0};
    unsigned char result_binary[IPV * CHAR_BIT + 1] = {0};

    assert(NULL != dhcp);

    DecimalToBinary((char *)ip_binary, (char *)Ip, IPV);
    DecimalToBinary((char *)subnet_binary, (char *)dhcp->subnet_ip, IPV);

    host_binary = ip_binary + (IPV * CHAR_BIT - dhcp->host_size);

    if (TRIE_SUCCESS != TrieInsert(dhcp->addresses, host_binary, result_binary))
    {
        return DHCP_FAILURE;
    }

    host_binary = subnet_binary + (IPV * CHAR_BIT - dhcp->host_size);

    memcpy(host_binary, result_binary, dhcp->host_size);

    BinaryToDecimal(result, subnet_binary, IPV);

    return DHCP_SUCCESS;
}

/* -------------- DHCPFree -------------- */
dhcp_status_t DHCPFree(dhcp_t *dhcp, const unsigned char Ip[IPV])
{
    unsigned char ip_binary[IPV * CHAR_BIT + 1] = {0};
    unsigned char *host_binary = NULL;
    unsigned char subnet_binary[IPV * CHAR_BIT + 1] = {0};

    assert(NULL != dhcp);

    DecimalToBinary((char *)ip_binary, (char *)Ip, IPV);
    DecimalToBinary((char *)subnet_binary, (char *)dhcp->subnet_ip, IPV);

    if (0 != strncmp((char *)subnet_binary, (char *)ip_binary, (IPV * CHAR_BIT - dhcp->host_size)))
    {
        return DHCP_FAILURE;
    }

    host_binary = ip_binary + (IPV * CHAR_BIT - dhcp->host_size);

    if (TRIE_NOT_FOUND == TrieRemove(dhcp->addresses, host_binary))
    {
        return DHCP_DOUBLE_FREE;
    }

    return DHCP_SUCCESS;
}

/* -------------- DHCPCountFree -------------- */
size_t DHCPCountFree(const dhcp_t *dhcp)
{
    assert(NULL != dhcp);

    return PowerWithBaseTwo(dhcp->host_size) - TrieCount(dhcp->addresses);
}

/* --------------- Static Functions ----------------- */

static dhcp_status_t PreallocateRestrictedIps(dhcp_t *dhcp)
{
    unsigned char addresses[TOTAL_RESTRICTED_ADDRESSES + 1][IPV] =
    {
		 {0x00, 0x00, 0x00, 0x00},
         {0xFF, 0xFF, 0xFF, 0xFE},
         {0xFF, 0xFF, 0xFF, 0xFF},
         {ADDRESS_BUFFER}
	};

    size_t i = 0;

    for (i = 0; i < TOTAL_RESTRICTED_ADDRESSES; ++i)
    {
        if (DHCP_SUCCESS != DHCPAllocateIp(dhcp, addresses[i], addresses[TOTAL_RESTRICTED_ADDRESSES]))
        {
            return DHCP_FAILURE;
        }
    }

    return DHCP_SUCCESS;
}

static void DecimalToBinary(char *dest, char *src, size_t len)
{
    char ch = 0;
    size_t i = 0;
    int j = 0;

    assert(NULL != src);

    for (i=0; i<len; ++i)
    {
        ch = *src;
        for (j=CHAR_BIT-1; j >= 0; --j)
        {
            if (ch & (1 << j))
            {
                *dest = '1';
            }
            else
            {
                *dest = '0';
            }
            ++dest;
        }
        ++src;
    }
    *dest = '\0';
}

static void BinaryToDecimal(unsigned char *dest, unsigned char *src, size_t len)
{
    size_t i = 0;
    int j = 0;

    assert(NULL != dest);
    assert(NULL != src);

    for (i = 0; i < len; ++i)
    {
        for (j = CHAR_BIT - 1; j >= 0; --j)
        {
            if ('1' == (*src)) 
            {
                *dest |= MASK << j;
            }
            else
            {
                *dest &= ~(MASK << j);
            }

            ++src;
        }
        ++dest;
    }
}

static size_t PowerWithBaseTwo(size_t exp)
{
	return 1 << exp;
}
