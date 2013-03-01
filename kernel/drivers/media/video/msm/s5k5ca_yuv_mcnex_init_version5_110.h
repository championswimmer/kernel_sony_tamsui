//****************************************/
//****************************************/
//=================================================================================================
// * Name: S5K5CAGX EVT1.0 Initial Setfile
// * PLL mode: MCLK=24MHz / SYSCLK=30MHz / PCLK=60MHz
// * FPS : Preview YUV QXGA 7.5fps / Capture YUV QXGA 7.5fps
// * Analog and TnP modified(20100225)
//=================================================================================================
// ARM GO
// Direct mode
{0xFCFC, 0xD000 ,16,0},
{0x0010, 0x0001 ,16,0}, //Reset
{0x1030, 0x0000 ,16,0}, //Clear host interrupt so main will wait
{0x0014, 0x0001 ,16,10}, //ARM go
//p10 //Min.10ms delay is required

// Start T&P part
// DO NOT DELETE T&P SECTION COMMENTS! They are required to debug T&P related issues.
// svn://transrdsrv/svn/svnroot/System/Software/tcevb/SDK+FW/ISP_5CA/Firmware
// Rev: WC
// Signature:
// md5 b093df4c68b392b85938fb2d5d1a3ed8 .btp
// md5 4013ff93e02c5ca42ee80f5d436679cb .htp
// md5 8c46487f45dee2566f9a04abe3fd8f52 .RegsMap.h
// md5 90230b6b3e71c02e34af139b81219a11 .RegsMap.bin
// md5 506b4144bd48cdb79cbecdda4f7176ba .base.RegsMap.h
// md5 fd8f92f13566c1a788746b23691c5f5f .base.RegsMap.bin
//
{0x0028, 0x7000 ,16,0},
{0x002A, 0x2CF8 ,16,0},
{0x0F12, 0xB510 ,16,0},
{0x0F12, 0x4827 ,16,0},
{0x0F12, 0x21C0 ,16,0},
{0x0F12, 0x8041 ,16,0},
{0x0F12, 0x4825 ,16,0},
{0x0F12, 0x4A26 ,16,0},
{0x0F12, 0x3020 ,16,0},
{0x0F12, 0x8382 ,16,0},
{0x0F12, 0x1D12 ,16,0},
{0x0F12, 0x83C2 ,16,0},
{0x0F12, 0x4822 ,16,0},
{0x0F12, 0x3040 ,16,0},
{0x0F12, 0x8041 ,16,0},
{0x0F12, 0x4821 ,16,0},
{0x0F12, 0x4922 ,16,0},
{0x0F12, 0x3060 ,16,0},
{0x0F12, 0x8381 ,16,0},
{0x0F12, 0x1D09 ,16,0},
{0x0F12, 0x83C1 ,16,0},
{0x0F12, 0x4821 ,16,0},
{0x0F12, 0x491D ,16,0},
{0x0F12, 0x8802 ,16,0},
{0x0F12, 0x3980 ,16,0},
{0x0F12, 0x804A ,16,0},
{0x0F12, 0x8842 ,16,0},
{0x0F12, 0x808A ,16,0},
{0x0F12, 0x8882 ,16,0},
{0x0F12, 0x80CA ,16,0},
{0x0F12, 0x88C2 ,16,0},
{0x0F12, 0x810A ,16,0},
{0x0F12, 0x8902 ,16,0},
{0x0F12, 0x491C ,16,0},
{0x0F12, 0x80CA ,16,0},
{0x0F12, 0x8942 ,16,0},
{0x0F12, 0x814A ,16,0},
{0x0F12, 0x8982 ,16,0},
{0x0F12, 0x830A ,16,0},
{0x0F12, 0x89C2 ,16,0},
{0x0F12, 0x834A ,16,0},
{0x0F12, 0x8A00 ,16,0},
{0x0F12, 0x4918 ,16,0},
{0x0F12, 0x8188 ,16,0},
{0x0F12, 0x4918 ,16,0},
{0x0F12, 0x4819 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xFA0C ,16,0},
{0x0F12, 0x4918 ,16,0},
{0x0F12, 0x4819 ,16,0},
{0x0F12, 0x6341 ,16,0},
{0x0F12, 0x4919 ,16,0},
{0x0F12, 0x4819 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xFA05 ,16,0},
{0x0F12, 0x4816 ,16,0},
{0x0F12, 0x4918 ,16,0},
{0x0F12, 0x3840 ,16,0},
{0x0F12, 0x62C1 ,16,0},
{0x0F12, 0x4918 ,16,0},
{0x0F12, 0x3880 ,16,0},
{0x0F12, 0x63C1 ,16,0},
{0x0F12, 0x4917 ,16,0},
{0x0F12, 0x6301 ,16,0},
{0x0F12, 0x4917 ,16,0},
{0x0F12, 0x3040 ,16,0},
{0x0F12, 0x6181 ,16,0},
{0x0F12, 0x4917 ,16,0},
{0x0F12, 0x4817 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF9F5 ,16,0},
{0x0F12, 0x4917 ,16,0},
{0x0F12, 0x4817 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF9F1 ,16,0},
{0x0F12, 0x4917 ,16,0},
{0x0F12, 0x4817 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF9ED ,16,0},
{0x0F12, 0xBC10 ,16,0},
{0x0F12, 0xBC08 ,16,0},
{0x0F12, 0x4718 ,16,0},
{0x0F12, 0x1100 ,16,0},
{0x0F12, 0xD000 ,16,0},
{0x0F12, 0x267C ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x2CE8 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x3274 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0xF400 ,16,0},
{0x0F12, 0xD000 ,16,0},
{0x0F12, 0xF520 ,16,0},
{0x0F12, 0xD000 ,16,0},
{0x0F12, 0x2DF1 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x89A9 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x2E43 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x0140 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x2E75 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0xB4F7 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x2EFF ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x2F23 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x2FCD ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x2FE1 ,16,0},
{0x0F12, 0x7000 ,16,0},

{0x0F12, 0x2FB5 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x013D ,16,0},
{0x0F12, 0x0001 ,16,0},
{0x0F12, 0x3067 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x5823 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x30B5 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0xD789 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0xB570 ,16,0},
{0x0F12, 0x6804 ,16,0},
{0x0F12, 0x6845 ,16,0},
{0x0F12, 0x6881 ,16,0},
{0x0F12, 0x6840 ,16,0},
{0x0F12, 0x2900 ,16,0},
{0x0F12, 0x6880 ,16,0},
{0x0F12, 0xD007 ,16,0},
{0x0F12, 0x49C2 ,16,0},
{0x0F12, 0x8949 ,16,0},
{0x0F12, 0x084A ,16,0},
{0x0F12, 0x1880 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF9B8 ,16,0},
{0x0F12, 0x80A0 ,16,0},
{0x0F12, 0xE000 ,16,0},
{0x0F12, 0x80A0 ,16,0},
{0x0F12, 0x88A0 ,16,0},
{0x0F12, 0x2800 ,16,0},
{0x0F12, 0xD010 ,16,0},
{0x0F12, 0x68A9 ,16,0},
{0x0F12, 0x6828 ,16,0},
{0x0F12, 0x084A ,16,0},
{0x0F12, 0x1880 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF9AC ,16,0},
{0x0F12, 0x8020 ,16,0},
{0x0F12, 0x1D2D ,16,0},
{0x0F12, 0xCD03 ,16,0},
{0x0F12, 0x084A ,16,0},
{0x0F12, 0x1880 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF9A5 ,16,0},
{0x0F12, 0x8060 ,16,0},
{0x0F12, 0xBC70 ,16,0},
{0x0F12, 0xBC08 ,16,0},
{0x0F12, 0x4718 ,16,0},
{0x0F12, 0x2000 ,16,0},
{0x0F12, 0x8060 ,16,0},
{0x0F12, 0x8020 ,16,0},
{0x0F12, 0xE7F8 ,16,0},
{0x0F12, 0xB510 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF9A0 ,16,0},
{0x0F12, 0x48B1 ,16,0},
{0x0F12, 0x49B2 ,16,0},
{0x0F12, 0x8800 ,16,0},
{0x0F12, 0x4AB2 ,16,0},
{0x0F12, 0x2805 ,16,0},
{0x0F12, 0xD003 ,16,0},
{0x0F12, 0x4BB1 ,16,0},
{0x0F12, 0x795B ,16,0},
{0x0F12, 0x2B00 ,16,0},
{0x0F12, 0xD005 ,16,0},
{0x0F12, 0x2001 ,16,0},
{0x0F12, 0x8008 ,16,0},
{0x0F12, 0x8010 ,16,0},
{0x0F12, 0xBC10 ,16,0},
{0x0F12, 0xBC08 ,16,0},
{0x0F12, 0x4718 ,16,0},
{0x0F12, 0x2800 ,16,0},
{0x0F12, 0xD1FA ,16,0},
{0x0F12, 0x2000 ,16,0},
{0x0F12, 0x8008 ,16,0},
{0x0F12, 0x8010 ,16,0},
{0x0F12, 0xE7F6 ,16,0},
{0x0F12, 0xB5F8 ,16,0},
{0x0F12, 0x2407 ,16,0},
{0x0F12, 0x2C06 ,16,0},
{0x0F12, 0xD035 ,16,0},
{0x0F12, 0x2C07 ,16,0},
{0x0F12, 0xD033 ,16,0},
{0x0F12, 0x48A3 ,16,0},
{0x0F12, 0x8BC1 ,16,0},
{0x0F12, 0x2900 ,16,0},
{0x0F12, 0xD02A ,16,0},
{0x0F12, 0x00A2 ,16,0},
{0x0F12, 0x1815 ,16,0},
{0x0F12, 0x4AA4 ,16,0},
{0x0F12, 0x6DEE ,16,0},
{0x0F12, 0x8A92 ,16,0},
{0x0F12, 0x4296 ,16,0},
{0x0F12, 0xD923 ,16,0},
{0x0F12, 0x0028 ,16,0},
{0x0F12, 0x3080 ,16,0},
{0x0F12, 0x0007 ,16,0},
{0x0F12, 0x69C0 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF96D ,16,0},
{0x0F12, 0x1C71 ,16,0},
{0x0F12, 0x0280 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF969 ,16,0},
{0x0F12, 0x0006 ,16,0},
{0x0F12, 0x4898 ,16,0},
{0x0F12, 0x0061 ,16,0},
{0x0F12, 0x1808 ,16,0},
{0x0F12, 0x8D80 ,16,0},
{0x0F12, 0x0A01 ,16,0},
{0x0F12, 0x0600 ,16,0},
{0x0F12, 0x0E00 ,16,0},
{0x0F12, 0x1A08 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF96C ,16,0},
{0x0F12, 0x0002 ,16,0},
{0x0F12, 0x6DE9 ,16,0},
{0x0F12, 0x6FE8 ,16,0},
{0x0F12, 0x1A08 ,16,0},
{0x0F12, 0x4351 ,16,0},
{0x0F12, 0x0300 ,16,0},
{0x0F12, 0x1C49 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF955 ,16,0},
{0x0F12, 0x0401 ,16,0},
{0x0F12, 0x0430 ,16,0},
{0x0F12, 0x0C00 ,16,0},
{0x0F12, 0x4301 ,16,0},
{0x0F12, 0x61F9 ,16,0},
{0x0F12, 0xE004 ,16,0},
{0x0F12, 0x00A2 ,16,0},
{0x0F12, 0x4990 ,16,0},
{0x0F12, 0x1810 ,16,0},
{0x0F12, 0x3080 ,16,0},
{0x0F12, 0x61C1 ,16,0},
{0x0F12, 0x1E64 ,16,0},
{0x0F12, 0xD2C5 ,16,0},
{0x0F12, 0x2006 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF95B ,16,0},
{0x0F12, 0x2007 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF958 ,16,0},
{0x0F12, 0xBCF8 ,16,0},
{0x0F12, 0xBC08 ,16,0},
{0x0F12, 0x4718 ,16,0},
{0x0F12, 0xB510 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF95A ,16,0},
{0x0F12, 0x2800 ,16,0},
{0x0F12, 0xD00A ,16,0},
{0x0F12, 0x4881 ,16,0},
{0x0F12, 0x8B81 ,16,0},
{0x0F12, 0x0089 ,16,0},
{0x0F12, 0x1808 ,16,0},
{0x0F12, 0x6DC1 ,16,0},
{0x0F12, 0x4883 ,16,0},
{0x0F12, 0x8A80 ,16,0},
{0x0F12, 0x4281 ,16,0},
{0x0F12, 0xD901 ,16,0},
{0x0F12, 0x2001 ,16,0},
{0x0F12, 0xE7A1 ,16,0},
{0x0F12, 0x2000 ,16,0},
{0x0F12, 0xE79F ,16,0},
{0x0F12, 0xB5F8 ,16,0},
{0x0F12, 0x0004 ,16,0},
{0x0F12, 0x4F80 ,16,0},
{0x0F12, 0x227D ,16,0},
{0x0F12, 0x8938 ,16,0},
{0x0F12, 0x0152 ,16,0},
{0x0F12, 0x4342 ,16,0},
{0x0F12, 0x487E ,16,0},
{0x0F12, 0x9000 ,16,0},
{0x0F12, 0x8A01 ,16,0},
{0x0F12, 0x0848 ,16,0},
{0x0F12, 0x1810 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF91F ,16,0},
{0x0F12, 0x210F ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF942 ,16,0},
{0x0F12, 0x497A ,16,0},
{0x0F12, 0x8C49 ,16,0},
{0x0F12, 0x090E ,16,0},
{0x0F12, 0x0136 ,16,0},
{0x0F12, 0x4306 ,16,0},
{0x0F12, 0x4979 ,16,0},
{0x0F12, 0x2C00 ,16,0},
{0x0F12, 0xD003 ,16,0},
{0x0F12, 0x2001 ,16,0},
{0x0F12, 0x0240 ,16,0},
{0x0F12, 0x4330 ,16,0},
{0x0F12, 0x8108 ,16,0},
{0x0F12, 0x4876 ,16,0},
{0x0F12, 0x2C00 ,16,0},
{0x0F12, 0x8D00 ,16,0},
{0x0F12, 0xD001 ,16,0},
{0x0F12, 0x2501 ,16,0},
{0x0F12, 0xE000 ,16,0},
{0x0F12, 0x2500 ,16,0},
{0x0F12, 0x4972 ,16,0},
{0x0F12, 0x4328 ,16,0},
{0x0F12, 0x8008 ,16,0},
{0x0F12, 0x207D ,16,0},
{0x0F12, 0x00C0 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF930 ,16,0},
{0x0F12, 0x2C00 ,16,0},
{0x0F12, 0x496E ,16,0},
{0x0F12, 0x0328 ,16,0},
{0x0F12, 0x4330 ,16,0},
{0x0F12, 0x8108 ,16,0},
{0x0F12, 0x88F8 ,16,0},
{0x0F12, 0x2C00 ,16,0},
{0x0F12, 0x01AA ,16,0},
{0x0F12, 0x4310 ,16,0},
{0x0F12, 0x8088 ,16,0},
{0x0F12, 0x2C00 ,16,0},
{0x0F12, 0xD00B ,16,0},
{0x0F12, 0x9800 ,16,0},
{0x0F12, 0x8A01 ,16,0},
{0x0F12, 0x4869 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF8F1 ,16,0},
{0x0F12, 0x4969 ,16,0},
{0x0F12, 0x8809 ,16,0},
{0x0F12, 0x4348 ,16,0},
{0x0F12, 0x0400 ,16,0},
{0x0F12, 0x0C00 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF918 ,16,0},
{0x0F12, 0x0020 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF91D ,16,0},
{0x0F12, 0x4865 ,16,0},
{0x0F12, 0x7004 ,16,0},
{0x0F12, 0xE7A1 ,16,0},
{0x0F12, 0xB510 ,16,0},
{0x0F12, 0x0004 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF91E ,16,0},
{0x0F12, 0x6020 ,16,0},
{0x0F12, 0x4962 ,16,0},
{0x0F12, 0x8B49 ,16,0},
{0x0F12, 0x0789 ,16,0},
{0x0F12, 0xD001 ,16,0},
{0x0F12, 0x0040 ,16,0},
{0x0F12, 0x6020 ,16,0},
{0x0F12, 0xE74A ,16,0},
{0x0F12, 0xB510 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF91B ,16,0},
{0x0F12, 0x485E ,16,0},
{0x0F12, 0x8880 ,16,0},
{0x0F12, 0x0601 ,16,0},
{0x0F12, 0x4853 ,16,0},
{0x0F12, 0x1609 ,16,0},
{0x0F12, 0x8141 ,16,0},
{0x0F12, 0xE740 ,16,0},
{0x0F12, 0xB5F8 ,16,0},
{0x0F12, 0x000F ,16,0},
{0x0F12, 0x4C54 ,16,0},
{0x0F12, 0x3420 ,16,0},
{0x0F12, 0x2500 ,16,0},
{0x0F12, 0x5765 ,16,0},
{0x0F12, 0x0039 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF913 ,16,0},
{0x0F12, 0x9000 ,16,0},
{0x0F12, 0x2600 ,16,0},
{0x0F12, 0x57A6 ,16,0},
{0x0F12, 0x4C4B ,16,0},
{0x0F12, 0x42AE ,16,0},
{0x0F12, 0xD01B ,16,0},
{0x0F12, 0x4D53 ,16,0},
{0x0F12, 0x8AE8 ,16,0},
{0x0F12, 0x2800 ,16,0},
{0x0F12, 0xD013 ,16,0},
{0x0F12, 0x484C ,16,0},
{0x0F12, 0x8A01 ,16,0},
{0x0F12, 0x8B80 ,16,0},
{0x0F12, 0x4378 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF8B5 ,16,0},
{0x0F12, 0x89A9 ,16,0},
{0x0F12, 0x1A41 ,16,0},
{0x0F12, 0x484D ,16,0},
{0x0F12, 0x3820 ,16,0},
{0x0F12, 0x8AC0 ,16,0},
{0x0F12, 0x4348 ,16,0},
{0x0F12, 0x17C1 ,16,0},
{0x0F12, 0x0D89 ,16,0},
{0x0F12, 0x1808 ,16,0},
{0x0F12, 0x1280 ,16,0},
{0x0F12, 0x8961 ,16,0},
{0x0F12, 0x1A08 ,16,0},
{0x0F12, 0x8160 ,16,0},
{0x0F12, 0xE003 ,16,0},
{0x0F12, 0x88A8 ,16,0},
{0x0F12, 0x0600 ,16,0},
{0x0F12, 0x1600 ,16,0},
{0x0F12, 0x8160 ,16,0},
{0x0F12, 0x200A ,16,0},
{0x0F12, 0x5E20 ,16,0},
{0x0F12, 0x42B0 ,16,0},
{0x0F12, 0xD011 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF8AB ,16,0},
{0x0F12, 0x1D40 ,16,0},
{0x0F12, 0x00C3 ,16,0},
{0x0F12, 0x1A18 ,16,0},
{0x0F12, 0x214B ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF897 ,16,0},
{0x0F12, 0x211F ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF8BA ,16,0},
{0x0F12, 0x210A ,16,0},
{0x0F12, 0x5E61 ,16,0},
{0x0F12, 0x0FC9 ,16,0},
{0x0F12, 0x0149 ,16,0},
{0x0F12, 0x4301 ,16,0},
{0x0F12, 0x483C ,16,0},
{0x0F12, 0x81C1 ,16,0},
{0x0F12, 0x9800 ,16,0},
{0x0F12, 0xE748 ,16,0},
{0x0F12, 0xB5F1 ,16,0},
{0x0F12, 0xB082 ,16,0},
{0x0F12, 0x2500 ,16,0},
{0x0F12, 0x4839 ,16,0},
{0x0F12, 0x9001 ,16,0},
{0x0F12, 0x2400 ,16,0},
{0x0F12, 0x2028 ,16,0},
{0x0F12, 0x4368 ,16,0},
{0x0F12, 0x4A39 ,16,0},
{0x0F12, 0x4937 ,16,0},
{0x0F12, 0x1887 ,16,0},
{0x0F12, 0x1840 ,16,0},
{0x0F12, 0x9000 ,16,0},
{0x0F12, 0x9800 ,16,0},
{0x0F12, 0x0066 ,16,0},
{0x0F12, 0x9A01 ,16,0},
{0x0F12, 0x1980 ,16,0},
{0x0F12, 0x218C ,16,0},
{0x0F12, 0x5A09 ,16,0},
{0x0F12, 0x8A80 ,16,0},
{0x0F12, 0x8812 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF8CA ,16,0},
{0x0F12, 0x53B8 ,16,0},
{0x0F12, 0x1C64 ,16,0},
{0x0F12, 0x2C14 ,16,0},
{0x0F12, 0xDBF1 ,16,0},
{0x0F12, 0x1C6D ,16,0},
{0x0F12, 0x2D03 ,16,0},
{0x0F12, 0xDBE6 ,16,0},
{0x0F12, 0x9802 ,16,0},
{0x0F12, 0x6800 ,16,0},
{0x0F12, 0x0600 ,16,0},
{0x0F12, 0x0E00 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF8C5 ,16,0},
{0x0F12, 0xBCFE ,16,0},
{0x0F12, 0xBC08 ,16,0},
{0x0F12, 0x4718 ,16,0},
{0x0F12, 0xB570 ,16,0},
{0x0F12, 0x6805 ,16,0},
{0x0F12, 0x2404 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF8C5 ,16,0},
{0x0F12, 0x2800 ,16,0},
{0x0F12, 0xD103 ,16,0},
{0x0F12, 0xF000 ,16,0},
{0x0F12, 0xF8C9 ,16,0},
{0x0F12, 0x2800 ,16,0},
{0x0F12, 0xD000 ,16,0},
{0x0F12, 0x2400 ,16,0},
{0x0F12, 0x3540 ,16,0},
{0x0F12, 0x88E8 ,16,0},
{0x0F12, 0x0500 ,16,0},
{0x0F12, 0xD403 ,16,0},
{0x0F12, 0x4822 ,16,0},
{0x0F12, 0x89C0 ,16,0},
{0x0F12, 0x2800 ,16,0},
{0x0F12, 0xD002 ,16,0},
{0x0F12, 0x2008 ,16,0},
{0x0F12, 0x4304 ,16,0},
{0x0F12, 0xE001 ,16,0},
{0x0F12, 0x2010 ,16,0},
{0x0F12, 0x4304 ,16,0},
{0x0F12, 0x481F ,16,0},
{0x0F12, 0x8B80 ,16,0},
{0x0F12, 0x0700 ,16,0},
{0x0F12, 0x0F81 ,16,0},
{0x0F12, 0x2001 ,16,0},
{0x0F12, 0x2900 ,16,0},
{0x0F12, 0xD000 ,16,0},
{0x0F12, 0x4304 ,16,0},
{0x0F12, 0x491C ,16,0},
{0x0F12, 0x8B0A ,16,0},
{0x0F12, 0x42A2 ,16,0},
{0x0F12, 0xD004 ,16,0},
{0x0F12, 0x0762 ,16,0},
{0x0F12, 0xD502 ,16,0},
{0x0F12, 0x4A19 ,16,0},
{0x0F12, 0x3220 ,16,0},
{0x0F12, 0x8110 ,16,0},
{0x0F12, 0x830C ,16,0},
{0x0F12, 0xE693 ,16,0},
{0x0F12, 0x0C3C ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x26E8 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x6100 ,16,0},
{0x0F12, 0xD000 ,16,0},
{0x0F12, 0x6500 ,16,0},
{0x0F12, 0xD000 ,16,0},
{0x0F12, 0x1A7C ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x1120 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0xFFFF ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x3374 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x1D6C ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x167C ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0xF400 ,16,0},
{0x0F12, 0xD000 ,16,0},
{0x0F12, 0x2C2C ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x40A0 ,16,0},
{0x0F12, 0x00DD ,16,0},
{0x0F12, 0xF520 ,16,0},
{0x0F12, 0xD000 ,16,0},
{0x0F12, 0x2C29 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x1A54 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x1564 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0xF2A0 ,16,0},
{0x0F12, 0xD000 ,16,0},
{0x0F12, 0x2440 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x3274 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x05A0 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x2894 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0x1224 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x0F12, 0xB000 ,16,0},
{0x0F12, 0xD000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0x1A3F ,16,0},
{0x0F12, 0x0001 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xF004 ,16,0},
{0x0F12, 0xE51F ,16,0},
{0x0F12, 0x1F48 ,16,0},
{0x0F12, 0x0001 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0x24BD ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0x36DD ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0xB4CF ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0xB5D7 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0x36ED ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0xF53F ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0xF5D9 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0x013D ,16,0},
{0x0F12, 0x0001 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0xF5C9 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0xFAA9 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0x3723 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0x5823 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0xD771 ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x4778 ,16,0},
{0x0F12, 0x46C0 ,16,0},
{0x0F12, 0xC000 ,16,0},
{0x0F12, 0xE59F ,16,0},
{0x0F12, 0xFF1C ,16,0},
{0x0F12, 0xE12F ,16,0},
{0x0F12, 0xD75B ,16,0},
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x7E77 ,16,0},
{0x0F12, 0x0000 ,16,0}, // End T&P part

