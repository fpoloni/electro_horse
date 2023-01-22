#!/bin/sh

source ./utils.sh

./default_inits_10G.sh

# TX and Rx XCO0 OTN Global Control Register
xco0_wr 0x30 QSFP 0x001 0x0000
xco0_wr 0x30 QSFP 0x400 0x0000
xco0_wr 0x30   BP 0x400 0x0000
xco0_wr 0x30   BP 0x001 0x0000

xco0_wr 0x31 QSFP 0x001 0x0000
xco0_wr 0x31 QSFP 0x400 0x0000
xco0_wr 0x31   BP 0x400 0x0000
xco0_wr 0x31   BP 0x001 0x0000

xco0_wr 0x32 QSFP 0x001 0x0000
xco0_wr 0x32 QSFP 0x400 0x0000
xco0_wr 0x32   BP 0x400 0x0000
xco0_wr 0x32   BP 0x001 0x0000

xco0_wr 0x33 QSFP 0x001 0x0000
xco0_wr 0x33 QSFP 0x400 0x0000
xco0_wr 0x33   BP 0x400 0x0000
xco0_wr 0x33   BP 0x001 0x0000

xco0_wr 0x34 QSFP 0x001 0x0000
xco0_wr 0x34 QSFP 0x400 0x0000
xco0_wr 0x34   BP 0x400 0x0000
xco0_wr 0x34   BP 0x001 0x0000

xco0_wr 0x35 QSFP 0x001 0x0000
xco0_wr 0x35 QSFP 0x400 0x0000
xco0_wr 0x35   BP 0x400 0x0000
xco0_wr 0x35   BP 0x001 0x0000

xco0_wr 0x36 QSFP 0x001 0x0000
xco0_wr 0x36 QSFP 0x400 0x0000
xco0_wr 0x36   BP 0x400 0x0000
xco0_wr 0x36   BP 0x001 0x0000

xco0_wr 0x37 QSFP 0x001 0x0000
xco0_wr 0x37 QSFP 0x400 0x0000
xco0_wr 0x37   BP 0x400 0x0000
xco0_wr 0x37   BP 0x001 0x0000

# force TX XCO0 OTN Payload Type insertion
# 0x1a6[15] = 1
# 0x1aa[7:0]=0x07 for PCS transparent
xco0_wr 0x30 QSFP 0x1AA 0xAA07
xco0_wr 0x30 QSFP 0x1A6 0x80a0
xco0_wr 0x30   BP 0x1AA 0xAA07
xco0_wr 0x30   BP 0x1A6 0x80a0

xco0_wr 0x31 QSFP 0x1AA 0xAA07
xco0_wr 0x31 QSFP 0x1A6 0x80a0
xco0_wr 0x31   BP 0x1AA 0xAA07
xco0_wr 0x31   BP 0x1A6 0x80a0

xco0_wr 0x32 QSFP 0x1AA 0xAA07
xco0_wr 0x32 QSFP 0x1A6 0x80a0
xco0_wr 0x32   BP 0x1AA 0xAA07
xco0_wr 0x32   BP 0x1A6 0x80a0

xco0_wr 0x33 QSFP 0x1AA 0xAA07
xco0_wr 0x33 QSFP 0x1A6 0x80a0
xco0_wr 0x33   BP 0x1AA 0xAA07
xco0_wr 0x33   BP 0x1A6 0x80a0

xco0_wr 0x34 QSFP 0x1AA 0xAA07
xco0_wr 0x34 QSFP 0x1A6 0x80a0
xco0_wr 0x34   BP 0x1AA 0xAA07
xco0_wr 0x34   BP 0x1A6 0x80a0

xco0_wr 0x35 QSFP 0x1AA 0xAA07
xco0_wr 0x35 QSFP 0x1A6 0x80a0
xco0_wr 0x35   BP 0x1AA 0xAA07
xco0_wr 0x35   BP 0x1A6 0x80a0

xco0_wr 0x36 QSFP 0x1AA 0xAA07
xco0_wr 0x36 QSFP 0x1A6 0x80a0
xco0_wr 0x36   BP 0x1AA 0xAA07
xco0_wr 0x36   BP 0x1A6 0x80a0

xco0_wr 0x37 QSFP 0x1AA 0xAA07
xco0_wr 0x37 QSFP 0x1A6 0x80a0
xco0_wr 0x37   BP 0x1AA 0xAA07
xco0_wr 0x37   BP 0x1A6 0x80a0

# Force Rx expected Payload Type
# 0x6d8[7:0] = 0x07
xco0_wr  0x30 QSFP 0x6d8 0x6d07
xco0_wr  0x30   BP 0x6d8 0x6d07

