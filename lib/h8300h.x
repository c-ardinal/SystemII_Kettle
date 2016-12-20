/*******************************************

  H8-3048F 用リンクスクリプト

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
	rom(rx)		: o = 0x00100, l = 0x1ff00	/* 内蔵ROM	*/
	ram(rwx)	: o = 0xfef10, l = 0x01000	/* 内蔵RAM	*/
	topram(rw)	: o = 0xffefc, l = 0x00004	/* 内蔵RAMの末尾	*/
}

/*
	SECTIONS での記述は以下の通り
	出力セクション [start-address] :
		{
			ファイル名(入力セクション[...])
			[...]
		}
	"*(.rodata)" は「入力ファイル中のすべての.rodataセクション」の意
	入力ファイル中のセクション名と出力ファイル中のセクション名はまったく独立
*/


SECTIONS
{
.vectors :
	{
	/* リセットベクタ */
	LONG(ABSOLUTE(_start))							/*  0: Reset vector	*/

	/* システム予約 */
	LONG(ABSOLUTE(_start))							/*  1: Reserved	*/
	LONG(ABSOLUTE(_start))							/*  2: Reserved	*/
	LONG(ABSOLUTE(_start))							/*  3: Reserved	*/
	LONG(ABSOLUTE(_start))							/*  4: Reserved	*/
	LONG(ABSOLUTE(_start))							/*  5: Reserved	*/
	LONG(ABSOLUTE(_start))							/*  6: Reserved	*/

	/* 外部割り込み */
	LONG(DEFINED(_int_nmi)?ABSOLUTE(_int_nmi):ABSOLUTE(_start))		/*  7: NMI	*/

	/* トラップ命令 */
	LONG(DEFINED(_int_trap0)?ABSOLUTE(_int_trap0):ABSOLUTE(_start))		/*  8: trap0	*/
	LONG(DEFINED(_int_trap1)?ABSOLUTE(_int_trap1):ABSOLUTE(_start))		/*  9: trap1	*/
	LONG(DEFINED(_int_trap2)?ABSOLUTE(_int_trap2):ABSOLUTE(_start))		/* 10: trap2	*/
	LONG(DEFINED(_int_trap3)?ABSOLUTE(_int_trap3):ABSOLUTE(_start))		/* 11: trap3	*/

	/* 外部割り込み */
	LONG(DEFINED(_int_irq0)?ABSOLUTE(_int_irq0):ABSOLUTE(_start))		/* 12: IRQ0	*/
	LONG(DEFINED(_int_irq1)?ABSOLUTE(_int_irq1):ABSOLUTE(_start))		/* 13: IRQ1	*/
	LONG(DEFINED(_int_irq2)?ABSOLUTE(_int_irq2):ABSOLUTE(_start))		/* 14: IRQ2	*/
	LONG(DEFINED(_int_irq3)?ABSOLUTE(_int_irq3):ABSOLUTE(_start))		/* 15: IRQ3	*/
	LONG(DEFINED(_int_irq4)?ABSOLUTE(_int_irq4):ABSOLUTE(_start))		/* 16: IRQ4	*/
	LONG(DEFINED(_int_irq5)?ABSOLUTE(_int_irq5):ABSOLUTE(_start))		/* 17: IRQ5	*/

	/* システム予約 */
	LONG(ABSOLUTE(_start))							/* 18: Reserved	*/
	LONG(ABSOLUTE(_start))							/* 19: Reserved	*/

	/* WDT(ウォッチドッグタイマ) */
	LONG(DEFINED(_int_wovi)?ABSOLUTE(_int_wovi):ABSOLUTE(_start))		/* 20: WOVI(インターバルタイマ)	*/
	LONG(DEFINED(_int_cmi)?ABSOLUTE(_int_cmi):ABSOLUTE(_start))		/* 21: CMI(コンペアマッチ)	*/

	/* システム予約 */
	LONG(ABSOLUTE(_start))							/* 22: Reserved	*/
	LONG(ABSOLUTE(_start))							/* 23: Reserved	*/

	/* ITUチャネル0 */
	LONG(DEFINED(_int_imia0)?ABSOLUTE(_int_imia0):ABSOLUTE(_start))		/* 24: IMIA0(コンペアマッチ/インプットキャプチャA0)	*/
	LONG(DEFINED(_int_imib0)?ABSOLUTE(_int_imib0):ABSOLUTE(_start))		/* 25: IMIB0(コンペアマッチ/インプットキャプチャB0)	*/
	LONG(DEFINED(_int_ovi0)?ABSOLUTE(_int_ovi0):ABSOLUTE(_start))		/* 26: OVI0(オーバーフロー0)	*/

	/* システム予約 */
	LONG(ABSOLUTE(_start))							/* 27: Reserved */

	/* ITUチャネル1 */
	LONG(DEFINED(_int_imia1)?ABSOLUTE(_int_imia1):ABSOLUTE(_start))		/* 28: IMIA1(コンペアマッチ/インプットキャプチャA1)	*/
	LONG(DEFINED(_int_imib1)?ABSOLUTE(_int_imib1):ABSOLUTE(_start))		/* 29: IMIB1(コンペアマッチ/インプットキャプチャB1)	*/
	LONG(DEFINED(_int_ovi1)?ABSOLUTE(_int_ovi1):ABSOLUTE(_start))		/* 30: OVI1(オーバーフロー1)	*/

	/* システム予約 */
	LONG(ABSOLUTE(_start))							/* 31: Reserved */

	/* ITUチャネル2 */
	LONG(DEFINED(_int_imia2)?ABSOLUTE(_int_imia2):ABSOLUTE(_start))		/* 32: IMIA2(コンペアマッチ/インプットキャプチャA2)	*/
	LONG(DEFINED(_int_imib2)?ABSOLUTE(_int_imib2):ABSOLUTE(_start))		/* 33: IMIB2(コンペアマッチ/インプットキャプチャB2)	*/
	LONG(DEFINED(_int_ovi2)?ABSOLUTE(_int_ovi2):ABSOLUTE(_start))		/* 34: OVI2(オーバーフロー2)	*/

	/* システム予約 */
	LONG(ABSOLUTE(_start))							/* 35: Reserved */

	/* ITUチャネル3 */
	LONG(DEFINED(_int_imia3)?ABSOLUTE(_int_imia3):ABSOLUTE(_start))		/* 36: IMIA3(コンペアマッチ/インプットキャプチャA3)	*/
	LONG(DEFINED(_int_imib3)?ABSOLUTE(_int_imib3):ABSOLUTE(_start))		/* 37: IMIB3(コンペアマッチ/インプットキャプチャB3)	*/
	LONG(DEFINED(_int_ovi3)?ABSOLUTE(_int_ovi3):ABSOLUTE(_start))		/* 38: OVI3(オーバーフロー3)	*/

	/* システム予約 */
	LONG(ABSOLUTE(_start))							/* 39: Reserved */

	/* ITUチャネル4 */
	LONG(DEFINED(_int_imia4)?ABSOLUTE(_int_imia4):ABSOLUTE(_start))		/* 40: IMIA4(コンペアマッチ/インプットキャプチャA4)	*/
	LONG(DEFINED(_int_imib4)?ABSOLUTE(_int_imib4):ABSOLUTE(_start))		/* 41: IMIB4(コンペアマッチ/インプットキャプチャB4)	*/
	LONG(DEFINED(_int_ovi4)?ABSOLUTE(_int_ovi4):ABSOLUTE(_start))		/* 42: OVI4(オーバーフロー4)	*/

	/* システム予約 */
	LONG(ABSOLUTE(_start))							/* 43: Reserved */

	/* DMAC */
	LONG(DEFINED(_int_dend0a)?ABSOLUTE(_int_dend0a):ABSOLUTE(_start))	/* 44: DEND0A	*/
	LONG(DEFINED(_int_dend0b)?ABSOLUTE(_int_dend0b):ABSOLUTE(_start))	/* 45: DEND0B	*/
	LONG(DEFINED(_int_dend1a)?ABSOLUTE(_int_dend1a):ABSOLUTE(_start))	/* 46: DEND1A	*/
	LONG(DEFINED(_int_dend1b)?ABSOLUTE(_int_dend1b):ABSOLUTE(_start))	/* 47: DEND1B	*/

	/* システム予約 */
	LONG(ABSOLUTE(_start))							/* 48: Reserved */
	LONG(ABSOLUTE(_start))							/* 49: Reserved */
	LONG(ABSOLUTE(_start))							/* 50: Reserved */
	LONG(ABSOLUTE(_start))							/* 51: Reserved */

	/* SCIチャネル0 */
	LONG(DEFINED(_int_eri0)?ABSOLUTE(_int_eri0):ABSOLUTE(_start))		/* 52: ERI0(受信エラー0)		*/
	LONG(DEFINED(_int_rxi0)?ABSOLUTE(_int_rxi0):ABSOLUTE(_start))		/* 53: RXI0(受信データフル0)	*/
	LONG(DEFINED(_int_txi0)?ABSOLUTE(_int_txi0):ABSOLUTE(_start))		/* 54: TXI0(送信データエンプティ0) */
	LONG(DEFINED(_int_tei0)?ABSOLUTE(_int_tei0):ABSOLUTE(_start))		/* 55: TEI0(送信終了0)		*/

	/* SCIチャネル1 */
	LONG(DEFINED(_int_eri1)?ABSOLUTE(_int_eri1):ABSOLUTE(_start))		/* 56: ERI1(受信エラー1)		*/
	LONG(DEFINED(_int_rxi1)?ABSOLUTE(_int_rxi1):ABSOLUTE(_start))		/* 57: RXI1(受信データフル1)	*/
	LONG(DEFINED(_int_txi1)?ABSOLUTE(_int_txi1):ABSOLUTE(_start))		/* 58: TXI1(送信データエンプティ1) */
	LONG(DEFINED(_int_tei1)?ABSOLUTE(_int_tei1):ABSOLUTE(_start))		/* 59: TEI1(送信終了1)		*/

	/* A/D */
	LONG(DEFINED(_int_adi)?ABSOLUTE(_int_adi):ABSOLUTE(_start))		/* 60: ADI(A/Dエンド)		*/
	}  > vectors

.text :
	{
	  *(.rodata)				/* 書換え不可能なデータ(定数)	*/
	  *(.text)				/* 実行プログラム			*/
	  *(.strings)				/* 文字列			*/
   	   _etext = . ;				/* "_etext" ラベルを定義		*/
	}  > rom

.tors :						/* C++ でいうコンストラクタ・デストラクタ	*/
	{
	  ___ctors = . ;
	  *(.ctors)
	  ___ctors_end = . ;
	  ___dtors = . ;
	  *(.dtors)
	  ___dtors_end = . ;
	} > rom

.data : 					/* 書換え可能で初期値を持つデータを配置	*/
	AT (ADDR(.tors)+SIZEOF(.tors)) {	/* 初期値は AT命令で ROM に配置		*/
	___data = . ;
	*(.data)
	 _edata = . ;
	}  > ram				/* 実行時に RAM に配置			*/

.bss :						/* 書換え可能で初期値を持たないデータを配置	*/
	{
	   _bss_start = . ;
	  *(.bss)
	  *(COMMON)
	   _end = . ;
	}  > ram

.stack :					/* スタックを配置				*/
	{
	   _stack = . ;
	  *(.stack)
	}  > topram
}
