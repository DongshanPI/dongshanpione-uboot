/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2011 Simon Guinot <sguinot@lacie.com>
 */

#ifndef _CONFIG_LACIE_KW_H
#define _CONFIG_LACIE_KW_H

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_FEROCEON_88FR131		/* CPU Core subversion */
/* SoC name */
#if defined(CONFIG_NETSPACE_LITE_V2) || defined(CONFIG_NETSPACE_MINI_V2)
#define CONFIG_KW88F6192
#else
#define CONFIG_KW88F6281
#endif

/*
 * SDRAM configuration
 */

/*
 * Different SDRAM configuration and size for some of the boards derived
 * from the Network Space v2
 */
#if defined(CONFIG_INETSPACE_V2)
#define CONFIG_SYS_KWD_CONFIG $(CONFIG_BOARDDIR)/kwbimage-is2.cfg
#elif defined(CONFIG_NETSPACE_LITE_V2) || defined(CONFIG_NETSPACE_MINI_V2)
#define CONFIG_SYS_KWD_CONFIG $(CONFIG_BOARDDIR)/kwbimage-ns2l.cfg
#endif

/*
 * mv-common.h should be defined after CMD configs since it used them
 * to enable certain macros
 */
#include "mv-common.h"

/* Remove or override few declarations from mv-common.h */
#undef CONFIG_SYS_IDE_MAXBUS
#undef CONFIG_SYS_IDE_MAXDEVICE

/*
 * Enable platform initialisation via misc_init_r() function
 */

/*
 * Ethernet Driver configuration
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE_PORTS		{1, 0} /* enable port 0 only */
#endif

/*
 * SATA Driver configuration
 */

#ifdef CONFIG_SATA
#define CONFIG_SYS_64BIT_LBA
#define CONFIG_LBA48
#if defined(CONFIG_NETSPACE_MAX_V2) || defined(CONFIG_D2NET_V2) || \
	defined(CONFIG_NET2BIG_V2)
#define CONFIG_SYS_SATA_MAX_DEVICE	2
#else
#define CONFIG_SYS_SATA_MAX_DEVICE	1
#endif
#endif /* CONFIG_SATA */

/*
 * Enable GPI0 support
 */
#define CONFIG_KIRKWOOD_GPIO

/*
 * Enable I2C support
 */
#ifdef CONFIG_CMD_I2C
/* I2C EEPROM HT24LC04 (512B - 32 pages of 16 Bytes) */
#if defined(CONFIG_NET2BIG_V2)
#define CONFIG_SYS_I2C_G762_ADDR		0x3e
#endif
#endif /* CONFIG_CMD_I2C */

/*
 * Partition support
 */

/*
 * File systems support
 */

/*
 * Environment variables configurations
 */

/*
 * Default environment variables
 */
#define CONFIG_BOOTCOMMAND					\
	"dhcp && run netconsole; "				\
	"if run usbload || run diskload; then bootm; fi"

#define CONFIG_EXTRA_ENV_SETTINGS				\
	"stdin=serial\0"					\
	"stdout=serial\0"					\
	"stderr=serial\0"					\
	"bootfile=uImage\0"					\
	"loadaddr=0x800000\0"					\
	"autoload=no\0"						\
	"netconsole="						\
		"set stdin $stdin,nc; "				\
		"set stdout $stdout,nc; "			\
		"set stderr $stderr,nc;\0"			\
	"diskload=sata init && "				\
		"ext2load sata 0:1 $loadaddr /boot/$bootfile\0"	\
	"usbload=usb start && "					\
		"fatload usb 0:1 $loadaddr /boot/$bootfile\0"

#endif /* _CONFIG_LACIE_KW_H */
