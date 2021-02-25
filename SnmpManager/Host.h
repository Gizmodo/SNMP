//
// Created by user on 02.02.2021.
//

#ifndef SNMPMANAGER_HOST_H
#define SNMPMANAGER_HOST_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <string>

struct cc_oid {
    oid o[MAX_OID_LEN];
    size_t length;
};

class Host {
public:
  //  std::string hostName;       //NICKNAME
    std::string ip;             //IP
    struct snmp_session *pSession;
    std::vector<cc_oid> listOid;

    Host() {}

    ~Host() {}
};

#endif //SNMPMANAGER_HOST_H
