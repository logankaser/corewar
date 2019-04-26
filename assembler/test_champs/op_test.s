  .name "op_test"

.comment "op testing file"

#comment
label: #comment
live: live %1
		ld: ld 1 , r2
		ld :live,r1
		fork %1
