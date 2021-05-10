#ifndef _C_NET_RAW_PROTO_H_
  #define _C_NET_RAW_PROTO_H_ 

  #include <cstdint>
  
//////////////////////////////////////////////////////////////////////////////////
//  | Netzwerk Protokolle |    |            |    |            |
//////////////////////////////////////////////////////////////////////////////////
 //
 //  last Modi: 03.01.17 [�~]
 //
 //
//////////////////////////////////////////////////////////////////////////////////
 // [ INTERN_HEADER ] ( for Packet Engine )
//////////////////////////////////////////////////////////////////////////////////
 //

 typedef uint8_t  UCHAR;
 typedef uint16_t WORD;
 typedef uint32_t DWORD;
 typedef uint64_t QWORD;
 
 const UCHAR SIZE_MAC  = 0x06;
 const UCHAR SIZE_IP   = 0x04;
 const UCHAR SIZE_PORT = 0x02;

 const UCHAR IP_ZERO[SIZE_IP]        = {0x00, 0x00, 0x00, 0x00};
 const UCHAR IP_BROADCAST[SIZE_IP]   = {0xFF, 0xFF, 0xFF, 0xFF};
 const UCHAR IP_SUBMASK[SIZE_IP]     = {0xFF, 0xFF, 0xFF, 0x00};

 const UCHAR MAC_ZERO[SIZE_MAC]       = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
 const UCHAR MAC_BROADCAST[SIZE_MAC]  = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

 //////////////////////////////////////////////////
 
 const UCHAR SIZE_IPV6C = 0x10;
 const UCHAR SIZE_IPV6W = 0x08; 
 
 const UCHAR MAC_IPV6MCAST_NODES[SIZE_MAC]  = {0x33, 0x33, 0x00, 0x00, 0x00, 0x01};
 const UCHAR MAC_IPV6MCAST_ROUTER[SIZE_MAC] = {0x33, 0x33, 0x00, 0x00, 0x00, 0x02};
 
 const WORD IPV6_NODE_ALL_NODES[SIZE_IPV6W]  = {0x01FF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0100}; // Net Short
 const WORD IPV6_NODE_ALL_ROUTER[SIZE_IPV6W] = {0x01FF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0200}; // Net Short
 
 const WORD IPV6_LINK_ALL_NODES[SIZE_IPV6W]  = {0x02FF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0100}; // Net Short
 const WORD IPV6_LINK_ALL_ROUTER[SIZE_IPV6W] = {0x02FF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0200}; // Net Short
 
 const WORD IPV6_UNICAST[SIZE_IPV6W] = {0x80FE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Net Short
 
 //////////////////////////////////////////////////
 
 struct S_ArpPacket {
    WORD   Operation;
    UCHAR* pETH_MAC_D;
    UCHAR* pETH_MAC_S;
    UCHAR* pARP_MAC_D;
    UCHAR* pARP_MAC_S;
    UCHAR* pARP_IP_D;
    UCHAR* pARP_IP_S;
 };

 struct S_IpPacket {
    UCHAR* pETH_MAC_D;
    UCHAR* pETH_MAC_S;
    UCHAR* pIP_D;
    UCHAR* pIP_S;
    UCHAR  pIP_Type;
    WORD   pIP_ID; 
    WORD   pIP_Frag;
    UCHAR  pIP_TTL;
    UCHAR  pIP_Protocol;      
 };

 struct S_IcmpPacket {
    UCHAR ICMP_Type;
    UCHAR ICMP_Code;
    WORD  ICMP_ID;          
    WORD  ICMP_Sequence;    
    DWORD ICMP_TimeStamp;    
 };

 struct S_UdpPacket {
    WORD  UDP_Port_D;
    WORD  UDP_Port_S;
 };

 struct S_TcpPacket {
    WORD  TCP_Port_D;
    WORD  TCP_Port_S;
    UCHAR TCP_Flag;
    DWORD TCP_nSeq;
    DWORD TCP_nAck;
 };
 //
//////////////////////////////////////////////////////////////////////////////////
 // [ REAL_HEADER ]
//////////////////////////////////////////////////////////////////////////////////
 //
 //
 //////////////////////////////////////////////////////////////////////////////////
 //--------------------------[ PHYSICAL LAYER ]------------------------------0x00//
 //////////////////////////////////////////////////////////////////////////////////
 //
 //////////////////////////////////////////////////////////////////////////////////
 //--------------------------[ DATA LINK LAYER ]-----------------------------0x01//
 //////////////////////////////////////////////////////////////////////////////////
 //
 //////////////////////////////////////////////////////////////////////////////////
 // ++ [ ETHERNET_HEADER ]
 //////////////////////////////////////////////////////////////////////////////////
 //
 struct ETHERNET_HEADER {
    UCHAR   MAC_D[SIZE_MAC];  
    UCHAR   MAC_S[SIZE_MAC];      
    WORD    Type;               
 };

 const DWORD cETHERNET_HEADER = sizeof(ETHERNET_HEADER);

 ///////////////////////////////////////////////////
 // ETHERNET_HEADER CONSTANT
 //
 const WORD ETH_TYP_IPv4 = 0x0008;
 const WORD ETH_TYP_IPv6 = 0xDD86; 
 const WORD ETH_TYP_ARP  = 0x0608; 
 const WORD ETH_TYP_RARP = 0x3580; 

/*
 Typfeld	Protokoll
0x0800	IP Internet Protocol (IPv4)
0x86DD	Internet Protocol, Version 6 (IPv6)
0x0806	Address Resolution Protocol (ARP)
0x8035	Reverse Address Resolution Protocol (RARP)

0x809B	Appletalk (Ethertalk)
0x80F3	Appletalk Address Resolution Protocol (AARP)
0x8100	VLAN Tag (VLAN)
0x8137	Novell IPX (alt)
0x8138	Novell
*/

 //
 //////////////////////////////////////////////////////////////////////////////////
 //---------------------------[ NETWORK LAYER ]------------------------------0x02//
 //////////////////////////////////////////////////////////////////////////////////
 //
 //////////////////////////////////////////////////////////////////////////////////
 // ++ [ ARP_HEADER ]
 //////////////////////////////////////////////////////////////////////////////////
 //
 typedef struct ARP_HEADER {
    WORD    ARP_HType;           // Hardware Format
    WORD    ARP_PType;           // Protocol Format
    UCHAR   ARP_cHAddr;          // Hardware Address Length
    UCHAR   ARP_cPAddr;          // Protocol Address Length
    WORD    ARP_OpCode;          // Opcode
    UCHAR   ARP_MAC_S[SIZE_MAC]; // Sender Ethernet Address
    UCHAR   ARP_IP_S[SIZE_IP];   // Sender IP Address
    UCHAR   ARP_MAC_D[SIZE_MAC]; // Target Ethernet Address
    UCHAR   ARP_IP_D[SIZE_IP];   // Target IP Address
 }  ARP_HEADER;

 const DWORD cARP_HEADER = sizeof(ARP_HEADER);

 ///////////////////////////////////////////////////
 // ARP_HEADER CONSTANT
 //
 const WORD  ARP_HTYP_ETH  = 0x0100;   // Hardware Format [ ethernet ]
 const WORD  ARP_PTYP_IP   = 0x0008;   // Protocol Format [ ip ]

 const WORD  ARP_REQUEST   = 0x0100;   // Opcode
 const WORD  ARP_RESPONSE  = 0x0200;   // Opcode

 const UCHAR ARP_MAC_LEN   = SIZE_MAC; // Hardware Address Length [ ethernet ]
 const UCHAR ARP_PRO_LEN   = SIZE_IP;  // Protocol Address Length [ ip ]

 //////////////////////////////////////////////////////////////////////////////////
 // ++ [ IP_HEADER ]
 //////////////////////////////////////////////////////////////////////////////////
 //
 struct IP_HEADER {
    UCHAR  IP_VerLen;    // version(4Bit) & length(4Bit)
    UCHAR  IP_ToS;       // Type of service(8Bit)
    WORD   IP_cPacket;   // Total length of the packet(16Bit)
    WORD   IP_ID;        // Unique identifier(16Bit)
    WORD   IP_Flags;     // Flags(3Bit) & Frag offset(13Bit)
    UCHAR  IP_Ttl;       // Time to live(8Bit)
    UCHAR  IP_Protocol;  // Protocol(8Bit) (TCP, UDP etc)
    WORD   IP_Checksum;  // IP checksum(16Bit)
    UCHAR  IP_IP_S[SIZE_IP];   // Source IP(32Bit)
    UCHAR  IP_IP_D[SIZE_IP];   // Destination IP(32Bit)
    //unsigned char  options[40];  // Optional bytes(40 byte max)
 };

 const DWORD cIP_HEADER = sizeof(IP_HEADER);

 ///////////////////////////////////////////////////
 // IP_HEADER CONSTANT
 //
 const UCHAR IP_ICMP = 0x01;
 const UCHAR IP_IGMP = 0x02;
 const UCHAR IP_IP   = 0x04;
 const UCHAR IP_TCP  = 0x06;
 const UCHAR IP_UDP  = 0x11;

 const UCHAR IP_VERSION = 64;
 const UCHAR IP_DEFAULT = IP_VERSION | (cIP_HEADER / 4);

 //////////////////////////////////////////////////////////////////////////////////
 // ++ [ ICMP_HEADER ]
 //////////////////////////////////////////////////////////////////////////////////
 //
 struct ICMP_HEADER {
    UCHAR ICMP_Type;        // ICMP Message Type
    UCHAR ICMP_Code;        // Message Interner (Fehler-)Code 
    WORD  ICMP_CheckSum;    // Checksum f�r das ICMP Paket 
    WORD  ICMP_ID;          // ID des Pakets, oft wie Port bei TCP / UDP genutzt 
    WORD  ICMP_Sequence;    // Sequenznummer, bei mehreren typgleichen, (sinn-)zusammenh�ngenden Paketen 
    //DWORD   ICMP_TimeStamp;   // Zeitstempel beim Abesenden 
 };   

 const DWORD cICMP_HEADER = sizeof(ICMP_HEADER);

///////////////////////////////////////////////////
 // ICMP_HEADER CONSTANT
 //
 // TYPE
 const UCHAR ICMP_TYPE_RESPONSE      = 0x00;
 const UCHAR ICMP_TYPE_UNREACHABLE   = 0x03;
 const UCHAR ICMP_TYPE_REDIRECT      = 0x05;
 const UCHAR ICMP_TYPE_REQUEST       = 0x08;
 const UCHAR ICMP_TYPE_R_ADVERT      = 0x09;
 const UCHAR ICMP_TYPE_R_SOLICIT     = 0x0A;
 const UCHAR ICMP_TYPE_TIME          = 0x0B;
 const UCHAR ICMP_TYPE_BAD_IP_HDR    = 0x0C;
 const UCHAR ICMP_TYPE_TIMESTAMP     = 0x0D;
 const UCHAR ICMP_TYPE_TIMESTAMP_REP = 0x0E;
 
 // CODE [PING]
 const UCHAR ICMP_CODE_ECHO_RESPONSE = 0x00;
 const UCHAR ICMP_CODE_ECHO_REQUEST  = 0x00;

 // CODE [UNREACHABLE]
 const UCHAR ICMP_CODE_UNREACHABLE_NET      = 0x00;
 const UCHAR ICMP_CODE_UNREACHABLE_HOST     = 0x01;
 const UCHAR ICMP_CODE_UNREACHABLE_PROTO    = 0x02;
 const UCHAR ICMP_CODE_UNREACHABLE_PORT     = 0x03; 
 const UCHAR ICMP_CODE_UNREACHABLE_FRAG     = 0x04;
 const UCHAR ICMP_CODE_UNREACHABLE_ROUTE    = 0x05;
 const UCHAR ICMP_CODE_UNKNOWN_NET          = 0x06;
 const UCHAR ICMP_CODE_UNKNOWN_HOST         = 0x07;
 const UCHAR ICMP_CODE_ISOLATED_HOST        = 0x08;
 const UCHAR ICMP_CODE_PROHIBITED_NET       = 0x09;
 const UCHAR ICMP_CODE_PROHIBITED_HOST      = 0x0A;
 const UCHAR ICMP_CODE_UNREACHABLE_TOS_NET  = 0x0B;
 const UCHAR ICMP_CODE_UNREACHABLE_TOS_HOST = 0x0C;
 const UCHAR ICMP_CODE_PROHIBITED           = 0x0D;
 const UCHAR ICMP_CODE_PRECEDENCE_VIOLATION = 0x0E;
 const UCHAR ICMP_CODE_PRECEDENCE_CUTOFF    = 0x0F;
 
 // CODE [REDIRECT]
 const UCHAR ICMP_CODE_REDIRECT_NET      = 0x00;
 const UCHAR ICMP_CODE_REDIRECT_HOST     = 0x01;
 const UCHAR ICMP_CODE_REDIRECT_NET_TOS  = 0x02;
 const UCHAR ICMP_CODE_REDIRECT_HOST_TOS = 0x03;
 
 // CODE [ROUTER]
 const UCHAR ICMP_CODE_R_ADVERTISEMENT   = 0x00;
 const UCHAR ICMP_CODE_R_SOLICITATION    = 0x00;
 
 // CODE [TIME]
 const UCHAR ICMP_CODE_TIME_TTL_EXPIRED  = 0x00;
 const UCHAR ICMP_CODE_TIME_FRAGMENT     = 0x01;
 
 // CODE [BAD IP]
 const UCHAR ICMP_CODE_BAD_IP_POINTER        = 0x00;
 const UCHAR ICMP_CODE_BAD_IP_MISSING_OPTION = 0x01;
 const UCHAR ICMP_CODE_BAD_IP_BAD_LENGTH     = 0x02;
 
 // CODE [TIMESTAMP]
 const UCHAR ICMP_CODE_TIMESTAMP       = 0x00;
 const UCHAR ICMP_CODE_TIMESTAMP_REPLY = 0x00;

 //////////////////////////////////////////////////////////////////////////////////
 // ++ [ IPv6_HEADER ]
 //////////////////////////////////////////////////////////////////////////////////
 //
 
 struct IPv6_HEADER {
    //UCHAR version :  4;   // IP-Version(4bit)
    //DWORD qos     :  8,   // Quality of Service (8bit) (0-5 == DSCP)(6-7 == ECN)
    //      ident   : 20;   // high-entropy identifier (20bit)

    DWORD bitfield;        // IP-Version(4bit) + DSCP(6bit) + ECN(2bit) + id(20bit)   
    WORD  length;          // Size of Payload + extension headers (16bit)
    UCHAR next_header;     // Protocol (8Bit) (TCP, UDP etc) or Extension Headers
    UCHAR ttl;             // time to live [8bit]
    UCHAR src[SIZE_IPV6C]; // Source IP (128Bit)
    UCHAR dst[SIZE_IPV6C]; // Destination IP (128Bit)
 };
 
 const DWORD cIPv6_HEADER = sizeof(IPv6_HEADER);
 
 ///////////////////////////////////////////////////
 // IPv6_Extension Headers
 //
 
 const UCHAR IPV6_HOP_BY_HOP     = 0x00;
 const UCHAR IPV6_ROUTING        = 0x2B;
 const UCHAR IPV6_FRAGMENT       = 0x2C;
 const UCHAR IPV6_SECURITY       = 0x32;
 const UCHAR IPV6_AUTHENTICATION = 0x33;
 const UCHAR IPV6_ICMP           = 0x3A;
 const UCHAR IPV6_NO_NEXT_HEADER = 0x3B;
 const UCHAR IPV6_DESTINATION    = 0x3C;
 const UCHAR IPV6_MOBILITY       = 0x87;
 const UCHAR IPV6_HOST_IDENTITY  = 0x8B;
 const UCHAR IPV6_SHIM6          = 0x8C;
 
 ///////////////////////////////////////////////////
 // IPv6_Hop by Hop Header
 //
 
 struct IPv6_HopbyHop {
    UCHAR next_header;   // Protocol (8Bit) (TCP, UDP etc) or Extension Headers
    UCHAR length;        // Size of this Header(8bit), not including the first 8 octets
    UCHAR options[6];    // Options and Padding(48bit)
    // Optional: more Options and Padding... the total header length a multiple of 8 octets
 };
 
 ///////////////////////////////////////////////////
 // IPv6_Routing Header
 //
 
 struct IPv6_Routing {
    UCHAR next_header;   // Protocol (8Bit) (TCP, UDP etc) or Extension Headers
    UCHAR length;        // Size of this Header(8bit), not including the first 8 octets
    UCHAR type;          // Routing Type (8bit)
    UCHAR segleft;       // Segments Left (8bit), Number of nodes this packet still has to visit before reaching its final destination
    UCHAR specific[4];   // Type-specific Data (32bit)
    // Optional: more Type-specific Data...  the total header length a multiple of 8 octets
 };
 
 ///////////////////////////////////////////////////
 // IPv6_Fragment Header
 //
 
 struct IPv6_Fragment {
    UCHAR next_header;   // Protocol (8Bit) (TCP, UDP etc) or Extension Headers
    UCHAR reserved;      // Reserved (8bit) Initialized to all zeroes
    WORD  offset : 13,   // Fragment Offset (13bit),  in 8-octet units, relative to the start of the fragmentable part of the original packet
          res    :  2,   // Reserved(2bit) initialized to zeroes.
          flag   :  1;   // M Flag (1bit) 1 means more fragments follow; 0 means last fragment.
    DWORD id;            // Identification (32bit), Packet identification value, generated by the source node
 };
 
 ///////////////////////////////////////////////////
 // IPv6_Destination Header
 //
 
 struct IPv6_Destination {
    UCHAR next_header;   // Protocol (8Bit) (TCP, UDP etc) or Extension Headers
    UCHAR length;        // Size of this Header(8bit), not including the first 8 octets
    UCHAR options[6];    // Options and Padding(48bit)
    // Optional: more Options and Padding... the total header length a multiple of 8 octets
 };
 
 
 //////////////////////////////////////////////////////////////////////////////////
 // ++ [ ICMPv6_HEADER ]
 //////////////////////////////////////////////////////////////////////////////////
 //
 struct ICMPv6_HEADER {
    UCHAR type;        // ICMP Message Type
    UCHAR code;        // Message Interner (Fehler-)Code 
    WORD  checksum;    // Checksum f�r das ICMP Paket 
    DWORD message;     // Message body
 }; 
 
 const DWORD cICMPv6_HEADER = sizeof(ICMPv6_HEADER);
 
 
 ///////////////////////////////////////////////////
 // ICMPv6_PSEUDO_HEADER
 //
 struct ICMPv6_PSEUDO_HEADER {
    UCHAR src[SIZE_IPV6C]; // Source IP (128Bit)
    UCHAR dst[SIZE_IPV6C]; // Destination IP (128Bit)    
    DWORD length;  
    UCHAR zeros[3];
    UCHAR next_header;
 };

 const DWORD cICMPv6_PS_HEADER = sizeof(ICMPv6_PSEUDO_HEADER);
 
///////////////////////////////////////////////////
 // ICMPv6_HEADER CONSTANT
 //
 // TYPE Error Messages
 
 const UCHAR ICMPV6_TYPE_UNREACHABLE    = 0x01;
 const UCHAR ICMPV6_TYPE_PACKET_TOO_BIG = 0x02;
 const UCHAR ICMPV6_TYPE_TIME_EXCEEDED  = 0x03;
 const UCHAR ICMPV6_TYPE_PARAM_PROBLEM  = 0x03;
 
 // CODE [UNREACHABLE]
 const UCHAR ICMPV6_CODE_UNREACHABLE_NO_ROUTE     = 0x00;
 const UCHAR ICMPV6_CODE_UNREACHABLE_PROHIBITED   = 0x01;
 const UCHAR ICMPV6_CODE_UNREACHABLE_SCOPE        = 0x02;
 const UCHAR ICMPV6_CODE_UNREACHABLE_ADDRESS      = 0x03;
 const UCHAR ICMPV6_CODE_UNREACHABLE_PORT         = 0x04;
 const UCHAR ICMPV6_CODE_UNREACHABLE_POLICY       = 0x05;
 const UCHAR ICMPV6_CODE_UNREACHABLE_REJECT_ROUTE = 0x06;
 const UCHAR ICMPV6_CODE_UNREACHABLE_ERROR_HEADER = 0x07;
 
 // CODE [TIME_EXCEEDED]
 const UCHAR ICMPV6_CODE_TIME_TTL_EXPIRED = 0x00;
 const UCHAR ICMPV6_CODE_TIME_FRAGMENT    = 0x01;
 
 // CODE [PARAM_PROBLEM]
 const UCHAR ICMPV6_CODE_PARAM_HEADER_FIELD = 0x00;
 const UCHAR ICMPV6_CODE_PARAM_HEADER_TXPE  = 0x01;
 const UCHAR ICMPV6_CODE_PARAM_OPTION       = 0x02;
 //
 // TYPE Informational Messages
 
 const UCHAR ICMPV6_TYPE_REQUEST          = 0x80;
 const UCHAR ICMPV6_TYPE_RESPONSE         = 0x81;
 
 const UCHAR ICMPV6_TYPE_MCL_QUERY        = 0x82;  // Multicast Listener Query
 const UCHAR ICMPV6_TYPE_MCL_REPORT       = 0x83;  // Multicast Listener Report
 const UCHAR ICMPV6_TYPE_MCL_DONE         = 0x84;  // Multicast Listener Done
 
 const UCHAR ICMPV6_TYPE_ROUTER_SOLICIT   = 0x85;  // Router Solicitation - Neighbor Discovery Protocol
 const UCHAR ICMPV6_TYPE_ROUTER_ADVERT    = 0x86;  // Router Advertisement - Neighbor Discovery Protocol
 const UCHAR ICMPV6_TYPE_NEIGHBOR_SOLICIT = 0x87;  // Neighbor Solicitation - Neighbor Discovery Protocol
 const UCHAR ICMPV6_TYPE_NEIGHBOR_ADVERT  = 0x88;  // Neighbor Advertisement - Neighbor Discovery Protocol
 const UCHAR ICMPV6_TYPE_REDIRECT_MESSAGE = 0x89;  // Neighbor Discovery Protocol
 
 // CODE [PING]
 const UCHAR ICMPV6_CODE_ECHO_RESPONSE = 0x00;
 const UCHAR ICMPV6_CODE_ECHO_REQUEST  = 0x00;
 

 //
 //////////////////////////////////////////////////////////////////////////////////
 //-------------------------[ TRANSPORT LAYER ]------------------------------0x03//
 //////////////////////////////////////////////////////////////////////////////////
 //
 //////////////////////////////////////////////////////////////////////////////////
 // ++ [ UDP_HEADER ]
 //////////////////////////////////////////////////////////////////////////////////
 //
 struct UDP_HEADER {
    WORD UDP_Port_S;         // [00] - source port            
    WORD UDP_Port_D;         // [02] - destination port       
    WORD UDP_cPacket;        // [04] - Packet length + message length         
    WORD UDP_Checksum;       // [06] - checksum           
 };

 const DWORD cUDP_HEADER = sizeof(UDP_HEADER);

 ///////////////////////////////////////////////////
 // UDP_PSEUDO_HEADER
 //
 struct UDP_PSEUDO_HEADER {
    UCHAR      UDP_PS_IP_S[SIZE_IP];    
    UCHAR      UDP_PS_IP_D[SIZE_IP];     
    UCHAR      UDP_PS_Empty;  
    UCHAR      UDP_PS_Protocol;
    WORD       UDP_PS_Size;  
    UDP_HEADER UDP_PS_UDP_HEADER;
 };

 const DWORD cUDP_PS_HEADER = sizeof(UDP_PSEUDO_HEADER);

 ///////////////////////////////////////////////////
 // UDP_HEADER DEFAULT PORTS
 //
 const WORD UDP_PORT_NS_DNS    = 0x3500; //  DNS  net Short 
 const WORD UDP_PORT_NS_DHCP_S = 0x4300; //  DHCP Server net Short
 const WORD UDP_PORT_NS_DHCP_C = 0x4400; //  DHCP Client net Short
 const WORD UDP_PORT_NS_NBS137 = 0x8900; //  137
 const WORD UDP_PORT_NS_NBS138 = 0x8A00; //  138
 const WORD UDP_PORT_NS_NBS2   = 0xBD01; //  445
 const WORD UDP_PORT_NS_IPSEC1 = 0xF401; //  500
 const WORD UDP_PORT_NS_IPSEC2 = 0x9411; // 4500

 const WORD UDP_PORT_HS_DNS    = 0x0035; //  DNS win host Short
 const WORD UDP_PORT_HS_DHCP_S = 0x0043; //  DHCP Server host Short
 const WORD UDP_PORT_HS_DHCP_C = 0x0044; //  DHCP Client host Short
 const WORD UDP_PORT_HS_NBS137 = 0x0089; //  137
 const WORD UDP_PORT_HS_NBS138 = 0x008A; //  138
 const WORD UDP_PORT_HS_NBS2   = 0x01BD; //  445
 const WORD UDP_PORT_HS_IPSEC1 = 0x01F4; //  500
 const WORD UDP_PORT_HS_IPSEC2 = 0x1194; // 4500


 //////////////////////////////////////////////////////////////////////////////////
 // ++ [ TCP_HEADER ]
 //////////////////////////////////////////////////////////////////////////////////
 //
 struct TCP_HEADER {
    WORD   TCP_Port_S;     // Source Port
    WORD   TCP_Port_D;     // Destination Port
    DWORD  TCP_nSeq;       // Sequence Nummer
    DWORD  TCP_nAck;       // Acknowledged Nummer
    UCHAR  TCP_cHead;      // Data offset(4bit) & Reserved(4bit)(bNULL)
    UCHAR  TCP_FLAG;       // Flag
    WORD   TCP_cWin;       // Windows Size
    WORD   TCP_Checksum;   // Checksum
    WORD   TCP_pUrgent;    // Urgent pointer
    //
    //UCHAR TCP_Options[n * 32]; //optional Data [ (TCP_cHead & 0xF0) - cTCP_HEADER ]
 };                     

 const DWORD cTCP_HEADER = sizeof(TCP_HEADER);

 ///////////////////////////////////////////////////
 // TCP_HEADER CONSTANT
 //
 const UCHAR TCP_FLAG_FIN = 0x01; //flags
 const UCHAR TCP_FLAG_SYN = 0x02; 
 const UCHAR TCP_FLAG_RST = 0x04; 
 const UCHAR TCP_FLAG_PSH = 0x08;
 const UCHAR TCP_FLAG_ACK = 0x10;
 const UCHAR TCP_FLAG_URG = 0x20;
 const UCHAR TCP_FLAG_ECE = 0x40;
 const UCHAR TCP_FLAG_CWR = 0x80; //flags

 //const UCHAR TCP_FLAG_FIN_ACK = 0x11;
 //const UCHAR TCP_FLAG_SYN_ACK = 0x12;
 //const UCHAR TCP_FLAG_RST_ACK = 0x14;
 //const UCHAR TCP_FLAG_PSH_ACK = 0x18;

 //const UCHAR TCP_FLAG_FIN_PSH_ACK = 0x19;

 ///////////////////////////////////////////////////
 // TCP_PSEUDO_HEADER
 //
 struct TCP_PSEUDO_HEADER {
    UCHAR      TCP_PS_IP_S[SIZE_IP];    
    UCHAR      TCP_PS_IP_D[SIZE_IP];     
    UCHAR      TCP_PS_Empty;  
    UCHAR      TCP_PS_Protocol;
    WORD       TCP_PS_Size;  
    TCP_HEADER TCP_PS_TCP_HEADER;
 };

 const DWORD cTCP_PSEUDO_HEADER = sizeof(TCP_PSEUDO_HEADER);

 ///////////////////////////////////////////////////
 // TCP_HEADER DEFAULT PORTS
 //
 const WORD TCP_PORT_NS_FTP   = 0x1400; //net Short 
 const WORD TCP_PORT_NS_CTP   = 0x1500; 
 const WORD TCP_PORT_NS_HTTP  = 0x5000; 
 const WORD TCP_PORT_NS_HTTPS = 0xBB01; 
 const WORD TCP_PORT_NS_POP3  = 0x6E00;
 const WORD TCP_PORT_NS_NBS1  = 0x8B00; // 139
 const WORD TCP_PORT_NS_NBS2  = 0xBD01; // 445
 const WORD TCP_PORT_NS_DCE   = 0x8700; // 135

 const WORD TCP_PORT_HS_FTP   = 0x0014; //win host Short 
 const WORD TCP_PORT_HS_CTP   = 0x0015;
 const WORD TCP_PORT_HS_HTTP  = 0x0050; 
 const WORD TCP_PORT_HS_HTTPS = 0x01BB; 
 const WORD TCP_PORT_HS_POP3  = 0x006E;
 const WORD TCP_PORT_HS_NBS1  = 0x008B; // 139
 const WORD TCP_PORT_HS_NBS2  = 0x01BD; // 445
 const WORD TCP_PORT_HS_DCE   = 0x0087; // 135

 //
 //////////////////////////////////////////////////////////////////////////////////
 //-------------------------[ APPLICATION LAYER ]----------------------------0x04//
 //////////////////////////////////////////////////////////////////////////////////
 //
 //////////////////////////////////////////////////////////////////////////////////
 // ++ [ DNS_HEADER ]
 //////////////////////////////////////////////////////////////////////////////////
 //
 struct DNS_HEADER {
    WORD DNS_ID;
    WORD DNS_Flags;
    WORD DNS_cQuestion;
    WORD DNS_cAnswer;
    WORD DNS_cAuthority;
    WORD DNS_cAdditional;
 };

 struct DNS_QUEST {
    // UCHAR DNS_cName;  // example: ([WWW].BMW.COM) = 0x03; ([geocities].com) = 0x09;
    // char  DNS_Name[DNS_cName];
    WORD DNS_Type;
    WORD DNS_Class;
 };

 struct DNS_ANSWER {
    WORD  DNS_pNAME;  // ( Offset(DNS_pName) | 0xC000 );
    WORD  DNS_Type;
    WORD  DNS_Class;
    DWORD DNS_TTL;
    WORD  DNS_cData;
    //UCHAR DNS_DATA[DNS_cData]; // IP OR Name String
 };

 ///////////////////////////////////////////////////
 // DNS_HEADER CONSTANT
 //
 // DNS_Flags 
 // WORD Type:1, OpCode:4, AAnswer:1, TrunCation:1, RecD:1, RecA:1, NotUse:3, RCode:4;
 //
 const WORD DNS_FLAG_TYP_REQUEST     = 0x0000;   // Request
 const WORD DNS_FLAG_TYP_RESPONSE    = 0x8000;   // Response

 const WORD DNS_FLAG_OPCODE_SQUERY   = 0x0000;   // Standart Query
 const WORD DNS_FLAG_OPCODE_IQUERY   = 0x0800;   // Inverse Query
 const WORD DNS_FLAG_OPCODE_SERVER   = 0x2000;   // Server Status Request

 const WORD DNS_FLAG_BIT_AA          = 0x0040;   // Authoritative Answer
 const WORD DNS_FLAG_BIT_TC          = 0x0080;   // TrunCation
 const WORD DNS_FLAG_BIT_RD          = 0x0100;   // Recursion Desired
 const WORD DNS_FLAG_BIT_RA          = 0x0200;   // Recursion Available

 const WORD DNS_FLAG_RCODE_SUCCESS   = 0x0000;   // No Error
 const WORD DNS_FLAG_RCODE_FORMAT    = 0x0001;   // Format Error
 const WORD DNS_FLAG_RCODE_SERVER    = 0x0002;   // Server Error
 const WORD DNS_FLAG_RCODE_NAME      = 0x0003;   // Not Exist Error
 const WORD DNS_FLAG_RCODE_IMPLEMENT = 0x0004;   // Not Implmemted Error
 const WORD DNS_FLAG_RCODE_REFUSED   = 0x0005;   // Refused Error

 // DNS_QUEST

 const WORD DNS_QUEST_TYP_ADDRESS    = 0x0100;   // Address
 const WORD DNS_QUEST_TYP_CNAME      = 0x0500;   // String

 const WORD DNS_QUEST_ClASS_INTERNET = 0x0100;   // Class Internet
 const WORD DNS_QUEST_CLASS_PTR      = 0x0C00;   // Class PTR ?

 /*
 //// Sample
 ////
 static UCHAR DnsQuestion[] = {0xFF, 0x00,              // DNS_ID
                               0x01, 0x00,              // DNS_Flags
                               0x00, 0x01,              // DNS_cQuestion
                               0x00, 0x00,              // DNS_cAnswer
                               0x00, 0x00,              // DNS_cAuthority
                               0x00, 0x00,              // DNS_cAdditional

                               0x06, 0x67, 0x6F, 0x6F,  // [0x06]Google.com[0x00]
                               0x67, 0x6C, 0x65, 0x03,  //  0x06 == strlen("Google") 
                               0x63, 0x6F, 0x6D, 0x00,  //

                               0x00, 0x01,              // DNS_QTYP_ADDRESS
                               0x00, 0x01 };            // DNS_QClASS_INTERNET

 ////////////////////////////////////////////////////////////////////////////////////////////

 static UCHAR DnsAnswer[] = {  0xFF, 0x00,              // DNS_ID
                               0x81, 0x80,              // DNS_Flags         (!!)
                               0x00, 0x01,              // DNS_cQuestion
                               0x00, 0x03,              // DNS_cAnswer       (!!)
                               0x00, 0x00,              // DNS_cAuthority
                               0x00, 0x00,              // DNS_cAdditional

                               0x06, 0x67, 0x6F, 0x6F,  // [0x06]Google.com[0x00]
                               0x67, 0x6C, 0x65, 0x03,  //  0x06 == strlen("Google") 
                               0x63, 0x6F, 0x6D, 0x00,  //

                               0x00, 0x01,              // DNS_QTYP_ADDRESS
                               0x00, 0x01,              // DNS_QClASS_INTERNET

                                                         // DNS_ANSWER

                               0xC0, 0x0C,              // DNS_pNAME
                               0x00, 0x01,              // DNS_QTYP_ADDRESS
                               0x00, 0x01,              // DNS_QClASS_INTERNET
                               0x00, 0x00, 0x06, 0x1D,  // DNS_TTL 26'05''
                               0x00, 0x04,
                               0x42, 0xF9, 0x5D, 0x68,  // DNS_IP 66.249.93.104

                               0xC0, 0x0C,              // DNS_pNAME
                               0x00, 0x01,              // DNS_QTYP_ADDRESS
                               0x00, 0x01,              // DNS_QClASS_INTERNET
                               0x00, 0x00, 0x06, 0x1D,  // DNS_TTL 26'05''
                               0x00, 0x04,
                               0xD8, 0xEF, 0x3B, 0x68,  // DNS_IP 216.239.59.104

                               0xC0, 0x0C,              // DNS_pNAME
                               0x00, 0x01,              // DNS_QTYP_ADDRESS
                               0x00, 0x01,              // DNS_QClASS_INTERNET
                               0x00, 0x00, 0x06, 0x1D,  // DNS_TTL 26'05''
                               0x00, 0x04,
                               0x48, 0x0E, 0xDD, 0x68   // DNS_IP 72.14.221.104
                             };
*/
//////////////////////////////////////////////////////////////////////////////////
 // [ END ]
//////////////////////////////////////////////////////////////////////////////////

#endif // _C_NET_RAW_PROTO_H_