{0x0028, 0x7000 ,16,0}, // CIS/APS/Analog setting   
{0x002A, 0x157A ,16,0},
{0x0F12, 0x0001 ,16,0},
{0x002A, 0x1578 ,16,0},
{0x0F12, 0x0001 ,16,0},
{0x002A, 0x1576 ,16,0},
{0x0F12, 0x0020 ,16,0},
{0x002A, 0x1574 ,16,0},
{0x0F12, 0x0006 ,16,0},
{0x002A, 0x156E ,16,0},
{0x0F12, 0x0001 ,16,0}, // Slope calibration tolerance in units of 1/256
{0x002A, 0x1568 ,16,0},
{0x0F12, 0x00FC ,16,0},
{0x002A, 0x155A ,16,0}, //ADC control
{0x0F12, 0x01CC ,16,0}, //ADC SAT of 450mV for 10bit default in EVT1
{0x002A, 0x157E ,16,0},
{0x0F12, 0x0C80 ,16,0}, // 3200 Max. Reset ramp DCLK counts (default 2048 800)
{0x0F12, 0x0578 ,16,0}, // 1400 Max. Reset ramp DCLK counts for x3.5
{0x002A, 0x157C ,16,0},
{0x0F12, 0x0190 ,16,0}, // 400 Reset ramp for x1 in DCLK counts
{0x002A, 0x1570 ,16,0},
{0x0F12, 0x00A0 ,16,0}, // 256 LSB
{0x0F12, 0x0010 ,16,0}, // reset threshold
{0x002A, 0x12C4 ,16,0},
{0x0F12, 0x006A ,16,0}, // 106 additional timing columns.
{0x002A, 0x12C8 ,16,0},
{0x0F12, 0x08AC ,16,0}, // 2220 ADC columns in normal mode including Hold & Latch
{0x0F12, 0x0050 ,16,0}, // 80 addition of ADC columns in Y-ave mode (default 244 74)
{0x002A, 0x1696 ,16,0}, //WRITE #senHal_ForceModeType   0001 // Long exposure mode
{0x0F12, 0x0000 ,16,0}, // based on APS guidelines
{0x0F12, 0x0000 ,16,0}, // based on APS guidelines
{0x0F12, 0x00C6 ,16,0}, // default. 1492 used for ADC dark characteristics
{0x0F12, 0x00C6 ,16,0},
{0x002A, 0x12B8 ,16,0},
{0x0F12, 0x0B00 ,16,0}, //disable CINTR 0
{0x002A, 0x1690 ,16,0},
{0x0F12, 0x0001 ,16,0}, // when set double sampling is activated - requires different set of pointers
{0x002A, 0x12B0 ,16,0},
{0x0F12, 0x0055 ,16,0}, // comp and pixel bias control F40E - default for EVT1
{0x0F12, 0x005A ,16,0}, // comp and pixel bias control F40E for binning mode
{0x002A, 0x337A ,16,0},
{0x0F12, 0x0006 ,16,0}, // [7] - is used for rest-only mode (EVT0 value is D and HW 6)
{0x0F12, 0x0068 ,16,0}, // 104M
{0x002A, 0x327C ,16,0},
{0x0F12, 0x1000 ,16,0}, // [11]: Enable DBLR Regulation
{0x0F12, 0x6998 ,16,0}, //7996// [3:0]: VPIX ~2.8V ****
{0x0F12, 0x0078 ,16,0}, // [0]: Static RC-filter
{0x0F12, 0x04FE ,16,0}, // [7:4]: Full RC-filter
{0x0F12, 0x8800 ,16,0}, // [11]: Add load to CDS block
{0x002A, 0x3274 ,16,0},
{0x0F12, 0x0155 ,16,0}, //#Tune_TP_IO_DrivingCurrent_D0_D4_cs10Set IO driving current 
{0x0F12, 0x0155 ,16,0}, //#Tune_TP_IO_DrivingCurrent_D9_D5_cs10Set IO driving current
{0x0F12, 0x1555 ,16,0}, //#Tune_TP_IO_DrivingCurrent_GPIO_cd10 Set IO driving current
{0x0F12, 0x0FFF ,16,0}, //#Tune_TP_IO_DrivingCurrent_CLKs_cd10 Set IO driving current
{0x002A, 0x169E ,16,0},
{0x0F12, 0x0007 ,16,0}, // [3:0]- specifies the target (default 7)- DCLK = 64MHz instead of 116MHz.
{0x002A, 0x0BF6 ,16,0},
{0x0F12, 0x0000 ,16,0}, //from ALEX //Enable Bayer Downscaler
{0x0028, 0x7000 ,16,0}, //Asserting CDS pointers - Long exposure MS Normal
{0x002A, 0x12D2 ,16,0},
{0x0F12, 0x0003 ,16,0}, //#senHal_pContSenModesRegsArray[0][0]2 700012D2
{0x0F12, 0x0003 ,16,0}, //#senHal_pContSenModesRegsArray[0][1]2 700012D4
{0x0F12, 0x0003 ,16,0}, //#senHal_pContSenModesRegsArray[0][2]2 700012D6
{0x0F12, 0x0003 ,16,0}, //#senHal_pContSenModesRegsArray[0][3]2 700012D8
{0x0F12, 0x0884 ,16,0}, //#senHal_pContSenModesRegsArray[1][0]2 700012DA
{0x0F12, 0x08CF ,16,0}, //#senHal_pContSenModesRegsArray[1][1]2 700012DC
{0x0F12, 0x0500 ,16,0}, //#senHal_pContSenModesRegsArray[1][2]2 700012DE
{0x0F12, 0x054B ,16,0}, //#senHal_pContSenModesRegsArray[1][3]2 700012E0
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[2][0]2 700012E2
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[2][1]2 700012E4
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[2][2]2 700012E6
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[2][3]2 700012E8
{0x0F12, 0x0885 ,16,0}, //#senHal_pContSenModesRegsArray[3][0]2 700012EA
{0x0F12, 0x0467 ,16,0}, //#senHal_pContSenModesRegsArray[3][1]2 700012EC
{0x0F12, 0x0501 ,16,0}, //#senHal_pContSenModesRegsArray[3][2]2 700012EE
{0x0F12, 0x02A5 ,16,0}, //#senHal_pContSenModesRegsArray[3][3]2 700012F0
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[4][0]2 700012F2
{0x0F12, 0x046A ,16,0}, //#senHal_pContSenModesRegsArray[4][1]2 700012F4
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[4][2]2 700012F6
{0x0F12, 0x02A8 ,16,0}, //#senHal_pContSenModesRegsArray[4][3]2 700012F8
{0x0F12, 0x0885 ,16,0}, //#senHal_pContSenModesRegsArray[5][0]2 700012FA
{0x0F12, 0x08D0 ,16,0}, //#senHal_pContSenModesRegsArray[5][1]2 700012FC
{0x0F12, 0x0501 ,16,0}, //#senHal_pContSenModesRegsArray[5][2]2 700012FE
{0x0F12, 0x054C ,16,0}, //#senHal_pContSenModesRegsArray[5][3]2 70001300
{0x0F12, 0x0006 ,16,0}, //#senHal_pContSenModesRegsArray[6][0]2 70001302
{0x0F12, 0x0020 ,16,0}, //#senHal_pContSenModesRegsArray[6][1]2 70001304
{0x0F12, 0x0006 ,16,0}, //#senHal_pContSenModesRegsArray[6][2]2 70001306
{0x0F12, 0x0020 ,16,0}, //#senHal_pContSenModesRegsArray[6][3]2 70001308
{0x0F12, 0x0881 ,16,0}, //#senHal_pContSenModesRegsArray[7][0]2 7000130A
{0x0F12, 0x0463 ,16,0}, //#senHal_pContSenModesRegsArray[7][1]2 7000130C
{0x0F12, 0x04FD ,16,0}, //#senHal_pContSenModesRegsArray[7][2]2 7000130E
{0x0F12, 0x02A1 ,16,0}, //#senHal_pContSenModesRegsArray[7][3]2 70001310
{0x0F12, 0x0006 ,16,0}, //#senHal_pContSenModesRegsArray[8][0]2 70001312
{0x0F12, 0x0489 ,16,0}, //#senHal_pContSenModesRegsArray[8][1]2 70001314
{0x0F12, 0x0006 ,16,0}, //#senHal_pContSenModesRegsArray[8][2]2 70001316
{0x0F12, 0x02C7 ,16,0}, //#senHal_pContSenModesRegsArray[8][3]2 70001318
{0x0F12, 0x0881 ,16,0}, //#senHal_pContSenModesRegsArray[9][0]2 7000131A
{0x0F12, 0x08CC ,16,0}, //#senHal_pContSenModesRegsArray[9][1]2 7000131C
{0x0F12, 0x04FD ,16,0}, //#senHal_pContSenModesRegsArray[9][2]2 7000131E
{0x0F12, 0x0548 ,16,0}, //#senHal_pContSenModesRegsArray[9][3]2 70001320
{0x0F12, 0x03A2 ,16,0}, //#senHal_pContSenModesRegsArray[10][0] 2 70001322
{0x0F12, 0x01D3 ,16,0}, //#senHal_pContSenModesRegsArray[10][1] 2 70001324
{0x0F12, 0x01E0 ,16,0}, //#senHal_pContSenModesRegsArray[10][2] 2 70001326
{0x0F12, 0x00F2 ,16,0}, //#senHal_pContSenModesRegsArray[10][3] 2 70001328
{0x0F12, 0x03F2 ,16,0}, //#senHal_pContSenModesRegsArray[11][0] 2 7000132A
{0x0F12, 0x0223 ,16,0}, //#senHal_pContSenModesRegsArray[11][1] 2 7000132C
{0x0F12, 0x0230 ,16,0}, //#senHal_pContSenModesRegsArray[11][2] 2 7000132E
{0x0F12, 0x0142 ,16,0}, //#senHal_pContSenModesRegsArray[11][3] 2 70001330
{0x0F12, 0x03A2 ,16,0}, //#senHal_pContSenModesRegsArray[12][0] 2 70001332
{0x0F12, 0x063C ,16,0}, //#senHal_pContSenModesRegsArray[12][1] 2 70001334
{0x0F12, 0x01E0 ,16,0}, //#senHal_pContSenModesRegsArray[12][2] 2 70001336
{0x0F12, 0x0399 ,16,0}, //#senHal_pContSenModesRegsArray[12][3] 2 70001338
{0x0F12, 0x03F2 ,16,0}, //#senHal_pContSenModesRegsArray[13][0] 2 7000133A
{0x0F12, 0x068C ,16,0}, //#senHal_pContSenModesRegsArray[13][1] 2 7000133C
{0x0F12, 0x0230 ,16,0}, //#senHal_pContSenModesRegsArray[13][2] 2 7000133E
{0x0F12, 0x03E9 ,16,0}, //#senHal_pContSenModesRegsArray[13][3] 2 70001340
{0x0F12, 0x0002 ,16,0}, //#senHal_pContSenModesRegsArray[14][0] 2 70001342
{0x0F12, 0x0002 ,16,0}, //#senHal_pContSenModesRegsArray[14][1] 2 70001344
{0x0F12, 0x0002 ,16,0}, //#senHal_pContSenModesRegsArray[14][2] 2 70001346
{0x0F12, 0x0002 ,16,0}, //#senHal_pContSenModesRegsArray[14][3] 2 70001348
{0x0F12, 0x003C ,16,0}, //#senHal_pContSenModesRegsArray[15][0] 2 7000134A
{0x0F12, 0x003C ,16,0}, //#senHal_pContSenModesRegsArray[15][1] 2 7000134C
{0x0F12, 0x003C ,16,0}, //#senHal_pContSenModesRegsArray[15][2] 2 7000134E
{0x0F12, 0x003C ,16,0}, //#senHal_pContSenModesRegsArray[15][3] 2 70001350
{0x0F12, 0x01D3 ,16,0}, //#senHal_pContSenModesRegsArray[16][0] 2 70001352
{0x0F12, 0x01D3 ,16,0}, //#senHal_pContSenModesRegsArray[16][1] 2 70001354
{0x0F12, 0x00F2 ,16,0}, //#senHal_pContSenModesRegsArray[16][2] 2 70001356
{0x0F12, 0x00F2 ,16,0}, //#senHal_pContSenModesRegsArray[16][3] 2 70001358
{0x0F12, 0x020B ,16,0}, //#senHal_pContSenModesRegsArray[17][0] 2 7000135A
{0x0F12, 0x024A ,16,0}, //#senHal_pContSenModesRegsArray[17][1] 2 7000135C
{0x0F12, 0x012A ,16,0}, //#senHal_pContSenModesRegsArray[17][2] 2 7000135E
{0x0F12, 0x0169 ,16,0}, //#senHal_pContSenModesRegsArray[17][3] 2 70001360
{0x0F12, 0x0002 ,16,0}, //#senHal_pContSenModesRegsArray[18][0] 2 70001362
{0x0F12, 0x046B ,16,0}, //#senHal_pContSenModesRegsArray[18][1] 2 70001364
{0x0F12, 0x0002 ,16,0}, //#senHal_pContSenModesRegsArray[18][2] 2 70001366
{0x0F12, 0x02A9 ,16,0}, //#senHal_pContSenModesRegsArray[18][3] 2 70001368
{0x0F12, 0x0419 ,16,0}, //#senHal_pContSenModesRegsArray[19][0] 2 7000136A
{0x0F12, 0x04A5 ,16,0}, //#senHal_pContSenModesRegsArray[19][1] 2 7000136C
{0x0F12, 0x0257 ,16,0}, //#senHal_pContSenModesRegsArray[19][2] 2 7000136E
{0x0F12, 0x02E3 ,16,0}, //#senHal_pContSenModesRegsArray[19][3] 2 70001370
{0x0F12, 0x0630 ,16,0}, //#senHal_pContSenModesRegsArray[20][0] 2 70001372
{0x0F12, 0x063C ,16,0}, //#senHal_pContSenModesRegsArray[20][1] 2 70001374
{0x0F12, 0x038D ,16,0}, //#senHal_pContSenModesRegsArray[20][2] 2 70001376
{0x0F12, 0x0399 ,16,0}, //#senHal_pContSenModesRegsArray[20][3] 2 70001378
{0x0F12, 0x0668 ,16,0}, //#senHal_pContSenModesRegsArray[21][0] 2 7000137A
{0x0F12, 0x06B3 ,16,0}, //#senHal_pContSenModesRegsArray[21][1] 2 7000137C
{0x0F12, 0x03C5 ,16,0}, //#senHal_pContSenModesRegsArray[21][2] 2 7000137E
{0x0F12, 0x0410 ,16,0}, //#senHal_pContSenModesRegsArray[21][3] 2 70001380
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[22][0] 2 70001382
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[22][1] 2 70001384
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[22][2] 2 70001386
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[22][3] 2 70001388
{0x0F12, 0x03A2 ,16,0}, //#senHal_pContSenModesRegsArray[23][0] 2 7000138A
{0x0F12, 0x01D3 ,16,0}, //#senHal_pContSenModesRegsArray[23][1] 2 7000138C
{0x0F12, 0x01E0 ,16,0}, //#senHal_pContSenModesRegsArray[23][2] 2 7000138E
{0x0F12, 0x00F2 ,16,0}, //#senHal_pContSenModesRegsArray[23][3] 2 70001390
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[24][0] 2 70001392
{0x0F12, 0x0461 ,16,0}, //#senHal_pContSenModesRegsArray[24][1] 2 70001394
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[24][2] 2 70001396
{0x0F12, 0x029F ,16,0}, //#senHal_pContSenModesRegsArray[24][3] 2 70001398
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[25][0] 2 7000139A
{0x0F12, 0x063C ,16,0}, //#senHal_pContSenModesRegsArray[25][1] 2 7000139C
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[25][2] 2 7000139E
{0x0F12, 0x0399 ,16,0}, //#senHal_pContSenModesRegsArray[25][3] 2 700013A0
{0x0F12, 0x003D ,16,0}, //#senHal_pContSenModesRegsArray[26][0] 2 700013A2
{0x0F12, 0x003D ,16,0}, //#senHal_pContSenModesRegsArray[26][1] 2 700013A4
{0x0F12, 0x003D ,16,0}, //#senHal_pContSenModesRegsArray[26][2] 2 700013A6
{0x0F12, 0x003D ,16,0}, //#senHal_pContSenModesRegsArray[26][3] 2 700013A8
{0x0F12, 0x01D0 ,16,0}, //#senHal_pContSenModesRegsArray[27][0] 2 700013AA
{0x0F12, 0x01D0 ,16,0}, //#senHal_pContSenModesRegsArray[27][1] 2 700013AC
{0x0F12, 0x00EF ,16,0}, //#senHal_pContSenModesRegsArray[27][2] 2 700013AE
{0x0F12, 0x00EF ,16,0}, //#senHal_pContSenModesRegsArray[27][3] 2 700013B0
{0x0F12, 0x020C ,16,0}, //#senHal_pContSenModesRegsArray[28][0] 2 700013B2
{0x0F12, 0x024B ,16,0}, //#senHal_pContSenModesRegsArray[28][1] 2 700013B4
{0x0F12, 0x012B ,16,0}, //#senHal_pContSenModesRegsArray[28][2] 2 700013B6
{0x0F12, 0x016A ,16,0}, //#senHal_pContSenModesRegsArray[28][3] 2 700013B8
{0x0F12, 0x039F ,16,0}, //#senHal_pContSenModesRegsArray[29][0] 2 700013BA
{0x0F12, 0x045E ,16,0}, //#senHal_pContSenModesRegsArray[29][1] 2 700013BC
{0x0F12, 0x01DD ,16,0}, //#senHal_pContSenModesRegsArray[29][2] 2 700013BE
{0x0F12, 0x029C ,16,0}, //#senHal_pContSenModesRegsArray[29][3] 2 700013C0
{0x0F12, 0x041A ,16,0}, //#senHal_pContSenModesRegsArray[30][0] 2 700013C2
{0x0F12, 0x04A6 ,16,0}, //#senHal_pContSenModesRegsArray[30][1] 2 700013C4
{0x0F12, 0x0258 ,16,0}, //#senHal_pContSenModesRegsArray[30][2] 2 700013C6
{0x0F12, 0x02E4 ,16,0}, //#senHal_pContSenModesRegsArray[30][3] 2 700013C8
{0x0F12, 0x062D ,16,0}, //#senHal_pContSenModesRegsArray[31][0] 2 700013CA
{0x0F12, 0x0639 ,16,0}, //#senHal_pContSenModesRegsArray[31][1] 2 700013CC
{0x0F12, 0x038A ,16,0}, //#senHal_pContSenModesRegsArray[31][2] 2 700013CE
{0x0F12, 0x0396 ,16,0}, //#senHal_pContSenModesRegsArray[31][3] 2 700013D0
{0x0F12, 0x0669 ,16,0}, //#senHal_pContSenModesRegsArray[32][0] 2 700013D2
{0x0F12, 0x06B4 ,16,0}, //#senHal_pContSenModesRegsArray[32][1] 2 700013D4
{0x0F12, 0x03C6 ,16,0}, //#senHal_pContSenModesRegsArray[32][2] 2 700013D6
{0x0F12, 0x0411 ,16,0}, //#senHal_pContSenModesRegsArray[32][3] 2 700013D8
{0x0F12, 0x087C ,16,0}, //#senHal_pContSenModesRegsArray[33][0] 2 700013DA
{0x0F12, 0x08C7 ,16,0}, //#senHal_pContSenModesRegsArray[33][1] 2 700013DC
{0x0F12, 0x04F8 ,16,0}, //#senHal_pContSenModesRegsArray[33][2] 2 700013DE
{0x0F12, 0x0543 ,16,0}, //#senHal_pContSenModesRegsArray[33][3] 2 700013E0
{0x0F12, 0x0040 ,16,0}, //#senHal_pContSenModesRegsArray[34][0] 2 700013E2
{0x0F12, 0x0040 ,16,0}, //#senHal_pContSenModesRegsArray[34][1] 2 700013E4
{0x0F12, 0x0040 ,16,0}, //#senHal_pContSenModesRegsArray[34][2] 2 700013E6
{0x0F12, 0x0040 ,16,0}, //#senHal_pContSenModesRegsArray[34][3] 2 700013E8
{0x0F12, 0x01D0 ,16,0}, //#senHal_pContSenModesRegsArray[35][0] 2 700013EA
{0x0F12, 0x01D0 ,16,0}, //#senHal_pContSenModesRegsArray[35][1] 2 700013EC
{0x0F12, 0x00EF ,16,0}, //#senHal_pContSenModesRegsArray[35][2] 2 700013EE
{0x0F12, 0x00EF ,16,0}, //#senHal_pContSenModesRegsArray[35][3] 2 700013F0
{0x0F12, 0x020F ,16,0}, //#senHal_pContSenModesRegsArray[36][0] 2 700013F2
{0x0F12, 0x024E ,16,0}, //#senHal_pContSenModesRegsArray[36][1] 2 700013F4
{0x0F12, 0x012E ,16,0}, //#senHal_pContSenModesRegsArray[36][2] 2 700013F6
{0x0F12, 0x016D ,16,0}, //#senHal_pContSenModesRegsArray[36][3] 2 700013F8
{0x0F12, 0x039F ,16,0}, //#senHal_pContSenModesRegsArray[37][0] 2 700013FA
{0x0F12, 0x045E ,16,0}, //#senHal_pContSenModesRegsArray[37][1] 2 700013FC
{0x0F12, 0x01DD ,16,0}, //#senHal_pContSenModesRegsArray[37][2] 2 700013FE
{0x0F12, 0x029C ,16,0}, //#senHal_pContSenModesRegsArray[37][3] 2 70001400
{0x0F12, 0x041D ,16,0}, //#senHal_pContSenModesRegsArray[38][0] 2 70001402
{0x0F12, 0x04A9 ,16,0}, //#senHal_pContSenModesRegsArray[38][1] 2 70001404
{0x0F12, 0x025B ,16,0}, //#senHal_pContSenModesRegsArray[38][2] 2 70001406
{0x0F12, 0x02E7 ,16,0}, //#senHal_pContSenModesRegsArray[38][3] 2 70001408
{0x0F12, 0x062D ,16,0}, //#senHal_pContSenModesRegsArray[39][0] 2 7000140A
{0x0F12, 0x0639 ,16,0}, //#senHal_pContSenModesRegsArray[39][1] 2 7000140C
{0x0F12, 0x038A ,16,0}, //#senHal_pContSenModesRegsArray[39][2] 2 7000140E
{0x0F12, 0x0396 ,16,0}, //#senHal_pContSenModesRegsArray[39][3] 2 70001410
{0x0F12, 0x066C ,16,0}, //#senHal_pContSenModesRegsArray[40][0] 2 70001412
{0x0F12, 0x06B7 ,16,0}, //#senHal_pContSenModesRegsArray[40][1] 2 70001414
{0x0F12, 0x03C9 ,16,0}, //#senHal_pContSenModesRegsArray[40][2] 2 70001416
{0x0F12, 0x0414 ,16,0}, //#senHal_pContSenModesRegsArray[40][3] 2 70001418
{0x0F12, 0x087C ,16,0}, //#senHal_pContSenModesRegsArray[41][0] 2 7000141A
{0x0F12, 0x08C7 ,16,0}, //#senHal_pContSenModesRegsArray[41][1] 2 7000141C
{0x0F12, 0x04F8 ,16,0}, //#senHal_pContSenModesRegsArray[41][2] 2 7000141E
{0x0F12, 0x0543 ,16,0}, //#senHal_pContSenModesRegsArray[41][3] 2 70001420
{0x0F12, 0x0040 ,16,0}, //#senHal_pContSenModesRegsArray[42][0] 2 70001422
{0x0F12, 0x0040 ,16,0}, //#senHal_pContSenModesRegsArray[42][1] 2 70001424
{0x0F12, 0x0040 ,16,0}, //#senHal_pContSenModesRegsArray[42][2] 2 70001426
{0x0F12, 0x0040 ,16,0}, //#senHal_pContSenModesRegsArray[42][3] 2 70001428
{0x0F12, 0x01D0 ,16,0}, //#senHal_pContSenModesRegsArray[43][0] 2 7000142A
{0x0F12, 0x01D0 ,16,0}, //#senHal_pContSenModesRegsArray[43][1] 2 7000142C
{0x0F12, 0x00EF ,16,0}, //#senHal_pContSenModesRegsArray[43][2] 2 7000142E
{0x0F12, 0x00EF ,16,0}, //#senHal_pContSenModesRegsArray[43][3] 2 70001430
{0x0F12, 0x020F ,16,0}, //#senHal_pContSenModesRegsArray[44][0] 2 70001432
{0x0F12, 0x024E ,16,0}, //#senHal_pContSenModesRegsArray[44][1] 2 70001434
{0x0F12, 0x012E ,16,0}, //#senHal_pContSenModesRegsArray[44][2] 2 70001436
{0x0F12, 0x016D ,16,0}, //#senHal_pContSenModesRegsArray[44][3] 2 70001438
{0x0F12, 0x039F ,16,0}, //#senHal_pContSenModesRegsArray[45][0] 2 7000143A
{0x0F12, 0x045E ,16,0}, //#senHal_pContSenModesRegsArray[45][1] 2 7000143C
{0x0F12, 0x01DD ,16,0}, //#senHal_pContSenModesRegsArray[45][2] 2 7000143E
{0x0F12, 0x029C ,16,0}, //#senHal_pContSenModesRegsArray[45][3] 2 70001440
{0x0F12, 0x041D ,16,0}, //#senHal_pContSenModesRegsArray[46][0] 2 70001442
{0x0F12, 0x04A9 ,16,0}, //#senHal_pContSenModesRegsArray[46][1] 2 70001444
{0x0F12, 0x025B ,16,0}, //#senHal_pContSenModesRegsArray[46][2] 2 70001446
{0x0F12, 0x02E7 ,16,0}, //#senHal_pContSenModesRegsArray[46][3] 2 70001448
{0x0F12, 0x062D ,16,0}, //#senHal_pContSenModesRegsArray[47][0] 2 7000144A
{0x0F12, 0x0639 ,16,0}, //#senHal_pContSenModesRegsArray[47][1] 2 7000144C
{0x0F12, 0x038A ,16,0}, //#senHal_pContSenModesRegsArray[47][2] 2 7000144E
{0x0F12, 0x0396 ,16,0}, //#senHal_pContSenModesRegsArray[47][3] 2 70001450
{0x0F12, 0x066C ,16,0}, //#senHal_pContSenModesRegsArray[48][0] 2 70001452
{0x0F12, 0x06B7 ,16,0}, //#senHal_pContSenModesRegsArray[48][1] 2 70001454
{0x0F12, 0x03C9 ,16,0}, //#senHal_pContSenModesRegsArray[48][2] 2 70001456
{0x0F12, 0x0414 ,16,0}, //#senHal_pContSenModesRegsArray[48][3] 2 70001458
{0x0F12, 0x087C ,16,0}, //#senHal_pContSenModesRegsArray[49][0] 2 7000145A
{0x0F12, 0x08C7 ,16,0}, //#senHal_pContSenModesRegsArray[49][1] 2 7000145C
{0x0F12, 0x04F8 ,16,0}, //#senHal_pContSenModesRegsArray[49][2] 2 7000145E
{0x0F12, 0x0543 ,16,0}, //#senHal_pContSenModesRegsArray[49][3] 2 70001460
{0x0F12, 0x003D ,16,0}, //#senHal_pContSenModesRegsArray[50][0] 2 70001462
{0x0F12, 0x003D ,16,0}, //#senHal_pContSenModesRegsArray[50][1] 2 70001464
{0x0F12, 0x003D ,16,0}, //#senHal_pContSenModesRegsArray[50][2] 2 70001466
{0x0F12, 0x003D ,16,0}, //#senHal_pContSenModesRegsArray[50][3] 2 70001468
{0x0F12, 0x01D2 ,16,0}, //#senHal_pContSenModesRegsArray[51][0] 2 7000146A
{0x0F12, 0x01D2 ,16,0}, //#senHal_pContSenModesRegsArray[51][1] 2 7000146C
{0x0F12, 0x00F1 ,16,0}, //#senHal_pContSenModesRegsArray[51][2] 2 7000146E
{0x0F12, 0x00F1 ,16,0}, //#senHal_pContSenModesRegsArray[51][3] 2 70001470
{0x0F12, 0x020C ,16,0}, //#senHal_pContSenModesRegsArray[52][0] 2 70001472
{0x0F12, 0x024B ,16,0}, //#senHal_pContSenModesRegsArray[52][1] 2 70001474
{0x0F12, 0x012B ,16,0}, //#senHal_pContSenModesRegsArray[52][2] 2 70001476
{0x0F12, 0x016A ,16,0}, //#senHal_pContSenModesRegsArray[52][3] 2 70001478
{0x0F12, 0x03A1 ,16,0}, //#senHal_pContSenModesRegsArray[53][0] 2 7000147A
{0x0F12, 0x0460 ,16,0}, //#senHal_pContSenModesRegsArray[53][1] 2 7000147C
{0x0F12, 0x01DF ,16,0}, //#senHal_pContSenModesRegsArray[53][2] 2 7000147E
{0x0F12, 0x029E ,16,0}, //#senHal_pContSenModesRegsArray[53][3] 2 70001480
{0x0F12, 0x041A ,16,0}, //#senHal_pContSenModesRegsArray[54][0] 2 70001482
{0x0F12, 0x04A6 ,16,0}, //#senHal_pContSenModesRegsArray[54][1] 2 70001484
{0x0F12, 0x0258 ,16,0}, //#senHal_pContSenModesRegsArray[54][2] 2 70001486
{0x0F12, 0x02E4 ,16,0}, //#senHal_pContSenModesRegsArray[54][3] 2 70001488
{0x0F12, 0x062F ,16,0}, //#senHal_pContSenModesRegsArray[55][0] 2 7000148A
{0x0F12, 0x063B ,16,0}, //#senHal_pContSenModesRegsArray[55][1] 2 7000148C
{0x0F12, 0x038C ,16,0}, //#senHal_pContSenModesRegsArray[55][2] 2 7000148E
{0x0F12, 0x0398 ,16,0}, //#senHal_pContSenModesRegsArray[55][3] 2 70001490
{0x0F12, 0x0669 ,16,0}, //#senHal_pContSenModesRegsArray[56][0] 2 70001492
{0x0F12, 0x06B4 ,16,0}, //#senHal_pContSenModesRegsArray[56][1] 2 70001494
{0x0F12, 0x03C6 ,16,0}, //#senHal_pContSenModesRegsArray[56][2] 2 70001496
{0x0F12, 0x0411 ,16,0}, //#senHal_pContSenModesRegsArray[56][3] 2 70001498
{0x0F12, 0x087E ,16,0}, //#senHal_pContSenModesRegsArray[57][0] 2 7000149A
{0x0F12, 0x08C9 ,16,0}, //#senHal_pContSenModesRegsArray[57][1] 2 7000149C
{0x0F12, 0x04FA ,16,0}, //#senHal_pContSenModesRegsArray[57][2] 2 7000149E
{0x0F12, 0x0545 ,16,0}, //#senHal_pContSenModesRegsArray[57][3] 2 700014A0
{0x0F12, 0x03A2 ,16,0}, //#senHal_pContSenModesRegsArray[58][0] 2 700014A2
{0x0F12, 0x01D3 ,16,0}, //#senHal_pContSenModesRegsArray[58][1] 2 700014A4
{0x0F12, 0x01E0 ,16,0}, //#senHal_pContSenModesRegsArray[58][2] 2 700014A6
{0x0F12, 0x00F2 ,16,0}, //#senHal_pContSenModesRegsArray[58][3] 2 700014A8
{0x0F12, 0x03AF ,16,0}, //#senHal_pContSenModesRegsArray[59][0] 2 700014AA
{0x0F12, 0x01E0 ,16,0}, //#senHal_pContSenModesRegsArray[59][1] 2 700014AC
{0x0F12, 0x01ED ,16,0}, //#senHal_pContSenModesRegsArray[59][2] 2 700014AE
{0x0F12, 0x00FF ,16,0}, //#senHal_pContSenModesRegsArray[59][3] 2 700014B0
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[60][0] 2 700014B2
{0x0F12, 0x0461 ,16,0}, //#senHal_pContSenModesRegsArray[60][1] 2 700014B4
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[60][2] 2 700014B6
{0x0F12, 0x029F ,16,0}, //#senHal_pContSenModesRegsArray[60][3] 2 700014B8
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[61][0] 2 700014BA
{0x0F12, 0x046E ,16,0}, //#senHal_pContSenModesRegsArray[61][1] 2 700014BC
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[61][2] 2 700014BE
{0x0F12, 0x02AC ,16,0}, //#senHal_pContSenModesRegsArray[61][3] 2 700014C0
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[62][0] 2 700014C2
{0x0F12, 0x063C ,16,0}, //#senHal_pContSenModesRegsArray[62][1] 2 700014C4
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[62][2] 2 700014C6
{0x0F12, 0x0399 ,16,0}, //#senHal_pContSenModesRegsArray[62][3] 2 700014C8
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[63][0] 2 700014CA
{0x0F12, 0x0649 ,16,0}, //#senHal_pContSenModesRegsArray[63][1] 2 700014CC
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[63][2] 2 700014CE
{0x0F12, 0x03A6 ,16,0}, //#senHal_pContSenModesRegsArray[63][3] 2 700014D0
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[64][0] 2 700014D2
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[64][1] 2 700014D4
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[64][2] 2 700014D6
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[64][3] 2 700014D8
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[65][0] 2 700014DA
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[65][1] 2 700014DC
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[65][2] 2 700014DE
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[65][3] 2 700014E0
{0x0F12, 0x03AA ,16,0}, //#senHal_pContSenModesRegsArray[66][0] 2 700014E2
{0x0F12, 0x01DB ,16,0}, //#senHal_pContSenModesRegsArray[66][1] 2 700014E4
{0x0F12, 0x01E8 ,16,0}, //#senHal_pContSenModesRegsArray[66][2] 2 700014E6
{0x0F12, 0x00FA ,16,0}, //#senHal_pContSenModesRegsArray[66][3] 2 700014E8
{0x0F12, 0x03B7 ,16,0}, //#senHal_pContSenModesRegsArray[67][0] 2 700014EA
{0x0F12, 0x01E8 ,16,0}, //#senHal_pContSenModesRegsArray[67][1] 2 700014EC
{0x0F12, 0x01F5 ,16,0}, //#senHal_pContSenModesRegsArray[67][2] 2 700014EE
{0x0F12, 0x0107 ,16,0}, //#senHal_pContSenModesRegsArray[67][3] 2 700014F0
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[68][0] 2 700014F2
{0x0F12, 0x0469 ,16,0}, //#senHal_pContSenModesRegsArray[68][1] 2 700014F4
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[68][2] 2 700014F6
{0x0F12, 0x02A7 ,16,0}, //#senHal_pContSenModesRegsArray[68][3] 2 700014F8
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[69][0] 2 700014FA
{0x0F12, 0x0476 ,16,0}, //#senHal_pContSenModesRegsArray[69][1] 2 700014FC
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[69][2] 2 700014FE
{0x0F12, 0x02B4 ,16,0}, //#senHal_pContSenModesRegsArray[69][3] 2 70001500
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[70][0] 2 70001502
{0x0F12, 0x0644 ,16,0}, //#senHal_pContSenModesRegsArray[70][1] 2 70001504
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[70][2] 2 70001506
{0x0F12, 0x03A1 ,16,0}, //#senHal_pContSenModesRegsArray[70][3] 2 70001508
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[71][0] 2 7000150A
{0x0F12, 0x0651 ,16,0}, //#senHal_pContSenModesRegsArray[71][1] 2 7000150C
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[71][2] 2 7000150E
{0x0F12, 0x03AE ,16,0}, //#senHal_pContSenModesRegsArray[71][3] 2 70001510
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[72][0] 2 70001512
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[72][1] 2 70001514
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[72][2] 2 70001516
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[72][3] 2 70001518
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[73][0] 2 7000151A
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[73][1] 2 7000151C
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[73][2] 2 7000151E
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[73][3] 2 70001520
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[74][0] 2 70001522
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[74][1] 2 70001524
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[74][2] 2 70001526
{0x0F12, 0x0001 ,16,0}, //#senHal_pContSenModesRegsArray[74][3] 2 70001528
{0x0F12, 0x000F ,16,0}, //#senHal_pContSenModesRegsArray[75][0] 2 7000152A
{0x0F12, 0x000F ,16,0}, //#senHal_pContSenModesRegsArray[75][1] 2 7000152C
{0x0F12, 0x000F ,16,0}, //#senHal_pContSenModesRegsArray[75][2] 2 7000152E
{0x0F12, 0x000F ,16,0}, //#senHal_pContSenModesRegsArray[75][3] 2 70001530
{0x0F12, 0x05AD ,16,0}, //#senHal_pContSenModesRegsArray[76][0] 2 70001532
{0x0F12, 0x03DE ,16,0}, //#senHal_pContSenModesRegsArray[76][1] 2 70001534
{0x0F12, 0x030A ,16,0}, //#senHal_pContSenModesRegsArray[76][2] 2 70001536
{0x0F12, 0x021C ,16,0}, //#senHal_pContSenModesRegsArray[76][3] 2 70001538
{0x0F12, 0x062F ,16,0}, //#senHal_pContSenModesRegsArray[77][0] 2 7000153A
{0x0F12, 0x0460 ,16,0}, //#senHal_pContSenModesRegsArray[77][1] 2 7000153C
{0x0F12, 0x038C ,16,0}, //#senHal_pContSenModesRegsArray[77][2] 2 7000153E
{0x0F12, 0x029E ,16,0}, //#senHal_pContSenModesRegsArray[77][3] 2 70001540
{0x0F12, 0x07FC ,16,0}, //#senHal_pContSenModesRegsArray[78][0] 2 70001542
{0x0F12, 0x0847 ,16,0}, //#senHal_pContSenModesRegsArray[78][1] 2 70001544
{0x0F12, 0x0478 ,16,0}, //#senHal_pContSenModesRegsArray[78][2] 2 70001546
{0x0F12, 0x04C3 ,16,0}, //#senHal_pContSenModesRegsArray[78][3] 2 70001548
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[79][0] 2 7000154A
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[79][1] 2 7000154C
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[79][2] 2 7000154E
{0x0F12, 0x0000 ,16,0}, //#senHal_pContSenModesRegsArray[79][3] 2 70001550
              
