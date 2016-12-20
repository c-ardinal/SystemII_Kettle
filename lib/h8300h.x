/*******************************************

  H8-3048F �ѥ�󥯥�����ץ�

*******************************************/

OUTPUT_FORMAT("coff-h8300")	/* object format	: COFF		*/
OUTPUT_ARCH(h8300h)		/* default architecture	: H8/300H	*/
ENTRY("_start")			/* start from "_start" label		*/
/*
  Memory Map
  0x00000 - 0x000ff (0x00100 bytes)	: internal ROM Vector		(   256B)
  0x00100 - 0x1ffff (0x1ff00 bytes)	: internal ROM Area		(130816B)
  0xfef10 - 0xfff0f (0x01000 bytes)	: internal RAM Data Area	(  4096B)
  0xffefc - 0xffeff (0x00004 bytes)	: internal RAM Stack Area	(     4B)
*/
MEMORY
{	
	vectors(r)	: o = 0x00000, l = 0x00100
	rom(rx)		: o = 0x00100, l = 0x1ff00	/* ��¢ROM	*/
	ram(rwx)	: o = 0xfef10, l = 0x01000	/* ��¢RAM	*/
	topram(rw)	: o = 0xffefc, l = 0x00004	/* ��¢RAM������	*/
}

/*
	SECTIONS �Ǥε��Ҥϰʲ����̤�
	���ϥ�������� [start-address] :
		{
			�ե�����̾(���ϥ��������[...])
			[...]
		}
	"*(.rodata)" �ϡ����ϥե�������Τ��٤Ƥ�.rodata���������פΰ�
	���ϥե�������Υ��������̾�Ƚ��ϥե�������Υ��������̾�Ϥޤä�����Ω
*/


