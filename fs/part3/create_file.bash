# for i in {1..40}
# do
# 	mkfile -n ${i}k "$i"
# done

for ((i=2048;i<=131072;i=i+i))
do
	mkfile -n ${i}k "$i"
done