//============================================================
// Analog Setting END
//============================================================
              
////============================================================
//// AF Interface setting
////============================================================
//WRITE 700001D4 0000 //REG_TC_IPRM_AuxGpios : 0 - no Flash
//WRITE 700001DE 0003 //REG_TC_IPRM_CM_Init_AfModeType : 3 - AFD_VCM_I2C
//WRITE 700001E0 0000 //REG_TC_IPRM_CM_Init_PwmConfig1 : 0 - no PWM
//WRITE 700001E4 0000 //REG_TC_IPRM_CM_Init_GpioConfig1 : 0 - no GPIO
//WRITE 700001E8 200C //REG_TC_IPRM_CM_Init_Mi2cBits : MSCL - GPIO1 MSDA - GPIO2 Device ID (0C)
//WRITE 700001EA 0190 //REG_TC_IPRM_CM_Init_Mi2cRateKhz : MI2C Speed - 400KHz
//            
////============================================================
//// AF Parameter setting
////============================================================
//// AF Window Settings
//WRITE 7000025A 0100 //#REG_TC_AF_FstWinStartX
//WRITE 7000025C 00E3 //#REG_TC_AF_FstWinStartY
//WRITE 7000025E 0200 //#REG_TC_AF_FstWinSizeX
//WRITE 70000260 0238 //#REG_TC_AF_FstWinSizeY
//WRITE 70000262 018C //#REG_TC_AF_ScndWinStartX
//WRITE 70000264 0166 //#REG_TC_AF_ScndWinStartY
//WRITE 70000266 00E6 //#REG_TC_AF_ScndWinSizeX
//WRITE 70000268 0132 //#REG_TC_AF_ScndWinSizeY
//WRITE 7000026A 0001 //#REG_TC_AF_WinSizesUpdated
//
//// AF Setot Settings
//WRITE 70000586 00FF //#skl_af_StatOvlpExpFactor
//
//// AF Scene Settings
//WRITE 7000115E 0003 //#af_scene_usSaturatedScene
//
//// AF Fine Search Settings
//WRITE 700010D4 1000 //FineSearch Disable //#af_search_usSingleAfFlags
//WRITE 700010DE 0004 //#af_search_usFinePeakCount
//WRITE 7000106C 0202 //#af_pos_usFineStepNumSize
//
//// AF Peak Threshold Setting
//WRITE 700010CA 00C0
//
//// AF Default Position
//WRITE 70001060 003C //#af_pos_usHomePos
//WRITE 70001062 783C //#af_pos_usLowConfPos
//
//// AF LowConfThr Setting
//WRITE 700010F4 0280
//WRITE 70001100 03A0
//WRITE 70001102 0320
//
//WRITE 70001134 0030 //af_stat_usMinStatVal
//
//// AF low Br Th
//WRITE 70001154 0060
//
//// AF Policy
//WRITE 700010E2 0000 //#af_search_usCapturePolicy: Focus_Priority, 0002 : Shutter_Priority_Fixed, 0001 : Shutter_Priority_Last_BFP 0000: Shutter_Priority_Current
//WRITE 70001072 003C //#af_pos_usCaptureFixedPos// 0x0008
//
//// AF Lens Position Table Settings
//WRITE 70001074 0010 //#af_pos_usTableLastInd// 16 Steps 091222
//WRITE 70001076 003C //#af_pos_usTable_0_// af_pos_usTable
//WRITE 70001078 003F //#af_pos_usTable_1_
//WRITE 7000107A 0042 //#af_pos_usTable_2_
//WRITE 7000107C 0045 //#af_pos_usTable_3_
//WRITE 7000107E 0048 //#af_pos_usTable_4_
//WRITE 70001080 004B //#af_pos_usTable_5_
//WRITE 70001082 004E //#af_pos_usTable_6_
//WRITE 70001084 0051 //#af_pos_usTable_7_
//WRITE 70001086 0054 //#af_pos_usTable_8_
//WRITE 70001088 0057 //#af_pos_usTable_9_
//WRITE 7000108A 005A //#af_pos_usTable_10_
//WRITE 7000108C 005E //#af_pos_usTable_11_
//WRITE 7000108E 0061 //#af_pos_usTable_12_
//WRITE 70001090 0064 //#af_pos_usTable_13_
//WRITE 70001092 0068 //#af_pos_usTable_14_
//WRITE 70001094 006C //#af_pos_usTable_15_
//WRITE 70001096 0078 //#af_pos_usTable_16_
//
//WRITE 70000252 0003 //init

//============================================================
// ISP-FE Setting
//============================================================
{0x002A, 0x158A ,16,0},
{0x0F12, 0xEAF0 ,16,0},
{0x002A, 0x15C6 ,16,0},
{0x0F12, 0x0020 ,16,0},
{0x0F12, 0x0060 ,16,0},
{0x002A, 0x15BC ,16,0},
{0x0F12, 0x0200 ,16,0},
              
//Analog Offset for MSM
{0x002A, 0x1608 ,16,0},
{0x0F12, 0x0100 ,16,0}, //#gisp_msm_sAnalogOffset[0]
{0x0F12, 0x0100 ,16,0}, //#gisp_msm_sAnalogOffset[1]
{0x0F12, 0x0100 ,16,0}, //#gisp_msm_sAnalogOffset[2]
{0x0F12, 0x0100 ,16,0}, //#gisp_msm_sAnalogOffset[3]
              
//================================================================================================
// SET AE   
//================================================================================================
// AE target
{0x002A, 0x0F70 ,16,0},
{0x0F12, 0x0030 ,16,0}, //003A // #TVAR_ae_BrAve
// AE mode  
{0x002A, 0x0F76 ,16,0},
{0x0F12, 0x000F ,16,0}, //Disable illumination & contrast  // #ae_StatMode
// AE weight
{0x002A, 0x0F7E ,16,0},
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_0_
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_1_
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_2_
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_3_
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_4_
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_5_
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_6_
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_7_
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_8_
{0x0F12, 0x0303 ,16,0}, // #ae_WeightTbl_16_9_
{0x0F12, 0x0303 ,16,0}, // #ae_WeightTbl_16_10
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_11
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_12
{0x0F12, 0x0303 ,16,0}, // #ae_WeightTbl_16_13
{0x0F12, 0x0303 ,16,0}, // #ae_WeightTbl_16_14
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_15
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_16
{0x0F12, 0x0303 ,16,0}, // #ae_WeightTbl_16_17
{0x0F12, 0x0303 ,16,0}, // #ae_WeightTbl_16_18
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_19
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_20
{0x0F12, 0x0303 ,16,0}, // #ae_WeightTbl_16_21
{0x0F12, 0x0303 ,16,0}, // #ae_WeightTbl_16_22
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_23
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_24
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_25
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_26
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_27
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_28
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_29
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_30
{0x0F12, 0x0101 ,16,0}, // #ae_WeightTbl_16_31
              
//================================================================================================
// SET FLICKER
//================================================================================================
{0x002A, 0x0C18 ,16,0},                                     
{0x0F12, 0x0000 ,16,0}, // 0001: 60Hz start auto / 0000: 50Hz start auto
{0x002A, 0x04D2 ,16,0},
{0x0F12, 0x067F ,16,0}, // #REG_TC_DBG_AutoAlgEnBits
{0x002A, 0x04BA ,16,0},
{0x0F12, 0x0002 ,16,0}, // #REG_SF_USER_FlickerQuant
{0x002A, 0x0C04 ,16,0},
{0x0F12, 0xFFFF ,16,0}, // #AFC_StandingWavesLimit
              
//================================================================================================
// SET GAS    
//================================================================================================
// GAS alpha  
// R, Gr, Gb, B per light source
{0x002A, 0x06CE ,16,0},
{0x0F12, 0x00FD ,16,0}, //0150//0100 // #TVAR_ash_GASAlpha[0] // Horizon
{0x0F12, 0x00FD ,16,0}, //0113//0100 // #TVAR_ash_GASAlpha[1]
{0x0F12, 0x00FD ,16,0}, //011D//0100 // #TVAR_ash_GASAlpha[2]
{0x0F12, 0x00FC ,16,0}, //0100//0100 // #TVAR_ash_GASAlpha[3]
{0x0F12, 0x00FD ,16,0}, //0146//0100 // #TVAR_ash_GASAlpha[4] // IncandA
{0x0F12, 0x00FD ,16,0}, //0113//0100 // #TVAR_ash_GASAlpha[5]
{0x0F12, 0x00FD ,16,0}, //011D//0100 // #TVAR_ash_GASAlpha[6]
{0x0F12, 0x00FC ,16,0}, //0109//0100 // #TVAR_ash_GASAlpha[7]
{0x0F12, 0x00FD ,16,0}, //0120//0100 // #TVAR_ash_GASAlpha[8] // WW
{0x0F12, 0x00FD ,16,0}, //00E6//0100 // #TVAR_ash_GASAlpha[9]
{0x0F12, 0x00FD ,16,0}, //00F0//0100 // #TVAR_ash_GASAlpha[10]
{0x0F12, 0x00FC ,16,0}, //00DD//0100 // #TVAR_ash_GASAlpha[11]
{0x0F12, 0x00FD ,16,0}, //00D7//0100 // #TVAR_ash_GASAlpha[12]// CWF
{0x0F12, 0x00FD ,16,0}, //00F9//0100 // #TVAR_ash_GASAlpha[13]
{0x0F12, 0x00FD ,16,0}, //00F7//0100 // #TVAR_ash_GASAlpha[14]
{0x0F12, 0x00FC ,16,0}, //00EF//0100 // #TVAR_ash_GASAlpha[15]
{0x0F12, 0x00FD ,16,0}, //00F0//0100 // #TVAR_ash_GASAlpha[16]// D50
{0x0F12, 0x00FD ,16,0}, //0103//0100 // #TVAR_ash_GASAlpha[17]
{0x0F12, 0x00FD ,16,0}, //00FC//0100 // #TVAR_ash_GASAlpha[18]
{0x0F12, 0x00FC ,16,0}, //010C//0100 // #TVAR_ash_GASAlpha[19]
{0x0F12, 0x00FD ,16,0}, //0100//0100 // #TVAR_ash_GASAlpha[20]// D65
{0x0F12, 0x00FD ,16,0}, //00FF//0100 // #TVAR_ash_GASAlpha[21]
{0x0F12, 0x00FD ,16,0}, //00F3//0100 // #TVAR_ash_GASAlpha[22]
{0x0F12, 0x00FC ,16,0}, //010F//0100 // #TVAR_ash_GASAlpha[23]
{0x0F12, 0x00FD ,16,0}, //0100//0100 // #TVAR_ash_GASAlpha[24]// D75
{0x0F12, 0x00FD ,16,0}, //0109//0100 // #TVAR_ash_GASAlpha[25]
{0x0F12, 0x00FD ,16,0}, //00FA//0100 // #TVAR_ash_GASAlpha[26]
{0x0F12, 0x00FC ,16,0}, //011E//0100 // #TVAR_ash_GASAlpha[27]
{0x0F12, 0x00FD ,16,0}, //00C8//0100 // #TVAR_ash_GASOutdoorAlpha[0] // Outdoor
{0x0F12, 0x00FD ,16,0}, //00F0//0100 // #TVAR_ash_GASOutdoorAlpha[1]
{0x0F12, 0x00FD ,16,0}, //00F8//0100 // #TVAR_ash_GASOutdoorAlpha[2]
{0x0F12, 0x00FC ,16,0}, //00F8//0100 // #TVAR_ash_GASOutdoorAlpha[3]
// GAS beta   
{0x0F12, 0x0032 ,16,0}, //005A//0000 // #ash_GASBeta[0]// Horizon
{0x0F12, 0x0019 ,16,0}, //002D//0000 // #ash_GASBeta[1]
{0x0F12, 0x0017 ,16,0}, //002D//0000 // #ash_GASBeta[2]
{0x0F12, 0x0000 ,16,0}, //0000//0000 // #ash_GASBeta[3]
{0x0F12, 0x0032 ,16,0}, //005B//0000 // #ash_GASBeta[4]// IncandA
{0x0F12, 0x0019 ,16,0}, //0029//0000 // #ash_GASBeta[5]
{0x0F12, 0x0017 ,16,0}, //002A//0000 // #ash_GASBeta[6]
{0x0F12, 0x0000 ,16,0}, //0000//0000 // #ash_GASBeta[7]
{0x0F12, 0x0032 ,16,0}, //0040//0000 // #ash_GASBeta[8]// WW
{0x0F12, 0x0019 ,16,0}, //002E//0000 // #ash_GASBeta[9]
{0x0F12, 0x0017 ,16,0}, //0031//0000 // #ash_GASBeta[10]
{0x0F12, 0x0000 ,16,0}, //0000//0000 // #ash_GASBeta[11]
{0x0F12, 0x0032 ,16,0}, //0025//0000 // #ash_GASBeta[12] // CWF
{0x0F12, 0x0019 ,16,0}, //0029//0000 // #ash_GASBeta[13]
{0x0F12, 0x0017 ,16,0}, //0027//0000 // #ash_GASBeta[14]
{0x0F12, 0x0000 ,16,0}, //0000//0000 // #ash_GASBeta[15]
{0x0F12, 0x0032 ,16,0}, //0037//0000 // #ash_GASBeta[16] // D50
{0x0F12, 0x0019 ,16,0}, //001F//0000 // #ash_GASBeta[17]
{0x0F12, 0x0017 ,16,0}, //001C//0000 // #ash_GASBeta[18]
{0x0F12, 0x0000 ,16,0}, //0000//0000 // #ash_GASBeta[19]
{0x0F12, 0x0032 ,16,0}, //0031//0000 // #ash_GASBeta[20] // D65
{0x0F12, 0x0019 ,16,0}, //001A//0000 // #ash_GASBeta[21]
{0x0F12, 0x0017 ,16,0}, //0017//0000 // #ash_GASBeta[22]
{0x0F12, 0x0000 ,16,0}, //0000//0000 // #ash_GASBeta[23]
{0x0F12, 0x0032 ,16,0}, //0031//0000 // #ash_GASBeta[24] // D75
{0x0F12, 0x0019 ,16,0}, //0019//0000 // #ash_GASBeta[25]
{0x0F12, 0x0017 ,16,0}, //0014//0000 // #ash_GASBeta[26]
{0x0F12, 0x0000 ,16,0}, //0000//0000 // #ash_GASBeta[27]
{0x0F12, 0x0032 ,16,0}, //0035//0000 // #ash_GASOutdoorBeta[0] // Outdoor
{0x0F12, 0x0019 ,16,0}, //001D//0000 // #ash_GASOutdoorBeta[1]
{0x0F12, 0x0017 ,16,0}, //001A//0000 // #ash_GASOutdoorBeta[2]
{0x0F12, 0x0000 ,16,0}, //0000//0000 // #ash_GASOutdoorBeta[3]
              
// Parabloic function
{0x002A, 0x075A ,16,0},
{0x0F12, 0x0000 ,16,0}, //0000 // #ash_bParabolicEstimation
{0x0F12, 0x0400 ,16,0}, //0400 // #ash_uParabolicCenterX
{0x0F12, 0x0300 ,16,0}, //0300 // #ash_uParabolicCenterY
{0x0F12, 0x0010 ,16,0}, //0010 // #ash_uParabolicScalingA
{0x0F12, 0x0011 ,16,0}, //0011 // #ash_uParabolicScalingB
              
//ash_CGrasAlp ,16,0},has
{0x002A, 0x06C6 ,16,0},
{0x0F12, 0x0100 ,16,0}, //0100 //ash_CGrasAlphas_0_
{0x0F12, 0x0100 ,16,0}, //0100 //ash_CGrasAlphas_1_
{0x0F12, 0x0100 ,16,0}, //0100 //ash_CGrasAlphas_2_
{0x0F12, 0x0100 ,16,0}, //0100 //ash_CGrasAlphas_3_
{0x002A, 0x0E3C ,16,0},                          
{0x0F12, 0x00C0 ,16,0}, // #awbb_Alpha_Comp_Mode               
{0x002A, 0x074E ,16,0},
{0x0F12, 0x0000 ,16,0}, // #ash_bLumaMode //use Beta : 0001 not use Beta : 0000
{0x002A, 0x0D30 ,16,0},
{0x0F12, 0x02A7 ,16,0}, //02A7 // #awbb_GLocusR
{0x0F12, 0x0343 ,16,0}, //0343 // #awbb_GLocusB
              