SECTIONS
{
.vectors :
	{
	/* �ꥻ�åȥ٥��� */
	LONG(ABSOLUTE(_start))							/*  0: Reset vector	*/

	/* �����ƥ�ͽ�� */
	LONG(ABSOLUTE(_start))							/*  1: Reserved	*/
	LONG(ABSOLUTE(_start))							/*  2: Reserved	*/
	LONG(ABSOLUTE(_start))							/*  3: Reserved	*/
	LONG(ABSOLUTE(_start))							/*  4: Reserved	*/
	LONG(ABSOLUTE(_start))							/*  5: Reserved	*/
	LONG(ABSOLUTE(_start))							/*  6: Reserved	*/

	/* ���������� */
	LONG(DEFINED(_int_nmi)?ABSOLUTE(_int_nmi):ABSOLUTE(_start))		/*  7: NMI	*/

	/* �ȥ�å�̿�� */
	LONG(DEFINED(_int_trap0)?ABSOLUTE(_int_trap0):ABSOLUTE(_start))		/*  8: trap0	*/
	LONG(DEFINED(_int_trap1)?ABSOLUTE(_int_trap1):ABSOLUTE(_start))		/*  9: trap1	*/
	LONG(DEFINED(_int_trap2)?ABSOLUTE(_int_trap2):ABSOLUTE(_start))		/* 10: trap2	*/
	LONG(DEFINED(_int_trap3)?ABSOLUTE(_int_trap3):ABSOLUTE(_start))		/* 11: trap3	*/

	/* ���������� */
	LONG(DEFINED(_int_irq0)?ABSOLUTE(_int_irq0):ABSOLUTE(_start))		/* 12: IRQ0	*/
	LONG(DEFINED(_int_irq1)?ABSOLUTE(_int_irq1):ABSOLUTE(_start))		/* 13: IRQ1	*/
	LONG(DEFINED(_int_irq2)?ABSOLUTE(_int_irq2):ABSOLUTE(_start))		/* 14: IRQ2	*/
	LONG(DEFINED(_int_irq3)?ABSOLUTE(_int_irq3):ABSOLUTE(_start))		/* 15: IRQ3	*/
	LONG(DEFINED(_int_irq4)?ABSOLUTE(_int_irq4):ABSOLUTE(_start))		/* 16: IRQ4	*/
	LONG(DEFINED(_int_irq5)?ABSOLUTE(_int_irq5):ABSOLUTE(_start))		/* 17: IRQ5	*/

	/* �����ƥ�ͽ�� */
	LONG(ABSOLUTE(_start))							/* 18: Reserved	*/
	LONG(ABSOLUTE(_start))							/* 19: Reserved	*/

	/* WDT(�����å��ɥå�������) */
	LONG(DEFINED(_int_wovi)?ABSOLUTE(_int_wovi):ABSOLUTE(_start))		/* 20: WOVI(���󥿡��Х륿����)	*/
	LONG(DEFINED(_int_cmi)?ABSOLUTE(_int_cmi):ABSOLUTE(_start))		/* 21: CMI(����ڥ��ޥå�)	*/

	/* �����ƥ�ͽ�� */
	LONG(ABSOLUTE(_start))							/* 22: Reserved	*/
	LONG(ABSOLUTE(_start))							/* 23: Reserved	*/

	/* ITU����ͥ�0 */
	LONG(DEFINED(_int_imia0)?ABSOLUTE(_int_imia0):ABSOLUTE(_start))		/* 24: IMIA0(����ڥ��ޥå�/����ץåȥ���ץ���A0)	*/
	LONG(DEFINED(_int_imib0)?ABSOLUTE(_int_imib0):ABSOLUTE(_start))		/* 25: IMIB0(����ڥ��ޥå�/����ץåȥ���ץ���B0)	*/
	LONG(DEFINED(_int_ovi0)?ABSOLUTE(_int_ovi0):ABSOLUTE(_start))		/* 26: OVI0(�����С��ե�0)	*/

	/* �����ƥ�ͽ�� */
	LONG(ABSOLUTE(_start))							/* 27: Reserved */

	/* ITU����ͥ�1 */
	LONG(DEFINED(_int_imia1)?ABSOLUTE(_int_imia1):ABSOLUTE(_start))		/* 28: IMIA1(����ڥ��ޥå�/����ץåȥ���ץ���A1)	*/
	LONG(DEFINED(_int_imib1)?ABSOLUTE(_int_imib1):ABSOLUTE(_start))		/* 29: IMIB1(����ڥ��ޥå�/����ץåȥ���ץ���B1)	*/
	LONG(DEFINED(_int_ovi1)?ABSOLUTE(_int_ovi1):ABSOLUTE(_start))		/* 30: OVI1(�����С��ե�1)	*/

	/* �����ƥ�ͽ�� */
	LONG(ABSOLUTE(_start))							/* 31: Reserved */

	/* ITU����ͥ�2 */
	LONG(DEFINED(_int_imia2)?ABSOLUTE(_int_imia2):ABSOLUTE(_start))		/* 32: IMIA2(����ڥ��ޥå�/����ץåȥ���ץ���A2)	*/
	LONG(DEFINED(_int_imib2)?ABSOLUTE(_int_imib2):ABSOLUTE(_start))		/* 33: IMIB2(����ڥ��ޥå�/����ץåȥ���ץ���B2)	*/
	LONG(DEFINED(_int_ovi2)?ABSOLUTE(_int_ovi2):ABSOLUTE(_start))		/* 34: OVI2(�����С��ե�2)	*/

	/* �����ƥ�ͽ�� */
	LONG(ABSOLUTE(_start))							/* 35: Reserved */

	/* ITU����ͥ�3 */
	LONG(DEFINED(_int_imia3)?ABSOLUTE(_int_imia3):ABSOLUTE(_start))		/* 36: IMIA3(����ڥ��ޥå�/����ץåȥ���ץ���A3)	*/
	LONG(DEFINED(_int_imib3)?ABSOLUTE(_int_imib3):ABSOLUTE(_start))		/* 37: IMIB3(����ڥ��ޥå�/����ץåȥ���ץ���B3)	*/
	LONG(DEFINED(_int_ovi3)?ABSOLUTE(_int_ovi3):ABSOLUTE(_start))		/* 38: OVI3(�����С��ե�3)	*/

	/* �����ƥ�ͽ�� */
	LONG(ABSOLUTE(_start))							/* 39: Reserved */

	/* ITU����ͥ�4 */
	LONG(DEFINED(_int_imia4)?ABSOLUTE(_int_imia4):ABSOLUTE(_start))		/* 40: IMIA4(����ڥ��ޥå�/����ץåȥ���ץ���A4)	*/
	LONG(DEFINED(_int_imib4)?ABSOLUTE(_int_imib4):ABSOLUTE(_start))		/* 41: IMIB4(����ڥ��ޥå�/����ץåȥ���ץ���B4)	*/
	LONG(DEFINED(_int_ovi4)?ABSOLUTE(_int_ovi4):ABSOLUTE(_start))		/* 42: OVI4(�����С��ե�4)	*/

	/* �����ƥ�ͽ�� */
	LONG(ABSOLUTE(_start))							/* 43: Reserved */

	/* DMAC */
	LONG(DEFINED(_int_dend0a)?ABSOLUTE(_int_dend0a):ABSOLUTE(_start))	/* 44: DEND0A	*/
	LONG(DEFINED(_int_dend0b)?ABSOLUTE(_int_dend0b):ABSOLUTE(_start))	/* 45: DEND0B	*/
	LONG(DEFINED(_int_dend1a)?ABSOLUTE(_int_dend1a):ABSOLUTE(_start))	/* 46: DEND1A	*/
	LONG(DEFINED(_int_dend1b)?ABSOLUTE(_int_dend1b):ABSOLUTE(_start))	/* 47: DEND1B	*/

	/* �����ƥ�ͽ�� */
	LONG(ABSOLUTE(_start))							/* 48: Reserved */
	LONG(ABSOLUTE(_start))							/* 49: Reserved */
	LONG(ABSOLUTE(_start))							/* 50: Reserved */
	LONG(ABSOLUTE(_start))							/* 51: Reserved */

	/* SCI����ͥ�0 */
	LONG(DEFINED(_int_eri0)?ABSOLUTE(_int_eri0):ABSOLUTE(_start))		/* 52: ERI0(�������顼0)		*/
	LONG(DEFINED(_int_rxi0)?ABSOLUTE(_int_rxi0):ABSOLUTE(_start))		/* 53: RXI0(�����ǡ����ե�0)	*/
	LONG(DEFINED(_int_txi0)?ABSOLUTE(_int_txi0):ABSOLUTE(_start))		/* 54: TXI0(�����ǡ�������ץƥ�0) */
	LONG(DEFINED(_int_tei0)?ABSOLUTE(_int_tei0):ABSOLUTE(_start))		/* 55: TEI0(������λ0)		*/

	/* SCI����ͥ�1 */
	LONG(DEFINED(_int_eri1)?ABSOLUTE(_int_eri1):ABSOLUTE(_start))		/* 56: ERI1(�������顼1)		*/
	LONG(DEFINED(_int_rxi1)?ABSOLUTE(_int_rxi1):ABSOLUTE(_start))		/* 57: RXI1(�����ǡ����ե�1)	*/
	LONG(DEFINED(_int_txi1)?ABSOLUTE(_int_txi1):ABSOLUTE(_start))		/* 58: TXI1(�����ǡ�������ץƥ�1) */
	LONG(DEFINED(_int_tei1)?ABSOLUTE(_int_tei1):ABSOLUTE(_start))		/* 59: TEI1(������λ1)		*/

	/* A/D */
	LONG(DEFINED(_int_adi)?ABSOLUTE(_int_adi):ABSOLUTE(_start))		/* 60: ADI(A/D�����)		*/
	}  > vectors

.text :
	{
	  *(.rodata)				/* �񴹤��Բ�ǽ�ʥǡ���(���)	*/
	  *(.text)				/* �¹ԥץ����			*/
	  *(.strings)				/* ʸ����			*/
   	   _etext = . ;				/* "_etext" ��٥�����		*/
	}  > rom

.tors :						/* C++ �Ǥ������󥹥ȥ饯�����ǥ��ȥ饯��	*/
	{
	  ___ctors = . ;
	  *(.ctors)
	  ___ctors_end = . ;
	  ___dtors = . ;
	  *(.dtors)
	  ___dtors_end = . ;
	} > rom

.data : 					/* �񴹤���ǽ�ǽ���ͤ���ĥǡ���������	*/
	AT (ADDR(.tors)+SIZEOF(.tors)) {	/* ����ͤ� AT̿��� ROM ������		*/
	___data = . ;
	*(.data)
	 _edata = . ;
	}  > ram				/* �¹Ի��� RAM ������			*/

.bss :						/* �񴹤���ǽ�ǽ���ͤ�����ʤ��ǡ���������	*/
	{
	   _bss_start = . ;
	  *(.bss)
	  *(COMMON)
	   _end = . ;
	}  > ram

.stack :					/* �����å�������				*/
	{
	   _stack = . ;
	  *(.stack)
	}  > topram
}
