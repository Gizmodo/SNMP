#include "Manager.h"
#include <cstdlib>
#include <iostream>

using namespace std;
vector<std::string> IPs;
const char *hosts[3] = {
        "192.168.6.1",
        "192.168.88.1",
        "106.54.89.218"
};
const char *oids[4] = {
        ".1.3.6.1.2.1.1.1.0",
        ".1.3.6.1.2.1.1.3.0",
        ".1.3.6.1.2.1.1.4.0",
        ".1.3.6.1.2.1.1.7.0"
};

void print_result(int status, struct snmp_session *sp, struct snmp_pdu *pdu);

void test(Host h, snmp_pdu *p) {
    cout << " test called" << endl;
    print_result(STAT_SUCCESS, h.pSession, p);
}

void print_result(int status, struct snmp_session *sp, struct snmp_pdu *pdu) {
    struct variable_list *vp;
    vp = pdu->variables;

    if (!pdu->errstat == SNMP_ERR_NOERROR) {
        cout << "errstst false!" << endl;
        exit(1);
    }
    char buf[1024];
    while (vp) {
        snprint_variable(buf, sizeof(buf), vp->name, vp->name_length, vp);
        fprintf(stdout, "%s : %s\n", sp->peername, buf);
        vp = vp->next_variable;
    }
}

void initIP(bool devMode) {
    if (devMode) {
        IPs.push_back("153.19.67.9");
    } else {
        for (int i = 0; i < 190; ++i) {
            for (int j = 0; j < 255; ++j) {
                IPs.push_back("10.159." + std::to_string(i) + "." + std::to_string(j));
            }
        }
    }
}

int main() {
    initIP(true);
    Manager m;
    m.set_interval(3);
    SOCK_STARTUP;
    init_snmp("snmpapp");
    for (auto ip:IPs) {
        //for (int i = 0; i < 2; i++) {
        Host *h = new Host();;
        // h->hostName = "Host" + std::to_string(i);
        h->ip = ip;
        h->pSession = nullptr;
        h->listOid.clear();
        for (int j = 0; j < 4; j++) {
            cc_oid o;
            o.length = MAX_OID_LEN;
            if (!read_objid(oids[j], o.o, &o.length)) {
                cout << "read_objid failed!" << endl;
                return 1;
            }
            h->listOid.push_back(o);
        }
        m.add_host(h);
    }

    m.set_func(test);
    m.run();
    //while (1);
}