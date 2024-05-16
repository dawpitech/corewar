.name    "pdd"
.comment "pdd"

	sti	r1, %:live, %1 # copies the address of live: + 1 into r1
	fork	%:live         # creates a new process running live
begin:	ld	%76, r1        # r1 = [76]
	ld	%40, r6        # r6 = [40]
	ld	%1, r7         # r7 = [1]
	ld	%15, r4        # r4 = [15]
	ld	%15, r5        # r5 = [15]
	sub	r4, r5, r3     # r3 = r4 - r5
	zjmp	%:attack       # if ?
live:	live	%2             # send live
	ld	%0, r4         # loads addr 0 in r4
	zjmp	%:live         # if ??
attack:	ld	%65, r8        # r8 = [60]
	st	r8, 100        # copies r8 value to addr 100
	aff	r1             # shows r1 ?????
	add	r6, r7, r7     # r7 += r6
	sti	r7, r7, r1     # stores r7 value into r7 + r1
	ld	%15, r4        # r4 = [15]
	ld	%15, r5        # r5 = [15]
	sub	r4, r5, r3     # r3 = r4 - r5
	zjmp	%:attack       # if ?
