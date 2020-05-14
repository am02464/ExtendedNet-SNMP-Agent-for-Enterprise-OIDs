/*
 * Note: this file originally auto-generated by mib2c
 * using mib2c.scalar.conf
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "../../include/snmpSignal.h"
#include <libpq-fe.h>
#include "../../include/postgresUtils.h"

/** Initializes the snmpSignal module */
void
init_snmpSignal(void)
{
    const oid snmpSignal_oid[] = { 1,3,6,1,4,1,53864, 3 };

  DEBUGMSGTL(("snmpSignal", "Initializing\n"));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("snmpSignal", handle_snmpSignal,
                               snmpSignal_oid, OID_LENGTH(snmpSignal_oid),
                               HANDLER_CAN_RONLY
        ));
}

int
handle_snmpSignal(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    
    int * hasError = malloc(sizeof(int));
    * hasError = 0;
    char * signal = getQueryResult(hasError);

    
    switch(reqinfo->mode) {

        case MODE_GET:
            if (*hasError)
                return SNMP_ERR_GENERR;
                
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     signal,
                                     strlen(signal));
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_snmpSignal\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
