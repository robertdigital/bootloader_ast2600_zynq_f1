
#if defined sg25
  #define   DDR800            1
  #define REG_MCR10           0x02080206
  #define REG_MCR14           0x07110145
  #define REG_MCR18           0x0A020200
  #define REG_MCR1C           0x00008020
  #define REG_MCR20           0x00401510
  #define REG_MCR24           0x00000200
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0x4545331F
#elif sg25E                   
  #define   DDR800            1
  #define REG_MCR10           0x02080206
  #define REG_MCR14           0x07010145
  #define REG_MCR18           0x0A010200
  #define REG_MCR1C           0x00000020
  #define REG_MCR20           0x00401510
  #define REG_MCR24           0x00000200
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0x4545331F
#elif sg187E
  #define   DDR1066           1
  #define REG_MCR10           0x02090306
  #define REG_MCR14           0x0923015C
  #define REG_MCR18           0x0E020301
  #define REG_MCR1C           0x00000020
  #define REG_MCR20           0x00401930
  #define REG_MCR24           0x00000208
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0x5D5D452A
#elif sg187
  #define   DDR1066           1
  #define REG_MCR10           0x02090306
  #define REG_MCR14           0x0924015C
  #define REG_MCR18           0x0E030301
  #define REG_MCR1C           0x00000020
  #define REG_MCR20           0x00401940
  #define REG_MCR24           0x00000208
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0x5D5D452A
#elif sg15E
  #define   DDR1333           1
  #define REG_MCR10           0x030B0307
  #define REG_MCR14           0x0B350174
  #define REG_MCR18           0x0F030302
  #define REG_MCR1C           0x00008020
  #define REG_MCR20           0x00401B50
  #define REG_MCR24           0x00000210
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0x74745635
#elif sg15
  #define   DDR1333           1
  #define REG_MCR10           0x030B0407
  #define REG_MCR14           0x0B360174
  #define REG_MCR18           0x0F040302
  #define REG_MCR1C           0x00008020
  #define REG_MCR20           0x00401B60
  #define REG_MCR24           0x00000210
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0x74745635
#elif sg125E
  #define   DDR1600           1
  #define REG_MCR10           0x030C0308
// Nikhil - modifying this so that CWL set in the MMC controller is 5
// The controller will use the value 5 + 3 = 8.
  // #define REG_MCR14           0x0D47128B
  // #define REG_MCR14           0x0D46128B
  #define REG_MCR14           0x0D36128B
  #define REG_MCR18           0x10040302
  #define REG_MCR1C           0x00000020
  //#define REG_MCR20           0x00401D70
  #define REG_MCR20           0x00401D60
  #define REG_MCR24           0x00000218
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0x8B8B673F
#elif sg125
  #define   DDR1600           1
  #define REG_MCR10           0x030C0408
  #define REG_MCR14           0x0D47128B
  #define REG_MCR18           0x10040303
  #define REG_MCR1C           0x00000020
  #define REG_MCR20           0x00401D70
  #define REG_MCR24           0x00000218
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0x8B8B673F
#elif sg107F
  #define   DDR1866           1
  #define REG_MCR10           0x040E0309
  #define REG_MCR14           0x0F5712A2
  #define REG_MCR18           0x11040303
  #define REG_MCR1C           0x00008020
  #define REG_MCR20           0x00421F70
  #define REG_MCR24           0x00000220
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0xA3A3794A
#elif sg107E
  #define   DDR1866           1
  #define REG_MCR10           0x040E0409
  #define REG_MCR14           0x0F5812A2
  #define REG_MCR18           0x11050303
  #define REG_MCR1C           0x00008020
  #define REG_MCR20           0x00421F04
  #define REG_MCR24           0x00000220
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0xA3A3794A
#elif sg107
  #define   DDR1866           1
  #define REG_MCR10           0x040E0409
  #define REG_MCR14           0x0F5912A2
  #define REG_MCR18           0x11050304
  #define REG_MCR1C           0x00008020
  #define REG_MCR20           0x00421F14
  #define REG_MCR24           0x00000220
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0xA3A3794A
#elif sg093F
  #define   DDR2133           1
  #define REG_MCR10           0x040F030A
  #define REG_MCR14           0x116823BA
  #define REG_MCR18           0x13050403
  #define REG_MCR1C           0x00000020
  #define REG_MCR20           0x00421104
  #define REG_MCR24           0x00000228
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0xBABA8A55
#elif sg093E
  #define   DDR2133           1
  #define REG_MCR10           0x040F040A
  #define REG_MCR14           0x116923BA
  #define REG_MCR18           0x13050404
  #define REG_MCR1C           0x00000020
  #define REG_MCR20           0x00421114
  #define REG_MCR24           0x00000228
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0xBABA8A55
#elif sg093
  #define   DDR2133           1
  #define REG_MCR10           0x040F040A
  #define REG_MCR14           0x116A23BA
  #define REG_MCR18           0x13060404
  #define REG_MCR1C           0x00000020
  #define REG_MCR20           0x00421124
  #define REG_MCR24           0x00000228
  #define REG_MCR28           0x00000000
  #define REG_MCR2C           0x00000000
  #define REG_MCRFC           0xBABA8A55