xco0_wr  0x31 QSFP 0x6d8 0x6d07
xco0_wr  0x31   BP 0x6d8 0x6d07

xco0_wr  0x32 QSFP 0x6d8 0x6d07
xco0_wr  0x32   BP 0x6d8 0x6d07

xco0_wr  0x33 QSFP 0x6d8 0x6d07
xco0_wr  0x33   BP 0x6d8 0x6d07

xco0_wr  0x34 QSFP 0x6d8 0x6d07
xco0_wr  0x34   BP 0x6d8 0x6d07

xco0_wr  0x35 QSFP 0x6d8 0x6d07
xco0_wr  0x35   BP 0x6d8 0x6d07

xco0_wr  0x36 QSFP 0x6d8 0x6d07
xco0_wr  0x36   BP 0x6d8 0x6d07

xco0_wr  0x37 QSFP 0x6d8 0x6d07
xco0_wr  0x37   BP 0x6d8 0x6d07

# Set internal TS1 in ADM from QSFP and BP
# QSFP bit 0 = 0
#   BP bit 8 = 0
eki_wr 0x42 0x0 0x0

# set ODTU2.1 mapper de-mapper straight
# TS0 to internal ODU0 data path 0
# TSn to internal ODU0 data path n
# TS7 to internal ODU0 data path 7
#
# S1 mapped to internal ODU0 datapath 0 <=> TS1
# [3:0] = 0
eki_wr 0x42 0x21 0x76543210
eki_wr 0x42 0x22 0x76543210

# S1 de-mapped from internal ODU0 datapath 0 <=> TS1
# [3:0] = 0
eki_wr 0x42 0x23 0x76543210
eki_wr 0x42 0x24 0x76543210

# forces drop from east aka S10
eki_wr 0x10 0x00 0xA0340009

# OTU2 framer to insert FAS MFAS + SM OH
eki_wr 0x40 0x16 0x3fff
eki_wr 0x41 0x16 0x3fff
# OTU2 framer to insert ROW 2 OH
eki_wr 0x40 0x17 0x3fff
eki_wr 0x41 0x17 0x3fff
# OTU2 framer to insert ROW 3 OH
eki_wr 0x40 0x18 0x3fff
eki_wr 0x41 0x18 0x3fff
# OTU2 framer to insert ROW 4 OH
eki_wr 0x40 0x19 0x3fff
eki_wr 0x41 0x19 0x3fff

# All TCMs in OPERATIONAL Mode
# All TCMs SAPI + DAPI to dTIM enabled
eki_wr 0x40 0x20 0x0fff0555
eki_wr 0x41 0x20 0x0fff0555

# SM Rx SAPI trace
set_tti S10 sm rx SAPI "SM-TRC SAPI-SEC"
set_tti S9  sm rx SAPI "SM-TRC SAPI-SEC"
# SM Rx DAPI trace
set_tti S10 sm rx DAPI "SM-TRC DAPI-SEC"
set_tti S9  sm rx DAPI "SM-TRC DAPI-SEC"

# PM Rx SAPI trace
set_tti S10 pm rx SAPI "PM-TRC SAPI-SEC"
set_tti S9  pm rx SAPI "PM-TRC SAPI-SEC"
# PM Rx DAPI trace
set_tti S10 pm rx DAPI "PM-TRC DAPI-SEC"
set_tti S9  pm rx DAPI "PM-TRC DAPI-SEC"

# TCM1 Rx SAPI trace
set_tti S10 tcm1 rx SAPI "TCM1-TRACE SAPI"
set_tti S9  tcm1 rx SAPI "TCM1-TRACE SAPI"
# TCM1 Rx DAPI trace
set_tti S10 tcm1 rx DAPI "TCM1-TRACE DAPI"
set_tti S9  tcm1 rx DAPI "TCM1-TRACE DAPI"

# TCM2 Rx SAPI trace
set_tti S10 tcm2 rx SAPI "TCM2-TRACE SAPI"
set_tti S9  tcm2 rx SAPI "TCM2-TRACE SAPI"
# TCM2 Rx DAPI trace
set_tti S10 tcm2 rx DAPI "TCM2-TRACE DAPI"
set_tti S9  tcm2 rx DAPI "TCM2-TRACE DAPI"

# TCM3 Rx SAPI trace
set_tti S10 tcm3 rx SAPI "TCM3-TRACE SAPI"
set_tti S9  tcm3 rx SAPI "TCM3-TRACE SAPI"
# TCM3 Rx DAPI trace
set_tti S10 tcm3 rx DAPI "TCM3-TRACE DAPI"
set_tti S9  tcm3 rx DAPI "TCM3-TRACE DAPI"

