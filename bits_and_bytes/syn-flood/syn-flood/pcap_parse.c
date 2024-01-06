#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
// PCAP file format: https://wiki.wireshark.org/Development/LibpcapFileFormat#libpcap-file-format

/*
 * Figure out what percentage of SYN packets were ACK'ed.
 * What was the server actually able to acknowledge?
 */
// Utility method to obtain a # of bytes from a buffer 
// and return a value in little endian
int toBigEndian(char* buffer, int startIndex, int numBytes) {
    char chars[numBytes];
    int c;
    int value = 0;
    for (int ii=startIndex; ii < startIndex + numBytes; ii++) {
        c = buffer[ii];
        chars[startIndex - ii] = c;
    }

    for (int ii=numBytes - 1; ii >= 0; ii--) {
        value ^= chars[ii];
        if (ii > 0) {
            value <<= 8;
        }
    }    
    return value;
}
// prevent padding this struct to 16 bytes which breaks things
typedef struct __attribute__((packed)) { 
    uint32_t magicNum;
    // The size of the BMP file in bytes
    uint16_t majorVersion;
    uint16_t minorVersion;
    
    // an unsigned value indicating the maximum number of octets captured from 
    // each packet. The portion of each packet that exceeds this value will not 
    // be stored in the file. This value MUST NOT be zero; if no limit was 
    // specified, the value should be a number greater than or equal to the 
    // largest packet length in the file
    uint32_t snapLen;
    // not used
    uint32_t reserved1; 
    // not used`
    uint32_t reserved2;
    uint16_t fcs;
    uint16_t linkType;
} GLOBALHEADER;

typedef struct {
    uint32_t tsSecs; // timestamp seconds
    uint32_t tsUsecs; // timestamp microseconds
    uint32_t capturedLen; // number of octets of packet saved in a file
    uint32_t origLen; // actual length of packet
} PACKETHEADER;

int main () 
{
    FILE* fp = fopen("synflood.pcap", "rb");
    /* File Header */
    GLOBALHEADER* fileHeader = malloc(sizeof(GLOBALHEADER));
    char* fileHeaderBuffer = malloc(sizeof(GLOBALHEADER));
    if (!fread(fileHeaderBuffer, sizeof(GLOBALHEADER), 1, fp)) {
        printf("Error reading file header");
    }    
    memcpy(fileHeader, fileHeaderBuffer, sizeof(GLOBALHEADER));
    assert(fileHeader->magicNum == 0xa1b2c3d4);
    // If the value is 0xA1B2C3D4, time stamps in Packet Records (see Figure 2) 
    // are in seconds and microseconds;
    assert(fileHeader->linkType == 0); // BSD loopback encapsulation
    int count = 0;
    int synCount = 0;
    int ackCount = 0;
    while (!feof(fp)) {
        /* Begin packet header */
        PACKETHEADER* packetHeader = malloc(sizeof(PACKETHEADER));
        char* packetHeaderBuffer = malloc(sizeof(PACKETHEADER));
        if (!fread(packetHeaderBuffer, sizeof(PACKETHEADER), 1, fp)) {
            break;
        }
        count++;
        memcpy(packetHeader, packetHeaderBuffer, sizeof(PACKETHEADER));
        // no bytes were dropped
        assert(packetHeader->capturedLen == packetHeader->origLen);
        
        char* packetBuffer = malloc(packetHeader->capturedLen);
        fread(packetBuffer, packetHeader->capturedLen, 1, fp);

        uint32_t protocolType = toBigEndian(packetBuffer, 0, 4);
        assert(protocolType == 2);
        
        uint8_t versionIHL = toBigEndian(packetBuffer, 4, 1);
        assert((versionIHL & 0x40) >> 4 == 4);
        uint8_t IHL = versionIHL & 0x05;
        assert( versionIHL & 0x05 == 5);

        // 6 is TCP
        uint32_t ipProtocol = toBigEndian(packetBuffer, 13, 1);
        assert(6 == ipProtocol);

        uint16_t tcp_offset = 24;
        uint16_t sourcePort = toBigEndian(packetBuffer, tcp_offset, 2);
        uint16_t destinationPort = toBigEndian(packetBuffer, tcp_offset + 2, 2);

        uint8_t flags = toBigEndian(packetBuffer, tcp_offset + 13, 1);
        if (flags == 2) { // SYN
            synCount++;
        } 
        if (flags == 18) { // ACK
            ackCount++;
        }
    }
    printf("Parsed %d packets\n", count);
    printf("SYN: %d, ACK: %d\n", synCount, ackCount);        
    printf("ACK'ed packet percentage %.2f\n", ((double)ackCount / (double)synCount) * 100);            
}