for i in {1..30}; do 
	bin/predict \
		--nested-threads \
		--nthreads 24 \
		--nfeatures 290 \
		--nselected 11 \
		--popsize 50 \
		--ngen 200 \
		--proteins \
			input/Hidrolases/* \
			input/Isomerases/* \
			input/Liases/* \
			input/Ligases/* \
			input/Oxidoreductases/* \
			input/Transferases/* \
		1> $i.out \
		2> $i.err 
done