# TCM4 Rx SAPI trace
set_tti S10 tcm4 rx SAPI "TCM4-TRACE SAPI"
set_tti S9  tcm4 rx SAPI "TCM4-TRACE SAPI"
# TCM4 Rx DAPI trace
set_tti S10 tcm4 rx DAPI "TCM4-TRACE DAPI"
set_tti S9  tcm4 rx DAPI "TCM4-TRACE DAPI"

# TCM5 Rx SAPI trace
set_tti S10 tcm5 rx SAPI "TCM5-TRACE SAPI"
set_tti S9  tcm5 rx SAPI "TCM5-TRACE SAPI"
# TCM5 Rx DAPI trace
set_tti S10 tcm5 rx DAPI "TCM5-TRACE DAPI"
set_tti S9  tcm5 rx DAPI "TCM5-TRACE DAPI"

# TCM6 Rx SAPI trace
set_tti S10 tcm6 rx SAPI "TCM6-TRACE SAPI"
set_tti S9  tcm6 rx SAPI "TCM6-TRACE SAPI"
# TCM6 Rx DAPI trace
set_tti S10 tcm6 rx DAPI "TCM6-TRACE DAPI"
set_tti S9  tcm6 rx DAPI "TCM6-TRACE DAPI"

# SM Tx SAPI trace
set_tti S10 sm tx SAPI "S10 Eki SM SAPI"
set_tti S9  sm tx SAPI "S9  Eki SM SAPI"
# SM Tx DAPI trace
set_tti S10 sm tx DAPI "S10 Eki SM DAPI"
set_tti S9  sm tx DAPI "S9  Eki SM DAPI"

# PM Tx SAPI trace
set_tti S10 pm tx SAPI "S10 Eki PM SAPI"
set_tti S9  pm tx SAPI "S9  Eki PM SAPI"
# PM Tx DAPI trace
set_tti S10 pm tx DAPI "S10 Eki PM DAPI"
set_tti S9  pm tx DAPI "S9  Eki PM DAPI"

# TCM1 Tx SAPI trace
set_tti S10 tcm1 tx SAPI "S10 EkiTcm1Sapi"
set_tti S9  tcm1 tx SAPI "S9  EkiTcm1Sapi"
# TCM1 Tx DAPI trace
set_tti S10 tcm1 tx DAPI "S10 EkiTcm1Dapi"
set_tti S9  tcm1 tx DAPI "S9  EkiTcm1Dapi"

# TCM2 Tx SAPI trace
set_tti S10 tcm2 tx SAPI "S10 EkiTcm2Sapi"
set_tti S9  tcm2 tx SAPI "S9  EkiTcm2Sapi"
# TCM2 Tx DAPI trace
set_tti S10 tcm2 tx DAPI "S10 EkiTcm2Dapi"
set_tti S9  tcm2 tx DAPI "S9  EkiTcm2Dapi"

# TCM3 Tx SAPI trace
set_tti S10 tcm3 tx SAPI "S10 EkiTcm3Sapi"
set_tti S9  tcm3 tx SAPI "S9  EkiTcm3Sapi"
# TCM3 Tx DAPI trace
set_tti S10 tcm3 tx DAPI "S10 EkiTcm3Dapi"
set_tti S9  tcm3 tx DAPI "S9  EkiTcm3Dapi"

# TCM4 Tx SAPI trace
set_tti S10 tcm4 tx SAPI "S10 EkiTcm4Sapi"
set_tti S9  tcm4 tx SAPI "S9  EkiTcm4Sapi"
# TCM4 Tx DAPI trace
set_tti S10 tcm4 tx DAPI "S10 EkiTcm4Dapi"
set_tti S9  tcm4 tx DAPI "S9  EkiTcm4Dapi"

# TCM5 Tx SAPI trace
set_tti S10 tcm5 tx SAPI "S10 EkiTcm5Sapi"
set_tti S9  tcm5 tx SAPI "S9  EkiTcm5Sapi"
# TCM5 Tx DAPI trace
set_tti S10 tcm5 tx DAPI "S10 EkiTcm5Dapi"
set_tti S9  tcm5 tx DAPI "S9  EkiTcm5Dapi"

# TCM6 Tx SAPI trace
set_tti S10 tcm6 tx SAPI "S10 EkiTcm6Sapi"
set_tti S9  tcm6 tx SAPI "S9  EkiTcm6Sapi"
# TCM6 Tx DAPI trace
set_tti S10 tcm6 tx DAPI "S10 EkiTcm6Dapi"
set_tti S9  tcm6 tx DAPI "S9  EkiTcm6Dapi"

