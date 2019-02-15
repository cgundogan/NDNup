#include <stdio.h>
#include "ndnup_tlfield.h"
#include "ndnup_buffer.h"
#include "tlv.h"
#include "ndnup_interest.h"

int8_t ndnup_interest_encode(ndnup_buffer_write_t *out, ndnup_interest_t *intmsg)
{
    int8_t result = -1;
    const enum tlv_type outertlv = interest;

    /* write outer TLV */
    ndnup_tlfield_encode(out, outertlv);
    /* for now length 0 */
    ndnup_tlfield_encode(out, 0x00);

    /* for now no errors */
    result = 0;

    return result;
}
