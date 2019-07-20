.name "Charles Manson"
.comment "“We`re not in Wonderland anymore, Alice."

run:	sti r1, %:live, %1
		fork %100

live:	live %1
		zjmp %:run