// GAS LUT start address // 7000_347C
{0x002A, 0x0754 ,16,0},
{0x0F12, 0x347C ,16,0},
{0x0F12, 0x7000 ,16,0},
// GAS LUT    
{0x002A, 0x347C ,16,0},
{0x0F12, 0x0220 ,16,0}, //#TVAR_ash_pGAS[0]
{0x0F12, 0x01D0 ,16,0}, //#TVAR_ash_pGAS[1]
{0x0F12, 0x019C ,16,0}, //#TVAR_ash_pGAS[2]
{0x0F12, 0x0163 ,16,0}, //#TVAR_ash_pGAS[3]
{0x0F12, 0x0138 ,16,0}, //#TVAR_ash_pGAS[4]
{0x0F12, 0x011C ,16,0}, //#TVAR_ash_pGAS[5]
{0x0F12, 0x010D ,16,0}, //#TVAR_ash_pGAS[6]
{0x0F12, 0x0112 ,16,0}, //#TVAR_ash_pGAS[7]
{0x0F12, 0x0123 ,16,0}, //#TVAR_ash_pGAS[8]
{0x0F12, 0x0149 ,16,0}, //#TVAR_ash_pGAS[9]
{0x0F12, 0x0180 ,16,0}, //#TVAR_ash_pGAS[10]
{0x0F12, 0x01B0 ,16,0}, //#TVAR_ash_pGAS[11]
{0x0F12, 0x01E4 ,16,0}, //#TVAR_ash_pGAS[12]
{0x0F12, 0x01C3 ,16,0}, //#TVAR_ash_pGAS[13]
{0x0F12, 0x019A ,16,0}, //#TVAR_ash_pGAS[14]
{0x0F12, 0x0156 ,16,0}, //#TVAR_ash_pGAS[15]
{0x0F12, 0x0115 ,16,0}, //#TVAR_ash_pGAS[16]
{0x0F12, 0x00E9 ,16,0}, //#TVAR_ash_pGAS[17]
{0x0F12, 0x00CB ,16,0}, //#TVAR_ash_pGAS[18]
{0x0F12, 0x00BE ,16,0}, //#TVAR_ash_pGAS[19]
{0x0F12, 0x00C4 ,16,0}, //#TVAR_ash_pGAS[20]
{0x0F12, 0x00DB ,16,0}, //#TVAR_ash_pGAS[21]
{0x0F12, 0x0101 ,16,0}, //#TVAR_ash_pGAS[22]
{0x0F12, 0x013D ,16,0}, //#TVAR_ash_pGAS[23]
{0x0F12, 0x0184 ,16,0}, //#TVAR_ash_pGAS[24]
{0x0F12, 0x01AF ,16,0}, //#TVAR_ash_pGAS[25]
{0x0F12, 0x0197 ,16,0}, //#TVAR_ash_pGAS[26]
{0x0F12, 0x015C ,16,0}, //#TVAR_ash_pGAS[27]
{0x0F12, 0x010A ,16,0}, //#TVAR_ash_pGAS[28]
{0x0F12, 0x00CC ,16,0}, //#TVAR_ash_pGAS[29]
{0x0F12, 0x009C ,16,0}, //#TVAR_ash_pGAS[30]
{0x0F12, 0x007D ,16,0}, //#TVAR_ash_pGAS[31]
{0x0F12, 0x006F ,16,0}, //#TVAR_ash_pGAS[32]
{0x0F12, 0x0078 ,16,0}, //#TVAR_ash_pGAS[33]
{0x0F12, 0x0092 ,16,0}, //#TVAR_ash_pGAS[34]
{0x0F12, 0x00BC ,16,0}, //#TVAR_ash_pGAS[35]
{0x0F12, 0x00F8 ,16,0}, //#TVAR_ash_pGAS[36]
{0x0F12, 0x0149 ,16,0}, //#TVAR_ash_pGAS[37]
{0x0F12, 0x0189 ,16,0}, //#TVAR_ash_pGAS[38]
{0x0F12, 0x016D ,16,0}, //#TVAR_ash_pGAS[39]
{0x0F12, 0x0122 ,16,0}, //#TVAR_ash_pGAS[40]
{0x0F12, 0x00D2 ,16,0}, //#TVAR_ash_pGAS[41]
{0x0F12, 0x0091 ,16,0}, //#TVAR_ash_pGAS[42]
{0x0F12, 0x005F ,16,0}, //#TVAR_ash_pGAS[43]
{0x0F12, 0x0042 ,16,0}, //#TVAR_ash_pGAS[44]
{0x0F12, 0x0035 ,16,0}, //#TVAR_ash_pGAS[45]
{0x0F12, 0x003E ,16,0}, //#TVAR_ash_pGAS[46]
{0x0F12, 0x0058 ,16,0}, //#TVAR_ash_pGAS[47]
{0x0F12, 0x0085 ,16,0}, //#TVAR_ash_pGAS[48]
{0x0F12, 0x00C4 ,16,0}, //#TVAR_ash_pGAS[49]
{0x0F12, 0x0119 ,16,0}, //#TVAR_ash_pGAS[50]
{0x0F12, 0x0165 ,16,0}, //#TVAR_ash_pGAS[51]
{0x0F12, 0x0149 ,16,0}, //#TVAR_ash_pGAS[52]
{0x0F12, 0x00FA ,16,0}, //#TVAR_ash_pGAS[53]
{0x0F12, 0x00A9 ,16,0}, //#TVAR_ash_pGAS[54]
{0x0F12, 0x0066 ,16,0}, //#TVAR_ash_pGAS[55]
{0x0F12, 0x0037 ,16,0}, //#TVAR_ash_pGAS[56]
{0x0F12, 0x0019 ,16,0}, //#TVAR_ash_pGAS[57]
{0x0F12, 0x0010 ,16,0}, //#TVAR_ash_pGAS[58]
{0x0F12, 0x0018 ,16,0}, //#TVAR_ash_pGAS[59]
{0x0F12, 0x0032 ,16,0}, //#TVAR_ash_pGAS[60]
{0x0F12, 0x0062 ,16,0}, //#TVAR_ash_pGAS[61]
{0x0F12, 0x00A2 ,16,0}, //#TVAR_ash_pGAS[62]
{0x0F12, 0x00F5 ,16,0}, //#TVAR_ash_pGAS[63]
{0x0F12, 0x0145 ,16,0}, //#TVAR_ash_pGAS[64]
{0x0F12, 0x0138 ,16,0}, //#TVAR_ash_pGAS[65]
{0x0F12, 0x00EA ,16,0}, //#TVAR_ash_pGAS[66]
{0x0F12, 0x0099 ,16,0}, //#TVAR_ash_pGAS[67]
{0x0F12, 0x0056 ,16,0}, //#TVAR_ash_pGAS[68]
{0x0F12, 0x0025 ,16,0}, //#TVAR_ash_pGAS[69]
{0x0F12, 0x000A ,16,0}, //#TVAR_ash_pGAS[70]
{0x0F12, 0x0000 ,16,0}, //#TVAR_ash_pGAS[71]
{0x0F12, 0x0008 ,16,0}, //#TVAR_ash_pGAS[72]
{0x0F12, 0x0023 ,16,0}, //#TVAR_ash_pGAS[73]
{0x0F12, 0x0052 ,16,0}, //#TVAR_ash_pGAS[74]
{0x0F12, 0x0094 ,16,0}, //#TVAR_ash_pGAS[75]
{0x0F12, 0x00E7 ,16,0}, //#TVAR_ash_pGAS[76]
{0x0F12, 0x013D ,16,0}, //#TVAR_ash_pGAS[77]
{0x0F12, 0x0138 ,16,0}, //#TVAR_ash_pGAS[78]
{0x0F12, 0x00EB ,16,0}, //#TVAR_ash_pGAS[79]
{0x0F12, 0x0097 ,16,0}, //#TVAR_ash_pGAS[80]
{0x0F12, 0x0057 ,16,0}, //#TVAR_ash_pGAS[81]
{0x0F12, 0x0029 ,16,0}, //#TVAR_ash_pGAS[82]
{0x0F12, 0x000A ,16,0}, //#TVAR_ash_pGAS[83]
{0x0F12, 0x0002 ,16,0}, //#TVAR_ash_pGAS[84]
{0x0F12, 0x000B ,16,0}, //#TVAR_ash_pGAS[85]
{0x0F12, 0x0025 ,16,0}, //#TVAR_ash_pGAS[86]
{0x0F12, 0x0055 ,16,0}, //#TVAR_ash_pGAS[87]
{0x0F12, 0x0096 ,16,0}, //#TVAR_ash_pGAS[88]
{0x0F12, 0x00EB ,16,0}, //#TVAR_ash_pGAS[89]
{0x0F12, 0x013D ,16,0}, //#TVAR_ash_pGAS[90]
{0x0F12, 0x0148 ,16,0}, //#TVAR_ash_pGAS[91]
{0x0F12, 0x00FF ,16,0}, //#TVAR_ash_pGAS[92]
{0x0F12, 0x00AB ,16,0}, //#TVAR_ash_pGAS[93]
{0x0F12, 0x006C ,16,0}, //#TVAR_ash_pGAS[94]
{0x0F12, 0x003D ,16,0}, //#TVAR_ash_pGAS[95]
{0x0F12, 0x0021 ,16,0}, //#TVAR_ash_pGAS[96]
{0x0F12, 0x0017 ,16,0}, //#TVAR_ash_pGAS[97]
{0x0F12, 0x0021 ,16,0}, //#TVAR_ash_pGAS[98]
{0x0F12, 0x003C ,16,0}, //#TVAR_ash_pGAS[99]
{0x0F12, 0x006D ,16,0}, //#TVAR_ash_pGAS[100]
{0x0F12, 0x00AD ,16,0}, //#TVAR_ash_pGAS[101]
{0x0F12, 0x0100 ,16,0}, //#TVAR_ash_pGAS[102]
{0x0F12, 0x0153 ,16,0}, //#TVAR_ash_pGAS[103]
{0x0F12, 0x016B ,16,0}, //#TVAR_ash_pGAS[104]
{0x0F12, 0x0123 ,16,0}, //#TVAR_ash_pGAS[105]
{0x0F12, 0x00D2 ,16,0}, //#TVAR_ash_pGAS[106]
{0x0F12, 0x0093 ,16,0}, //#TVAR_ash_pGAS[107]
{0x0F12, 0x0066 ,16,0}, //#TVAR_ash_pGAS[108]
{0x0F12, 0x0049 ,16,0}, //#TVAR_ash_pGAS[109]
{0x0F12, 0x003F ,16,0}, //#TVAR_ash_pGAS[110]
{0x0F12, 0x004A ,16,0}, //#TVAR_ash_pGAS[111]
{0x0F12, 0x0069 ,16,0}, //#TVAR_ash_pGAS[112]
{0x0F12, 0x0099 ,16,0}, //#TVAR_ash_pGAS[113]
{0x0F12, 0x00D8 ,16,0}, //#TVAR_ash_pGAS[114]
{0x0F12, 0x0125 ,16,0}, //#TVAR_ash_pGAS[115]
{0x0F12, 0x016E ,16,0}, //#TVAR_ash_pGAS[116]
{0x0F12, 0x0190 ,16,0}, //#TVAR_ash_pGAS[117]
{0x0F12, 0x0155 ,16,0}, //#TVAR_ash_pGAS[118]
{0x0F12, 0x0106 ,16,0}, //#TVAR_ash_pGAS[119]
{0x0F12, 0x00CC ,16,0}, //#TVAR_ash_pGAS[120]
{0x0F12, 0x009F ,16,0}, //#TVAR_ash_pGAS[121]
{0x0F12, 0x0086 ,16,0}, //#TVAR_ash_pGAS[122]
{0x0F12, 0x007D ,16,0}, //#TVAR_ash_pGAS[123]
{0x0F12, 0x0088 ,16,0}, //#TVAR_ash_pGAS[124]
{0x0F12, 0x00A4 ,16,0}, //#TVAR_ash_pGAS[125]
{0x0F12, 0x00D2 ,16,0}, //#TVAR_ash_pGAS[126]
{0x0F12, 0x0113 ,16,0}, //#TVAR_ash_pGAS[127]
{0x0F12, 0x015C ,16,0}, //#TVAR_ash_pGAS[128]
{0x0F12, 0x0192 ,16,0}, //#TVAR_ash_pGAS[129]
{0x0F12, 0x01A8 ,16,0}, //#TVAR_ash_pGAS[130]
{0x0F12, 0x0185 ,16,0}, //#TVAR_ash_pGAS[131]
{0x0F12, 0x0140 ,16,0}, //#TVAR_ash_pGAS[132]
{0x0F12, 0x0107 ,16,0}, //#TVAR_ash_pGAS[133]
{0x0F12, 0x00DC ,16,0}, //#TVAR_ash_pGAS[134]
{0x0F12, 0x00C4 ,16,0}, //#TVAR_ash_pGAS[135]
{0x0F12, 0x00BE ,16,0}, //#TVAR_ash_pGAS[136]
{0x0F12, 0x00C9 ,16,0}, //#TVAR_ash_pGAS[137]
{0x0F12, 0x00E3 ,16,0}, //#TVAR_ash_pGAS[138]
{0x0F12, 0x010D ,16,0}, //#TVAR_ash_pGAS[139]
{0x0F12, 0x014D ,16,0}, //#TVAR_ash_pGAS[140]
{0x0F12, 0x018F ,16,0}, //#TVAR_ash_pGAS[141]
{0x0F12, 0x01A9 ,16,0}, //#TVAR_ash_pGAS[142]
{0x0F12, 0x01CD ,16,0}, //#TVAR_ash_pGAS[143]
{0x0F12, 0x0174 ,16,0}, //#TVAR_ash_pGAS[144]
{0x0F12, 0x0149 ,16,0}, //#TVAR_ash_pGAS[145]
{0x0F12, 0x0118 ,16,0}, //#TVAR_ash_pGAS[146]
{0x0F12, 0x00F2 ,16,0}, //#TVAR_ash_pGAS[147]
{0x0F12, 0x00D8 ,16,0}, //#TVAR_ash_pGAS[148]
{0x0F12, 0x00CC ,16,0}, //#TVAR_ash_pGAS[149]
{0x0F12, 0x00CD ,16,0}, //#TVAR_ash_pGAS[150]
{0x0F12, 0x00DF ,16,0}, //#TVAR_ash_pGAS[151]
{0x0F12, 0x00FC ,16,0}, //#TVAR_ash_pGAS[152]
{0x0F12, 0x0125 ,16,0}, //#TVAR_ash_pGAS[153]
{0x0F12, 0x0150 ,16,0}, //#TVAR_ash_pGAS[154]
{0x0F12, 0x018B ,16,0}, //#TVAR_ash_pGAS[155]
{0x0F12, 0x017B ,16,0}, //#TVAR_ash_pGAS[156]
{0x0F12, 0x0144 ,16,0}, //#TVAR_ash_pGAS[157]
{0x0F12, 0x0109 ,16,0}, //#TVAR_ash_pGAS[158]
{0x0F12, 0x00D7 ,16,0}, //#TVAR_ash_pGAS[159]
{0x0F12, 0x00B4 ,16,0}, //#TVAR_ash_pGAS[160]
{0x0F12, 0x009A ,16,0}, //#TVAR_ash_pGAS[161]
{0x0F12, 0x008E ,16,0}, //#TVAR_ash_pGAS[162]
{0x0F12, 0x0090 ,16,0}, //#TVAR_ash_pGAS[163]
{0x0F12, 0x00A2 ,16,0}, //#TVAR_ash_pGAS[164]
{0x0F12, 0x00C2 ,16,0}, //#TVAR_ash_pGAS[165]
{0x0F12, 0x00EE ,16,0}, //#TVAR_ash_pGAS[166]
{0x0F12, 0x0127 ,16,0}, //#TVAR_ash_pGAS[167]
{0x0F12, 0x015A ,16,0}, //#TVAR_ash_pGAS[168]
{0x0F12, 0x0157 ,16,0}, //#TVAR_ash_pGAS[169]
{0x0F12, 0x0116 ,16,0}, //#TVAR_ash_pGAS[170]
{0x0F12, 0x00D4 ,16,0}, //#TVAR_ash_pGAS[171]
{0x0F12, 0x00A0 ,16,0}, //#TVAR_ash_pGAS[172]
{0x0F12, 0x007A ,16,0}, //#TVAR_ash_pGAS[173]
{0x0F12, 0x0061 ,16,0}, //#TVAR_ash_pGAS[174]
{0x0F12, 0x0056 ,16,0}, //#TVAR_ash_pGAS[175]
{0x0F12, 0x005B ,16,0}, //#TVAR_ash_pGAS[176]
{0x0F12, 0x006F ,16,0}, //#TVAR_ash_pGAS[177]
{0x0F12, 0x008F ,16,0}, //#TVAR_ash_pGAS[178]
{0x0F12, 0x00BE ,16,0}, //#TVAR_ash_pGAS[179]
{0x0F12, 0x00FA ,16,0}, //#TVAR_ash_pGAS[180]
{0x0F12, 0x013A ,16,0}, //#TVAR_ash_pGAS[181]
{0x0F12, 0x0133 ,16,0}, //#TVAR_ash_pGAS[182]
{0x0F12, 0x00EA ,16,0}, //#TVAR_ash_pGAS[183]
{0x0F12, 0x00A9 ,16,0}, //#TVAR_ash_pGAS[184]
{0x0F12, 0x0075 ,16,0}, //#TVAR_ash_pGAS[185]
{0x0F12, 0x004D ,16,0}, //#TVAR_ash_pGAS[186]
{0x0F12, 0x0034 ,16,0}, //#TVAR_ash_pGAS[187]
{0x0F12, 0x002A ,16,0}, //#TVAR_ash_pGAS[188]
{0x0F12, 0x002F ,16,0}, //#TVAR_ash_pGAS[189]
{0x0F12, 0x0043 ,16,0}, //#TVAR_ash_pGAS[190]
{0x0F12, 0x0066 ,16,0}, //#TVAR_ash_pGAS[191]
{0x0F12, 0x0097 ,16,0}, //#TVAR_ash_pGAS[192]
{0x0F12, 0x00D7 ,16,0}, //#TVAR_ash_pGAS[193]
{0x0F12, 0x011B ,16,0}, //#TVAR_ash_pGAS[194]
{0x0F12, 0x0115 ,16,0}, //#TVAR_ash_pGAS[195]
{0x0F12, 0x00CB ,16,0}, //#TVAR_ash_pGAS[196]
{0x0F12, 0x008D ,16,0}, //#TVAR_ash_pGAS[197]
{0x0F12, 0x0056 ,16,0}, //#TVAR_ash_pGAS[198]
{0x0F12, 0x002F ,16,0}, //#TVAR_ash_pGAS[199]
{0x0F12, 0x0016 ,16,0}, //#TVAR_ash_pGAS[200]
{0x0F12, 0x000C ,16,0}, //#TVAR_ash_pGAS[201]
{0x0F12, 0x0012 ,16,0}, //#TVAR_ash_pGAS[202]
{0x0F12, 0x0029 ,16,0}, //#TVAR_ash_pGAS[203]
{0x0F12, 0x004C ,16,0}, //#TVAR_ash_pGAS[204]
{0x0F12, 0x007F ,16,0}, //#TVAR_ash_pGAS[205]
{0x0F12, 0x00BF ,16,0}, //#TVAR_ash_pGAS[206]
{0x0F12, 0x0109 ,16,0}, //#TVAR_ash_pGAS[207]
{0x0F12, 0x0107 ,16,0}, //#TVAR_ash_pGAS[208]
{0x0F12, 0x00BC ,16,0}, //#TVAR_ash_pGAS[209]
{0x0F12, 0x007D ,16,0}, //#TVAR_ash_pGAS[210]
{0x0F12, 0x004B ,16,0}, //#TVAR_ash_pGAS[211]
{0x0F12, 0x0022 ,16,0}, //#TVAR_ash_pGAS[212]
{0x0F12, 0x0008 ,16,0}, //#TVAR_ash_pGAS[213]
{0x0F12, 0x0000 ,16,0}, //#TVAR_ash_pGAS[214]
{0x0F12, 0x0006 ,16,0}, //#TVAR_ash_pGAS[215]
{0x0F12, 0x001E ,16,0}, //#TVAR_ash_pGAS[216]
{0x0F12, 0x0043 ,16,0}, //#TVAR_ash_pGAS[217]
{0x0F12, 0x0074 ,16,0}, //#TVAR_ash_pGAS[218]
{0x0F12, 0x00B8 ,16,0}, //#TVAR_ash_pGAS[219]
{0x0F12, 0x0100 ,16,0}, //#TVAR_ash_pGAS[220]
{0x0F12, 0x0102 ,16,0}, //#TVAR_ash_pGAS[221]
{0x0F12, 0x00BB ,16,0}, //#TVAR_ash_pGAS[222]
{0x0F12, 0x007C ,16,0}, //#TVAR_ash_pGAS[223]
{0x0F12, 0x0049 ,16,0}, //#TVAR_ash_pGAS[224]
{0x0F12, 0x0022 ,16,0}, //#TVAR_ash_pGAS[225]
{0x0F12, 0x0009 ,16,0}, //#TVAR_ash_pGAS[226]
{0x0F12, 0x0001 ,16,0}, //#TVAR_ash_pGAS[227]
{0x0F12, 0x0009 ,16,0}, //#TVAR_ash_pGAS[228]
{0x0F12, 0x0021 ,16,0}, //#TVAR_ash_pGAS[229]
{0x0F12, 0x0047 ,16,0}, //#TVAR_ash_pGAS[230]
{0x0F12, 0x0077 ,16,0}, //#TVAR_ash_pGAS[231]
{0x0F12, 0x00BA ,16,0}, //#TVAR_ash_pGAS[232]
{0x0F12, 0x0105 ,16,0}, //#TVAR_ash_pGAS[233]
{0x0F12, 0x010D ,16,0}, //#TVAR_ash_pGAS[234]
{0x0F12, 0x00C8 ,16,0}, //#TVAR_ash_pGAS[235]
{0x0F12, 0x0088 ,16,0}, //#TVAR_ash_pGAS[236]
{0x0F12, 0x0057 ,16,0}, //#TVAR_ash_pGAS[237]
{0x0F12, 0x0032 ,16,0}, //#TVAR_ash_pGAS[238]
{0x0F12, 0x001A ,16,0}, //#TVAR_ash_pGAS[239]
{0x0F12, 0x0012 ,16,0}, //#TVAR_ash_pGAS[240]
{0x0F12, 0x0019 ,16,0}, //#TVAR_ash_pGAS[241]
{0x0F12, 0x0032 ,16,0}, //#TVAR_ash_pGAS[242]
{0x0F12, 0x0059 ,16,0}, //#TVAR_ash_pGAS[243]
{0x0F12, 0x0088 ,16,0}, //#TVAR_ash_pGAS[244]
{0x0F12, 0x00C8 ,16,0}, //#TVAR_ash_pGAS[245]
{0x0F12, 0x0116 ,16,0}, //#TVAR_ash_pGAS[246]
{0x0F12, 0x0128 ,16,0}, //#TVAR_ash_pGAS[247]
{0x0F12, 0x00E3 ,16,0}, //#TVAR_ash_pGAS[248]
{0x0F12, 0x00A4 ,16,0}, //#TVAR_ash_pGAS[249]
{0x0F12, 0x0074 ,16,0}, //#TVAR_ash_pGAS[250]
{0x0F12, 0x0051 ,16,0}, //#TVAR_ash_pGAS[251]
{0x0F12, 0x003B ,16,0}, //#TVAR_ash_pGAS[252]
{0x0F12, 0x0033 ,16,0}, //#TVAR_ash_pGAS[253]
{0x0F12, 0x003C ,16,0}, //#TVAR_ash_pGAS[254]
{0x0F12, 0x0055 ,16,0}, //#TVAR_ash_pGAS[255]
{0x0F12, 0x007B ,16,0}, //#TVAR_ash_pGAS[256]
{0x0F12, 0x00AB ,16,0}, //#TVAR_ash_pGAS[257]
{0x0F12, 0x00E8 ,16,0}, //#TVAR_ash_pGAS[258]
{0x0F12, 0x012E ,16,0}, //#TVAR_ash_pGAS[259]
{0x0F12, 0x0145 ,16,0}, //#TVAR_ash_pGAS[260]
{0x0F12, 0x010C ,16,0}, //#TVAR_ash_pGAS[261]
{0x0F12, 0x00CC ,16,0}, //#TVAR_ash_pGAS[262]
{0x0F12, 0x009E ,16,0}, //#TVAR_ash_pGAS[263]
{0x0F12, 0x007B ,16,0}, //#TVAR_ash_pGAS[264]
{0x0F12, 0x0069 ,16,0}, //#TVAR_ash_pGAS[265]
{0x0F12, 0x0063 ,16,0}, //#TVAR_ash_pGAS[266]
{0x0F12, 0x006C ,16,0}, //#TVAR_ash_pGAS[267]
{0x0F12, 0x0083 ,16,0}, //#TVAR_ash_pGAS[268]
{0x0F12, 0x00AA ,16,0}, //#TVAR_ash_pGAS[269]
{0x0F12, 0x00D8 ,16,0}, //#TVAR_ash_pGAS[270]
{0x0F12, 0x0115 ,16,0}, //#TVAR_ash_pGAS[271]
{0x0F12, 0x0147 ,16,0}, //#TVAR_ash_pGAS[272]
{0x0F12, 0x015C ,16,0}, //#TVAR_ash_pGAS[273]
{0x0F12, 0x012F ,16,0}, //#TVAR_ash_pGAS[274]
{0x0F12, 0x00F8 ,16,0}, //#TVAR_ash_pGAS[275]
{0x0F12, 0x00C9 ,16,0}, //#TVAR_ash_pGAS[276]
{0x0F12, 0x00AB ,16,0}, //#TVAR_ash_pGAS[277]
{0x0F12, 0x0099 ,16,0}, //#TVAR_ash_pGAS[278]
{0x0F12, 0x0093 ,16,0}, //#TVAR_ash_pGAS[279]
{0x0F12, 0x009E ,16,0}, //#TVAR_ash_pGAS[280]
{0x0F12, 0x00B5 ,16,0}, //#TVAR_ash_pGAS[281]
{0x0F12, 0x00D7 ,16,0}, //#TVAR_ash_pGAS[282]
{0x0F12, 0x0108 ,16,0}, //#TVAR_ash_pGAS[283]
{0x0F12, 0x0141 ,16,0}, //#TVAR_ash_pGAS[284]
{0x0F12, 0x015B ,16,0}, //#TVAR_ash_pGAS[285]
{0x0F12, 0x018E ,16,0}, //#TVAR_ash_pGAS[286]
{0x0F12, 0x0147 ,16,0}, //#TVAR_ash_pGAS[287]
{0x0F12, 0x0121 ,16,0}, //#TVAR_ash_pGAS[288]
{0x0F12, 0x00F6 ,16,0}, //#TVAR_ash_pGAS[289]
{0x0F12, 0x00D9 ,16,0}, //#TVAR_ash_pGAS[290]
{0x0F12, 0x00C8 ,16,0}, //#TVAR_ash_pGAS[291]
{0x0F12, 0x00C1 ,16,0}, //#TVAR_ash_pGAS[292]
{0x0F12, 0x00CC ,16,0}, //#TVAR_ash_pGAS[293]
{0x0F12, 0x00E2 ,16,0}, //#TVAR_ash_pGAS[294]
{0x0F12, 0x0107 ,16,0}, //#TVAR_ash_pGAS[295]
{0x0F12, 0x0134 ,16,0}, //#TVAR_ash_pGAS[296]
{0x0F12, 0x0160 ,16,0}, //#TVAR_ash_pGAS[297]
{0x0F12, 0x0193 ,16,0}, //#TVAR_ash_pGAS[298]
{0x0F12, 0x0158 ,16,0}, //#TVAR_ash_pGAS[299]
{0x0F12, 0x0127 ,16,0}, //#TVAR_ash_pGAS[300]
{0x0F12, 0x00EF ,16,0}, //#TVAR_ash_pGAS[301]
{0x0F12, 0x00C3 ,16,0}, //#TVAR_ash_pGAS[302]
{0x0F12, 0x00A3 ,16,0}, //#TVAR_ash_pGAS[303]
{0x0F12, 0x0090 ,16,0}, //#TVAR_ash_pGAS[304]
{0x0F12, 0x008B ,16,0}, //#TVAR_ash_pGAS[305]
{0x0F12, 0x0092 ,16,0}, //#TVAR_ash_pGAS[306]
{0x0F12, 0x00A8 ,16,0}, //#TVAR_ash_pGAS[307]
{0x0F12, 0x00CE ,16,0}, //#TVAR_ash_pGAS[308]
{0x0F12, 0x00FF ,16,0}, //#TVAR_ash_pGAS[309]
{0x0F12, 0x0138 ,16,0}, //#TVAR_ash_pGAS[310]
{0x0F12, 0x0169 ,16,0}, //#TVAR_ash_pGAS[311]
{0x0F12, 0x013B ,16,0}, //#TVAR_ash_pGAS[312]
{0x0F12, 0x00FD ,16,0}, //#TVAR_ash_pGAS[313]
{0x0F12, 0x00C0 ,16,0}, //#TVAR_ash_pGAS[314]
{0x0F12, 0x0092 ,16,0}, //#TVAR_ash_pGAS[315]
{0x0F12, 0x0072 ,16,0}, //#TVAR_ash_pGAS[316]
{0x0F12, 0x005C ,16,0}, //#TVAR_ash_pGAS[317]
{0x0F12, 0x0055 ,16,0}, //#TVAR_ash_pGAS[318]
{0x0F12, 0x005F ,16,0}, //#TVAR_ash_pGAS[319]
{0x0F12, 0x0076 ,16,0}, //#TVAR_ash_pGAS[320]
{0x0F12, 0x009B ,16,0}, //#TVAR_ash_pGAS[321]
{0x0F12, 0x00CD ,16,0}, //#TVAR_ash_pGAS[322]
{0x0F12, 0x010D ,16,0}, //#TVAR_ash_pGAS[323]
{0x0F12, 0x014A ,16,0}, //#TVAR_ash_pGAS[324]
{0x0F12, 0x011C ,16,0}, //#TVAR_ash_pGAS[325]
{0x0F12, 0x00DA ,16,0}, //#TVAR_ash_pGAS[326]
{0x0F12, 0x009E ,16,0}, //#TVAR_ash_pGAS[327]
{0x0F12, 0x006C ,16,0}, //#TVAR_ash_pGAS[328]
{0x0F12, 0x0048 ,16,0}, //#TVAR_ash_pGAS[329]
{0x0F12, 0x0031 ,16,0}, //#TVAR_ash_pGAS[330]
{0x0F12, 0x002A ,16,0}, //#TVAR_ash_pGAS[331]
{0x0F12, 0x0033 ,16,0}, //#TVAR_ash_pGAS[332]
{0x0F12, 0x004A ,16,0}, //#TVAR_ash_pGAS[333]
{0x0F12, 0x0071 ,16,0}, //#TVAR_ash_pGAS[334]
{0x0F12, 0x00A4 ,16,0}, //#TVAR_ash_pGAS[335]
{0x0F12, 0x00E6 ,16,0}, //#TVAR_ash_pGAS[336]
{0x0F12, 0x012B ,16,0}, //#TVAR_ash_pGAS[337]
{0x0F12, 0x0108 ,16,0}, //#TVAR_ash_pGAS[338]
{0x0F12, 0x00C2 ,16,0}, //#TVAR_ash_pGAS[339]
{0x0F12, 0x0085 ,16,0}, //#TVAR_ash_pGAS[340]
{0x0F12, 0x0054 ,16,0}, //#TVAR_ash_pGAS[341]
{0x0F12, 0x002C ,16,0}, //#TVAR_ash_pGAS[342]
{0x0F12, 0x0014 ,16,0}, //#TVAR_ash_pGAS[343]
{0x0F12, 0x000C ,16,0}, //#TVAR_ash_pGAS[344]
{0x0F12, 0x0014 ,16,0}, //#TVAR_ash_pGAS[345]
{0x0F12, 0x002D ,16,0}, //#TVAR_ash_pGAS[346]
{0x0F12, 0x0055 ,16,0}, //#TVAR_ash_pGAS[347]
{0x0F12, 0x0088 ,16,0}, //#TVAR_ash_pGAS[348]
{0x0F12, 0x00C9 ,16,0}, //#TVAR_ash_pGAS[349]
{0x0F12, 0x0111 ,16,0}, //#TVAR_ash_pGAS[350]
{0x0F12, 0x0101 ,16,0}, //#TVAR_ash_pGAS[351]
{0x0F12, 0x00B9 ,16,0}, //#TVAR_ash_pGAS[352]
{0x0F12, 0x007C ,16,0}, //#TVAR_ash_pGAS[353]
{0x0F12, 0x004A ,16,0}, //#TVAR_ash_pGAS[354]
{0x0F12, 0x0021 ,16,0}, //#TVAR_ash_pGAS[355]
{0x0F12, 0x0009 ,16,0}, //#TVAR_ash_pGAS[356]
{0x0F12, 0x0000 ,16,0}, //#TVAR_ash_pGAS[357]
{0x0F12, 0x0007 ,16,0}, //#TVAR_ash_pGAS[358]
{0x0F12, 0x0020 ,16,0}, //#TVAR_ash_pGAS[359]
{0x0F12, 0x0047 ,16,0}, //#TVAR_ash_pGAS[360]
{0x0F12, 0x0079 ,16,0}, //#TVAR_ash_pGAS[361]
{0x0F12, 0x00BA ,16,0}, //#TVAR_ash_pGAS[362]
{0x0F12, 0x0106 ,16,0}, //#TVAR_ash_pGAS[363]
{0x0F12, 0x0104 ,16,0}, //#TVAR_ash_pGAS[364]
{0x0F12, 0x00BE ,16,0}, //#TVAR_ash_pGAS[365]
{0x0F12, 0x007F ,16,0}, //#TVAR_ash_pGAS[366]
{0x0F12, 0x004D ,16,0}, //#TVAR_ash_pGAS[367]
{0x0F12, 0x0025 ,16,0}, //#TVAR_ash_pGAS[368]
{0x0F12, 0x000A ,16,0}, //#TVAR_ash_pGAS[369]
{0x0F12, 0x0001 ,16,0}, //#TVAR_ash_pGAS[370]
{0x0F12, 0x0008 ,16,0}, //#TVAR_ash_pGAS[371]
{0x0F12, 0x001F ,16,0}, //#TVAR_ash_pGAS[372]
{0x0F12, 0x0044 ,16,0}, //#TVAR_ash_pGAS[373]
{0x0F12, 0x0074 ,16,0}, //#TVAR_ash_pGAS[374]
{0x0F12, 0x00B4 ,16,0}, //#TVAR_ash_pGAS[375]
{0x0F12, 0x0101 ,16,0}, //#TVAR_ash_pGAS[376]
{0x0F12, 0x0114 ,16,0}, //#TVAR_ash_pGAS[377]
{0x0F12, 0x00CE ,16,0}, //#TVAR_ash_pGAS[378]
{0x0F12, 0x008F ,16,0}, //#TVAR_ash_pGAS[379]
{0x0F12, 0x005D ,16,0}, //#TVAR_ash_pGAS[380]
{0x0F12, 0x0036 ,16,0}, //#TVAR_ash_pGAS[381]
{0x0F12, 0x001C ,16,0}, //#TVAR_ash_pGAS[382]
{0x0F12, 0x0011 ,16,0}, //#TVAR_ash_pGAS[383]
{0x0F12, 0x0018 ,16,0}, //#TVAR_ash_pGAS[384]
{0x0F12, 0x002E ,16,0}, //#TVAR_ash_pGAS[385]
{0x0F12, 0x0052 ,16,0}, //#TVAR_ash_pGAS[386]
{0x0F12, 0x0080 ,16,0}, //#TVAR_ash_pGAS[387]
{0x0F12, 0x00BC ,16,0}, //#TVAR_ash_pGAS[388]
{0x0F12, 0x0108 ,16,0}, //#TVAR_ash_pGAS[389]
{0x0F12, 0x0136 ,16,0}, //#TVAR_ash_pGAS[390]
{0x0F12, 0x00EE ,16,0}, //#TVAR_ash_pGAS[391]
{0x0F12, 0x00AD ,16,0}, //#TVAR_ash_pGAS[392]
{0x0F12, 0x007D ,16,0}, //#TVAR_ash_pGAS[393]
{0x0F12, 0x0058 ,16,0}, //#TVAR_ash_pGAS[394]
{0x0F12, 0x003E ,16,0}, //#TVAR_ash_pGAS[395]
{0x0F12, 0x0032 ,16,0}, //#TVAR_ash_pGAS[396]
{0x0F12, 0x0037 ,16,0}, //#TVAR_ash_pGAS[397]
{0x0F12, 0x004D ,16,0}, //#TVAR_ash_pGAS[398]
{0x0F12, 0x006F ,16,0}, //#TVAR_ash_pGAS[399]
{0x0F12, 0x009D ,16,0}, //#TVAR_ash_pGAS[400]
{0x0F12, 0x00D4 ,16,0}, //#TVAR_ash_pGAS[401]
{0x0F12, 0x011D ,16,0}, //#TVAR_ash_pGAS[402]
{0x0F12, 0x0158 ,16,0}, //#TVAR_ash_pGAS[403]
{0x0F12, 0x0119 ,16,0}, //#TVAR_ash_pGAS[404]
{0x0F12, 0x00D9 ,16,0}, //#TVAR_ash_pGAS[405]
{0x0F12, 0x00AB ,16,0}, //#TVAR_ash_pGAS[406]
{0x0F12, 0x0085 ,16,0}, //#TVAR_ash_pGAS[407]
{0x0F12, 0x006E ,16,0}, //#TVAR_ash_pGAS[408]
{0x0F12, 0x0063 ,16,0}, //#TVAR_ash_pGAS[409]
{0x0F12, 0x0066 ,16,0}, //#TVAR_ash_pGAS[410]
{0x0F12, 0x007B ,16,0}, //#TVAR_ash_pGAS[411]
{0x0F12, 0x009A ,16,0}, //#TVAR_ash_pGAS[412]
{0x0F12, 0x00C5 ,16,0}, //#TVAR_ash_pGAS[413]
{0x0F12, 0x00FD ,16,0}, //#TVAR_ash_pGAS[414]
{0x0F12, 0x0135 ,16,0}, //#TVAR_ash_pGAS[415]
{0x0F12, 0x0173 ,16,0}, //#TVAR_ash_pGAS[416]
{0x0F12, 0x0140 ,16,0}, //#TVAR_ash_pGAS[417]
{0x0F12, 0x0106 ,16,0}, //#TVAR_ash_pGAS[418]
{0x0F12, 0x00D7 ,16,0}, //#TVAR_ash_pGAS[419]
{0x0F12, 0x00B7 ,16,0}, //#TVAR_ash_pGAS[420]
{0x0F12, 0x00A0 ,16,0}, //#TVAR_ash_pGAS[421]
{0x0F12, 0x0096 ,16,0}, //#TVAR_ash_pGAS[422]
{0x0F12, 0x0097 ,16,0}, //#TVAR_ash_pGAS[423]
{0x0F12, 0x00A9 ,16,0}, //#TVAR_ash_pGAS[424]
{0x0F12, 0x00C6 ,16,0}, //#TVAR_ash_pGAS[425]
{0x0F12, 0x00F0 ,16,0}, //#TVAR_ash_pGAS[426]
{0x0F12, 0x0126 ,16,0}, //#TVAR_ash_pGAS[427]
{0x0F12, 0x0145 ,16,0}, //#TVAR_ash_pGAS[428]
{0x0F12, 0x0163 ,16,0}, //#TVAR_ash_pGAS[429]
{0x0F12, 0x012E ,16,0}, //#TVAR_ash_pGAS[430]
{0x0F12, 0x0108 ,16,0}, //#TVAR_ash_pGAS[431]
{0x0F12, 0x00E2 ,16,0}, //#TVAR_ash_pGAS[432]
{0x0F12, 0x00C5 ,16,0}, //#TVAR_ash_pGAS[433]
{0x0F12, 0x00B9 ,16,0}, //#TVAR_ash_pGAS[434]
{0x0F12, 0x00B2 ,16,0}, //#TVAR_ash_pGAS[435]
{0x0F12, 0x00B9 ,16,0}, //#TVAR_ash_pGAS[436]
{0x0F12, 0x00CE ,16,0}, //#TVAR_ash_pGAS[437]
{0x0F12, 0x00EF ,16,0}, //#TVAR_ash_pGAS[438]
{0x0F12, 0x0119 ,16,0}, //#TVAR_ash_pGAS[439]
{0x0F12, 0x0144 ,16,0}, //#TVAR_ash_pGAS[440]
{0x0F12, 0x016D ,16,0}, //#TVAR_ash_pGAS[441]
{0x0F12, 0x012D ,16,0}, //#TVAR_ash_pGAS[442]
{0x0F12, 0x0108 ,16,0}, //#TVAR_ash_pGAS[443]
{0x0F12, 0x00D8 ,16,0}, //#TVAR_ash_pGAS[444]
{0x0F12, 0x00AE ,16,0}, //#TVAR_ash_pGAS[445]
{0x0F12, 0x0094 ,16,0}, //#TVAR_ash_pGAS[446]
{0x0F12, 0x0087 ,16,0}, //#TVAR_ash_pGAS[447]
{0x0F12, 0x0080 ,16,0}, //#TVAR_ash_pGAS[448]
{0x0F12, 0x0088 ,16,0}, //#TVAR_ash_pGAS[449]
{0x0F12, 0x009C ,16,0}, //#TVAR_ash_pGAS[450]
{0x0F12, 0x00BC ,16,0}, //#TVAR_ash_pGAS[451]
{0x0F12, 0x00E7 ,16,0}, //#TVAR_ash_pGAS[452]
{0x0F12, 0x011C ,16,0}, //#TVAR_ash_pGAS[453]
{0x0F12, 0x0143 ,16,0}, //#TVAR_ash_pGAS[454]
{0x0F12, 0x010F ,16,0}, //#TVAR_ash_pGAS[455]
{0x0F12, 0x00E3 ,16,0}, //#TVAR_ash_pGAS[456]
{0x0F12, 0x00AA ,16,0}, //#TVAR_ash_pGAS[457]
{0x0F12, 0x0081 ,16,0}, //#TVAR_ash_pGAS[458]
{0x0F12, 0x0066 ,16,0}, //#TVAR_ash_pGAS[459]
{0x0F12, 0x0056 ,16,0}, //#TVAR_ash_pGAS[460]
{0x0F12, 0x0050 ,16,0}, //#TVAR_ash_pGAS[461]
{0x0F12, 0x0059 ,16,0}, //#TVAR_ash_pGAS[462]
{0x0F12, 0x006C ,16,0}, //#TVAR_ash_pGAS[463]
{0x0F12, 0x008D ,16,0}, //#TVAR_ash_pGAS[464]
{0x0F12, 0x00B9 ,16,0}, //#TVAR_ash_pGAS[465]
{0x0F12, 0x00F1 ,16,0}, //#TVAR_ash_pGAS[466]
{0x0F12, 0x0125 ,16,0}, //#TVAR_ash_pGAS[467]
{0x0F12, 0x00EF ,16,0}, //#TVAR_ash_pGAS[468]
{0x0F12, 0x00BB ,16,0}, //#TVAR_ash_pGAS[469]
{0x0F12, 0x0083 ,16,0}, //#TVAR_ash_pGAS[470]
{0x0F12, 0x005B ,16,0}, //#TVAR_ash_pGAS[471]
{0x0F12, 0x003E ,16,0}, //#TVAR_ash_pGAS[472]
{0x0F12, 0x002F ,16,0}, //#TVAR_ash_pGAS[473]
{0x0F12, 0x002A ,16,0}, //#TVAR_ash_pGAS[474]
{0x0F12, 0x0030 ,16,0}, //#TVAR_ash_pGAS[475]
{0x0F12, 0x0044 ,16,0}, //#TVAR_ash_pGAS[476]
{0x0F12, 0x0062 ,16,0}, //#TVAR_ash_pGAS[477]
{0x0F12, 0x0091 ,16,0}, //#TVAR_ash_pGAS[478]
{0x0F12, 0x00C9 ,16,0}, //#TVAR_ash_pGAS[479]
{0x0F12, 0x00FF ,16,0}, //#TVAR_ash_pGAS[480]
{0x0F12, 0x00D6 ,16,0}, //#TVAR_ash_pGAS[481]
{0x0F12, 0x009F ,16,0}, //#TVAR_ash_pGAS[482]
{0x0F12, 0x006A ,16,0}, //#TVAR_ash_pGAS[483]
{0x0F12, 0x0041 ,16,0}, //#TVAR_ash_pGAS[484]
{0x0F12, 0x0021 ,16,0}, //#TVAR_ash_pGAS[485]
{0x0F12, 0x0011 ,16,0}, //#TVAR_ash_pGAS[486]
{0x0F12, 0x000D ,16,0}, //#TVAR_ash_pGAS[487]
{0x0F12, 0x0012 ,16,0}, //#TVAR_ash_pGAS[488]
{0x0F12, 0x0025 ,16,0}, //#TVAR_ash_pGAS[489]
{0x0F12, 0x0046 ,16,0}, //#TVAR_ash_pGAS[490]
{0x0F12, 0x0070 ,16,0}, //#TVAR_ash_pGAS[491]
{0x0F12, 0x00A9 ,16,0}, //#TVAR_ash_pGAS[492]
{0x0F12, 0x00E1 ,16,0}, //#TVAR_ash_pGAS[493]
{0x0F12, 0x00CB ,16,0}, //#TVAR_ash_pGAS[494]
{0x0F12, 0x0094 ,16,0}, //#TVAR_ash_pGAS[495]
{0x0F12, 0x005F ,16,0}, //#TVAR_ash_pGAS[496]
{0x0F12, 0x0036 ,16,0}, //#TVAR_ash_pGAS[497]
{0x0F12, 0x0017 ,16,0}, //#TVAR_ash_pGAS[498]
{0x0F12, 0x0005 ,16,0}, //#TVAR_ash_pGAS[499]
{0x0F12, 0x0001 ,16,0}, //#TVAR_ash_pGAS[500]
{0x0F12, 0x0006 ,16,0}, //#TVAR_ash_pGAS[501]
{0x0F12, 0x0018 ,16,0}, //#TVAR_ash_pGAS[502]
{0x0F12, 0x0037 ,16,0}, //#TVAR_ash_pGAS[503]
{0x0F12, 0x005E ,16,0}, //#TVAR_ash_pGAS[504]
{0x0F12, 0x009A ,16,0}, //#TVAR_ash_pGAS[505]
{0x0F12, 0x00D9 ,16,0}, //#TVAR_ash_pGAS[506]
{0x0F12, 0x00C9 ,16,0}, //#TVAR_ash_pGAS[507]
{0x0F12, 0x0094 ,16,0}, //#TVAR_ash_pGAS[508]
{0x0F12, 0x0060 ,16,0}, //#TVAR_ash_pGAS[509]
{0x0F12, 0x0037 ,16,0}, //#TVAR_ash_pGAS[510]
{0x0F12, 0x0018 ,16,0}, //#TVAR_ash_pGAS[511]
{0x0F12, 0x0005 ,16,0}, //#TVAR_ash_pGAS[512]
{0x0F12, 0x0000 ,16,0}, //#TVAR_ash_pGAS[513]
{0x0F12, 0x0005 ,16,0}, //#TVAR_ash_pGAS[514]
{0x0F12, 0x0017 ,16,0}, //#TVAR_ash_pGAS[515]
{0x0F12, 0x0033 ,16,0}, //#TVAR_ash_pGAS[516]
{0x0F12, 0x005A ,16,0}, //#TVAR_ash_pGAS[517]
{0x0F12, 0x0090 ,16,0}, //#TVAR_ash_pGAS[518]
{0x0F12, 0x00CF ,16,0}, //#TVAR_ash_pGAS[519]
{0x0F12, 0x00D8 ,16,0}, //#TVAR_ash_pGAS[520]
{0x0F12, 0x00A3 ,16,0}, //#TVAR_ash_pGAS[521]
{0x0F12, 0x006D ,16,0}, //#TVAR_ash_pGAS[522]
{0x0F12, 0x0044 ,16,0}, //#TVAR_ash_pGAS[523]
{0x0F12, 0x0028 ,16,0}, //#TVAR_ash_pGAS[524]
{0x0F12, 0x0015 ,16,0}, //#TVAR_ash_pGAS[525]
{0x0F12, 0x000D ,16,0}, //#TVAR_ash_pGAS[526]
{0x0F12, 0x0013 ,16,0}, //#TVAR_ash_pGAS[527]
{0x0F12, 0x0023 ,16,0}, //#TVAR_ash_pGAS[528]
{0x0F12, 0x003F ,16,0}, //#TVAR_ash_pGAS[529]
{0x0F12, 0x0063 ,16,0}, //#TVAR_ash_pGAS[530]
{0x0F12, 0x0095 ,16,0}, //#TVAR_ash_pGAS[531]
{0x0F12, 0x00D3 ,16,0}, //#TVAR_ash_pGAS[532]
{0x0F12, 0x00F6 ,16,0}, //#TVAR_ash_pGAS[533]
{0x0F12, 0x00C2 ,16,0}, //#TVAR_ash_pGAS[534]
{0x0F12, 0x008A ,16,0}, //#TVAR_ash_pGAS[535]
{0x0F12, 0x0061 ,16,0}, //#TVAR_ash_pGAS[536]
{0x0F12, 0x0045 ,16,0}, //#TVAR_ash_pGAS[537]
{0x0F12, 0x0035 ,16,0}, //#TVAR_ash_pGAS[538]
{0x0F12, 0x002B ,16,0}, //#TVAR_ash_pGAS[539]
{0x0F12, 0x0030 ,16,0}, //#TVAR_ash_pGAS[540]
{0x0F12, 0x003F ,16,0}, //#TVAR_ash_pGAS[541]
{0x0F12, 0x005A ,16,0}, //#TVAR_ash_pGAS[542]
{0x0F12, 0x007D ,16,0}, //#TVAR_ash_pGAS[543]
{0x0F12, 0x00AB ,16,0}, //#TVAR_ash_pGAS[544]
{0x0F12, 0x00E4 ,16,0}, //#TVAR_ash_pGAS[545]
{0x0F12, 0x0116 ,16,0}, //#TVAR_ash_pGAS[546]
{0x0F12, 0x00EB ,16,0}, //#TVAR_ash_pGAS[547]
{0x0F12, 0x00B4 ,16,0}, //#TVAR_ash_pGAS[548]
{0x0F12, 0x008C ,16,0}, //#TVAR_ash_pGAS[549]
{0x0F12, 0x0071 ,16,0}, //#TVAR_ash_pGAS[550]
{0x0F12, 0x0060 ,16,0}, //#TVAR_ash_pGAS[551]
{0x0F12, 0x005A ,16,0}, //#TVAR_ash_pGAS[552]
{0x0F12, 0x005B ,16,0}, //#TVAR_ash_pGAS[553]
{0x0F12, 0x0068 ,16,0}, //#TVAR_ash_pGAS[554]
{0x0F12, 0x0081 ,16,0}, //#TVAR_ash_pGAS[555]
{0x0F12, 0x00A4 ,16,0}, //#TVAR_ash_pGAS[556]
{0x0F12, 0x00D5 ,16,0}, //#TVAR_ash_pGAS[557]
{0x0F12, 0x00FA ,16,0}, //#TVAR_ash_pGAS[558]
{0x0F12, 0x0138 ,16,0}, //#TVAR_ash_pGAS[559]
{0x0F12, 0x0113 ,16,0}, //#TVAR_ash_pGAS[560]
{0x0F12, 0x00DF ,16,0}, //#TVAR_ash_pGAS[561]
{0x0F12, 0x00B9 ,16,0}, //#TVAR_ash_pGAS[562]
{0x0F12, 0x009F ,16,0}, //#TVAR_ash_pGAS[563]
{0x0F12, 0x008C ,16,0}, //#TVAR_ash_pGAS[564]
{0x0F12, 0x0084 ,16,0}, //#TVAR_ash_pGAS[565]
{0x0F12, 0x0086 ,16,0}, //#TVAR_ash_pGAS[566]
{0x0F12, 0x0090 ,16,0}, //#TVAR_ash_pGAS[567]
{0x0F12, 0x00A9 ,16,0}, //#TVAR_ash_pGAS[568]
{0x0F12, 0x00CE ,16,0}, //#TVAR_ash_pGAS[569]
{0x0F12, 0x00FA ,16,0}, //#TVAR_ash_pGAS[570]
{0x0F12, 0x0107 ,16,0}, //#TVAR_ash_pGAS[571]
              
