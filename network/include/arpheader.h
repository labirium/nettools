#pragma once

// Ethernet/IP ARP message
#define ETH_ADDR_LEN	6
/// Ip len
#define IP_ADDR_LEN	4	

// Hardware address format
#define ARP_HRD_ETH 	0x0001	/// ethernet hardware 
#define ARP_HRD_IEEE802	0x0006	/// IEEE 802 hardware 

#define ARP_HDR_LEN	8	/// base ARP header length
#define ARP_ETHIP_LEN	20	/// base ARP message length
#define ETH_HDR_LEN	14


#define ETH_TYPE_IP	0x0800		    /// IP protocol 
#define ETH_TYPE_ARP	0x0806		/// address resolution protocol 


// Protocol address format
#define ARP_PRO_IP	0x0800	/// IP protocol 


// ARP operation

#define	ARP_OP_REQUEST		1	/// request to resolve ha given pa 
#define	ARP_OP_REPLY		2	/// response giving hardware address 
#define	ARP_OP_REVREQUEST	3	/// request to resolve pa given ha 
#define	ARP_OP_REVREPLY		4	/// response giving protocol address 

#define ETH_ADDR_BROADCAST	"\xff\xff\xff\xff\xff\xff"
#define ETH_ADDR_EMPTY      "\x00\x00\x00\x00\x00\x00"

namespace network
{
namespace arp
{

struct arp_ethip {
	uint8_t		ar_sha[ETH_ADDR_LEN];	/// sender hardware address
	uint8_t		ar_spa[IP_ADDR_LEN];	/// sender protocol address
	uint8_t		ar_tha[ETH_ADDR_LEN];	/// target hardware address 
	uint8_t		ar_tpa[IP_ADDR_LEN];	/// target protocol address 
};

typedef struct eth_addr {
	uint8_t		data[ETH_ADDR_LEN];
} eth_addr_t;

struct eth_hdr {
	eth_addr_t	eth_dst;	/// destination address 
	eth_addr_t	eth_src;	/// source address 
	uint16_t	eth_type;	/// payload type 
};


/// ARP header
struct arp_hdr {
	uint16_t	ar_hrd; /// Hardware Type 
	uint16_t	ar_pro; /// Protocol Type 
	uint8_t		ar_hln;	/// length of hardware address (ETH_ADDR_LEN) 
	uint8_t		ar_pln;	/// length of protocol address (IP_ADDR_LEN) 
	uint16_t	ar_op;	/// operation 
};


/// @brief Формирует arp заголовок
///
void arp_pack_hdr_ethip_f(uint8_t* hdr, uint16_t op, const char*sha, const struct in_addr& spa, const char*tha, const struct in_addr& tpa);
/// @brief Формирует arp заголовок
///
void eth_pack_hdr_f(uint8_t* hdr, const char* dst, const char* src, uint16_t type);
}
}
