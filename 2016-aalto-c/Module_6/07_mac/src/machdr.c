#include "machdr.h"

/* a) Implement all get_* functions. <header> points to the start of the
 * MAC header. The functions return the value of the respective field.
 * For flags, any non-zero return value indicates that flag is set, and zero
 * means it is not set.
 */

int get_proto_version(const unsigned char *header)
{
    return header[0] >> 6;
}

int get_type(const unsigned char *header)
{
    return (header[0] >> 4) & 3;
}

int get_subtype(const unsigned char *header)
{
    return header[0] & 15;
}

int get_to_ds(const unsigned char *header)
{
    return header[1] >> 7;
}

int get_from_ds(const unsigned char *header)
{
    return (header[1] >> 6) & 1;
}

int get_retry(const unsigned char *header)
{
    return (header[1] >> 4) & 1;
}

int get_more_data(const unsigned char *header)
{
    return (header[1] >> 2) & 1;
}

/* b) Implement all set_* functions that set the values of respective
 * fields in the MAC header. <header> points to the start of the header,
 * and the second parameter indicates the value to be set.
 */

void set_proto_version(unsigned char *header, int version)
{
    header[0] = (header[0] & 63) | (version << 6);
}

void set_type(unsigned char *header, int type)
{
    header[0] = (header[0] & 207) | (type << 4);
}

void set_subtype(unsigned char *header, int subtype)
{
    header[0] = (header[0] & 240) | subtype;
}

void set_to_ds(unsigned char *header, int flag)
{
    header[1] = (header[1] & 127) | (flag << 7);
}

void set_from_ds(unsigned char *header, int flag)
{
    header[1] = (header[1] & 191) | (flag << 6);
}

void set_retry(unsigned char *header, int flag)
{
    header[1] = (header[1] & 239) | (flag << 4);
}

void set_more_data(unsigned char *header, int flag)
{
    header[1] = (header[1] & 251) | (flag << 2);
}
