	.name "Test"
	.comment "Ce programme te déteste."

	sti r1, %:hi, %1

hi:	live %234
        ld %5, r2
        ld %6, r3
        add r2, r3, r1
	ld %0, r3
	zjmp %:hi
