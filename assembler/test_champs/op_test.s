  .name "op_test"

.comment "op testing file"

#comment
live:live %1
#comment
live:	live %1
		ld :live, r2

		fork %:live
