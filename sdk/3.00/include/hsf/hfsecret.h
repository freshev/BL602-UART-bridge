#ifndef _HF_SECRET_H__
#define _HF_SECRET_H__

#define HF_PRODUCT_WRITE_MAC_MD5_MAX_LEN 20
void HSF_IAPI hfwifi_init(void);

char *hf_get_secret_sdk_from(void);

int read_mac(unsigned int addr, unsigned char *mac, char *key);

int write_wifi_mac(unsigned char *mac,char *key,int type);
int hfget_mac_write_type(void);


enum
{
	HF_NONE_WRITE_MAC_MODE=0,
	HF_PRODUCT_WRITE_MAC_MODE=1,
    HF_AT_COMMON_WRITE_MAC_MODE=2,
};
enum
{
	HF_NONE_MAC_MODE=0,
	HF_PRODUCT_WRITE_MAC_MD5=1,
    HF_WRITE_MAC_RSA=2,
};

#define SECRET_MASSAGE_SIZE 256

#endif