#elif TS_1875
  #define   DDR1066           1
  #define REG_MCR10           0x030C0207
  #define REG_MCR14           0x0A55015C
  #define REG_MCR18           0x0A040302
  #define REG_MCR1C           0x00009140
  #define REG_MCR20           0x01010100
  #define REG_MCR24           0x00000000
  #define REG_MCR28           0x04000000
  #define REG_MCR2C           0x00000400
  #define REG_MCRFC           0x5D5D452A
#elif TS_1500
  #define   DDR1333           1
  #define REG_MCR10           0x030C0207
  #define REG_MCR14           0x0C550174
  #define REG_MCR18           0x0C040303
  #define REG_MCR1C           0x00009240
  #define REG_MCR20           0x01010100
  #define REG_MCR24           0x00000000
  #define REG_MCR28           0x04000000
  #define REG_MCR2C           0x00000400
  #define REG_MCRFC           0x74745635
#elif TS_1250
  #define   DDR1600           1
  #define REG_MCR10           0x030D0307
  #define REG_MCR14           0x0D46118B
  #define REG_MCR18           0x0E050303
  #define REG_MCR1C           0x00001240
  #define REG_MCR20           0x01010304
  #define REG_MCR24           0x00000000
  #define REG_MCR28           0x04000000
  #define REG_MCR2C           0x00000400
  #define REG_MCRFC           0x8B8B673F
#elif TS_1072
  #define   DDR1866           1
  #define REG_MCR10           0x040E0308
  #define REG_MCR14           0x0F6812A2
  #define REG_MCR18           0x0E060304
  #define REG_MCR1C           0x00001240
  #define REG_MCR20           0x01010514
  #define REG_MCR24           0x00000008
  #define REG_MCR28           0x04000000
  #define REG_MCR2C           0x00000400
  #define REG_MCRFC           0xA3A3794A
#elif TS_938
  #define   DDR2133           1
  #define REG_MCR10           0x04100408
  #define REG_MCR14           0x117A22BA
  #define REG_MCR18           0x10060304
  #define REG_MCR1C           0x0000A340
  #define REG_MCR20           0x01010724
  #define REG_MCR24           0x00000010
  #define REG_MCR28           0x04000000
  #define REG_MCR2C           0x00000800
  #define REG_MCRFC           0xBABA8A55
#elif TS_833
  #define   DDR2133           1
  #define REG_MCR10           0x05110409
  #define REG_MCR14           0x138B22D1
  #define REG_MCR18           0x12060405
  #define REG_MCR1C           0x00002340
  #define REG_MCR20           0x01010930
  #define REG_MCR24           0x00000018
  #define REG_MCR28           0x04000000
  #define REG_MCR2C           0x00000800
  #define REG_MCRFC           0xD1D19B5F
#elif TS_750
  #define   DDR2133           1
  #define REG_MCR10           0x05120409
  #define REG_MCR14           0x158B23E8
  #define REG_MCR18           0x14070406
  #define REG_MCR1C           0x00003340
  #define REG_MCR20           0x01010B30
  #define REG_MCR24           0x00000018
  #define REG_MCR28           0x04000000
  #define REG_MCR2C           0x00000C00
  #define REG_MCRFC           0xE9E9AD6A
#elif TS_682
  #define   DDR2133           1
  #define REG_MCR10           0x05120409
  #define REG_MCR14           0x158B23E8
  #define REG_MCR18           0x14070406
  #define REG_MCR1C           0x00003340
  #define REG_MCR20           0x01010B30
  #define REG_MCR24           0x00000018
  #define REG_MCR28           0x04000000
  #define REG_MCR2C           0x00000C00
  #define REG_MCRFC           0xE9E9AD6A
#elif TS_625
  #define   DDR2133           1
  #define REG_MCR10           0x05120409
  #define REG_MCR14           0x158B23E8
  #define REG_MCR18           0x14070406
  #define REG_MCR1C           0x00003340
  #define REG_MCR20           0x01010B30
  #define REG_MCR24           0x00000018
  #define REG_MCR28           0x04000000
  #define REG_MCR2C           0x00000C00
  #define REG_MCRFC           0xE9E9AD6A
#endif
