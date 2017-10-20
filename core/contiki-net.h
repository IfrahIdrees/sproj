/*
 * Copyright (c) 2005, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef CONTIKI_NET_H_
#define CONTIKI_NET_H_

#include "/home/iffi/Downloads/contiki-master/core/contiki.h"

#include "/home/iffi/Downloads/contiki-master/core/net/ip/tcpip.h"
#include "/home/iffi/Downloads/contiki-master/core/net/ip/uip.h"
#include "/home/iffi/Downloads/contiki-master/core/net/ipv4/uip-fw.h"
#include "/home/iffi/Downloads/contiki-master/core/net/ipv4/uip-fw-drv.h"
#include "/home/iffi/Downloads/contiki-master/core/net/ipv4/uip_arp.h"
#include "/home/iffi/Downloads/contiki-master/core/net/ip/uiplib.h"
#include "/home/iffi/Downloads/contiki-master/core/net/ip/uip-udp-packet.h"
#include "/home/iffi/Downloads/contiki-master/core/net/ip/simple-udp.h"
#include "/home/iffi/Downloads/contiki-master/core/net/ip/uip-nameserver.h"

#if NETSTACK_CONF_WITH_IPV6
#include "/home/iffi/Downloads/contiki-master/core/net/ipv6/uip-icmp6.h"
#include "/home/iffi/Downloads/contiki-master/core/net/ipv6/uip-ds6.h"
#endif /* NETSTACK_CONF_WITH_IPV6 */

#include "/home/iffi/Downloads/contiki-master/core/net/ip/resolv.h"

#include "/home/iffi/Downloads/contiki-master/core/net/ip/psock.h"

#include "/home/iffi/Downloads/contiki-master/core/net/ip/udp-socket.h"
#include "/home/iffi/Downloads/contiki-master/core/net/ip/tcp-socket.h"

#include "/home/iffi/Downloads/contiki-master/core/net/rime/rime.h"

#include "/home/iffi/Downloads/contiki-master/core/net/netstack.h"

#endif /* CONTIKI_NET_H_ */