// param_start TVAR_ash_AwbAshCord
{0x002A, 0x06B8 ,16,0},
{0x0F12, 0x00C7 ,16,0}, //00C0//00D0 // #TVAR_ash_AwbAshCord_0_
{0x0F12, 0x00d9 ,16,0}, //00E0//0102 // #TVAR_ash_AwbAshCord_1_
{0x0F12, 0x0110 ,16,0}, //00F0//010E // #TVAR_ash_AwbAshCord_2_
{0x0F12, 0x0129 ,16,0}, //0129//0137 // #TVAR_ash_AwbAshCord_3_
{0x0F12, 0x0159 ,16,0}, //0156//0171 // #TVAR_ash_AwbAshCord_4_
{0x0F12, 0x0179 ,16,0}, //017F//0198 // #TVAR_ash_AwbAshCord_5_
{0x0F12, 0x018c ,16,0}, //018F//01A8 // #TVAR_ash_AwbAshCord_6_
              
//================================================================================================
// SET CCM    
//================================================================================================
{0x002A, 0x06A6 ,16,0},
{0x0F12, 0x00DE ,16,0}, //00C0//00D8 // #SARR_AwbCcmCord_0_
{0x0F12, 0x00FE ,16,0}, //00E0//00FC // #SARR_AwbCcmCord_1_
{0x0F12, 0x0107 ,16,0}, //00F0//0120 // #SARR_AwbCcmCord_2_
{0x0F12, 0x0138 ,16,0}, //0129//014C // #SARR_AwbCcmCord_3_
{0x0F12, 0x016B ,16,0}, //0156//0184 // #SARR_AwbCcmCord_4_
{0x0F12, 0x0198 ,16,0}, //017F//01AD // #SARR_AwbCcmCord_5_
              
// CCM start address // 7000_33A4
{0x002A, 0x0698 ,16,0}, // SET CCM  
{0x0F12, 0x33A4 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x002A, 0x33A4 ,16,0}, // Horizon
{0x0F12, 0x0172 ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFF64 ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFFA0 ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFF4D ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x01FA ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFEF4 ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFFD9 ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0025 ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x026F ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0299 ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x012F ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFE21 ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0143 ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFF4E ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0183 ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFEBA ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0191 ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x013D ,16,0}, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0172 ,16,0}, //#TVAR_wbt_pBaseCcms[18] // Inca                
{0x0F12, 0xFF64 ,16,0}, //#TVAR_wbt_pBaseCcms[19]                        
{0x0F12, 0xFFA0 ,16,0}, //#TVAR_wbt_pBaseCcms[20]                        
{0x0F12, 0xFF4D ,16,0}, //#TVAR_wbt_pBaseCcms[21]                        
{0x0F12, 0x01FA ,16,0}, //#TVAR_wbt_pBaseCcms[22]                        
{0x0F12, 0xFEF4 ,16,0}, //#TVAR_wbt_pBaseCcms[23]                        
{0x0F12, 0xFFD9 ,16,0}, //#TVAR_wbt_pBaseCcms[24]                        
{0x0F12, 0x0025 ,16,0}, //#TVAR_wbt_pBaseCcms[25]                        
{0x0F12, 0x026F ,16,0}, //#TVAR_wbt_pBaseCcms[26]                        
{0x0F12, 0x0299 ,16,0}, //#TVAR_wbt_pBaseCcms[27]                        
{0x0F12, 0x012F ,16,0}, //#TVAR_wbt_pBaseCcms[28]                        
{0x0F12, 0xFE21 ,16,0}, //#TVAR_wbt_pBaseCcms[29]                        
{0x0F12, 0x0143 ,16,0}, //#TVAR_wbt_pBaseCcms[30]                        
{0x0F12, 0xFF4E ,16,0}, //#TVAR_wbt_pBaseCcms[31]                        
{0x0F12, 0x0183 ,16,0}, //#TVAR_wbt_pBaseCcms[32]                        
{0x0F12, 0xFEBA ,16,0}, //#TVAR_wbt_pBaseCcms[33]                        
{0x0F12, 0x0191 ,16,0}, //#TVAR_wbt_pBaseCcms[34]                        
{0x0F12, 0x013D ,16,0}, //#TVAR_wbt_pBaseCcms[35]                        
{0x0F12, 0x01C8 ,16,0}, //#TVAR_wbt_pBaseCcms[36] // WW                  
{0x0F12, 0xFF57 ,16,0}, //#TVAR_wbt_pBaseCcms[37]                        
{0x0F12, 0xFFC3 ,16,0}, //#TVAR_wbt_pBaseCcms[38]                        
{0x0F12, 0xFF67 ,16,0}, //#TVAR_wbt_pBaseCcms[39]                        
{0x0F12, 0x01AD ,16,0}, //#TVAR_wbt_pBaseCcms[40]                        
{0x0F12, 0xFF39 ,16,0}, //#TVAR_wbt_pBaseCcms[41]                        
{0x0F12, 0xFFE6 ,16,0}, //#TVAR_wbt_pBaseCcms[42]                        
{0x0F12, 0xFFF0 ,16,0}, //#TVAR_wbt_pBaseCcms[43]                        
{0x0F12, 0x01B0 ,16,0}, //#TVAR_wbt_pBaseCcms[44]                        
{0x0F12, 0x00EF ,16,0}, //#TVAR_wbt_pBaseCcms[45]                        
{0x0F12, 0x00EE ,16,0}, //#TVAR_wbt_pBaseCcms[46]                        
{0x0F12, 0xFF1D ,16,0}, //#TVAR_wbt_pBaseCcms[47]                        
{0x0F12, 0x01A4 ,16,0}, //#TVAR_wbt_pBaseCcms[48]                        
{0x0F12, 0xFF70 ,16,0}, //#TVAR_wbt_pBaseCcms[49]                        
{0x0F12, 0x01D0 ,16,0}, //#TVAR_wbt_pBaseCcms[50]                        
{0x0F12, 0xFF3B ,16,0}, //#TVAR_wbt_pBaseCcms[51]                        
{0x0F12, 0x016F ,16,0}, //#TVAR_wbt_pBaseCcms[52]                        
{0x0F12, 0x012C ,16,0}, //#TVAR_wbt_pBaseCcms[53]                        
{0x0F12, 0x01C8 ,16,0}, //#TVAR_wbt_pBaseCcms[54] // CWF                 
{0x0F12, 0xFF57 ,16,0}, //#TVAR_wbt_pBaseCcms[55]                        
{0x0F12, 0xFFC3 ,16,0}, //#TVAR_wbt_pBaseCcms[56]                        
{0x0F12, 0xFF67 ,16,0}, //#TVAR_wbt_pBaseCcms[57]                        
{0x0F12, 0x01AD ,16,0}, //#TVAR_wbt_pBaseCcms[58]                        
{0x0F12, 0xFF39 ,16,0}, //#TVAR_wbt_pBaseCcms[59]                        
{0x0F12, 0xFFE6 ,16,0}, //#TVAR_wbt_pBaseCcms[60]                        
{0x0F12, 0xFFF0 ,16,0}, //#TVAR_wbt_pBaseCcms[61]                        
{0x0F12, 0x01B0 ,16,0}, //#TVAR_wbt_pBaseCcms[62]                        
{0x0F12, 0x00EF ,16,0}, //#TVAR_wbt_pBaseCcms[63]                        
{0x0F12, 0x00EE ,16,0}, //#TVAR_wbt_pBaseCcms[64]                        
{0x0F12, 0xFF1D ,16,0}, //#TVAR_wbt_pBaseCcms[65]                        
{0x0F12, 0x01A4 ,16,0}, //#TVAR_wbt_pBaseCcms[66]                        
{0x0F12, 0xFF70 ,16,0}, //#TVAR_wbt_pBaseCcms[67]                        
{0x0F12, 0x01D0 ,16,0}, //#TVAR_wbt_pBaseCcms[68]                        
{0x0F12, 0xFF3B ,16,0}, //#TVAR_wbt_pBaseCcms[69]                        
{0x0F12, 0x016F ,16,0}, //#TVAR_wbt_pBaseCcms[70]                        
{0x0F12, 0x012C ,16,0}, //#TVAR_wbt_pBaseCcms[71]                        
{0x0F12, 0x01DD ,16,0}, //#TVAR_wbt_pBaseCcms[72] // D50                 
{0x0F12, 0xFF68 ,16,0}, //#TVAR_wbt_pBaseCcms[73]                        
{0x0F12, 0xFFDC ,16,0}, //#TVAR_wbt_pBaseCcms[74]                        
{0x0F12, 0xFF26 ,16,0}, //#TVAR_wbt_pBaseCcms[75]                        
{0x0F12, 0x0221 ,16,0}, //#TVAR_wbt_pBaseCcms[76]                        
{0x0F12, 0xFF05 ,16,0}, //#TVAR_wbt_pBaseCcms[77]                        
{0x0F12, 0xFFD6 ,16,0}, //#TVAR_wbt_pBaseCcms[78]                        
{0x0F12, 0xFFEF ,16,0}, //#TVAR_wbt_pBaseCcms[79]                        

