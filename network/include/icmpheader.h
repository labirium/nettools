#pragma once
#include <stdint.h>

namespace network
{
namespace icmp
{


#define	ICMP_ECHO		8
#define	ICMP_REPLY		0

#define ICMP_MIN_SIZE    8

/// @brief Internal of an ICMP Router Advertisement
///
struct icmp_ra_addr {
	uint32_t ira_addr;
	uint32_t ira_preference;
};

struct ip
{
	unsigned char ip_hl : 4,
	ip_v : 4;
	unsigned char ip_tos;
	unsigned short int ip_len;
	unsigned short int ip_id;
	unsigned short int ip_off;
	unsigned char ip_ttl;
	unsigned char ip_p;
	unsigned short int ip_sum;
	unsigned int ip_src;
	unsigned int ip_dst;
};

/// @brief Structure of an icmp header.
///
struct icmp {
	uint8_t	icmp_type;		/// type of message, see below 
	uint8_t	icmp_code;		/// type sub code
	uint16_t	icmp_cksum;		/// ones complement cksum of struct 
	union {
		uint8_t ih_pptr;			/// ICMP_PARAMPROB 
		struct in_addr ih_gwaddr;	/// ICMP_REDIRECT 
		struct ih_idseq {
			int16_t	icd_id;
			int16_t	icd_seq;
		} ih_idseq;
		int ih_void;

		/// ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) 
		struct ih_pmtu {
			int16_t ipm_void;
			int16_t ipm_nextmtu;
		} ih_pmtu;

		struct ih_rtradv {
			uint8_t irt_num_addrs;
			uint8_t irt_wpa;
			uint16_t irt_lifetime;
		} ih_rtradv;
	} icmp_hun;
#define	icmp_pptr	icmp_hun.ih_pptr
#define	icmp_gwaddr	icmp_hun.ih_gwaddr
#define	icmp_id		icmp_hun.ih_idseq.icd_id
#define	icmp_seq	icmp_hun.ih_idseq.icd_seq
#define	icmp_void	icmp_hun.ih_void
#define	icmp_pmvoid	icmp_hun.ih_pmtu.ipm_void
#define	icmp_nextmtu	icmp_hun.ih_pmtu.ipm_nextmtu
#define	icmp_num_addrs	icmp_hun.ih_rtradv.irt_num_addrs
#define	icmp_wpa	icmp_hun.ih_rtradv.irt_wpa
#define	icmp_lifetime	icmp_hun.ih_rtradv.irt_lifetime
	union {
		struct id_ts {
			uint32_t its_otime;
			uint32_t its_rtime;
			uint32_t its_ttime;
		} id_ts;
		struct id_ip  {
			struct ip idi_ip;
			/// options and then 64 bits of data 
		} id_ip;
		struct icmp_ra_addr id_radv;
		uint32_t id_mask;
		char	id_data[1];
	} icmp_dun;
#define	icmp_otime	icmp_dun.id_ts.its_otime
#define	icmp_rtime	icmp_dun.id_ts.its_rtime
#define	icmp_ttime	icmp_dun.id_ts.its_ttime
#define	icmp_ip		icmp_dun.id_ip.idi_ip
#define	icmp_radv	icmp_dun.id_radv
#define	icmp_mask	icmp_dun.id_mask
#define	icmp_data	icmp_dun.id_data
};

/// @brief Формирует icmp
BlobPacket СreateIcmpPacket( const size_t sizeMessageIcmp );

}
}
