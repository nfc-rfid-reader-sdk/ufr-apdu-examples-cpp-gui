/*
 * uFR.h
 */

#ifndef UFR_H_
#define UFR_H_

#include "ini.h"

#define MIN_APDU_HEX_STR_LEN	5
//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
UFR_STATUS ApduCommand(const char *apdu, char **response, uint8_t *sw);
size_t hex2bin(uint8_t *dst, const char *src);
bool CheckDependencies(void);
const char *GetDlTypeName(uint8_t dl_type_code);
//------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus
#endif /* UFR_H_ */
