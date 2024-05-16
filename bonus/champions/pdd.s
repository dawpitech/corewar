.name    "pdd"
.comment "pdd"

	sti	r1, %:live, %1 # copies the address of live: + 1 into r1
	fork	%:live         # creates a new process running live
live:	live	%2             # send live
	ld	%0, r4         # loads addr 0 in r4
	zjmp	%:live         # if ??
