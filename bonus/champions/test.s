	.name "Test"
	.comment "Ce programme te déteste."

	sti r1, %:hi, %1
        fork %:hi

hi:	live %234
	ld %0, r3
