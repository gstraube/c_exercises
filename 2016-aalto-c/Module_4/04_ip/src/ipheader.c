#include <stdio.h>
#include <arpa/inet.h>
#include "ipheader.h"


/* Parses the given buffer into an IP header structure.
 * 
 * Parameters:
 * ip: pointer to the IP header structure that will be filled based
 *      on the data in the buffer
 * buffer: buffer of 20 bytes that contain the IP header. */
void parseIp(struct ipHeader *ip, const void *buffer)
{
	const unsigned char *header_ptr = buffer;
	
	unsigned short total_length = 0;
	total_length |= header_ptr[2] << 8;
	total_length |= header_ptr[3];

	unsigned short identification = 0;
	identification |= header_ptr[4] << 8;
	identification |= header_ptr[5];

	unsigned short fragment_offset = 0;
	fragment_offset |= (header_ptr[6] & 31) << 8;
	fragment_offset |= header_ptr[7];

	unsigned short header_checksum = 0;
	header_checksum |= header_ptr[10] << 8;
	header_checksum |= header_ptr[11];

	ip->version = header_ptr[0] >> 4;
	ip->ihl = (header_ptr[0] & 0xf) * 4;
	ip->dscp = header_ptr[1] >> 2;
	ip->ecn = (header_ptr[1] & 3);
	ip->length = total_length;
	ip->identification = identification;
	ip->flags = header_ptr[6] >> 5;
	ip->fragment_offset = fragment_offset; 
	ip->time_to_live = header_ptr[8];
	ip->protocol = header_ptr[9];
	ip->header_checksum = header_checksum;
	ip->source_ip[0] = header_ptr[12];
	ip->source_ip[1] = header_ptr[13];
	ip->source_ip[2] = header_ptr[14];
	ip->source_ip[3] = header_ptr[15];
	ip->destination_ip[0] = header_ptr[16];
	ip->destination_ip[1] = header_ptr[17];
	ip->destination_ip[2] = header_ptr[18];
	ip->destination_ip[3] = header_ptr[19];
}


/* Builds a 20-byte byte stream based on the given IP header structure
 * 
 * Parameters:
 * buffer: pointer to the 20-byte buffer to which the header is constructed
 * ip: IP header structure that will be packed to the buffer */
void sendIp(void *buffer, const struct ipHeader *ip)
{
	unsigned char *header_ptr = buffer;
	header_ptr[0] = ((ip->version << 4) | 0) | (ip->ihl / 4);
	header_ptr[1] = (ip->dscp << 2 | 0) | ip->ecn;
	header_ptr[2] = ip->length >> 8;
	header_ptr[3] = ip->length & 0xff;
	header_ptr[4] = ip->identification >> 8;
	header_ptr[5] = ip->identification & 0xff;
	header_ptr[6] = ((ip->flags << 5) | 0) | (ip->fragment_offset >> 8);
	header_ptr[7] = ip->fragment_offset & 0xff;
	header_ptr[8] = ip->time_to_live;
	header_ptr[9] = ip->protocol;
	header_ptr[10] = ip->header_checksum >> 8;
	header_ptr[11] = ip->header_checksum & 0xff;
	header_ptr[12] = ip->source_ip[0];
	header_ptr[13] = ip->source_ip[1];
	header_ptr[14] = ip->source_ip[2];
	header_ptr[15] = ip->source_ip[3];
	header_ptr[16] = ip->destination_ip[0];
	header_ptr[17] = ip->destination_ip[1];
	header_ptr[18] = ip->destination_ip[2];
	header_ptr[19] = ip->destination_ip[3];
}


/* Prints the given IP header structure */
void printIp(const struct ipHeader *ip)
{
    /* Note: ntohs below is for converting numbers from network byte order
     to host byte order. You can ignore them for now
     To be discussed further in Network Programming course... */
    printf("version: %d   ihl: %d   dscp: %d   ecn: %d\n",
            ip->version, ip->ihl, ip->dscp, ip->ecn);
    printf("length: %d   id: %d   flags: %d   offset: %d\n",
            ntohs(ip->length), ntohs(ip->identification), ip->flags, ip->fragment_offset);
    printf("time to live: %d   protocol: %d   checksum: 0x%04x\n",
            ip->time_to_live, ip->protocol, ntohs(ip->header_checksum));
    printf("source ip: %d.%d.%d.%d\n", ip->source_ip[0], ip->source_ip[1],
            ip->source_ip[2], ip->source_ip[3]);
    printf("destination ip: %d.%d.%d.%d\n", ip->destination_ip[0],
            ip->destination_ip[1],
            ip->destination_ip[2], ip->destination_ip[3]);    
}

/* Shows hexdump of given data buffer */
void hexdump(const void *buffer, unsigned int length)
{
    const unsigned char *cbuf = buffer;
    unsigned int i;
    for (i = 0; i < length; ) {
        printf("%02x ", cbuf[i]);
        i++;
        if (!(i % 8))
            printf("\n");
    }
}
