  .name "op_test"

.comment "op testing file"

#comment

live:	live %1
		zjmp r2
		ld: ld 1 , r2
		ld :live,r1
		fork %1
