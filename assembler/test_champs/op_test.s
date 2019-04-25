  .name "op_test"

.comment "op testing file"

#comment
ld:live %1
		ld: ld %1, r2
		ld 2,r1
		fork %:ld
