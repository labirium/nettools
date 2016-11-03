#include <network/include/precompiled.h>

#include <pcap/pcap.h>
#include <network/include/icmpheader.h>

using namespace network::icmp;

namespace
{
/// @brief подсчет контрольной сумму для ICMP пакета
///
uint16_t in_cksum(void *addr, int len)
{
	int sum = 0;
	u_short answer = 0;
	u_short *w = (unsigned short *)addr;
	int nleft = len;
	
	// Algorithm is simple, using a 32 bit accumulator (sum), we add
	// sequential 16 bit words to it, and at the end, fold back all the
	// carry bits from the top 16 bits into the lower 16 bits.
	
	while (nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}
	// mop up an odd byte, if necessary 
	if (nleft == 1)
	{
		*(u_char *)(&answer) = *(u_char *)w;
		sum += answer;
	}
	// add back carry outs from top 16 bits to low 16 bits 
	sum = (sum >> 16) + (sum & 0xffff);     // add hi 16 to low 16 
	sum += (sum >> 16);             // add carry 
	answer = ~sum;              // truncate to 16 bits 
	return (answer);
}
}

BlobPacket network::icmp::СreateIcmpPacket( const size_t sizeMessageIcmp )
{
	srand(static_cast<unsigned int>(time(NULL)));

	struct icmp icmpHeader;
	memset(&icmpHeader, 0x00, sizeof(icmpHeader));
	// ICMP заголовок
	icmpHeader.icmp_type = ICMP_ECHO;

	// индентификатор пакета
	uint16_t number = rand() % 65535 + 0;
	icmpHeader.icmp_hun.ih_idseq.icd_id = htons(++number);
	// контрольная сумма icmp
	icmpHeader.icmp_cksum = in_cksum(&icmpHeader, sizeof(icmp));

	// помещение пакета в вектор
	BlobPacket dataBuffer(sizeof(struct icmp) + sizeMessageIcmp, 0);
	memcpy(&dataBuffer[0], &icmpHeader, sizeof(struct icmp));

	if (sizeMessageIcmp){
		BlobPacket data(sizeMessageIcmp, 0);
		memcpy(&dataBuffer[0]  + sizeof(icmpHeader), data.data(), data.size());
	}

	return std::move(dataBuffer);
}
