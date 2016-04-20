for i in {1..5}; do
			bin/predict \
				--nested-threads \
				--nthreads 24 \
				--nfeatures 290 \
				--nselected 11 \
				--popsize 50 \
				--ngen 100 \
				--proteins \
					input/Hidrolases/* \
					input/Isomerases/* \
					input/Liases/* \
					input/Ligases/* \
					input/Oxidoreductases/* \
					input/Transferases/* \
				1> 0.6-0.1-$i.out \
				2> 0.6-0.1-$i.err
done
