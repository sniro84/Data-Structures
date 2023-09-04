/************************************************ 
EXERCISE      : DHCP
Implmented by : Snir Holland
Reviewed by   : 
Date          : 22/6/23
File          : dhcp_test.c
*************************************************/

#include <stdio.h>  /* printf */
#include <string.h> /* strcmp */

#include "dhcp.h"

void TestDHCPCreate();
void TestDHCPDestroy();
void TestDHCPCountFree();
void TestDHCPAllocateIp();
void TestDHCPFree();

int main()
{
	TestDHCPCreate();

 	TestDHCPDestroy();

	TestDHCPCountFree();

	TestDHCPAllocateIp();

	TestDHCPFree(); 

	return 0;
}

void TestDHCPCreate()
{
	dhcp_t *dhcp = NULL;
    unsigned char subnet_ip[4] = {198, 5, 1, 0};
    size_t bits_in_subnet = 8;
    size_t available_ips = 256 - 3;

    printf("--------Testing DHCPCreate()--------\t");

    dhcp = DHCPCreate(subnet_ip, bits_in_subnet);
    
	(available_ips == DHCPCountFree(dhcp)) ? printf("Success\n") : printf("Failure\n");

    DHCPDestroy(dhcp);
}

void TestDHCPDestroy()
{
	dhcp_t *dhcp = NULL;
    unsigned char subnet_ip[4] = {198, 5, 1, 0};
    size_t bits_in_subnet = 8;

    printf("--------Testing DHCPDestroy()--------\t");

    dhcp = DHCPCreate(subnet_ip, bits_in_subnet);
    
    DHCPDestroy(dhcp);

	/* checks will be done through valgrind */
	printf("Success\n");
}

void TestDHCPAllocateIp()
{
	dhcp_t *dhcp = NULL;
    size_t num_of_bits = 8;

    unsigned char ip_ddr1[4] = {192, 5, 1, 13};
    unsigned char ip_ddr2[4] = {192, 5, 1, 14};

    unsigned char res_addr1[4] = {0, 0, 0, 0};
    unsigned char res_addr2[4] = {0, 0, 0, 0};

	printf("--------Testing DHCPAllocateIp()-------\t");

    dhcp = DHCPCreate(ip_ddr1, num_of_bits);

    DHCPAllocateIp(dhcp, ip_ddr1, res_addr1);
    DHCPAllocateIp(dhcp, ip_ddr1, res_addr2);

    (0 == memcmp(ip_ddr2, res_addr2, 4)) ? printf("Success\n") : printf("Failure\n");

    DHCPDestroy(dhcp);
}

void TestDHCPFree()
{
	dhcp_t *dhcp = NULL;
    size_t num_of_bits = 8;

	size_t test_count = 3;

    unsigned char ip_ddr1[4] = {192, 5, 1, 13};
    unsigned char ip_ddr2[4] = {192, 5, 1, 14};

    unsigned char ip_ddr3_not_exist[4] = {168, 4, 1, 22};

    unsigned char res_addr1[4] = {0, 0, 0, 0};
    unsigned char res_addr2[4] = {0, 0, 0, 0};

	printf("--------Testing DHCPFree()-------\t");

    dhcp = DHCPCreate(ip_ddr1, num_of_bits);

    DHCPAllocateIp(dhcp, ip_ddr1, res_addr1);
    DHCPAllocateIp(dhcp, ip_ddr2, res_addr2);

    (DHCP_SUCCESS == DHCPFree(dhcp, res_addr1)) ? --test_count : test_count;
    (DHCP_DOUBLE_FREE == DHCPFree(dhcp, res_addr1)) ? --test_count : test_count;
    (DHCP_FAILURE == DHCPFree(dhcp, ip_ddr3_not_exist)) ? --test_count : test_count;

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

    DHCPDestroy(dhcp);
}

void TestDHCPCountFree()
{
	dhcp_t *dhcp = NULL;
    unsigned char subnet_ip[4] = {198, 5, 1, 0};
    size_t bits_in_subnet = 8;
    size_t available_ips = 256 - 3 - 2;

    unsigned char ip_ddr1[4] = {192, 5, 1, 13};
    unsigned char ip_ddr2[4] = {192, 5, 1, 14};

    unsigned char res_addr1[4] = {0, 0, 0, 0};
    unsigned char res_addr2[4] = {0, 0, 0, 0};

    printf("--------Testing DHCPCountFree()--------\t");

    dhcp = DHCPCreate(subnet_ip, bits_in_subnet);

    DHCPAllocateIp(dhcp, ip_ddr1, res_addr1);
    DHCPAllocateIp(dhcp, ip_ddr2, res_addr2);

	(available_ips == DHCPCountFree(dhcp)) ? printf("Success\n") : printf("Failure\n");

    DHCPDestroy(dhcp);
}