{0x0F12, 0x01C5 ,16,0}, //#TVAR_wbt_pBaseCcms[80]                        
{0x0F12, 0x0139 ,16,0}, //#TVAR_wbt_pBaseCcms[81]                        
{0x0F12, 0x0139 ,16,0}, //#TVAR_wbt_pBaseCcms[82]                        
{0x0F12, 0xFEF5 ,16,0}, //#TVAR_wbt_pBaseCcms[83]                        
{0x0F12, 0x0204 ,16,0}, //#TVAR_wbt_pBaseCcms[84]                        
{0x0F12, 0xFF5A ,16,0}, //#TVAR_wbt_pBaseCcms[85]                        
{0x0F12, 0x0234 ,16,0}, //#TVAR_wbt_pBaseCcms[86]                        
{0x0F12, 0xFF11 ,16,0}, //#TVAR_wbt_pBaseCcms[87]                        
{0x0F12, 0x0185 ,16,0}, //#TVAR_wbt_pBaseCcms[88]                        
{0x0F12, 0x013E ,16,0}, //#TVAR_wbt_pBaseCcms[89]                        
{0x0F12, 0x0199 ,16,0}, //#TVAR_wbt_pBaseCcms[90] // D65                 
{0x0F12, 0xFFA5 ,16,0}, //#TVAR_wbt_pBaseCcms[91]                        
{0x0F12, 0xFFFC ,16,0}, //#TVAR_wbt_pBaseCcms[92]                        
{0x0F12, 0xFF6F ,16,0}, //#TVAR_wbt_pBaseCcms[93]                        
{0x0F12, 0x019F ,16,0}, //#TVAR_wbt_pBaseCcms[94]                        
{0x0F12, 0xFF43 ,16,0}, //#TVAR_wbt_pBaseCcms[95]                        
{0x0F12, 0xFFFB ,16,0}, //#TVAR_wbt_pBaseCcms[96]                        
{0x0F12, 0x0003 ,16,0}, //#TVAR_wbt_pBaseCcms[97]                        
{0x0F12, 0x018E ,16,0}, //#TVAR_wbt_pBaseCcms[98]                        
{0x0F12, 0x010C ,16,0}, //#TVAR_wbt_pBaseCcms[99]                        
{0x0F12, 0x010B ,16,0}, //#TVAR_wbt_pBaseCcms[100]                       
{0x0F12, 0xFF4B ,16,0}, //#TVAR_wbt_pBaseCcms[101]                       
{0x0F12, 0x01F6 ,16,0}, //#TVAR_wbt_pBaseCcms[102]                       
{0x0F12, 0xFFBC ,16,0}, //#TVAR_wbt_pBaseCcms[103]                       
{0x0F12, 0x0222 ,16,0}, //#TVAR_wbt_pBaseCcms[104]                       
{0x0F12, 0xFF4F ,16,0}, //#TVAR_wbt_pBaseCcms[105]                       
{0x0F12, 0x0162 ,16,0}, //#TVAR_wbt_pBaseCcms[106]                       
{0x0F12, 0x0124 ,16,0}, //#TVAR_wbt_pBaseCcms[107]                       
{0x002A, 0x06A0 ,16,0}, // Outdoor CCM address // 7000_3380              
{0x0F12, 0x3380 ,16,0},
{0x0F12, 0x7000 ,16,0},
{0x002A, 0x3380 ,16,0},
{0x0F12, 0x01E0 ,16,0}, //#TVAR_wbt_pOutdoorCcm[0]// Outdoor CCM     
{0x0F12, 0xFF80 ,16,0}, //#TVAR_wbt_pOutdoorCcm[1]                   
{0x0F12, 0xFFD0 ,16,0}, //#TVAR_wbt_pOutdoorCcm[2]                   
{0x0F12, 0xFF61 ,16,0}, //#TVAR_wbt_pOutdoorCcm[3]                   
{0x0F12, 0x01BD ,16,0}, //#TVAR_wbt_pOutdoorCcm[4]                   
{0x0F12, 0xFF34 ,16,0}, //#TVAR_wbt_pOutdoorCcm[5]                   
{0x0F12, 0xFFFE ,16,0}, //#TVAR_wbt_pOutdoorCcm[6]                   
{0x0F12, 0xFFF6 ,16,0}, //#TVAR_wbt_pOutdoorCcm[7]                   
{0x0F12, 0x019D ,16,0}, //#TVAR_wbt_pOutdoorCcm[8]                   
{0x0F12, 0x0107 ,16,0}, //#TVAR_wbt_pOutdoorCcm[9]                   
{0x0F12, 0x010F ,16,0}, //#TVAR_wbt_pOutdoorCcm[10]                  
{0x0F12, 0xFF67 ,16,0}, //#TVAR_wbt_pOutdoorCcm[11]                  
{0x0F12, 0x016C ,16,0}, //#TVAR_wbt_pOutdoorCcm[12]                  
{0x0F12, 0xFF54 ,16,0}, //#TVAR_wbt_pOutdoorCcm[13]                  
{0x0F12, 0x01FC ,16,0}, //#TVAR_wbt_pOutdoorCcm[14]                  
{0x0F12, 0xFF82 ,16,0}, //#TVAR_wbt_pOutdoorCcm[15]                  
{0x0F12, 0x015D ,16,0}, //#TVAR_wbt_pOutdoorCcm[16]                  
{0x0F12, 0x00FD ,16,0}, //#TVAR_wbt_pOutdoorCcm[17]
//===============================================================================================
// SET AWB   
//===============================================================================================
// Indoor boundary
//           
{0x002A, 0x0C48 ,16,0}, // set awb                                                                                    
{0x0F12, 0x03B6 ,16,0}, //03B6 //03C8 // #awbb_IndoorGrZones_m_BGrid[0] // Indoor boundary                                 
{0x0F12, 0x03E2 ,16,0}, //03E2 //03E2 // #awbb_IndoorGrZones_m_BGrid[1]                                                    
{0x0F12, 0x0352 ,16,0}, //0352 //038A // #awbb_IndoorGrZones_m_BGrid[2]                                                    
{0x0F12, 0x03F4 ,16,0}, //03F4 //03F4 // #awbb_IndoorGrZones_m_BGrid[3]                                                    
{0x0F12, 0x0300 ,16,0}, //0300 //034E // #awbb_IndoorGrZones_m_BGrid[4]                                                    
{0x0F12, 0x03E2 ,16,0}, //03E2 //03E2 // #awbb_IndoorGrZones_m_BGrid[5]                                                    
{0x0F12, 0x02CC ,16,0}, //02CA //030A // #awbb_IndoorGrZones_m_BGrid[6]                                                    
{0x0F12, 0x03B6 ,16,0}, //03B6 //03B8 // #awbb_IndoorGrZones_m_BGrid[7]                                                    
{0x0F12, 0x0298 ,16,0}, //0298 //02C8 // #awbb_IndoorGrZones_m_BGrid[8]                                                    
{0x0F12, 0x038A ,16,0}, //038A //038A // #awbb_IndoorGrZones_m_BGrid[9]                                                    
{0x0F12, 0x027A ,16,0}, //027A //029C // #awbb_IndoorGrZones_m_BGrid[10]                                                   
{0x0F12, 0x0356 ,16,0}, //0356 //0356 // #awbb_IndoorGrZones_m_BGrid[11]                                                   
{0x0F12, 0x025E ,16,0}, //025E //0286 // #awbb_IndoorGrZones_m_BGrid[12]                                                   
{0x0F12, 0x0322 ,16,0}, //0322 //0322 // #awbb_IndoorGrZones_m_BGrid[13]                                                   
{0x0F12, 0x023C ,16,0}, //024C //026C // #awbb_IndoorGrZones_m_BGrid[14]                                                   
{0x0F12, 0x02F6 ,16,0}, //02F6 //02F6 // #awbb_IndoorGrZones_m_BGrid[15]                                                   
{0x0F12, 0x021C ,16,0}, //0232 //0254 // #awbb_IndoorGrZones_m_BGrid[16]                                                   
{0x0F12, 0x02CA ,16,0}, //02CA //02CA // #awbb_IndoorGrZones_m_BGrid[17]                                                   
{0x0F12, 0x01FE ,16,0}, //0210 //023E // #awbb_IndoorGrZones_m_BGrid[18]                                                   
{0x0F12, 0x02B8 ,16,0}, //02B8 //02B8 // #awbb_IndoorGrZones_m_BGrid[19]                                                   
{0x0F12, 0x01EE ,16,0}, //01F6 //022E // #awbb_IndoorGrZones_m_BGrid[20]                                                   
{0x0F12, 0x02A6 ,16,0}, //02A6 //02A4 // #awbb_IndoorGrZones_m_BGrid[21]                                                   
{0x0F12, 0x01E4 ,16,0}, //01E4 //0226 // #awbb_IndoorGrZones_m_BGrid[22]                                                   
{0x0F12, 0x0294 ,16,0}, //0294 //0294 // #awbb_IndoorGrZones_m_BGrid[23]                                                   
{0x0F12, 0x01E0 ,16,0}, //01E6 //0220 // #awbb_IndoorGrZones_m_BGrid[24]                                                   
{0x0F12, 0x027E ,16,0}, //027E //027E // #awbb_IndoorGrZones_m_BGrid[25]                                                   
{0x0F12, 0x01E4 ,16,0}, //01EE //022A // #awbb_IndoorGrZones_m_BGrid[26]                                                   
{0x0F12, 0x0264 ,16,0}, //025A //025E // #awbb_IndoorGrZones_m_BGrid[27]                                                   
{0x0F12, 0x01EA ,16,0}, //01FC //0000 // #awbb_IndoorGrZones_m_BGrid[28]                                                   
{0x0F12, 0x024A ,16,0}, //0238 //0000 // #awbb_IndoorGrZones_m_BGrid[29]                                                   
{0x0F12, 0x01F6 ,16,0}, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[30]                                                   
{0x0F12, 0x0230 ,16,0}, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[31]                                                   
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[32]                                                   
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[33]                                                   
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[34]                                                   
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[35]                                                   
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[36]                                                   
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[37]                                                   
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[38]                                                   
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[39]                                                   
{0x0F12, 0x0005 ,16,0}, // #awbb_IndoorGrZones_m_GridStep                                                    
{0x002A, 0x0C9C ,16,0},                                                                                      
{0x0F12, 0x0010 ,16,0}, // #awbb_IndoorGrZones_ZInfo_m_GridSz                                                     
{0x002A, 0x0CA0 ,16,0},                                                                                      
{0x0F12, 0x00FE ,16,0}, // #awbb_IndoorGrZones_m_Boffs[0]                
{0x002A, 0x0CA4 ,16,0},                 
{0x0F12, 0x0218 ,16,0}, //0290 //027E // #awbb_OutdoorGrZones_m_BGrid[0] // Outdoor boundary                               
{0x0F12, 0x0294 ,16,0}, //02C0 //02AE // #awbb_OutdoorGrZones_m_BGrid[1]                                                   
{0x0F12, 0x0200 ,16,0}, //026A //025C // #awbb_OutdoorGrZones_m_BGrid[2]                                                   
{0x0F12, 0x0290 ,16,0}, //02B4 //02B2 // #awbb_OutdoorGrZones_m_BGrid[3]                                                   
{0x0F12, 0x01F4 ,16,0}, //0246 //0244 // #awbb_OutdoorGrZones_m_BGrid[4]                                                   
{0x0F12, 0x027A ,16,0}, //02A8 //02A0 // #awbb_OutdoorGrZones_m_BGrid[5]                                                   
{0x0F12, 0x01EC ,16,0}, //022A //0236 // #awbb_OutdoorGrZones_m_BGrid[6]                                                   
{0x0F12, 0x0264 ,16,0}, //02A0 //0290 // #awbb_OutdoorGrZones_m_BGrid[7]                                                   
{0x0F12, 0x01F6 ,16,0}, //0214 //0230 // #awbb_OutdoorGrZones_m_BGrid[8]                                                   
{0x0F12, 0x024C ,16,0}, //0290 //027A // #awbb_OutdoorGrZones_m_BGrid[9]                                                   
{0x0F12, 0x01FE ,16,0}, //020C //0236 // #awbb_OutdoorGrZones_m_BGrid[10]                                                  
{0x0F12, 0x022E ,16,0}, //027A //025E // #awbb_OutdoorGrZones_m_BGrid[11]                                                  
{0x0F12, 0x0000 ,16,0}, //0218 //0000 // #awbb_OutdoorGrZones_m_BGrid[12]                                                  
{0x0F12, 0x0000 ,16,0}, //025E //0000 // #awbb_OutdoorGrZones_m_BGrid[13]                                                  
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[14]                                                  
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[15]                                                  
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[16]                                                  
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[17]                                                  
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[18]                                                  
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[19]                                                  
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[20]                                                  
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[21]                                                  
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[22]                                  
{0x0F12, 0x0000 ,16,0}, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[23]                                  
{0x0F12, 0x0005 ,16,0}, // #awbb_OutdoorGrZones_m_GridStep                                                         
{0x002A, 0x0CD8 ,16,0},                                                                                            
{0x0F12, 0x0006 ,16,0}, // #awbb_OutdoorGrZones_ZInfo_m_GridSz
{0x002A, 0x0CDC ,16,0}, 
{0x0F12, 0x022E ,16,0}, // #awbb_OutdoorGrZones_m_Boffs                                                            
{0x002A, 0x0D88 ,16,0},                                                                                            
{0x0F12, 0x0000 ,16,0}, // #awbb_OutdoorDetectionZone_m_BGrid[0]_m_left // Outdoor detection zone                  
{0x0F12, 0x00D1 ,16,0}, // #awbb_OutdoorDetectionZone_m_BGrid[0]_m_right                                           
{0x0F12, 0xFFB9 ,16,0}, // #awbb_OutdoorDetectionZone_m_BGrid[1]_m_left                                            
{0x0F12, 0x00C8 ,16,0}, // #awbb_OutdoorDetectionZone_m_BGrid[1]_m_right                                           
{0x0F12, 0xFF63 ,16,0}, // #awbb_OutdoorDetectionZone_m_BGrid[2]_m_left                                            
{0x0F12, 0x00BC ,16,0}, // #awbb_OutdoorDetectionZone_m_BGrid[2]_m_right                                           
{0x0F12, 0xFF1E ,16,0}, // #awbb_OutdoorDetectionZone_m_BGrid[3]_m_left                                            
{0x0F12, 0x00B8 ,16,0}, // #awbb_OutdoorDetectionZone_m_BGrid[3]_m_right                                           
{0x0F12, 0xFEC7 ,16,0}, // #awbb_OutdoorDetectionZone_m_BGrid[4]_m_left                                            
{0x0F12, 0x00D7 ,16,0}, // #awbb_OutdoorDetectionZone_m_BGrid[4]_m_right                                           
{0x0F12, 0x0E74 ,16,0}, // #awbb_OutdoorDetectionZone_ZInfo_m_AbsGridStep                                          
{0x0F12, 0x0000 ,16,0},                                                                                            
{0x0F12, 0x0005 ,16,0}, // #awbb_OutdoorDetectionZone_ZInfo_m_GridSz                                               
{0x0F12, 0x0000 ,16,0},                                                                                            
{0x0F12, 0x03E8 ,16,0}, // #awbb_OutdoorDetectionZone_ZInfo_m_NBoffs                                               
{0x0F12, 0x0000 ,16,0},                                                                                           
{0x0F12, 0x4E20 ,16,0}, // #awbb_OutdoorDetectionZone_ZInfo_m_MaxNB                                               
{0x0F12, 0x0000 ,16,0},
{0x002A, 0x0CE0 ,16,0}, 
{0x0F12, 0x03EA ,16,0}, // #awbb_LowBrGrZones_m_BGrid[0] // LowBr boundary   
{0x0F12, 0x044E ,16,0}, // #awbb_LowBrGrZones_m_BGrid[1]                     
{0x0F12, 0x035E ,16,0}, // #awbb_LowBrGrZones_m_BGrid[2]                     
{0x0F12, 0x044C ,16,0}, // #awbb_LowBrGrZones_m_BGrid[3]                     
{0x0F12, 0x02FA ,16,0}, // #awbb_LowBrGrZones_m_BGrid[4]                     
{0x0F12, 0x0434 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[5]                     
{0x0F12, 0x0296 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[6]                     
{0x0F12, 0x03F2 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[7]                     
{0x0F12, 0x0250 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[8]                     
{0x0F12, 0x03AE ,16,0}, // #awbb_LowBrGrZones_m_BGrid[9]                     
{0x0F12, 0x0216 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[10]                    
{0x0F12, 0x0364 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[11]                    
{0x0F12, 0x01DE ,16,0}, // #awbb_LowBrGrZones_m_BGrid[12]                    
{0x0F12, 0x031C ,16,0}, // #awbb_LowBrGrZones_m_BGrid[13]                    
{0x0F12, 0x01BE ,16,0}, // #awbb_LowBrGrZones_m_BGrid[14]                    
{0x0F12, 0x02D4 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[15]                    
{0x0F12, 0x019C ,16,0}, // #awbb_LowBrGrZones_m_BGrid[16]                    
{0x0F12, 0x029A ,16,0}, // #awbb_LowBrGrZones_m_BGrid[17]                    
{0x0F12, 0x0184 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[18]                    
{0x0F12, 0x0262 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[19]                    
{0x0F12, 0x0190 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[20]                    
{0x0F12, 0x0216 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[21]                    
{0x0F12, 0x0000 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[22]                    
{0x0F12, 0x0000 ,16,0}, // #awbb_LowBrGrZones_m_BGrid[23]                    
{0x0F12, 0x0006 ,16,0}, // #awbb_LowBrGrZones_m_GridStep                     
{0x002A, 0x0D14 ,16,0},                                                      
{0x0F12, 0x000B ,16,0}, // #awbb_LowBrGrZones_ZInfo_m_GridSz                    
{0x002A, 0x0D18 ,16,0},
{0x0F12, 0x009A ,16,0}, // #awbb_LowBrGrZones_m_Boffs    
{0x002A, 0x0D1C ,16,0},
{0x0F12, 0x036C ,16,0}, // #awbb_CrclLowT_R_c                                                       
{0x002A, 0x0D20 ,16,0},                                                                             
{0x0F12, 0x011C ,16,0}, // #awbb_CrclLowT_B_c                                                       
{0x002A, 0x0D24 ,16,0},                                                                             
{0x0F12, 0x6184 ,16,0}, // #awbb_CrclLowT_Rad_c                                                     
{0x002A, 0x0D2C ,16,0},                                                                             
{0x0F12, 0x0135 ,16,0}, // #awbb_IntcR                                                              
{0x0F12, 0x012B ,16,0}, // #awbb_IntcB                                                              
{0x002A, 0x0D28 ,16,0},                                                                             
{0x0F12, 0x024E ,16,0}, // #awbb_OutdoorWP_r                                                        
{0x0F12, 0x027B ,16,0}, // #awbb_OutdoorWP_b                                                        
{0x002A, 0x0E4C ,16,0},                                                                             
{0x0F12, 0x0000 ,16,0}, // #awbboost_useBoosting4Outdoor                                            
{0x002A, 0x0D4C ,16,0},                                                                             
{0x0F12, 0x0653 ,16,0}, // #awbb_GamutWidthThr1                                                     
{0x0F12, 0x02EB ,16,0}, // #awbb_GamutHeightThr1                                                    
{0x0F12, 0x002C ,16,0}, // #awbb_GamutWidthThr2                                                     
{0x0F12, 0x000B ,16,0}, // #awbb_GamutHeightThr2                                                    
{0x002A, 0x0D5C ,16,0},                                                                             
{0x0F12, 0x7FFF ,16,0}, // #awbb_LowTempRB                                                          
{0x0F12, 0x0050 ,16,0}, // #awbb_LowTemp_RBzone                                                     
{0x002A, 0x0D46 ,16,0},                                                                             
{0x0F12, 0x053A ,16,0}, //035E // #awbb_MvEq_RBthresh                                              
{0x002A, 0x0D4A ,16,0},                                                                             
{0x0F12, 0x000A ,16,0}, // #awbb_MovingScale10                                                      
{0x002A, 0x0DD4 ,16,0},                                                                             
{0x0F12, 0xFFFE ,16,0}, // #awbb_GridCorr_R_0__0_ 
{0x0F12, 0xFFFE ,16,0}, // #awbb_GridCorr_R_0__1_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_0__2_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_0__3_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_0__4_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_0__5_ 
{0x0F12, 0xFFFD ,16,0}, // #awbb_GridCorr_R_1__0_ 
{0x0F12, 0xFFFD ,16,0}, // #awbb_GridCorr_R_1__1_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_1__2_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_1__3_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_1__4_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_1__5_ 
{0x0F12, 0xFFFC ,16,0}, // #awbb_GridCorr_R_2__0_ 
{0x0F12, 0xFFFC ,16,0}, // #awbb_GridCorr_R_2__1_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_2__2_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_2__3_                                                                              
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_2__4_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_R_2__5_ 
{0x0F12, 0x000C ,16,0}, // #awbb_GridCorr_B_0__0_ 
{0x0F12, 0x0006 ,16,0}, // #awbb_GridCorr_B_0__1_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_0__2_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_0__3_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_0__4_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_0__5_ 
{0x0F12, 0x000C ,16,0}, // #awbb_GridCorr_B_1__0_ 
{0x0F12, 0x0006 ,16,0}, // #awbb_GridCorr_B_1__1_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_1__2_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_1__3_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_1__4_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_1__5_ 
{0x0F12, 0x000C ,16,0}, // #awbb_GridCorr_B_2__0_ 
{0x0F12, 0x0006 ,16,0}, // #awbb_GridCorr_B_2__1_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_2__2_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_2__3_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_2__4_ 
{0x0F12, 0x0000 ,16,0}, // #awbb_GridCorr_B_2__5_ 
{0x0F12, 0x02F0 ,16,0}, // #awbb_GridConst_1_0_ 
{0x0F12, 0x0358 ,16,0}, // #awbb_GridConst_1_1_ 
{0x0F12, 0x03A5 ,16,0}, // #awbb_GridConst_1_2_ 
{0x0F12, 0x0F9C ,16,0}, // #awbb_GridConst_2_0_
{0x0F12, 0x0FFA ,16,0}, // #awbb_GridConst_2_1_
{0x0F12, 0x10B5 ,16,0}, // #awbb_GridConst_2_2_
{0x0F12, 0x1126 ,16,0}, // #awbb_GridConst_2_3_
{0x0F12, 0x1176 ,16,0}, // #awbb_GridConst_2_4_
{0x0F12, 0x1220 ,16,0}, // #awbb_GridConst_2_5_
{0x0F12, 0x00B2 ,16,0}, // #awbb_GridCoeff_R_1
{0x0F12, 0x00B8 ,16,0}, // #awbb_GridCoeff_B_1
{0x0F12, 0x00B7 ,16,0}, // #awbb_GridCoeff_R_2
{0x0F12, 0x00B3 ,16,0}, // #awbb_GridCoeff_B_2
{0x002A, 0x0E3E ,16,0},
{0x0F12, 0x0000 ,16,0}, // #awbb_rpl_InvalidOutdoor off                                             
{0x002A, 0x22DE ,16,0},                                                                             
{0x0F12, 0x0004 ,16,0}, // #Mon_AWB_ByPassMode // [0]Outdoor [1]LowBr [2]LowTemp                    
{0x002A, 0x337C ,16,0},                                                                             
{0x0F12, 0x00B3 ,16,0}, // #Tune_TP_ChMoveToNearR                                                   
{0x0F12, 0x0040 ,16,0}, // #Tune_TP_AvMoveToGamutDist                                               
{0x002A, 0x0E44 ,16,0}, // AWB initial point                                                        
{0x0F12, 0x053C ,16,0}, // #define awbb_GainsInit_0_                                               
{0x0F12, 0x0400 ,16,0}, // #define awbb_GainsInit_1_                                                
{0x0F12, 0x055C ,16,0}, // #define awbb_GainsInit_2_                                                
{0x002A, 0x0E36 ,16,0}, // Set AWB global offset                                                    
{0x0F12, 0x0000 ,16,0}, // #awbb_RGainOff                                                            
{0x0F12, 0x0000 ,16,0}, // #awbb_BGainOff                                                            
{0x0F12, 0x0000 ,16,0}, // #awbb_GGainOff                                                            
{0x002A, 0x0E4A ,16,0},                                                                             
{0x0F12, 0x0002 ,16,0},
//===============================================================================================
// SET GAMMA 
//===============================================================================================
{0x002A, 0x3288 ,16,0},
{0x0F12, 0x0000 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__0_ 70003288// Indoor gamma                
{0x0F12, 0x0046 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__1_ 7000328A                               
{0x0F12, 0x0064 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__2_ 7000328C                               
{0x0F12, 0x008A ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__3_ 7000328E                               
{0x0F12, 0x00BE ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__4_ 70003290                               
{0x0F12, 0x0118 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__5_ 70003292                               
{0x0F12, 0x015E ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__6_ 70003294                               
{0x0F12, 0x017C ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__7_ 70003296                               
{0x0F12, 0x0194 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__8_ 70003298                               
{0x0F12, 0x01C0 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__9_ 7000329A                               
{0x0F12, 0x01E7 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__10_ 7000329C                              
{0x0F12, 0x020E ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__11_ 7000329E                              
{0x0F12, 0x0232 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__12_ 700032A0                              
{0x0F12, 0x0273 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__13_ 700032A2                              
{0x0F12, 0x02AF ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__14_ 700032A4                              
{0x0F12, 0x0309 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__15_ 700032A6                              
{0x0F12, 0x0355 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__16_ 700032A8                              
{0x0F12, 0x0394 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__17_ 700032AA                              
{0x0F12, 0x03CE ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__18_ 700032AC                              
{0x0F12, 0x03FF ,16,0}, // #SARR_usDualGammaLutRGBIndoor_0__19_ 700032AE                              
{0x0F12, 0x0000 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__0_ 700032B0                               
{0x0F12, 0x0046 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__1_ 700032B2                               
{0x0F12, 0x0064 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__2_ 700032B4                               
{0x0F12, 0x008A ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__3_ 700032B6                               
{0x0F12, 0x00BE ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__4_ 700032B8                               
{0x0F12, 0x0118 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__5_ 700032BA                               
{0x0F12, 0x015E ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__6_ 700032BC                               
{0x0F12, 0x017C ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__7_ 700032BE                               
{0x0F12, 0x0194 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__8_ 700032C0                               
{0x0F12, 0x01C0 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__9_ 700032C2                               
{0x0F12, 0x01E7 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__10_ 700032C4                              
{0x0F12, 0x020E ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__11_ 700032C6                              
{0x0F12, 0x0232 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__12_ 700032C8                              
{0x0F12, 0x0273 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__13_ 700032CA                              
{0x0F12, 0x02AF ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__14_ 700032CC                              
{0x0F12, 0x0309 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__15_ 700032CE                              
{0x0F12, 0x0355 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__16_ 700032D0                              
{0x0F12, 0x0394 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__17_ 700032D2                              
{0x0F12, 0x03CE ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__18_ 700032D4                              
{0x0F12, 0x03FF ,16,0}, // #SARR_usDualGammaLutRGBIndoor_1__19_ 700032D6                              
{0x0F12, 0x0000 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__0_ 700032D8                               
{0x0F12, 0x0046 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__1_ 700032DA                               
{0x0F12, 0x0064 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__2_ 700032DC                               
{0x0F12, 0x008A ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__3_ 700032DE                               
{0x0F12, 0x00BE ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__4_ 700032E0                               
{0x0F12, 0x0118 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__5_ 700032E2                               
{0x0F12, 0x015E ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__6_ 700032E4                               
{0x0F12, 0x017C ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__7_ 700032E6                               
{0x0F12, 0x0194 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__8_ 700032E8                               
{0x0F12, 0x01C0 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__9_ 700032EA                               
{0x0F12, 0x01E7 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__10_ 700032EC                              
{0x0F12, 0x020E ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__11_ 700032EE                              
{0x0F12, 0x0232 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__12_ 700032F0                              
{0x0F12, 0x0273 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__13_ 700032F2                              
{0x0F12, 0x02AF ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__14_ 700032F4                              
{0x0F12, 0x0309 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__15_ 700032F6                              
{0x0F12, 0x0355 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__16_ 700032F8                              
{0x0F12, 0x0394 ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__17_ 700032FA                              
{0x0F12, 0x03CE ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__18_ 700032FC                              
{0x0F12, 0x03FF ,16,0}, // #SARR_usDualGammaLutRGBIndoor_2__19_ 700032FE                              
{0x0F12, 0x0000 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__0_ 70003300// Outdoor gamma              
{0x0F12, 0x0004 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__1_ 70003302                              
{0x0F12, 0x0010 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__2_ 70003304                              
{0x0F12, 0x002A ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__3_ 70003306                              
{0x0F12, 0x0062 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__4_ 70003308                              
{0x0F12, 0x00D5 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__5_ 7000330A                              
{0x0F12, 0x0138 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__6_ 7000330C                              
{0x0F12, 0x0161 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__7_ 7000330E                              
{0x0F12, 0x0186 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__8_ 70003310                              
{0x0F12, 0x01BC ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__9_ 70003312                              
{0x0F12, 0x01E8 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__10_70003314                              
{0x0F12, 0x020F ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__11_70003316                              
{0x0F12, 0x0232 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__12_70003318                              
{0x0F12, 0x0273 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__13_7000331A                              
{0x0F12, 0x02AF ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__14_7000331C                              
{0x0F12, 0x0309 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__15_7000331E                              
{0x0F12, 0x0355 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__16_70003320                              
{0x0F12, 0x0394 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__17_70003322                              
{0x0F12, 0x03CE ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__18_70003324                              
{0x0F12, 0x03FF ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_0__19_70003326                              
{0x0F12, 0x0000 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__0_ 70003328                              
{0x0F12, 0x0004 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__1_ 7000332A                              
{0x0F12, 0x0010 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__2_ 7000332C                              
{0x0F12, 0x002A ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__3_ 7000332E                              
{0x0F12, 0x0062 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__4_ 70003330                              
{0x0F12, 0x00D5 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__5_ 70003332                              
{0x0F12, 0x0138 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__6_ 70003334                              
{0x0F12, 0x0161 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__7_ 70003336                              
{0x0F12, 0x0186 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__8_ 70003338                              
{0x0F12, 0x01BC ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__9_ 7000333A                              
{0x0F12, 0x01E8 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__10_7000333C                              
{0x0F12, 0x020F ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__11_7000333E                              
{0x0F12, 0x0232 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__12_70003340                              
{0x0F12, 0x0273 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__13_70003342                              
{0x0F12, 0x02AF ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__14_70003344                              
{0x0F12, 0x0309 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__15_70003346                              
{0x0F12, 0x0355 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__16_70003348                              
{0x0F12, 0x0394 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__17_7000334A                              
{0x0F12, 0x03CE ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__18_7000334C                              
{0x0F12, 0x03FF ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_1__19_7000334E                              
{0x0F12, 0x0000 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__0_ 70003350                              
{0x0F12, 0x0004 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__1_ 70003352                              
{0x0F12, 0x0010 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__2_ 70003354                              
{0x0F12, 0x002A ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__3_ 70003356                              
{0x0F12, 0x0062 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__4_ 70003358                              
{0x0F12, 0x00D5 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__5_ 7000335A                              
{0x0F12, 0x0138 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__6_ 7000335C                              
{0x0F12, 0x0161 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__7_ 7000335E                              
{0x0F12, 0x0186 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__8_ 70003360                              
{0x0F12, 0x01BC ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__9_ 70003362                              
{0x0F12, 0x01E8 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__10_70003364                              
{0x0F12, 0x020F ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__11_70003366                              
{0x0F12, 0x0232 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__12_70003368                              
{0x0F12, 0x0273 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__13_7000336A                              
{0x0F12, 0x02AF ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__14_7000336C                              
{0x0F12, 0x0309 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__15_7000336E                              
{0x0F12, 0x0355 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__16_70003370                              
{0x0F12, 0x0394 ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__17_70003372                              
{0x0F12, 0x03CE ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__18_70003374                              
{0x0F12, 0x03FF ,16,0}, // #SARR_usDualGammaLutRGBOutdoor_2__19_70003376                              
{0x002A, 0x06A6 ,16,0},
{0x0F12, 0x00CA ,16,0}, // #SARR_AwbCcmCord_0_
{0x0F12, 0x00EA ,16,0}, // #SARR_AwbCcmCord_1_
{0x0F12, 0x0110 ,16,0}, // #SARR_AwbCcmCord_2_
{0x0F12, 0x0124 ,16,0}, // #SARR_AwbCcmCord_3_
{0x0F12, 0x0160 ,16,0}, // #SARR_AwbCcmCord_4_
{0x0F12, 0x0180 ,16,0}, // #SARR_AwbCcmCord_5_
//================================================================================================
// SET AFIT
//================================================================================================
// Noise index
{0x002A, 0x0764 ,16,0},
{0x0F12, 0x0041 ,16,0}, //0049 ,16,0}, //0041 // #afit_uNoiseIndInDoor[0] // 64
{0x0F12, 0x0063 ,16,0}, //005F ,16,0}, //0063 // #afit_uNoiseIndInDoor[1] // 165
{0x0F12, 0x00BB ,16,0}, //0138 ,16,0}, //00BB // #afit_uNoiseIndInDoor[2] // 377
{0x0F12, 0x0193 ,16,0}, //01E0 ,16,0}, //0193 // #afit_uNoiseIndInDoor[3] // 616
{0x0F12, 0x02BC ,16,0}, //0220 ,16,0}, //02BC // #afit_uNoiseIndInDoor[4] // 700
// AFIT table start address // 7000_07C4
{0x002A, 0x0770 ,16,0},
{0x0F12, 0x07C4 ,16,0},
{0x0F12, 0x7000 ,16,0},
// AFIT table (Variables)
{0x002A, 0x07C4 ,16,0},
{0x0F12, 0x0014 ,16,0}, //0014 //0014 //0014 //0014
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0014 ,16,0}, //0014 //0014 //0014 //0014
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x00C4 ,16,0}, //00C4 //00C1 //00C1 //00C1
{0x0F12, 0x03FF ,16,0}, //03FF //03FF //03FF //03FF
{0x0F12, 0x009C ,16,0}, //009C //009C //009C //009C
{0x0F12, 0x017C ,16,0}, //017C //017C //017C //017C
{0x0F12, 0x03FF ,16,0}, //03FF //03FF //03FF //03FF
{0x0F12, 0x000C ,16,0}, //000C //000C //000C //000C
{0x0F12, 0x0010 ,16,0}, //0010 //0010 //0010 //0010
{0x0F12, 0x012C ,16,0}, //012C //012C //012C //012C
{0x0F12, 0x03E8 ,16,0}, //03E8 //03E8 //03E8 //03E8
{0x0F12, 0x0046 ,16,0}, //0046 //0046 //0046 //0046
{0x0F12, 0x005A ,16,0}, //005A //005A //005A //005A
{0x0F12, 0x0070 ,16,0}, //0070 //0070 //0070 //0070
{0x0F12, 0x0019 ,16,0}, //0019 //0028 //0028 //0028
{0x0F12, 0x0019 ,16,0}, //0019 //0028 //0028 //0028
{0x0F12, 0x01AA ,16,0}, //01AA //01AA //01AA //01AA
{0x0F12, 0x0064 ,16,0}, //0064 //0064 //0064 //0064
{0x0F12, 0x0064 ,16,0}, //0064 //0064 //0064 //0064
{0x0F12, 0x000A ,16,0}, //000A //0014 //0014 //0014
{0x0F12, 0x000A ,16,0}, //000A //0014 //0014 //0014
{0x0F12, 0x0032 ,16,0}, //0032 //003C //003C //003C
{0x0F12, 0x0012 ,16,0}, //0012 //0014 //0014 //0014
{0x0F12, 0x002A ,16,0}, //002A //003C //003C //003C
{0x0F12, 0x0024 ,16,0}, //0024 //001E //001E //001E
{0x0F12, 0x002A ,16,0}, //002A //003C //003C //003C
{0x0F12, 0x0024 ,16,0}, //0024 //001E //001E //001E
{0x0F12, 0x0A24 ,16,0}, //0A24 //0A24 //0A24 //0A24
{0x0F12, 0x1701 ,16,0}, //1701 //1701 //1701 //1701
{0x0F12, 0x0229 ,16,0}, //0229 //0229 //0229 //0229
{0x0F12, 0x1403 ,16,0}, //1403 //1403 //1403 //1403
{0x0F12, 0x0000 ,16,0}, //0000 //6464 //6464 //6464
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x00FF ,16,0}, //00FF //00FF //00FF //00FF
{0x0F12, 0x043B ,16,0}, //043B //0A3B //0A3B //0A3B
{0x0F12, 0x1414 ,16,0}, //1414 //1414 //1414 //1414
{0x0F12, 0x0301 ,16,0}, //0301 //0301 //0301 //0301
{0x0F12, 0xFF07 ,16,0}, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x051E ,16,0}, //051E //081E //081E //081E
{0x0F12, 0x0A1E ,16,0}, //0A1E //0A1E //0A1E //0A1E
{0x0F12, 0x0F0F ,16,0}, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x0A3C ,16,0}, //0A3C //0028 //0028 //0028
{0x0F12, 0x0A28 ,16,0}, //0A28 //001E //001E //001E
{0x0F12, 0x0002 ,16,0}, //0002 //0002 //0002 //0002
{0x0F12, 0x00FF ,16,0}, //00FF //00FF //00FF //00FF
{0x0F12, 0x1102 ,16,0}, //1102 //1102 //1102 //1102
{0x0F12, 0x001B ,16,0}, //001B //001B //001B //001B
{0x0F12, 0x0900 ,16,0}, //0900 //0900 //0900 //0900
{0x0F12, 0x0600 ,16,0}, //0600 //0600 //0600 //0600
{0x0F12, 0x0504 ,16,0}, //0504 //0504 //0504 //0504
{0x0F12, 0x0305 ,16,0}, //0305 //0306 //0306 //0306
{0x0F12, 0x1E03 ,16,0}, // 1E03 //1E03 //1E03 //1E03
{0x0F12, 0x0080 ,16,0}, //0080 //0080 //0080 //0078
{0x0F12, 0x0064 ,16,0}, //0064 //0064 //0064 //0F64
{0x0F12, 0x0080 ,16,0}, //0080 //0080 //0080 //0080
{0x0F12, 0x1414 ,16,0}, //1414 //1414 //1414 //1414
{0x0F12, 0x0101 ,16,0}, //0101 //0101 //0101 //0101
{0x0F12, 0x5002 ,16,0}, //5002 //B402 //B402 //B402
{0x0F12, 0x7850 ,16,0}, //7850 //DCB4 //DCB4 //DCB4
{0x0F12, 0x2878 ,16,0}, //2878 //46DC //46DC //46DC
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A0A //0A0A //0A0A
{0x0F12, 0x1403 ,16,0}, //1403 //0003 //0003 //0003
{0x0F12, 0x1E0C ,16,0}, // 1E0C //1E00 //1E00 //1E00
{0x0F12, 0x070A ,16,0}, //070A //0714 //0714 //0714
{0x0F12, 0x32FF ,16,0}, //32FF //50FF //50FF //50FF
{0x0F12, 0x4104 ,16,0}, //4104 //0506 //0506 //0506
{0x0F12, 0x123C ,16,0}, //123C //0F05 //0F05 //0F05
{0x0F12, 0x4012 ,16,0}, //4012 //400F //400F //400F
{0x0F12, 0x0204 ,16,0}, //0204 //0204 //0204 //0204
{0x0F12, 0x1E03 ,16,0}, // 1E03 //1403 //1403 //1403
{0x0F12, 0x011E ,16,0}, //011E //0114 //0114 //0114
{0x0F12, 0x0201 ,16,0}, //0201 //0201 //0201 //0201
{0x0F12, 0x5050 ,16,0}, //5050 //445A //445A //445A
{0x0F12, 0x3C3C ,16,0}, // 3C3C //DCDC //DCDC //DCDC
{0x0F12, 0x0028 ,16,0}, //0028 //0028 //0028 //0028
{0x0F12, 0x030A ,16,0}, //030A //030A //030A //030A
{0x0F12, 0x0714 ,16,0}, //0714 //0000 //0000 //0000
{0x0F12, 0x0A1E ,16,0}, //0A1E //141E //141E //141E
{0x0F12, 0xFF07 ,16,0}, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x0432 ,16,0}, //0432 //0432 //0432 //0432
{0x0F12, 0x4050 ,16,0}, //4050 //0000 //0000 //0000
{0x0F12, 0x0F0F ,16,0}, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0440 ,16,0}, //0440 //0440 //0440 //0440
{0x0F12, 0x0302 ,16,0}, //0302 //0302 //0302 //0302
{0x0F12, 0x1E1E ,16,0}, // 1E1E //1414 //1414 //1414
{0x0F12, 0x0101 ,16,0}, //0101 //0101 //0101 //0101
{0x0F12, 0x5002 ,16,0}, //5002 //4601 //4601 //4601
{0x0F12, 0x3C50 ,16,0}, // 3C50 //6444 //6444 //6444
{0x0F12, 0x283C ,16,0}, //283C //285A //285A //285A
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x1403 ,16,0}, //1403 //0003 //0003 //0003
{0x0F12, 0x1E07 ,16,0}, // 1E07 //1E00 //1E00 //1E00
{0x0F12, 0x070A ,16,0}, //070A //0714 //0714 //0714
{0x0F12, 0x32FF ,16,0}, //32FF //32FF //32FF //32FF
{0x0F12, 0x5004 ,16,0}, //5004 //0004 //0004 //0004
{0x0F12, 0x0F40 ,16,0}, //0F40 //0F00 //0F00 //0F00
{0x0F12, 0x400F ,16,0}, //400F //400F //400F //400F
{0x0F12, 0x0204 ,16,0}, //0204 //0204 //0204 //0204
{0x0F12, 0x0003 ,16,0}, //0003 //0003 //0003 //0003
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0014 ,16,0}, //0014 //0014 //0014 //0014
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x00C4 ,16,0}, //00C4 //00C1 //00C1 //00C1
{0x0F12, 0x03FF ,16,0}, //03FF //03FF //03FF //03FF
{0x0F12, 0x009C ,16,0}, //009C //009C //009C //009C
{0x0F12, 0x017C ,16,0}, //017C //017C //017C //017C
{0x0F12, 0x03FF ,16,0}, //03FF //03FF //03FF //03FF
{0x0F12, 0x000C ,16,0}, //000C //000C //000C //000C
{0x0F12, 0x0010 ,16,0}, //0010 //0010 //0010 //0010
{0x0F12, 0x012C ,16,0}, //012C //012C //012C //012C
{0x0F12, 0x03E8 ,16,0}, //03E8 //03E8 //03E8 //03E8
{0x0F12, 0x0046 ,16,0}, //0046 //0046 //0046 //0046
{0x0F12, 0x005A ,16,0}, //005A //005A //005A //005A
{0x0F12, 0x0070 ,16,0}, //0070 //0070 //0070 //0070
{0x0F12, 0x000F ,16,0}, //000F //0000 //0000 //0000
{0x0F12, 0x000F ,16,0}, //000F //0000 //0000 //0000
{0x0F12, 0x01AA ,16,0}, //01AA //01AA //01AA //01AA
{0x0F12, 0x003C ,16,0}, //003C //0064 //0064 //0064
{0x0F12, 0x003C ,16,0}, //003C //0064 //0064 //0064
{0x0F12, 0x0005 ,16,0}, //0005 //0014 //0014 //0014
{0x0F12, 0x0005 ,16,0}, //0005 //0014 //0014 //0014
{0x0F12, 0x0046 ,16,0}, //0046 //0064 //0064 //0064
{0x0F12, 0x0019 ,16,0}, //0019 //0014 //0014 //0014
{0x0F12, 0x002A ,16,0}, //002A //003C //003C //003C
{0x0F12, 0x0024 ,16,0}, //0024 //001E //001E //001E
{0x0F12, 0x002A ,16,0}, //002A //003C //003C //003C
{0x0F12, 0x0024 ,16,0}, //0024 //001E //001E //001E
{0x0F12, 0x0A24 ,16,0}, //0A24 //0A24 //0A24 //0A24
{0x0F12, 0x1701 ,16,0}, //1701 //1701 //1701 //1701
{0x0F12, 0x0229 ,16,0}, //0229 //0229 //0229 //0229
{0x0F12, 0x1403 ,16,0}, //1403 //1403 //1403 //1403
{0x0F12, 0x0000 ,16,0}, //0000 //6464 //6464 //6464
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x00FF ,16,0}, //00FF //00FF //00FF //00FF
{0x0F12, 0x043B ,16,0}, //043B //023B //023B //023B
{0x0F12, 0x1414 ,16,0}, //1414 //1414 //1414 //1414
{0x0F12, 0x0301 ,16,0}, //0301 //0301 //0301 //0301
{0x0F12, 0xFF07 ,16,0}, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x051E ,16,0}, //051E //081E //081E //081E
{0x0F12, 0x0A1E ,16,0}, //0A1E //0A1E //0A1E //0A1E
{0x0F12, 0x0F0F ,16,0}, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x0A3C ,16,0}, //0A3C //0028 //0028 //0028
{0x0F12, 0x0A28 ,16,0}, //0A28 //0005 //0005 //0005
{0x0F12, 0x0002 ,16,0}, //0002 //0002 //0002 //0002
{0x0F12, 0x00FF ,16,0}, //00FF //00FF //00FF //00FF
{0x0F12, 0x1102 ,16,0}, //1102 //1102 //1102 //1102
{0x0F12, 0x001B ,16,0}, //001B //001B //001B //001B
{0x0F12, 0x0900 ,16,0}, //0900 //0900 //0900 //0900
{0x0F12, 0x0600 ,16,0}, //0600 //0600 //0600 //0600
{0x0F12, 0x0504 ,16,0}, //0504 //0504 //0504 //0504
{0x0F12, 0x0305 ,16,0}, //0305 //0306 //0306 //0306
{0x0F12, 0x4603 ,16,0}, //4603 //4603 //4603 //4603
{0x0F12, 0x0080 ,16,0}, //0080 //0080 //0080 //006E
{0x0F12, 0x0080 ,16,0}, //0080 //0080 //0080 //0F80
{0x0F12, 0x0080 ,16,0}, //0080 //0080 //0080 //0080
{0x0F12, 0x1919 ,16,0}, //1919 //2323 //2323 //2323
{0x0F12, 0x0101 ,16,0}, //0101 //0101 //0101 //0101
{0x0F12, 0x3C02 ,16,0}, // 3C02 //6402 //6402 //6402
{0x0F12, 0x643C ,16,0}, //643C //7864 //7864 //7864
{0x0F12, 0x2864 ,16,0}, //2864 //4678 //4678 //4678
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A0A //0A0A //0A0A
{0x0F12, 0x1403 ,16,0}, //1403 //0003 //0003 //0003
{0x0F12, 0x1E0C ,16,0}, // 1E0C //1E02 //1E02 //1E02
{0x0F12, 0x070A ,16,0}, //070A //0764 //0764 //0764
{0x0F12, 0x32FF ,16,0}, //32FF //50FF //50FF //50FF
{0x0F12, 0x4104 ,16,0}, //4104 //0506 //0506 //0506
{0x0F12, 0x123C ,16,0}, //123C //0F05 //0F05 //0F05
{0x0F12, 0x4012 ,16,0}, //4012 //400F //400F //400F
{0x0F12, 0x0204 ,16,0}, //0204 //0204 //0204 //0204
{0x0F12, 0x1E03 ,16,0}, // 1E03 //1E03 //1E03 //1E03
{0x0F12, 0x011E ,16,0}, //011E //011E //011E //011E
{0x0F12, 0x0201 ,16,0}, //0201 //0201 //0201 //0201
{0x0F12, 0x3232 ,16,0}, //3232 //3A3C //3A3C //3A3C
{0x0F12, 0x3C3C ,16,0}, // 3C3C //4E50 //4E50 //4E50
{0x0F12, 0x0028 ,16,0}, //0028 //0028 //0028 //0028
{0x0F12, 0x030A ,16,0}, //030A //030A //030A //030A
{0x0F12, 0x0714 ,16,0}, //0714 //0000 //0000 //0000
{0x0F12, 0x0A1E ,16,0}, //0A1E //141E //141E //141E
{0x0F12, 0xFF07 ,16,0}, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x0432 ,16,0}, //0432 //0432 //0432 //0432
{0x0F12, 0x4050 ,16,0}, //4050 //0000 //0000 //0000
{0x0F12, 0x0F0F ,16,0}, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0440 ,16,0}, //0440 //0440 //0440 //0440
{0x0F12, 0x0302 ,16,0}, //0302 //0302 //0302 //0302
{0x0F12, 0x1E1E ,16,0}, // 1E1E //1E1E //1E1E //1E1E
{0x0F12, 0x0101 ,16,0}, //0101 //0101 //0101 //0101
{0x0F12, 0x3202 ,16,0}, //3202 //3C01 //3C01 //3C01
{0x0F12, 0x3C32 ,16,0}, // 3C32 //503A //503A //503A
{0x0F12, 0x283C ,16,0}, //283C //284E //284E //284E
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x1403 ,16,0}, //1403 //0003 //0003 //0003
{0x0F12, 0x1E07 ,16,0}, // 1E07 //1E00 //1E00 //1E00
{0x0F12, 0x070A ,16,0}, //070A //0714 //0714 //0714
{0x0F12, 0x32FF ,16,0}, //32FF //32FF //32FF //32FF
{0x0F12, 0x5004 ,16,0}, //5004 //0004 //0004 //0004
{0x0F12, 0x0F40 ,16,0}, //0F40 //0F00 //0F00 //0F00
{0x0F12, 0x400F ,16,0}, //400F //400F //400F //400F
{0x0F12, 0x0204 ,16,0}, //0204 //0204 //0204 //0204
{0x0F12, 0x0003 ,16,0}, //0003 //0003 //0003 //0003
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x00C4 ,16,0}, //00C4 //00C1 //00C1 //00C1
{0x0F12, 0x03FF ,16,0}, //03FF //03FF //03FF //03FF
{0x0F12, 0x009C ,16,0}, //009C //009C //009C //009C
{0x0F12, 0x017C ,16,0}, //017C //017C //017C //017C
{0x0F12, 0x03FF ,16,0}, //03FF //03FF //03FF //03FF
{0x0F12, 0x000C ,16,0}, //000C //000C //000C //000C
{0x0F12, 0x0010 ,16,0}, //0010 //0010 //0010 //0010
{0x0F12, 0x012C ,16,0}, //012C //012C //012C //012C
{0x0F12, 0x03E8 ,16,0}, //03E8 //03E8 //03E8 //03E8
{0x0F12, 0x0046 ,16,0}, //0046 //0046 //0046 //0046
{0x0F12, 0x0078 ,16,0}, //0078 //005A //005A //005A
{0x0F12, 0x0070 ,16,0}, //0070 //0070 //0070 //0070
{0x0F12, 0x0004 ,16,0}, //0004 //0000 //0000 //0000
{0x0F12, 0x0004 ,16,0}, //0004 //0000 //0000 //0000
{0x0F12, 0x01AA ,16,0}, //01AA //01AA //01AA //01AA
{0x0F12, 0x001E ,16,0}, //001E //0032 //0032 //0032
{0x0F12, 0x001E ,16,0}, //001E //0032 //0032 //0032
{0x0F12, 0x0002 ,16,0}, //0002 //0002 //0002 //0002
{0x0F12, 0x0002 ,16,0}, //0002 //0002 //0002 //0002
{0x0F12, 0x0064 ,16,0}, //0064 //00C8 //00C8 //00C8
{0x0F12, 0x003C ,16,0}, //001B //0014 //0014 //0014
{0x0F12, 0x002A ,16,0}, //002A //003C //003C //003C
{0x0F12, 0x0024 ,16,0}, //0024 //001E //001E //001E
{0x0F12, 0x002A ,16,0}, //002A //003C //003C //003C
{0x0F12, 0x0024 ,16,0}, //0024 //001E //001E //001E
{0x0F12, 0x0A24 ,16,0}, //0A24 //0A24 //0A24 //0A24
{0x0F12, 0x1701 ,16,0}, //1701 //1701 //1701 //1701
{0x0F12, 0x0229 ,16,0}, //0229 //0229 //0229 //0229
{0x0F12, 0x1403 ,16,0}, //1403 //1403 //1403 //1403
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x00FF ,16,0}, //00FF //00FF //00FF //00FF
{0x0F12, 0x043B ,16,0}, //043B //023B //023B //023B
{0x0F12, 0x1414 ,16,0}, //1414 //1414 //1414 //1414
{0x0F12, 0x0301 ,16,0}, //0301 //0301 //0301 //0301
{0x0F12, 0xFF07 ,16,0}, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x051E ,16,0}, //051E //081E //081E //081E
{0x0F12, 0x0A1E ,16,0}, //0A1E //0A1E //0A1E //0A1E
{0x0F12, 0x0F0F ,16,0}, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x0A3C ,16,0}, //0A3C //0028 //0028 //0028
{0x0F12, 0x0D2E ,16,0}, //0528 //0528 //0005 //0005 //0005
{0x0F12, 0x0002 ,16,0}, //0002 //0001 //0001 //0001
{0x0F12, 0x00FF ,16,0}, //00FF //00FF //00FF //00FF
{0x0F12, 0x1102 ,16,0}, //1102 //1102 //1102 //1102
{0x0F12, 0x001B ,16,0}, //001B //001B //001B //001B
{0x0F12, 0x0900 ,16,0}, //0900 //0900 //0900 //0900
{0x0F12, 0x0600 ,16,0}, //0600 //0600 //0600 //0600
{0x0F12, 0x0504 ,16,0}, //0504 //0504 //0504 //0504
{0x0F12, 0x0305 ,16,0}, //0305 //0306 //0306 //0306
{0x0F12, 0x4602 ,16,0}, //4602 //4602 //4602 //4602
{0x0F12, 0x2880 ,16,0}, //2880 //2880 //0080 //0080
{0x0F12, 0x0080 ,16,0}, //0080 //0080 //0080 //0080
{0x0F12, 0x0080 ,16,0}, //0080 //0080 //0080 //0080
{0x0F12, 0x2323 ,16,0}, //2323 //3C3C //3C3C //3C3C
{0x0F12, 0x0101 ,16,0}, //0101 //0101 //0101 //0101
{0x0F12, 0x2A02 ,16,0}, // 2A02 //1E02 //1E02 //1E02
{0x0F12, 0x3C2A ,16,0}, // 3C2A //2428 //2428 //2428
{0x0F12, 0x283C ,16,0}, //283C //462D //462D //462D
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A0A //0A0A //0A0A
{0x0F12, 0x1403 ,16,0}, //1403 //2303 //2303 //2303
{0x0F12, 0x1E0C ,16,0}, // 1E0C //1402 //1402 //1402
{0x0F12, 0x070A ,16,0}, //070A //08C8 //08C8 //08C8
{0x0F12, 0x32FF ,16,0}, //32FF //1464 //1464 //1464
{0x0F12, 0x6E04 ,16,0}, //6E04 //B402 //B402 //B402
{0x0F12, 0x0F96 ,16,0}, //0F48 //2514 //2514 //2514
{0x0F12, 0x400F ,16,0}, //400F //4009 //4009 //4009
{0x0F12, 0x0204 ,16,0}, //0204 //0204 //0204 //0204
{0x0F12, 0x2303 ,16,0}, //2303 //2803 //2803 //2803
{0x0F12, 0x0123 ,16,0}, //0123 //0128 //0128 //0128
{0x0F12, 0x0201 ,16,0}, //0201 //0201 //0201 //0201
{0x0F12, 0x262A ,16,0}, //262A //2224 //2224 //2224
{0x0F12, 0x2C2C ,16,0}, // 2C2C //282C //282C //282C
{0x0F12, 0x0028 ,16,0}, //0028 //0028 //0028 //0028
{0x0F12, 0x030A ,16,0}, //030A //030A //030A //030A
{0x0F12, 0x0714 ,16,0}, //0714 //0410 //0410 //0410
{0x0F12, 0x0A1E ,16,0}, //0A1E //141E //141E //141E
{0x0F12, 0xFF07 ,16,0}, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x0432 ,16,0}, //0432 //0432 //0432 //0432
{0x0F12, 0x4050 ,16,0}, //4050 //4050 //4050 //4050
{0x0F12, 0x0F0F ,16,0}, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0440 ,16,0}, //0440 //0440 //0440 //0440
{0x0F12, 0x0302 ,16,0}, //0302 //0302 //0302 //0302
{0x0F12, 0x2323 ,16,0}, //2323 //2828 //2828 //2828
{0x0F12, 0x0101 ,16,0}, //0101 //0101 //0101 //0101
{0x0F12, 0x2A02 ,16,0}, // 2A02 //2401 //2401 //2401
{0x0F12, 0x2C26 ,16,0}, // 2C26 //2C22 //2C22 //2C22
{0x0F12, 0x282C ,16,0}, //282C //2828 //2828 //2828
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x1403 ,16,0}, //1403 //1003 //1003 //1003
{0x0F12, 0x1E07 ,16,0}, // 1E07 //1E04 //1E04 //1E04
{0x0F12, 0x070A ,16,0}, //070A //0714 //0714 //0714
{0x0F12, 0x32FF ,16,0}, //32FF //32FF //32FF //32FF
{0x0F12, 0x5004 ,16,0}, //5004 //5004 //5004 //5004
{0x0F12, 0x0F40 ,16,0}, //0F40 //0F40 //0F40 //0F40
{0x0F12, 0x400F ,16,0}, //400F //400F //400F //400F
{0x0F12, 0x0204 ,16,0}, //0204 //0204 //0204 //0204
{0x0F12, 0x0003 ,16,0}, //0003 //0003 //0003 //0003
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x00C4 ,16,0}, //00C4 //00C1 //00C1 //00C1
{0x0F12, 0x03FF ,16,0}, //03FF //03FF //03FF //03FF
{0x0F12, 0x009C ,16,0}, //009C //009C //009C //009C
{0x0F12, 0x017C ,16,0}, //017C //017C //017C //017C
{0x0F12, 0x03FF ,16,0}, //03FF //03FF //03FF //03FF
{0x0F12, 0x000C ,16,0}, //000C //000C //000C //000C
{0x0F12, 0x0010 ,16,0}, //0010 //0010 //0010 //0010
{0x0F12, 0x00C8 ,16,0}, //00C8 //00C8 //00C8 //00C8
{0x0F12, 0x03E8 ,16,0}, //03E8 //03E8 //03E8 //03E8
{0x0F12, 0x0046 ,16,0}, //0046 //0046 //0046 //0046
{0x0F12, 0x0082 ,16,0}, //0082 //0050 //0050 //0050
{0x0F12, 0x0070 ,16,0}, //0070 //0070 //0070 //0070
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x01AA ,16,0}, //01AA //01AA //01AA //01AA
{0x0F12, 0x001E ,16,0}, //001E //0032 //0032 //0032
{0x0F12, 0x001E ,16,0}, //001E //0032 //0032 //0032
{0x0F12, 0x0002 ,16,0}, //0002 //0002 //0002 //0002
{0x0F12, 0x0002 ,16,0}, //0002 //0002 //0002 //0002
{0x0F12, 0x010E ,16,0}, //010E //00C8 //00C8 //00C8
{0x0F12, 0x003C ,16,0}, //0028 //0014 //0014 //0014
{0x0F12, 0x0032 ,16,0}, //0032 //002D //002D //002D
{0x0F12, 0x0028 ,16,0}, //0028 //0019 //0019 //0019
{0x0F12, 0x0032 ,16,0}, //0032 //002D //002D //002D
{0x0F12, 0x0028 ,16,0}, //0028 //0019 //0019 //0019
{0x0F12, 0x0A24 ,16,0}, //0A24 //0A24 //0A24 //0A24
{0x0F12, 0x1701 ,16,0}, //1701 //1701 //1701 //1701
{0x0F12, 0x0229 ,16,0}, //0229 //0229 //0229 //0229
{0x0F12, 0x1403 ,16,0}, //1403 //1403 //1403 //1403
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x00FF ,16,0}, //00FF //00FF //00FF //00FF
{0x0F12, 0x043B ,16,0}, //043B //023B //023B //023B
{0x0F12, 0x1414 ,16,0}, //1414 //1414 //1414 //1414
{0x0F12, 0x0301 ,16,0}, //0301 //0301 //0301 //0301
{0x0F12, 0xFF07 ,16,0}, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x051E ,16,0}, //051E //081E //081E //081E
{0x0F12, 0x0A1E ,16,0}, //0A1E //0A1E //0A1E //0A1E
{0x0F12, 0x0F0F ,16,0}, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x0A3C ,16,0}, //0A3C //0028 //0028 //0028
{0x0F12, 0x173E ,16,0}, //0532 //0532 //0005 //0005 //0005
{0x0F12, 0x0002 ,16,0}, //0002 //0001 //0001 //0001
{0x0F12, 0x00FF ,16,0}, //00FF //00FF //00FF //00FF
{0x0F12, 0x1002 ,16,0}, //1002 //1002 //1002 //1002
{0x0F12, 0x001E ,16,0}, //001E //001E //001E //001E
{0x0F12, 0x0900 ,16,0}, //0900 //0900 //0900 //0900
{0x0F12, 0x0600 ,16,0}, //0600 //0600 //0600 //0600
{0x0F12, 0x0504 ,16,0}, //0504 //0504 //0504 //0504
{0x0F12, 0x0305 ,16,0}, //0305 //0307 //0307 //0307
{0x0F12, 0x5002 ,16,0}, //5002 //5002 //5002 //5002
{0x0F12, 0x2880 ,16,0}, //2880 //2880 //0080 //0080
{0x0F12, 0x0080 ,16,0}, //0080 //0080 //0080 //0080
{0x0F12, 0x0080 ,16,0}, //0080 //0080 //0080 //0080
{0x0F12, 0x2328 ,16,0}, //2328 //4646 //4646 //4646
{0x0F12, 0x0101 ,16,0}, //0101 //0101 //0101 //0101
{0x0F12, 0x2A02 ,16,0}, // 2A02 //1E02 //1E02 //1E02
{0x0F12, 0x2228 ,16,0}, //2228 //1D28 //1D28 //1D28
{0x0F12, 0x2822 ,16,0}, //2822 //321D //321D //321D
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A0A //0A0A //0A0A
{0x0F12, 0x1903 ,16,0}, //1903 //2303 //2303 //2303
{0x0F12, 0x1E0F ,16,0}, // 1E0F //1402 //1402 //1402
{0x0F12, 0x070A ,16,0}, //070A //08B4 //08B4 //08B4
{0x0F12, 0x32FF ,16,0}, //32FF //1464 //1464 //1464
{0x0F12, 0xAA04 ,16,0}, //AA04 //B402 //B402 //B402
{0x0F12, 0x0F96 ,16,0}, //0F5A //2514 //2514 //2514
{0x0F12, 0x400F ,16,0}, //400F //4009 //4009 //4009
{0x0F12, 0x0504 ,16,0}, //0504 //0204 //0204 //0204
{0x0F12, 0x2805 ,16,0}, //2805 //3C03 //3C03 //3C03
{0x0F12, 0x0123 ,16,0}, //0123 //013C //013C //013C
{0x0F12, 0x0201 ,16,0}, //0201 //0201 //0201 //0201
{0x0F12, 0x2024 ,16,0}, //2024 //1C1E //1C1E //1C1E
{0x0F12, 0x1C1C ,16,0}, // 1C1C //1418 //1418 //1418
{0x0F12, 0x0028 ,16,0}, //0028 //0028 //0028 //0028
{0x0F12, 0x030A ,16,0}, //030A //030A //030A //030A
{0x0F12, 0x0A0A ,16,0}, //0A0A //0214 //0214 //0214
{0x0F12, 0x0A2D ,16,0}, //0A2D //0E14 //0E14 //0E14
{0x0F12, 0xFF07 ,16,0}, //FF07 //FF06 //FF06 //FF06
{0x0F12, 0x0432 ,16,0}, //0432 //0432 //0432 //0432
{0x0F12, 0x4050 ,16,0}, //4050 //4052 //4052 //4052
{0x0F12, 0x0F0F ,16,0}, //0F0F //150C //150C //150C
{0x0F12, 0x0440 ,16,0}, //0440 //0440 //0440 //0440
{0x0F12, 0x0302 ,16,0}, //0302 //0302 //0302 //0302
{0x0F12, 0x2328 ,16,0}, //2328 //3C3C //3C3C //3C3C
{0x0F12, 0x0101 ,16,0}, //0101 //0101 //0101 //0101
{0x0F12, 0x3C02 ,16,0}, // 3C02 //1E01 //1E01 //1E01
{0x0F12, 0x1C3C ,16,0}, // 1C3C //181C //181C //181C
{0x0F12, 0x281C ,16,0}, //281C //2814 //2814 //2814
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x0A03 ,16,0}, //0A03 //1403 //1403 //1403
{0x0F12, 0x2D0A ,16,0}, // 2D0A //1402 //1402 //1402
{0x0F12, 0x070A ,16,0}, //070A //060E //060E //060E
{0x0F12, 0x32FF ,16,0}, //32FF //32FF //32FF //32FF
{0x0F12, 0x5004 ,16,0}, //5004 //5204 //5204 //5204
{0x0F12, 0x0F40 ,16,0}, //0F40 //0C40 //0C40 //0C40
{0x0F12, 0x400F ,16,0}, //400F //4015 //4015 //4015
{0x0F12, 0x0204 ,16,0}, //0204 //0204 //0204 //0204
{0x0F12, 0x0003 ,16,0}, //0003 //0003 //0003 //0003
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x00C4 ,16,0}, //00C4 //00C1 //00C1 //00C1
{0x0F12, 0x03FF ,16,0}, //03FF //03FF //03FF //03FF
{0x0F12, 0x009C ,16,0}, //009C //009C //009C //009C
{0x0F12, 0x017C ,16,0}, //017C //017C //017C //017C
{0x0F12, 0x03FF ,16,0}, //03FF //03FF //03FF //03FF
{0x0F12, 0x000C ,16,0}, //000C //000C //000C //000C
{0x0F12, 0x0010 ,16,0}, //0010 //0010 //0010 //0010
{0x0F12, 0x00C8 ,16,0}, //00C8 //0032 //0032 //0032
{0x0F12, 0x028A ,16,0}, //028A //028A //028A //028A
{0x0F12, 0x0046 ,16,0}, //0046 //0032 //0032 //0032
{0x0F12, 0x015E ,16,0}, //015E //01F4 //01F4 //01F4
{0x0F12, 0x0070 ,16,0}, //0070 //0070 //0070 //0070
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x01AA ,16,0}, //01AA //01AA //01AA //01AA
{0x0F12, 0x0014 ,16,0}, //0014 //003C //003C //003C
{0x0F12, 0x0014 ,16,0}, //0014 //0050 //0050 //0050
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x0140 ,16,0}, //0140 //00B4 //00B4 //00B4
{0x0F12, 0x003C ,16,0}, //003C //0014 //0014 //0014
{0x0F12, 0x0032 ,16,0}, //0032 //0046 //0046 //0046
{0x0F12, 0x0023 ,16,0}, //0023 //0019 //0019 //0019
{0x0F12, 0x0023 ,16,0}, //0023 //0046 //0046 //0046
{0x0F12, 0x0032 ,16,0}, //0032 //0019 //0019 //0019
{0x0F12, 0x0A24 ,16,0}, //0A24 //0A24 //0A24 //0A24
{0x0F12, 0x1701 ,16,0}, //1701 //1701 //1701 //1701
{0x0F12, 0x0229 ,16,0}, //0229 //0229 //0229 //0229
{0x0F12, 0x1403 ,16,0}, //1403 //0503 //0503 //0503
{0x0F12, 0x0000 ,16,0}, //0000 //080F //080F //080F
{0x0F12, 0x0000 ,16,0}, //0000 //0808 //0808 //0808
{0x0F12, 0x0000 ,16,0}, //0000 //0000 //0000 //0000
{0x0F12, 0x00FF ,16,0}, //00FF //00FF //00FF //00FF
{0x0F12, 0x043B ,16,0}, //043B //022D //022D //022D
{0x0F12, 0x1414 ,16,0}, //1414 //1414 //1414 //1414
{0x0F12, 0x0301 ,16,0}, //0301 //0301 //0301 //0301
{0x0F12, 0xFF07 ,16,0}, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x051E ,16,0}, //051E //061E //061E //061E
{0x0F12, 0x0A1E ,16,0}, //0A1E //0A1E //0A1E //0A1E
{0x0F12, 0x0606 ,16,0}, //0606 //0606 //0606 //0606
{0x0F12, 0x0A01 ,16,0}, //0A01 //0A01 //0A01 //0A01
{0x0F12, 0x143C ,16,0}, //143C //0028 //0028 //0028
{0x0F12, 0x203E ,16,0}, //0532 //0532 //0002 //0002 //0002
{0x0F12, 0x0002 ,16,0}, //0002 //0001 //0001 //0001
{0x0F12, 0x00FF ,16,0}, //00FF //00FF //00FF //00FF
{0x0F12, 0x1002 ,16,0}, //1002 //1002 //1002 //1002
{0x0F12, 0x001E ,16,0}, //001E //001E //001E //001E
{0x0F12, 0x0900 ,16,0}, //0900 //0900 //0900 //0900
{0x0F12, 0x0600 ,16,0}, //0600 //0600 //0600 //0600
{0x0F12, 0x0504 ,16,0}, //0504 //0504 //0504 //0504
{0x0F12, 0x0305 ,16,0}, //0305 //0307 //0307 //0307
{0x0F12, 0x5001 ,16,0}, //5001 //5001 //5001 //5001
{0x0F12, 0x2880 ,16,0}, //2880 //2880 //0080 //0080
{0x0F12, 0x0080 ,16,0}, //0080 //0080 //0080 //0080
{0x0F12, 0x0080 ,16,0}, //0080 //0080 //0080 //0080
{0x0F12, 0x5050 ,16,0}, //5050 //5050 //5050 //5050
{0x0F12, 0x0101 ,16,0}, //0101 //0101 //0101 //0101
{0x0F12, 0x1C02 ,16,0}, // 1C02 //1E02 //1E02 //1E02
{0x0F12, 0x191C ,16,0}, //191C //1219 //1219 //1219
{0x0F12, 0x2819 ,16,0}, //2819 //320E //320E //320E
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A0A //0A0A //0A0A
{0x0F12, 0x1E03 ,16,0}, // 1E03 //2504 //2504 //2504
{0x0F12, 0x1E0F ,16,0}, // 1E0F //0A08 //0A08 //0A08
{0x0F12, 0x0508 ,16,0}, //0508 //0832 //0832 //0832
{0x0F12, 0x32FF ,16,0}, //32FF //1432 //1432 //1432
{0x0F12, 0xBE04 ,16,0}, //BE04 //A001 //A001 //A001
{0x0F12, 0x1496 ,16,0}, //146E //250A //250A //250A
{0x0F12, 0x4015 ,16,0}, //4015 //4005 //4005 //4005
{0x0F12, 0x0604 ,16,0}, //0604 //0604 //0604 //0604
{0x0F12, 0x5006 ,16,0}, //5006 //4606 //4606 //4606
{0x0F12, 0x0150 ,16,0}, //0150 //0146 //0146 //0146
{0x0F12, 0x0201 ,16,0}, //0201 //0201 //0201 //0201
{0x0F12, 0x1E1E ,16,0}, // 1E1E //1C18 //1C18 //1C18
{0x0F12, 0x1212 ,16,0}, //1212 //0E0F //0E0F //0E0F
{0x0F12, 0x0028 ,16,0}, //0028 //0028 //0028 //0028
{0x0F12, 0x030A ,16,0}, //030A //030A //030A //030A
{0x0F12, 0x0A10 ,16,0}, //0A10 //0514 //0514 //0514
{0x0F12, 0x0819 ,16,0}, //0819 //0C14 //0C14 //0C14
{0x0F12, 0xFF05 ,16,0}, //FF05 //FF05 //FF05 //FF05
{0x0F12, 0x0432 ,16,0}, //0432 //0432 //0432 //0432
{0x0F12, 0x4052 ,16,0}, //4052 //4052 //4052 //4052
{0x0F12, 0x1514 ,16,0}, //1514 //1514 //1514 //1514
{0x0F12, 0x0440 ,16,0}, //0440 //0440 //0440 //0440
{0x0F12, 0x0302 ,16,0}, //0302 //0302 //0302 //0302
{0x0F12, 0x5050 ,16,0}, //5050 //4646 //4646 //4646
{0x0F12, 0x0101 ,16,0}, //0101 //0101 //0101 //0101
{0x0F12, 0x1E02 ,16,0}, // 1E02 //1801 //1801 //1801
{0x0F12, 0x121E ,16,0}, //121E //0F1C //0F1C //0F1C
{0x0F12, 0x2812 ,16,0}, //2812 //280E //280E //280E
{0x0F12, 0x0A00 ,16,0}, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x1003 ,16,0}, //1003 //1403 //1403 //1403
{0x0F12, 0x190A ,16,0}, //190A //1405 //1405 //1405
{0x0F12, 0x0508 ,16,0}, //0508 //050C //050C //050C
{0x0F12, 0x32FF ,16,0}, //32FF //32FF //32FF //32FF
{0x0F12, 0x5204 ,16,0}, //5204 //5204 //5204 //5204
{0x0F12, 0x1440 ,16,0}, //1440 //1440 //1440 //1440
{0x0F12, 0x4015 ,16,0}, //4015 //4015 //4015 //4015
{0x0F12, 0x0204 ,16,0}, //0204 //0204 //0204 //0204
{0x0F12, 0x0003 ,16,0}, //0003 //0003 //0003 //0003
// AFIT table (Constants)
{0x0F12, 0x7F7A ,16,0}, //7FFA // #afit_pConstBaseVals[0]
{0x0F12, 0x7FBD ,16,0}, //FFBD // #afit_pConstBaseVals[1]
{0x0F12, 0xBEFC ,16,0}, //26FE // #afit_pConstBaseVals[2]
{0x0F12, 0xF7BC ,16,0}, //F7BC // #afit_pConstBaseVals[3]
{0x0F12, 0x7E06 ,16,0}, //7E06 // #afit_pConstBaseVals[4]
{0x0F12, 0x0053 ,16,0}, //00D3 // #afit_pConstBaseVals[5]
// Update Changed Registers
{0x002A, 0x0664 ,16,0},
{0x0F12, 0x013E ,16,0}, //013E //seti_uContrastCenter

//WRITE 700004D6 0001 // #REG_TC_DBG_ReInitCmd

//============================================================
// ISP-FE Setting END
//============================================================
              
//================================================================================================
// SET PLL    
//================================================================================================
// How to set 
// 1. MCLK    
// 2. System CLK
// 3. PCLK    
//================================================================================================
// Set input CLK // 24MHz
              
{0x002A, 0x01CC ,16,0},
{0x0F12, 0x5DC0 ,16,0}, // #REG_TC_IPRM_InClockLSBs
{0x0F12, 0x0000 ,16,0}, // #REG_TC_IPRM_InClockMSBs
{0x002A, 0x01EE ,16,0},
{0x0F12, 0x0000 ,16,0}, // #REG_TC_IPRM_UseNPviClocks // Number of PLL setting
// Set system CLK // 58MHz
{0x0F12, 0x0001 ,16,1},  //#REG_TC_IPRM_UseNMiPiClocks  // Number of PLL setting                                     
{0x0F12, 0x0001 ,16,1},  //#REG_TC_IPRM_NumberOfMipiLanes      // Number of MIPI Lane  
{0x002A, 0x01F6 ,16,0},
{0x0F12, 0x38A4 ,16,0}, //1D4C //50M 1D4C // #REG_TC_IPRM_OpClk4KHz_0
// Set pixel CLK // 48MHz (0x3A98)
{0x0F12, 0x2ED0 ,16,0}, // #REG_TC_IPRM_MinOutRate4KHz_0
{0x0F12, 0x2EF0 ,16,0}, // #REG_TC_IPRM_MaxOutRate4KHz_0

// Set system CLK // 30MHz
{0x0F12, 0x1D4C ,16,0}, //1D4C //50M 1D4C // #REG_TC_IPRM_OpClk4KHz_1
// Set pixel CLK // 48MHz (0x3A98)
{0x0F12, 0x2ED0 ,16,0}, // #REG_TC_IPRM_MinOutRate4KHz_1
{0x0F12, 0x2EF0 ,16,0}, // #REG_TC_IPRM_MaxOutRate4KHz_1

// Update PLL 
{0x002A, 0x0208 ,16,0},
{0x0F12, 0x0001 ,16,0}, // #REG_TC_IPRM_InitParamsUpdated
              
//============================================================
// Frame rate setting
//============================================================
// How to set 
// 1. Exposure value
// dec2hex((1 / (frame rate you want(ms))) * 100d * 4d)
// 2. Analog Digital gain
// dec2hex((Analog gain you want) * 256d)
//============================================================
// Set preview exposure time
{0x002A, 0x0530 ,16,0},
{0x0F12, 0x3A98 ,16,0}, // #lt_uMaxExp1    30ms
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0x7EF4 ,16,0}, // #lt_uMaxExp2    65ms
{0x0F12, 0x0000 ,16,0},
{0x002A, 0x167C ,16,0},
{0x0F12, 0x9C40 ,16,0}, // #evt1_lt_uMaxExp3  80ms
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0xF424 ,16,0}, // #evt1_lt_uMaxExp4  125ms
{0x0F12, 0x0000 ,16,0},
              
// Set capture, exposure time
{0x002A, 0x0538 ,16,0},
{0x0F12, 0x9C40 ,16,0}, // #lt_uCapMaxExp1   30ms
{0x0F12, 0x0000 ,16,0},
{0x0F12, 0xD055 ,16,0}, // #lt_uCapMaxExp2      65ms
{0x0F12, 0x0000 ,16,0},
{0x002A, 0x1684 ,16,0},
{0x0F12, 0x0360 ,16,0}, // #evt1_lt_uCapMaxExp3 80ms
{0x0F12, 0x0001 ,16,0},
{0x0F12, 0x3880 ,16,0}, // #evt1_lt_uCapMaxExp4 125ms
{0x0F12, 0x0001 ,16,0},

// Set gain   
{0x002A, 0x0540 ,16,0},
{0x0F12, 0x0170 ,16,0}, //0320 // #lt_uMaxAnGain1
{0x0F12, 0x0250 ,16,0}, //0380 // #lt_uMaxAnGain2
{0x002A, 0x168C ,16,0},
{0x0F12, 0x0380 ,16,0}, //0500 // #evt1_lt_uMaxAnGain3
{0x0F12, 0x0800 ,16,0}, //0800 // #evt1_lt_uMaxAnGain4
              
{0x002A, 0x0544 ,16,0},
{0x0F12, 0x0100 ,16,0}, // #lt_uMaxDigGain
{0x0F12, 0x0800 ,16,0}, // #lt_uMaxTotGain

{0x002A, 0x1694 ,16,0},
{0x0F12, 0x0001 ,16,0}, // #evt1_senHal_bExpandForbid

{0x002A, 0x051A ,16,0},
{0x0F12, 0x0111 ,16,0}, // #lt_uLimitHigh
{0x0F12, 0x00F0 ,16,0}, // #lt_uLimitLow
              
{0x002A, 0x0572 ,16,0},
{0x0F12, 0x0007 ,16,0}, //#skl_usConfigStbySettings // Enable T&P code after HW stby + skip ZI part on HW wakeup.
               
//================================================================================================
// SET PREVIEW CONFIGURATION_0
// # Foramt : YUV422
// # Size: QXGA
// # FPS : 30fps
//================================================================================================
{0x002A, 0x026C ,16,0},
{0x0F12, 0x0280 ,16,0}, //#REG_0TC_PCFG_usWidth//640
{0x0F12, 0x01E0 ,16,0}, //#REG_0TC_PCFG_usHeight //480    026E
{0x0F12, 0x0005 ,16,0}, //#REG_0TC_PCFG_Format            0270
{0x0F12, 0x2EF0 ,16,0}, //#REG_0TC_PCFG_usMaxOut4KHzRate  0272
{0x0F12, 0x2ED0 ,16,0}, //#REG_0TC_PCFG_usMinOut4KHzRate  0274
{0x0F12, 0x0100 ,16,0}, //#REG_0TC_PCFG_OutClkPerPix88    0276
{0x0F12, 0x0800 ,16,0}, //#REG_0TC_PCFG_uMaxBpp88         027
{0x0F12, 0x0052 ,16,0}, //#REG_0TC_PCFG_PVIMask //s0050 = FALSE in MSM6290 : s0052 = TRUE in MSM6800 //reg 027A
{0x002A, 0x027E ,16,0},
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_usJpegPacketSize
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_usJpegTotalPackets
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_uClockInd
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_usFrTimeType
{0x0F12, 0x0001 ,16,0}, //#REG_0TC_PCFG_FrRateQualityType
{0x0F12, 0x0535 ,16,0}, //#REG_0TC_PCFG_usMaxFrTimeMsecMult10 //7.5fps
{0x0F12, 0x014E ,16,0}, //029a //#REG_0TC_PCFG_usMinFrTimeMsecMult10 //25fps
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_bSmearOutput
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_sSaturation
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_sSharpBlur
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_sColorTemp
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_uDeviceGammaIndex
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_uPrevMirror
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_uCaptureMirror
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_uRotation
 //================================================================================================
// SET PREVIEW CONFIGURATION_1
// # Foramt : YUV422
// # Size: QXGA
// # FPS : 5fps~30fps
//================================================================================================
{0x0F12, 0x0280 ,16,0}, //REG_PrevConfigControls_1_
{0x0F12, 0x01E0 ,16,0}, //REG_1TC_PCFG_usHeight
{0x0F12, 0x0005 ,16,0}, //REG_1TC_PCFG_Format
{0x0F12, 0x2EF0 ,16,0}, //#REG_0TC_PCFG_usMaxOut4KHzRate  0272
{0x0F12, 0x2ED0 ,16,0}, //#REG_0TC_PCFG_usMinOut4KHzRate  0274
{0x0F12, 0x0100 ,16,0}, //REG_1TC_PCFG_OutClkPerPix884BC4
{0x0F12, 0x0800 ,16,0}, //REG_1TC_PCFG_uMaxBpp88
{0x0F12, 0x0052 ,16,0}, //REG_1TC_PCFG_PVIMask
{0x0F12, 0x0000 ,16,0}, //REG_1TC_PCFG_OIFMask
{0x002A, 0x02B2 ,16,0},
{0x0F12, 0x0000 ,16,0}, //REG_1TC_PCFG_uClockInd
{0x0F12, 0x0000 ,16,0}, //REG_1TC_PCFG_usFrTimeType
{0x0F12, 0x0002 ,16,0}, //REG_1TC_PCFG_FrRateQualityType
{0x0F12, 0x0535 ,16,0}, //REG_0TC_PCFG_usMaxFrTimeMsecMult10  //7.5fps 
{0x0F12, 0x029A ,16,0}, //REG_0TC_PCFG_usMinFrTimeMsecMult10  //15fps   
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_bSmearOutput
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_sSaturation
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_sSharpBlur
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_sColorTemp
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_uDeviceGammaIndex
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_uPrevMirror
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_uCaptureMirror
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_PCFG_uRotation
//================================================================================================
// SET PREVIEW CONFIGURATION_2 (Night Mode)
// # Foramt : YUV422
// # Size: QXGA
// # FPS : 4fps~15fps
//================================================================================================
{0x002A, 0x02CC ,16,0}, 
{0x0F12, 0x0280 ,16,0},  //REG_2TC_PCFG_usWidth
{0x0F12, 0x01E0 ,16,0},  //REG_2TC_PCFG_usHeight
{0x0F12, 0x0005 ,16,0},  //REG_2TC_PCFG_Format
{0x0F12, 0x2EF0 ,16,0},  //REG_2TC_PCFG_usMaxOut4KHzRate
{0x0F12, 0x2ED0 ,16,0},  //REG_2TC_PCFG_usMinOut4KHzRate
{0x0F12, 0x0100 ,16,0},  //REG_2TC_PCFG_OutClkPerPix88
{0x0F12, 0x0800 ,16,0},  //REG_2TC_PCFG_uMaxBpp88
{0x0F12, 0x0052 ,16,0},  //REG_2TC_PCFG_PVIMask
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_OIFMask
{0x0F12, 0x01E0 ,16,0},  //REG_2TC_PCFG_usJpegPacketSize
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_usJpegTotalPackets
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_uClockInd
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_usFrTimeType
{0x0F12, 0x0001 ,16,0},  //REG_2TC_PCFG_FrRateQualityType
{0x0F12, 0x09C4 ,16,0},  //REG_2TC_PCFG_usMaxFrTimeMsecMult10 //4fps
{0x0F12, 0x029A ,16,0},  //REG_2TC_PCFG_usMinFrTimeMsecMult10 //15fps
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_bSmearOutput
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_sSaturation
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_sSharpBlur
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_sColorTemp
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_uDeviceGammaIndex
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_uPrevMirror
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_uCaptureMirror
{0x0F12, 0x0000 ,16,0},  //REG_2TC_PCFG_uRotation

//================================================================================================
// APPLY PREVIEW CONFIGURATION & RUN PREVIEW
//================================================================================================
{0x002A, 0x023C ,16,0},
{0x0F12, 0x0000 ,16,0}, // #REG_TC_GP_ActivePrevConfig // Select preview configuration_0
{0x002A, 0x0240 ,16,0},
{0x0F12, 0x0001 ,16,0}, // #REG_TC_GP_PrevOpenAfterChange
{0x002A, 0x0230 ,16,0},
{0x0F12, 0x0001 ,16,0}, // #REG_TC_GP_NewConfigSync // Update preview configuration
{0x002A, 0x023E ,16,0},
{0x0F12, 0x0001 ,16,0}, // #REG_TC_GP_PrevConfigChanged
{0x002A, 0x0220 ,16,0},
{0x0F12, 0x0001 ,16,0}, // #REG_TC_GP_EnablePreview // Start preview
//{0x0028, 0xD000 ,16,0},
//{0x002A, 0xB0A0 ,16,0},
//{0x0F12, 0x0000 ,16,0}, // Clear cont. clock befor config change
//{0x0028, 0x7000 ,16,0},
//{0x002A, 0x0222 ,16,0},
{0x0F12, 0x0001 ,16,0}, // #REG_TC_GP_EnablePreviewChanged
              
//================================================================================================
// SET CAPTURE CONFIGURATION_0
// # Foramt :JPEG
// # Size: QXGA
// # FPS : 10 ~ 7.5fps
//================================================================================================
{0x002A, 0x035C ,16,0},
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_CCFG_uCaptureModeJpEG
{0x0F12, 0x0800 ,16,0}, //#REG_0TC_CCFG_usWidth
{0x0F12, 0x0600 ,16,0}, //#REG_0TC_CCFG_usHeight
{0x0F12, 0x0005 ,16,0}, //#REG_0TC_CCFG_Format//5:YUV9:JPEG
{0x0F12, 0x2EF0 ,16,0}, //#REG_0TC_CCFG_usMaxOut4KHzRate
{0x0F12, 0x2ED0 ,16,0}, //#REG_0TC_CCFG_usMinOut4KHzRate
{0x0F12, 0x0100 ,16,0}, //#REG_0TC_CCFG_OutClkPerPix88
{0x0F12, 0x0800 ,16,0}, //#REG_0TC_CCFG_uMaxBpp88
{0x0F12, 0x0052 ,16,0}, //#REG_0TC_CCFG_PVIMask
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_CCFG_OIFMask
//WRITE 70000370 0600 //#REG_0TC_CCFG_usJpegPacketSize
//WRITE 70000372 0400  //08FC //#REG_0TC_CCFG_usJpegTotalPackets
{0x002A, 0x0374 ,16,0},
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_CCFG_uClockInd
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_CCFG_usFrTimeType
{0x0F12, 0x0002 ,16,0}, //#REG_0TC_CCFG_FrRateQualityType
{0x0F12, 0x0596 ,16,0}, //#REG_0TC_CCFG_usMaxFrTimeMsecMult10 //7.5fps
{0x0F12, 0x029A ,16,0}, //#REG_0TC_CCFG_usMinFrTimeMsecMult10 //15fps
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_CCFG_bSmearOutput
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_CCFG_sSaturation
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_CCFG_sSharpBlur
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_CCFG_sColorTemp
{0x0F12, 0x0000 ,16,0}, //#REG_0TC_CCFG_uDeviceGammaIndex
              
//================================================================================================
// SET CAPTURE CONFIGURATION_1 (Night Mode)
// # Foramt :JPEG
// # Size: 3M (2048x1536)
// # FPS : 10 ~ 7.5fps
//================================================================================================
{0x002A, 0x038A ,16,0}, 
{0x0F12, 0x0800 ,16,0},  //#REG_1TC_CCFG_usWidth
{0x0F12, 0x0600 ,16,0},  //#REG_1TC_CCFG_usHeight
{0x0F12, 0x0005 ,16,0},  //#REG_1TC_CCFG_Format
{0x0F12, 0x2EF0 ,16,0},  //#REG_1TC_CCFG_usMaxOut4KHzRate
{0x0F12, 0x2ED0 ,16,0},  //#REG_1TC_CCFG_usMinOut4KHzRate
{0x0F12, 0x0100 ,16,0},  //#REG_1TC_CCFG_OutClkPerPix88
{0x0F12, 0x0800 ,16,0},  //#REG_1TC_CCFG_uMaxBpp88
{0x0F12, 0x0052 ,16,0},  //#REG_1TC_CCFG_PVIMask
{0x0F12, 0x0000 ,16,0},  //#REG_1TC_CCFG_OIFMask
{0x002A, 0x03A0 ,16,0},  //#REG_1TC_CCFG_usJpegTotalPackets
{0x0F12, 0x0000 ,16,0},  //#REG_1TC_CCFG_uClockInd
{0x0F12, 0x0000 ,16,0},  //#REG_1TC_CCFG_usFrTimeType
{0x0F12, 0x0002 ,16,0},  //#REG_1TC_CCFG_FrRateQualityType
{0x0F12, 0x1388 ,16,0},  //#REG_1TC_CCFG_usMaxFrTimeMsecMult10
{0x0F12, 0x1388 ,16,0},  //#REG_1TC_CCFG_usMinFrTimeMsecMult10

//================================================================================================
// SET JPEG & SPOOF
//================================================================================================
{0x002A, 0x0454 ,16,0},
{0x0F12, 0x0055 ,16,0}, // #REG_TC_BRC_usCaptureQuality // JPEG BRC (BitRateControl) value // 85
//WRITE D000007A         0A02     // JPEG CLK off
//WRITE 70000450  0001  //#BRC_BRC_Type // JPEG inspection off

//================================================================================================
// SET THUMBNAIL
// # Foramt : RGB565
// # Size: VGA
//================================================================================================
{0x0F12, 0x0000 ,16,0}, //0001 // thumbnail disable
{0x0F12, 0x0140 ,16,0}, // Width//320 //640
{0x0F12, 0x00F0 ,16,0}, // Height //240 //480
{0x0F12, 0x0000 ,16,0}, // Thumbnail format : 0RGB565 1 RGB888 2 Full-YUV (0-255)
              

             
// Fill RAM wi ,16,0},th alternative op-codes
{0x002A, 0x2CE8 ,16,0},
{0x0F12, 0x0007 ,16,0}, // Modify LSB to control AWBB_YThreshLow
{0x0F12, 0x00E2 ,16,0}, //
{0x0F12, 0x0005 ,16,0}, // Modify LSB to control AWBB_YThreshLowBrLow
{0x0F12, 0x00E2 ,16,0}, //
             
/////////////////////////////////////////////////////////////////////////
// AFC - fix i ,16,0},f ( G_AFC_Confidence[G_AFC_SuspectedState] > AFC_CONFIDENCE_HIGH_THR ) condition to if ( G_AFC_Confidence[G_AFC_SuspectedState] > (10<<10) )
// Fill RAM wi ,16,0},th alternative op-codes
{0x002A, 0x2CE6 ,16,0},
{0x0F12, 0x220A ,16,0}, //  3 ==> A Modify AFC_CONFIDENCE_HIGH_THR
{0x002A, 0x3378 ,16,0},
{0x0F12, 0x0034 ,16,0}, //#Tune_TP_AFC_SCD_Thresh ==> Set > 0 to activate the SCD T&P code for AFC.
             
{0x002A, 0x10E2 ,16,0},
{0x0F12, 0x0006 ,16,0}, // 192, decay factor (using af_search_usCapturePolicy) ==> change to 230 ??
{0x002A, 0x10E0 ,16,0},
//{0x0F12, 0x0006 ,16,0}, // 8 frames wait for scene stable (using M_af_search_usFineMaxScale) ==> can vary between 4..10
             
// force zeroing of "G_AFC_Conf50_VerySlow" and "G_AFC_Conf60_VerySlow", (using M_af_stat_usG2)
             
{0x002A, 0x0C1E ,16,0},
{0x0F12, 0x0016 ,16,0}, // change "alpha" parameter from "0x10" to "0x16"
/////////////////////////////////////////////////////////////////////////
             
{0x0028, 0xD000 ,16,0},
{0x002A, 0x1000 ,16,0},
{0x0F12, 0x0001 ,16,0},              




