;;; 
;;; H8-3048F �ѥ������ȥ��åץե�����
;;; 

	.h8300h
	.section .text
	.global	_start
_start:
	;; �����å��ݥ��󥿤ν����
	mov.l	#_stack, sp

	;; ROM ����ǡ����򥳥ԡ�
	mov.l	#___dtors_end,er0
	mov.l	#_edata,er1
	mov.l	#___data,er2

.loop0:	mov.w	@er0,r3
	mov.w	r3,@er2
	adds	#2,er0
	adds	#2,er2
	cmp.l	er1,er2
	blo	.loop0
	
	;; clear BSS
	mov.l	#_edata,er0
	mov.l	#_end,er1
	mov.w	#0,r2

.loop:	mov.w	r2,@er0		; playing it safe for now
	adds	#2,er0
	cmp.l	er1,er0
	blo	.loop
	jsr	@___main
	jsr	@_main		; main() �򥳡���
	jsr	@_exit		; main() ����λ�����齪λ

	.section .stack
_stack:	.long 	1